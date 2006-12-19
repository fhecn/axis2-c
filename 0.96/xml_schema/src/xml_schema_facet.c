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

#include <xml_schema_facet.h>
#include <axiom_element.h>
#include <axiom_node.h>

typedef struct xml_schema_facet_impl
            xml_schema_facet_impl_t;

struct xml_schema_facet_impl
{
    xml_schema_facet_t facet;

    xml_schema_annotated_t *annotated;

    axis2_bool_t fixed ;

int obj_type;

axis2_hash_t* ht_super;

axis2_char_t *value;
};

#define AXIS2_INTF_TO_IMPL(facet) \
        ((xml_schema_facet_impl_t *) facet)

/****************** function prototypes ***************************************/

axis2_status_t AXIS2_CALL
xml_schema_facet_free(
    void *facet,
    const axis2_env_t *env);

xml_schema_annotated_t *AXIS2_CALL
xml_schema_facet_get_base_impl(
    void *facet,
    const axis2_env_t *env);

axis2_bool_t AXIS2_CALL
xml_schema_facet_is_fixed(
    void *facet,
    const axis2_env_t *env);

axis2_status_t AXIS2_CALL
xml_schema_facet_set_fixed(
    void *facet,
    const axis2_env_t *env,
    axis2_bool_t fixed);

axis2_char_t *AXIS2_CALL
xml_schema_facet_get_value(
    void *facet,
    const axis2_env_t *env);

axis2_status_t AXIS2_CALL
xml_schema_facet_set_value(
    void *facet,
    const axis2_env_t *env,
    axis2_char_t *value);

axis2_status_t AXIS2_CALL
xml_schema_facet_set_facet_type(
    void *facet,
    const axis2_env_t *env,
    int facet_type);

xml_schema_types_t AXIS2_CALL
xml_schema_facet_get_type(
    void *facet,
    const axis2_env_t *env);

axis2_hash_t* AXIS2_CALL
xml_schema_facet_super_objs(
    void *facet,
    const axis2_env_t *env);

/********************** end function prototypes *******************************/

AXIS2_EXTERN xml_schema_facet_t * AXIS2_CALL
xml_schema_facet_create(const axis2_env_t *env,
        axis2_char_t *value,
        axis2_bool_t fixed ,
        xml_schema_types_t type)
{
    xml_schema_facet_impl_t *facet_impl = NULL;
    axis2_status_t status = AXIS2_FAILURE;

    facet_impl = AXIS2_MALLOC(env->allocator,
            sizeof(xml_schema_facet_impl_t));
    if (!facet_impl)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }

    facet_impl->annotated = NULL;
    facet_impl->facet.ops = NULL;
    facet_impl->obj_type = type;
    facet_impl->facet.base.ops = NULL;

    facet_impl->fixed = fixed ;
facet_impl->value = AXIS2_STRDUP(value, env);

    facet_impl->facet.ops = AXIS2_MALLOC(env->allocator,
            sizeof(xml_schema_facet_ops_t));
    if (!facet_impl->facet.ops)
    {
        xml_schema_facet_free(&(facet_impl->facet), env);
        return NULL;
    }

    facet_impl->facet.ops->free =
        xml_schema_facet_free;
    facet_impl->facet.ops->get_base_impl =
        xml_schema_facet_get_base_impl;
    facet_impl->facet.ops->is_fixed =
        xml_schema_facet_is_fixed;
    facet_impl->facet.ops->set_fixed =
        xml_schema_facet_set_fixed;
    facet_impl->facet.ops->get_value =
        xml_schema_facet_get_value;
    facet_impl->facet.ops->set_value =
        xml_schema_facet_set_value;
    facet_impl->facet.ops->get_type =
        xml_schema_facet_get_type;
    facet_impl->facet.ops->set_facet_type =
        xml_schema_facet_set_facet_type;
    facet_impl->facet.ops->super_objs =
        xml_schema_facet_super_objs;


    facet_impl->annotated = xml_schema_annotated_create(env);
    if (!facet_impl->annotated)
    {
        xml_schema_facet_free(&(facet_impl->facet), env);
        return NULL;
    }

    facet_impl->ht_super = axis2_hash_make(env);
    if (!facet_impl->ht_super)
    {
        xml_schema_facet_free(&(facet_impl->facet), env);
        return NULL;
    }
    axis2_hash_set(facet_impl->ht_super, AXIS2_STRDUP("XML_SCHEMA_FACET", env),
            AXIS2_HASH_KEY_STRING, &(facet_impl->facet));
    axis2_hash_set(facet_impl->ht_super, AXIS2_STRDUP("XML_SCHEMA_ANNOTATED", env),
            AXIS2_HASH_KEY_STRING, facet_impl->annotated);
    axis2_hash_set(facet_impl->ht_super, AXIS2_STRDUP("XML_SCHEMA_OBJ", env),
            AXIS2_HASH_KEY_STRING,
            XML_SCHEMA_ANNOTATED_GET_BASE_IMPL(
                facet_impl->annotated, env));

    status = xml_schema_annotated_resolve_methods(
                &(facet_impl->facet.base), env, facet_impl->annotated,
                xml_schema_facet_super_objs,
                xml_schema_facet_get_type,
                xml_schema_facet_free);

    return &(facet_impl->facet);
}

