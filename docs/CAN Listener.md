# CAN Listener

## About

This test rig receives messages from a CAN bus and prints them to the UART3
serial port. Receiving is implemented using [RTCAN](https://github.com/sufst/rtcan)
and is limited to a predefined set of messages in [`config.h`](../src/SUFST/Inc/config.h).

## Configuration

This test rig is set up through the [configuration header](../src/SUFST/Inc/config.h).
The following settings are available:

| Macro Name                   | Values              | Description                                   |
|------------------------------|---------------------|-----------------------------------------------|
| `CONFIG_ENABLE_CAN_LISTENER` | `1` or `0`          | Enables/disables the test rig                 |
| `CONFIG_LISTEN_TO_CAN1`      | `1` or `0`          | Monitors and prints messages received on CAN1 | 
| `CONFIG_LISTEN_TO_CAN2`      | `1` or `0`          | Monitors and prints messages received on CAN2 | 
| `CONFIG_CAN1_NAME`           | C string            | Custom name to identify CAN1 bus              |
| `CONFIG_CAN2_NAME`           | C string            | Custom name to identify CAN2 bus              |
| `CONFIG_CAN1_LISTEN_IDS`     | Array of `uint32_t` | List of CAN IDs to listen for on CAN1         |
| `CONFIG_CAN2_LISTEN_IDS`     | Array of `uint32_t` | List of CAN IDs to listen for on CAN2         |

## Hardware Setup

Setup:
1. Connect the CAN1 or CAN2 Tx and Rx pins of the STM32 to a CAN transceiver.
2. Connect the CAN transceiver to the CAN bus to be listened to.
3. Build and flash the code.
4. Connect the STM32 to your computer using a micro USB cable and open a serial 
   monitor (PuTTY, `screen`, `minicom`, etc) at 115200 baud.
5. Reset the STM32.

Info about received messages is sent to UART3 and looks like:

```text
Bus:     CAN1
Tick:    75030
ID:      0x100
Length:  8
Data:    0xff03000000000000
```

Make sure that:
- Devices on the CAN bus which you want to listen to operate at 500kbps (in line 
  with everything CAN on the car).
- The serial connection is configured to 115200 baud, no parity, 1 stop bit.

## Limitations
- It is likely that because of the serial printing, if the CAN bus utilisation
  gets really high or messages arrive very close to each other, the listener
  won't be able to keep up.
- If you want to actually monitor and log CAN bus messages during testing, use 
  the L120 datalogger.
