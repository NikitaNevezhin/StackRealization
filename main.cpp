#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <iostream>

#include "ErrorProcessor.cpp"
#include "Stack.cpp"

#define GET_NAME(var) #var

int main(void)
{   
    stack_t stk1 = {};
    int stk1_err_status = OKAY;

    StackInit(&stk1, 20, &stk1_err_status ON_DEBUG(, __FILE__, GET_NAME(stk1), __LINE__));
    ProcessError(stk1_err_status);
    ShowStack(&stk1, &stk1_err_status);
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

    // stk1.data = NULL;
    double x = StackPop(&stk1, &stk1_err_status);
    ProcessError(stk1_err_status);

    printf("x = %lg\n", x);

    ShowStack(&stk1, &stk1_err_status);
    ProcessError(stk1_err_status);

    StackDestroy(&stk1, &stk1_err_status);
    ProcessError(stk1_err_status);

    return EXIT_SUCCESS;
}

