# Contiki program

The program used in the lab is the located at `/contiki/examples/cc26xx/cc26xx-web-demo`.

Explanation of the different files:

`cc26xx-web-demo.c`:
- Main program that is executed after the startup of the Sensortag.

`cc26xx-web-demo.h`: 
- Different settings of the application
- You can set the following parameters of the MQTT publisher here:
    + Username
    + Password
    + IPv6 Adress of the broker

`cetic-6lbr-client.c`:
- Client that sends UDP packets to the edge router in order to signal a connected Sensortag.

`httpd_simple.c` `http_simple.h`:
- Provides the web server to display the sensor values as a html site.

`mqtt-client.c` `mqtt-client.h`:
- Implementation of the MQTT client for the sensortag. The MQTT implementation is located at `/contiki/apps/mqtt`
- The `publish` function is used to publish the sensor values as an MQTT-message.

`project-conf.h`:
- Includes defines for netwerk parameters etc. this does not have to be changed by you.

## Adding own sources to the project

To add your own sources to the project you have to add them in the `Makefile`:
- Add the name of your c files at "PROJECT_SOURCEFILES".
- Header files are automatically included when located in the project directory `cc26xx-web-demo`.





