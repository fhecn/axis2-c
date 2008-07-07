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

#include <xml_schema_any.h>
#include <axis2_utils.h>

typedef struct xml_schema_any_impl
            xml_schema_any_impl_t;

/**
 * @brief Other Extension Struct Impl
 *   Axis2 Other Extension
 */
struct xml_schema_any_impl
{
    xml_schema_any_t any;

    xml_schema_particle_t *particle;

    xml_schema_types_t obj_type;

    axis2_hash_t *ht_super;

    xml_schema_content_processing_t *process_content;
    /**
     * Namespaces containing the elements that can be used.
     */
    axis2_char_t *ns;
};

#define AXIS2_INTF_TO_IMPL(any) ((xml_schema_any_impl_t *) any)

/******************* function prototypes **********************************/
axis2_status_t AXIS2_CALL
xml_schema_any_free(
    void *any,
    const axis2_env_t *env);

axis2_hash_t *AXIS2_CALL
xml_schema_any_super_objs(
    void *any,
    const axis2_env_t *env);

xml_schema_types_t AXIS2_CALL
xml_schema_any_get_type(
    void *any,
    const axis2_env_t *env);

xml_schema_particle_t *AXIS2_CALL
xml_schema_any_get_base_impl(void *any,
        const axis2_env_t *env);

axis2_char_t *AXIS2_CALL
xml_schema_any_get_namespace(void *any,
        const axis2_env_t *env);

axis2_status_t AXIS2_CALL
xml_schema_any_set_namespace(void *any,
        const axis2_env_t *env,
        axis2_char_t *namespc);

xml_schema_content_processing_t *AXIS2_CALL
xml_schema_any_get_process_content(void *any,
        const axis2_env_t *env);

axis2_status_t AXIS2_CALL
xml_schema_any_set_process_content(
    void *any,
    const axis2_env_t *env,
    xml_schema_content_processing_t *process_content);

/************************ end function prototypes ******************************/

