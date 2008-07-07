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
#include <axiom_node.h>
#include <axiom_element.h>
#include <axiom_text.h>
#include <axis2_stream.h>
#include <axis2_log_default.h>
#include <axis2_error_default.h>
#include <axis2_svc_client.h>
#include <axis2_util.h>
#include <stdlib.h>
#include <stdio.h>

static axiom_node_t *
build_om_programatically_for_wsdl1(
    const axis2_env_t *env);

static axiom_node_t *
build_om_programatically_for_wsdl2(
    const axis2_env_t *env);

static int
process_for_wsdl1(
    const axis2_env_t *env,
    axis2_char_t *wsdl_uri_str);

static int
process_for_wsdl2(
    const axis2_env_t *env,
    axis2_char_t *wsdl_uri_str);

int main(int argc, char** argv)
{
    axis2_env_t *env = NULL;
    axis2_error_t *error = NULL;
    axis2_log_t *log = NULL;
    axis2_allocator_t *allocator = NULL;
    axis2_char_t *wsdl_uri_str = NULL;

    /* set up the envioronment with allocator and log*/
    allocator = axis2_allocator_init(NULL);
    error = axis2_error_create(allocator);
    log = axis2_log_create(allocator, NULL, "addr_echo.log");
    env = axis2_env_create_with_error_log(allocator, error, log);
    env->log->level = AXIS2_LOG_LEVEL_TRACE;
    axis2_error_init();

    if (argc <= 1)
    {
        printf("Usage: print <wsdl_File_Name>\n");
        return 1;
    }
    wsdl_uri_str = argv[1];
    if (strstr(wsdl_uri_str, "cal_1.1"))
    {
        printf("Calculator\n");
        process_for_wsdl1(env, wsdl_uri_str);
    }
    else
    {
        printf("Hotel Reservation\n");
        process_for_wsdl2(env, wsdl_uri_str);
    }
    return 0;
}

static int
process_for_wsdl1(
    const axis2_env_t *env,
    axis2_char_t *wsdl_uri_str)
{
    axiom_node_t *payload = NULL;
    axiom_node_t *response = NULL;
    axis2_uri_t *wsdl_uri = NULL;
    axis2_qname_t *op_qname = NULL;
    axis2_svc_client_t *svc_client = NULL;
    const axis2_char_t *client_home = NULL;
    axis2_qname_t *wsdl_svc_qname = NULL;


    /* Set up deploy folder. It is from the deploy folder, the configuration
     * is picked up using the axis2.xml file.
     * In this sample client_home points to the Axis2/C default deploy folder. 
     * The client_home can be different from this folder on your system. For 
     * example, you may have a different folder (say, my_client_folder) with 
     * its own axis2.xml file. my_client_folder/modules will have the 
     * modules that the client uses
     */
    client_home = AXIS2_GETENV("AXIS2C_HOME");
    if (!client_home || !strcmp (client_home, ""))
        client_home = "../..";

    wsdl_svc_qname = axis2_qname_create(env, "Calculator",
            "http://localhost/axis/Calculator", NULL);
    wsdl_uri = axis2_uri_parse_string(env, wsdl_uri_str);
    svc_client =
        axis2_svc_client_create_for_dynamic_invocation(
            env, NULL, wsdl_uri, wsdl_svc_qname, "Calculator", client_home);
    if (!svc_client)
    {
        printf("Error creating service client, Please check AXIS2C_HOME again\n");
        AXIS2_LOG_DEBUG(env->log, AXIS2_LOG_SI, "Service client is NULL");
        return 1;
    }
    payload = build_om_programatically_for_wsdl1(env);
    op_qname = axis2_qname_create(env, "add", "http://localhost/axis/Calculator",
            NULL);
    response = AXIS2_SVC_CLIENT_SEND_RECEIVE_WITH_OP_QNAME(svc_client, env,
            op_qname, payload);

    if (response)
    {
        axis2_char_t *om_str = NULL;

        om_str = AXIOM_NODE_TO_STRING(response, env);
        if (om_str)
            printf("\nReceived OM : %s\n", om_str);
        printf("status:%s\n", "Successful");
    }
    else
        printf("status:%s\n", "Failure");
    if (svc_client)
    {
        AXIS2_SVC_CLIENT_FREE(svc_client, env);
        svc_client = NULL;
    }
    return 0;
}

