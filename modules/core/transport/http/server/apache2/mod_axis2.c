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


#include <httpd.h>
#include <http_config.h>
#include <http_protocol.h>
#include <ap_config.h>
#include <apr_strings.h>
#include "axis2_apache2_worker.h"
#include <axis2_error_default.h>
#include <axis2_log_default.h>
#include <axis2_thread_pool.h>
#include <axiom_xml_reader.h>

/* Configuration structure populated by apache2.conf */
typedef struct axis2_config_rec
{
    char * axis2_log_file;
    char * axis2_repo_path;
    axis2_log_levels_t log_level;
}
axis2_config_rec_t;

axis2_apache2_worker_t *axis2_worker = NULL;
const axis2_env_t *axis2_env = NULL;

/******************************Function Headers********************************/
static void *
axis2_create_svr(
    apr_pool_t *p,
    server_rec *s);

static const char *
axis2_set_repo_path(
    cmd_parms *cmd,
    void *dummy,
    const char *arg);

static const char *
axis2_set_log_file(
    cmd_parms *cmd,
    void *dummy,
    const char *arg);

static const char *
axis2_set_log_level(
    cmd_parms *cmd,
    void *dummy,
    const char *arg);

static int
axis2_handler(
    request_rec *req);

static void
axis2_module_init(
    apr_pool_t* p,
    server_rec* svr_rec);

static void
axis2_register_hooks(
    apr_pool_t *p);

/***************************End of Function Headers****************************/

static const command_rec axis2_cmds[] =
    {
        AP_INIT_TAKE1("Axis2RepoPath", axis2_set_repo_path, NULL, RSRC_CONF,
                "Axis2/C repository path"),
        AP_INIT_TAKE1("Axis2LogFile", axis2_set_log_file, NULL, RSRC_CONF,
                "Axis2/C log file name"),
        AP_INIT_TAKE1("Axis2LogLevel", axis2_set_log_level, NULL, RSRC_CONF,
                "Axis2/C log level"),
        {NULL}
    };

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA axis2_module =
    {
        STANDARD20_MODULE_STUFF,
        NULL,                  /* create per-dir    config structures */
        NULL,                  /* merge  per-dir    config structures */
        axis2_create_svr,      /* create per-server config structures */
        NULL,                  /* merge  per-server config structures */
        axis2_cmds,            /* table of config file commands       */
        axis2_register_hooks   /* register hooks                      */
    };

static void *
axis2_create_svr(
    apr_pool_t *p,
    server_rec *s)
{
    axis2_config_rec_t *conf = apr_palloc(p, sizeof(*conf));
    conf->axis2_log_file = NULL;
    conf->axis2_repo_path = NULL;
    conf->log_level = AXIS2_LOG_LEVEL_DEBUG;
    return conf;
}

static const char *
axis2_set_repo_path(
    cmd_parms *cmd,
    void *dummy,
    const char *arg)
{
	axis2_config_rec_t *conf = NULL;		
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL)
    {
        return err;
    }

    conf = (axis2_config_rec_t*)ap_get_module_config(
                cmd->server->module_config, &axis2_module);
    conf->axis2_repo_path = apr_pstrdup(cmd->pool, arg);
    return NULL;
}

static const char *
axis2_set_log_file(
    cmd_parms *cmd,
    void *dummy,
    const char *arg)
{
	axis2_config_rec_t *conf = NULL;		
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL)
    {
        return err;
    }

    conf = (axis2_config_rec_t*)ap_get_module_config(
                cmd->server->module_config, &axis2_module);
    conf->axis2_log_file = apr_pstrdup(cmd->pool, arg);
    return NULL;
}

static const char *
axis2_set_log_level(
    cmd_parms *cmd,
    void *dummy,
    const char *arg)
{
    char *str;
    axis2_log_levels_t level = AXIS2_LOG_LEVEL_DEBUG;
	axis2_config_rec_t *conf = NULL;
	const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL)
    {
        return err;
    }

    conf = (axis2_config_rec_t*)ap_get_module_config(
                cmd->server->module_config, &axis2_module);

    if ((str = ap_getword_conf(cmd->pool, &arg)))
    {
        if (!strcasecmp(str, "crit"))
        {
            level = AXIS2_LOG_LEVEL_CRITICAL;
        }
        else if (!strcasecmp(str, "error"))
        {
            level = AXIS2_LOG_LEVEL_ERROR;
        }
        else if (!strcasecmp(str, "warn"))
        {
            level = AXIS2_LOG_LEVEL_WARNING;
        }
        else if (!strcasecmp(str, "info"))
        {
            level = AXIS2_LOG_LEVEL_INFO;
        }
        else if (!strcasecmp(str, "debug"))
        {
            level = AXIS2_LOG_LEVEL_DEBUG;
        }
        else if (!strcasecmp(str, "trace"))
        {
            level = AXIS2_LOG_LEVEL_TRACE;
        }
    }
    conf->log_level = level;
    return NULL;
}

