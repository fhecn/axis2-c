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

#include <woden_nested_element.h>

axis2_status_t AXIS2_CALL
woden_nested_element_resolve_methods(
        woden_nested_element_t *nested_element,
        const axis2_env_t *env,
        axis2_hash_t *methods)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, methods, AXIS2_FAILURE);
    
    nested_element->ops->free = axis2_hash_get(methods, "free", 
            AXIS2_HASH_KEY_STRING);
    nested_element->ops->type = axis2_hash_get(methods, "type", 
            AXIS2_HASH_KEY_STRING);
    nested_element->ops->set_parent_element = axis2_hash_get(methods,
            "set_parent_element", AXIS2_HASH_KEY_STRING);
    nested_element->ops->get_parent_element = axis2_hash_get(methods,
            "get_parent_element", AXIS2_HASH_KEY_STRING);

    return AXIS2_SUCCESS;    
}
