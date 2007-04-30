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
 
#ifndef WODEN_SOAP_CONSTANTS_H
#define WODEN_SOAP_CONSTANTS_H

/**
 * @file axiom_soap_constants.h
 * @brief Axis2 Xml Soap Constants
 *          Constants for XML Soap elements, attributes and URIs.
 */
 
#include <axis2_utils.h>

#ifdef __cplusplus
extern "C" 
{
#endif
    
/** @defgroup woden_soap_constants 
  * @ingroup woden_soap
  * @{
  */
/*********************************** Constansts********************************/

/* Namespace URIs.*/
#define WODEN_NS_URI_SOAP "http://www.w3.org/2006/01/wsdl/soap"

/* Protocol URIs.*/
#define WODEN_PROTOCOL_URI_HTTP "http://www.w3.org/2003/05/soap/bindings/HTTP/"

/* Element names. */
#define WODEN_ELEM_MODULE "module"
#define WODEN_ELEM_HEADER "header"

/* Attribute names. */
#define WODEN_ATTR_VERSION "version"
#define WODEN_ATTR_PROTOCOL "protocol"
#define WODEN_ATTR_MEPDEFAULT "mepDefault"
#define WODEN_ATTR_CODE "code"
#define WODEN_ATTR_SUBCODES "subcodes"
#define WODEN_ATTR_MEP "mep"
#define WODEN_ATTR_ACTION "action"
#define WODEN_ATTR_MUSTUNDERSTAND "mustUnderstand"

/* Prefixes */
#define WODEN_PFX_WSOAP "wsoap"
#define WODEN_PFX_WHTTP "whttp"   /* TODO move to HTTPConstants? */

/* Qualified element names.*/

#define WODEN_Q_ELEM_SOAP_MODULE "module|http://www.w3.org/2006/01/wsdl/soap|wsoap"

#define WODEN_Q_ELEM_SOAP_HEADER "header|http://www.w3.org/2006/01/wsdl/soap|wsoap"

/* Qualified attribute names.*/

#define WODEN_Q_ATTR_SOAP_VERSION "version|http://www.w3.org/2006/01/wsdl/soap|wsoap"

#define WODEN_Q_ATTR_SOAP_PROTOCOL "protocol|http://www.w3.org/2006/01/wsdl/soap|wsoap"

#define WODEN_Q_ATTR_SOAP_MEPDEFAULT "mepDefault|http://www.w3.org/2006/01/wsdl/soap|wsoap"

#define WODEN_Q_ATTR_SOAP_CODE "ATTR_CODE|http://www.w3.org/2006/01/wsdl/soap|wsoap"

#define WODEN_Q_ATTR_SOAP_SUBCODES "subcodes|http://www.w3.org/2006/01/wsdl/soap|wsoap"

#define WODEN_Q_ATTR_SOAP_MEP "mep|http://www.w3.org/2006/01/wsdl/soap|wsoap"

#define WODEN_Q_ATTR_SOAP_ACTION "action|http://www.w3.org/2006/01/wsdl/soap|wsoap"



/*********************************** Constants*********************************/   
   
   
#ifdef __cplusplus
}
#endif

#endif /* WODEN_SOAP_CONSTANTS_H */

