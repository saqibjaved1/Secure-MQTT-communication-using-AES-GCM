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

/* Data/Time Stamp: 06/11/2018 06:21:24 AM 
Saad: 
	- Function API now supports return of Tag to the caller function.
	- Function API now supports use of additional_data to be included in the GMAC chain. 

*/

unsigned char* aes_gcm_encrypt(unsigned char* output, const unsigned char* input, int input_length, const unsigned char* key, const size_t key_len, const unsigned char * iv, const size_t iv_len, const unsigned char *add_data, size_t add_len, unsigned char tag[]){
    
    //int ret = 0;                // our return value
    gcm_context ctx;            // includes the AES context structure
    
    size_t tag_len = 16; // Setting the tag length to 16 bytes
    //unsigned char *tag_buf;
    
    
   //memset(tag_buf,0x00,tag_len );
    
    gcm_setkey( &ctx, key, (const uint)key_len );
    
    gcm_crypt_and_tag( &ctx, ENCRYPT, iv, iv_len, add_data, add_len,
                            input, output, input_length, tag, 16);
    printf("\nTag in aes-gcm = ");
    for(int i = 0; i< 16; i++)
       printf("%x", tag[i]);
  
    gcm_zero_ctx( &ctx );

// returning the tag to main function. Delete this if not working properly at first.
/* read on the internet that malloc was necessary for returning a character pointer */
    
    return(tag);
}

unsigned char* aes_gcm_decrypt(unsigned char* output, const unsigned char* input, int input_length, const unsigned char* key, const size_t key_len, const unsigned char * iv, const size_t iv_len){
    
    int ret = 0;                // our return value
    gcm_context ctx;            // includes the AES context structure
    
    size_t tag_len = 0;
    unsigned char * tag_buf = NULL;
    
    gcm_setkey( &ctx, key, (const uint)key_len );
    
    gcm_crypt_and_tag( &ctx, DECRYPT, iv, iv_len, NULL, 0,
                            input, output, input_length, tag_buf, tag_len);
    
    gcm_zero_ctx( &ctx );
    
    return(tag_buf);

}

