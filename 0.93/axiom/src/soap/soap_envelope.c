/*
 * Copyright 2004,2005 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
 #include "_axiom_soap_envelope.h"
 #include <axiom_soap_body.h>
 #include <axiom_soap_header.h>
 #include <axiom_soap_header_block.h>
 #include <axis2_hash.h>
 #include <axiom_soap_const.h>
 #include <axiom_soap_builder.h>
 #include <axiom_soap_fault_code.h>
 #include <axiom_soap_fault_reason.h>
 #include <axiom_soap_fault_detail.h>
 #include <axiom_soap_fault_role.h>
 #include <axiom_soap_fault_value.h> 
 #include <axiom_soap_fault_text.h>
 #include <axiom_namespace_internal.h>
 /******************* impl struct *********************************************/
 
 typedef struct axiom_soap_envelope_impl_t
 {
    axiom_soap_envelope_t soap_envelope;
    /* corresponding om element node */    
    axiom_node_t *om_ele_node;
    /* soap version */
    int soap_version;
    /* soap header */
    axiom_soap_header_t *header;
    /* soap body */
    axiom_soap_body_t *body;
    /* pointer to soap builder */
    axiom_soap_builder_t *soap_builder;
    
 }axiom_soap_envelope_impl_t;
 
 /****************** Macro ****************************************************/
 
 #define AXIS2_INTF_TO_IMPL(envelope) ((axiom_soap_envelope_impl_t*)envelope)
 
 /****************** Function prototypes **************************************/

axiom_soap_header_t* AXIS2_CALL
axiom_soap_envelope_get_header(axiom_soap_envelope_t *envelope,
                                const axis2_env_t *env);
                                
                                
axiom_soap_header_block_t* AXIS2_CALL 
axiom_soap_envelope_add_header(axiom_soap_envelope_t *envelope,
                                const axis2_env_t *env,
                                axis2_char_t *namespace_uri, 
                                axis2_char_t *name);
                                
axiom_soap_body_t* AXIS2_CALL 
axiom_soap_envelope_get_body(axiom_soap_envelope_t *envelope,
                                const axis2_env_t *env);
                                
                                
axis2_status_t AXIS2_CALL 
axiom_soap_envelope_serialize(axiom_soap_envelope_t *envelope,
                                const axis2_env_t *env,
                                axiom_output_t *om_output, 
                                axis2_bool_t cache);
                                
axis2_status_t AXIS2_CALL
axiom_soap_envelope_free(axiom_soap_envelope_t *envelope,
                            const axis2_env_t *env);
axiom_node_t* AXIS2_CALL 
axiom_soap_envelope_get_base_node(axiom_soap_envelope_t *envelope,
                             const axis2_env_t *env);
                             
                                  
int AXIS2_CALL 
axiom_soap_envelope_get_soap_version(axiom_soap_envelope_t *envelope,
                                   const axis2_env_t *env);
                                   
axiom_namespace_t* AXIS2_CALL 
axiom_soap_envelope_get_namespace(axiom_soap_envelope_t *envelope,
                                  const axis2_env_t *env);
                                  
static axis2_status_t
check_and_set_soap_version(axiom_soap_envelope_t *env_impl, 
                           const axis2_env_t *env, 
                           axiom_namespace_t *ns);


axis2_status_t AXIS2_CALL
axiom_soap_envelope_set_soap_version(axiom_soap_envelope_t *soap_envelope,
                                     const axis2_env_t *env,
                                     int soap_version);
/*************** function implementations *************************************/

