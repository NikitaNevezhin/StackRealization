#ifndef ASSERT_STACK_OK_H

#define ASSERT_STACK_OK_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ErrorProcessor.cpp"
#include "Stack.cpp"
#include "PrintColor.h"

#define STACK_DUMP(stk)                                                                     \
    printf("stack_t \"%s\" initialized in %s:%d\n", stk->name, stk->file, stk->line);       \
    printf("\t{\n");                                                                        \
    printf("\t\tcapacity = %d\n", stk->capacity);                                           \
    printf("\t\tsize = %d\n", stk->size);                                                   \
    printf("\t\tdata [" GREEN "%p" RESET "]\n", stk->data);                                 \
    printf("\t\t{\n");                                                                      \
    if (stk->size < 0)                                                                      \
        printf("\t\t  No pushed elements\n");                                               \
    else if (stk->data == NULL)                                                             \
        printf("\t\t  NULL DATA\n");                                                        \
    else                                                                                    \
    {                                                                                       \
        for (int i = 0; i < stk->size; i++)                                                 \
            printf("\t\t  * [%d] = %lg\n", i, stk->data[i]);                                \
                                                                                            \
        for (int i = stk->size; i < stk->capacity; i++)                                     \
            printf("\t\t    [%d] = %lg\n", i, stk->data[i]);                                \
    }                                                                                       \
    printf("\t\t}\n");                                                                      \
    

    
#define ASSERT_STACK_OK(verify_status, stk)                                                 \
    if (verify_status != OKAY)                                                              \
    {                                                                                       \
        STACK_DUMP(stk);                                                                    \
        ProcessError(verify_status);                                                        \
    }                                                                                       \

#endif