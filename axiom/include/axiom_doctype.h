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

#ifndef AXIOM_DOCTYPE_H
#define AXIOM_DOCTYPE_H

/**
 *@file axiom_doctype.h   
 *@brief defines struct representing xml DTD and its manipulation functions
 */

#include <axiom_node.h>
#include <axiom_output.h>

#ifdef __cplusplus
extern "C"
{
#endif

    struct axiom_doctype;
    struct axiom_doctype_ops;

/**
 * @defgroup axiom_doctype OM Doctype
 * @ingroup axiom 
 * @{
 */

  /**
    * \brief OM doctype ops struct
    * Encapsulator struct for ops of axiom_doctype
    */
 AXIS2_DECLARE_DATA   typedef struct axiom_doctype_ops
    {
      /**
        * free doctype struct
        * @param om_doctype pointer to axiom_doctype_t struct to be freed
        * @param env Environment. MUST NOT be NULL,
        * @return satus of the op. AXIS2_SUCCESS on success
        *         AXIS2_FAILURE on error.
        */
        axis2_status_t (AXIS2_CALL *
        free)(struct axiom_doctype *om_doctype,
              const axis2_env_t *env);
       /**
        * @param om_doctype pointer to a axiom_doctype_t struct
        * @param env environment must not be null       
        * @return DTD text 
        */
        axis2_char_t* (AXIS2_CALL *
        get_value)(struct axiom_doctype *om_doctype,
                   const axis2_env_t *env);
       /**
        * @param om_doctype pointer to axiom doctype_t struct
        * @param env environment , MUST NOT be NULL.
        * @param value doctype text value
        * @return status of the op,
        *         AXIS2_SUCCESS on success, AXIS2_FAILURE on error.
        */

        axis2_status_t (AXIS2_CALL *
        set_value)(struct axiom_doctype *om_doctype,
                   const axis2_env_t *env,
                   const axis2_char_t *value);
       /**
        * serialize op 
        * @param om_doctype pointer to axiom_doctype_t struct
        * @param env environment , MUST NOT be NULL
        * @param om_output pointer to axiom_output_t struct
        * @returns status of the op,
        *          AXIS2_SUCCESS on success, AXIS2_FAILURE on error.
        */                                   
        
        axis2_status_t (AXIS2_CALL *
        serialize)(struct axiom_doctype *om_doctype,
                   const axis2_env_t *env,
                   axiom_output_t *om_output);
                                                                                                                                      
    } axiom_doctype_ops_t;

  /**
    * \brief OM doctype struct
    * Handles XML document type in OM
    */
    typedef struct axiom_doctype
    {
        /** Doctype related ops */
        axiom_doctype_ops_t *ops;

    } axiom_doctype_t;

  /**
    * Creates a axiom_doctype_t struct
    * @param env Environment. MUST  NOT be NULL,
    * @param parent parent of the new node. Optinal, can be NULL. 
    * @param value doctype text
    * @param node This is an out parameter.cannot be NULL.
    *               Returns the node corresponding to the doctype created.
    *               Node type will be set to AXIOM_DOCTYPE
    * @return pointer to newly created doctype struct 
    */
    AXIS2_EXTERN axiom_doctype_t * AXIS2_CALL
    axiom_doctype_create (const axis2_env_t *env,
                             axiom_node_t * parent,
                             const axis2_char_t * value,
                             axiom_node_t ** node);

/** free given doctype */    
#define AXIOM_DOCTYPE_FREE(doctype, env) \
        ((doctype)->ops->free(doctype, env))
/** returns the value of doctype */
#define AXIOM_DOCTYPE_GET_VALUE(doctype, env) \
        ((doctype)->ops->get_value(doctype, env))
/** set the doctype value */
#define AXIOM_DOCTYPE_SET_VALUE(doctype, env, value) \
        ((doctype)->ops->set_value(doctype, env, value))
/** serialize op */       
#define AXIOM_DOCTYPE_SERIALIZE(doctype, env, om_output) \
        ((doctype)->ops->serialize(doctype, env, om_output))

/** @} */
    
#ifdef __cplusplus
}
#endif

#endif                          /* AXIOM_DOCTYPE_H */