AXIS2_EXTERN axiom_soap_envelope_t* AXIS2_CALL
axiom_soap_envelope_create_null(const axis2_env_t *env)
{
    axiom_soap_envelope_impl_t *envelope_impl = NULL;
    AXIS2_ENV_CHECK(env, NULL);
    envelope_impl = (axiom_soap_envelope_impl_t*)AXIS2_MALLOC(
                    env->allocator,
                    sizeof(axiom_soap_envelope_impl_t));
    if(!envelope_impl)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    envelope_impl->soap_envelope.ops = NULL;
    envelope_impl->om_ele_node = NULL;
    envelope_impl->soap_version = AXIOM_SOAP12;    
    envelope_impl->header = NULL;
    envelope_impl->body = NULL;
    envelope_impl->soap_builder = NULL;
    
    envelope_impl->soap_envelope.ops  = AXIS2_MALLOC( env->allocator, 
                                        sizeof(axiom_soap_envelope_ops_t) );
    if (!envelope_impl->soap_envelope.ops)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        axiom_soap_envelope_free(&(envelope_impl->soap_envelope), env);
        return NULL;        
    }
   
    envelope_impl->soap_envelope.ops->free_fn = 
            axiom_soap_envelope_free;
    
    envelope_impl->soap_envelope.ops->get_base_node = 
            axiom_soap_envelope_get_base_node;

    envelope_impl->soap_envelope.ops->get_soap_version = 
            axiom_soap_envelope_get_soap_version;

    envelope_impl->soap_envelope.ops->get_body = 
            axiom_soap_envelope_get_body;
    
    envelope_impl->soap_envelope.ops->get_header = 
            axiom_soap_envelope_get_header;
   
    envelope_impl->soap_envelope.ops->get_namespace = 
            axiom_soap_envelope_get_namespace;
   
    envelope_impl->soap_envelope.ops->serialize = 
            axiom_soap_envelope_serialize;    

    envelope_impl->soap_envelope.ops->set_soap_version =
            axiom_soap_envelope_set_soap_version;
    return &(envelope_impl->soap_envelope);        
}


AXIS2_EXTERN axiom_soap_envelope_t* AXIS2_CALL
axiom_soap_envelope_create(const axis2_env_t *env, 
                           axiom_namespace_t *ns)
{
    axiom_soap_envelope_impl_t *envelope_impl = NULL;
    axiom_soap_envelope_t *envelope = NULL;
    axiom_element_t *ele = NULL;
    int status = AXIS2_SUCCESS;
    AXIS2_ENV_CHECK(env, NULL);
    AXIS2_PARAM_CHECK(env->error, ns, NULL);
    
    envelope = axiom_soap_envelope_create_null(env);
    if(!envelope)
        return NULL;        
    envelope_impl = AXIS2_INTF_TO_IMPL(envelope);
    
    status =  check_and_set_soap_version(&(envelope_impl->soap_envelope), env, ns);
    if(status == AXIS2_FAILURE)
    {
        AXIS2_FREE(env->allocator, envelope_impl); 
        return NULL; 
    }
     
    ele = axiom_element_create(env, NULL, 
                                  AXIOM_SOAP_ENVELOPE_LOCAL_NAME, ns, 
                                  &(envelope_impl->om_ele_node));
    if (!ele)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        axiom_soap_envelope_free(&(envelope_impl->soap_envelope), env);
        return NULL;
    }
    return &(envelope_impl->soap_envelope);        
}

AXIS2_EXTERN axiom_soap_envelope_t* AXIS2_CALL
axiom_soap_envelope_create_with_soap_version_prefix(const axis2_env_t *env,
                                                    int soap_version,
                                                    const axis2_char_t *prefix)
{
    axiom_namespace_t *ns        = NULL;
    const axis2_char_t *ns_prefix = NULL;
    const axis2_char_t *ns_uri    = NULL;
    AXIS2_ENV_CHECK(env, NULL);
    if(soap_version == AXIOM_SOAP11)
    {
        ns_uri = AXIOM_SOAP11_SOAP_ENVELOPE_NAMESPACE_URI;
    }
    else if(soap_version == AXIOM_SOAP12)
    {
        ns_uri = AXIOM_SOAP12_SOAP_ENVELOPE_NAMESPACE_URI;
    }
    else
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_INVALID_SOAP_VERSION, AXIS2_FAILURE);
        return NULL;
    }
    if(!prefix || AXIS2_STRCMP(prefix, "") == 0)
    {
        ns_prefix = AXIOM_SOAP_DEFAULT_NAMESPACE_PREFIX;
    }    
    else
    {
        ns_prefix = prefix;
    }
    
    ns = axiom_namespace_create(env, ns_uri, ns_prefix);
    if(!ns)
        return NULL;
    return axiom_soap_envelope_create(env, ns);
}                                                    

