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

#include <axiom_attribute.h>
#include <string.h>
#include <axis2_utils_defines.h>

axis2_status_t AXIS2_CALL
axiom_attribute_free(axiom_attribute_t *om_attribute,
        const axis2_env_t *env);

axis2_qname_t * AXIS2_CALL
axiom_attribute_get_qname(axiom_attribute_t *om_attribute,
        const axis2_env_t *env);

axis2_status_t AXIS2_CALL
axiom_attribute_serialize(axiom_attribute_t *om_attribute,
        const axis2_env_t *env,
        axiom_output_t *om_output);

axis2_char_t* AXIS2_CALL
axiom_attribute_get_localname(axiom_attribute_t *om_attribute,
        const axis2_env_t *env);

axis2_char_t* AXIS2_CALL
axiom_attribute_get_value(axiom_attribute_t *om_attribute,
        const axis2_env_t *env);

axiom_namespace_t* AXIS2_CALL
axiom_attribute_get_namespace(axiom_attribute_t *om_attribute,
        const axis2_env_t *env);

axis2_status_t AXIS2_CALL
axiom_attribute_set_localname(axiom_attribute_t *om_attribute,
        const axis2_env_t *env,
        const axis2_char_t *localname);

axis2_status_t AXIS2_CALL
axiom_attribute_set_value(axiom_attribute_t *om_attribute,
        const axis2_env_t *env,
        const axis2_char_t *value);

axis2_status_t AXIS2_CALL
axiom_attribute_set_namespace(axiom_attribute_t *om_attribute,
        const axis2_env_t *env,
        axiom_namespace_t *om_namespace);

axiom_attribute_t* AXIS2_CALL
axiom_attribute_clone(axiom_attribute_t *om_attribute,
        const axis2_env_t *env);


/*********************************** axiom_attribute_impl_t ************************/

typedef struct axiom_attribute_impl
{
    axiom_attribute_t om_attribute;
    /** localname of this attribute  */
    axis2_char_t *localname;
    /** value of this attribute */
    axis2_char_t *value;
    /** attribute namespace */
    axiom_namespace_t *ns;
    /** store qname here */
    axis2_qname_t *qname;

}
axiom_attribute_impl_t;

/***************************************** macro *******************************/

#define AXIS2_INTF_TO_IMPL(om_attr) ((axiom_attribute_impl_t*)om_attr)


/*************************************** ***************************************/

AXIS2_EXTERN axiom_attribute_t* AXIS2_CALL
axiom_attribute_create(const axis2_env_t *env,
        const axis2_char_t * localname,
        const axis2_char_t * value,
        axiom_namespace_t * ns)
{
    axiom_attribute_impl_t *attribute_impl = NULL;

    AXIS2_ENV_CHECK(env, NULL);
    /* localname is mandatory */
    AXIS2_PARAM_CHECK(env->error, localname, NULL);

    attribute_impl = (axiom_attribute_impl_t *) AXIS2_MALLOC(env->allocator,
            sizeof(axiom_attribute_impl_t));
    if (!attribute_impl)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    /**  initialize fields */
    attribute_impl->localname = NULL;
    attribute_impl->value     = NULL;
    attribute_impl->ns        = NULL;
    attribute_impl->om_attribute.ops = NULL;
    attribute_impl->qname = NULL;

    attribute_impl->localname = (axis2_char_t*) AXIS2_STRDUP(localname, env);
    if (!(attribute_impl->localname))
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        AXIS2_FREE(env->allocator, attribute_impl);
        return NULL;
    }
    if (value)
    {
        attribute_impl->value = (axis2_char_t*) AXIS2_STRDUP(value, env);
        if (!(attribute_impl->value))
        {
            AXIS2_ERROR_SET(env->error , AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
            AXIS2_FREE(env->allocator, attribute_impl->localname);
            AXIS2_FREE(env->allocator, attribute_impl);
            return NULL;
        }
    }
    attribute_impl->ns = ns;

    attribute_impl->om_attribute.ops = (axiom_attribute_ops_t*)AXIS2_MALLOC(
                env->allocator,
                sizeof(axiom_attribute_ops_t));

    if (!(attribute_impl->om_attribute.ops))
    {
        AXIS2_FREE(env->allocator, attribute_impl->value);
        AXIS2_FREE(env->allocator, attribute_impl->localname);
        AXIS2_FREE(env->allocator, attribute_impl);
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }

    attribute_impl->om_attribute.ops->free = axiom_attribute_free;
    attribute_impl->om_attribute.ops->get_qname = axiom_attribute_get_qname;
    attribute_impl->om_attribute.ops->serialize = axiom_attribute_serialize;

    attribute_impl->om_attribute.ops->get_localname = axiom_attribute_get_localname;
    attribute_impl->om_attribute.ops->get_value = axiom_attribute_get_value;
    attribute_impl->om_attribute.ops->get_namespace = axiom_attribute_get_namespace;

    attribute_impl->om_attribute.ops->set_localname = axiom_attribute_set_localname;
    attribute_impl->om_attribute.ops->set_namespace = axiom_attribute_set_namespace;
    attribute_impl->om_attribute.ops->set_value = axiom_attribute_set_value;

    attribute_impl->om_attribute.ops->clone = axiom_attribute_clone;
    return &(attribute_impl->om_attribute);
}


