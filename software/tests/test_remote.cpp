#include <cstdlib>
#include <iostream>
#include <cstring>
#include "../firmware/BluetoothIrRemote/BluetoothIrRemote.ino"
static_assert(IR_SEND_PIN == 3, "reported transmit pin must remain D3");
SerialFake Serial;
SenderFake IrSender;
std::vector<unsigned long> delays;
static unsigned checks = 0;
void check(bool ok, const char* message) {
    ++checks;
    if (!ok) { std::cerr << "FAIL: " << message << '\n'; std::exit(1); }
}
// Independent literal oracle transcribed from printed report pp. 25-27.
const uint8_t expected[20] = {0x0C,0x10,0x11,0x38,0x58,0x59,0x5A,0x5B,0x5C,0xBF,
                            0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x00};
const char inputs[] = "0123456789ABCDEFGHIJ";
int main() {
    check(remote::kCommandCount == 20, "table count");
    for (unsigned b=0; b<256; ++b) {
        const auto* got = remote::lookup(static_cast<uint8_t>(b));
        const char* pos = b == 0 ? nullptr : std::strchr(inputs, static_cast<int>(b));
        if (pos != nullptr) {
            const auto i = static_cast<size_t>(pos-inputs);
            check(got != nullptr, "valid byte found");
            check(got->input == b && got->address == 0 && got->command == expected[i], "complete tuple");
        } else check(got == nullptr, "unsupported byte rejected");
    }
    for (size_t i=0; i<remote::kCommandCount; ++i)
        for (size_t j=i+1; j<remote::kCommandCount; ++j)
            check(remote::kCommands[i].input != remote::kCommands[j].input, "unique input");
    setup();
    check(Serial.baud == 9600 && IrSender.started, "setup");
    loop(); check(Serial.reads == 0 && IrSender.frames.empty() && delays.empty(), "idle");
    for (unsigned b=0; b<256; ++b) Serial.input.push_back(static_cast<int>(b));
    for (unsigned b=0; b<256; ++b) loop();
    check(Serial.input.empty() && Serial.reads == 256, "one read per queued byte");
    check(IrSender.frames.size() == 20 && delays.size() == 20, "one frame and delay per valid byte");
    for (size_t i=0; i<20; ++i) {
        const Frame& f=IrSender.frames[i];
        check(f.address == 0 && f.command == expected[i] && f.repeats == 0, "dispatch tuple and repeats");
        check(delays[i] == 40, "post-send delay request");
    }
    Serial.input.push_back(-1); loop();
    check(IrSender.frames.size() == 20 && delays.size() == 20, "read failure ignored");
    Serial.input.push_back('0'); Serial.input.push_back('0'); loop(); loop();
    check(IrSender.frames.size() == 22 && delays.size() == 22, "repeated commands retained");
    check(IrSender.frames[20].command == 0x0C && IrSender.frames[21].command == 0x0C, "repeat content");
    loop(); check(IrSender.frames.size() == 22, "no idle retransmission");
    std::cout << "PASS: " << checks << " checks; all 256 input bytes; 20 complete mappings; firmware dispatch with host doubles\n";
}
