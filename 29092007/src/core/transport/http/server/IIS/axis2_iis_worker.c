
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
    
#include <axis2_http_transport.h>
#include <axis2_conf.h>
#include <axutil_string.h>
#include <axis2_msg_ctx.h>
#include <axis2_http_out_transport_info.h>
#include <axis2_http_transport_utils.h>
#include <axis2_op_ctx.h>
#include <axis2_engine.h>
#include <axutil_uuid_gen.h>
#include <axis2_conf_init.h>
#include <axutil_url.h>
#include <axiom_soap.h>
#include "axis2_iis_out_transport_info.h"
#include "axis2_iis_stream.h"
#include "axis2_iis_worker.h"
    
// Files from iis
#include <httpfilt.h>
#include <httpext.h>
    
#include "axis2_iis_constants.h"
    
#define READ_SIZE  32
    
                                                             

                                                       
                                                       stream);

                                           
                                           
                                           
                                           
                                           

                                unsigned int l);

{
    
    

{
    
    {
    "200 OK", 6}, 
    {
    "202 Accepted", 12}, 
    {
"500 Internal Server Error", 25} 

{
    


    int status);

axis2_iis_worker_create(
                        
{
    
    
    
        AXIS2_MALLOC(env->allocator, sizeof(axis2_iis_worker_t));
    
        
    {
        
        
    
    
    
        
    {
        
        
    
    


axis2_iis_worker_free(
    
    
{
    
    
        
    {
        
        
    
    
    


axis2_iis_worker_process_request(
    
    
    
{
    
    
    
    
    
    
    
    
    
        //int content_length = -1;
        //axis2_char_t *req_url = NULL;
        axis2_char_t * body_string = NULL;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
        // Check the parameters
        if (!env)
        
    {
        
    
    
        
    {
        
                                      AXIS2_ERROR_INVALID_NULL_PARAM);
        
    
    
    
        
    {
        
                         
        
    
    
    
        lpECB->GetServerVariable(lpECB->ConnID, 
                                 
    
    
        lpECB->GetServerVariable(lpECB->ConnID, "SERVER_PORT", port, &cbSize);
    
    
        lpECB->GetServerVariable(lpECB->ConnID, "HTTP_URL", redirect_url,
                                 &cbSize);
    
    
        // create the url using the above variables                     
        sprintf(req_url, "%s%s%s%s", "http", server_name, port, original_url);
    
    
                                              (iis_worker->conf_ctx, env), env,
                                              
    
        axis2_conf_get_transport_in(axis2_conf_ctx_get_conf 
                                    (iis_worker->conf_ctx, env), env,
                                    
    
    
    
    
    
        
    {
        
            axutil_string_create_assume_ownership(env, &ctx_uuid);
        
        
    
    
    
                                               iis_out_transport_info);
    
    
         GetServerVariable(lpECB->ConnID, "HTTP_SOAPAction", soap_action,
                           &cbSize))
        
    {
        
    
    
    
        
    {
        
                         " creating input stream.");
        
    
    
        
    {
        
            (env, msg_ctx, request_body, out_stream, 
             soap_str_action, 
             
                                                            
                                                            req_url));
        
            // If this is not a valid GET request display the list of displayed services.
            if (processed == AXIS2_FAILURE)
            
        {
            
                axis2_http_transport_utils_get_services_html(env, 
            
                
            {
                
            
            
                (iis_out_transport_info, env, "text/html");
            
        
    
    
    else if (stricmp(lpECB->lpszMethod, "POST") == 0)
        
    {
        
        
            (env, msg_ctx, request_body, out_stream, 
             lpECB->cbTotalBytes, 
        
            // generate a soap fault and send it
            if (status == AXIS2_FAILURE)
            
        {
            
            
            
            
                
            {
                
            
            
                
            {
                
                    AXIOM_SOAP11_FAULT_CODE_SENDER;
            
            
            else
                
            {
                
                    AXIOM_SOAP12_SOAP_FAULT_VALUE_SENDER;
            
            
                axis2_engine_create_fault_msg_ctx(engine, env, msg_ctx,
                                                  
                                                  axutil_error_get_message(env->
                                                                           error));
            
            
                
            {
                
                
            
            
            
        
    
    
        // Nothing wrong has happen. So proceed with the request
        if (-1 == send_status)
        
    {
        
        
            
        {
            
                
            {
                
                
            
            
        
        
        else
            
        {
            
        
    
    
        
    {
        
        };
        
        
        
            axis2_iis_out_transport_get_content(iis_out_transport_info);
        
        
             (lpECB, send_status, NULL, headers_names, headers_vhtml, 2))
            
        {
            
                             " writing response.");
        
        
            
        {
            
                             " writing response.");
        
        
        
    
    
    else
        
    {
        
            
        {
            
                             " writing response.");
        
    
    
        
    {
        
        
    
    
    



                                unsigned int l) 
{
    
    {
        
        {
            
            
            
                // If couldn't write the data at onece try again until all the data is written.
                while (written < l)
            {
                
                
                     WriteClient(lpECB->ConnID, 
                                 0))
                {
                    
                
                
            
        
        
    
    



                                           
                                           
                                           
                                           
{
    
    
    {
        
    
    
    {
        
        
        
        
            /*
             * Create the status line
             */ 
            if (reason)
        {
            
            
            
        
        
        else
        {
            
            {
            
                
                
                
            
                
                
                
            
                
                
                
            
                
                
                
            
        
        
            /*
             * Create response headers string
             */ 
            if (num_of_headers)
        {
            
            
            {
                
                
                
            
            
            
            
            
            {
                
                
                
                
            
            
        
        
        else
        {
            
        
        
              ServerSupportFunction(lpECB->ConnID,
                                    
                                    
                                    
        {
            
        
        
    
    



                                                           char ret_url[]) 
{
    
    
        
    
        
    
    



axis2_iis_worker_get_bytes(
                           
{
    
    
    
    
    
    
    
        
    {
        
        
        
        
        
            
        {
            
        
        
        
            
        {
            
        
    
    
    
        
    {
        
                                        (return_size + 2));
        
            axutil_stream_read(tmp_stream, env, buffer, 
        
    
    
    


