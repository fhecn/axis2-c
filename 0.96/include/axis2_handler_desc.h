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

#ifndef AXIS2_HANDLER_DESC_H
#define AXIS2_HANDLER_DESC_H

/**
 * @defgroup axis2_handler_desc handler description
 * @ingroup axis2_desc
 * handler description captures information on a handler. Each handler in the 
 * system has an associated handler description. Deployment engine would create 
 * handler descriptions based on configuration information. When handlers are 
 * loaded from shared libraries, the information captured in handler description
 * would be used.
 * @{
 */

/**
 * @file axis2_handler_desc.h
 */

#include <axis2_utils_defines.h>
#include <axis2_qname.h>
#include <axis2_param.h>
#include <axis2_param_container.h>
#include <axis2_phase_rule.h>
#include <axis2_handler.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /** Type name for struct axis2_handler_desc */
    typedef struct axis2_handler_desc axis2_handler_desc_t;
    /** Type name for struct axis2_handler_desc_ops  */
    typedef struct axis2_handler_desc_ops axis2_handler_desc_ops_t;

    /**
     * handler description ops struct.
     * Encapsulator struct for ops of axis2_handler_desc.
     */
    struct axis2_handler_desc_ops
    {
        /**
         * Gets QName.
         * @param handler_desc pointer to handler description
         * @param env pointer to environment struct
         * @return pointer to QName, returns a reference, not a cloned copy
         */
        const axis2_qname_t *(AXIS2_CALL *
                get_qname)(
                    const axis2_handler_desc_t *handler_desc,
                    const axis2_env_t *env);

        /**
         * Sets QName.
         * @param handler_desc pointer to handler description
         * @param env pointer to environment struct
         * @param qname pointer to QName, handler description creates a clone
         * of QName
         * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
         */
        axis2_status_t (AXIS2_CALL *
                set_qname)(
                    axis2_handler_desc_t *handler_desc,
                    const axis2_env_t *env,
                    const axis2_qname_t *qname);

        /**
         * Gets phase rules.
         * @param handler_desc pointer to handler description
         * @param env pointer to environment struct
         * @return pointer to phase rule struct containing phase rules
         */
        axis2_phase_rule_t *(AXIS2_CALL *
                get_rules)(
                    const axis2_handler_desc_t *handler_desc,
                    const axis2_env_t *env);

        /**
         * Sets phase rules.
         * @param handler_desc pointer to handler description
         * @param env pointer to environment struct
         * @param phase_rule pointer to phase rule struct, handler description
         * assumes ownership of the struct
         * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
         */
        axis2_status_t (AXIS2_CALL *
                set_rules)(
                    axis2_handler_desc_t *handler_desc,
                    const axis2_env_t *env,
                    axis2_phase_rule_t *phase_rule);

        /**
         * Gets named parameter.
         * @param handler_desc pointer to handler description
         * @param env pointer to environment struct
         * @param name parameter name string 
         * @return pointer to parameter if found, else NULL. Return a reference
         * not a cloned copy
         */
        axis2_param_t *(AXIS2_CALL *
                get_param)(
                    const axis2_handler_desc_t *handler_desc,
                    const axis2_env_t *env,
                    const axis2_char_t *name);

        /**
         * Adds given parameter to the parameter list.
         * @param handler_desc pointer to handler description
         * @param env pointer to environment struct
         * @param param pointer to param
         * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
         */
        axis2_status_t (AXIS2_CALL *
                add_param)(
                    axis2_handler_desc_t *handler_desc,
                    const axis2_env_t *env,
                    axis2_param_t *param);

        /**
         * Gets all parameters stored within handler description.
         * @param handler_desc pointer to handler description
         * @param env pointer to environment struct
         * @return pointer to array list containing parameters, returns a 
         * reference, not a cloned copy
         */
        axis2_array_list_t *(AXIS2_CALL *
                get_all_params)(
                    const axis2_handler_desc_t *handler_desc,
                    const axis2_env_t *env);

        /**
         * Checks if the named parameter is locked at any level
         * @param handler_desc pointer to handler description
         * @param env pointer to environment struct
         * @param param_name parameter name string 
         * @return AXIS2_TRUE if the parameter is locked, else AXIS2_FALSE
         */
        axis2_bool_t (AXIS2_CALL *
                is_param_locked)(
                    const axis2_handler_desc_t *handler_desc,
                    const axis2_env_t *env, 
                    const axis2_char_t *param_name);

        /**
         * Gets the handler associated with the handler description.
         * @param handler_desc pointer to handler description
         * @param env pointer to environment struct
         * @return pointer to handler, returns a reference, not a cloned copy
         */
        axis2_handler_t *(AXIS2_CALL *
                get_handler)(
                    const axis2_handler_desc_t *handler_desc,
                    const axis2_env_t *env);

        /**
         * Sets the handler associated with the handler description.
         * @param handler_desc pointer to handler description
         * @param env pointer to environment struct
         * @param handler pointer to handler, handler description assumes
         * the ownership of the handler
         * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
         */
        axis2_status_t (AXIS2_CALL *
                set_handler)(
                    axis2_handler_desc_t *handler_desc,
                    const axis2_env_t *env,
                    axis2_handler_t *handler);

        /**
         * Gets the class name. Class name is the name of the shared library 
         * file that contains the implementation of the handler.
         * @param handler_desc pointer to handler description
         * @param env pointer to environment struct
         * @return class name string
         */
        const axis2_char_t *(AXIS2_CALL *
                get_class_name)(
                    const axis2_handler_desc_t *handler_desc,
                    const axis2_env_t *env);

        /**
         * Sets the class name. Class name is the name of the shared library 
         * file that contains the implementation of the handler.
         * @param handler_desc pointer to handler description
         * @param env pointer to environment struct
         * @param class_name class name string
         * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
         */
        axis2_status_t (AXIS2_CALL *
                set_class_name)(
                    axis2_handler_desc_t *handler_desc,
                    const axis2_env_t *env,
                    const axis2_char_t *class_name);

        /**
         * Gets the parent. Parent of handler description is of type parameter
         * container.
         * @param handler_desc pointer to handler description
         * @param env pointer to environment struct
         * @return pointer to parent parameter container, returns a reference,
         * not a cloned copy
         */
        axis2_param_container_t *(AXIS2_CALL *
                get_parent)(
                    const axis2_handler_desc_t *handler_desc,
                    const axis2_env_t *env);

        /**
         * Gets the parent. Parent of handler description is of type parameter
         * container.
         * @param handler_desc pointer to handler description
         * @param env pointer to environment struct
         * @param parent pointer to parent parameter container struct, handler
         * description assumes ownership of struct
         * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
         */
        axis2_status_t (AXIS2_CALL *
                set_parent)(
                    axis2_handler_desc_t *handler_desc,
                    const axis2_env_t *env,
                    axis2_param_container_t *parent);

        /**
         * Frees handler description.
         * @param handler_desc pointer to handler description
         * @param env pointer to environment struct
         * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
         */
        axis2_status_t (AXIS2_CALL *
                free)(
                    axis2_handler_desc_t *handler_desc,
                    const axis2_env_t *env);

    };

    /**
     * handler description struct
     */
    struct axis2_handler_desc
    {
        /** handler description related ops */
        axis2_handler_desc_ops_t *ops;

        /** parameter container */
        axis2_param_container_t *param_container;

    };


    /**
     * Creates handler description struct instance.
     * @param env pointer to env pointer to environment struct
     * @param qname pointer to QName of handler, can be NULL, create function 
     * clones this    
     * @return pointer to newly created handler description struct
     */
    AXIS2_EXTERN axis2_handler_desc_t *AXIS2_CALL
    axis2_handler_desc_create_with_qname(
        const axis2_env_t *env, 
        const axis2_qname_t *qname);

