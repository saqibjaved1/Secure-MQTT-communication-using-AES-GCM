

#include "aes-gcm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Data/Time Stamp: 06/11/2018 06:21:24 AM 
Saad: 
	- Function API now supports return of Tag to the caller function.
	- Function API now supports use of additional_data to be included in the GMAC chain. 

*/

void aes_gcm_encrypt(unsigned char* output, const unsigned char* input, int input_length, const unsigned char* key, const size_t key_len, const unsigned char * iv, const size_t iv_len, const unsigned char *add_data, size_t add_len, unsigned char tag[]){
    
    
    gcm_context ctx;            // includes the AES context structure
   
    
    gcm_setkey( &ctx, key, (const uint)key_len );
    
    gcm_crypt_and_tag( &ctx, ENCRYPT, iv, iv_len, add_data, add_len,
                            input, output, input_length, tag, 16);
  
    gcm_zero_ctx( &ctx );

    
    
}

