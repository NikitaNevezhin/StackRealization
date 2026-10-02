#ifndef STACK_CPP

#define STACK_CPP

#define STACK_DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>


#include "ErrorProcessor.cpp"
#include "ASSERT_STACK_OK.h"

#ifdef STACK_DEBUG

#define ON_DEBUG(...) __VA_ARGS__

#define STACK_INIT(stk, capacity, err_status) StackInit(stk, capacity, err_status, __FILE__, #stk, __LINE__)

#else

#define ON_DEBUG(...)

#define STACK_INIT(stk, capacity, err_status) StackInit(stk, capacity, err_status)

#endif

#define POIZON NAN

#define STRUCT_LEFT_CANARY  0xDEDDEDDED
#define STRUCT_RIGHT_CANARY 0xEDAEDAEDA

#define DATA_LEFT_CANARY  1776.2076
#define DATA_RIGHT_CANARY -2012.1231

#define STACK_DUMP(stk, err_status) StackDump(stk, err_status, __FILE__, __LINE__, __func__)  

typedef double stack_elem_t;

struct stack_t 
{
    unsigned long long left_canary;

    stack_elem_t* data;
    int size;
    int capacity;

    ON_DEBUG
    (
        const char* file; 
        const char* name; 
        int line;
    )

    unsigned long long right_canary;
}; 

enum RESIZE_DIRECTIONS
{
    UP,
    DOWN
};


void             StackInit        (stack_t* stk, int capacity, int* err_status ON_DEBUG(, const char* file, const char* name, int line));

void             PrintStackData   (stack_t* stk);

void             StackDump        (stack_t* stk, int err_status, const char* file, int line, const char* func);

int              StackVerify      (stack_t* stk);

void             StackResize      (stack_t* stk, int* err_status, int direction);

void             StackPush        (stack_t* stk, stack_elem_t value, int* err_status);

stack_elem_t     StackPop         (stack_t* stk, int* err_status);

void             StackDestroy     (stack_t* stk, int* err_status);


void StackInit(stack_t* stk, int capacity, int* err_status ON_DEBUG(, const char* file, const char* name, int line))
{
    assert(stk);

    if (capacity <= 0)
    {
        *err_status = NON_POSITIVE_CAPACITY;
        return;
    } 

    stk->left_canary = STRUCT_LEFT_CANARY;
    stk->right_canary = STRUCT_RIGHT_CANARY;

    stack_elem_t* given_memory = (stack_elem_t*)malloc((capacity + 2) * sizeof(stack_elem_t)); // +2 - takes places for two canaries

    if (given_memory == NULL)
    {
        *err_status = CALLOC_FAILURE;
        return;
    }

    given_memory[0] = DATA_LEFT_CANARY;
    
    stk->data = given_memory + 1; // skipping canary to the useful info
    stk->size = 0;
    stk->capacity = capacity;

    for (int i = 0; i < capacity; i++) 
    {
        stk->data[i] = POIZON;
    }

    stk->data[capacity] = DATA_RIGHT_CANARY;

    ON_DEBUG(stk->file = file);
    ON_DEBUG(stk->name = name);
    ON_DEBUG(stk->line = line);

    ASSERT_STACK_OK(stk);

    *err_status = OKAY;
    return;
}

void PrintStackData(stack_t* stk)  // this function is used in StackDump. Thats why we dont check the status of stk - we want to see elements anyways
{
    if (stk == NULL)
    {
        printf(RED "Cannot print data from NULL stack\n" RESET);
        return;
    }

    else if (stk->data == NULL)
    {
        printf("NULL data\n");
        return;
    }

    printf("    {\n");

    for (int i = 0; i < stk->capacity; i++)
    {
        if (i < stk->size)
            printf(GREEN "       *[%d] = %lg\n" RESET, i, stk->data[i]);

        else
        {
            if (isnan((float)stk->data[i]))  // conversion to float to escape [-Wconversion] warning (isnan() converts its argument to float)
                printf(RED "        [%d] = %lg [POIZON]\n" RESET, i, stk->data[i]);
            
            else
                printf(YELLOW "        [%d] = %lg [UNKNOWN]\n" RESET, i, stk->data[i]);
        }
    }

    printf("    }\n");
}

