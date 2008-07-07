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
 
 /** <wsa:RelatesTo RelationshipType="..."?>xs:anyURI</wsa:RelatesTo> */

#include <axis2_msg_info_headers.h>
#include <axis2_string.h>

typedef struct axis2_msg_info_headers_impl
{
    axis2_msg_info_headers_t msg_info_headers;    
    /** The address of the intended receiver of the message. This is mandatory */
    axis2_endpoint_ref_t *to;
    /** Reference of the endpoint where the message originated from */
    axis2_endpoint_ref_t *from;
    /** Pair of values that indicate how this message related to another message */
    axis2_relates_to_t *relates_to;    
    /** identifies the intended receiver for replies to the message,
        if this is set, none and anonymous settings are ignored */
    axis2_endpoint_ref_t *reply_to;
    /** reply to should be none */
    axis2_bool_t reply_to_none;
    /** reply to should be anonymous, this is overwridden by none*/
    axis2_bool_t reply_to_anonymous;
    /** identifies the intended receiver for faults related to the message 
        if this is set, none and anonymous settings are ignored */
    axis2_endpoint_ref_t *fault_to;
    /** fault to should be none */
    axis2_bool_t fault_to_none;
    /** fault to should be anonymous, this is overwridden by none*/
    axis2_bool_t fault_to_anonymous;
    /** action */
    axis2_char_t *action;    
    /** message Id */
    axis2_char_t *message_id;
    /** referance parameters */
    axis2_array_list_t *ref_params;
}
axis2_msg_info_headers_impl_t;

/** Interface to implementation conversion macro */
#define AXIS2_INTF_TO_IMPL(msg_info_headers) ((axis2_msg_info_headers_impl_t *)msg_info_headers)


axis2_endpoint_ref_t *AXIS2_CALL 
axis2_msg_info_headers_get_to(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env); 
                              
axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_to(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    axis2_endpoint_ref_t *to);
                              
axis2_endpoint_ref_t *AXIS2_CALL 
axis2_msg_info_headers_get_from(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env);
                                
axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_from(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    axis2_endpoint_ref_t *from);
                                
axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_reply_to_none(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    axis2_bool_t none);

axis2_bool_t AXIS2_CALL 
axis2_msg_info_headers_get_reply_to_none(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env);

axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_reply_to_anonymous(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    axis2_bool_t anonymous);

axis2_bool_t AXIS2_CALL 
axis2_msg_info_headers_get_reply_to_anonymous(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env);

axis2_endpoint_ref_t *AXIS2_CALL 
axis2_msg_info_headers_get_reply_to(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env);
                                    
axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_reply_to(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    axis2_endpoint_ref_t *reply_to);
                                    
axis2_endpoint_ref_t *AXIS2_CALL 
axis2_msg_info_headers_get_fault_to(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env);
                                    
axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_fault_to(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    axis2_endpoint_ref_t *fault_to);
                                    
axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_fault_to_none(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    axis2_bool_t none);

axis2_bool_t AXIS2_CALL 
axis2_msg_info_headers_get_fault_to_none(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env);

axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_fault_to_anonymous(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    axis2_bool_t anonymous);

axis2_bool_t AXIS2_CALL 
axis2_msg_info_headers_get_fault_to_anonymous(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env);

axis2_char_t *AXIS2_CALL 
axis2_msg_info_headers_get_action(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env);
                                  
axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_action(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    const axis2_char_t *action);
                                  
axis2_char_t *AXIS2_CALL 
axis2_msg_info_headers_get_message_id(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env);
                                      
axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_message_id(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    const axis2_char_t *message_id);
                                      
axis2_relates_to_t *AXIS2_CALL 
axis2_msg_info_headers_get_relates_to(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env);
                                      
axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_relates_to(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    axis2_relates_to_t *relates_to);
                                      
axis2_array_list_t *AXIS2_CALL 
axis2_msg_info_headers_get_ref_params(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env);
                                      
axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_add_ref_param(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    axiom_node_t *ref_param);
                                     
axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_free(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env);
                            
/**
 * Addressing Header MUST have a to and an action
 *
 * @param wsaTo
 * @param action
 */
