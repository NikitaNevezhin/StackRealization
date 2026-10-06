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

    StackDump(&stk1, stk1_err_status, __FILE__, __LINE__, __func__);
    ProcessError(stk1_err_status);

    for (int i = 0; i < 5; i++)
    {
        StackPush(&stk1, i, &stk1_err_status);
        ProcessError(stk1_err_status);
    }

    // for (int i = 0; i < 5; i++)
    // {
    //    StackPop(&stk1, &stk1_err_status);
    //    ProcessError(stk1_err_status);
    // }

    // stk1.size = 100;
    stack_elem_t x = StackPop(&stk1, &stk1_err_status);
    ProcessError(stk1_err_status);

    printf("x = %lg\n", x);

    StackDump(&stk1, stk1_err_status, __FILE__, __LINE__, __func__);
    ProcessError(stk1_err_status);

    StackDestroy(&stk1, &stk1_err_status);
    ProcessError(stk1_err_status);

    return EXIT_SUCCESS;
}