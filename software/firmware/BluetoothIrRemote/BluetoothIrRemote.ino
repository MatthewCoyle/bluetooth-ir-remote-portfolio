// 2026 reconstruction of the 2023 prototype controller; see docs/project-history.md.
// Target: Uno R3; Arduino AVR Boards 1.8.6; IRremote 4.4.1.
#include <Arduino.h>
#define IR_SEND_PIN 3
#define DISABLE_CODE_FOR_RECEIVER
#include <IRremote.hpp>
#include "RemoteCommands.h"

void setup() {
    Serial.begin(9600);
    IrSender.begin();
}

void loop() {
    if (Serial.available() <= 0) return;
    const int received = Serial.read();
    if (received < 0) return;
    const remote::IrCommand* command = remote::lookup(static_cast<uint8_t>(received));
    if (command == nullptr) return;
    IrSender.sendRC6(command->address, command->command, 0);
    delay(40); // Short post-send pause in the single-byte command loop.
}
