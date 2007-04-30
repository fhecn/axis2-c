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
 
 #ifndef AXIOM_SOAP_HEADER_H
 #define AXIOM_SOAP_HEADER_H
 
   /**
    * @file axiom_soap_header.h
    * @brief axiom_soap_header struct
    */
#include <axis2_env.h>
#include <axiom_node.h>
#include <axiom_element.h>
#include <axis2_array_list.h>
#include <axiom_children_qname_iterator.h>
#include <axiom_children_with_specific_attribute_iterator.h>
#include <axis2_hash.h>
#include <axiom_soap_envelope.h>

#ifdef __cplusplus
extern "C"
{
#endif
    
typedef struct axiom_soap_header  axiom_soap_header_t;
typedef struct axiom_soap_header_ops axiom_soap_header_ops_t;

struct axiom_soap_header_block;   
struct axiom_soap_builder; 

    
/**
 * @defgroup axiom_soap_header soap header
 * @ingroup axiom_soap
 * @{
 */

/**
 *   \brief soap_header operations struct
 *   ops Encapsulator struct of axiom_soap header
 */
    struct axiom_soap_header_ops
    {
      /**
        * Free an axiom_soap_header
        * @param  header pointer to soap_header struct
        * @param  env Environment. MUST NOT be NULL
        * @return satus of the op. AXIS2_SUCCESS on success 
        *         else AXIS2_FAILURE
        */
        axis2_status_t (AXIS2_CALL *
      free_fn)(axiom_soap_header_t *header,
                 const axis2_env_t *env);
                                             
       /**
        * create a new axiom_soap_header_block_t struct initialized  with the
        * specified name and adds it to passed axiom_soap_header_t struct.
        * @param env environment must not be null
        * @param localName
        * @param ns
        * @return The newly created axiom_soap_header_block_t struct
        */
        struct axiom_soap_header_block* (AXIS2_CALL *
      add_header_block)(axiom_soap_header_t* header,
                      const axis2_env_t *env,
                    const axis2_char_t *localname,
                    axiom_namespace_t *ns); 
       /**
        * returns a hash_table of all the soap_header_block_t  struct in this
        * soap_header_t  object that have the the specified actor. An
        * actor is a global attribute that indicates the intermediate parties to
        * whom the message should be sent. An actor receives the message and then
        * sends it to the next actor. The default actor is the ultimate intended
        * recipient for the message, so if no actor attribute is set in a
        * axiom_soap_header_t struct the message is sent to its ultimate
        * destination.
        */
        axis2_hash_t* (AXIS2_CALL *
      examine_header_blocks)(axiom_soap_header_t* header,
                               const axis2_env_t *env,
                               axis2_char_t* param_role);
       /**
        * returns an arraylist of header_blocks which has a given namesapce uri
        * @param header 
        * @param env envirbonment must not be null
        * @param ns_uri namespace uri 
        * @return pointer to axis2_array_list_t, or null if no header_blocks with
        * given namespace uri exists
        * The returned array_list must be freed by the user.
        */
        axis2_array_list_t* (AXIS2_CALL *
      get_header_blocks_with_namespace_uri)(axiom_soap_header_t* header,
                                              const axis2_env_t *env,
                                              const axis2_char_t *ns_uri);
       /**
        * returns an iterator to iterate through all soap header block's om nodes 
        * @param header 
        * @param env environment
        * @returns axiom_children_qname_iterator_t or null if no header blocks 
        * present
        */
        axiom_children_qname_iterator_t* (AXIS2_CALL *
      examine_all_header_blocks)(axiom_soap_header_t* header,
                                   const axis2_env_t *env);
       /**
        * returns an iterator to iterate through all  header blocks om_nodes 
        * with the matching role attribute
        * @param header soap_header
        * @param env environment 
        * @param role 
        * @returns iterator or null if no header blocks present with matching 
        * role attribute
        */
        axiom_children_with_specific_attribute_iterator_t *(AXIS2_CALL *
      extract_header_blocks)(axiom_soap_header_t *header,
                               const axis2_env_t *env,
                               axis2_char_t *role);
                                         
       /**
        * returns the axiom_node_t struct wrapped in soap_header
        * @param header soap_header_t
        * @param env environment must not be null
        * @return axiom_node_t
        */
        axiom_node_t* (AXIS2_CALL *
      get_base_node)(axiom_soap_header_t *header,
                       const axis2_env_t *env);
        /**
         *  return the soap_version of this soap_header
         *  @param header soap_header
         *  @param env environment must not be null
         *  @return AXIOM_SOAP11 or AXIOM_SOAP12
         */
       int  (AXIS2_CALL *
      get_soap_version) (axiom_soap_header_t *header,
                          const axis2_env_t *env);
        
         
       /**
        * @returns a hash table of all header_blocks in this header
        * the returned hash is a readonly hash should not be modified
        */
        axis2_hash_t* (AXIS2_CALL *
        get_all_header_blocks)(axiom_soap_header_t *header,
                               const axis2_env_t *env);                                                
       /**
        * remove header block that matches to the given qname
        * qname should not be null
        * 
        */                                  
        axis2_status_t (AXIS2_CALL *
        remove_header_block)(axiom_soap_header_t *header,
                             const axis2_env_t *env,
                             axis2_qname_t *qname);
        
        
    };

  /**
    * \brief soap_header struct
    * represent a soap_header
    */
    struct axiom_soap_header
    {
        /** operation of axiom_soap_header struct */
        axiom_soap_header_ops_t *ops;
       
    };

  /**
    * creates a soap struct 
    * @param env Environment. MUST NOT be NULL
    */


    
AXIS2_EXTERN axiom_soap_header_t * AXIS2_CALL
axiom_soap_header_create_with_parent(const axis2_env_t *env,
                                     struct axiom_soap_envelope *envelope);
                                     
/******************** Macros **************************************************/
    
    
/** free soap_header */
#define AXIOM_SOAP_HEADER_FREE(header , env) \
        ((header)->ops->free_fn(header, env))

#define AXIOM_SOAP_HEADER_ADD_HEADER_BLOCK(header, env, localname, ns) \
        ((header)->ops->add_header_block(header, env, localname, ns))
        
#define AXIOM_SOAP_HEADER_EXAMINE_HEADER_BLOCKS(header, env, param_role) \
        ((header)->ops->examine_header_blocks(header, env, param_role))

#define AXIOM_SOAP_HEADER_EXAMINE_ALL_HEADER_BLOCKS(header, env) \
        ((header)->ops->examine_all_header_blocks(header, env))
        
#define AXIOM_SOAP_HEADER_EXTRACT_HEADER_BLOCKS(header, env, role) \
        ((header)->ops->extract_header_blocks(header, env, role))                        

#define AXIOM_SOAP_HEADER_GET_BASE_NODE(header, env) \
        ((header)->ops->get_base_node(header, env)) 
       
#define AXIOM_SOAP_HEADER_GET_SOAP_VERSION(header, env) \
        ((header)->ops->get_soap_version(header, env))

#define AXIOM_SOAP_HEADER_GET_HEADER_BLOCKS_WITH_NAMESPACE_URI(header, env, uri)\
        ((header)->ops->get_header_blocks_with_namespace_uri(header, env, uri))

#define AXIOM_SOAP_HEADER_GET_ALL_HEADER_BLOCKS(header, env) \
        ((header)->ops->get_all_header_blocks(header, env))
        
#define AXIOM_SOAP_HEADER_REMOVE_HEADER_BLOCK(header, env, qname) \
        ((header)->ops->remove_header_block(header, env, qname))        

/** @} */
#ifdef __cplusplus
}
#endif
#endif /* AXIOM_SOAP_HEADER_H */