axis2_status_t AXIS2_CALL
axiom_soap_envelope_free(axiom_soap_envelope_t *envelope,
                       const axis2_env_t *env)
{
    axiom_soap_envelope_impl_t *envelope_impl = NULL;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    envelope_impl = AXIS2_INTF_TO_IMPL(envelope);
    if(envelope_impl->header)
    {
        AXIOM_SOAP_HEADER_FREE(envelope_impl->header, env);
        envelope_impl->header = NULL;      
    }
    if(envelope_impl->body)
    {
        AXIOM_SOAP_BODY_FREE(envelope_impl->body, env); 
        envelope_impl->body = NULL;        
    }
    if(envelope->ops)
    {
        AXIS2_FREE(env->allocator, envelope->ops);
        envelope->ops = NULL;
    }
    if(envelope_impl->om_ele_node)
    {
        if(envelope_impl->soap_builder)
        {
            AXIOM_SOAP_BUILDER_FREE(envelope_impl->soap_builder, env);
            envelope_impl->soap_builder = NULL;
            envelope_impl->om_ele_node = NULL;
        }
        else
        {
            AXIOM_NODE_FREE_TREE(envelope_impl->om_ele_node, env); 
            envelope_impl->om_ele_node = NULL;
        }
    }
    
    AXIS2_FREE(env->allocator, envelope_impl);
    envelope_impl = NULL;
    return AXIS2_SUCCESS;
}
    
axiom_node_t* AXIS2_CALL 
axiom_soap_envelope_get_base_node(axiom_soap_envelope_t *envelope,
                                const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, NULL);
    return AXIS2_INTF_TO_IMPL(envelope)->om_ele_node;
}

axis2_status_t AXIS2_CALL 
axiom_soap_envelope_set_base_node(axiom_soap_envelope_t *envelope,
                                  const axis2_env_t *env,
                                  axiom_node_t *node)
{
   axiom_soap_envelope_impl_t *envelope_impl = NULL;
   AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
   AXIS2_PARAM_CHECK(env->error, node, AXIS2_FAILURE);
   envelope_impl = AXIS2_INTF_TO_IMPL(envelope);
   if(AXIOM_NODE_GET_NODE_TYPE(node, env) != AXIOM_ELEMENT)
   {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_INVALID_BASE_TYPE, AXIS2_FAILURE);
        return AXIS2_FAILURE;
   }
   envelope_impl->om_ele_node = node;
   return AXIS2_SUCCESS;
}  
                                             
int AXIS2_CALL 
axiom_soap_envelope_get_soap_version(axiom_soap_envelope_t *envelope,
                                   const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    return AXIS2_INTF_TO_IMPL(envelope)->soap_version;    
}
 
/** this is an internal function */ 
axis2_status_t AXIS2_CALL 
axiom_soap_envelope_set_soap_version_internal(axiom_soap_envelope_t *envelope,
                                   const axis2_env_t *env,
                                   int soap_version)
{
    axiom_soap_envelope_impl_t *envelope_impl = NULL;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    envelope_impl = AXIS2_INTF_TO_IMPL(envelope);
    envelope_impl->soap_version = soap_version;
    
    return AXIS2_SUCCESS;
}

axiom_soap_header_t* AXIS2_CALL 
axiom_soap_envelope_get_header(axiom_soap_envelope_t *envelope,
                                const axis2_env_t *env)
{
    axiom_soap_envelope_impl_t *envelope_impl = NULL;
    int status = AXIS2_SUCCESS;
    AXIS2_ENV_CHECK(env, NULL);
    envelope_impl = AXIS2_INTF_TO_IMPL(envelope);
    
    if(envelope_impl->header)
    {
        return envelope_impl->header;
    }
    else if(envelope_impl->soap_builder)
    {
        while(!(envelope_impl->header) && !AXIOM_NODE_IS_COMPLETE(
                envelope_impl->om_ele_node, env))
        {
            status = AXIOM_SOAP_BUILDER_NEXT(envelope_impl->soap_builder, env);  
            if(status == AXIS2_FAILURE)
               break;
        }
    }        
    
    return envelope_impl->header;
}

