# TI Sensortag

The documentation for the Sensortag can be found in `/Documents`.
You are given the:
- Microcontroller datasheet
- Reference manual of the microcontroller
- Schematics
- Instruction for using GDB with the Sensortag

## Compiling contiki for the sensortag

The contiki program we are using in this lecture is located in the folder `/contiki/examples/cc26xx/cc26xx-web-demo`:

It can be compiled with the following command:
```bash
make cc26xx-web-demo BOARD=sensortag/cc2650 TARGET=srf06-cc26xx
```

The program is then compiled as:
- cc26xx-web-demo.elf

## Flashing a program onto the sensortag

To flash an `.elf` or `.hex` file onto the sensortag you have to use the programming script provided in `/Programm_device`:
```bash
./flash_prog.sh <binary in .hex or .elf format> 
```

## Debugging

The debugger is creating two serial devices when connected to a PC. You can find out the names of this two devices with:
```bash
dmesg | grep tty
```
They are usually called `/dev/ttyACM0` and `/dev/ttyACM1`.
You can use `screen` or other programs to connect to the serial port:
```bash
screen /dev/tty<correct device number> 115200
```

Your debugging messages or data can be send out trough this serial port by calling  `printf(<DATA>)` from  contiki.