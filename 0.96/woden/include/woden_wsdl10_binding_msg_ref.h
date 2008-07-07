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

#ifndef WODEN_WSDL10_BINDING_MSG_REF_H
#define WODEN_WSDL10_BINDING_MSG_REF_H

/**
 * @file woden_wsdl10_binding_msg_ref.h
 * @brief Axis2 Binding Message Reference Binding Message Reference
 * This class represents the Binding Message Reference component of the 
 * WSDL 2.0 Component model and the &lt;input&gt; and &lt;output&gt; 
 * child elements of a WSDL binding &lt;operation&gt;. 
 * 
 */

#include <woden.h>
#include <woden_wsdl10_binding_msg_ref_element.h>
#include <woden_nested_configurable.h>
#include <axis2_qname.h>

/** @defgroup woden_wsdl10_binding_msg_ref Binding Message Reference
  * @ingroup woden
  * @{
  */

typedef union woden_wsdl10_binding_msg_ref_base woden_wsdl10_binding_msg_ref_base_t;
typedef struct woden_wsdl10_binding_msg_ref woden_wsdl10_binding_msg_ref_t;
typedef struct woden_wsdl10_binding_msg_ref_ops woden_wsdl10_binding_msg_ref_ops_t;


#ifdef __cplusplus
extern "C"
{
#endif

struct woden_wsdl10_binding_msg_ref_ops
{
   /** 
     * Deallocate memory
     * @return status code
     */
    axis2_status_t (AXIS2_CALL *
    free) (void *binding_msg_ref,
            const axis2_env_t *env);

    axis2_status_t (AXIS2_CALL *
    to_binding_msg_ref_free) (void *binding_msg_ref,
            const axis2_env_t *env);
    
    axis2_hash_t *(AXIS2_CALL *
    super_objs) (void *binding_msg_ref,
            const axis2_env_t *env);

    woden_obj_types_t (AXIS2_CALL *
    type) (void *binding_msg_ref,
            const axis2_env_t *env);
    /**
     * @return the base implementation class
     */
    struct woden_nested_configurable *(AXIS2_CALL *
    get_base_impl) (
            void *binding_msg_ref,
            const axis2_env_t *env);

    void *(AXIS2_CALL *
    get_interface_msg_ref) (
            void *binding_msg_ref,
            const axis2_env_t *env);

    void *(AXIS2_CALL *
    to_element)  (
            void *binding_msg_ref,
            const axis2_env_t *env);

    axis2_status_t (AXIS2_CALL *
    set_interface_msg_ref_element) (
            void *binding_msg_ref,
            const axis2_env_t *env,
            void *int_msg_ref);

};

union woden_wsdl10_binding_msg_ref_base
{
    woden_nested_configurable_t nested_configurable;
    woden_wsdl10_binding_msg_ref_element_t binding_msg_ref_element;
};

struct woden_wsdl10_binding_msg_ref
{
    woden_wsdl10_binding_msg_ref_base_t base;
    woden_wsdl10_binding_msg_ref_ops_t *ops;
};

AXIS2_EXTERN woden_wsdl10_binding_msg_ref_t * AXIS2_CALL
woden_wsdl10_binding_msg_ref_create(
        const axis2_env_t *env);


/***************************Woden C Internal Methods***************************/
AXIS2_EXTERN woden_wsdl10_binding_msg_ref_t * AXIS2_CALL
woden_wsdl10_binding_msg_ref_to_binding_msg_ref_element(
        void *binding_msg_ref,
        const axis2_env_t *env);

AXIS2_EXTERN woden_wsdl10_binding_msg_ref_t * AXIS2_CALL
woden_wsdl10_binding_msg_ref_to_nested_configurable(
        void *binding_msg_ref,
        const axis2_env_t *env);

AXIS2_EXTERN woden_wsdl10_binding_msg_ref_t * AXIS2_CALL
woden_wsdl10_binding_msg_ref_to_configurable(
        void *binding_msg_ref,
        const axis2_env_t *env);

AXIS2_EXTERN woden_wsdl10_binding_msg_ref_t * AXIS2_CALL
woden_wsdl10_binding_msg_ref_to_wsdl_obj(
        void *binding_msg_ref,
        const axis2_env_t *env);

AXIS2_EXTERN woden_wsdl10_binding_msg_ref_t * AXIS2_CALL
woden_wsdl10_binding_msg_ref_to_nested_element(
        void *binding_msg_ref,
        const axis2_env_t *env);

AXIS2_EXTERN woden_wsdl10_binding_msg_ref_t * AXIS2_CALL
woden_wsdl10_binding_msg_ref_to_wsdl_component(
        void *binding_msg_ref,
        const axis2_env_t *env);

AXIS2_EXTERN woden_wsdl10_binding_msg_ref_t * AXIS2_CALL
woden_wsdl10_binding_msg_ref_to_configurable_element(
        void *binding_msg_ref,
        const axis2_env_t *env);

AXIS2_EXTERN woden_wsdl10_binding_msg_ref_t * AXIS2_CALL
woden_wsdl10_binding_msg_ref_to_documentable_element(
        void *binding_msg_ref,
        const axis2_env_t *env);

AXIS2_EXTERN woden_wsdl10_binding_msg_ref_t * AXIS2_CALL
woden_wsdl10_binding_msg_ref_to_documentable(
        void *binding_msg_ref,
        const axis2_env_t *env);

AXIS2_EXTERN woden_wsdl10_binding_msg_ref_t * AXIS2_CALL
woden_wsdl10_binding_msg_ref_to_attr_extensible(
        void *binding_msg_ref,
        const axis2_env_t *env);

AXIS2_EXTERN woden_wsdl10_binding_msg_ref_t * AXIS2_CALL
woden_wsdl10_binding_msg_ref_to_element_extensible(
        void *binding_msg_ref,
        const axis2_env_t *env);

AXIS2_EXTERN axis2_status_t AXIS2_CALL
woden_wsdl10_binding_msg_ref_resolve_methods(
        woden_wsdl10_binding_msg_ref_t *binding_msg_ref,
        const axis2_env_t *env,
        woden_wsdl10_binding_msg_ref_t *binding_msg_ref_impl,
        axis2_hash_t *methods);
/************************End of Woden C Internal Methods***********************/

#define WODEN_WSDL10_BINDING_MSG_REF_FREE(binding_msg_ref, env) \
      (((woden_wsdl10_binding_msg_ref_t *) binding_msg_ref)->ops->free(binding_msg_ref, env))

#define WODEN_WSDL10_BINDING_MSG_REF_TO_BINDING_MSG_REF_FREE(binding_msg_ref, env) \
      (((woden_wsdl10_binding_msg_ref_t *) binding_msg_ref)->ops->to_binding_msg_ref_free(binding_msg_ref, env))

#define WODEN_WSDL10_BINDING_MSG_REF_SUPER_OBJS(binding_msg_ref, env) \
      (((woden_wsdl10_binding_msg_ref_t *) binding_msg_ref)->ops->super_objs(binding_msg_ref, env))

#define WODEN_WSDL10_BINDING_MSG_REF_TYPE(binding_msg_ref, env) \
      (((woden_wsdl10_binding_msg_ref_t *) binding_msg_ref)->ops->type(binding_msg_ref, env))

#define WODEN_WSDL10_BINDING_MSG_REF_GET_BASE_IMPL(binding_msg_ref, env) \
      (((woden_wsdl10_binding_msg_ref_t *) binding_msg_ref)->ops->get_base_impl(binding_msg_ref, env))

#define WODEN_WSDL10_BINDING_MSG_REF_GET_INTERFACE_MSG_REF(binding_msg_ref, env) \
      (((woden_wsdl10_binding_msg_ref_t *) binding_msg_ref)->ops->\
         get_interface_msg_ref(binding_msg_ref, env))

#define WODEN_WSDL10_BINDING_MSG_REF_TO_ELEMENT(binding_msg_ref, env) \
      (((woden_wsdl10_binding_msg_ref_t *) binding_msg_ref)->ops->\
         to_element(binding_msg_ref, env))

#define WODEN_WSDL10_BINDING_MSG_REF_SET_INTERFACE_MSG_REF_ELEMENT(binding_msg_ref, env, int_msg_ref) \
      (((woden_wsdl10_binding_msg_ref_t *) binding_msg_ref)->ops->\
         set_interface_msg_ref_element(binding_msg_ref, env, int_msg_ref))

/** @} */
#ifdef __cplusplus
}
#endif
#endif /* WODEN_WSDL10_BINDING_MSG_REF_H */