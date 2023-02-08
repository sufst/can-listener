# CAN Test Rig

## About
A set of test rigs for monitoring and creating CAN bus traffic using an STM32 F746ZG.

## Usage

The following test rigs are currently available:

| Name                                 | Purpose                                          |          
|--------------------------------------|--------------------------------------------------|
| [Listener](./docs/CAN%20Listener.md) | Receive and print specific messages on a CAN bus |

Refer to the linked instructions for usage information.


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

## Creating New Test Rigs

- Each test rig is implemented in its own C and header files, usually as a thread.
- Tests are configured in the [configuration header](./src/SUFST/Inc/config.h). All test options should be set here with `#define` and prefixed with `CONFIG_`.
- The configuration header includes an option to disable each test rig. 
- The [top level test rig](./src/SUFST/Src/test_rig.c) instantiates all tests.
- New tests can use the [RTCAN](https://github.com/sufst/rtcan) instances provided by the top level test rig to interface with the CAN buses.
- While calling `printf()` (configured to write to UART3), threads must lock the `printf_mutex` provided by the top level test rig. While `printf()` is by itself thread safe, this mutex prevents mixing of printed outputs from different threads.