static int
process_for_wsdl2(
    const axis2_env_t *env,
    axis2_char_t *wsdl_uri_str)
{
    axiom_node_t *payload = NULL;
    axiom_node_t *response = NULL;
    axis2_uri_t *wsdl_uri = NULL;
    axis2_qname_t *op_qname = NULL;
    axis2_svc_client_t *svc_client = NULL;
    const axis2_char_t *client_home = NULL;
    axis2_qname_t *wsdl_svc_qname = NULL;

    /* Set up deploy folder. It is from the deploy folder, the configuration
     * is picked up using the axis2.xml file.
     * In this sample client_home points to the Axis2/C default deploy folder. 
     * The client_home can be different from this folder on your system. For 
     * example, you may have a different folder (say, my_client_folder) with 
     * its own axis2.xml file. my_client_folder/modules will have the 
     * modules that the client uses
     */
    client_home = AXIS2_GETENV("AXIS2C_HOME");
    if (!client_home || !strcmp (client_home, ""))
        client_home = "../..";

    wsdl_svc_qname = axis2_qname_create(env, "reservationService",
            "http://greath.example.com/2004/wsdl/resSvc", NULL);
    wsdl_uri = axis2_uri_parse_string(env, wsdl_uri_str);
    svc_client =
        axis2_svc_client_create_for_dynamic_invocation(
            env, NULL, wsdl_uri, wsdl_svc_qname, "reservationService", client_home);
    if (!svc_client)
    {
        printf("Service client is NULL \n");
        AXIS2_LOG_DEBUG(env->log, AXIS2_LOG_SI, "Service client is NULL");
        return -1;
    }
    payload = build_om_programatically_for_wsdl2(env);
    op_qname = axis2_qname_create(env, "add", "http://localhost/axis/Calculator",
            NULL);
    response = AXIS2_SVC_CLIENT_SEND_RECEIVE_WITH_OP_QNAME(svc_client, env,
            op_qname, payload);

    if (response)
    {
        axis2_char_t *om_str = NULL;

        om_str = AXIOM_NODE_TO_STRING(response, env);
        if (om_str)
            printf("\nReceived OM : %s\n", om_str);
        printf("status:%s\n", "Success");
    }
    else
        printf("status:%s\n", "Failure");
    if (svc_client)
    {
        AXIS2_SVC_CLIENT_FREE(svc_client, env);
        svc_client = NULL;
    }
    return 0;
}


/* build SOAP request message content using OM */
static axiom_node_t *
build_om_programatically_for_wsdl1(
    const axis2_env_t *env)
{
    axiom_node_t *add_om_node = NULL;
    axiom_element_t* add_om_ele = NULL;
    axiom_node_t *arg0_om_node = NULL;
    axiom_element_t* arg0_om_ele = NULL;
    axiom_node_t *arg1_om_node = NULL;
    axiom_element_t* arg1_om_ele = NULL;
    axiom_node_t *seq_om_node = NULL;
    axiom_element_t* seq_om_ele = NULL;
    axiom_node_t *cmplx_type_om_node = NULL;
    axiom_element_t* cmplx_type_om_ele = NULL;
    axiom_namespace_t *ns1 = NULL;
    axiom_attribute_t *attr = NULL;
    axiom_attribute_t *attr_name_arg0 = NULL;
    axiom_attribute_t *attr_name_arg1 = NULL;


    axiom_xml_writer_t *xml_writer = NULL;
    axiom_output_t *om_output = NULL;
    axis2_char_t *buffer = NULL;
    axis2_char_t *ns = NULL;

    ns = AXIS2_STRDUP("http://localhost/axis/Calculator", env);
    ns1 = axiom_namespace_create(env, ns, "tns0");

    add_om_ele = axiom_element_create(env, NULL, "add", ns1, &add_om_node);
    cmplx_type_om_ele = axiom_element_create(env, add_om_node, "complexType", ns1, &cmplx_type_om_node);
    seq_om_ele = axiom_element_create(env, cmplx_type_om_node, "sequence", ns1, &seq_om_node);
    attr = axiom_attribute_create(env, "type", "xsd:int", ns1);
    attr_name_arg0 = axiom_attribute_create(env, "name", "arg_0_0", ns1);
    attr_name_arg1 = axiom_attribute_create(env, "name", "arg_1_0", ns1);
    arg0_om_ele = axiom_element_create(env, seq_om_node, "arg_0_0", NULL, &arg0_om_node);
    AXIOM_ELEMENT_SET_TEXT(arg0_om_ele, env, "5", arg0_om_node);
    AXIOM_ELEMENT_ADD_ATTRIBUTE(arg0_om_ele, env, attr, arg0_om_node);
    AXIOM_ELEMENT_ADD_ATTRIBUTE(arg0_om_ele, env, attr_name_arg0, arg0_om_node);
    arg1_om_ele = axiom_element_create(env, seq_om_node, "arg_1_0", NULL, &arg1_om_node);
    AXIOM_ELEMENT_SET_TEXT(arg1_om_ele, env, "10", arg1_om_node);
    AXIOM_ELEMENT_ADD_ATTRIBUTE(arg1_om_ele, env, attr_name_arg1, arg1_om_node);
    AXIOM_ELEMENT_ADD_ATTRIBUTE(arg1_om_ele, env, attr, arg1_om_node);

    xml_writer = axiom_xml_writer_create_for_memory(env, NULL, AXIS2_FALSE,
            AXIS2_FALSE, AXIS2_XML_PARSER_TYPE_BUFFER);
    om_output = axiom_output_create(env, xml_writer);

    AXIOM_NODE_SERIALIZE(add_om_node, env, om_output);
    buffer = AXIOM_XML_WRITER_GET_XML(xml_writer, env);
    printf("\nOM node in XML : %s \n",  buffer);
    AXIS2_FREE(env->allocator, buffer);
    AXIOM_OUTPUT_FREE(om_output, env);

    return add_om_node;
}