axiom_soap_header_block_t* AXIS2_CALL 
axiom_soap_envelope_add_header(axiom_soap_envelope_t *envelope,
                                const axis2_env_t *env,
                                axis2_char_t *namespace_uri, 
                                axis2_char_t *name)
{
    axiom_soap_envelope_impl_t *envelope_impl = NULL;
    axiom_namespace_t *ns = NULL;
    AXIS2_ENV_CHECK(env, NULL);
    envelope_impl = AXIS2_INTF_TO_IMPL(envelope);
    
    /* TODO : cache SOAP header and envelope instead of looking them up?*/
    if(!envelope_impl->header)
        return NULL;
    
    if (namespace_uri)
    {
        ns = axiom_namespace_create(env, namespace_uri, NULL);
    }
    
    return axiom_soap_header_block_create_with_parent(env, name, ns, envelope_impl->header);
}

axiom_soap_body_t* AXIS2_CALL 
axiom_soap_envelope_get_body(axiom_soap_envelope_t *envelope,
                            const axis2_env_t *env)
{
    axiom_soap_envelope_impl_t *envelope_impl = NULL;
    int status = AXIS2_SUCCESS;
    AXIS2_ENV_CHECK(env, NULL);
    envelope_impl = AXIS2_INTF_TO_IMPL(envelope);
    
    if(envelope_impl->body)
    {
        return envelope_impl->body;
    }
    else if(envelope_impl->soap_builder)
    {
        while(!(envelope_impl->body)  && !AXIOM_NODE_IS_COMPLETE(envelope_impl->om_ele_node, env))
        {
            status = AXIOM_SOAP_BUILDER_NEXT(envelope_impl->soap_builder, env);
            if(status == AXIS2_FAILURE)
            {
                return NULL;
            }                
        }
    }
    return envelope_impl->body;
}

axis2_status_t AXIS2_CALL 
axiom_soap_envelope_serialize(axiom_soap_envelope_t *envelope,
                              const axis2_env_t *env,
                              axiom_output_t *om_output, 
                              axis2_bool_t cache)
{
    axiom_soap_envelope_impl_t *envelope_impl = NULL;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, envelope, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, om_output, AXIS2_FAILURE);
    
    envelope_impl = AXIS2_INTF_TO_IMPL(envelope);
