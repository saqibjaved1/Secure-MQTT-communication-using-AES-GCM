# Wireshark to capture packets

You are given a compiled program for the sensortag that is able to capture packets on a chosen channel and transmit them trough UART to the LAB PC.

In the folder `/sensniff` there is a script `sensniff.sh` which receives the packets and write them to a pipe `/tmp/sensniff`. This pipe can then be viewed with wireshark. The VM provides a user "wireshark" that can be used to access for this purpose (don't use it on the lab PCs because you don't have access rights).

You have to make sure that the script is sniffing on the correct channel. You can change the channel by typing your number and pressing enter.

If you are using wireshark for first time make sure the following settings are correct:

- Edit->Preferences->Protocols->6LowPAN : add "fd00::" to Context 0:
- Edit->Preferences->IEEE802.15.4 : Check box at "TI CC24xx FCS format"

Start the capturing process with:
Capture -> Options -> Manage Interfaces -> New : In Register "Pipe" add /tmp/sensniff  

Now you should see the packages on the chosen channel.

## Installation on your own machine (Not guarantied to work)

```bash
sudo apt-get install wireshark
```

The packetsniffer python script has to be started with the following parameters:

```bash
# python sensniff.py -d <uart-device> -D INFO -b <baudrate of uart>
# uart-device = check with "dmesg | grep tty", usually ttyACM0
# baudrate of uart = see CC26XX_UART_CONF_BAUD_RATE in /srf06-cc26xx/target-conf.h
python sensniff.py -d /dev/ttyACM0 -D INFO -b 460800
```

