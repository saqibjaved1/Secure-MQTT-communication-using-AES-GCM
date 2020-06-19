# __Lab Report - IOT-LAB__ 

**Author:** Hassan, Muhammad Ammar

**Matr.:** 03693544

**Group:** 01       


## First part: Setup + Clone Sensortag ##

* **Date:** *08/05/2018*
* **Tasks:**          
 * Task 1
     * We first set up the virtual machine as specified in the instructions/Lab_Setup.md file. Then one Sensortag was attached to a debugger and flashed with the binaries/slip-radio.elf to connect the edge-router on the VM to the 6LoWPAN network. This Slip Sensortag is always connected to the computer via a debugger when the set up is running. Here we noted that the connection to any Sensortag device has to be enabled in the Virtualbox settings and it may take a short period for the device to be seen by the VM. Following this another Sensortag was flashed with the precompiled binaries/cc26xx-web-demoG1.elf. Here we noted that only one Sensortag must be connected to the computer before flashing. The functionality of the simple set up with the two mentioned Sensortags was then checked via the edge router's web interface.
 * Task 2
     * A third Sensortag was flashed with the binaries/sensniff.elf file and then the Slip Sensortag was reconnected. The sensniff/startSniff.sh script was then run and the correct channel for our group was set. After this we started Wireshark while taking instructions/Sniffing_the_wireshark_communication.md into consideration and observed the packets sent/received after powering up the Sensortag flashed with the precompiled binary. Our group's username and password credentials were found in a MQTT CONNECT command packet.
 * Task 3
     * The login credentials found were added to the relevant part of the contiki/examples/cc26xx/cc26xx-web-demo/cc26xx-web-demo.h header file and then this demo was compiled as mentioned in instructions/Sensortag.md. A fourth Sensortag was then flashed with the resulting binary. This Clone Sensortag and the "Original" Sensortag (with the precompiled binary) were then observed to be communicating correctly with the MQTT broker by viewing the sniffed packets in Wireshark.
 * Issues
     * One of the Sensortags (G2) appears to only work correctly if powered by via a cable. This may be an issue with the battery connector or something else. The lab TA was informed of this problem and it was decided that this Sensortag would be used as either the Slip or Sniffer instead of a client.
     
* **Date:** *15/05/2018*
* **Tasks:**          
 * Task 1
     * The working setup from the previous week was presented as required.
 * Task 2
     * It was decided that the group members would research and review literature and existing implementations relevant to part 2 of the lab and then meet again to divide tasks. 
 
## __Second part: Securing MQTT__ ##

* **Date:** *24/05/2018*
* **Tasks:**          
 * Task 1
     * For the literature review, I read over the AES standard available in the documentation folder and used it to understand the built-in AES-128 implementation found at contiki/core/lib. The implementation uses a 128-bit key for encryption and no decryption function is provided. I noted that the given implementation appears to be purely software based.
 * Task 2 
     * During our meeting, we discussed the findings of our literature reviews. A true random number generator was found at contiki_task2/cpu/cc26xx-cc13xx/random.c which uses the hardware TRNG available on the Sensortag. We then decided to meet up during the tutor hours on the upcoming tuesday to test the built-in functions found.
 
* **Date:** *29/05/2018*
* **Tasks:**          
 * Task 1
     * We first tried to use the built-in TRNG implementation. After talking to the tutor, we found that the random.c implementation for the TRNG overrides the software implementation. We then wrote a small piece of code in the publish function of the contiki_task2/examples/cc26xx/cc26xx-web-demo/mqtt-client.c in order to test the TRNG. A Sensortag was flashed with the resulting binary after compilation and then the output of the TRNG function calls was observed on the serial port by listening to the tty connection as mentioned in instructions/Sensortag.md. The output of the makefile after compilation was also checked to ensure that the correct random.c file is being used.
 * Task 2
     * The built-in AES-128 encryption function was then tested in a similar way after checking the API and making relevant changes to the contiki_task2/examples/cc26xx/cc26xx-web-demo/mqtt-client.c and contiki_task2/examples/cc26xx/cc26xx-web-demo/project-conf.h files. The output was observed by listening to the tty connection but since a decryption function is not available that was not tested.

* **Date:** *29/05/2018*
* **Tasks:**          
 * Task 1
     * We now decided to move forward with the AES-GCM implementation. After discussing the feasibility of making our own implementation, we deiced to instead search for existing implementations that could be integrated into our project. The most promising of these was found to be https://github.com/mko-x/SharedAES-GCM.
     * We read the API for this library and integrated the source files into our project however the project failed to compile because the AES implementation included was using too much memory due to the variable sizes and storage of the substitution tables. 
     * First, we attempted to modify the AES functionality included in the AES-GCM library, however this proved problematic so it was decided that we would attempt to integrate the built-in AES-128 with the AES-GCM library instead. Changes were made to the AES-GCM library to account for the function changes and the project compiled correctly but the output observed by listening to the tty connection was incorrect. The Test Case 1 available in documents/AES/gcm-spec.pdf was used for this test. The hash value H was however observed at the output so we decided to continue attempting to use the AES-GCM library.

* **Date:** *05/06/2018*
* **Tasks:**          
 * Task 1
     * I read over the AES documentation provided and used relevant web sources to help me understand the AES-GCM standard and to an extent the library we are attempting to integrate. 
 * Task 2
     * We met up during tutor hours on Tuesday and added some of the test cases available in documents/AES/gcm-spec.pdf to our code. Various compilation errors were corrected an then the output was tested again by listening to the API. Unfortunately, the outputs were all mostly still incorrect.
     * The tutor suggested we try to test the AES-GCM library locally in order to remove the layer of complexity added by testing and debugging on the Sensortag. 
 * Task 3
     * Saad was able to check the AES-GCM library locally, thus proving its correct functionality with the test vectors provided. I also tested his changes in order to understand what was previously wrong with our code.

* **Date:** *12/06/2018*
* **Tasks:**
 * Task 1
     * Relevant changes were made to the contiki_task2/examples/cc26xx/cc26xx-web-demo/mqtt-client.c again and compilation of the project was attempted. The resulting errors showed an issue with the usage of the malloc command in the AES-GCM so these were replaced with fixed variables instead, since the packet and array sizes are fixed in our implementation anyway.
     * After correcting minor errors with regard to printing, we observed the output again by listening to the tty connection and a correct output was observed. However, the tag value appeared to be incorrect occasionally which was bizarre. We debugged this by printing the tag value at various points of the code but it appeared to only change during the printing process and not inside any functions. This points to a potential issue with printing, though it is not really a requirement of our final implementation.

* **Date:** *14/06/2018*
* **Tasks:**
 * Task 1
     * We met up again in order to check the printing issue but were not able to solve it so instead we moved forward with attempting to form the correct packet format as described in the instructions available on the local machine at /IOT-LAB folder. The output was not completely correct and inconsistencies were again observed with the tag output.

* **Date:** *19/06/2018*
* **Tasks:**
 * Task 1
     * After the payload was set up according to the instructions provided on the local machine in the /IOT-LAB folder, we ignored the print issue and used the modified mosquito.sub provided to test decryption. While the tag and IV (the latter was set to a fixed value for initial tests) were correct, the payload output was incorrect. After discussing with the TA and observing the MQTT packets on wireshark, we tried to use the app_buffer variable as the pointer for the packet as suggested by the TA. This worked correctly though the reason is not quite clear at the moment.
 * Task 2
     * We discussed the upcoming presentation later on and decided on which parts of the presentation will be handled by which group member.