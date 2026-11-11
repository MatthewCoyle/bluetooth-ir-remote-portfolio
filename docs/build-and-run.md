# Build and run

## 1. Run automated tests (Windows / PowerShell)

**Requirements:** Python 3 and a GCC-compatible `g++` compiler. On Windows, the MSYS2 UCRT64 toolchain is suitable. No third-party Python packages are required.

From the project root:

```powershell
python software/tools/run_tests.py
```

If `g++` is not on your PATH:

```powershell
python software/tools/run_tests.py --compiler 'C:\msys64\ucrt64\bin\g++.exe'
```

The runner builds and executes the tests in both standard and `-DNDEBUG` configurations and returns a nonzero exit code on failure. Temporary executables are written to the ignored `build/` directory. To save a fresh JSON result:

```powershell
python software/tools/run_tests.py --report build/host-tests.json
```

## 2. Build firmware for Arduino Uno

The reconstructed firmware targets **Arduino Uno R3**, **Arduino AVR Boards 1.8.6** and **IRremote 4.4.1**. Install Arduino CLI and run:

```powershell
arduino-cli core update-index
arduino-cli core install arduino:avr@1.8.6
arduino-cli lib install 'IRremote@4.4.1'
arduino-cli compile --fqbn arduino:avr:uno --warnings all software/firmware/BluetoothIrRemote
```

Alternatively, use the Arduino IDE with the equivalent board and library versions. The host test suite has been run successfully; the target Arduino compile still needs to be performed using the real AVR core and IRremote library.

## 3. Validate with hardware

1. Check module voltage ratings and connections against the [hardware reference](hardware.md).
2. Disconnect the HC-05 TX/RX wiring while uploading code to the Uno; reconnect for Bluetooth operation.
3. Match the HC-05's configured **data-mode baud rate** to the sketch's `Serial.begin(9600)`.
4. For a USB serial bench test, keep Bluetooth disconnected and send ASCII `0` or `1` at 9600 baud. The output is infrared, not a serial response.
5. Use a separate IR receiver to inspect the actual protocol/address/command before attempting television control.
6. Connect an Android App Inventor interface using the [single-byte command contract](commands.md).

The physical tests above are a repeatable plan for a new hardware build, rather than recorded results of the 2026 reconstruction.