axis2_status_t AXIS2_CALL
axiom_attribute_free(axiom_attribute_t *om_attribute,
        const axis2_env_t *env)
{
    axiom_attribute_impl_t *attribute_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    attribute_impl = AXIS2_INTF_TO_IMPL(om_attribute);

    if (attribute_impl->localname)
    {
        AXIS2_FREE(env->allocator, attribute_impl->localname);
        attribute_impl->localname = NULL;
    }
    if (attribute_impl->value)
    {
        AXIS2_FREE(env->allocator, attribute_impl->value);
        attribute_impl->value = NULL;
    }
    if (attribute_impl->qname)
    {
        AXIS2_QNAME_FREE(attribute_impl->qname, env);
        attribute_impl->qname = NULL;
    }
    AXIS2_FREE(env->allocator, om_attribute->ops);
    AXIS2_FREE(env->allocator, attribute_impl);
    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL
axiom_attribute_free_void_arg(
    void *om_attribute,
    const axis2_env_t *env)
{
    axiom_attribute_t *om_attribute_l = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    om_attribute_l = (axiom_attribute_t *) om_attribute;
    return axiom_attribute_free(om_attribute_l, env);
}


axis2_qname_t * AXIS2_CALL
axiom_attribute_get_qname(axiom_attribute_t *om_attribute,
        const axis2_env_t *env)
{
    axis2_qname_t *qname = NULL;
    axiom_attribute_impl_t *attribute_impl = NULL;
    AXIS2_ENV_CHECK(env, NULL);
    attribute_impl = AXIS2_INTF_TO_IMPL(om_attribute);
    if (!(attribute_impl->qname))
    {
        if (attribute_impl->ns)
        {
            qname = axis2_qname_create(env,
                    attribute_impl->localname,
                    AXIOM_NAMESPACE_GET_URI(attribute_impl->ns, env),
                    AXIOM_NAMESPACE_GET_PREFIX(attribute_impl->ns, env));
        }
        else
        {
            qname = axis2_qname_create(env, attribute_impl->localname,
                    NULL,  NULL);
        }
        attribute_impl->qname = qname;
        return qname;
    }
    return attribute_impl->qname;
}


axis2_status_t AXIS2_CALL
axiom_attribute_serialize(axiom_attribute_t *om_attribute,
        const axis2_env_t *env,
        axiom_output_t *om_output)
{
    int status = AXIS2_SUCCESS;
    axiom_attribute_impl_t *attribute = NULL;


    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, om_output, AXIS2_FAILURE);
    attribute = AXIS2_INTF_TO_IMPL(om_attribute);

    if (attribute->ns)
    {
        axis2_char_t *uri = NULL;
        axis2_char_t *prefix = NULL;

        uri = AXIOM_NAMESPACE_GET_URI(attribute->ns, env);
        prefix = AXIOM_NAMESPACE_GET_PREFIX(attribute->ns, env);

        if ((uri) && (NULL != prefix) && (AXIS2_STRCMP(prefix, "") != 0))
        {
            status = axiom_output_write(om_output, env, AXIOM_ATTRIBUTE, 4,
                    attribute->localname,
                    attribute->value,
                    uri , prefix);
        }
        else if (uri)
        {
            status = axiom_output_write(om_output, env, AXIOM_ATTRIBUTE, 3,
                    attribute->localname, attribute->value, uri);
        }
    }
    else
    {
        status = axiom_output_write(om_output, env, AXIOM_ATTRIBUTE, 2,
                attribute->localname, attribute->value);
    }
    return status;
}