axis2_msg_info_headers_t *AXIS2_CALL 
axis2_msg_info_headers_create(
    const axis2_env_t *env, 
    axis2_endpoint_ref_t *to,
    const axis2_char_t *action) 
{
    axis2_msg_info_headers_impl_t *msg_info_headers_impl = NULL;
    
    AXIS2_ENV_CHECK(env, NULL);
    
    msg_info_headers_impl = 
        AXIS2_MALLOC( env->allocator, sizeof(axis2_msg_info_headers_impl_t) );
    
    if (!msg_info_headers_impl)
    { 
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;        
    }

    msg_info_headers_impl->msg_info_headers.ops = NULL;
    msg_info_headers_impl->to = NULL;
    msg_info_headers_impl->from = NULL;
    msg_info_headers_impl->relates_to = NULL;    
    msg_info_headers_impl->reply_to_none= AXIS2_FALSE;
    msg_info_headers_impl->reply_to_anonymous = AXIS2_FALSE;
    msg_info_headers_impl->reply_to = NULL;
    msg_info_headers_impl->fault_to_none= AXIS2_FALSE;
    msg_info_headers_impl->fault_to_anonymous = AXIS2_FALSE;
    msg_info_headers_impl->fault_to = NULL;
    msg_info_headers_impl->action = NULL;    
    msg_info_headers_impl->message_id = NULL;
    msg_info_headers_impl->ref_params = NULL;

    if (to)
    {
        msg_info_headers_impl->to = to;
    }
    
    if (action)
    {
        msg_info_headers_impl->action = AXIS2_STRDUP(action, env);
        if (!(msg_info_headers_impl->action))
        {
            AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
            axis2_msg_info_headers_free(&(msg_info_headers_impl->msg_info_headers), env);
            return NULL;        
        }
    }
    
    /* initialize ops */
    msg_info_headers_impl->msg_info_headers.ops  = 
        AXIS2_MALLOC( env->allocator, sizeof(axis2_msg_info_headers_ops_t) );
    
    if (!msg_info_headers_impl->msg_info_headers.ops)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        axis2_msg_info_headers_free(&(msg_info_headers_impl->msg_info_headers), env);
        return NULL;        
    }

    msg_info_headers_impl->msg_info_headers.ops->get_to = 
        axis2_msg_info_headers_get_to;
    
    msg_info_headers_impl->msg_info_headers.ops->set_to = 
        axis2_msg_info_headers_set_to;
    
    msg_info_headers_impl->msg_info_headers.ops->get_from = 
        axis2_msg_info_headers_get_from;
   
    msg_info_headers_impl->msg_info_headers.ops->set_from = 
        axis2_msg_info_headers_set_from;
        
    msg_info_headers_impl->msg_info_headers.ops->set_reply_to_none = 
        axis2_msg_info_headers_set_reply_to_none;
        
    msg_info_headers_impl->msg_info_headers.ops->get_reply_to_none = 
        axis2_msg_info_headers_get_reply_to_none;
        
    msg_info_headers_impl->msg_info_headers.ops->set_reply_to_anonymous= 
        axis2_msg_info_headers_set_reply_to_anonymous;
        
    msg_info_headers_impl->msg_info_headers.ops->get_reply_to_anonymous = 
        axis2_msg_info_headers_get_reply_to_anonymous;
        
    msg_info_headers_impl->msg_info_headers.ops->get_reply_to = 
        axis2_msg_info_headers_get_reply_to;
        
    msg_info_headers_impl->msg_info_headers.ops->set_reply_to = 
        axis2_msg_info_headers_set_reply_to;
        
    msg_info_headers_impl->msg_info_headers.ops->set_fault_to_none = 
        axis2_msg_info_headers_set_fault_to_none;
        
    msg_info_headers_impl->msg_info_headers.ops->get_fault_to_none = 
        axis2_msg_info_headers_get_fault_to_none;
        
    msg_info_headers_impl->msg_info_headers.ops->set_fault_to_anonymous= 
        axis2_msg_info_headers_set_fault_to_anonymous;
        
    msg_info_headers_impl->msg_info_headers.ops->get_fault_to_anonymous = 
        axis2_msg_info_headers_get_fault_to_anonymous;
        
    msg_info_headers_impl->msg_info_headers.ops->get_fault_to = 
        axis2_msg_info_headers_get_fault_to;
        
    msg_info_headers_impl->msg_info_headers.ops->set_fault_to = 
        axis2_msg_info_headers_set_fault_to;
        
    msg_info_headers_impl->msg_info_headers.ops->get_action = 
        axis2_msg_info_headers_get_action;
        
    msg_info_headers_impl->msg_info_headers.ops->set_action = 
        axis2_msg_info_headers_set_action;
        
    msg_info_headers_impl->msg_info_headers.ops->get_message_id = 
        axis2_msg_info_headers_get_message_id;
        
    msg_info_headers_impl->msg_info_headers.ops->set_message_id = 
        axis2_msg_info_headers_set_message_id;
        
    msg_info_headers_impl->msg_info_headers.ops->get_relates_to = 
        axis2_msg_info_headers_get_relates_to;
        
    msg_info_headers_impl->msg_info_headers.ops->set_relates_to = 
        axis2_msg_info_headers_set_relates_to;
        
    msg_info_headers_impl->msg_info_headers.ops->get_ref_params = 
        axis2_msg_info_headers_get_ref_params;
        
    msg_info_headers_impl->msg_info_headers.ops->add_ref_param = 
        axis2_msg_info_headers_add_ref_param;
        
    msg_info_headers_impl->msg_info_headers.ops->free = 
        axis2_msg_info_headers_free;

    return &(msg_info_headers_impl->msg_info_headers);
}

