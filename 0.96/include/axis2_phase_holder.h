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

#ifndef AXIS2_PHASE_HOLDER_H
#define AXIS2_PHASE_HOLDER_H

/** 
 * @defgroup axis2_phase_holder phase holder
 * @ingroup axis2_phase_resolver
 * phase holder is used by phase resolver to hold information related to
 * phases and handlers within a phase. This struct hold the list of phases 
 * found in the services.xml and axis2.xml.
 * @{
 */

/**
 * @file axis2_phase_holder.h
 */

#include <axis2_const.h>
#include <axis2_error.h>
#include <axis2_defines.h>
#include <axis2_env.h>
#include <axis2_allocator.h>
#include <axis2_qname.h>
#include <axis2_array_list.h>
#include <axis2_handler_desc.h>
#include <axis2_phase.h>
#include <axis2_phase_rule.h>
#include <axis2_handler.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /** Type name for struct axis2_phase_holder */
    typedef struct axis2_phase_holder axis2_phase_holder_t;
    /** Type name for struct axis2_phase_holder_ops  */
    typedef struct axis2_phase_holder_ops axis2_phase_holder_ops_t;

    struct axis2_phase;
    struct axis2_handler_desc;
    struct axis2_handler;
    struct axis2_phase_rule;

    /**
     * phase holder ops struct.
     * Encapsulator struct for ops of axis2_phase_holder.
     */
    struct axis2_phase_holder_ops
    {
        /** 
         * Frees phase holder.
         * @param phase_holder pointer to phase holder
         * @param env pointer to environment struct
         * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
         */
        axis2_status_t (AXIS2_CALL *
                free)(
                    axis2_phase_holder_t *phase_holder,
                    const axis2_env_t *env);

        /**
         * Checks if the named phase exist.
         * @param phase_holder pointer to phase holder
         * @param env pointer to environment struct
         * @param phase_name phase name string
         * @return AXIS2_TRUE if the named phase exist, else AXIS2_FALSE
         */
        axis2_bool_t (AXIS2_CALL *
                is_phase_exist)(
                    axis2_phase_holder_t *phase_holder,
                    const axis2_env_t *env,
                    const axis2_char_t *phase_name);

        /**
         * Adds given handler to phase holder.
         * @param phase_holder pointer to phase holder
         * @param env pointer to environment struct
         * @para handler pointer to handler
         * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
         */
        axis2_status_t (AXIS2_CALL *
                add_handler)(
                    axis2_phase_holder_t *phase_holder,
                    const axis2_env_t *env,
                    struct axis2_handler_desc *handler);

        /**
         * Gets the named phase from phase array list.
         * @param phase_holder pointer to phase holder
         * @param env pointer to environment struct
         * @param phase_name pointer to phase name
         * @return pointer to named phase if it exists, else NULL. Returns a 
         * reference, not a cloned copy 
         */
        struct axis2_phase *(AXIS2_CALL *
                get_phase)(
                    const axis2_phase_holder_t *phase_holder,
                    const axis2_env_t *env,
                    const axis2_char_t *phase_name);

        /**
         * Builds the transport phase. This method loads the corresponding 
         * handlers and added them into correct phase. 
         * @param phase_holder pointer to phase holder
         * @param env pointer to environment struct
         * @param phase pointer to phase, phase holder does not assume the 
         * ownership the phase
         * @param handlers pointer to array list of handlers, phase holder does 
         * not assume the ownership of the list
         * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
         */
        axis2_status_t (AXIS2_CALL *
                build_transport_handler_chain)(
                    axis2_phase_holder_t *phase_holder,
                    const axis2_env_t *env,
                    struct axis2_phase *phase,
                    axis2_array_list_t *handlers);
    };

    /**
     * phase holder struct.
     */
    struct axis2_phase_holder
    {
        /** operations of phase holder struct */
        axis2_phase_holder_ops_t *ops;
    };

    /**
     * Creates phase holder struct.
     * @param env pointer to environment struct
     * @return pointer to newly created phase holder
     */
    AXIS2_EXTERN axis2_phase_holder_t *AXIS2_CALL
    axis2_phase_holder_create (
        const axis2_env_t *env);

    /**
     * Creates phase holder struct with given list of phases.
     * @param env pointer to environment struct
     * @param phases pointer to array list of phases
     * @return pointer to newly created phase holder
     */
    AXIS2_EXTERN axis2_phase_holder_t *AXIS2_CALL
    axis2_phase_holder_create_with_phases (
        const axis2_env_t *env,
        axis2_array_list_t *phases);

/** Frees phase holder.
    @sa axis2_phase_holder_ops#free */
#define AXIS2_PHASE_HOLDER_FREE(phase_holder, env) \
      ((phase_holder)->ops->free (phase_holder, env))

/** Checks of a named phase exist.
    @sa axis2_phase_holder_ops#is_phase_exist */
#define AXIS2_PHASE_HOLDER_IS_PHASE_EXIST(phase_holder, env, phase_name) \
      ((phase_holder)->ops->is_phase_exist (phase_holder, env, phase_name))

/** Adds handler.
    @sa axis2_phase_holder_ops#add_handler */
#define AXIS2_PHASE_HOLDER_ADD_HANDLER(phase_holder, env, handler) \
      ((phase_holder)->ops->add_handler (phase_holder, env, handler))

/** Gets named phase.
    @sa axis2_phase_holder_ops#get_phase */
#define AXIS2_PHASE_HOLDER_GET_PHASE(phase_holder, env, phase_name) \
      ((phase_holder)->ops->get_phase (phase_holder, env, phase_name))

/** Builds transport handler chain.
    @sa axis2_phase_holder_ops#build_transport_handler_chain */
#define AXIS2_PHASE_HOLDER_BUILD_TRANSPORT_HANDLER_CHAIN(phase_holder, env, phase, handlers) \
      ((phase_holder)->ops->build_transport_handler_chain (phase_holder, env, phase, handlers))

/** @} */

#ifdef __cplusplus
}
#endif
#endif  /* AXIS2_PHASE_HOLDER_H */