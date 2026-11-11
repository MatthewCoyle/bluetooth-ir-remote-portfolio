#pragma once
#include <stdint.h>
#include <stddef.h>

// RC6 TV command mapping reconstructed in 2026 from the 2023 controller design.
namespace remote {
struct IrCommand { uint8_t input; uint8_t address; uint8_t command; };
static constexpr IrCommand kCommands[] = {
    {'0', 0x00, 0x0C}, // power
    {'1', 0x00, 0x10}, // volume_up
    {'2', 0x00, 0x11}, // volume_down
    {'3', 0x00, 0x38}, // source
    {'4', 0x00, 0x58}, // up
    {'5', 0x00, 0x59}, // down
    {'6', 0x00, 0x5A}, // left
    {'7', 0x00, 0x5B}, // right
    {'8', 0x00, 0x5C}, // select
    {'9', 0x00, 0xBF}, // setup
    {'A', 0x00, 0x01}, // digit_1
    {'B', 0x00, 0x02}, // digit_2
    {'C', 0x00, 0x03}, // digit_3
    {'D', 0x00, 0x04}, // digit_4
    {'E', 0x00, 0x05}, // digit_5
    {'F', 0x00, 0x06}, // digit_6
    {'G', 0x00, 0x07}, // digit_7
    {'H', 0x00, 0x08}, // digit_8
    {'I', 0x00, 0x09}, // digit_9
    {'J', 0x00, 0x00}, // digit_0
};
static constexpr size_t kCommandCount = sizeof(kCommands) / sizeof(kCommands[0]);
inline const IrCommand* lookup(uint8_t input) {
    for (size_t i = 0; i < kCommandCount; ++i) {
        if (kCommands[i].input == input) return &kCommands[i];
    }
    return nullptr;
}
} // namespace remote