/*
   if soap version is soap11 we modify the soap fault part.
   This is done because the builder construct a soap12 fault all
   the time. So when serializing if the soap version is soap11
   we should convert it back to soap11 fault
*/
    if(envelope_impl->soap_version == AXIOM_SOAP11)
    {
        axiom_soap_body_t *soap_body = NULL;
        soap_body = AXIOM_SOAP_ENVELOPE_GET_BODY(envelope, env);
        if(soap_body)
        {
            axiom_soap_fault_t *soap_fault = NULL;
            if(AXIOM_SOAP_BODY_HAS_FAULT(soap_body, env))
            {
                soap_fault = AXIOM_SOAP_BODY_GET_FAULT(soap_body, env);
                if(soap_fault)
                {   
                    axiom_soap_fault_code_t *fault_code = NULL;
                    axiom_soap_fault_reason_t *fault_reason = NULL;
                    axiom_soap_fault_detail_t *fault_detail = NULL;
                    axiom_soap_fault_role_t *fault_role = NULL;
                    fault_code = AXIOM_SOAP_FAULT_GET_CODE(soap_fault, env);
                    if(fault_code)
                    {
                        axiom_node_t *fault_code_om_node = NULL;
                        axiom_element_t *fault_code_om_ele = NULL;
                        axiom_node_t *fault_value_om_node = NULL;
                        axiom_element_t *fault_value_om_ele = NULL;
                        axiom_soap_fault_value_t *fault_value = NULL;
                        axis2_char_t *text = NULL;

                        fault_code_om_node = AXIOM_SOAP_FAULT_CODE_GET_BASE_NODE(fault_code, env);
                        if(NULL != fault_code_om_node)
                        {
                           fault_code_om_ele = (axiom_element_t *)
                           AXIOM_NODE_GET_DATA_ELEMENT(fault_code_om_node, env);
                           if(NULL != fault_code_om_ele)
                           {                               
                                AXIOM_ELEMENT_SET_LOCALNAME(fault_code_om_ele, 
                                    env, AXIOM_SOAP11_SOAP_FAULT_CODE_LOCAL_NAME); 
                                
                                fault_value = AXIOM_SOAP_FAULT_CODE_GET_VALUE(fault_code, env);
                                
                                if(NULL != fault_value)
                                {
                                    fault_value_om_node = AXIOM_SOAP_FAULT_VALUE_GET_BASE_NODE(fault_value, env);
                                    if(fault_value_om_node)
                                    {
                                       fault_value_om_node =  AXIOM_NODE_DETACH(fault_value_om_node, env);
                                        fault_value_om_ele = (axiom_element_t *)
                                        AXIOM_NODE_GET_DATA_ELEMENT(fault_value_om_node, env);
                                        if(fault_value_om_ele)
                                        {
                                            text = AXIOM_ELEMENT_GET_TEXT(fault_value_om_ele, env, fault_value_om_node);
                                            if(NULL != text)
                                            {
                                                AXIOM_ELEMENT_SET_TEXT(fault_code_om_ele, env, text, fault_code_om_node);
                                             }
                                             AXIOM_NODE_FREE_TREE(fault_value_om_node, env);
                                        }
                                        
                                    }
                                }
                            }
                        }                            
                    }
                    fault_reason = AXIOM_SOAP_FAULT_GET_REASON(soap_fault, env);
                    if(fault_reason)
                    {
                        axiom_node_t *fault_reason_om_node = NULL;
                        axiom_element_t *fault_reason_om_ele = NULL;
                        axiom_node_t *fault_text_om_node = NULL;
                        axiom_element_t *fault_text_om_ele = NULL;
                        axiom_soap_fault_text_t *fault_text = NULL;
                        axis2_char_t *text =  NULL;                        
                    
                        fault_reason_om_node = AXIOM_SOAP_FAULT_REASON_GET_BASE_NODE(fault_reason, env);
                        if(fault_reason_om_node)
                        {
                            fault_reason_om_ele  = (axiom_element_t *)
                                AXIOM_NODE_GET_DATA_ELEMENT(fault_reason_om_node, env);
                        
                            if(fault_reason_om_ele)
                            {
                                
                                AXIOM_ELEMENT_SET_LOCALNAME(fault_reason_om_ele, 
                                    env, AXIOM_SOAP11_SOAP_FAULT_STRING_LOCAL_NAME);
                        
                                fault_text = 
                                AXIOM_SOAP_FAULT_REASON_GET_FIRST_SOAP_FAULT_TEXT(fault_reason, env);
                                if(NULL != fault_text)
                                {
                                    fault_text_om_node = AXIOM_SOAP_FAULT_TEXT_GET_BASE_NODE(fault_text, env);
                                    if(fault_text_om_node)
                                    {
                                        fault_text_om_node = AXIOM_NODE_DETACH(fault_text_om_node, env);                                                        fault_text_om_ele  = (axiom_element_t *)
                                        AXIOM_NODE_GET_DATA_ELEMENT(fault_text_om_node, env);
                                        if(fault_text_om_ele)
                                        {
                                            text = AXIOM_ELEMENT_GET_TEXT(fault_text_om_ele, env, fault_text_om_node);
                                            if(NULL != text)
                                            {
                                                AXIOM_ELEMENT_SET_TEXT( fault_reason_om_ele, 
                                                    env, text, fault_reason_om_node);   
                                            }   
                                        }                     
                                        AXIOM_NODE_FREE_TREE(fault_text_om_node, env);
                                    }
                                }
                            }
                        }
                    }
                   
                    fault_role = AXIOM_SOAP_FAULT_GET_ROLE(soap_fault, env);
                    if(fault_role)
                    {
                        axiom_node_t *fault_role_om_node = NULL;
                        axiom_element_t *fault_role_om_ele = NULL;
                        
                        fault_role_om_node = AXIOM_SOAP_FAULT_ROLE_GET_BASE_NODE(fault_role, env);
                        if(fault_role_om_node)
                        {
                            fault_role_om_ele = (axiom_element_t *)
                                AXIOM_NODE_GET_DATA_ELEMENT(fault_role_om_node, env);
                            if(fault_role_om_ele)
                            {
                                AXIOM_ELEMENT_SET_LOCALNAME(fault_role_om_ele, env, 
                                    AXIOM_SOAP11_SOAP_FAULT_ACTOR_LOCAL_NAME);
                            }                                
                        }
                    }
                
                    fault_detail = AXIOM_SOAP_FAULT_GET_DETAIL(soap_fault, env);
                    if(fault_detail)
                    {
                        axiom_node_t *fault_detail_om_node = NULL;
                        axiom_element_t *fault_detail_om_ele = NULL;
                        fault_detail_om_node = AXIOM_SOAP_FAULT_DETAIL_GET_BASE_NODE(fault_detail, env);
                        if(fault_detail_om_node)
                        {
                            fault_detail_om_ele = (axiom_element_t *)
                                AXIOM_NODE_GET_DATA_ELEMENT(fault_detail_om_node, env);
                            if(fault_detail_om_ele)
                            {
                            AXIOM_ELEMENT_SET_LOCALNAME(fault_detail_om_ele, 
                                env, AXIOM_SOAP11_SOAP_FAULT_DETAIL_LOCAL_NAME);
                            }
                        }
                    }
                }  
            }
        }
    }
    /* write the xml version and encoding 
       These should be set to om output before calling the serialize function
       Otherwise default values will be written
    */
    AXIOM_OUTPUT_WRITE_XML_VERSION_ENCODING(om_output, env);
    return AXIOM_NODE_SERIALIZE(envelope_impl->om_ele_node, env, om_output);
}

