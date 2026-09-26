#ifndef ASSERT_STACK_OK_H

#define ASSERT_STACK_OK_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ErrorProcessor.cpp"
#include "Stack.cpp"

#define ASSERT_STACK_OK(verify_status, stk)                                                   \
    if (verify_status != OKAY)                                                                \
    {             \
        printf("data = [" GREEN "%p" RESET "]\n", stk->data);   \
        printf("size = %d\n", stk->size);\
        printf("capacity = %d\n", stk->capacity);                                                                    \
        ProcessError(verify_status); \
    } \

#endif