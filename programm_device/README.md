# Flash sensortag from command line

The following script can be used for programming.

Supported file types of the program:

 - .hex
 - .elf

Usage:

```bash
./flash_prog.sh <filename>
```


### Troubleshooting 


If there is any error use the script in */install_drivers*. It sets the udev rules for the TI debuggers. Make sure to execute the script as root.

__Warning__: The script overwrites existing rules in */etc/udev/71-ti-permissions.rules*.
