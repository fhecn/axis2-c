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

#ifndef AXIS2_PHASE_H
#define AXIS2_PHASE_H

/**
 * @defgroup axis2_phase phases
 * @ingroup axis2_engine
 * phase is a logical unit of execution in the Axis2 engine's execution flows.
 * A phase encapsulates one or more handlers in a given sequence to be invoked. 
 * The sequencing of handlers within a phase are often defined by module 
 * configuration which specifies where in the phase's handler chain a given 
 * handler should be placed.
 * Calling invoke on phase triggers invoke on the handlers stored within the 
 * phase in the sequence they are ordered. 
 * @{
 */

/**
 * @file axis2_phase.h
 */

#include <axis2_defines.h>
#include <axis2_env.h>
#include <axis2_handler.h>
#include <axis2_handler_desc.h>
#include <axis2_array_list.h>
#include <axis2_qname.h>

/** 
 * A given handler's location within the list of handlers is before a particular
 * handler and after another particular handler. 
 */
#define AXIS2_PHASE_BOTH_BEFORE_AFTER  0

/** 
 * A given handler's location within the list of handlers is before another 
 * given handler.
 */
#define AXIS2_PHASE_BEFORE  1

/** 
 * A given handler's location within the list of handlers is after another 
 * given handler.
 */
#define AXIS2_PHASE_AFTER  2

/** 
 * A given handler's location within the list of handlers could be anywhere in
 * the list.
 */
#define AXIS2_PHASE_ANYWHERE  3

