/* 
This is the main test file where AES encryption along this GCM will be testes

Made by: Saad Bin Shams
Date: 6/6/18
Version: 1.0

Status: 06/06/2018 08:18:12 PM : Going to try and encrypt a 128 bit packet with AES encryption
- 06/07/2018 04:10:01 AM : Was able to compile the files for AES encryption. Trying to check a test vector for AES encryption. Only the first byte is printed. Maybe need a loop?
- 06/07/2018 04:35:27 AM : AES Encryption is working. Going to include AES-GCM files now. 
- 06/07/2018 05:31:08 AM : New file created for AES-GCM.
- 06/11/2018 07:06:51 AM : Test Case 4 tested and is working perfectly. 
*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "aes-gcm.h"
#include <string.h>

int main(void){

	unsigned char *tag;
	
	//Initialization Vector for AES-GCM 	
	unsigned char iv[] = {0xca, 0xfe, 0xba, 0xbe, 0xfa, 0xce, 0xdb, 0xad, 0xde, 0xca, 0xf8, 0x88};
	
	const unsigned char key[16] = {0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c, 0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08};
							
	unsigned char plainText[] = {0xd9, 0x31, 0x32, 0x25, 0xf8, 0x84, 0x06, 0xe5, 0xa5, 0x59, 0x09, 0xc5, 0xaf, 0xf5, 0x26, 0x9a, 0x86, 0xa7, 0xa9, 0x53, 0x15, 0x34, 0xf7, 0xda, 0x2e, 0x4c, 0x30, 0x3d, 0x8a, 0x31, 0x8a, 0x72, 0x1c, 0x3c, 0x0c, 0x95, 0x95, 0x68, 0x09, 0x53, 0x2f, 0xcf, 0x0e, 0x24, 0x49, 0xa6, 0xb5, 0x25, 0xb1, 0x6a, 0xed, 0xf5, 0xaa, 0x0d, 0xe6, 0x57, 0xba, 0x63, 0x7b, 0x39};
	
	unsigned char add_data_tag[] = {0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef, 0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef, 0xab, 0xad, 0xda, 0xd2};
	
	unsigned char *encryptedText;
	
	encryptedText = (unsigned char *)malloc(sizeof(plainText));
	
	
	printf("\n\nMain Function...\n");
	printf("Plain Text ( %d ) = ", (int)sizeof(plainText));
	for(int i = 0; i< sizeof(plainText); i++)
		printf("%x", *(plainText+i));
	printf("\nAES Key = ");
	for(int i = 0; i< sizeof(key); i++)
		printf("%x", *(key+i));
	printf("\nInitialization Vector ( %d ) = ", (int)sizeof(iv));
	for(int i = 0; i< sizeof(iv); i++)
		printf("%x", *(iv+i));
	printf("\nAdditional Data ( %d ) = ", (int)sizeof(add_data_tag));
	for(int i = 0; i< sizeof(add_data_tag); i++)
		printf("%x", *(add_data_tag+i));

	
	// Calling the AES-GCM fucntion for authenticated Encryption
	tag = aes_gcm_encrypt(encryptedText, plainText, (int)sizeof(plainText), key, (size_t)sizeof(key), iv, (size_t)sizeof(iv), add_data_tag, sizeof(add_data_tag));
	
	// printing the plain text before encryption
	printf("\n\nBACK TO Main Function...\n");
	/*
	printf("Plain Text = ");
	for(int i = 0; i< sizeof(plainText); i++)
		printf("%x", *(plainText+i));
	
	printf("\nSize of AES KEY: %d\n", (int)sizeof(key));
	printf("Size of PLAIN TEXT: %d\n", (int)sizeof(plainText));
	// calling the set_key function
	
	printf("Size of CIPHER TEXT: %d\n", (int)sizeof(plainText));
	*/
	// printing of tag which was calculated
	printf("\nSize of Tag: 16");
	printf("\nTag = ");
	for(int i = 0; i< 16; i++)
		printf("%x", *(tag+i));
	
	// printing the encrypted text
	
	printf("\nCipher Text ( %d )= ", (int)sizeof(plainText));
	
	for(int i = 0; i< sizeof(plainText); i++)
		printf("%x", *(encryptedText+i));

	printf("\n");
	
	
	//*******************************************************************************************
	// Code for testing if static variable round_keys of AES is accessible here or not. And its not. 
	/*
	for(int i = 0; i<80;i++)
		printf("*");
	
	printf("\n");
	
	for(int i=0 ; i<11 ; i++){
		for(int j = 0; j<16 ; j++){
			printf("%x",round_keys[i][j]);
		}
		printf("\n");
	}
	*/
	
	free(encryptedText);
	return(0);
}
