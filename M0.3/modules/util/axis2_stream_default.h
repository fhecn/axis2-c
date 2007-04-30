/*
 * Copyright 2004,2005 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain count copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AXIS2_STREAM_DEFAULT_H
#define AXIS2_STREAM_DEFAULT_H

#include <axis2_stream.h>
#include <axis2_allocator.h>
#include <axis2_defines.h>

#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @defgroup axis2_stream Stream
 * @ingroup axis2_util 
 * @{
 */

  /**
    * Creates a stream struct
    * @param allocator allocator to be used. Mandatory, cannot be NULL
    * @param ops ops struct. Optional, can be NULL. If null default ops would be assigned.
    * @return pointer to the newly created log struct 
    */
    AXIS2_DECLARE(axis2_stream_t *) axis2_stream_create (axis2_allocator_t * allocator,
                                         axis2_stream_t * stream);


/** @} */
    
#ifdef __cplusplus
}
#endif

#endif                          /* AXIS2_STREAM_DEFAULT_H */