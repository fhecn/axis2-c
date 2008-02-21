
/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef GUTHTHILA_H
#define GUTHTHILA_H

#include <guththila_defines.h>
#include <guththila_token.h>
#include <guththila_reader.h>
#include <guththila_xml_writer.h>
#include <guththila_attribute.h>
#include <guththila_namespace.h>
#include <guththila_buffer.h>
#include <guththila_stack.h>
#include <guththila_error.h>

#include <axutil_utils.h>

/*
All the functions in this library does not check weather the given arguments are NULL.
It is the responsblity of the user to check weather the arguments contain NULL values.
*/

{
    S_0 = 0, 
};

{
    None = 1, LE, BE };

{
    type_file_name =
        0, 
} guththila_type_t;

{
    GUTHTHILA_START_DOCUMENT =
        0, 
    
    
    
};

{

    guththila_tok_list_t
    tokens;

    guththila_buffer_t
    buffer;
    
    guththila_reader_t *
    reader;

    guththila_token_t *
    prefix;

    guththila_token_t *
    name;

    guththila_token_t *
    value;
    
    guththila_stack_t
    elem;

    guththila_stack_t
    attrib;

    guththila_stack_t
    namesp;
    
    is_whitespace;
    
    is_char;
    
    unicode_state;
    
    status;
    
    guththila_event;
    
    next;
    
    last_start;

    guththila_token_t *
    temp_prefix;

    guththila_token_t *
    temp_name;

    guththila_token_t *
    temp_tok;
    
}
guththila_t;

{

    guththila_namespace_t *
    namesp;
    
    no;
    
    size;
    
}
guththila_elem_namesp_t;

{

    guththila_token_t *
    name;

    guththila_token_t *
    prefix;
    
    is_namesp;
    
}
guththila_element_t;

guththila_init(
    guththila_t * m,
    void *reader,
    const axutil_env_t * env);

        const
        axutil_env_t *
        env);

guththila_free(
    guththila_t * m,
    const axutil_env_t * env);

guththila_un_init(
    guththila_t * m,
    const axutil_env_t * env);

    GUTHTHILA_CALL * guththila_error_func)(
        void *arg,
        
        
        


/*
Public functions for reading XML documents
*/
GUTHTHILA_EXPORT int
GUTHTHILA_CALL
guththila_next(
    guththila_t * p,
    const axutil_env_t * env);

GUTHTHILA_CALL
guththila_get_attribute_count(
    guththila_t * p,
    const axutil_env_t * env);

guththila_get_attribute_name(guththila_t * p, guththila_attr_t * att,
        const axutil_env_t * env);

GUTHTHILA_CALL 
        guththila_attr_t * att,
        const axutil_env_t * env);

GUTHTHILA_CALL 
        guththila_attr_t * att,
        const axutil_env_t * env);

GUTHTHILA_CALL 
        const axutil_env_t * env);

GUTHTHILA_CALL 
        int i,
        const axutil_env_t *
        env);

GUTHTHILA_CALL 
        int i,
        const axutil_env_t
        * env);

GUTHTHILA_CALL 
        int i,
        const axutil_env_t
        * env);

GUTHTHILA_CALL 
        const axutil_env_t * env);

GUTHTHILA_CALL 
        const axutil_env_t * env);

GUTHTHILA_CALL 
        const axutil_env_t * env);

GUTHTHILA_CALL 
        const axutil_env_t * env);

GUTHTHILA_CALL
guththila_get_namespace_count(
    guththila_t * p,
    const axutil_env_t * env);

guththila_get_namespace_uri(guththila_t * p, guththila_namespace_t * ns,
        const axutil_env_t * env);

GUTHTHILA_CALL 
        guththila_namespace_t * ns,
        const axutil_env_t * env);

GUTHTHILA_CALL 
        int i,
        const axutil_env_t
        * env);

GUTHTHILA_CALL 
        int i,
        const axutil_env_t *
        env);

GUTHTHILA_CALL 
        p, int i,
        const
        axutil_env_t *
        env);

GUTHTHILA_CALL 
        const axutil_env_t * env);

GUTHTHILA_CALL
guththila_set_error_handler(
    guththila_t * m,
    guththila_error_func,
    const axutil_env_t * env);

#endif  /* 