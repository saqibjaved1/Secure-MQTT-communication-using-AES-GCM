# __Lab Report - IOT-LAB__ 

**Author:** Rezabek Filip

**Matr.:** 03681147

**Group:** 01       


## __First part: Setup + Clone Sensortag ##

* **Date:** *08/05/2018*
* **Tasks:** 
* Task 1
* Setup VirtualBox with its proper parameters - follow instructions instructions/Lab_Setup.md. Result - everything went smoothly. Important part was flashing the Sensortag with provided compiled system .elf file (Slip-radio.elf). After this was done it is important to restart the VM and enable USB connection with given 6LoWPAN shield. Also very important for future have only one device connected in case you want to flash it, to avoid problems. Secondly, I had to flash the sensortag with precompiled contiki OS. We could verify functionality by opening the Web address, where is also visible in the future which Sensortags are connected and received data.
* Task 2
 After default setup was necessary to connect a sniffer (again needed to flash with sensniff.elf) and then start the Wireshark to sniff the password. Before opening the Wireshark it was important to change the listend channel - in our group it is 26. It was important to catch the MQTT Connect Command, which contains the password and user ID in a plain text. There were no problems on the way. Relevant information were in "instructions/Sniffing_the_wireshark_communication.md".
* Task 3
* Modify contiki header file to contain sniffed credentials (contiki/examples/cc26xx/cc26xx-web-demo/cc26xx-web-demo.h). I needed to run the command make cc26xx-web-demo BOARD=sensortag/cc2650 TARGET=srf06-cc26xx and then flash it with provided script (same as before). Validation of this task was possible with connecting two sensortags - one with original .elf and second one with modified file. Both were successfully connected to a broker and started to exchange communication.  

* ISSUES on the way: 1 sensortag is not working well, seems like a problem with a battery holder. Sniffer has a bit of delay, so it takes to see the actual communication in Wireshark. Second group presented in the room was listining on the same channel as us.
* Lab setup and TI boards are working well and it is robust if the setup steps are well followed. We presented the task 1 results later on to the tutor and also Thomas Schamberger on 15 May. 

## __Second part: Securing MQTT__ ##

* **Tasks:**          
 * Implementation of AES  
 * Implementation of RNG for the creation of the IV for GCM - 
 *  TRNG Sensortag
 *  Implementation of PRNG
 * Multiplication in GF(128)
 * GHASH Function – MAC 
 * GCTR Function –initialization vector

* **Date:** *22/05/2018*
* After getting familiar with the task we started with solving the problems and improve missing knowledge of AES-GCM, which was really important for solving our final goal. We also setup regular meeting on Tuesdays morning in the laboratory, where we worked together and in case needed seperated the tasks for the meeting in the following week.
* We started with contiki documentation and already implemented parts in the provided files. Very helpful was folder documents/Sensortag, AES and 6LoWPAN. First part of our work was to make sure we have TRNG and AES-128 as a base for our task, which worked and we were capable of re-use provided implementation on Contiki. We had to firstly verify the functionility by printing the values and calling specific API, to ensure we are using right code. Once we had that verified, we did similar for AES128. These 2 parts were our building blocks and following part was to include GCM part to ensure not only Confidentiality of data, but also Authenticity of given data. 

 
* **Date:** *29&31/05/2018*
For the purpose of GCM implementation we found a GitHub library from https://github.com/mko-x/SharedAES-GCM. This library included all AES-GCM functionality, however we wanted to reuse the functionality of given AES128, since this library was too generic and is providing unnecessary functionality for us. We took an advantage of free day, so we could meet and proceed. During this session we were able to include the project into our contiki files and start printing valid tag based on provided testing vectors. There was a challenge to ensure proper complete flow. 
 
* **Date:** *5&12/06/2018*
* Almost last step was to fix the final step, which required a lot of debugging. We tried to deploy the things separetely to our PCs without need of contiki to fasten the debugging. Saad made the biggest progress in that area to make it happen. Key role played the testing vectors, which were working and then we could move towards last part - preparing the payload, which contains data, Additional data and lastly generated Tag. Important part of the debugging was understading of overall AES-GCM. Very helpful for that were videos from "Christof Paar", channel "Introduction to Cryptography by Christof Paar", which provided great introduction to GF, AES steps - SubBytes, ShiftRows, MixColumns and AddRoundKey. AES-GCM standard explained well how is Authenticity ensured and what is the Tag used for. 

* **Date:** *19/06/2018*
* Last task before final presentation was the creation of Payload. This was done by modifying Publish function in the mqqt-client.c. Where the payload contatins cipher text (sensortag data), IV - generated with help of TRNG and Tag, which is an output of AES-GCM function. These changes were tested with modified mosquioto.sub, where could be seen at the end decrypted data. Everything looks great. 
 
* Issues: Integration of libraries to ensure our goal, important part was how the final tag was stored, so in case we wanted to store it as an output of gcm_encrypt function we were facing sometimes issues, as a result we decided the tag as a input to the function and work with (issues was most likely overwriting with data later on), next issue was creating new variable buffer, it also behaved not correctly and it was better to reuse already provided variables "app_buffer" and "app_buffer2."

Last step is to present about our journey on Thu 28 and then oral exam on 3 July. 