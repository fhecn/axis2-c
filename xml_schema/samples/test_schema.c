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

#include <xml_schema_includes.h>
#include <stdio.h>
#include <axis2_env.h>
#include <axis2_utils_defines.h>

axis2_status_t
xml_schema_test(
        axis2_env_t *env,
        axis2_char_t *filename)
{
    axiom_xml_reader_t *xml_reader      = NULL;
    axiom_stax_builder_t *om_builder = NULL;
    axiom_document_t *om_doc         = NULL;
    xml_schema_collection_t *schema_collection = NULL;
    xml_schema_t *schema          = NULL;
    
    xml_reader = 
    axiom_xml_reader_create_for_file(env, filename, NULL);
    if(!xml_reader)
        return AXIS2_FAILURE;   
    
    om_builder = axiom_stax_builder_create(env, xml_reader);
    
    om_doc = axiom_document_create(env, NULL, om_builder);
    
    AXIOM_DOCUMENT_BUILD_ALL(om_doc, env);
    
    schema_collection = xml_schema_collection_create(env);
    
    schema = XML_SCHEMA_COLLECTION_READ_DOCUMENT(
        schema_collection, env, om_doc);
        
    if(NULL != schema)
    {
        printf("\n parsing schema is successful \n");
        
        printf("%s", XML_SCHEMA_SERIALIZE(schema, env));
    }                
    
    
    return AXIS2_SUCCESS;
}

int main(int argc, char *argv[])
{
    axis2_env_t *env = NULL;
    axis2_char_t *filename = NULL;
    if(argc > 1)
    {
        filename = argv[1];
        printf("filename:%s\n", filename);
    }
    else
    {
        printf("Give an XML schema file as the first argument\n");
        return 0;        
    }
    env = axis2_env_create_all("test.log", 1);   
    xml_schema_test(env, filename);
    return 0;
}