void StackDump(stack_t* stk, int err_status, const char* file, int line, const char* func)
{   
    printf( "------------StackDump----------------\n");
    printf("StackDump was called in %s:%d in function %s\n", file, line, func);

    if (err_status == STACK_NULL || stk == NULL) 
    {
        printf(RED "Stack pointer is NULL!\n" RESET);
        printf("-------------------------------------\n");
        return;
    }
    
    #ifdef STACK_DEBUG
    printf("stack_t \"%s\" initialized in %s:%d\n", stk->name, stk->file, stk->line); // debug info we only have in debug mode
    #endif

    printf("err_status = %s\n", GetErrorString(err_status));

    if (err_status == STACK_NULL)
        return;

    printf("Struct canaries:\n");
    printf("    Left:  %#llX (expected %#llX)\n", stk->left_canary, STRUCT_LEFT_CANARY);
    printf("    Right: %#llX (expected %#llX)\n", stk->right_canary, STRUCT_RIGHT_CANARY);

    printf("    Size:      %d\n", stk->size);
    printf("    Capacity:  %d\n", stk->capacity);

    printf("    data [" GREEN "%p" RESET "]\n", stk->data);
    printf("    data canaries:\n");

    if (stk->data != NULL)
    {
        printf("        Left:  %lf (expected %lf)\n", stk->data[-1], DATA_LEFT_CANARY);
        printf("        Right: %lf (expected %lf)\n", stk->data[stk->capacity], DATA_RIGHT_CANARY);
    }

    else printf("       data is NULL, no canaries :( \n");

    PrintStackData(stk);

    printf("-------------------------------------\n");
}

int StackVerify(stack_t* stk)
{
    if (stk == NULL)
        return STACK_NULL;

    else if (stk->left_canary != STRUCT_LEFT_CANARY || stk->right_canary != STRUCT_RIGHT_CANARY)
        return STRUCT_CANARY_CHANGED;

    else if (!FloatEqual(stk->data[-1], DATA_LEFT_CANARY) || !FloatEqual(stk->data[stk->capacity], DATA_RIGHT_CANARY))
        return DATA_CANARY_CHANGED;

    else if (stk->data == NULL)
        return DATA_NULL;
    
    else if (stk->capacity <= 0)
        return NON_POSITIVE_CAPACITY;

    else if (stk->size < 0)
        return STACK_UNDERFLOW;

    else if (stk->size > stk->capacity)
        return STACK_OVERFLOW;

    return OKAY;
}

void StackResize(stack_t* stk,int* err_status, int direction)
{
    ASSERT_STACK_OK(stk);

    int new_capacity = stk->capacity;

    if (direction == UP)
        new_capacity *= 2;

    else if (direction == DOWN)
        new_capacity /= 2;

    if (new_capacity < 4) // in case we work with small stacks, we wouldn't like the capacity to fall less than 4
        new_capacity = 4;

    stack_elem_t* temp = (stack_elem_t*)realloc(stk->data - 1, (new_capacity + 2) * sizeof(stack_elem_t)); // -1 to get the pointer on the left canary

    if (temp == NULL)
    {
        *err_status = REALLOC_FAILURE;
        return;
    }

    stk->data = temp + 1; // skipping left canary to the useful info

    if (direction == UP)
    {
        for (int i = stk->capacity; i < new_capacity; i++)
            stk->data[i] = POIZON;
    }

    stk->capacity = new_capacity;
    stk->data[stk->capacity] = DATA_RIGHT_CANARY;

    ASSERT_STACK_OK(stk)

    *err_status = OKAY;
    return;
}

void StackPush(stack_t* stk, stack_elem_t value, int* err_status)
{
    ASSERT_STACK_OK(stk);

    if (stk->size == stk->capacity)
    {
        StackResize(stk, err_status, UP);
        ProcessError(*err_status);
    }

    stk->data[stk->size++] = value;

    ASSERT_STACK_OK(stk);

    *err_status = OKAY;
    return;
}

stack_elem_t StackPop(stack_t* stk, int* err_status)
{
    ASSERT_STACK_OK(stk);
    
    if (stk->size == 0)
    {
        *err_status = STACK_UNDERFLOW;
        return NAN;
    }

    stk->size--;
    stack_elem_t last_value = stk->data[stk->size];
    stk->data[stk->size] = POIZON;

    if (stk->size < stk->capacity / 4)
        StackResize(stk, err_status, DOWN);
    ProcessError(*err_status);

    ASSERT_STACK_OK(stk);

    *err_status = OKAY;
    return last_value;
}

void StackDestroy(stack_t* stk, int* err_status)
{
    if (stk == NULL)
    {
        *err_status = STACK_NULL;
        return;
    }

    else if (stk->data == NULL && stk->capacity == 0) // in case if stk is already destroyed
    {
        *err_status = OKAY;
        return;
    }

    ASSERT_STACK_OK(stk);

    if (stk->data != NULL)
    {
        free(stk->data - 1); // stk->data points on useful info but we have canary before. that's why -1
        stk->data = NULL;
    }

    stk->size = 0;
    stk->capacity = 0;

    *err_status = OKAY;
}

#endif