axis2_status_t AXIS2_CALL 
axiom_soap_envelope_set_body(axiom_soap_envelope_t *envelope,
                            const axis2_env_t *env, 
                            axiom_soap_body_t *body)
{
    axiom_soap_envelope_impl_t *envelope_impl = NULL;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    envelope_impl = AXIS2_INTF_TO_IMPL(envelope);
    
    if (!(envelope_impl->body))
    {
        envelope_impl->body = body;
    }
    else
    {
        AXIS2_LOG_ERROR(env->log, AXIS2_LOG_SI, 
            "trying to set a soap bedy to envelope when a soap body alrady exists");
        return AXIS2_FAILURE;
    }
    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL axiom_soap_envelope_set_header(axiom_soap_envelope_t *envelope,
    const axis2_env_t *env, axiom_soap_header_t *header)
{
    axiom_soap_envelope_impl_t *envelope_impl = NULL;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    envelope_impl = AXIS2_INTF_TO_IMPL(envelope);
    
    if (!(envelope_impl->header))
    {
        envelope_impl->header = header;
    }
    else
    {
       AXIS2_LOG_ERROR(env->log, AXIS2_LOG_SI, 
        " trying to set a soap header to envelope when a soap header alrady exists");
        return AXIS2_FAILURE;
    }
    return AXIS2_SUCCESS;
}

axiom_namespace_t* AXIS2_CALL 
axiom_soap_envelope_get_namespace(axiom_soap_envelope_t *envelope,
                                  const axis2_env_t *env)
{
    axiom_soap_envelope_impl_t *envelope_impl = NULL;
    AXIS2_ENV_CHECK(env, NULL);
    envelope_impl = AXIS2_INTF_TO_IMPL(envelope);
    
    if (envelope_impl->om_ele_node)
    {
        axiom_element_t *ele = NULL;
        if (AXIOM_NODE_GET_NODE_TYPE(envelope_impl->om_ele_node, env) == AXIOM_ELEMENT)
        {
            ele = (axiom_element_t*)AXIOM_NODE_GET_DATA_ELEMENT(envelope_impl->om_ele_node, env);
            if (ele)
            {
                return AXIOM_ELEMENT_GET_NAMESPACE(ele, env, envelope_impl->om_ele_node);
            }
        }
    }
    return NULL;
}

axis2_status_t AXIS2_CALL
axiom_soap_envelope_set_builder(axiom_soap_envelope_t *envelope,
                                const axis2_env_t *env,
                                axiom_soap_builder_t *soap_builder)
{
    axiom_soap_envelope_impl_t *envelope_impl = NULL;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, soap_builder, AXIS2_FAILURE);
    envelope_impl = AXIS2_INTF_TO_IMPL(envelope);
    envelope_impl->soap_builder = soap_builder;
    return AXIS2_SUCCESS;
}

