//
//  aes-gcm.c
//  Pods
//
//  Created by Markus Kosmal on 20/11/14.
//
//

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "aes-gcm.h"

/* Saad: For the support of additioal data authentication, which usually used in packet authentication in communication, the arguments of the function "aes_gcm_encrypt()" need to add in fields fori) *add (pointer to additional data), ii) add_length (size_t variable). 

Which are then to be passed on the "gcm_crypt_tag() function in the place of "NULL" and "0" function arguments. 

*/



/* Adding the support for returning the tag to the main window after it is calculated. The tag will be a character pointer
*/

char* aes_gcm_encrypt(unsigned char* output, const unsigned char* input, int input_length, const unsigned char* key, const size_t key_len, const unsigned char * iv, const size_t iv_len){
    
    int ret = 0;                // our return value
    gcm_context ctx;            // includes the AES context structure
    
    size_t tag_len = 0;
    unsigned char * tag_buf = NULL;
    
    gcm_setkey( &ctx, key, (const uint)key_len );
    
    ret = gcm_crypt_and_tag( &ctx, ENCRYPT, iv, iv_len, NULL, 0,
                            input, output, input_length, tag_buf, tag_len);
    
    gcm_zero_ctx( &ctx );

/* read on the internet that malloc was necessary for returning a character pointer */
    char *tag_return_value;
    tag_return_value = (char *)malloc(tag_len);
    strncpy(tag_return_value, tag_buf, tag_len); 
    return( tag_return_value );
}

int aes_gcm_decrypt(unsigned char* output, const unsigned char* input, int input_length, const unsigned char* key, const size_t key_len, const unsigned char * iv, const size_t iv_len){
    
    int ret = 0;                // our return value
    gcm_context ctx;            // includes the AES context structure
    
    size_t tag_len = 0;
    unsigned char * tag_buf = NULL;
    
    gcm_setkey( &ctx, key, (const uint)key_len );
    
    ret = gcm_crypt_and_tag( &ctx, DECRYPT, iv, iv_len, NULL, 0,
                            input, output, input_length, tag_buf, tag_len);
    
    gcm_zero_ctx( &ctx );
    
    return( ret );

}
