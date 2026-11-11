# Bluetooth-to-Infrared Remote Controller

**Embedded systems · Arduino Uno · C/C++ · Bluetooth · Infrared protocols · Hardware validation**

A complete hardware-and-software remote-control system built for my final-year Electronic and Computer Engineering project at the University of Limerick (2023). An Android application communicates with an Arduino Uno over Bluetooth, allowing users to operate a television through infrared commands.

The project combined circuit design, microcontroller programming, wireless communication, infrared protocol decoding, iterative hardware testing and enclosure design. Development progressed from independent transmitter and receiver circuits to a working Bluetooth-controlled television remote.

![Completed Bluetooth infrared controller prototype](assets/prototype-2023.png)

## Engineering highlights

- **End-to-end integration:** Connected an Android app, HC-05 Bluetooth module, Arduino Uno and IR transmitter into one control system.
- **Communication protocols:** Decoded and reproduced NEC/NEC2 infrared commands for LED-strip testing and RC6 commands for television control.
- **Test-driven hardware development:** Built separate transmitter and receiver circuits to inspect transmitted codes before combining the subsystems.
- **Embedded command handling:** Mapped app button inputs to device-specific IR address and command values.
- **Product design:** Designed an enclosure in SolidWorks and assembled the final prototype in a 3D-printed housing.

## How the system works

![System architecture showing Android phone, HC-05, Arduino Uno and IR transmitter](assets/architecture-2026.svg)

1. The user selects a function in the **Android application**, created using MIT App Inventor.
2. The app sends a command character over **Bluetooth** to an HC-05 module.
3. The **Arduino Uno** reads the serial input at 9600 baud and selects the corresponding infrared command.
4. An **IR transmitter on digital pin D3** sends the signal to the television.

**Example:** The app's Volume Up button sends `'1'` (ASCII 49). The controller maps that input to RC6 address `0x00`, command `0x10`.

The [command reference](docs/commands.md) documents all 20 television controls. See [hardware and wiring](docs/hardware.md) for the circuit design and components.

## Development and demonstrated results

| Stage | What I built and demonstrated |
| --- | --- |
| Infrared decoding | Built an IR receiver circuit and decoded remote-control command, address and protocol information through the Arduino serial monitor. |
| Infrared transmission | Used a separate Arduino transmitter to reproduce captured commands and operate an LED strip. |
| Bluetooth control | Developed an Android interface and verified wireless commands by switching an Arduino-connected LED on and off. |
| System integration | Combined Bluetooth input and infrared output to control an LED strip, then adapted the system to operate a television. |
| Final assembly | Designed the enclosure in SolidWorks and assembled the working prototype. |

The [project evidence gallery](docs/evidence.md) includes prototype photographs, circuit assemblies, wiring diagrams and Android app screenshots from development.

## Firmware and software verification

The repository includes an **updated Arduino/C++ command-dispatch implementation**, reconstructed in 2026 from the documented interface of the 2023 prototype. Its history is explained in [project history](docs/project-history.md).

The implementation uses a fixed command table to translate Bluetooth serial inputs into IR commands, alongside host-side tests that check command dispatch without requiring a connected Arduino.

**Verified software results (Windows, 11 November 2026):**

- Standard build: **515 checks passed**.
- `NDEBUG` build: **515 checks passed**.
- All **256 possible input byte values** exercised; all **20 supported television commands** checked.

Run the tests from the repository root with Python 3 and a C++ compiler (`g++`):

```powershell
python software/tools/run_tests.py
```

The original 2023 hardware demonstrations and the later host-based software checks are separate forms of evidence; see [verification details](docs/verification.md) for the precise testing scope.

## Explore the project

| Resource | Contents |
| --- | --- |
| [Project evidence](docs/evidence.md) | Prototype photographs, circuit images, Android app and development stages |
| [Hardware and wiring](docs/hardware.md) | Components, wiring diagrams and signal paths |
| [Firmware implementation](docs/implementation.md) | Embedded software structure and communication workflow |
| [IR command reference](docs/commands.md) | Input characters, command addresses and protocols |
| [Firmware source](software/firmware/BluetoothIrRemote/BluetoothIrRemote.ino) | Reconstructed Arduino implementation |
| [Build and run](docs/build-and-run.md) | Local software test and target-build instructions |
| [Verification](docs/verification.md) | Test methodology and evidence |
| [Project history](docs/project-history.md) | Development timeline and source provenance |

---

*Matthew Coyle · Bachelor of Engineering, Electronic and Computer Engineering · University of Limerick*