/** Gets handler associated with handler description.
    @sa axis2_handler_desc_ops#get_handler */
#define AXIS2_HANDLER_DESC_GET_HANDLER(handler_desc, env) \
        ((handler_desc)->ops->get_handler(handler_desc, env))

/** Sets handler associated with handler description.
    @sa axis2_handler_desc_ops#set_handler */
#define AXIS2_HANDLER_DESC_SET_HANDLER(handler_desc, env, handler) \
        ((handler_desc)->ops->set_handler(handler_desc, env, handler))

/** Gets rules.
    @sa axis2_handler_desc_ops#get_rules */
#define AXIS2_HANDLER_DESC_GET_RULES(handler_desc, env) \
        ((handler_desc)->ops->get_rules(handler_desc, env))

/** Sets rules.
    @sa axis2_handler_desc_ops#set_rules */
#define AXIS2_HANDLER_DESC_SET_RULES(handler_desc, env, rules) \
        ((handler_desc)->ops->set_rules(handler_desc, env, rules))

/** Gets QName.
    @sa axis2_handler_desc_ops#get_qname */
#define AXIS2_HANDLER_DESC_GET_QNAME(handler_desc, env) \
        ((handler_desc)->ops->get_qname(handler_desc, env))

/** Sets QName.
    @sa axis2_handler_desc_ops#set_qname */
#define AXIS2_HANDLER_DESC_SET_QNAME(handler_desc, env, name) \
        ((handler_desc)->ops->set_qname(handler_desc, env, name))

/** Gets parameter with given name.
    @sa axis2_handler_desc_ops#get_param */
#define AXIS2_HANDLER_DESC_GET_PARAM(handler_desc, env, name) \
        ((handler_desc)->ops->get_param(handler_desc, env, name))

/** Adds parameter to parameter list.
    @sa axis2_handler_desc_ops#add_param */
#define AXIS2_HANDLER_DESC_ADD_PARAM(handler_desc, env, param) \
        ((handler_desc)->ops->add_param(handler_desc, env, param))

/** Gets class name of handler.
    @sa axis2_handler_desc_ops#get_class_name */
#define AXIS2_HANDLER_DESC_GET_CLASS_NAME(handler_desc, env) \
        ((handler_desc)->ops->get_class_name(handler_desc, env))

/** Sets class name of handler.
    @sa axis2_handler_desc_ops#set_class_name */
#define AXIS2_HANDLER_DESC_SET_CLASS_NAME(handler_desc, env, class_name) \
        ((handler_desc)->ops->set_class_name(handler_desc, env, class_name))

/** Gets parent.
    @sa axis2_handler_desc_ops#get_parent */
#define AXIS2_HANDLER_DESC_GET_PARENT(handler_desc, env) \
        ((handler_desc)->ops->get_parent(handler_desc, env))

/** Sets parent.
    @sa axis2_handler_desc_ops#set_parent */
#define AXIS2_HANDLER_DESC_SET_PARENT(handler_desc, env, parent) \
        ((handler_desc)->ops->set_parent(handler_desc, env, parent))

/** Frees handler description.
    @sa axis2_handler_desc_ops#free */
#define AXIS2_HANDLER_DESC_FREE(handler_desc, env) \
        ((handler_desc)->ops->free(handler_desc, env))

/** @} */

#ifdef __cplusplus
}
#endif

#endif    /* AXIS2_HANDLER_DESC_H */