/* build SOAP request message content using OM */
static axiom_node_t *
build_om_programatically_for_wsdl2(
    const axis2_env_t *env)
{
    axiom_node_t *add_om_node = NULL;
    axiom_element_t* add_om_ele = NULL;
    axiom_node_t *arg0_om_node = NULL;
    axiom_element_t* arg0_om_ele = NULL;
    axiom_node_t *arg1_om_node = NULL;
    axiom_element_t* arg1_om_ele = NULL;
    axiom_node_t *seq_om_node = NULL;
    axiom_element_t* seq_om_ele = NULL;
    axiom_node_t *cmplx_type_om_node = NULL;
    axiom_element_t* cmplx_type_om_ele = NULL;
    axiom_namespace_t *ns1 = NULL;
    axiom_attribute_t *attr = NULL;
    axiom_attribute_t *attr_name_arg0 = NULL;
    axiom_attribute_t *attr_name_arg1 = NULL;


    axiom_xml_writer_t *xml_writer = NULL;
    axiom_output_t *om_output = NULL;
    axis2_char_t *buffer = NULL;
    axis2_char_t *ns = NULL;

    ns = AXIS2_STRDUP("http://localhost/axis/Calculator", env);
    ns1 = axiom_namespace_create(env, ns, "tns0");

    add_om_ele = axiom_element_create(env, NULL, "add", ns1, &add_om_node);
    cmplx_type_om_ele = axiom_element_create(env, add_om_node, "complexType", ns1, &cmplx_type_om_node);
    seq_om_ele = axiom_element_create(env, cmplx_type_om_node, "sequence", ns1, &seq_om_node);
    attr = axiom_attribute_create(env, "type", "xsd:int", ns1);
    attr_name_arg0 = axiom_attribute_create(env, "name", "arg_0_0", ns1);
    attr_name_arg1 = axiom_attribute_create(env, "name", "arg_1_0", ns1);
    arg0_om_ele = axiom_element_create(env, seq_om_node, "arg_0_0", NULL, &arg0_om_node);
    AXIOM_ELEMENT_SET_TEXT(arg0_om_ele, env, "5", arg0_om_node);
    AXIOM_ELEMENT_ADD_ATTRIBUTE(arg0_om_ele, env, attr, arg0_om_node);
    AXIOM_ELEMENT_ADD_ATTRIBUTE(arg0_om_ele, env, attr_name_arg0, arg0_om_node);
    arg1_om_ele = axiom_element_create(env, seq_om_node, "arg_1_0", NULL, &arg1_om_node);
    AXIOM_ELEMENT_SET_TEXT(arg1_om_ele, env, "10", arg1_om_node);
    AXIOM_ELEMENT_ADD_ATTRIBUTE(arg1_om_ele, env, attr_name_arg1, arg1_om_node);
    AXIOM_ELEMENT_ADD_ATTRIBUTE(arg1_om_ele, env, attr, arg1_om_node);

    xml_writer = axiom_xml_writer_create_for_memory(env, NULL, AXIS2_FALSE,
            AXIS2_FALSE, AXIS2_XML_PARSER_TYPE_BUFFER);
    om_output = axiom_output_create(env, xml_writer);

    AXIOM_NODE_SERIALIZE(add_om_node, env, om_output);
    buffer = AXIOM_XML_WRITER_GET_XML(xml_writer, env);
    printf("\nOM node in XML : %s \n",  buffer);
    AXIS2_FREE(env->allocator, buffer);
    AXIOM_OUTPUT_FREE(om_output, env);

    return add_om_node;
}
