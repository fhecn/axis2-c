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

#ifndef WODEN_BINDING_MSG_REF_ELEMENT_H
#define WODEN_BINDING_MSG_REF_ELEMENT_H

/**
 * @file woden_binding_msg_ref_element.h
 * @brief Axis2 Binding Msg Reference Element Binding
 * This interface represents the &lt;input&gt; and &lt;output&gt; 
 * child elements of a WSDL binding &lt;operation&gt;. 
 */

#include <axis2_allocator.h>
#include <axis2_env.h>
#include <axis2_error.h>
#include <axis2_string.h>
#include <axis2_utils.h>
#include <axis2_hash.h>
#include <axis2_qname.h>
#include <axis2_uri.h>
#include <axis2_array_list.h>
#include <woden.h>
#include <woden_documentable_element.h>
#include <woden_configurable_element.h>
#include <woden_nested_element.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct woden_binding_msg_ref_element woden_binding_msg_ref_element_t;
typedef struct woden_binding_msg_ref_element_ops woden_binding_msg_ref_element_ops_t;
typedef union woden_binding_msg_ref_element_base woden_binding_msg_ref_element_base_t;

/** @defgroup woden_binding_msg_ref_element Binding Msg Reference Element
  * @ingroup axis2_binding
  * @{
  */

struct woden_binding_msg_ref_element_ops
{
   /** 
     * Deallocate memory
     * @return status code
     */
    axis2_status_t (AXIS2_CALL *
    free) (
            void *binding_msg_ref_element,
            const axis2_env_t *env);
 
    woden_obj_types_t (AXIS2_CALL *
    type) (
            void *binding_msg_ref_element,
            const axis2_env_t *env);
    
    axis2_status_t (AXIS2_CALL *
    set_msg_label) (
            void *iface_fault_ele,
            const axis2_env_t *env,
            void *msg_label);

    void *(AXIS2_CALL *
    get_msg_label) (
            void *iface_fault_ele,
            const axis2_env_t *env);
 
    axis2_status_t (AXIS2_CALL *
    set_direction) (
            void *iface_fault_ele,
            const axis2_env_t *env,
            void *dir);

    void *(AXIS2_CALL *
    get_direction) (
            void *iface_fault_ele,
            const axis2_env_t *env);
    

};

union woden_binding_msg_ref_element_base
{
    woden_documentable_element_t documentable_element;
    woden_configurable_element_t configurable_element;
    woden_nested_element_t nested_element;
};

struct woden_binding_msg_ref_element
{
    woden_binding_msg_ref_element_base_t base;
    woden_binding_msg_ref_element_ops_t *ops;
};

AXIS2_EXTERN woden_binding_msg_ref_element_t * AXIS2_CALL
woden_binding_msg_ref_element_create(
        const axis2_env_t *env);

/************************Woden C Internal Methods******************************/
AXIS2_EXTERN axis2_status_t AXIS2_CALL
woden_binding_msg_ref_element_resolve_methods(
        woden_binding_msg_ref_element_t *binding_msg_ref_element,
        const axis2_env_t *env,
        axis2_hash_t *methods);
/************************End of Woden C Internal Methods***********************/

#define WODEN_BINDING_MSG_REF_ELEMENT_FREE(binding_msg_ref_element, env) \
      (((woden_binding_msg_ref_element_t *) binding_msg_ref_element)->ops->\
         free (binding_msg_ref_element, env))

#define WODEN_BINDING_MSG_REF_ELEMENT_TYPE(binding_msg_ref_element, env) \
      (((woden_binding_msg_ref_element_t *) binding_msg_ref_element)->ops->\
         type (binding_msg_ref_element, env))

#define WODEN_BINDING_MSG_REF_ELEMENT_SET_MSG_LABEL(binding_msg_ref_element, env, msg_label) \
      (((woden_binding_msg_ref_element_t *) binding_msg_ref_element)->ops->\
         set_msg_label (binding_msg_ref_element, env, msg_label))

#define WODEN_BINDING_MSG_REF_ELEMENT_GET_MSG_LABEL(binding_msg_ref_element, env) \
      (((woden_binding_msg_ref_element_t *) binding_msg_ref_element)->ops->\
        get_msg_label  (binding_msg_ref_element, env))

#define WODEN_BINDING_MSG_REF_ELEMENT_SET_DIRECTION(binding_msg_ref_element, env, dir) \
      (((woden_binding_msg_ref_element_t *) binding_msg_ref_element)->ops->\
         set_direction (binding_msg_ref_element, env, dir))

#define WODEN_BINDING_MSG_REF_ELEMENT_GET_DIRECTION(binding_msg_ref_element, env) \
      (((woden_binding_msg_ref_element_t *) binding_msg_ref_element)->ops->\
         get_direction (binding_msg_ref_element, env))




/** @} */
#ifdef __cplusplus
}
#endif
#endif /* WODEN_BINDING_MSG_REF_ELEMENT_H */