/**
 * Method getTo
 *
 * @return
 */
axis2_endpoint_ref_t *AXIS2_CALL 
axis2_msg_info_headers_get_to(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env) 
{
    AXIS2_ENV_CHECK(env, NULL);
    return AXIS2_INTF_TO_IMPL(msg_info_headers)->to;
}

/**
 * Method set_to
 *
 * @param to
 */
axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_to(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    axis2_endpoint_ref_t *to) 
{
    axis2_msg_info_headers_impl_t *msg_info_headers_impl = NULL;
    
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    
    msg_info_headers_impl = AXIS2_INTF_TO_IMPL(msg_info_headers);
    
    if (msg_info_headers_impl->to && to) /* if the incomming to is NULL, 
                                            we consider that to be a reset,
                                            so dont free */
    {
        AXIS2_ENDPOINT_REF_FREE(msg_info_headers_impl->to, env);
        msg_info_headers_impl->to = NULL;
    }
    msg_info_headers_impl->to = to;
    return AXIS2_SUCCESS;
}

/**
 * Method getFrom
 *
 * @return
 */
axis2_endpoint_ref_t *AXIS2_CALL 
axis2_msg_info_headers_get_from(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env) 
{
    AXIS2_ENV_CHECK(env, NULL);
    return AXIS2_INTF_TO_IMPL(msg_info_headers)->from;
}

/**
 * Method set_from
 *
 * @param from
 */
axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_from(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    axis2_endpoint_ref_t *from) 
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_INTF_TO_IMPL(msg_info_headers)->from = from;
    return AXIS2_SUCCESS;
}

/**
 * Method getReply_to
 *
 * @return
 */
axis2_endpoint_ref_t *AXIS2_CALL 
axis2_msg_info_headers_get_reply_to(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env) 
{
    AXIS2_ENV_CHECK(env, NULL);
    return AXIS2_INTF_TO_IMPL(msg_info_headers)->reply_to;
}

/**
 * Method set_reply_to
 *
 * @param reply_to
 */
axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_reply_to(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    axis2_endpoint_ref_t *reply_to) 
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_INTF_TO_IMPL(msg_info_headers)->reply_to = reply_to;
    return AXIS2_SUCCESS;
}

/**
 * Method getFault_to
 *
 * @return
 */
axis2_endpoint_ref_t *AXIS2_CALL 
axis2_msg_info_headers_get_fault_to(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env) 
{
    AXIS2_ENV_CHECK(env, NULL);
    return AXIS2_INTF_TO_IMPL(msg_info_headers)->fault_to;
}

