#!/bin/bash

gcc string_util_test.c ../util/create_env.c -g -I$WSFC_HOME/include/axis2-1.2 -L$WSFC_HOME/lib -laxutil -laxis2_axiom -laxis2_parser -o string_util_test
