# __Lab Report - IOT-LAB__ 

**Author:** Shams, Saad Bin

**Matr.:** 03693218

**Group:** 01       


## __First part: Setup + Clone Sensortag ##

* **Date:** *08/05/2018*
* **Tasks:**          
 
 * Task 1
	* The first task that we performed was to setup the virtual machine following the instructions in the instructions from "instructions/Lab_Setup.md" file. 
	* We then flashed one of the sensor tags by attaching to the debugger and set it up as an edge router. We flashed it with the "*.elf" file provided to us, which was "binaries/slip-radio.elf". This was to serve as the edge router for the 6LoWPAN network. With the MQTT router running on the Virtual Machine which was setup earlier. 
	* We then flashed another sensor tag with the already provided  "binaries/cc26xx-web-demoG1.elf". We turned the sensor tag on by inserting the battery inside the battery bay. It took some time to connect to the edge router. When it was connected we were able to see a connected device on the web portal of the Virtual Machine. After we went to the "web" page of the sensor tag connected we were able to the sensor values that were being sent by the sensor to the edge router. 
	
 * Task 2
 	* We then flashed another sensor tag and set it up as a sniffer of MQTT packets. We flashed it with the already provided "binaries/sensniff.elf" file. The "sensniff/startSniff.sh" script was then run and the channel "26" which was allotted to our group was set up. After this we started Wireshark following the instructions in "instructions/Sniffing_the_wireshark_communication.md" 
 	* We then observed the sent and received packets after powering up the devices in the following order "Edge-Router>Sniffer>Sensor-Tag". Then the group's username and password credentials were found in the MQTT CONNECT command packet. 
 	
 * Task 3
	* The login credentials found were added to the relevant part of the "contiki/examples/cc26xx/cc26xx-web-demo/cc26xx-web-demo.h" header file and then this demo was compiled following the instructions in "instructions/Sensortag.md". Then after we were able to compile this program we then flashed it onto another sensor tag and cloning of the sensor tag was complete after we were able to connect to the edge router using the group's assigned credentials. 

 * Problems
	* One of the sensor tags presented to be problematic. It was not running properly with the battery and then it was powered by another debugger, which was provided by the TA. 
	* When we were sniffing for the MQTT CONNECT package to find our credentials for cloning we were getting "Group 2's" packets. We then found out that they were actually using our channel. After their cloned tag was flashed again with the proper channel. 
 
* **Date:** *15/05/2018*
* **Tasks:**          
 * Task 1
 	* The working setup with the cloned sensor tag was shown to the Lab Instructor. 
 * Task 2
 	* After a brief meeting with the group we decided that we will meet up again after doing a thorough literature review of the sensor tags, AES-GCM, contiki libraries. 
 
## __Second part: Securing MQTT__ ##

* **Date:** *24/05/2018*
* **Tasks:**          
 * Task 
 	* After doing a literature review we found that there were built in functionalities of encrypting with AES built inside the "contiki/core" library. And also a "true random number generator" was also included. We decided to meet up on a tutor on the coming tuesday to test out the already present functions. 

* **Date:** *29/05/2018*
* **Tasks:**          
 * Task 1
 	* We were able to run the "AES-128" library in the contiki operating system. It was using a 128-bit key to encrypt a 128 bit block of plain text. 
 	* We were also able to test the "True Random Number Generator".
 	* All of these were testing on the debugger mode by listening on the tty connection of the debugger with the connecting sensor tag attached to it. 

* **Date:** *31/05/2018*
* **Tasks:**          
 * Task 1
 	* We found a library by "Markus Kosmal" for AES-GCM implementation. It had its own implementation of AES. We included this in our project to see if we could use it for AES-GCM in our project. 
 	* After successfully including this in our project we compiled the program but we got an error that the size of the code is larger that the ROM. 
 	* We then looked inside the library and saw that that its AES file was populating its forward and reverse substitution table for both Encryption and Decryption, and this was occupying a lot of space in the memory. 
 	* We then worked on using our contiki's AES_encryption, which was working perfectly, in tandem with the GCM implementation we found on GitHub.
 	* After spending quite some time on it we were able to run the library but were not getting the desired outputs from the AES_GCM_ENCRYPT function.
 	* But the output encryption was in fact showing us the HASH=E(K,0) output, according to the Test Vector provided to us. Therefore we established that this was in fact a promising library and would be useful for us. 

* **Date:** *05/06/2018*
* **Tasks:**          
 * Task 1
 	* Over the weekend we spent time understanding the standard of AES and GCM. Did some correction work on the visible errors in our AES-GCM tandem. 
 	* We then met again on the tutor hours on Tuesday and wrote some test cases according to the Test Vectors provided to us. 
 	* After several compilation errors we were able to compile the program and test it. However, the problems were still present and we were not getting the desired outputs according to the test vectors. 
 	* The tutor advised us that we first get the AES-GCM running locally on our system so that we are certain that we are not getting any segmentation faults in our program, because otherwise it would be tremendously hard for us to debug the problem on the sensor tag's debugger. 
 	
 * Task 2
 	* Over the weekend I spend quite some time reading and understanding the AES encryption library and the GCM mode library on they were working separately. 
 	* I was then able to set up contiki library's AES encryption locally on my system. 
 	* I then worked on debugging the errors and warnings that presented themselves as I moved through the library functions for AES-GCM encryption. 
 	* After much travail I was able to get the desired outputs according to the Test Vectors provided to us. After refactoring the code for our requirement and removing it's dependence on its inherent AES library I incorporated the changes in our on-line sensor tag implementation for testing in the coming tutor hours. 
 	* In the coming tutor hours we plan to test the AES-GCM encryption on the sensor tags but viewing our outputs on the serial monitor. 
 	* Furthermore we plan to develop our strategy for securing communication for the sensor tags with encrypted sensor data using AES-GCM. 
 
* **Date:** *12/06/2018*
* **Tasks:**          
 * Task 1
 * Task 2
