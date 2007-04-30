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
 
#include <axis2_http_client.h>
#include <axis2_http_transport.h>
#include <axis2_stream.h>
#include <axis2_string.h>
#include <axis2_network_handler.h>
#include <axis2_http_request_line.h>
#include <axis2_http_header.h>
#include <axis2_http_status_line.h>


/** 
 * @brief HTTP Client struct impl
 *	Axis2 HTTP Client impl  
 */
typedef struct axis2_http_client_impl axis2_http_client_impl_t;  
  
struct axis2_http_client_impl
{
	axis2_http_client_t http_client;
	int sockfd;
	axis2_stream_t *data_stream;
	axis2_url_t *url;
	axis2_http_simple_response_t *response;
	axis2_bool_t request_sent;
	int timeout;
};

#define AXIS2_INTF_TO_IMPL(http_client) \
                ((axis2_http_client_impl_t *)(http_client))

/***************************** Function headers *******************************/
axis2_status_t AXIS2_CALL 
axis2_http_client_send (axis2_http_client_t *client, axis2_env_t **env,
						axis2_http_simple_request_t *request);
int AXIS2_CALL 
axis2_http_client_recieve_header (axis2_http_client_t *client, 
						axis2_env_t **env);
axis2_http_simple_response_t* AXIS2_CALL 
axis2_http_client_get_response (axis2_http_client_t *client, axis2_env_t **env);
axis2_status_t AXIS2_CALL 
axis2_http_client_set_url (axis2_http_client_t *client, 
						axis2_env_t **env, axis2_url_t *url);
axis2_url_t* AXIS2_CALL 
axis2_http_client_get_url (axis2_http_client_t *client, axis2_env_t **env);
axis2_status_t AXIS2_CALL 
axis2_http_client_set_timeout (axis2_http_client_t *client, axis2_env_t **env, 
						int timeout_ms);
int AXIS2_CALL 
axis2_http_client_get_timeout (axis2_http_client_t *client, axis2_env_t **env);

axis2_status_t AXIS2_CALL 
axis2_http_client_free (axis2_http_client_t *client, axis2_env_t **env);							

/***************************** End of function headers ************************/

