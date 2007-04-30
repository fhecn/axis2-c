/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#include <stdio.h>
#include <axis2_util.h>
#include <oxs_buffer.h>
#include <oxs_error.h>
#include <openssl_cipher_ctx.h>
#include <openssl_crypt.h>
#include <openssl/rand.h>

#define BUFSIZE 64

/**
* @param do_encrypt should be set to 1 for encryption, 0 for decryption and -1 to
* leave the value unchanged
*/
AXIS2_EXTERN int AXIS2_CALL  openssl_block_cipher_crypt(const axis2_env_t *env,
        openssl_cipher_ctx_t *oc_ctx,
        unsigned char *in_main_buf,
        int in_main_len,
        unsigned char **out_main_buf,
        int do_encrypt)
{
    EVP_CIPHER_CTX ctx ;

    unsigned char inbuf[BUFSIZE + 1 ], outbuf[BUFSIZE + EVP_MAX_BLOCK_LENGTH]; /*EVP_MAX_BLOCK_LENGTH = 32 in evp.h*/
    unsigned char *tempbuf = NULL;
    unsigned char *tempbuf2 = NULL;

    int inlen, outlen, i,  out_buf_index;
    int ret;

    i = 0;
    out_buf_index = 0;

    /*Init ctx*/
    EVP_CIPHER_CTX_init(&ctx);
    ret = EVP_CipherInit_ex(&ctx, (EVP_CIPHER *)OPENSSL_CIPHER_CTX_GET_CIPHER(oc_ctx, env), NULL, NULL, NULL, do_encrypt);
    ret  = EVP_CipherInit_ex(&ctx, NULL, NULL, (unsigned char*)OPENSSL_CIPHER_CTX_GET_KEY(oc_ctx, env),
            (unsigned char*)OPENSSL_CIPHER_CTX_GET_IV(oc_ctx, env),
            do_encrypt);
    for (;;)
    {
        memset(inbuf, 0 , BUFSIZE);/*Reset memory for the inbuf*/
        memcpy(inbuf, in_main_buf + (i * BUFSIZE) , BUFSIZE);/*Copy the first block to the inbuf*/

        if (in_main_len <= i*BUFSIZE) break; /*Finish!!! */

        /*If we are in the last block, set inlen according to the in_main_len */
        if (in_main_len <= (i + 1)*BUFSIZE)
        {
            inlen = in_main_len - (i * BUFSIZE);
        }
        else
        {
            inlen = BUFSIZE;
        }

        if (do_encrypt == 1)
        {
            printf("\nEncrypting block[%d] %s", inlen, inbuf);
        }

        memset(outbuf, 0 , BUFSIZE + EVP_MAX_BLOCK_LENGTH);/*Reset memory for the outbuf*/
        if (!EVP_CipherUpdate(&ctx, outbuf, &outlen, inbuf, inlen))
        {
            /* Error */
            oxs_error(ERROR_LOCATION, OXS_ERROR_OPENSSL_FUNC_FAILED,
                    "Encryption failed");

            EVP_CIPHER_CTX_cleanup(&ctx);
            return (-1);
        }
        /*TODO: Write the encrypted block to the tempbuf*/
        tempbuf2 = malloc(out_buf_index + outlen);
        if (i > 0)
        {/*Skip for the i=0 step*/
            memcpy(tempbuf2, tempbuf, out_buf_index);
            /*free tempbuf*/
            free(tempbuf);
        }
        memcpy(tempbuf2 + out_buf_index, outbuf, outlen);
        tempbuf = tempbuf2; /*Assign new tempbuf2 to the old one*/
        out_buf_index = out_buf_index + outlen;/*Update the writing position of the tempbuf*/

        i++;
    }/*End of for loop*/

    ret = EVP_CipherFinal_ex(&ctx, outbuf, &outlen);
    if (!ret)
    {
        /* Error */
        EVP_CIPHER_CTX_cleanup(&ctx);
        printf("\nERROR:EVP_CipherFinal_ex--- EVP_CIPHER_CTX_cleanup");
        return (-1);
    }
    /*Alright now we need to write the last drop*/
    tempbuf2 = malloc(out_buf_index + outlen);
    memcpy(tempbuf2, tempbuf, out_buf_index);
    /*free tempbuf*/
    free(tempbuf);
    memcpy(tempbuf2 + out_buf_index, outbuf, outlen);
    tempbuf = tempbuf2; /*Assign new tempbuf2 to the old one*/
    out_buf_index = out_buf_index + outlen;/*Update the writing position of the tempbuf*/
    EVP_CIPHER_CTX_cleanup(&ctx);
    /*Assign the temp buf to the out_main_buf*/
    *out_main_buf = tempbuf;
    free(tempbuf2);
    return out_buf_index;

}