AXIS2_EXTERN axiom_soap_envelope_t * AXIS2_CALL
axiom_soap_envelope_create_default_soap_envelope(const axis2_env_t *env,
                                                 int soap_version)
{
    axiom_soap_envelope_t *soap_env = NULL;
    axiom_soap_header_t *soap_header = NULL;
    axiom_soap_body_t *soap_body = NULL;
    axiom_namespace_t *om_ns = NULL;
    axiom_soap_envelope_impl_t *env_impl = NULL;
    AXIS2_ENV_CHECK(env, NULL);
    if(soap_version == AXIOM_SOAP11)
    {
        om_ns = axiom_namespace_create(env,
            AXIOM_SOAP11_SOAP_ENVELOPE_NAMESPACE_URI, 
            AXIOM_SOAP_DEFAULT_NAMESPACE_PREFIX);
        if(!om_ns)
            return NULL;    
        soap_env = axiom_soap_envelope_create(env, om_ns);
        env_impl = AXIS2_INTF_TO_IMPL(soap_env);
        
        soap_header = axiom_soap_header_create_with_parent(env, soap_env);
        soap_body   = axiom_soap_body_create_with_parent(env, soap_env);
        env_impl->body = soap_body;
        env_impl->header = soap_header;
        return soap_env;    
    }
    else if(soap_version == AXIOM_SOAP12)
    {
        om_ns = axiom_namespace_create(env,
            AXIOM_SOAP12_SOAP_ENVELOPE_NAMESPACE_URI, 
            AXIOM_SOAP_DEFAULT_NAMESPACE_PREFIX);
        if(!om_ns)
            return NULL;    
        soap_env = axiom_soap_envelope_create(env, om_ns);
        env_impl = AXIS2_INTF_TO_IMPL(soap_env);
        
        soap_header = axiom_soap_header_create_with_parent(env, soap_env);
        soap_body   = axiom_soap_body_create_with_parent(env, soap_env);
        env_impl->body = soap_body;
        env_impl->header = soap_header;
        return soap_env;    
    }
    
    AXIS2_ERROR_SET(env->error, 
        AXIS2_ERROR_INVALID_SOAP_VERSION, AXIS2_FAILURE);
    return NULL;
}

AXIS2_EXTERN axiom_soap_envelope_t * AXIS2_CALL
axiom_soap_envelope_create_default_soap_fault_envelope(const axis2_env_t *env,
    const axis2_char_t *code_value, 
    const axis2_char_t *reason_text, 
    const int soap_version,
    axis2_array_list_t *sub_codes,
    axiom_node_t *detail_node)
{
    axiom_soap_envelope_t *soap_env = NULL;
    axiom_soap_body_t *soap_body = NULL;
    axiom_soap_envelope_impl_t *env_impl = NULL;
   axiom_soap_fault_t *fault = NULL;
    AXIS2_ENV_CHECK(env, NULL);

   if (AXIOM_SOAP11 != soap_version && AXIOM_SOAP12 != soap_version)
   {
      AXIS2_ERROR_SET(env->error,
         AXIS2_ERROR_INVALID_SOAP_VERSION, AXIS2_FAILURE);
      return NULL;
   }
   
   soap_env = axiom_soap_envelope_create_default_soap_envelope(env, soap_version);
   if (!soap_env)
   {
        return NULL;
   }
   env_impl = AXIS2_INTF_TO_IMPL(soap_env);

    soap_body = AXIOM_SOAP_ENVELOPE_GET_BODY(soap_env, env);
   if (!soap_body)
   {
      AXIOM_SOAP_ENVELOPE_FREE(soap_env, env);
      return NULL;
   }
   fault = axiom_soap_fault_create_default_fault(env, soap_body,
            code_value, reason_text, soap_version);
   if (!fault)
   {
      AXIOM_SOAP_ENVELOPE_FREE(soap_env, env);
      return NULL;
   }

    if (sub_codes)
    {
        int i = 0;
        axiom_soap_fault_code_t *fault_code = NULL;
        fault_code = AXIOM_SOAP_FAULT_GET_CODE(fault, env);
        if (fault_code)
        {
            for ( i = 0; i < AXIS2_ARRAY_LIST_SIZE(sub_codes, env); i++)
            {
                axis2_char_t *sub_code = (axis2_char_t*) AXIS2_ARRAY_LIST_GET(sub_codes, env, i);
                if (sub_code)
                {
                    axiom_soap_fault_sub_code_create_with_parent_value(env, fault_code, sub_code);
                }
            }
        }
    }

    if (detail_node)
    {
        axiom_soap_fault_detail_t *detail = 
            axiom_soap_fault_detail_create_with_parent(env, fault);
        if (detail)
        {
            AXIOM_SOAP_FAULT_DETAIL_ADD_DETAIL_ENTRY(detail, env, detail_node);
        }
    }

   return soap_env;

}

