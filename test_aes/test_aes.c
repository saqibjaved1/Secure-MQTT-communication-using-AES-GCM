/* 
This is the main test file where AES encryption along this GCM will be testes

Made by: Saad Bin Shams
Date: 6/6/18
Version: 1.0

Status: 06/06/2018 08:18:12 PM : Going to try and encrypt a 128 bit packet with AES encryption
- 06/07/2018 04:10:01 AM : Was able to compile the files for AES encryption. Trying to check a test vector for AES encryption. Only the first byte is printed. Maybe need a loop?
- 06/07/2018 04:35:27 AM : AES Encryption is working. Going to include AES-GCM files now. 
*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "aes-128.h"
#include <string.h>

int main(void){
	
	const uint8_t AES_KEY[16] = {0x2b, 0x7e,0x15, 0x16,
							0x28, 0xae,0xd2, 0xa6,
							0xab, 0xf7,0x15, 0x88,
							0x09, 0xcf,0x4f, 0x3c};
							
	uint8_t PLAIN_TEXT[16] = {0x6b, 0xc1,0xbe, 0xe2,
								0x2e, 0x40,0x9f, 0x96,
								0xe9, 0x3d,0x7e, 0x11,
								0x73, 0x93,0x17, 0x2a};
	// cipher 3ad77bb40d7a3660a89ecaf324
	// printing the plain text before encryption
	printf("Plain Text = ");
	
	for(int i = 0; i< sizeof(PLAIN_TEXT); i++)
		printf("%x", *(PLAIN_TEXT+i));
	
	printf("\nSize of AES KEY: %d\n", (int)sizeof(AES_KEY));
	printf("\nSize of PLAIN TEXT: %d\n", (int)sizeof(PLAIN_TEXT));
	// calling the set_key function
	
	set_key(AES_KEY);
	encrypt(PLAIN_TEXT);
	
	printf("\nSize of CIPHER TEXT: %d\n", (int)sizeof(PLAIN_TEXT));
	// printing the encrypted text
	
	printf("Cipher Text = ");
	
	for(int i = 0; i< sizeof(PLAIN_TEXT); i++)
		printf("%x", *(PLAIN_TEXT+i));

	printf("\n");	
	return(0);
}
