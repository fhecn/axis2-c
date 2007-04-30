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

#include <listener_manager.h>
#include <axis2.h>
#include <axis2_hash.h>
#include <axis2_transport_receiver.h>

typedef struct axis2_listener_manager_impl
{
    /** context base struct */
    axis2_listener_manager_t listener_manager;
    /** hash map of listeners */
    axis2_hash_t *listener_map;
    /** configuration context */
    axis2_conf_ctx_t *conf_ctx;
} axis2_listener_manager_impl_t;

/**
 * keep information about the listener for a given transport
 */
typedef struct axis2_transport_listener_state 
{
    int waiting_calls;
    axis2_transport_receiver_t *listener;
} axis2_transport_listener_state_t;


/** Interface to implementation conversion macro */
#define AXIS2_INTF_TO_IMPL(listener_manager) ((axis2_listener_manager_impl_t *)listener_manager)

axis2_status_t AXIS2_CALL axis2_listener_manager_make_sure_started(struct axis2_listener_manager *listener_manager, 
    axis2_env_t **env, 
    axis2_char_t *transport,
    axis2_conf_ctx_t *conf_ctx);
axis2_status_t AXIS2_CALL axis2_listener_manager_stop(struct axis2_listener_manager *listener_manager, 
    axis2_env_t **env, 
    axis2_char_t *transport);
axis2_endpoint_ref_t* AXIS2_CALL axis2_listener_manager_reply_to_epr(struct axis2_listener_manager *listener_manager, 
    axis2_env_t **env, 
    axis2_char_t *svc_name,
    axis2_char_t *transport);
axis2_status_t AXIS2_CALL axis2_listener_manager_free (struct axis2_listener_manager *listener_manager, 
                                   axis2_env_t **env);

axis2_conf_ctx_t *AXIS2_CALL
axis2_listener_manager_get_conf_ctx(axis2_listener_manager_t *listener_manager,
                                    axis2_env_t **env);