axis2_status_t AXIS2_CALL
xml_schema_facet_free(void *facet,
        const axis2_env_t *env)
{
    xml_schema_facet_impl_t *facet_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    facet_impl = AXIS2_INTF_TO_IMPL(facet);

    if (facet_impl->annotated)
    {
        XML_SCHEMA_ANNOTATED_FREE(facet_impl->annotated, env);
        facet_impl->annotated = NULL;
    }

    if (facet_impl->facet.ops)
    {
        AXIS2_FREE(env->allocator, facet_impl->facet.ops);
        facet_impl->facet.ops = NULL;
    }
    if (facet_impl->facet.base.ops)
    {
        AXIS2_FREE(env->allocator, facet_impl->facet.base.ops);
        facet_impl->facet.base.ops = NULL;
    }
    if (facet_impl)
    {
        AXIS2_FREE(env->allocator, facet_impl);
        facet_impl = NULL;
    }
    return AXIS2_SUCCESS;
}

xml_schema_annotated_t *AXIS2_CALL
xml_schema_facet_get_base_impl(void *facet,
        const axis2_env_t *env)
{
    xml_schema_facet_impl_t *facet_impl = NULL;
    AXIS2_ENV_CHECK(env, NULL);
    facet_impl = AXIS2_INTF_TO_IMPL(facet);
    return facet_impl->annotated;
}

axis2_bool_t AXIS2_CALL
xml_schema_facet_is_fixed(void *facet,
        const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    return AXIS2_INTF_TO_IMPL(facet)->fixed ;
}

axis2_status_t AXIS2_CALL
xml_schema_facet_set_fixed(void *facet,
        const axis2_env_t *env,
        axis2_bool_t fixed)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_INTF_TO_IMPL(facet)->fixed = fixed ;
return AXIS2_SUCCESS;
}

axis2_char_t *AXIS2_CALL
xml_schema_facet_get_value(void *facet,
        const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, NULL);
    return AXIS2_INTF_TO_IMPL(facet)->value;
}

axis2_status_t AXIS2_CALL
xml_schema_facet_set_value(void *facet,
        const axis2_env_t *env,
        axis2_char_t *value)
{
    xml_schema_facet_impl_t *facet_impl = NULL;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    facet_impl =  AXIS2_INTF_TO_IMPL(facet);
    if (facet_impl->value)
    {
        AXIS2_FREE(env->allocator, facet_impl->value);
        facet_impl->value = NULL;
    }
    facet_impl->value = AXIS2_STRDUP(value, env);
    return AXIS2_SUCCESS;
}

