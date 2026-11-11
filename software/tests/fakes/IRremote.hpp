#pragma once
// Host test double only. Does not emulate the library, timers or waveforms.
#include <stdint.h>
#include <vector>
struct Frame { uint8_t address; uint8_t command; int repeats; };
struct SenderFake {
    bool started = false;
    std::vector<Frame> frames;
    void begin() { started = true; }
    void sendRC6(uint8_t address, uint8_t command, int repeats) {
        frames.push_back({address, command, repeats});
    }
};
extern SenderFake IrSender;