axis2_listener_manager_t* AXIS2_CALL axis2_listener_manager_create(axis2_env_t **env)
{
    axis2_listener_manager_impl_t *listener_manager_impl = NULL;
    
    AXIS2_ENV_CHECK(env, NULL);
    
    listener_manager_impl = AXIS2_MALLOC( (*env)->allocator, sizeof(axis2_listener_manager_impl_t) );
    if (!listener_manager_impl)
    { 
        AXIS2_ERROR_SET((*env)->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;        
    }

    listener_manager_impl->listener_manager.ops = NULL;
    listener_manager_impl->listener_map = NULL;
    listener_manager_impl->conf_ctx = NULL;
    
    listener_manager_impl->listener_map = axis2_hash_make(env);
    if (!(listener_manager_impl->listener_map))
    {
        axis2_listener_manager_free(&(listener_manager_impl->listener_manager), env);
        return NULL;        
    }
    
    /* initialize ops */    
    listener_manager_impl->listener_manager.ops  = AXIS2_MALLOC( (*env)->allocator, sizeof(axis2_listener_manager_ops_t) );
    if (!listener_manager_impl->listener_manager.ops)
    {
        AXIS2_ERROR_SET((*env)->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        axis2_listener_manager_free(&(listener_manager_impl->listener_manager), env);
        return NULL;        
    }

    listener_manager_impl->listener_manager.ops->make_sure_started = axis2_listener_manager_make_sure_started;
    listener_manager_impl->listener_manager.ops->stop = axis2_listener_manager_stop;
    listener_manager_impl->listener_manager.ops->reply_to_epr = axis2_listener_manager_reply_to_epr;
    listener_manager_impl->listener_manager.ops->get_conf_ctx = 
            axis2_listener_manager_get_conf_ctx;
    listener_manager_impl->listener_manager.ops->free = axis2_listener_manager_free;

    return &(listener_manager_impl->listener_manager);
}

axis2_status_t AXIS2_CALL axis2_listener_manager_make_sure_started(struct axis2_listener_manager *listener_manager, 
    axis2_env_t **env, 
    axis2_char_t *transport,
    axis2_conf_ctx_t *conf_ctx)
{
    axis2_listener_manager_impl_t *listener_manager_impl = NULL;
    axis2_transport_listener_state_t *tl_state = NULL;
    
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK((*env)->error, conf_ctx, AXIS2_FAILURE);
    
    listener_manager_impl = AXIS2_INTF_TO_IMPL(listener_manager);
    
    if (listener_manager_impl->conf_ctx)
    {
        if (conf_ctx != listener_manager_impl->conf_ctx)
        {
            AXIS2_ERROR_SET((*env)->error, AXIS2_ERROR_CLIENT_SIDE_SUPPORT_ONLY_ONE_CONF_CTX, AXIS2_FAILURE);
            return AXIS2_FAILURE;
        }
    }
    else
    {
        listener_manager_impl->conf_ctx = conf_ctx;
    }
    

    tl_state = (axis2_transport_listener_state_t*) axis2_hash_get(listener_manager_impl->listener_map, 
                transport, AXIS2_HASH_KEY_STRING);
    if (!tl_state) 
    {
        /*means this transport not yet started, start the transport*/
        axis2_transport_in_desc_t *transport_in = NULL;
        axis2_qname_t *qname = NULL;
        axis2_conf_t *conf = NULL;
        axis2_transport_receiver_t *listener = NULL;
        
        qname = axis2_qname_create(env, transport, NULL, NULL);
        if (qname)
        {
            conf = AXIS2_CONF_CTX_GET_CONF(conf_ctx, env);
            if (conf)
            {
                transport_in = AXIS2_CONF_GET_TRANSPORT_IN(conf, env, qname);
                if (transport_in)
                {
                    listener = AXIS2_TRANSPORT_IN_DESC_GET_RECV(transport_in, env);
                    if (listener)
                    {
                        AXIS2_TRANSPORT_RECEIVER_START(listener, env);
                        
                        tl_state  = AXIS2_MALLOC( (*env)->allocator, sizeof(axis2_transport_listener_state_t) );
                        if (!tl_state)
                        {
                            AXIS2_ERROR_SET((*env)->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
                        }
                        else
                        {
                            tl_state->listener = listener;
                            tl_state->waiting_calls = 0;
                            axis2_hash_set(listener_manager_impl->listener_map, transport, AXIS2_HASH_KEY_STRING, tl_state);
                        }                            
                    }
                }
            }
        }
    }
    
    if (tl_state)
    {
        tl_state->waiting_calls++;
        return AXIS2_SUCCESS;
    }
    else
        return AXIS2_FAILURE;
}

axis2_status_t AXIS2_CALL axis2_listener_manager_stop(struct axis2_listener_manager *listener_manager, 
    axis2_env_t **env, 
    axis2_char_t *transport)
{
    axis2_listener_manager_impl_t *listener_manager_impl = NULL;
    axis2_transport_listener_state_t *tl_state = NULL;
    axis2_status_t status = AXIS2_FAILURE;
    
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    
    listener_manager_impl = AXIS2_INTF_TO_IMPL(listener_manager);
    
    tl_state = (axis2_transport_listener_state_t*) axis2_hash_get(listener_manager_impl->listener_map, transport, AXIS2_HASH_KEY_STRING);
    if (tl_state) 
    {
        tl_state->waiting_calls--;
        if (tl_state->waiting_calls == 0) 
        {
            status = AXIS2_TRANSPORT_RECEIVER_STOP(tl_state->listener, env);
            if (status != AXIS2_SUCCESS)
                return status;
            
            axis2_hash_set(listener_manager_impl->listener_map, transport, AXIS2_HASH_KEY_STRING, NULL);            
        }
    }
    
    return status;
}

axis2_endpoint_ref_t* AXIS2_CALL axis2_listener_manager_reply_to_epr(struct axis2_listener_manager *listener_manager, 
    axis2_env_t **env, 
    axis2_char_t *svc_name,
    axis2_char_t *transport)
{
    axis2_listener_manager_impl_t *listener_manager_impl = NULL;
    axis2_transport_listener_state_t *tl_state = NULL;
    
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    
    listener_manager_impl = AXIS2_INTF_TO_IMPL(listener_manager);
    
    tl_state = (axis2_transport_listener_state_t*) axis2_hash_get(listener_manager_impl->listener_map, 
                    transport, AXIS2_HASH_KEY_STRING);
    if (tl_state) 
    {
        return AXIS2_TRANSPORT_RECEIVER_GET_REPLY_TO_EPR(tl_state->listener, env, svc_name);
    } 
    return NULL;
}

axis2_status_t AXIS2_CALL axis2_listener_manager_free (struct axis2_listener_manager *listener_manager, 
                                   axis2_env_t **env)
{
    axis2_listener_manager_impl_t *listener_manager_impl = NULL;
    
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    
    listener_manager_impl = AXIS2_INTF_TO_IMPL(listener_manager);
    
    if (listener_manager_impl->listener_manager.ops)
    {
        AXIS2_FREE((*env)->allocator, listener_manager_impl->listener_manager.ops);
        listener_manager_impl->listener_manager.ops = NULL;
    }
    
    if (listener_manager_impl->listener_map)
    {
        axis2_hash_free(listener_manager_impl->listener_map, env);
        listener_manager_impl->listener_map = NULL;
    }
    
    AXIS2_FREE((*env)->allocator, listener_manager_impl);
    listener_manager_impl = NULL;
    
    return AXIS2_SUCCESS;
}

axis2_conf_ctx_t *AXIS2_CALL
axis2_listener_manager_get_conf_ctx(axis2_listener_manager_t *listener_manager,
                                    axis2_env_t **env)
{
    AXIS2_ENV_CHECK(env, NULL);
    return AXIS2_INTF_TO_IMPL(listener_manager)->conf_ctx;
}