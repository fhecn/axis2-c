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
 
 #ifndef _AXIS2_SOAP_FAULT_CODE_H
 #define _AXIS2_SOAP_FAULT_CODE_H
 
 
 /** @defgroup axis2_soap AXIOM (Axis Object Model)
  * @ingroup axis2
  * @{
  */
  
/** @} */

#include <axis2_soap_fault_code.h>

#ifdef __cplusplus
extern "C"
{
#endif
  
/**
 * @defgroup axis2_soap_fault_code Soap fault code
 * @ingroup axis2_soap 
 * @{
 */

axis2_status_t AXIS2_CALL 
axis2_soap_fault_code_set_value(axis2_soap_fault_code_t *fault_code,
                                axis2_env_t **env,
                                struct axis2_soap_fault_value *fault_val);
axis2_status_t AXIS2_CALL 
axis2_soap_fault_code_set_sub_code(axis2_soap_fault_code_t *fault_code,
                                  axis2_env_t **env,
                                  struct axis2_soap_fault_sub_code *fault_subcode);
axis2_status_t AXIS2_CALL 
axis2_soap_fault_code_set_base_node(axis2_soap_fault_code_t *fault_code,
                                    axis2_env_t **env,
                                    axis2_om_node_t *node);
axis2_status_t AXIS2_CALL
axis2_soap_fault_code_set_builder(axis2_soap_fault_code_t *fault_code,
                                  axis2_env_t **env,
                                  struct axis2_soap_builder *soap_builder);
    
AXIS2_DECLARE(axis2_soap_fault_code_t *)
axis2_soap_fault_code_create(axis2_env_t **env);      
    
/** @} */
    
#ifdef __cplusplus
}
#endif

#endif /** _AXIS2_SOAP_FAULT_CODE_H  */