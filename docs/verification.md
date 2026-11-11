# Testing and verification

## Prototype testing (2023)

The prototype was developed with staged functional tests: decode IR input, send known signals to a receiver, control an LED over Bluetooth, operate an LED strip through infrared, and finally control television functions through the Android app. See the [photographs and milestones](evidence.md).

## Reconstructed firmware tests (2026)

The current [automated host test](../software/tests/test_remote.cpp) compiles the firmware dispatch logic with test doubles representing the Arduino serial and IRremote interfaces.

| Test area | Verified behaviour |
| --- | --- |
| Input domain | All 256 possible byte values are processed against the command lookup |
| Command values | Complete expected address/command pairs for all 20 valid inputs |
| Invalid bytes | Unsupported input does not invoke infrared transmission |
| Firmware dispatch | Valid bytes produce the corresponding sender call |
| Initialization and timing requests | Serial setup, IR initialization and programmed post-send delay |
| Build configurations | Standard and `-DNDEBUG`, with C++11 and warnings treated as errors |

**Results:** 515 checks pass in each build configuration. The suite passed on Windows with the user's MSYS2/GCC toolchain on **11 November 2026**; a separate Linux run also passed. Saved results from the original test environment are in [host-tests.json](../evidence/host-tests.json).

Run the checks yourself:

```powershell
python software/tools/run_tests.py
```

## Verification scope

Automated checks validate **command-table logic and calls to the infrared interface**, not electrical signals or physical TV response. The reconstructed sketch still requires an Arduino/AVR build and hardware validation if it is to be deployed to a new device; the [build guide](build-and-run.md) describes that process.