/* The sample content handler */
static int
axis2_handler(
    request_rec *req)
{
    int rv = 0;
    if (strcmp(req->handler, "axis2_module"))
    {
        return DECLINED;
    }

    /* Set up the read policy from the client.*/
    if ((rv = ap_setup_client_block(req, REQUEST_CHUNKED_DECHUNK)) != OK)
    {
        return rv;
    }
    ap_should_client_block(req);
    rv = AXIS2_APACHE2_WORKER_PROCESS_REQUEST(axis2_worker, axis2_env, req);
    if (AXIS2_CRITICAL_FAILURE == rv)
    {
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    return rv;
}

static void
axis2_module_init(
    apr_pool_t* p,
    server_rec* svr_rec)
{
    axis2_allocator_t *allocator = NULL;
    axis2_error_t *error = NULL;
    axis2_log_t *axis2_logger = NULL;
    axis2_thread_pool_t *thread_pool = NULL;
    axis2_status_t status = AXIS2_SUCCESS;
    axis2_config_rec_t *conf = (axis2_config_rec_t*)ap_get_module_config(
                svr_rec->module_config, &axis2_module);

    /* We need to init xml readers before we go into threaded env
     */
    axiom_xml_reader_init();

    /*apr_pool_cleanup_register(p, NULL, module_exit, apr_pool_cleanup_null);*/
    allocator = axis2_allocator_init(NULL);
    if (NULL == allocator)
    {
        fprintf(stderr, "[Axis2] Error initilizing mod_axis2. Reason :"
                "allocator init failed\n");
        status = AXIS2_FAILURE;
    }
    error = axis2_error_create(allocator);
    if (NULL == error)
    {
        fprintf(stderr, "[Axis2] Error initilizing mod_axis2. Reason :"
                "error struct creation failed\n");
        status = AXIS2_FAILURE;
    }
    axis2_logger = axis2_log_create(allocator, NULL, conf->axis2_log_file);
    if (NULL == axis2_logger)
    {
        fprintf(stderr, "[Axis2] Error initilizing mod_axis2. Reason :"
                "log init failed\n");
        status = AXIS2_FAILURE;
    }
    thread_pool = axis2_thread_pool_init(allocator);
    if (NULL == thread_pool)
    {
        fprintf(stderr, "[Axis2] Error initilizing mod_axis2. Reason :"
                "thread_pool init failed\n");
        status = AXIS2_FAILURE;
    }
    axis2_env = axis2_env_create_with_error_log_thread_pool(allocator, error,
            axis2_logger, thread_pool);
    if (NULL == axis2_env)
    {
        fprintf(stderr, "[Axis2] Error initilizing mod_axis2. Reason :"
                "axis2_environment init failed\n");
        status = AXIS2_FAILURE;
    }
    if (axis2_logger)
    {

        axis2_logger->level = conf->log_level;
        AXIS2_LOG_INFO(axis2_env->log, "Starting log with log level %d",
                conf->log_level);
    }
    axis2_worker = axis2_apache2_worker_create(axis2_env,
            conf->axis2_repo_path);
    if (NULL == axis2_worker)
    {
        fprintf(stderr, "[Axis2] Error initilizing mod_axis2. Reason :"
                "axis2_worker init failed\n");
        status = AXIS2_FAILURE;
    }
    if (AXIS2_FAILURE == status)
    {
        fprintf(stderr, "[Axis2] Due to one or more errors mod_axis2 loading"
                " failed. Causing apache2 to stop loading\n");
        exit(APEXIT_CHILDFATAL);
    }
}

static void
axis2_register_hooks(
    apr_pool_t *p)
{
    ap_hook_handler(axis2_handler, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_child_init(axis2_module_init, NULL, NULL, APR_HOOK_MIDDLE);
}


