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

#ifndef AXIS2_WODEN_NESTED_ELEMENT_H
#define AXIS2_WODEN_NESTED_ELEMENT_H

/**
 * @file axis2_woden_nested_element.h
 * @brief Axis2 Nested Element Interface
 * Elements which are nested within a 'top-level' WSDL element will
 * extend this interface. These are &lt;feature&gt;, &lt;property&gt;
 * and the child elements of &lt;interface&gt;, &lt;binding&gt; and
 * &lt;service&gt;.  
 * <p>
 * The elements which are not nested are &lt;description&gt;, 
 * &lt;import&gt;, &lt;include&gt;, &lt;types&gt;, &lt;interface&gt;, 
 * &lt;binding&gt; and &lt;service&gt;.
 * 
 *
 */

#include <axis2_allocator.h>
#include <axis2_env.h>
#include <axis2_error.h>
#include <axis2_string.h>
#include <axis2_const.h>
#include <axis2_hash.h>
#include <axis2_qname.h>
#include <woden/axis2_woden.h>
#include <woden/wsdl20/xml/axis2_woden_wsdl_element.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct axis2_woden_nested_element axis2_woden_nested_element_t;
typedef struct axis2_woden_nested_element_ops axis2_woden_nested_element_ops_t;
struct axis2_woden_wsdl_element;

/** @defgroup axis2_woden_nested_element Nested Element
  * @ingroup axis2_wsdl
  * @{
  */

struct axis2_woden_nested_element_ops
{
	/** 
     * Deallocate memory
     * @return status code
     */
    axis2_status_t (AXIS2_CALL *
    free) (
            void *doc_el,
            axis2_env_t **env);
    
    axis2_status_t (AXIS2_CALL *
    to_nested_element_free) (
            void *doc_el,
            axis2_env_t **env);
    
    axis2_woden_obj_types_t (AXIS2_CALL *
    type) (
            void *doc_el,
            axis2_env_t **env);
    
    axis2_status_t (AXIS2_CALL *
    set_parent_element) (
            void *doc_el,
            axis2_env_t **env,
            struct axis2_woden_wsdl_element *parent);

    void *(AXIS2_CALL *
    get_parent_element) (
            void *doc_el,
            axis2_env_t **env);

};

struct axis2_woden_nested_element
{
    axis2_woden_wsdl_element_t wsdl_element;
    axis2_woden_nested_element_ops_t *ops;
};

/************************Woden C Internal Methods*****************************/
axis2_status_t AXIS2_CALL
axis2_woden_nested_element_resolve_methods(
        axis2_woden_nested_element_t *nested_element,
        axis2_env_t **env,
        axis2_hash_t *methods);
/************************End of Woden C Internal Methods***********************/

#define AXIS2_WODEN_NESTED_ELEMENT_FREE(doc_el, env) \
		(((axis2_woden_nested_element_t *) doc_el)->ops->\
         free (doc_el, env))

#define AXIS2_WODEN_NESTED_ELEMENT_TO_NESTED_ELEMENT_FREE(doc_el, env) \
		(((axis2_woden_nested_element_t *) doc_el)->ops->\
         to_nested_element_free (doc_el, env))

#define AXIS2_WODEN_NESTED_ELEMENT_TYPE(doc_el, env) \
		(((axis2_woden_nested_element_t *) doc_el)->ops->\
         type (doc_el, env))

#define AXIS2_WODEN_NESTED_ELEMENT_SET_PARENT_ELEMENT(doc_el, env, parent) \
		(((axis2_woden_nested_element_t *) doc_el)->ops->\
         set_content(doc_el, env, parent))

#define AXIS2_WODEN_NESTED_ELEMENT_GET_PARENT_ELEMENT(doc_el, env) \
		(((axis2_woden_nested_element_t *) doc_el)->ops->\
         get_content(doc_el, env))


/** @} */
#ifdef __cplusplus
}
#endif
#endif /* AXIS2_WODEN_NESTED_ELEMENT_H */