/*
 *   Copyright 2004,2005 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */
 
#ifndef AXIS2_XML_READER_H
#define AXIS2_XML_READER_H

/**
 *@file axis2_xml_reader.h	
 *@brief this is the parser abstraction layer for axis2 
 */

#include <axis2_env.h>


#ifdef __cplusplus
extern "C"
{
#endif

typedef struct axis2_xml_reader_ops axis2_xml_reader_ops_t;
typedef struct axis2_xml_reader axis2_xml_reader_t;

/**
 * @defgroup axis2_xml_reader 
 * @ingroup axis2_om_parser
 * @{
 */

typedef enum axis2_xml_reader_event_types
{
    AXIS2_XML_READER_START_DOCUMENT = 0,
    AXIS2_XML_READER_START_ELEMENT,
    AXIS2_XML_READER_END_ELEMENT,
    AXIS2_XML_READER_SPACE,
    AXIS2_XML_READER_EMPTY_ELEMENT,
    AXIS2_XML_READER_CHARACTER,
    AXIS2_XML_READER_ENTITY_REFERENCE,
    AXIS2_XML_READER_COMMENT,
    AXIS2_XML_READER_PROCESSING_INSTRUCTION,
    AXIS2_XML_READER_CDATA,
    AXIS2_XML_READER_DOCUMENT_TYPE
}axis2_xml_reader_event_types;

  /**
    * \brief AXIS2_XML_READER ops
    * Encapsulator struct for ops of axis2_xml_reader
    */

AXIS2_DECLARE_DATA struct axis2_xml_reader_ops
    {
        /**
         * causes the reader to read the next parse event. 
         * returns the event just read
         * @param parser axis2_xml_reader struct 
         * @param env    axis2_environment, MUST NOT be NULL
         * @returns one of the events defined in 
         *          axis2_xml_reader_event_types
         */
        
        int (AXIS2_CALL *next)(axis2_xml_reader_t *parser,
                               axis2_env_t **env);
         /**
         * free pull_parser
         * @param parser axis2_xml_reader struct 
         * @param env    axis2_environment MUST NOT be NULL 
         * @returns axis2_status_code
         */
        
        axis2_status_t (AXIS2_CALL *free)(axis2_xml_reader_t *parser,
                                          axis2_env_t **env);
        /**
         * Get the Number of attributes in the current element 
         * @param parser axis2_xml_reader  
         * @param env    axis2_environment, MUST NOT be NULL.
         * @returns Number of attributes , AXIS2_FAILURE on error 
         */  
        
        int (AXIS2_CALL *get_attribute_count)(axis2_xml_reader_t *parser,
                                              axis2_env_t **env);
                                              
       /** This is used to get an attribute's localname using an index relative to 
         * current element.The iterations are not zero based. 
         * To access the first attribute use 1 for parameter i
         * @param parser parser struct 
         * @param env environment struct
         * @param i attribute index
         * @returns the attribute localname 
         *          caller must free the value using AXIS2_XML_READER_XML_FREE macro         
         */
        axis2_char_t* (AXIS2_CALL *get_attribute_name_by_number)
                                                    (axis2_xml_reader_t *parser,
                                                     axis2_env_t **env,
                                                     int i);
                                                     
       /** This is used to get an attribute's prefix using an index relative to 
         * current element. The iterations are not zero based. 
         * To access the first attribute use 1 for parameter i
         * @param parser parser struct 
         * @param env environment, MUST NOT be NULL
         * @param i attribute index.
         * @returns the attribute prefix, returns NULL on error,  
         *          caller must free the value using AXIS2_XML_READER_XML_FREE macro         
         */                                                     
        
        axis2_char_t* (AXIS2_CALL *get_attribute_prefix_by_number)
                                                    (axis2_xml_reader_t *parser,
                                                     axis2_env_t **env,
                                                     int i);
                                                     
        /** get an attribute's value using an index relative to 
         * current element. The iterations are not zero based. 
         * To access the first attribute use 1 for parameter i
         * @param parser parser struct 
         * @param env environment, MUST NOT be NULL.
         * @param i attribute index
         * @returns the attribute value, returns NULL on error,
         *          caller must free the value using AXIS2_XML_READER_XML_FREE macro         
         */        
                                             
        axis2_char_t* (AXIS2_CALL *get_attribute_value_by_number)
                                                    (axis2_xml_reader_t *parser,
                                                     axis2_env_t **env,
                                                     int i);
        
        /** get an attribute's namespace uri using an index relative to 
         * current element. The iterations are not zero based. 
         * To access the first attribute use 1 for parameter i
         * @param parser parser struct 
         * @param env environment struct
         * @param i attribute index
         * @returns the attribute value, returns NULL on error  
         *          caller must free the value using AXIS2_XML_READER_XML_FREE macro        
         */ 
        
        axis2_char_t* (AXIS2_CALL *get_attribute_namespace_by_number)
                                                    (axis2_xml_reader_t *parser,
                                                     axis2_env_t **env,
                                                     int i);
       /** returns the text value of current element
         * @param parser pointer to parser
         * @param env environment, MUST not be NULL
         * @returns Text Value, NULL on error 
         *          caller must free the value using AXIS2_XML_READER_XML_FREE macro 
         */
                                
        axis2_char_t* (AXIS2_CALL *get_value)(axis2_xml_reader_t *parser,
                                              axis2_env_t **env);
        
        /**
         * Returns the namespace count of current element 
         * @param parser parser struct 
         * @param env environment
         * @returns namespace count of current element,
         */
        int (AXIS2_CALL *get_namespace_count)(axis2_xml_reader_t *parser,
                                              axis2_env_t **env);
        /**
         * access the namespace uri of the namespaces declared in current element 
         * using an index 
         * @param parser parser struct 
         * @param env environment 
         * @param i index
         * @returns namespace uri of corresponding namespace 
         *          caller must free the value using AXIS2_XML_READER_XML_FREE macro         
         */
        axis2_char_t* (AXIS2_CALL *get_namespace_uri_by_number)
                                              (axis2_xml_reader_t *parser,
                                               axis2_env_t **env,
                                               int i);
        /**
         * access the namespace prefix of the namespaces declared in current element 
         * using an index 
         * @param parser parser struct 
         * @param env environment 
         * @param i index
         * @returns namespace prefix of corresponding namespace 
         * caller must free the value using AXIS2_XML_READER_XML_FREE macro         
         */                                               
        axis2_char_t* (AXIS2_CALL *get_namespace_prefix_by_number)
                                               (axis2_xml_reader_t *parser,
                                                axis2_env_t **env,
                                                int i); 
        /**
         * Used to obtain the current element prefix
         * @param parser parser struct 
         * @param env environment struct
         * @returns prefix , NULL on error 
         * caller must free the value using AXIS2_XML_READER_XML_FREE macro
         */         
        
        axis2_char_t* (AXIS2_CALL *get_prefix)(axis2_xml_reader_t *parser,
                                               axis2_env_t **env);   
        /**
         *  Used to obtain the current element localname
         * @param parser parser struct 
         * @param env environment struct
         * @returns localname , NULL on error 
         *          caller must free the value using AXIS2_XML_READER_XML_FREE macro
         */         
        axis2_char_t* (AXIS2_CALL *get_name)(axis2_xml_reader_t *parser,
                                             axis2_env_t **env); 
        /**
         * Used to get the processingInstruction target
         * @param parser parser struct
         * @param env environment, MUST NOT be NULL.
         * @returns target value of processingInstruction
         *          caller must free the value using AXIS2_XML_READER_XML_FREE macro
         */        
        axis2_char_t* (AXIS2_CALL *get_pi_target)(axis2_xml_reader_t *parser,
                                                  axis2_env_t **env);
        /**
         *  gets the processingInstruction data
         *@param parser parser struct
         *@param env environment, MUST NOT be NULL.
         *@returns data of processingInstruction
         *          caller must free the value using AXIS2_XML_READER_XML_FREE macro
         */        


        axis2_char_t* (AXIS2_CALL *get_pi_data)(axis2_xml_reader_t *parser,
                                                axis2_env_t **env);
        /**
         *  used to get the DTD 
         * @param parser pointer to pull parser struct
         * @param env environment, MUST NOT be NULL.
         * @return text of doctype declaration. NULL is returns of no data 
         *         exists.
         */         
        axis2_char_t* (AXIS2_CALL *get_dtd)(axis2_xml_reader_t *parser,
                                            axis2_env_t **env);                                                
        /**
         *  Free function , this function wraps the underlying parser's 
         *  xml free function. For freeing values obatined by calling
         *  pull parser api methods, This function must be used.
         * @param parser pointer to axis2_xml_reader
         * @param env environment, MUST NOT be NULL.
         * @param data data values to be destroyed
         * @return status of the op, AXIS2_SUCCESS on success,
         *                  AXIS2_FAILURE on error.
         */         
        axis2_status_t (AXIS2_CALL *xml_free)(axis2_xml_reader_t *parser,
                                   axis2_env_t **env,
                                   void *data);
                                   
        axis2_char_t* (AXIS2_CALL *get_char_set_encoding)
                                             (axis2_xml_reader_t *parser,
                                              axis2_env_t **env);                                                                                   
    };
     
/** 
 * @brief axis2_xml_reader struct
  *	Axis2 OM pull_parser
 */
struct axis2_xml_reader
{
    axis2_xml_reader_ops_t *ops;  
};    

/**
 * create an instance of axis2_xml_reader to parse
 * a file using an xml document in a file system
 * @param env environment struct, must not be null
 * @param filename url of an xml document
 * @returns a pointer to xml_pull_parser_t struct
 *          NULL on error with error code set in the environment's error 
 */

AXIS2_DECLARE(axis2_xml_reader_t *)
axis2_xml_reader_create_for_file(axis2_env_t **env,
                                  char *filename,
                                  const axis2_char_t *encoding);
/**
 * This create an instance of axis2_xml_reader to 
 * parse a xml document in a buffer. It takes a callback 
 * function that takes a buffer and the size of the buffer
 * The user must implement a function that takes in buffer
 * and size and fill the buffer with specified size
 * with xml stream, parser will call this function to fill the 
 * buffer on the fly while parsing.
 * @param env environment MUST NOT be NULL.
 * @param read_input_callback() callback function that fills
 *         a char buffer with size @size
 *         @param buffer a character buffer
 *         @param size size of the buffer to be filled
 * @param encoding encoding scheme of the xml stream
 */
 
AXIS2_DECLARE(axis2_xml_reader_t *)
axis2_xml_reader_create_for_memory(axis2_env_t **env,
                                    int (*read_input_callback)(char *buffer,int size,void* ctx),
                                    int (*close_input_callback)(void *ctx),
                                    void *ctx,
                                    const axis2_char_t *encoding);
                                    
/********************************* Macros *************************************/

/** Macros corresponding to above declared function pointers */

/** causes the reader to read the next parse event.
 returns an integer which identifies the type of event just read. */
#define AXIS2_XML_READER_NEXT(parser, env) \
        ((parser)->ops->next(parser, env))
/** Free pull parser struct */
#define AXIS2_XML_READER_FREE(parser, env) \
        ((parser)->ops->free(parser, env))
/** Get the Number of attributes in an element */
#define AXIS2_XML_READER_GET_ATTRIBUTE_COUNT(parser, env) \
        ((parser)->ops->get_attribute_count(parser, env))
/** Get the localname of the attribute corresponding to index i */
#define AXIS2_XML_READER_GET_ATTRIBUTE_NAME_BY_NUMBER(parser, env, i) \
        ((parser)->ops->get_attribute_name_by_number(parser, env, i))
/** Get value of attribute corresponding to index i */        
#define AXIS2_XML_READER_GET_ATTRIBUTE_VALUE_BY_NUMBER(parser, env, i) \
        ((parser)->ops->get_attribute_value_by_number(parser,env, i))
/** Get namespace uri of attribute corresponding to index i */
#define AXIS2_XML_READER_GET_ATTRIBUTE_NAMESPACE_BY_NUMBER(parser, env, i) \
        ((parser)->ops->get_attribute_namespace_by_number(parser, env, i))
/** get prefix of attribute corresponding to index i */
#define AXIS2_XML_READER_GET_ATTRIBUTE_PREFIX_BY_NUMBER(parser, env, i) \
        ((parser)->ops->get_attribute_prefix_by_number(parser, env, i))
/** get the localname of element */
#define AXIS2_XML_READER_GET_NAME(parser, env) \
        ((parser)->ops->get_name(parser, env))
/** get value of element */
#define AXIS2_XML_READER_GET_VALUE(parser, env) \
        ((parser)->ops->get_value(parser, env))
/** get prefix of element */        
#define AXIS2_XML_READER_GET_PREFIX(parser, env) \
        ((parser)->ops->get_prefix(parser, env))
/** get the number of namespaces declared in an element */
#define AXIS2_XML_READER_GET_NAMESPACE_COUNT(parser, env) \
        ((parser)->ops->get_namespace_count(parser, env))
/** get the elements namespace uri corresponding to index i */        
#define AXIS2_XML_READER_GET_NAMESPACE_URI_BY_NUMBER(parser, env, i) \
        ((parser)->ops->get_namespace_uri_by_number(parser, env, i))
/** get the elements namespace prefix corresponding to index i */        
#define AXIS2_XML_READER_GET_NAMESPACE_PREFIX_BY_NUMBER(parser, env, i) \
        ((parser)->ops->get_namespace_prefix_by_number(parser, env, i))
/** get processing instruction data */        
#define AXIS2_XML_READER_GET_PI_DATA(parser, env) \
        ((parser)->ops->get_pi_data(parser, env))
/** get processing instruction target */
#define AXIS2_XML_READER_GET_PI_TARGET(parser, env) \
        ((parser)->ops->get_pi_target(parser, env))
/** get document type declaration text */        
#define AXIS2_XML_READER_GET_DTD(parser, env) \
        ((parser)->ops->get_dtd(parser, env))
/** macro to free values returned by pull parser */        
#define AXIS2_XML_READER_XML_FREE(parser, env, data) \
        ((parser)->ops->xml_free(parser, env, data))
#define AXIS2_XML_READER_GET_CHAR_SET_ENCODING(parser, env) \
        ((parser)->ops->get_char_set_encoding(parser, env))        


/******************************* End Macros ***********************************/
/** @} */


#ifdef __cplusplus
}
#endif

#endif  /* AXIS2_XML_READER_H */