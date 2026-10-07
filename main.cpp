#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "ErrorProcessor.cpp"
#include "Stack.cpp"

#define GET_NAME(var) #var

int main(void)
{   
    stack_t stk1 = {};
    ERROR_STATUS stk1_err_status = OKAY;

    STACK_INIT(&stk1, 20, &stk1_err_status);
    ProcessError(stk1_err_status);

    STACK_DUMP(&stk1, stk1_err_status);
    ProcessError(stk1_err_status);

    for (int i = 0; i < 5; i++)
    {
        StackPush(&stk1, i, &stk1_err_status);
        ProcessError(stk1_err_status);
    }

    stk1.data = NULL;
    stk1.size = 100;
    stk1.left_canary = 0xB00B5;
    stack_elem_t x = StackPop(&stk1, &stk1_err_status);
    ProcessError(stk1_err_status);

    printf("x = %lg\n", x);

    STACK_DUMP(&stk1, stk1_err_status);
    ProcessError(stk1_err_status);

    StackDestroy(&stk1, &stk1_err_status);
    ProcessError(stk1_err_status);

    return EXIT_SUCCESS;
}