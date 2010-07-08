#include "../util/create_env.h"
#include <cut_defs.h>
#include <axutil_stack.h>

void test_stack(axutil_env_t * env, char * value)
{
    axutil_stack_t * stack = NULL;
    axis2_status_t status = AXIS2_FAILURE;
    void * get_value = NULL;
	
    stack = axutil_stack_create(env);
	CUT_ASSERT(stack != NULL);
    if (!stack)
    {
        return;
    }
    status = axutil_stack_push(stack,env,(void *)value);
    CUT_ASSERT(status == AXIS2_SUCCESS);
    CUT_ASSERT(axutil_stack_size(stack,env) == 1);
    CUT_ASSERT(value == (char *)axutil_stack_get(stack,env));
    get_value = axutil_stack_get_at(stack,env,0);
    CUT_ASSERT(strcmp(value,get_value) == 0);
    CUT_ASSERT(strcmp(value,(char *)axutil_stack_pop(stack,env)) == 0);
    CUT_ASSERT(axutil_stack_size(stack,env) == 0);
    
    /* To avoid warning of not using cut_ptr_equal */
    CUT_ASSERT_PTR_EQUAL(NULL, NULL, 0);
    /* To avoid warning of not using cut_int_equal */
    CUT_ASSERT_INT_EQUAL(0, 0, 0);
    /* To avoid warning of not using cut_str_equal */
    CUT_ASSERT_STR_EQUAL("", "", 0);

    axutil_stack_free(stack,env);
}
int main()
{
    char value[10] = "test\n";
    axutil_env_t *env = cut_setup_env("Stack");
	CUT_ASSERT(env != NULL);
	if (env) {
        test_stack(env,value);
        axutil_env_free(env);
    }
    CUT_RETURN_ON_FAILURE(-1);
    return 0;
}

