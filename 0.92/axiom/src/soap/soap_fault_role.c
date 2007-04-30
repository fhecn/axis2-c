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
 
 #include <axiom_soap_fault_role.h>
 #include "_axiom_soap_fault.h"
 #include <axiom_soap_builder.h>
 #include <axiom_element.h>
 
 /***************************** impl struct **********************************/
 
 typedef struct axiom_soap_fault_role_impl_t
 {
    axiom_soap_fault_role_t fault_role;
    
    axiom_node_t *om_ele_node;
    
 }axiom_soap_fault_role_impl_t;

/**************************** Macro *******************************************/

#define AXIS2_INTF_TO_IMPL(role) ((axiom_soap_fault_role_impl_t*)role)

/**************************** function prototypes *****************************/

axis2_status_t AXIS2_CALL 
axiom_soap_fault_role_free(axiom_soap_fault_role_t *fault_role,
                              const axis2_env_t *env);

axis2_status_t AXIS2_CALL 
axiom_soap_fault_role_set_role_value
                            (axiom_soap_fault_role_t *fault_role,
                             const axis2_env_t *env,
                             axis2_char_t* uri);
                                
axis2_char_t* AXIS2_CALL 
axiom_soap_fault_role_get_role_value
                            (axiom_soap_fault_role_t *fault_role,
                             const axis2_env_t *env);
                                
axiom_node_t* AXIS2_CALL
axiom_soap_fault_role_get_base_node
                        (axiom_soap_fault_role_t *fault_role,
                         const axis2_env_t *env);
                            
/*********************** end function prototypes ******************************/


AXIS2_EXTERN axiom_soap_fault_role_t * AXIS2_CALL
axiom_soap_fault_role_create(const axis2_env_t *env)
{
    axiom_soap_fault_role_impl_t *fault_role_impl = NULL;
    
    AXIS2_ENV_CHECK(env, NULL);
    
    fault_role_impl = (axiom_soap_fault_role_impl_t*) AXIS2_MALLOC(
                            env->allocator,
                            sizeof(axiom_soap_fault_role_impl_t));
    if(!fault_role_impl)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    
    fault_role_impl->fault_role.ops = NULL;
    fault_role_impl->om_ele_node = NULL;
    
    fault_role_impl->fault_role.ops = 
            (axiom_soap_fault_role_ops_t*)AXIS2_MALLOC(env->allocator,
                sizeof(axiom_soap_fault_role_ops_t));
                
    if(!(fault_role_impl->fault_role.ops))
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        AXIS2_FREE(env->allocator, fault_role_impl);
        return NULL;
    }                                                                  
    
    fault_role_impl->fault_role.ops->free_fn = 
        axiom_soap_fault_role_free;
        
    fault_role_impl->fault_role.ops->get_role_value =
        axiom_soap_fault_role_get_role_value;
        
    fault_role_impl->fault_role.ops->set_role_value =
        axiom_soap_fault_role_set_role_value;
        
    fault_role_impl->fault_role.ops->get_base_node =
        axiom_soap_fault_role_get_base_node;
        
  return  &(fault_role_impl->fault_role);  
}

AXIS2_EXTERN axiom_soap_fault_role_t * AXIS2_CALL
axiom_soap_fault_role_create_with_parent(const axis2_env_t *env,
                            axiom_soap_fault_t *fault)
{
    axiom_soap_fault_role_impl_t *fault_role_impl = NULL;
    axiom_soap_fault_role_t *fault_role = NULL;
    int soap_version = -1;
    
    axiom_element_t *this_ele = NULL;
    axiom_node_t *this_node = NULL;
    
    axiom_node_t *parent_node = NULL;
    axiom_element_t *parent_ele = NULL;
    
    axiom_namespace_t *parent_ns = NULL;
    
    AXIS2_ENV_CHECK(env, NULL);
    AXIS2_PARAM_CHECK(env->error, fault, NULL);
    
    fault_role = axiom_soap_fault_role_create(env);
    if(!fault_role)
        return NULL;
        
    fault_role_impl = AXIS2_INTF_TO_IMPL(fault_role);
    
    parent_node = AXIOM_SOAP_FAULT_GET_BASE_NODE(fault, env);
    if(!parent_node)
    {
        AXIOM_SOAP_FAULT_ROLE_FREE(fault_role, env);
        return NULL;
    }
    parent_ele  = (axiom_element_t *)AXIOM_NODE_GET_DATA_ELEMENT(
                        parent_node, env);
   
    if(!parent_ele)
    {
        AXIOM_SOAP_FAULT_ROLE_FREE(fault_role, env);
        return NULL;
    }
    soap_version = axiom_soap_fault_get_soap_version(fault, env);
    if(soap_version == AXIOM_SOAP12)
    {
        parent_ns = AXIOM_ELEMENT_GET_NAMESPACE(parent_ele, env, parent_node);
    }       
    this_ele = axiom_element_create(env, 
                    parent_node, AXIOM_SOAP12_SOAP_FAULT_ROLE_LOCAL_NAME,
                    parent_ns, &this_node);
    if(!this_ele)
    {
        AXIOM_SOAP_FAULT_ROLE_FREE(fault_role, env);
        return NULL;
    }
                                       
    fault_role_impl->om_ele_node = this_node;  
    
    axiom_soap_fault_set_role (fault, env, fault_role);

    return  &(fault_role_impl->fault_role);            
}