/**
 * Method set_fault_to
 *
 * @param fault_to
 */
axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_fault_to(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    axis2_endpoint_ref_t *fault_to) 
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_INTF_TO_IMPL(msg_info_headers)->fault_to = fault_to;
    return AXIS2_SUCCESS;
}

/**
 * Method get_action
 *
 * @return
 */
axis2_char_t *AXIS2_CALL 
axis2_msg_info_headers_get_action(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env) 
{
    AXIS2_ENV_CHECK(env, NULL);
    return AXIS2_INTF_TO_IMPL(msg_info_headers)->action;
}

/**
 * Method set_action
 *
 * @param action
 */
axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_action(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    const axis2_char_t *action) 
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    if(NULL != AXIS2_INTF_TO_IMPL(msg_info_headers)->action)
    {
        AXIS2_FREE(env->allocator, AXIS2_INTF_TO_IMPL(msg_info_headers)->action);
        AXIS2_INTF_TO_IMPL(msg_info_headers)->action = NULL;
    }
    if(NULL != action)
        AXIS2_INTF_TO_IMPL(msg_info_headers)->action = AXIS2_STRDUP(action, env);
    /* We should be able to reset action by passing NULL
     * so don't throw failure if action is NULL
     */
    /*if(NULL == AXIS2_INTF_TO_IMPL(msg_info_headers)->action)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return AXIS2_FAILURE;
    }*/
    return AXIS2_SUCCESS;
}

/**
 * Method get_message_id
 *
 * @return
 */
axis2_char_t *AXIS2_CALL 
axis2_msg_info_headers_get_message_id(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env) 
{
    AXIS2_ENV_CHECK(env, NULL);
    return AXIS2_INTF_TO_IMPL(msg_info_headers)->message_id;
}

/**
 * Method set_message_id
 *
 * @param message_id
 */
axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_message_id(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    const axis2_char_t *message_id) 
{
    axis2_msg_info_headers_impl_t *msg_info_headers_impl = NULL;
    
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    
    msg_info_headers_impl = AXIS2_INTF_TO_IMPL(msg_info_headers);
    
    if (msg_info_headers_impl->message_id)
    {
        AXIS2_FREE(env->allocator, msg_info_headers_impl->message_id);
        msg_info_headers_impl->message_id = NULL;        
    }
    
    if (message_id)
    {
        msg_info_headers_impl->message_id = AXIS2_STRDUP(message_id, env);
        if (!(msg_info_headers_impl->message_id))
        {
            AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);            
            return AXIS2_FAILURE;        
        }
    }
    
    return AXIS2_SUCCESS;
}

/**
 * Method get_relates_to
 *
 * @return
 */
axis2_relates_to_t *AXIS2_CALL 
axis2_msg_info_headers_get_relates_to(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env) 
{
    AXIS2_ENV_CHECK(env, NULL);
    return AXIS2_INTF_TO_IMPL(msg_info_headers)->relates_to;
}

/**
 * Method set_relates_to
 *
 * @param relates_to
 */
axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_relates_to(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    axis2_relates_to_t *relates_to) 
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_INTF_TO_IMPL(msg_info_headers)->relates_to = relates_to;
    return AXIS2_SUCCESS;
}

axis2_array_list_t *AXIS2_CALL 
axis2_msg_info_headers_get_ref_params(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env) 
{
    AXIS2_ENV_CHECK(env, NULL);
    return AXIS2_INTF_TO_IMPL(msg_info_headers)->ref_params;
}

axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_add_ref_param(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    axiom_node_t *ref_param) 
{
    axis2_msg_info_headers_impl_t *msg_info_headers_impl = NULL;
    
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    
    msg_info_headers_impl = AXIS2_INTF_TO_IMPL(msg_info_headers);
    
    if (!(msg_info_headers_impl->ref_params))
    {
        msg_info_headers_impl->ref_params = axis2_array_list_create(env, 10);
        if (!(msg_info_headers_impl->ref_params))
            return AXIS2_FAILURE;
    }

    if (ref_param) 
    {
        return AXIS2_ARRAY_LIST_ADD(msg_info_headers_impl->ref_params, env, ref_param);
    }
    
    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_free(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env)
{
    axis2_msg_info_headers_impl_t *msg_info_headers_impl = NULL;
    
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    
    msg_info_headers_impl = AXIS2_INTF_TO_IMPL(msg_info_headers);
    
    if (msg_info_headers_impl->to)
    {
        AXIS2_ENDPOINT_REF_FREE(msg_info_headers_impl->to, env);
        msg_info_headers_impl->to = NULL;
    }
    if (msg_info_headers_impl->from)
    {
        AXIS2_ENDPOINT_REF_FREE(msg_info_headers_impl->from, env);
        msg_info_headers_impl->from = NULL;
    }
    if (msg_info_headers_impl->reply_to)
    {
        AXIS2_ENDPOINT_REF_FREE(msg_info_headers_impl->reply_to, env);
        msg_info_headers_impl->reply_to = NULL;
    }
    if (msg_info_headers_impl->relates_to)
    {
        AXIS2_ENDPOINT_REF_FREE(msg_info_headers_impl->relates_to, env);
        msg_info_headers_impl->relates_to = NULL;
    }
    if (msg_info_headers_impl->msg_info_headers.ops)
    {
        AXIS2_FREE(env->allocator, msg_info_headers_impl->msg_info_headers.ops);
        msg_info_headers_impl->msg_info_headers.ops = NULL;
    }
    
    if (msg_info_headers_impl->ref_params)
    {
        AXIS2_ARRAY_LIST_FREE(msg_info_headers_impl->ref_params, env);
        msg_info_headers_impl->ref_params = NULL;
    }    
    if(NULL != AXIS2_INTF_TO_IMPL(msg_info_headers)->action)
    {
        AXIS2_FREE(env->allocator, AXIS2_INTF_TO_IMPL(msg_info_headers)->action);
        AXIS2_INTF_TO_IMPL(msg_info_headers)->action = NULL;
    }
    if (msg_info_headers_impl->message_id)
    {
        AXIS2_FREE(env->allocator, msg_info_headers_impl->message_id);
        msg_info_headers_impl->message_id = NULL;
    }
    
    AXIS2_FREE(env->allocator, msg_info_headers_impl);
    msg_info_headers_impl = NULL;
    
    return AXIS2_SUCCESS;
}


axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_reply_to_none(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    axis2_bool_t none)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_INTF_TO_IMPL(msg_info_headers)->reply_to_none = none;
    return AXIS2_SUCCESS;
}

axis2_bool_t AXIS2_CALL 
axis2_msg_info_headers_get_reply_to_none(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    return AXIS2_INTF_TO_IMPL(msg_info_headers)->reply_to_none;
}

axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_reply_to_anonymous(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    axis2_bool_t anonymous)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_INTF_TO_IMPL(msg_info_headers)->reply_to_anonymous = anonymous;
    return AXIS2_SUCCESS;
}

axis2_bool_t AXIS2_CALL 
axis2_msg_info_headers_get_reply_to_anonymous(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    return AXIS2_INTF_TO_IMPL(msg_info_headers)->reply_to_anonymous;
}

axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_fault_to_none(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    axis2_bool_t none)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_INTF_TO_IMPL(msg_info_headers)->fault_to_none = none;
    return AXIS2_SUCCESS;
}

axis2_bool_t AXIS2_CALL 
axis2_msg_info_headers_get_fault_to_none(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    return AXIS2_INTF_TO_IMPL(msg_info_headers)->fault_to_none;
}

axis2_status_t AXIS2_CALL 
axis2_msg_info_headers_set_fault_to_anonymous(
    struct axis2_msg_info_headers *msg_info_headers, 
    const axis2_env_t *env, 
    axis2_bool_t anonymous)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_INTF_TO_IMPL(msg_info_headers)->fault_to_anonymous = anonymous;
    return AXIS2_SUCCESS;
}

axis2_bool_t AXIS2_CALL 
axis2_msg_info_headers_get_fault_to_anonymous(
    const axis2_msg_info_headers_t *msg_info_headers, 
    const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    return AXIS2_INTF_TO_IMPL(msg_info_headers)->fault_to_anonymous;
}