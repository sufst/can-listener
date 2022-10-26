# CAN Listener

## About
A quick test tool for monitoring messages on a CAN bus using an STM32 F746ZG.

## Usage
Setup:
1. Connect the CAN1 Tx and Rx pins of the STM32 to a CAN transceiver.
2. Connect the CAN transceiver to the CAN bus to be listened to.
3. Build and flash the code.
4. Connect the STM32 to your computer using a micro USB cable and open a serial 
   monitor (PuTTY, `screen`, `minicom`, etc) at 115200 baud.
5. Reset the STM32.

Info about received messages is sent to UART3 and looks like:

```text
Time:    0
ID:      1af
Length:  2
Data:    f300
```

Make sure that:
- Devices on the CAN bus which you want to listen to operate at 1Mbps (in line 
  with everything CAN on the car).
- The serial connection is configured to 115200 baud, no parity, 1 stop bit.

## Building
You will need the [GNU ARM Embedded toolchain](https://developer.arm.com/downloads/-/gnu-rm) and `make` on your path. To build, run:

```sh
make -s
```

Add `-j $(nproc)` for a parallelised build.

## Flashing
You will need the [STLink toolset](https://github.com/stlink-org/stlink) on your
path. To flash, run:

```sh
make flash -s
```

## Limitations / Disclaimer
- This code is intended purely as a quick testing/debugging tool, not for 
  integration into any other projects.
- It is likely that because of the serial printing, if the CAN bus utilisation
  gets really high or messages arrive very close to each other, the listener
  won't be able to keep up.
- If you want to actually monitor and log CAN bus messages during testing, use 
  the L120 datalogger.