# CAN Test Rig

## About
A test rig for monitoring and creating CAN bus traffic using an STM32 F746ZG.

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
