#ifndef STACK_CPP

#define STACK_CPP

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <iostream>

#include "ErrorProcessor.cpp"
#include "ASSERT_STACK_OK.h"

struct stack_t 
{
    double* data;
    int size;
    int capacity;
};


void       StackInit        (stack_t* stk, int capacity, int* err_status);

void       ShowStack        (stack_t* stk, int* err_status);

int        StackVerify      (stack_t* stk);

void       ResizeUp         (stack_t* stk, int* err_status);

void       ResizeDown       (stack_t* stk, int* err_status);

void       StackPush        (stack_t* stk, double value, int* err_status);

double     StackPop         (stack_t* stk, int* err_status);

void       StackDestroy     (stack_t* stk, int* err_status);


void StackInit(stack_t* stk, int capacity, int* err_status)
{
    assert(stk);

    stk->data = (double*)calloc(capacity, sizeof(double));

    if (stk->data == NULL)
    {
        *err_status = CALLOC_FAILURE;
        return;
    }
    
    stk->size = 0;
    stk->capacity = capacity;

    ASSERT_STACK_OK(StackVerify(stk), stk);

    *err_status = OKAY;
    return;
}

void ShowStack(stack_t* stk, int* err_status)
{
    ASSERT_STACK_OK(StackVerify(stk), stk);

    printf("data = [" GREEN "%p" RESET "]\n", stk->data);
    printf("size = %d\n", stk->size);
    printf("capacity = %d\n", stk->capacity);

    *err_status = OKAY;
}

int StackVerify(stack_t* stk)
{
    assert(stk);

    if (stk->data == NULL)
        return DATA_NULL;
    
    else if (stk->capacity <= 0)
        return NON_POSITIVE_CAPACITY;

    else if (stk->size < 0)
        return STACK_UNDERFLOW;

    else if (stk->size > stk->capacity)
        return STACK_OVERFLOW;

    return OKAY;
}

void ResizeUp(stack_t* stk, int* err_status)
{
    ASSERT_STACK_OK(StackVerify(stk), stk);

    if (stk->size == stk->capacity)
    {
        double* temp = (double*)realloc(stk->data, stk->capacity * 2 * sizeof(double));

        if (temp == NULL)
        {
            *err_status = REALLOC_FAILURE;
            return;
        }

        stk->data = temp;
        stk->capacity *= 2;
        temp = NULL;
    }

    ASSERT_STACK_OK(StackVerify(stk), stk);
    
    *err_status = OKAY;
    return;
}

void ResizeDown(stack_t* stk, int* err_status)
{
    ASSERT_STACK_OK(StackVerify(stk), stk);

    if (stk->size > 0 && stk->size < stk->capacity / 4)
    {
        double* temp = (double*)realloc(stk->data, stk->capacity * sizeof(double) / 2);

        if (temp == NULL)
        {
            *err_status = REALLOC_FAILURE;
            return;
        }

        stk->data = temp;
        stk->capacity /= 2;
        temp = NULL;
    }

    ASSERT_STACK_OK(StackVerify(stk), stk);

    *err_status = OKAY;
    return;  
}

void StackPush(stack_t* stk, double value, int* err_status)
{
    ASSERT_STACK_OK(StackVerify(stk), stk);

    ResizeUp(stk, err_status);
    ProcessError(*err_status);

    stk->data[stk->size++] = value;

    ASSERT_STACK_OK(StackVerify(stk), stk);

    *err_status = OKAY;
    return;
}

double StackPop(stack_t* stk, int* err_status)
{
    ASSERT_STACK_OK(StackVerify(stk), stk);
    
    if (stk->size == 0)
    {
        *err_status = STACK_UNDERFLOW;
        return NAN;
    }

    stk->size--;
    double last_value = stk->data[stk->size];
    stk->data[stk->size] = NAN;

    ResizeDown(stk, err_status);
    ProcessError(*err_status);

    ASSERT_STACK_OK(StackVerify(stk), stk);

    *err_status = OKAY;
    return last_value;
}

void StackDestroy(stack_t* stk, int* err_status)
{
    ASSERT_STACK_OK(StackVerify(stk), stk);

    if (stk->data != NULL)
    {
        free(stk->data);
        stk->data = NULL;
    }

    stk->size = -1;
    stk->capacity = -1;
}

#endif