AXIS2_EXTERN xml_schema_any_t * AXIS2_CALL
xml_schema_any_create(const axis2_env_t *env)
{
    xml_schema_any_impl_t *any_impl = NULL;
    axis2_status_t status = AXIS2_FAILURE;
    xml_schema_annotated_t *annotated = NULL;

    any_impl = AXIS2_MALLOC(env->allocator,
            sizeof(xml_schema_any_impl_t));
    if (!any_impl)
    {
        AXIS2_ERROR_SET(env->error , AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    any_impl->any.base.ops = NULL;
    any_impl->any.ops = NULL;
    any_impl->ns = NULL;
    any_impl->obj_type = XML_SCHEMA_ANY;
    any_impl->ht_super = NULL;
    any_impl->particle = NULL;
    any_impl->process_content = NULL;

    any_impl->any.ops = AXIS2_MALLOC(env->allocator,
            sizeof(xml_schema_any_ops_t));

    if (!any_impl->any.ops)
    {
        xml_schema_any_free(&(any_impl->any), env);
        AXIS2_ERROR_SET(env->error ,
                AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }

    any_impl->process_content = xml_schema_content_processing_create(env,
            "None");

    if (!any_impl->process_content)
    {
        xml_schema_any_free(&(any_impl->any), env);
        return NULL;
    }

    any_impl->any.ops->free =
        xml_schema_any_free;
    any_impl->any.ops->super_objs =
        xml_schema_any_super_objs;
    any_impl->any.ops->get_type =
        xml_schema_any_get_type;
    any_impl->any.ops->get_base_impl =
        xml_schema_any_get_base_impl;
    any_impl->any.ops->get_namespace =
        xml_schema_any_get_namespace;
    any_impl->any.ops->set_namespace =
        xml_schema_any_set_namespace;
    any_impl->any.ops->get_process_content =
        xml_schema_any_get_process_content;
    any_impl->any.ops->set_process_content =
        xml_schema_any_set_process_content;

    any_impl->particle = xml_schema_particle_create(env);
    if (!any_impl->particle)
    {
        xml_schema_any_free(&(any_impl->any), env);
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    any_impl->ht_super = axis2_hash_make(env);
    if (!any_impl->ht_super)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    axis2_hash_set(any_impl->ht_super,
            AXIS2_STRDUP("XML_SCHEMA_ANY", env),
            AXIS2_HASH_KEY_STRING, &(any_impl->any));

    axis2_hash_set(any_impl->ht_super,
            AXIS2_STRDUP("XML_SCHEMA_PARTICLE", env),
            AXIS2_HASH_KEY_STRING, any_impl->particle);

    annotated = XML_SCHEMA_PARTICLE_GET_BASE_IMPL(any_impl->particle, env);
    if (annotated)
    {
        axis2_hash_set(any_impl->ht_super,
                AXIS2_STRDUP("XML_SCHEMA_ANNOTATED", env),
                AXIS2_HASH_KEY_STRING, annotated);

        axis2_hash_set(any_impl->ht_super,
                AXIS2_STRDUP("XML_SCHEMA_OBJ", env),
                AXIS2_HASH_KEY_STRING, XML_SCHEMA_ANNOTATED_GET_BASE_IMPL(annotated, env));
    }

    status = xml_schema_particle_resolve_methods(
                &(any_impl->any.base), env, any_impl->particle,
                xml_schema_any_super_objs,
                xml_schema_any_get_type,
                xml_schema_any_free);
    return &(any_impl->any);
}

axis2_status_t AXIS2_CALL
xml_schema_any_free(void *any,
        const axis2_env_t *env)
{
    xml_schema_any_impl_t *any_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    any_impl = AXIS2_INTF_TO_IMPL(any);

    if (any_impl->ns)
    {
        AXIS2_FREE(env->allocator, any_impl->ns);
        any_impl->ns = NULL;
    }

    if (any_impl->process_content)
    {
        XML_SCHEMA_CONTENT_PROCESSING_FREE(any_impl->process_content, env);
        any_impl->process_content = NULL;
    }

    if (any_impl->ht_super)
    {
        axis2_hash_free(any_impl->ht_super, env);
        any_impl->ht_super = NULL;
    }

    if (any_impl->particle)
    {
        XML_SCHEMA_PARTICLE_FREE(any_impl->particle, env);
        any_impl->particle = NULL;
    }

    if (any_impl->any.ops)
    {
        AXIS2_FREE(env->allocator, any_impl->any.ops);
        any_impl->any.ops = NULL;
    }
    if (any_impl->any.base.ops)
    {
        AXIS2_FREE(env->allocator, any_impl->any.base.ops);
        any_impl->any.base.ops = NULL;
    }

    AXIS2_FREE(env->allocator, any_impl);
    any_impl = NULL;
    return AXIS2_SUCCESS;
}

xml_schema_types_t AXIS2_CALL
xml_schema_any_get_type(void *any,
        const axis2_env_t *env)
{
    xml_schema_any_impl_t *any_impl = NULL;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    any_impl = AXIS2_INTF_TO_IMPL(any);
    return any_impl->obj_type;
}

axis2_hash_t *AXIS2_CALL
xml_schema_any_super_objs(
    void *any,
    const axis2_env_t *env)
{
    xml_schema_any_impl_t *any_impl = NULL;
    AXIS2_ENV_CHECK(env, NULL);
    any_impl = AXIS2_INTF_TO_IMPL(any);
    return any_impl->ht_super;
}

xml_schema_particle_t *AXIS2_CALL
xml_schema_any_get_base_impl(void *any,
        const axis2_env_t *env)
{
    xml_schema_any_impl_t *any_impl = NULL;
    AXIS2_ENV_CHECK(env, NULL);
    any_impl = AXIS2_INTF_TO_IMPL(any);
    return any_impl->particle;
}

AXIS2_EXTERN axis2_status_t AXIS2_CALL
xml_schema_any_resolve_methods(
    xml_schema_any_t *any,
    const axis2_env_t *env,
    xml_schema_any_t *any_impl,
    XML_SCHEMA_SUPER_OBJS_FN super_objs,
    XML_SCHEMA_GET_TYPE_FN get_type,
    XML_SCHEMA_FREE_FN free_fn)
{
    xml_schema_any_impl_t *sch_any_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, any_impl, AXIS2_FAILURE);

    sch_any_impl = (xml_schema_any_impl_t *) any_impl;

    any->ops = AXIS2_MALLOC(env->allocator,
            sizeof(xml_schema_any_ops_t));
    if (!any->ops)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return AXIS2_FAILURE;
    }
    any->ops->free = free_fn;

    any->ops->super_objs = super_objs;
    any->ops->get_type = get_type;

    any->ops->get_namespace =
        sch_any_impl->any.ops->get_namespace;

    any->ops->set_namespace =
        sch_any_impl->any.ops->set_namespace;

    any->ops->get_process_content =
        sch_any_impl->any.ops->get_process_content;

    any->ops->set_process_content =
        sch_any_impl->any.ops->set_process_content;

    return xml_schema_particle_resolve_methods(&(any->base),
            env, sch_any_impl->particle, super_objs, get_type, free_fn);
}

axis2_char_t *AXIS2_CALL
xml_schema_any_get_namespace(void *any,
        const axis2_env_t *env)
{
    xml_schema_any_impl_t *any_impl = NULL;
    axis2_hash_t *ht_super = NULL;

    ht_super = XML_SCHEMA_ANY_SUPER_OBJS(any, env);
    if (ht_super)
    {
        any_impl = AXIS2_INTF_TO_IMPL(axis2_hash_get(ht_super,
                "XML_SCHEMA_ANY", AXIS2_HASH_KEY_STRING));
        if (!any_impl)
            return NULL;
    }
    return any_impl->ns;
}

axis2_status_t AXIS2_CALL
xml_schema_any_set_namespace(void *any,
        const axis2_env_t *env,
        axis2_char_t *namespc)
{
    xml_schema_any_impl_t *any_impl = NULL;
    axis2_hash_t *ht_super = NULL;
    AXIS2_PARAM_CHECK(env->error, namespc, AXIS2_FAILURE);

    ht_super = XML_SCHEMA_ANY_SUPER_OBJS(any, env);
    if (ht_super)
    {
        any_impl = AXIS2_INTF_TO_IMPL(axis2_hash_get(ht_super,
                "XML_SCHEMA_ANY", AXIS2_HASH_KEY_STRING));
        if (!any_impl)
            return AXIS2_FAILURE;
    }
    if (any_impl->ns)
    {
        AXIS2_FREE(env->allocator, any_impl->ns);
        any_impl->ns = NULL;
    }
    any_impl->ns = AXIS2_STRDUP(any_impl->ns, env);
    return AXIS2_SUCCESS;
}

xml_schema_content_processing_t *AXIS2_CALL
xml_schema_any_get_process_content(void *any,
        const axis2_env_t *env)
{
    xml_schema_any_impl_t *any_impl = NULL;
    axis2_hash_t *ht_super = NULL;

    ht_super = XML_SCHEMA_ANY_SUPER_OBJS(any, env);
    if (ht_super)
    {
        any_impl = AXIS2_INTF_TO_IMPL(axis2_hash_get(ht_super,
                "XML_SCHEMA_ANY", AXIS2_HASH_KEY_STRING));
        if (!any_impl)
            return NULL;
    }
    return any_impl->process_content;
}

axis2_status_t AXIS2_CALL
xml_schema_any_set_process_content(void *any,
        const axis2_env_t *env,
        xml_schema_content_processing_t *
        process_content)
{
    xml_schema_any_impl_t *any_impl = NULL;
    axis2_hash_t *ht_super = NULL;

    AXIS2_PARAM_CHECK(env->error, process_content, AXIS2_FAILURE);

    ht_super = XML_SCHEMA_ANY_SUPER_OBJS(any, env);

    if (ht_super)
    {
        any_impl = AXIS2_INTF_TO_IMPL(axis2_hash_get(ht_super,
                "XML_SCHEMA_ANY", AXIS2_HASH_KEY_STRING));
        if (!any_impl)
            return AXIS2_FAILURE;
    }

    if (any_impl->process_content)
    {
        XML_SCHEMA_CONTENT_PROCESSING_FREE(any_impl->process_content, env);
        any_impl->process_content = NULL;
    }
    any_impl->process_content = process_content;
    return AXIS2_SUCCESS;
}
