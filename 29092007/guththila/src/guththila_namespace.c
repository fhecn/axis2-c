
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
#include <guththila_namespace.h>
#include <guththila_stack.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
    
guththila_namespace_list_grow(
    guththila_namespace_list_t * namesp_list,
    int addition,
    const axutil_env_t * env) 
{
    
    
         (addition < 0 && namesp_list->capacity + addition > 0 &&
          namesp_list->capacity + addition >= namesp_list->size))
    {
        
            (guththila_namespace_t *) realloc(namesp_list->list,
                                              sizeof(guththila_namespace_t) *
                                              (namesp_list->capacity +
                                               addition));
        
        {
            
                  i < namesp_list->capacity + addition; i++)
            {
                
                                      namesp_list->list + i, env);
            
            
        
        else
        {
            
        
    
    



    GUTHTHILA_CALL guththila_namespace_list_create(const axutil_env_t * env) 
{
    
    
        (guththila_namespace_list_t *) AXIS2_MALLOC(env->allocator,
                                                    sizeof
                                                    (guththila_namespace_list_t));
    
        return NULL;
    
        (guththila_namespace_t *) AXIS2_MALLOC(env->allocator,
                                               sizeof(guththila_namespace_t) *
                                               GUTHTHILA_NAMESPACE_DEF_SIZE);
    
          guththila_stack_init(&namesp_list->fr_stack, env))
    {
        
        
        
        {
            
                                  env);
        
        
    
    


guththila_namespace_list_init(
    guththila_namespace_list_t * namesp_list,
    const axutil_env_t * env) 
{
    
    
        (guththila_namespace_t *) AXIS2_MALLOC(env->allocator,
                                               sizeof(guththila_namespace_t) *
                                               GUTHTHILA_NAMESPACE_DEF_SIZE);
    
          guththila_stack_init(&namesp_list->fr_stack, env))
    {
        
        
        
        {
            
                                  env);
        
        
    
    



    GUTHTHILA_CALL guththila_namespace_list_get(guththila_namespace_list_t *
                                                namesp_list,
                                                const axutil_env_t * env) 
{
    
         guththila_namespace_list_grow(namesp_list,
                                       GUTHTHILA_NAMESPACE_DEF_SIZE, env))
    {
        
    
    


guththila_namespace_list_release(
    guththila_namespace_list_t * namesp_list,
    guththila_namespace_t * namespace,
    const axutil_env_t * env) 
{
    


msuila_namespace_list_free_data(
    guththila_namespace_list_t * namesp_list,
    const axutil_env_t * env) 
{
    
    


guththila_namespace_list_free(
    guththila_namespace_list_t * namesp_list,
    const axutil_env_t * env) 
{
    
    
    
