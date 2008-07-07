/*
 *   Copyright 2004,2005 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *   
 * @author Dinesh Premalal (xydinesh@gmail.com, premalwd@cse.mrt.ac.lk)   
*/

#include "guththila_xml_pull_parser.h"
#include "guththila_defines.h"
/* #include "guththila_environment.h" */

int
main (int argc, char *argv[])
{
    int c;
    axis2_allocator_t *allocator;
    guththila_reader_t *red;
    axis2_env_t *environment;
    guththila_xml_pull_parser_t *parser;
    allocator = axis2_allocator_init (NULL);
    environment =
        axis2_env_create (allocator);
    red = guththila_reader_create_for_file (environment, argv[1]);
    parser = guththila_xml_pull_parser_create (environment, red);
    guththila_xml_pull_parser_read (environment, parser);

    while ((c = guththila_xml_pull_parser_next (environment, parser)) != -1)
    {
        switch (c)
        {
        case GUTHTHILA_START_DOCUMENT:
            {
                int ix;
                printf ("<?xml ");

                ix = guththila_xml_pull_parser_get_attribute_count
                    (environment, parser);
                for (; ix > 0; ix--)
                {
                    guththila_attribute_t *a;
                    char *p;
                    a = guththila_xml_pull_parser_get_attribute (environment,
                                                                 parser);
                    p = guththila_xml_pull_parser_get_attribute_name
                        (environment, parser, a);
                    printf ("%s=\"", p);
                    AXIS2_FREE (allocator, p);
                    p = guththila_xml_pull_parser_get_attribute_value
                        (environment, parser, a);
                    printf ("%s\" ", p);
                    AXIS2_FREE (allocator, p);
                }
                printf ("?>");
            }
            break;
        case GUTHTHILA_START_ELEMENT:
        case GUTHTHILA_EMPTY_ELEMENT:
            {
                int ia;
                int d;
                char *p;
		guththila_depth_t *depth;

                printf ("<");
      /* printf ("\n %s \n", guththila_xml_pull_parser_get_encoding (environment, parser)); */
                p = guththila_xml_pull_parser_get_prefix (environment,
                                                          parser);
                if (p)
                {
                    printf ("%s:", p);
                    AXIS2_FREE (allocator, p);
                }
                p = guththila_xml_pull_parser_get_name (environment, parser);
                printf ("%s", p);
                AXIS2_FREE (allocator, p);

                ia = guththila_xml_pull_parser_get_attribute_count
                    (environment, parser);
                for (; ia > 0; ia--)
                {
                    /* p = guththila_xml_pull_parser_get_attribute_prefix_by_number
                       (parser, ia); */
                    p = guththila_xml_pull_parser_get_attribute_namespace_by_number (environment, parser, ia);
                    if (p)
                    {
                        printf (" %s:", p);
                        AXIS2_FREE (allocator, p);
                        p = guththila_xml_pull_parser_get_attribute_name_by_number (environment, parser, ia);
                        printf ("%s=\"", p);
                        AXIS2_FREE (allocator, p);
                        p = guththila_xml_pull_parser_get_attribute_value_by_number (environment, parser, ia);
                        printf ("%s\"", p);
                        AXIS2_FREE (allocator, p);
                    }
                    else
                    {
                        p = guththila_xml_pull_parser_get_attribute_name_by_number (environment, parser, ia);
                        printf (" %s=\"", p);
                        AXIS2_FREE (allocator, p);
                        p = guththila_xml_pull_parser_get_attribute_value_by_number (environment, parser, ia);
                        printf ("%s\"", p);
                        AXIS2_FREE (allocator, p);
                    }
                }
		depth = (guththila_depth_t *) AXIS2_STACK_GET (parser->dep, environment);
                d = depth->count;
                for (; d > 0; d--)
                {
                    p = guththila_xml_pull_parser_get_namespace_prefix_by_number (environment, parser, d);
                    if (strncmp (p, "xmlns", 5))
                        printf (" xmlns:");
                    printf ("%s=\"", p);
                    AXIS2_FREE (allocator, p);
                    p = guththila_xml_pull_parser_get_namespace_uri_by_number
                        (environment, parser, d);
                    printf ("%s\" ", p);
                    AXIS2_FREE (allocator, p);
                }
                if (parser->guththila_event == GUTHTHILA_START_ELEMENT)
                    printf (">");
                else
                    printf ("/>");
            }
            break;
        case GUTHTHILA_END_ELEMENT:
            {
                char *p;
                printf ("</");
      /* printf ("\n %s \n", guththila_xml_pull_parser_get_encoding (environment, parser)); */
                p = guththila_xml_pull_parser_get_prefix (environment,
                                                          parser);
                if (p)
                {
                    printf ("%s:", p);
                    AXIS2_FREE (allocator, p);
                }
                p = guththila_xml_pull_parser_get_name (environment, parser);
                printf ("%s", p);
                AXIS2_FREE (allocator, p);
                printf (">");
            }
            break;
        case GUTHTHILA_CHARACTER:
            {
                char *p;
                p = guththila_xml_pull_parser_get_value (environment, parser);
                printf (p);
                AXIS2_FREE (allocator, p);
            }
            break;
        case GUTHTHILA_COMMENT:
            break;
        };
    }
    guththila_char_t *charq;
    charq = guththila_xml_pull_parser_get_encoding (environment, parser);
    printf ("encoding method is %s", charq);
    guththila_reader_free (environment, red);
    guththila_xml_pull_parser_free (environment, parser);
    axis2_allocator_free (allocator);
    axis2_env_free (environment);
    return 0;
}