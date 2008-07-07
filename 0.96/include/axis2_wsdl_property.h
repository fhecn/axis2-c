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

#ifndef AXIS2_WSDL_PROPERTY_H
#define AXIS2_WSDL_PROPERTY_H

/**
 * @file axis2_wsdl_property.h
 * @brief Axis2 Wsdl property interface
 */

#include <axis2_const.h>
#include <axis2_error.h>
#include <axis2_defines.h>
#include <axis2_env.h>
#include <axis2_allocator.h>
#include <axis2_wsdl_component.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct axis2_wsdl_component;    
typedef struct axis2_wsdl_property axis2_wsdl_property_t;
typedef struct axis2_wsdl_property_ops axis2_wsdl_property_ops_t;

/** @defgroup axis2_wsdl_property Wsdl Property
 * @ingroup axis2_wsdl
 * @{
 */

/** 
 * @brief Wsdl Property ops struct
 * Encapsulator struct for ops of axis2_wsdl_property
 */
 struct axis2_wsdl_property_ops
{
   /** De-allocate memory
      * @return status code
      */
   axis2_status_t (AXIS2_CALL *free)(axis2_wsdl_property_t *wsdl_property,
                              const axis2_env_t *env);

    /**
     * Method getConstraint
     *
     * @return
     */
    void * (AXIS2_CALL *
    get_constraint) (axis2_wsdl_property_t *wsdl_property,
                                        const axis2_env_t *env);
    
    /**
     * Method setConstraint
     *
     * @param constraint
     */
    axis2_status_t (AXIS2_CALL *
    set_constraint) (axis2_wsdl_property_t *wsdl_property,
                                        const axis2_env_t *env,
                                        void *constraint);
    
    /**
     * Method getName
     *
     * @return
     */
    axis2_char_t *(AXIS2_CALL *
    get_name) (axis2_wsdl_property_t *wsdl_property,
                                    const axis2_env_t *env);
                                    
    /**
     * Method setName
     *
     * @param name
     */
    axis2_status_t (AXIS2_CALL *
    set_name) (axis2_wsdl_property_t *wsdl_property,
                                    const axis2_env_t *env,
                                    axis2_char_t *name);
    
    
    /**
     * Method getValue
     *
     * @return
     */
    void *(AXIS2_CALL *
    get_value) (axis2_wsdl_property_t *wsdl_property,
                                    const axis2_env_t *env);
                                    
    /**
     * Method setValue
     *
     * @param value
     */
    axis2_status_t (AXIS2_CALL *
    set_value) (axis2_wsdl_property_t *wsdl_property,
                                    const axis2_env_t *env,
                                    void *value);                                



};

/** 
 * @brief Wsdl container struct
 *   Property for params  
 */  
 struct axis2_wsdl_property
{
   axis2_wsdl_property_ops_t *ops;
    struct axis2_wsdl_component *wsdl_component;
};

/**
 * Creates wsdl property struct
 * @return pointer to newly created wsdl property
 */
AXIS2_EXTERN axis2_wsdl_property_t *AXIS2_CALL axis2_wsdl_property_create (const axis2_env_t *env);

/*************************** Function macros **********************************/

#define AXIS2_WSDL_PROPERTY_FREE(wsdl_property, env) \
      ((wsdl_property)->ops->free (wsdl_property, env))

#define AXIS2_WSDL_PROPERTY_GET_CONSTRAINT(wsdl_property, env) \
      ((wsdl_property)->ops->set_constraint (wsdl_property, env))

#define AXIS2_WSDL_PROPERTY_SET_CONSTRAINT(wsdl_property, env, constraint) \
      ((wsdl_property)->ops->get_constraint (wsdl_property, env, constraint))

#define AXIS2_WSDL_PROPERTY_GET_NAME(wsdl_property, env) \
      ((wsdl_property)->ops->get_name (wsdl_property, env))

#define AXIS2_WSDL_PROPERTY_SET_NAME(wsdl_property, env, name) \
      ((wsdl_property)->ops->set_name (wsdl_property, env, name))
        
#define AXIS2_WSDL_PROPERTY_GET_VALUE(wsdl_property, env) \
      ((wsdl_property)->ops->get_value (wsdl_property, env))

#define AXIS2_WSDL_PROPERTY_SET_VALUE(wsdl_property, env, value) \
      ((wsdl_property)->ops->set_value (wsdl_property, env, value))        

/*************************** End of function macros ***************************/

/** @} */

#ifdef __cplusplus
}
#endif
#endif  /* AXIS2_WSDL_PROPERTY_H */