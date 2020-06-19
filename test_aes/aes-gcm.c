//
//  aes-gcm.c
//  Pods
//
//  Created by Markus Kosmal on 20/11/14.
//
//

#include "aes-gcm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Saad: For the support of additioal data authentication, which usually used in packet authentication in communication, the arguments of the function "aes_gcm_encrypt()" need to add in fields fori) *add (pointer to additional data), ii) add_length (size_t variable). 

Which are then to be passed on the "gcm_crypt_tag() function in the place of "NULL" and "0" function arguments. 

*/



/* Adding the support for returning the tag to the main window after it is calculated. The tag will be a character pointer
*/

unsigned char* aes_gcm_encrypt(unsigned char* output, const unsigned char* input, int input_length, const unsigned char* key, const size_t key_len, const unsigned char * iv, const size_t iv_len, const unsigned char *add_data, size_t add_len){
    
    //int ret = 0;                // our return value
    gcm_context ctx;            // includes the AES context structure
    
    size_t tag_len = 16; // Setting the tag length to 16 bytes
    unsigned char *tag_buf;
    
    tag_buf = (unsigned char *)malloc(tag_len);
    
    memset(tag_buf,0x00,tag_len );
    
    // Printing transfers to the function****************************************************
  /*
    printf("\n\nAES GCM ENCRYPT Function...\n");
	printf("Plain Text = ");
	for(int i = 0; i< input_length; i++)
		printf("%x", *(input+i));

	printf("\nAES Key = ");
	for(int i = 0; i<key_len ; i++)
		printf("%x", *(key+i));
		
	printf("\nInitialization Vector = ");
	for(int i = 0; i< iv_len; i++)
		printf("%x", *(iv+i));
	
	*/		
	//***************************************************************************************
    gcm_setkey( &ctx, key, (const uint)key_len );
    
    gcm_crypt_and_tag( &ctx, ENCRYPT, iv, iv_len, add_data, add_len,
                            input, output, input_length, tag_buf, tag_len);
    
    gcm_zero_ctx( &ctx );

// returning the tag to main function. Delete this if not working properly at first.
/* read on the internet that malloc was necessary for returning a character pointer */
    
    return( tag_buf );
    
}

int aes_gcm_decrypt(unsigned char* output, const unsigned char* input, int input_length, const unsigned char* key, const size_t key_len, const unsigned char * iv, const size_t iv_len){
    
    int ret = 0;                // our return value
    gcm_context ctx;            // includes the AES context structure
    
    size_t tag_len = 0;
    unsigned char * tag_buf = NULL;
    
    gcm_setkey( &ctx, key, (const uint)key_len );
    
    gcm_crypt_and_tag( &ctx, DECRYPT, iv, iv_len, NULL, 0,
                            input, output, input_length, tag_buf, tag_len);
    
    gcm_zero_ctx( &ctx );
    
    return( ret );

}

