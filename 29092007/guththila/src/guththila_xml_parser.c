
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
#include <ctype.h>
    
#include <guththila.h>
    
#define GUTHTHILA_VALIDATION_PARSER

    guththila_t * m,
    int eof,
    const axutil_env_t * env);

    guththila_t * m,
    int eof,
    char *bytes,
    int no,
    const axutil_env_t * env);

    guththila_t * m,
    guththila_token_t * tok,
    int tok_type,
    int referer,
    const axutil_env_t * env);

    guththila_t * m,
    const axutil_env_t * env);

#ifndef GUTHTHILA_SKIP_SPACES
#define GUTHTHILA_SKIP_SPACES(m, c, _env) while (0x20 == c || 0x9 == c || 0xD == c || 0xA == c){c = guththila_next_char(m, 0, _env);}
#endif  /* 
    
#ifndef GUTHTHILA_SKIP_SPACES_WITH_NEW_LINE
#define GUTHTHILA_SKIP_SPACES_WITH_NEW_LINE(m, c, _env) while (0x20 == c || 0x9 == c || 0xD == c || 0xA == c || '\n' == c){c = guththila_next_char(m, 0, _env);}
#endif  /* 
    
#ifndef GUTHTHILA_LAST_CHAR
#define GUTHTHILA_LAST_CHAR(m) (m->buffer.buff + m->buffer.next - 1)
#endif  /* 
    
#ifndef GUTHTHILA_TOKEN_OPEN
#define GUTHTHILA_TOKEN_OPEN(m, tok, _env)					\
    m->temp_tok = guththila_tok_list_get_token(&m->tokens, _env);
\
\
\

#endif  /* 
    
#ifndef GUTHTHILA_PROCESS_EQU
#define GUTHTHILA_PROCESS_EQU(m, c, ic, _env)							\
    GUTHTHILA_SKIP_SPACES(m, c, _env);