AXIS2_EXTERN xml_schema_facet_t* AXIS2_CALL
xml_schema_facet_construct(const axis2_env_t *env,
        axiom_node_t *node)
{
    axiom_element_t *om_ele = NULL;
    axis2_char_t *localname = NULL;
    axis2_char_t *attr_value = NULL;
    axis2_bool_t is_fixed = AXIS2_FALSE;
    axis2_char_t *value = NULL;

    axis2_char_t *fixed_value = NULL;
    axis2_char_t *value_v     = NULL;
    void *facet = NULL;
    int facet_type;

    AXIS2_ENV_CHECK(env, NULL);
    AXIS2_PARAM_CHECK(env->error, node, NULL);


    if (AXIOM_NODE_GET_NODE_TYPE(node, env) != AXIOM_ELEMENT)
        return NULL;

    fixed_value = AXIS2_STRDUP("fixed", env);
    value_v = AXIS2_STRDUP("value", env);

    om_ele = AXIOM_NODE_GET_DATA_ELEMENT(node, env);
    localname = AXIOM_ELEMENT_GET_LOCALNAME(om_ele, env);

    if (AXIS2_STRCMP(localname, "enumeration") == 0)
    {
        facet_type = XML_SCHEMA_ENUMARATION_FACET;
    }
    else if (AXIS2_STRCMP(localname, "maxExclusive") == 0)
    {
        facet_type = XML_SCHEMA_MAX_EXCLUSIVE_FACET;
    }
    else if (AXIS2_STRCMP(localname, "maxInclusive") == 0)
    {
        facet_type = XML_SCHEMA_MAX_INCLUSIVE_FACET;
    }
    else if (AXIS2_STRCMP(localname, "minExclusive") == 0)
    {
        facet_type = XML_SCHEMA_MIN_EXCLUSIVE_FACET;
    }
    else if (AXIS2_STRCMP(localname, "maxInclusive") == 0)
    {
        facet_type = XML_SCHEMA_MIN_INCLUSIVE_FACET;
    }
    else if (AXIS2_STRCMP(localname, "pattern") == 0)
    {
        facet_type = XML_SCHEMA_PATTERN_FACET;
    }
    else if (AXIS2_STRCMP(localname, "whiteSpace") == 0)
    {
        facet_type = XML_SCHEMA_WHITE_SPACE_FACET;
    }
    else if (AXIS2_STRCMP(localname, "fractionDigits") == 0)
    {
        facet_type = XML_SCHEMA_FRACTION_DIGITS_FACET;
    }
    else if (AXIS2_STRCMP(localname, "length") == 0)
    {
        facet_type = XML_SCHEMA_LENGTH_FACET;
    }
    else if (AXIS2_STRCMP(localname, "maxLength") == 0)
    {
        facet_type = XML_SCHEMA_MAX_LENGTH_FACET;
    }
    else if (AXIS2_STRCMP(localname, "minLength") == 0)
    {
        facet_type = XML_SCHEMA_MIN_LENGTH_FACET;
    }
    else if (AXIS2_STRCMP(localname, "totalDigits") == 0)
    {
        facet_type = XML_SCHEMA_TATAL_DIGITS_FACET;
    }
    else
        return NULL;

    attr_value = AXIOM_ELEMENT_GET_ATTRIBUTE_VALUE_BY_NAME(om_ele, env, fixed_value);
    if (attr_value && AXIS2_STRCMP(attr_value, "fixed") == 0)
        is_fixed = AXIS2_TRUE;

    attr_value = NULL;
    attr_value = AXIOM_ELEMENT_GET_ATTRIBUTE_VALUE_BY_NAME(om_ele, env, value_v);
    if (attr_value)
        value = attr_value;
    else
        return NULL;

    facet = xml_schema_facet_create(env, value, is_fixed, facet_type);
    if (facet)
        return facet;
    return NULL;
}

axis2_status_t AXIS2_CALL
xml_schema_facet_set_facet_type(void *facet,
        const axis2_env_t *env,
        int facet_type)
{
    xml_schema_facet_impl_t *facet_impl = NULL;
    facet_impl = AXIS2_INTF_TO_IMPL(facet);
    facet_impl->obj_type = facet_type;
    return AXIS2_SUCCESS;
}

xml_schema_types_t AXIS2_CALL
xml_schema_facet_get_type(void *facet,
        const axis2_env_t *env)
{
    return AXIS2_INTF_TO_IMPL(facet)->obj_type;
}

axis2_hash_t* AXIS2_CALL
xml_schema_facet_super_objs(void *facet,
        const axis2_env_t *env)
{
    return AXIS2_INTF_TO_IMPL(facet)->ht_super;
}
