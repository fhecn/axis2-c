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
 
#ifndef AXIOM_SOAP_BODY_H
#define AXIOM_SOAP_BODY_H
 
/**
 * @file axiom_soap_body.h
 * @brief axiom_soap_body struct
 */
 
#include <axis2_env.h>
#include <axiom_node.h>
#include <axiom_element.h>
#include <axiom_namespace.h>
#include <axiom_soap_fault.h>
#include <axiom_soap_envelope.h>    


#ifdef __cplusplus
extern "C"
{
#endif


typedef struct axiom_soap_body      axiom_soap_body_t;
typedef struct axiom_soap_body_ops  axiom_soap_body_ops_t;
struct axiom_soap_builder;
    
/**
 * @defgroup axiom_soap_body soap body
 * @ingroup axiom_soap
 * @{
 */

/**
 * a struct that represents the contents of the SOAP body
 * element in a SOAP message. SOAP body element consists of XML data
 * that affects the way the application-specific content is processed.
 * soap_body_struct contains soap_header and 
 * which have the content for the SOAP body.
 * this also contains axiom_soap_fault_t struct , which carries status and/or
 * error information.
 */

/**
 *   \brief soap_body operations struct
 *   ops Encapsulator struct of axiom_soap body
 */
 AXIS2_DECLARE_DATA   struct axiom_soap_body_ops
    {
        /**
         * Deallocate all the resources associated to soap_body
         * But it does not deallocate the underlying om structure
         * @param body soap_body struct
         * @param env must not be null
         * @return status code AXIS2_SUCCESS 
         */
        axis2_status_t (AXIS2_CALL *
      free)(axiom_soap_body_t *body,
              const axis2_env_t *env);
      
        /**
         * Indicates whether a soap fault is available with this 
         * soap body 
         * @param body soap_body struct
         * @param env environment must not be null
         * @return AXIS2_TRUE if fault is available, AXIS2_FALSE otherwise
         */
        axis2_bool_t (AXIS2_CALL *
      has_fault)(axiom_soap_body_t *body,
                   const axis2_env_t *env);
               
        /**
         * returns the soap fault in this soap_body 
         * IF a soap_builder is associated with the soap_body
         * Pulling will  take place 
         * @param body soap_body 
         * @param env environment must not be null
         * @return axiom_soap_fault_t if available, NULL otherwise
        */
        axiom_soap_fault_t* (AXIS2_CALL *
      get_fault)(axiom_soap_body_t *body,
                   const axis2_env_t *env);
               
        /**
         * get the underlying om_node 
         * @param body soap_body
         * @param env environment must not be null
         * @returns axiom_node_t
         */
        axiom_node_t* (AXIS2_CALL *
      get_base_node)(axiom_soap_body_t *body,
                       const axis2_env_t *env);
                  
        /**
         *  return the soap version 
         * @param body soap_body
         * @param env environment must not be null
         * @return one of AXIOM_SOAP11 or AXIOM_SOAP12 
         */
        int (AXIS2_CALL *
      get_soap_version)(axiom_soap_body_t *body,
                          const axis2_env_t *env);
                                                      
                                                     
        /**
         * build the soap body completely . return the status code,
       * @return AXIS2_SUCCESS on success and AXIS2_FAILURE on error
         */                                                 
        axis2_status_t (AXIS2_CALL *
      build)(axiom_soap_body_t *body, 
               const axis2_env_t *env);                                                 

       /** add an om node as the child to this soap_body 
        * the child is added to as the first child 
        * @param body pointer to soap_body struct
        * @param env axis2_environment struct MUST not be NULL
        * @returns status code , AXIS2_SUCCESS on success , AXIS2_ERROR
        * otherwise
        */

        axis2_status_t (AXIS2_CALL *
        add_child)(axiom_soap_body_t *body,
                   const axis2_env_t *env,
                   axiom_node_t *child);
                   

};                                                      

  /**
    * \brief soap_body struct
    * represent a soap_body
    */
    struct axiom_soap_body
    {
        /** operation of axiom_soap_body struct */
        axiom_soap_body_ops_t *ops;
       
    };

  /**
    * creates a soap body struct 
    * @param env Environment. MUST NOT be NULL
    */
   
AXIS2_EXTERN axiom_soap_body_t * AXIS2_CALL
axiom_soap_body_create_with_parent(const axis2_env_t *env, 
                                   struct axiom_soap_envelope *envelope);
    
/******************** Macros **************************************************/
    
/** free soap_body */
#define AXIOM_SOAP_BODY_FREE( body, env) \
        ((body)->ops->free( body, env))
        
/** indecate whether soap_body has a fault or not*/        
#define AXIOM_SOAP_BODY_HAS_FAULT( body, env) \
        ((body)->ops->has_fault( body, env))
        
#define AXIOM_SOAP_BODY_GET_FAULT( body, env) \
        ((body)->ops->get_fault( body, env))
        
#define AXIOM_SOAP_BODY_GET_BASE_NODE( body, env) \
        ((body)->ops->get_base_node( body, env))
                                   
#define AXIOM_SOAP_BODY_GET_SOAP_VERSION( body, env) \
        ((body)->ops->get_soap_version( body, env))

#define AXIOM_SOAP_BODY_BUILD( body, env) \
        ((body)->ops->build( body, env))

#define AXIOM_SOAP_BODY_ADD_CHILD( body, env, child) \
        ((body)->ops->add_child( body, env, child));
/** @} */
#ifdef __cplusplus
}
#endif

#endif /* AXIOM_SOAP_BODY_H */