\
{
    \
    \
\

#endif  /* 
    
#ifndef GUTHTHILA_ATTRIBUTE_INITIALIZE
#define GUTHTHILA_ATTRIBUTE_INITIALIZE(_attr, _pref, _name, _val)	\
    (_attr->pref = (_pref));
\
\

#endif  /* 
    
#ifndef GUTHTHILA_NAMESPACE_INITIALIZE
#define GUTHTHILA_NAMESPACE_INITIALIZE(_namesp, _name, _uri)	\
    (_namesp->name = _name);
\

#endif  /* 
    
#ifndef GUTHTHILA_IS_SPACE
#define GUTHTHILA_IS_SPACE(c) (0x20 == c || 0xD == c || 0xA == c || 0x9 == c)     
#endif  /* 
    
#ifndef GUTHTHILA_IS_VALID_STRING_CHAR
#define GUTHTHILA_IS_VALID_STRING_CHAR(c) (isalpha(c) || '_' == c || ':' == c)
#endif  /* 
    
#ifndef GUTHTHILA_IS_VALID_STARTING_CHAR
#define GUTHTHILA_IS_VALID_STARTING_CHAR(c) (isalpha(c) || '_' == c || ':' == c)
#endif  /* 
    
guththila_token_close(
    guththila_t * m,
    guththila_token_t * tok,
    int tok_type,
    int referer,
    const axutil_env_t * env) 
{
    
    
    
    
    
        nmsp_no = 0,
        i = 0;
    
    
    
        GUTHTHILA_BUF_POS(m->buffer, m->next - 1) - m->temp_tok->size;
    
    
    
    {
    
        
        
        
    
        
        
        
    
        
             (m->temp_prefix->start)[0] == 'x' &&
             
             (m->temp_prefix->start)[2] == 'l' &&
             
             (m->temp_prefix->start)[4] == 's')
        {
            
#ifndef GUTHTHILA_VALIDATION_PARSER
                namesp =
                (guththila_namespace_t *)
                AXIS2_MALLOC(sizeof(guththila_namespace_t));
            
            
            
#else   /* 
                elem =
                (guththila_element_t *) guththila_stack_peek(&m->elem, env);
            
            {
                
                    (guththila_elem_namesp_t *) AXIS2_MALLOC(env->allocator,
                                                             sizeof
                                                             (guththila_elem_namesp_t));
                
                {
                    
                        (guththila_namespace_t *) AXIS2_MALLOC(env->allocator,
                                                               sizeof
                                                               (guththila_namespace_t)
                                                               *
                                                               GUTHTHILA_NAMESPACE_DEF_SIZE);
                    
                    {
                        
                        
                        
                        
                        
                        
                    
                
            
            else
            {
                
                    (guththila_elem_namesp_t *) guththila_stack_peek(&m->namesp,
                                                                     env);
                
                {
                    
                    
                    
                
                else
                {
                    
                        /*e_namesp->namesp = (guththila_namespace_t *)realloc(e_namesp->namesp , sizeof(guththila_namespace_t) * e_namesp->size * 2); */ 
                        namesp =
                        (guththila_namespace_t *) AXIS2_MALLOC(env->allocator,
                                                               sizeof
                                                               (guththila_namespace_t)
                                                               *
                                                               e_namesp->size *
                                                               2);
                    
                    {
                        
                        
                    
                    
                    
                    
                    {
                        
                        
                        
                        
                    
                
            
            
#endif  /* 
        }
        else
        {
            
                (guththila_attr_t *) AXIS2_MALLOC(env->allocator,
                                                  sizeof(guththila_attr_t));
            
#ifdef GUTHTHILA_VALIDATION_PARSER
                if (m->temp_prefix)
            {
                
                
                {
                    
                        (guththila_elem_namesp_t *)
                        guththila_stack_get_by_index(&m->namesp, counter, env);
                    
                    {
                        
                             (e_namesp->namesp[i].name, m->temp_prefix, env))
                        {
                            
                                                            m->temp_prefix,
                                                            m->temp_name,
                                                            m->temp_tok);
                            
                            
                            
                        
                    
                
            
            else
            {
                
                                                m->temp_name, m->temp_tok);
                
            
            
#else   /* 
                GUTHTHILA_ATTRIBUTE_INITIALIZE(attr, m->temp_prefix,
                                               m->temp_name, m->temp_tok);
            
            
#endif  /* 
        }
        
        
        
        
    
        
        
        
    
        
        
        
        
        
    



#ifndef GUTHTHILA_VARIABLE_INITIALZE
#define GUTHTHILA_VARIABLE_INITIALZE(m) \
    m->temp_prefix = NULL;
\
\
\
    guththila_tok_list_release_token(&m->tokens, m->value, env);
\
\
\

#endif  /* 
    
guththila_init(
    guththila_t * m,
    void *reader,
    const axutil_env_t * env) 
{
    
        return GUTHTHILA_FAILURE;
    
    
    {
        
    
    
    {
        
                                          m->reader->buff_size, env);
    
    else if (m->reader->type == GUTHTHILA_FILE_READER || GUTHTHILA_IO_READER)
    {
        
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    



                                                                 const
                                                                 axutil_env_t *
                                                                 env) 
{
    
        (guththila_t *) AXIS2_MALLOC(env->allocator, sizeof(guththila_t *));
    
        return NULL;
    
    
    {
        
        
    
    
    {
        
                                          m->reader->buff_size, env);
    
    else if (m->reader->type == GUTHTHILA_FILE_READER || GUTHTHILA_IO_READER)
    {
        
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    


guththila_free(
    guththila_t * m,
    const axutil_env_t * env) 
{
    
        i = 0;
    
    
    
    {
        
    
    
    {
        
    
    
    {
        
    
    
    {
        
    
    
    {
        
    
    
    {
        
    
    
    
    {
        
        
        {
            
                guththila_tok_list_release_token(&m->tokens, attr->name, env);
            
                guththila_tok_list_release_token(&m->tokens, attr->pref, env);
            
        
    
    
    
    
    {
        
            (guththila_namespace_t *) guththila_stack_pop(&m->namesp, env);
        
        {
            
                guththila_tok_list_release_token(&m->tokens, namesp->name, env);
            
                guththila_tok_list_release_token(&m->tokens, namesp->uri, env);
            
        
    
    
    
    
    
    


guththila_un_init(
    guththila_t * m,
    const axutil_env_t * env) 
{
    
        i = 0;
    
    
    
    {
        
    
    
    {
        
    
    
    {
        
    
    
    {
        
    
    
    {
        
    
    
    {
        
    
    
    
    {
        
        
        {
            
                guththila_tok_list_release_token(&m->tokens, attr->name, env);
            
                guththila_tok_list_release_token(&m->tokens, attr->pref, env);
            
        
    
    
    
    
    {
        
            (guththila_namespace_t *) guththila_stack_pop(&m->namesp, env);
        
        {
            
                guththila_tok_list_release_token(&m->tokens, namesp->name, env);
            
                guththila_tok_list_release_token(&m->tokens, namesp->uri, env);
            
        
    
    
    
    
    


guththila_next(
    guththila_t * m,
    const axutil_env_t * env) 
{
    
    
    
    
        ref = 0;
    
    
    
    
        i = 0,
        nmsp_counter,
        loop = 0,
        white_space = 0;
    
    
    {
        
        
        {
            
                guththila_tok_list_release_token(&m->tokens, attr->name, env);
            
                guththila_tok_list_release_token(&m->tokens, attr->pref, env);
            
        
    
    
    
#ifdef GUTHTHILA_VALIDATION_PARSER
        if (m->guththila_event == GUTHTHILA_EMPTY_ELEMENT)
    {
        
        
        {
            
                (guththila_elem_namesp_t *) guththila_stack_pop(&m->namesp,
                                                                env);
            
            {
                
                    guththila_tok_list_release_token(&m->tokens,
                                                     nmsp->namesp[nmsp_counter].
                                                     name, env);
                
                    guththila_tok_list_release_token(&m->tokens,
                                                     nmsp->namesp[nmsp_counter].
                                                     uri, env);
            
            
        
        
            guththila_tok_list_release_token(&m->tokens, elem->name, env);
        
            guththila_tok_list_release_token(&m->tokens, elem->prefix, env);
        
    
    
#endif  /* 
        do
    {
        
        
        
        {
            
            {
                
                
                    
            
            
            {
                
            
            else
            {
                
            
        
        
        {
            
            
            {
                
                {
                    
                    
                    
                    {
                        
                        {
                            
                        
                        else
                        {
                            
                            
                            
                        
                    
                    
                    
#ifdef GUTHTHILA_VALIDATION_PARSER		
                        elem =
                        (guththila_element_t *) AXIS2_MALLOC(env->allocator,
                                                             sizeof
                                                             (guththila_element_t));
                    
                    
                    
                    
                    
#endif  /* 
                }
                
                
                {
                    
                    {
                        
                        {
                            
                                GUTHTHILA_EMPTY_ELEMENT;
                        
                        else
                        {
                            
                        
                    
                    else if (c == '>')
                    {
                        
                        
                    
                    else if (c != -1)
                    {
                        
                        {
                            
                            
                            
                            {
                                
                                {
                                    
                                
                                else if (c == ':')
                                {
                                    
                                                           env);
                                    
                                    
                                
                            
                            
                                                   env);
                        
                        else
                        {
                            
                        
                        
                        
                        {
                            
                            
                            
                            {
                                
                            
                            
                                                   env);
                            
                            
                        
                        else
                        {
                            
                        
                    
                    else
                    {
                        
                    
                
            
            else if (c == '/')
            {
                
                
                
                {
                    
                    
                    
                    {
                        
                        {
                            
                        
                        else
                        {
                            
                            
                            
                        
                    
                    
                    
#ifdef GUTHTHILA_VALIDATION_PARSER	
                        elem =
                        (guththila_element_t *) guththila_stack_pop(&m->elem,
                                                                    env);
                    
                         (elem->prefix && !m->prefix))
                        return -1;
                    
                    {
                        
                    
                    
                         guththila_tok_tok_cmp(m->prefix, elem->prefix, env))
                    {
                        
                    
                    
                    {
                        
                            (guththila_elem_namesp_t *) guththila_stack_pop(&m->
                                                                            namesp,
                                                                            env);
                        
                              nmsp_counter++)
                        {
                            
                                guththila_tok_list_release_token(&m->tokens,
                                                                 nmsp->
                                                                 namesp
                                                                 [nmsp_counter].
                                                                 name, env);
                            
                                guththila_tok_list_release_token(&m->tokens,
                                                                 nmsp->
                                                                 namesp
                                                                 [nmsp_counter].
                                                                 uri, env);
                        
                        
                    
                    
                        guththila_tok_list_release_token(&m->tokens, elem->name,
                                                         env);
                    
                        guththila_tok_list_release_token(&m->tokens,
                                                         elem->prefix, env);
                    
                    
#endif  /* 
                        GUTHTHILA_SKIP_SPACES(m, c, env);
                    
                        
                    
                
                
            
            else if (c == '!')
            {
                
                     '-' == c_arra[0] && '-' == c_arra[1])
                {
                    
                    
                    
                    {
                        
                        
                        {
                            
                            
                            {
                                
                                {
                                    
                                    
                                    {
                                        
                                        
                                            
                                    
                                    
                                                           0, env);
                                    
                                    
                                
                                
                                else
                                {
                                    
                                
                            
                        
                    
                
                else
                {
                    
                    
                        
                
            
            else if (c == '?')
            {
                
                
                    
                
                else
                    
            
        
        else if (c != '<' && m->status == S_2 && c != -1)
        {
            
            
                
            
            else
                
            
            
            do
            {
                
                
                    
                
                    return -1;
            
            while (c != '<');
            
            
            
            {
                
                
                {
                    
                                                      env);
                    
                
            
            
            else
                return GUTHTHILA_CHARACTER;
        
        else
        {
            
        
    
    while (loop);
    


guththila_process_xml_dec(
    guththila_t * m,
    const axutil_env_t * env) 
{
    
    
    
    
    
    
          'x' == c_arra[0] && 'm' == c_arra[1] && 'l' == c_arra[2])
    {
        
        
        
        {
            
            
                 
                 'i' == c_arra[3] && 
            {
                
                
                
                
                
                
                    
                
                
                
            
            else
            {
                
            
        
        
        {
            
            
                 
                 'd' == c_arra[3] && 
                 
            {
                
                
                
                
                
                
                    
                
                
                
            
        
        
        {
            
            
                 
                 'd' == c_arra[3] && 
                 
            {
                
                
                
                
                
                
                    
                
                
                
            
        
        
        {
            
            {
                
            
            else
            {
                
            
        
    
    


guththila_get_attribute_count(
    guththila_t * m,
    const axutil_env_t * env) 
{
    



    GUTHTHILA_CALL guththila_get_attribute_name(guththila_t * m,
                                                guththila_attr_t * att,
                                                const axutil_env_t * env) 
{
    
    
    {
        
        
    
    



    GUTHTHILA_CALL guththila_get_attribute_value(guththila_t * m,
                                                 guththila_attr_t * att,
                                                 const axutil_env_t * env) 
{
    
    
    {
        
        
    
    



    GUTHTHILA_CALL guththila_get_attribute_prefix(guththila_t * m,
                                                  guththila_attr_t * att,
                                                  const axutil_env_t * env) 
{
    
    
    {
        
        
    
    



    GUTHTHILA_CALL guththila_get_attribute(guththila_t * m,
                                           const axutil_env_t * env) 
{
    



    GUTHTHILA_CALL guththila_get_attribute_name_by_number(guththila_t * m,
                                                          int i,
                                                          const axutil_env_t *
                                                          env) 
{
    
    
        (guththila_attr_t *) guththila_stack_get_by_index(&m->attrib, i - 1,
                                                          env);
    
    {
        
        
    
    



    GUTHTHILA_CALL guththila_get_attribute_value_by_number(guththila_t * m,
                                                           int i,
                                                           const axutil_env_t *
                                                           env) 
{
    
    
        (guththila_attr_t *) guththila_stack_get_by_index(&m->attrib, i - 1,
                                                          env);
    
    {
        
        
    
    



    GUTHTHILA_CALL guththila_get_attribute_prefix_by_number(guththila_t * m,
                                                            int i,
                                                            const axutil_env_t *
                                                            env) 
{
    
    
        (guththila_attr_t *) guththila_stack_get_by_index(&m->attrib, i - 1,
                                                          env);
    
    {
        
        
    
    



    GUTHTHILA_CALL guththila_get_name(guththila_t * m,
                                      const axutil_env_t * env) 
{
    
    
    {
        
        
    
    



    GUTHTHILA_CALL guththila_get_prefix(guththila_t * m,
                                        const axutil_env_t * env) 
{
    
    
    {
        
        
    
    



    GUTHTHILA_CALL guththila_get_value(guththila_t * m,
                                       const axutil_env_t * env) 
{
    
    
    {
        
        
    
    



    GUTHTHILA_CALL guththila_get_namespace(guththila_t * m,
                                           const axutil_env_t * env) 
{
    
#ifndef GUTHTHILA_VALIDATION_PARSER
        return (guththila_namespace_t *) guththila_stack_pop(&m->namesp, env);
    
#else   /* 
        return NULL;
    
#endif  /* 
}

guththila_get_namespace_count(
    guththila_t * m,
    const axutil_env_t * env) 
{
    
#ifndef GUTHTHILA_VALIDATION_PARSER
        return GUTHTHILA_STACK_SIZE(m->namesp);
    
#else   /* 
        guththila_elem_namesp_t * nmsp = NULL;
    
         is_namesp)
    {
        
            (guththila_elem_namesp_t *) guththila_stack_peek(&m->namesp, env);
        
    
    
    
#endif  /* 
}


    GUTHTHILA_CALL guththila_get_namespace_uri(guththila_t * m,
                                               guththila_namespace_t * ns,
                                               const axutil_env_t * env) 
{
    
    
    {
        
        
    
    



    GUTHTHILA_CALL guththila_get_namespace_prefix(guththila_t * m,
                                                  guththila_namespace_t * ns,
                                                  const axutil_env_t * env) 
{
    
    
    {
        
        
    
    



    GUTHTHILA_CALL guththila_get_namespace_prefix_by_number(guththila_t * m,
                                                            int i,
                                                            const axutil_env_t *
                                                            env) 
{
    
    
#ifndef GUTHTHILA_VALIDATION_PARSER
        if (GUTHTHILA_STACK_SIZE(m->namesp) >= i)
    {
        
        
        {
            
            
        
    
    
#else   /* 
        guththila_elem_namesp_t * nmsp = NULL;
    
         is_namesp)
    {
        
            (guththila_elem_namesp_t *) guththila_stack_peek(&m->namesp, env);
        
        {
            
            
        
    
    
#endif  /* 
        return NULL;



    GUTHTHILA_CALL guththila_get_namespace_uri_by_number(guththila_t * m, int i,
                                                         const axutil_env_t *
                                                         env) 
{
    
    
        /*TODO check the given index, this can begn from 1, here I assume begin from 0 */ 
#ifndef GUTHTHILA_VALIDATION_PARSER
        if (GUTHTHILA_STACK_SIZE(m->namesp) > i)
    {
        
        
        {
            
            
        
    
    
#else   /* 
        guththila_elem_namesp_t * nmsp = NULL;
    
         is_namesp)
    {
        
            (guththila_elem_namesp_t *) guththila_stack_peek(&m->namesp, env);
        
        {
            
            
        
    
    
#endif  /* 
        return NULL;



    GUTHTHILA_CALL guththila_get_attribute_namespace_by_number(guththila_t * m,
                                                               int i,
                                                               const
                                                               axutil_env_t *
                                                               env) 
{
    
#ifndef GUTHTHILA_VALIDATION_PARSER
        return NULL;
    
#else   /* 
        guththila_attr_t * attr = NULL;
    
    
        k = 0,
        count = 0;
    
    
    {
        
            (guththila_attr_t *) guththila_stack_get_by_index(&m->attrib, i - 1,
                                                              env);
        
        {
            
            
            {
                
                    (guththila_elem_namesp_t *)
                    guththila_stack_get_by_index(&m->namesp, j, env);
                
                {
                    
                         (nmsp->namesp[k].name, attr->pref, env))
                    {
                        
                                                   env);
                        
                    
                
            
        
    
    
    
#endif  /* 
}


    GUTHTHILA_CALL guththila_get_encoding(guththila_t * m,
                                          const axutil_env_t * env) 
{
    


guththila_next_char(
    guththila_t * m,
    int eof,
    const axutil_env_t * env) 
{
    
    
    
    
    
         m->next < GUTHTHILA_BUFFER_CURRENT_DATA_SIZE(m->buffer))
    {
        
        
    
    else if (m->reader->type == GUTHTHILA_IO_READER ||
             m->reader->type == GUTHTHILA_FILE_READER)
    {
        
             GUTHTHILA_BUFFER_PRE_DATA_SIZE(m->buffer) +
             GUTHTHILA_BUFFER_CURRENT_DATA_SIZE(m->buffer) &&
             m->buffer.cur_buff != -1)
        {
            
                                                    GUTHTHILA_BUFFER_PRE_DATA_SIZE
                                                    (m->buffer)];
            
        
        else if (m->next >=
                 GUTHTHILA_BUFFER_PRE_DATA_SIZE(m->buffer) +
                 GUTHTHILA_BUFFER_CURRENT_DATA_SIZE(m->buffer) &&
                 m->buffer.cur_buff != -1)
        {
            
            {
                
                
                    (char **) AXIS2_MALLOC(env->allocator,
                                           sizeof(char *) * temp);
                
                    (size_t *) AXIS2_MALLOC(env->allocator,
                                            sizeof(size_t) * temp);
                
                    (size_t *) AXIS2_MALLOC(env->allocator,
                                            sizeof(size_t) * temp);
                
                {
                    
                    
                    
                
                
                
                
                
                
                
                
            
            
            
                (char *) AXIS2_MALLOC(env->allocator,
                                      sizeof(char) *
                                      m->buffer.buffs_size[m->buffer.cur_buff -
                                                           1] * 2);
            
                m->buffer.buffs_size[m->buffer.cur_buff - 1] * 2;
            
            
            {
                
                    m->buffer.data_size[m->buffer.cur_buff - 1] -
                    (m->last_start - m->buffer.pre_tot_data);
                
                        
                        m->buffer.data_size[m->buffer.cur_buff - 1] - data_move,
                        
                
                
            
            
                m->buffer.data_size[m->buffer.cur_buff - 1];
            
                guththila_reader_read(m->reader,
                                      GUTHTHILA_BUFFER_CURRENT_BUFF(m->buffer),
                                      0,
                                      GUTHTHILA_BUFFER_CURRENT_BUFF_SIZE(m->
                                                                         buffer),
                                      env);
            
            {
                
            
            else
            {
                
            
            
                                                    GUTHTHILA_BUFFER_PRE_DATA_SIZE
                                                    (m->buffer)];
            
        
        else if (m->buffer.cur_buff == -1)
        {
            
                (char *) AXIS2_MALLOC(env->allocator,
                                      sizeof(char) * GUTHTHILA_BUFFER_DEF_SIZE);
            
            
            
                guththila_reader_read(m->reader, m->buffer.buff[0], 0,
                                      GUTHTHILA_BUFFER_DEF_SIZE, env);
            
            
            
        
    
    


guththila_next_no_char(
    guththila_t * m,
    int eof,
    char *bytes,
    int no,
    const axutil_env_t * env) 
{
    
        temp = 0,
        data_move = 0,
        i = 0;
    
    
    
         m->next + no - 1 < GUTHTHILA_BUFFER_CURRENT_DATA_SIZE(m->buffer) &&
         m->buffer.cur_buff != -1)
    {
        
        {
            
        
        
    
    else if (m->reader->type == GUTHTHILA_IO_READER ||
             m->reader->type == GUTHTHILA_FILE_READER)
    {
        
             GUTHTHILA_BUFFER_PRE_DATA_SIZE(m->buffer) +
             GUTHTHILA_BUFFER_CURRENT_DATA_SIZE(m->buffer) + no &&
             m->buffer.cur_buff != -1)
        {
            
            {
                
                    m->buffer.buff[m->buffer.cur_buff][m->next++ -
                                                       GUTHTHILA_BUFFER_PRE_DATA_SIZE
                                                       (m->buffer)];
            
            
        
        else if (m->next >=
                 GUTHTHILA_BUFFER_PRE_DATA_SIZE(m->buffer) +
                 GUTHTHILA_BUFFER_CURRENT_DATA_SIZE(m->buffer) + no &&
                 m->buffer.cur_buff != -1)
        {
            
            {
                
                
                    (char **) AXIS2_MALLOC(env->allocator,
                                           sizeof(char *) * temp);
                
                    (size_t *) AXIS2_MALLOC(env->allocator,
                                            sizeof(size_t) * temp);
                
                    (size_t *) AXIS2_MALLOC(env->allocator,
                                            sizeof(size_t) * temp);
                
                {
                    
                    
                    
                
                
                
                
                
                
                
                
            
            
                (char *) AXIS2_MALLOC(env->allocator,
                                      sizeof(char) *
                                      m->buffer.data_size[m->buffer.cur_buff] *
                                      2);
            
            
                m->buffer.buffs_size[m->buffer.cur_buff - 1] * 2;
            
            
            {
                
                    m->buffer.data_size[m->buffer.cur_buff - 1] -
                    (m->last_start - m->buffer.pre_tot_data);
                
                        
                        m->buffer.data_size[m->buffer.cur_buff - 1] - data_move,
                        
                
                
            
            
                m->buffer.data_size[m->buffer.cur_buff - 1];
            
                guththila_reader_read(m->reader,
                                      GUTHTHILA_BUFFER_CURRENT_BUFF(m->buffer),
                                      0,
                                      GUTHTHILA_BUFFER_CURRENT_BUFF_SIZE(m->
                                                                         buffer),
                                      env);
            
            {
                
            
            else
            {
                
            
            
            {
                
                    m->buffer.buff[m->buffer.cur_buff][m->next++ -
                                                       GUTHTHILA_BUFFER_PRE_DATA_SIZE
                                                       (m->buffer)];
            
            
        
        else if (m->buffer.cur_buff == -1)
        {
            
                (char *) AXIS2_MALLOC(env->allocator,
                                      sizeof(char) * GUTHTHILA_BUFFER_DEF_SIZE);
            
            
            
                guththila_reader_read(m->reader, m->buffer.buff[0], 0,
                                      GUTHTHILA_BUFFER_DEF_SIZE, env);
            
            
            {
                
                    m->buffer.buff[m->buffer.cur_buff][m->next++ -
                                                       GUTHTHILA_BUFFER_PRE_DATA_SIZE
                                                       (m->buffer)];
            
            
        
    
    


