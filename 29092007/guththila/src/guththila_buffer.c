
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <guththila_buffer.h>
    
guththila_buffer_init(
    guththila_buffer_t * buffer,
    int size,
    const axutil_env_t * env) 
{
    
    
        (size_t *) AXIS2_MALLOC(env->allocator,
                                sizeof(size_t) *
                                GUTHTHILA_BUFFER_NUMBER_OF_BUFFERS);
    
        (size_t *) AXIS2_MALLOC(env->allocator,
                                sizeof(size_t) *
                                GUTHTHILA_BUFFER_NUMBER_OF_BUFFERS);
    
        (char **) AXIS2_MALLOC(env->allocator,
                               sizeof(char *) *
                               GUTHTHILA_BUFFER_NUMBER_OF_BUFFERS);
    
    
    
    
    {
        
            (guththila_char *) AXIS2_MALLOC(env->allocator,
                                            sizeof(guththila_char) * size);
        
        
        
    
    


guththila_buffer_un_init(
    guththila_buffer_t * buffer,
    const axutil_env_t * env) 
{
    
    
         buffer->cur_buff == 0)
    {
        
            /*This is commented. because the ownership of the buffer is with the user.  */ 
            
            /*if (buffer->buff[0]) AXIS2_FREE(env->allocator, buffer->buff[0]); */ 
            if (buffer->buffs_size)
            AXIS2_FREE(env->allocator, buffer->buffs_size);
        
            AXIS2_FREE(env->allocator, buffer->data_size);
        
    
    else if (buffer->type == GUTHTHILA_MULTIPLE_BUFFER && buffer->buff)
    {
        
        {
            
        
        
        
            AXIS2_FREE(env->allocator, buffer->data_size);
        
            AXIS2_FREE(env->allocator, buffer->buffs_size);
    
    


guththila_buffer_init_for_buffer(
    guththila_buffer_t * buffer,
    char *buff,
    int size,
    const axutil_env_t * env) 
{
    
    
        (char **) AXIS2_MALLOC(env->allocator,
                               sizeof(char *) * GUTHTHILA_BUFFER_DEF_SIZE);
    
    
    
        (size_t *) AXIS2_MALLOC(env->allocator,
                                sizeof(size_t) * GUTHTHILA_BUFFER_DEF_SIZE);
    
    
    
        (size_t *) AXIS2_MALLOC(env->allocator,
                                sizeof(size_t) * GUTHTHILA_BUFFER_DEF_SIZE);
    
    
    


guththila_buffer_get(
    guththila_buffer_t * buffer,
    const axutil_env_t * env) 
{
    
    
    
    
    {
        
    
    
    
    {
        
        
    
    
    


