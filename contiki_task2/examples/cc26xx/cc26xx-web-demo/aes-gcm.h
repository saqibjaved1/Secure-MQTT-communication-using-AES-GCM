

#ifndef mko_aes_gcm_h
#define mko_aes_gcm_h

#include <stdint.h>
#include "gcm.h"  

// support for tag return to the caller function added.
// support for ADD_DATA and ADD_LEN is added. 

void aes_gcm_encrypt(unsigned char* output, const unsigned char* input, int input_length, const unsigned char* key, const size_t key_len, const unsigned char * iv, const size_t iv_len, const unsigned char *add_data, size_t add_len, unsigned char* tag);


#endif