static axis2_status_t
check_and_set_soap_version(axiom_soap_envelope_t *envelope,
                           const axis2_env_t *env,
                           axiom_namespace_t *ns)
{
    axiom_soap_envelope_impl_t *envelope_impl = NULL;
    axis2_char_t *uri = NULL;
    if(!envelope)
        return AXIS2_FAILURE;
    if(!ns)
        return AXIS2_FAILURE;
         
    envelope_impl = AXIS2_INTF_TO_IMPL(envelope);
    
    uri = AXIOM_NAMESPACE_GET_URI(ns, env);
    if(!uri)
        return AXIS2_FAILURE;
        
    if(AXIS2_STRCMP(uri, AXIOM_SOAP11_SOAP_ENVELOPE_NAMESPACE_URI) == 0)
    {
        envelope_impl->soap_version = AXIOM_SOAP11;
        return AXIS2_SUCCESS;
    }
    else if(AXIS2_STRCMP(uri, AXIOM_SOAP12_SOAP_ENVELOPE_NAMESPACE_URI) == 0)
    {
        envelope_impl->soap_version = AXIOM_SOAP12;
        return AXIS2_SUCCESS;
    }
    else
    {
        AXIS2_ERROR_SET(env->error, 
            AXIS2_ERROR_INVALID_SOAP_NAMESPACE_URI, AXIS2_FAILURE);
    }
    return AXIS2_FAILURE;
}

axis2_status_t AXIS2_CALL
axiom_soap_envelope_set_soap_version(axiom_soap_envelope_t *soap_envelope,
                                     const axis2_env_t *env,
                                     int soap_version)
{
    axiom_soap_envelope_impl_t *envelope_impl = NULL;
    axiom_element_t *env_ele  = NULL;
    axiom_namespace_t *env_ns = NULL;
    const axis2_char_t *ns_uri         = NULL;
    int status = AXIS2_SUCCESS;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    
    envelope_impl = AXIS2_INTF_TO_IMPL(soap_envelope);
    
    if(soap_version == AXIOM_SOAP11)
    {
        ns_uri = AXIOM_SOAP11_SOAP_ENVELOPE_NAMESPACE_URI;
    }
    else if(soap_version == AXIOM_SOAP12)
    {
        ns_uri = AXIOM_SOAP12_SOAP_ENVELOPE_NAMESPACE_URI;
    }
    else
    {   /** TODO set error */
        return AXIS2_FAILURE;
    }
    
    env_ele = (axiom_element_t*)
        AXIOM_NODE_GET_DATA_ELEMENT(envelope_impl->om_ele_node,
                                       env);
    if(!env_ele)
    {
        return AXIS2_FAILURE;
    }
                                           
    env_ns = AXIOM_ELEMENT_GET_NAMESPACE(env_ele, env, envelope_impl->om_ele_node);
    if(!env_ns)
        return AXIS2_FAILURE;

    status = axiom_namespace_set_uri(env_ns, env, ns_uri);
    if(status == AXIS2_SUCCESS)
    {
        axiom_soap_envelope_set_soap_version_internal(soap_envelope, env, soap_version);
        return AXIS2_SUCCESS;
    }
    return AXIS2_FAILURE;
}