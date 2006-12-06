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
 
 #ifndef AXIS2_WSDL4C_PART_H
 #define AXIS2_WSDL4C_PART_H
 
 /**
 * @file axis2_wsdl4c_part.h
 * @brief defines WSDL4C_PART
 */
#include <axis2_array_list.h>
#include <axis2_allocator.h>
#include <axis2_env.h>
#include <axis2_error.h>
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @defgroup axis2_wsdl4c_part wsdl4c_part
 * @ingroup axis2_wsdl4c
 * @{
 */

    enum axis2_part_ref_type
    {
        None,
        Elem,
        Type
    };

   typedef enum axis2_part_ref_type axis2_wsdl4c_part_ref_type_t;
    
    void *
    axis2_wsdl4c_part_create(char* n);
     
    void
    axis2_wsdl4c_part_destroy(void *part);

    /**
     * @name axis2_wsdl4c_part_ref_type
     * @return number of part ref type
     */
    axis2_wsdl4c_part_ref_type_t
    axis2_wsdl4c_part_ref_type(void *part);

    char *
    axis2_wsdl4c_part_name(void *part);

    int
    axis2_wsdl4c_part_type(void *part);
 
    void *
    axis2_wsdl4c_part_element(void *part);
 
    int
    axis2_wsdl4c_part_schema_id(void *part);
 
    void
    axis2_wsdl4c_part_set_type(void *part, 
                                int typeId, 
                                int schema);

    void
    axis2_wsdl4c_part_set_element(void *part, 
                                    void *element, 
                                    int schema);

/** @} */

#ifdef __cplusplus
}
#endif
#endif  /* AXIS2_WSDL4C_PART_H */