AXIS2_DECLARE(axis2_http_client_t *) 
axis2_http_client_create (axis2_env_t **env, axis2_url_t *url)
{
    AXIS2_ENV_CHECK(env, NULL);
            
    axis2_http_client_impl_t *http_client_impl = 
                        (axis2_http_client_impl_t *)AXIS2_MALLOC 
                        ((*env)->allocator, sizeof(axis2_http_client_impl_t));
	
    if(NULL == http_client_impl)
	{
		AXIS2_ERROR_SET((*env)->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
	}
    
	http_client_impl->url = url;
	http_client_impl->data_stream = NULL;
	http_client_impl->sockfd = -1;
	http_client_impl->response = NULL;
	http_client_impl->request_sent = AXIS2_FALSE;
	http_client_impl->timeout = AXIS2_HTTP_DEFAULT_CONNECTION_TIMEOUT;
	
    http_client_impl->http_client.ops = AXIS2_MALLOC((*env)->allocator,
						sizeof(axis2_http_client_ops_t));
    if(NULL == http_client_impl->http_client.ops)
	{
		axis2_http_client_free((axis2_http_client_t*) http_client_impl, env);
        AXIS2_ERROR_SET((*env)->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
	}
    
    http_client_impl->http_client.ops->send = axis2_http_client_send;                        
    http_client_impl->http_client.ops->recieve_header = 
						axis2_http_client_recieve_header;
    http_client_impl->http_client.ops->get_response = 
						axis2_http_client_get_response;
	http_client_impl->http_client.ops->set_url = axis2_http_client_set_url;
	http_client_impl->http_client.ops->get_url = axis2_http_client_get_url;
	http_client_impl->http_client.ops->set_timeout = 
						axis2_http_client_set_timeout;
	http_client_impl->http_client.ops->get_timeout = 
						axis2_http_client_get_timeout;
    http_client_impl->http_client.ops->free = axis2_http_client_free;
                        
	return &(http_client_impl->http_client);
}


axis2_status_t AXIS2_CALL 
axis2_http_client_free (axis2_http_client_t *client, axis2_env_t **env)
{
	AXIS2_FUNC_PARAM_CHECK(client, env, AXIS2_FAILURE);
    axis2_http_client_impl_t *http_client_impl = AXIS2_INTF_TO_IMPL(client);
    if(NULL != http_client_impl->url)
    {
        AXIS2_URL_FREE(http_client_impl->url, env);
        http_client_impl->url = NULL;
    }
    if(NULL != http_client_impl->data_stream)
    {
        AXIS2_STREAM_FREE(http_client_impl->data_stream, env);
        http_client_impl->data_stream = NULL;
    }
	if(NULL != http_client_impl->response)
    {
        AXIS2_HTTP_SIMPLE_RESPONSE_FREE(http_client_impl->response, env);
        http_client_impl->response  = NULL;
    }
	if(-1 != http_client_impl->sockfd)
	{
		axis2_network_handler_close_socket(env, http_client_impl->sockfd);
		http_client_impl->sockfd = -1;
	}
    if(NULL != client->ops)
        AXIS2_FREE((*env)->allocator, client->ops);
    
	AXIS2_FREE((*env)->allocator, AXIS2_INTF_TO_IMPL(client));
	return AXIS2_SUCCESS;
}


axis2_status_t AXIS2_CALL 
axis2_http_client_send (axis2_http_client_t *client, axis2_env_t **env,
						axis2_http_simple_request_t *request)
{
    axis2_http_client_impl_t *client_impl = NULL;
	char *wire_format = NULL;
	axis2_array_list_t *headers = NULL;
	char *str_header = NULL;
	char *str_body = NULL;
	char *str_request_line = NULL;
	int body_size = 0;
	int written = 0;
	AXIS2_FUNC_PARAM_CHECK(client, env, AXIS2_FAILURE);
    client_impl = AXIS2_INTF_TO_IMPL(client);
	
	if(NULL != client_impl->url)
	{
		AXIS2_ERROR_SET((*env)->error, AXIS2_ERROR_NULL_URL, AXIS2_FAILURE);
	}
    
	client_impl->sockfd = axis2_network_handler_open_socket(env, 
						AXIS2_URL_GET_SERVER(client_impl->url, env), 
						AXIS2_URL_GET_PORT(client_impl->url, env));
	if(client_impl->sockfd < 0)
	{
		AXIS2_ERROR_SET((*env)->error, AXIS2_ERROR_SOCKET_ERROR, AXIS2_FAILURE);
		return AXIS2_FAILURE;
	}
	/* ONLY FOR TESTING
	 * client_impl->data_stream = axis2_stream_create_file(env, 
	 *				stdout);
	 */
	if(client_impl->timeout > 0)
	{
		axis2_network_handler_set_sock_option(env, client_impl->sockfd, 
						SO_RCVTIMEO, client_impl->timeout);
		axis2_network_handler_set_sock_option(env, client_impl->sockfd, 
						SO_SNDTIMEO, client_impl->timeout);
	}
	client_impl->data_stream = axis2_stream_create_socket(env, 
					client_impl->sockfd);
	
	if(NULL == client_impl->data_stream)
	{
		axis2_network_handler_close_socket(env, client_impl->sockfd);
		return AXIS2_FAILURE;
	}
	
	headers = AXIS2_HTTP_SIMPLE_REQUEST_GET_HEADERS(request, env);
	if(NULL != headers)
	{
		int header_count = AXIS2_ARRAY_LIST_SIZE(headers, env);
		int i = 0;
		char *str_header2 = NULL;
		for(i = 0; i < header_count; i++)
		{
			axis2_http_header_t *tmp_header = (axis2_http_header_t*)
						AXIS2_ARRAY_LIST_GET(headers, env, i);
			axis2_char_t *header_ext_form = AXIS2_HTTP_HEADER_TO_EXTERNAL_FORM(
						tmp_header, env);
			str_header2 = AXIS2_STRACAT(str_header, header_ext_form, env);
			AXIS2_FREE((*env)->allocator, str_header);
			str_header = NULL;
			AXIS2_FREE((*env)->allocator, header_ext_form);
			header_ext_form = NULL;
			str_header = str_header2;
		}
	}
	str_request_line = AXIS2_HTTP_REQUEST_LINE_TO_STRING(
						AXIS2_HTTP_SIMPLE_REQUEST_GET_REQUEST_LINE(request, env)
						, env);
	wire_format = AXIS2_STRACAT(str_request_line, str_header, env);
	AXIS2_FREE((*env)->allocator, str_header);
	str_header = NULL;
	AXIS2_FREE((*env)->allocator, str_request_line);
	str_request_line = NULL;
	written = AXIS2_STREAM_WRITE(client_impl->data_stream, env, wire_format, 
						AXIS2_STRLEN(wire_format));
	AXIS2_FREE((*env)->allocator, wire_format);
	wire_format = NULL;
	written = AXIS2_STREAM_WRITE(client_impl->data_stream, env, AXIS2_HTTP_CRLF, 
						2);
	body_size = AXIS2_HTTP_SIMPLE_REQUEST_GET_BODY_BYTES(request, env, 
						&str_body);
	if(body_size > 0 && NULL != str_body)
	{
		written = AXIS2_STREAM_WRITE(client_impl->data_stream, env, str_body, 
						body_size);		
	}
	written = AXIS2_STREAM_WRITE(client_impl->data_stream, env, AXIS2_HTTP_CRLF, 
						2); 
	client_impl->request_sent = AXIS2_TRUE;
	if(NULL != str_body)
	{
		AXIS2_FREE((*env)->allocator, str_body);
		str_body = NULL;
	}
    return AXIS2_SUCCESS;
}


int AXIS2_CALL 
axis2_http_client_recieve_header(axis2_http_client_t *client, axis2_env_t **env)
{
	int status_code = -1;
	axis2_http_client_impl_t *client_impl = NULL;
	axis2_http_status_line_t *status_line = NULL;
	char str_status_line[512];
	char tmp_buf[3];
	char str_header[512];
	int read = 0;
	axis2_bool_t end_of_line = AXIS2_FALSE;
	axis2_bool_t end_of_headers = AXIS2_FALSE;
	
    AXIS2_FUNC_PARAM_CHECK(client, env, AXIS2_CRTICAL_FAILURE);
	
	client_impl = AXIS2_INTF_TO_IMPL(client);
	if(-1 == client_impl->sockfd || NULL == client_impl->data_stream || 
						AXIS2_FALSE == client_impl->request_sent)
	{
		AXIS2_ERROR_SET((*env)->error, AXIS2_ERROR_HTTP_REQUEST_NOT_SENT, 
						AXIS2_FAILURE);
		return -1;
	}
	/* read the status line */
	memset(str_status_line, 0, 512);
	while((read = AXIS2_STREAM_READ(client_impl->data_stream, env, tmp_buf, 
						1)) > 0)
	{
		tmp_buf[read] = '\0';
		strcat(str_status_line, tmp_buf);
		if(0 != strstr(str_status_line, AXIS2_HTTP_CRLF))
		{
			end_of_line = AXIS2_TRUE;
			break;
		}
	}
	status_line = axis2_http_status_line_create(env, str_status_line);
	if(NULL == status_line)
	{
		AXIS2_ERROR_SET((*env)->error, 
						AXIS2_ERROR_INVALID_HTTP_INVALID_HEADER_START_LINE, 
						AXIS2_FAILURE);
		return -1;
	}
	client_impl->response = axis2_http_simple_response_create_default(env);
	AXIS2_HTTP_SIMPLE_RESPONSE_SET_STAUTUS_LINE(client_impl->response, env, 
						AXIS2_HTTP_STATUS_LINE_GET_HTTP_VERSION(status_line, 
						env), AXIS2_HTTP_STATUS_LINE_GET_STATUS_CODE(
						status_line, env), 
						AXIS2_HTTP_STATUS_LINE_GET_REASON_PHRASE(status_line, 
						env));

	/* now read the headers */
	memset(str_header, 0, 512);
	end_of_line = AXIS2_FALSE;
	while(AXIS2_FALSE == end_of_headers)
	{
		while((read = AXIS2_STREAM_READ(client_impl->data_stream, env, tmp_buf, 
							1)) > 0)
		{
			tmp_buf[read] = '\0';
			strcat(str_header, tmp_buf);
			if(0 != strstr(str_header, AXIS2_HTTP_CRLF))
			{
				end_of_line = AXIS2_TRUE;
				break;
			}
		}
		if(AXIS2_TRUE == end_of_line)
		{
			if(0 == AXIS2_STRCMP(str_header, AXIS2_HTTP_CRLF))
			{
				end_of_headers = AXIS2_TRUE;
			}
			else
			{
				axis2_http_header_t *tmp_header = 
						axis2_http_header_create_by_str(env, str_header);
				memset(str_header, 0, 512);
				if(NULL != tmp_header)
				{
					AXIS2_HTTP_SIMPLE_RESPONSE_SET_HEADER(client_impl->response,
						env, tmp_header);
				}
			}
		}
		end_of_line = AXIS2_FALSE;
	}
	AXIS2_HTTP_SIMPLE_RESPONSE_SET_BODY_STREAM(client_impl->response, env, 
						client_impl->data_stream); 
	if(NULL != status_line)
	{
		status_code = AXIS2_HTTP_STATUS_LINE_GET_STATUS_CODE(status_line, env);
		AXIS2_HTTP_STATUS_LINE_FREE(status_line, env);
		status_line = NULL;
	}
    return status_code;
}


axis2_http_simple_response_t* AXIS2_CALL 
axis2_http_client_get_response (axis2_http_client_t *client, axis2_env_t **env)
{
    AXIS2_FUNC_PARAM_CHECK(client, env, NULL);
    return AXIS2_INTF_TO_IMPL(client)->response;
}

axis2_status_t AXIS2_CALL 
axis2_http_client_set_url (axis2_http_client_t *client, 
						axis2_env_t **env, axis2_url_t *url)
{
    AXIS2_FUNC_PARAM_CHECK(client, env, AXIS2_FAILURE);
	AXIS2_PARAM_CHECK((*env)->error, url, AXIS2_FAILURE);
	if(NULL != AXIS2_INTF_TO_IMPL(client)->url)
	{
		AXIS2_URL_FREE(AXIS2_INTF_TO_IMPL(client)->url, env);
		AXIS2_INTF_TO_IMPL(client)->url = NULL;
	}
    AXIS2_INTF_TO_IMPL(client)->url = url;
	return AXIS2_SUCCESS;
}

axis2_url_t* AXIS2_CALL 
axis2_http_client_get_url (axis2_http_client_t *client, axis2_env_t **env)
{
    AXIS2_FUNC_PARAM_CHECK(client, env, NULL);
    return AXIS2_INTF_TO_IMPL(client)->url;
}

axis2_status_t AXIS2_CALL 
axis2_http_client_set_timeout (axis2_http_client_t *client, axis2_env_t **env, 
						int timeout_ms)
{
    AXIS2_FUNC_PARAM_CHECK(client, env, AXIS2_FAILURE);
    AXIS2_INTF_TO_IMPL(client)->timeout = timeout_ms;
	return AXIS2_SUCCESS;
}

int AXIS2_CALL 
axis2_http_client_get_timeout (axis2_http_client_t *client, axis2_env_t **env)
{
    AXIS2_FUNC_PARAM_CHECK(client, env, AXIS2_CRTICAL_FAILURE);
    return AXIS2_INTF_TO_IMPL(client)->timeout;
}