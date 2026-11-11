# IR command reference

## Television control (RC6)

The final TV controller accepts one **ASCII-compatible serial byte** per button. Each valid byte selects RC6 device address **`0x00`**, the command shown below and zero additional repeats.

| Function | Input character | Decimal byte | Hex byte | RC6 command |
| --- | --- | ---: | --- | --- |
| Power | `0` | 48 | `0x30` | `0x0C` |
| Volume up | `1` | 49 | `0x31` | `0x10` |
| Volume down | `2` | 50 | `0x32` | `0x11` |
| Source | `3` | 51 | `0x33` | `0x38` |
| Navigate up | `4` | 52 | `0x34` | `0x58` |
| Navigate down | `5` | 53 | `0x35` | `0x59` |
| Navigate left | `6` | 54 | `0x36` | `0x5A` |
| Navigate right | `7` | 55 | `0x37` | `0x5B` |
| Select | `8` | 56 | `0x38` | `0x5C` |
| Setup | `9` | 57 | `0x39` | `0xBF` |
| Digit 1 | `A` | 65 | `0x41` | `0x01` |
| Digit 2 | `B` | 66 | `0x42` | `0x02` |
| Digit 3 | `C` | 67 | `0x43` | `0x03` |
| Digit 4 | `D` | 68 | `0x44` | `0x04` |
| Digit 5 | `E` | 69 | `0x45` | `0x05` |
| Digit 6 | `F` | 70 | `0x46` | `0x06` |
| Digit 7 | `G` | 71 | `0x47` | `0x07` |
| Digit 8 | `H` | 72 | `0x48` | `0x08` |
| Digit 9 | `I` | 73 | `0x49` | `0x09` |
| Digit 0 | `J` | 74 | `0x4A` | `0x00` |

**Example:** Pressing Volume Up sends decimal byte **49** (ASCII `'1'`). The firmware finds `'1'` and issues `sendRC6(0x00, 0x10, 0)` through the selected infrared library.

App Inventor's `Send1ByteNumber(49)` sends **one byte**; sending the text `"49"` sends two characters and produces different commands. Unsupported bytes are ignored, and accepted inputs are followed by a 40 ms programmed delay.

## LED-strip development stage (NEC2)

An earlier controller profile used address `0x01` with these NEC2 commands:

| Input | Function | NEC2 command |
| --- | --- | --- |
| `0` | On/off | `0x47` |
| `1` | Brightness up | `0x04` |
| `2` | Brightness down | `0x05` |
| `3` | Red | `0x00` |
| `4` | Green | `0x01` |
| `5` | Blue | `0x42` |
| `6` | White | `0x43` |

The final repository's firmware is configured for **television RC6 commands**. The NEC2 table illustrates the earlier device-integration stage rather than a selectable runtime profile.