axis2_status_t AXIS2_CALL 
axiom_soap_fault_role_free(axiom_soap_fault_role_t *fault_role,
                              const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    if(NULL != fault_role->ops)
    {
        AXIS2_FREE(env->allocator, fault_role->ops);
        fault_role->ops = NULL;
    }    
    AXIS2_FREE(env->allocator, AXIS2_INTF_TO_IMPL(fault_role));        
    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL 
axiom_soap_fault_role_set_role_value
                            (axiom_soap_fault_role_t *fault_role,
                             const axis2_env_t *env,
                             axis2_char_t* uri)
{
    axiom_soap_fault_role_impl_t *fault_role_impl = NULL;
    axiom_element_t *role_ele = NULL;
    
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, uri, AXIS2_FAILURE);
    fault_role_impl = AXIS2_INTF_TO_IMPL(fault_role);
    
    if(!fault_role_impl->om_ele_node)
        return AXIS2_FAILURE;
        
    role_ele = (axiom_element_t*)AXIOM_NODE_GET_DATA_ELEMENT
                    (fault_role_impl->om_ele_node, env);
    
    if(NULL != role_ele)
    {
        return AXIOM_ELEMENT_SET_TEXT(role_ele,  env, uri,
                                fault_role_impl->om_ele_node);
    }
    return AXIS2_FAILURE;    
}
                                
axis2_char_t* AXIS2_CALL 
axiom_soap_fault_role_get_role_value
                            (axiom_soap_fault_role_t *fault_role,
                             const axis2_env_t *env)
{
    axiom_soap_fault_role_impl_t *fault_role_impl = NULL;
    axiom_element_t *role_ele = NULL;
    
    AXIS2_ENV_CHECK(env, NULL);
    fault_role_impl = AXIS2_INTF_TO_IMPL(fault_role);
    if(!fault_role_impl->om_ele_node)
        return NULL;
    
    role_ele = (axiom_element_t *)AXIOM_NODE_GET_DATA_ELEMENT
                    (fault_role_impl->om_ele_node, env);
                    
    if(NULL != role_ele)   
    {
        return AXIOM_ELEMENT_GET_TEXT(role_ele,  env,
                                         fault_role_impl->om_ele_node); 
    }
    return NULL;
}
                                
axis2_status_t AXIS2_CALL 
axiom_soap_fault_role_set_base_node
                            (axiom_soap_fault_role_t *fault_role,
                             const axis2_env_t *env,
                             axiom_node_t *node)
{
   axiom_soap_fault_role_impl_t *fault_role_impl = NULL;
   AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
   AXIS2_PARAM_CHECK(env->error, node, AXIS2_FAILURE);
   fault_role_impl = AXIS2_INTF_TO_IMPL(fault_role);
   
   if(AXIOM_NODE_GET_NODE_TYPE(node, env) != AXIOM_ELEMENT)
   {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_INVALID_BASE_TYPE, AXIS2_FAILURE);
        return AXIS2_FAILURE;
   }
   fault_role_impl->om_ele_node = node;
   return AXIS2_SUCCESS;
}

axiom_node_t* AXIS2_CALL
axiom_soap_fault_role_get_base_node
                        (axiom_soap_fault_role_t *fault_role,
                         const axis2_env_t *env)
{
     AXIS2_ENV_CHECK(env, NULL);
     return AXIS2_INTF_TO_IMPL(fault_role)->om_ele_node;
}