axis2_char_t* AXIS2_CALL
axiom_attribute_get_localname(axiom_attribute_t *om_attribute,
        const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, NULL);
    return AXIS2_INTF_TO_IMPL(om_attribute)->localname;

}

axis2_char_t* AXIS2_CALL
axiom_attribute_get_value(axiom_attribute_t *om_attribute,
        const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, NULL);
    return AXIS2_INTF_TO_IMPL(om_attribute)->value;
}

axiom_namespace_t* AXIS2_CALL
axiom_attribute_get_namespace(axiom_attribute_t *om_attribute,
        const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, NULL);
    return AXIS2_INTF_TO_IMPL(om_attribute)->ns;
}

axis2_status_t AXIS2_CALL
axiom_attribute_set_localname(axiom_attribute_t *om_attribute,
        const axis2_env_t *env,
        const axis2_char_t *localname)
{
    axiom_attribute_impl_t *attr_impl = NULL;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, localname, AXIS2_FAILURE);
    attr_impl = AXIS2_INTF_TO_IMPL(om_attribute);

    if ((attr_impl->localname))
    {
        AXIS2_FREE(env->allocator, attr_impl->localname);
        attr_impl->localname = NULL;
    }

    attr_impl->localname = (axis2_char_t*)AXIS2_STRDUP(localname, env);

    if (!(attr_impl->localname))
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return AXIS2_FAILURE;
    }

    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL
axiom_attribute_set_value(axiom_attribute_t *om_attribute,
        const axis2_env_t *env,
        const axis2_char_t *value)
{
    axiom_attribute_impl_t *attr_impl = NULL;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, value, AXIS2_FAILURE);

    attr_impl = AXIS2_INTF_TO_IMPL(om_attribute);
    if (attr_impl->value)
    {
        AXIS2_FREE(env->allocator, attr_impl->value);
        attr_impl->value = NULL;
    }

    attr_impl->value = (axis2_char_t*)AXIS2_STRDUP(value, env);
    if (!(attr_impl->value))
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return AXIS2_FAILURE;
    }
    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL
axiom_attribute_set_namespace(axiom_attribute_t *om_attribute,
        const axis2_env_t *env,
        axiom_namespace_t *om_namespace)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_FUNC_PARAM_CHECK(om_namespace, env, AXIS2_FAILURE);
    AXIS2_INTF_TO_IMPL(om_attribute)->ns = om_namespace;
    return AXIS2_SUCCESS;
}

axiom_attribute_t* AXIS2_CALL
axiom_attribute_clone(axiom_attribute_t *om_attribute,
        const axis2_env_t *env)
{
    axiom_attribute_impl_t *attr_impl = NULL;
    axiom_attribute_t *cloned_attr    = NULL;
    if (!om_attribute) return NULL;
    AXIS2_ENV_CHECK(env, NULL);

    attr_impl = AXIS2_INTF_TO_IMPL(om_attribute);

    /** namespace is not cloned since it is a shollow copy*/
    cloned_attr = axiom_attribute_create(env,
            attr_impl->localname,
            attr_impl->value,
            attr_impl->ns);
    if (cloned_attr)
    {
        return cloned_attr;
    }
    return NULL;
}