#ifdef __cplusplus
extern "C"
{
#endif

    /** Type name for axis2_phase_ops */
    typedef struct axis2_phase_ops axis2_phase_ops_t;
    /** Type name for axis2_phase */
    typedef struct axis2_phase axis2_phase_t;
        
    struct axis2_msg_ctx;

    /**
     * phase ops struct.
     * Encapsulator struct for operations of axis2_phase.
     */
    struct axis2_phase_ops
    {
        /**
         * Adds given handler to the specified position in the handler array list.
         * @param phase pointer to phase struct
         * @param env pointer to environment struct
         * @param index index
         * @param handler pointer to handler, phase does not assume the 
         * ownership of the handler
         * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE 
         */
        axis2_status_t (AXIS2_CALL *
                add_handler_at)(
                    axis2_phase_t *phase,
                    const axis2_env_t *env,
                    const int index,
                    axis2_handler_t *handler);
        
        /**
         * Adds the given handler to the end of the handler list.
         * @param phase pointer to phase
         * @param env pointer to environment struct
         * @param handler pointer to handler, phase does not assume the 
         * ownership of the handler 
         * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE 
         */
        axis2_status_t (AXIS2_CALL *
                add_handler)(
                    axis2_phase_t *phase,
                    const axis2_env_t *env,
                    axis2_handler_t *handler);
                    
         /**
          * Invokes the phase. This function will in turn call invoke method of
          * each handler in the handler list, in sequence, starting from the 
          * beginning of the list to the end of the list.
          * @param phase pointer to phase
          * @param env pointer to environment struct
          * @param msg_ctx pointer to message context
          * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE 
          */
        axis2_status_t (AXIS2_CALL *
                invoke)(
                    axis2_phase_t *phase,
                    const axis2_env_t *env,
                    struct axis2_msg_ctx *msg_ctx);
        /**
         * Gets phase name.
         * @param phase pointer to phase
         * @param env pointer to environment struct
         * @return returns name of phase
         */
        const axis2_char_t *(AXIS2_CALL *
                get_name)(
                    const axis2_phase_t *phase,
                    const axis2_env_t *env);

        /**
         * Gets handler count in the handler list.
         * @param phase pointer to phase
         * @param env pointer to environment struct
         * @return the number of handlers in the handler list
         */
        int (AXIS2_CALL *
                get_handler_count)( 
                    const axis2_phase_t *phase,
                    const axis2_env_t *env);

        /**
         * Sets the first handler in the handler list.
         * @param phase pointer to phase
         * @param env pointer to environment struct
         * @param handler pointer to handler, phase does not assume the 
         * ownership of the handler
         * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE 
         */
        axis2_status_t (AXIS2_CALL *
                set_first_handler)(
                    axis2_phase_t *phase,
                    const axis2_env_t *env,
                    axis2_handler_t *handler);
                    
        /**
         * Sets the last handler in the handler list.
         * @param phase pointer to phase
         * @param env pointer to environment struct
         * @param handler pointer to handler, phase does not assume the 
         * ownership of the handler
         * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE 
         */
        axis2_status_t (AXIS2_CALL *
                set_last_handler)(  
                    axis2_phase_t *phase,
                    const axis2_env_t *env,
                    axis2_handler_t *handler);
                    
        /**
         * Adds handler within the handler description to the list of handlers 
         * in the phase.
         * @param phase pointer to phase
         * @param env pointer to environment struct
         * @param handler_desc pointer to handler description, phase does not 
         * assume the ownership of neither the handler description not the handler
         * within the handler description
         * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE 
         */
        axis2_status_t (AXIS2_CALL *
                add_handler_desc)(
                    axis2_phase_t *phase,
                    const axis2_env_t *env,
                    axis2_handler_desc_t *handler_desc);
                    
        /**
         * Inserts the handler into handler list of the phase based on the phase
         * rules associated with the handler. This function takes into account 
         * the before rules of the handler. Before rules specify the location
         * of a current handler in the handler list, before which the given 
         * handler is to be placed.
         * @param phase pointer to phase
         * @param env pointer to environment struct
         * @param handler pointer to handler, phase does not assume the 
         * ownership of the handler
         * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE 
         */
        axis2_status_t (AXIS2_CALL *
                insert_before)(
                    axis2_phase_t *phase,
                    const axis2_env_t *env,
                    axis2_handler_t *handler);

        /**
         * Inserts the handler into handler list of the phase based on the phase
         * rules associated with the handler. This function takes into account 
         * the after rules of the handler. After rules specify the location
         * of a current handler in the handler list, after which the given 
         * handler is to be placed.
         * @param phase pointer to phase
         * @param env pointer to environment struct
         * @param handler pointer to handler, phase does not assume the 
         * ownership of the handler
         * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE 
         */
        axis2_status_t (AXIS2_CALL *
                insert_after)(
                    axis2_phase_t *phase,
                    const axis2_env_t *env,
                    axis2_handler_t *handler);

        /**
         * Inserts the handler into handler list of the phase based on both 
         * before and after phase rules associated with the handler. 
         * This method assume that both the before and after cannot be the same 
         * handler . That condition is not checked by this function. 
         * It should be checked before calling this function
         * @param phase pointer to phase
         * @param env pointer to environment struct
         * @param handler pointer to handler, phase does not assume the 
         * ownership of the handler
         * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE 
         */
        axis2_status_t (AXIS2_CALL *
                insert_before_and_after)(
                    axis2_phase_t *phase,
                    const axis2_env_t *env,
                    axis2_handler_t *handler);

        /**
         * Inserts the handler to the correct location in the handler list of 
         * the phase. Location is evaluated based on the phase rules.
         * @param phase pointer to phase
         * @param env pointer to environment struct
         * @param handler_desc pointer to handler description, phase does not 
         * assume the ownership of neither the handler description not the handler
         * within the handler description
         * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE 
         */
        axis2_status_t (AXIS2_CALL *
                insert_handler_desc)(
                    axis2_phase_t *phase,
                    const axis2_env_t *env,
                    axis2_handler_desc_t *handler_desc);

        /**
         * Gets all the handlers in the phase.
         * @param phase pointer to phase
         * @param env pointer to environment struct
         * @return pointer to array list containing the list of handlers
         */
        axis2_array_list_t *(AXIS2_CALL *
                get_all_handlers)(
                    const axis2_phase_t *phase,
                    const axis2_env_t *env);

        /**
         * Invokes handlers starting from the given handler index.
         * @param phase pointer to phase
         * @param env pointer to environment struct
         * @param paused_handler_index index of the handler to start the 
         * invocation from
         * @param msg_ctx pointer to message context
         * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE 
         */
        axis2_status_t (AXIS2_CALL *
                invoke_start_from_handler)(
                    axis2_phase_t *phase,
                    const axis2_env_t *env,
                    const int paused_handler_index,
                    struct axis2_msg_ctx *msg_ctx);

        /**
         * Frees phase struct.
         * @param phase pointer to phase
         * @param env pointer to environment struct
         * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE 
         */
        axis2_status_t (AXIS2_CALL *
                free)(
                    axis2_phase_t *phase,
                    const axis2_env_t *env);

    };

    /**
     * phase struct.
     */
    struct axis2_phase
    {
        /** operations of phase */
        axis2_phase_ops_t *ops;
    };


    /**
     * creates phase struct instance.
     * @param env pointer to environment struct
     * @param phase_name name of the phase to be created
     * @return pointer to newly created phase
     */
    AXIS2_EXTERN axis2_phase_t *AXIS2_CALL
    axis2_phase_create(
            const axis2_env_t *env,
            const axis2_char_t *phase_name);

/** Add handler at a given location to the phase's list of handlers.
    @sa axis2_phase_ops#add_handler_at */
#define AXIS2_PHASE_ADD_HANDLER_AT(phase, env, index, handler) \
      ((phase)->ops->add_handler_at(phase, env, index, handler))

/** Adds the given handler to the end of the handler list.
    @sa axis2_phase_ops#add_handler */
#define AXIS2_PHASE_ADD_HANDLER(phase, env, handler) \
      ((phase)->ops->add_handler(phase, env, handler))

/** Adds the handler within given handler description to the handler list.
    @sa axis2_phase_ops#add_handler_desc */
#define AXIS2_PHASE_ADD_HANDLER_DESC(phase, env, handler_desc) \
      ((phase)->ops->add_handler_desc(phase, env, handler_desc))

/** 
 * Invokes phase, this method will call invoke of all the handlers in the list 
 * in sequence.
 * @sa axis2_phase_ops#invoke */
#define AXIS2_PHASE_INVOKE(phase, env, msg_ctx) \
       ((phase)->ops->invoke(phase, env, msg_ctx))

/** Gets phase name.
    @sa axis2_phase_ops#set_name */
#define AXIS2_PHASE_GET_NAME(phase, env) \
      ((phase)->ops->get_name(phase, env))

/** Gets handler count.
    @sa axis2_phase_ops#get_handler_count */
#define AXIS2_PHASE_GET_HANDLER_COUNT(phase, env) \
      ((phase)->ops->get_handler_count(phase, env))

/** Sets the first handler.
    @sa axis2_phase_ops#set_first_handler */
#define AXIS2_PHASE_SET_FIRST_HANDLER(phase, env, handler) \
      ((phase)->ops->set_first_handler(phase, env, handler))

/** Sets the last handler of the handler list.
    @sa axis2_phase_ops#set_last_handler */
#define AXIS2_PHASE_SET_LAST_HANDLER(phase, env, handler) \
      ((phase)->ops->set_last_handler(phase, env, handler))

/** Inserts given handler based on the before phase rules of the handler.
    @sa axis2_phase_ops#insert_before */
#define AXIS2_PHASE_INSERT_BEFORE(phase, env, handler) \
      ((phase)->ops->insert_before(phase, env, handler))

/** Inserts given handler based on the after phase rules of the handler.
    @sa axis2_phase_ops#insert_after */
#define AXIS2_PHASE_INSERT_AFTER(phase, env, handler) \
      ((phase)->ops->insert_after(phase, env, handler))

/** Inserts given handler based on the both before and after  phase rules of 
    the handler. 
    @sa axis2_phase_ops#insert_before_and_after */
#define AXIS2_PHASE_INSERT_BEFORE_AND_AFTER(phase, env, handler) \
      ((phase)->ops->insert_before_and_after(phase, env, handler))

/** Inserts the handler within given handler description to the handler list. 
    @sa axis2_phase_ops#insert_handler_desc */
#define AXIS2_PHASE_INSERT_HANDLER_DESC(phase, env, handler_desc) \
      ((phase)->ops->insert_handler_desc(phase, env, handler_desc))

/** Gets all handlers as an array list.
    @sa axis2_phase_ops#get_all_handlers */
#define AXIS2_PHASE_GET_ALL_HANDLERS(phase, env) \
      ((phase)->ops->get_all_handlers(phase, env))

/** Invoke phase starting from given handler.
    @sa axis2_phase_ops#invoke_start_from_handler */
#define AXIS2_PHASE_INVOKE_START_FROM_HANDLER(phase, env, paused_handler_index, \
        msg_ctx) \
      ((phase)->ops->invoke_start_from_handler(phase, env, paused_handler_index, \
        msg_ctx))

/** Frees phase struct.
    @sa axis2_phase_ops#free */
#define AXIS2_PHASE_FREE(phase, env) \
      ((phase)->ops->free(phase, env))

    /** @} */

#ifdef __cplusplus
}
#endif

#endif    /* AXIS2_PHASE_H */