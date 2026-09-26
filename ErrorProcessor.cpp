#ifndef ERROR_PROCESSOR_CPP

#define ERROR_PROCESSOR_CPP

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <iostream>

#include "PrintColor.h"

void    ProcessError   (int ErrorStatus);

enum ERROR_STATUSES
{
    OKAY = 1,
    CALLOC_FAILURE = -1,
    REALLOC_FAILURE = -2,
    STACK_OVERFLOW = -3,
    STACK_UNDERFLOW = -4,
    DATA_NULL = -5,
    NON_POSITIVE_CAPACITY = -6
};

void ProcessError(int err_status)
{
    switch (err_status)
    {  
    case OKAY:
        break;
    
    case CALLOC_FAILURE:
        printf(RED "Could not allocate memory with calloc\n" RESET);
        abort();
        break;

    case REALLOC_FAILURE:
        printf(RED "Could not reallocate memory with realloc\n" RESET);
        abort();
        break;        
    
    case STACK_OVERFLOW:
        printf(RED "StackOverFlowError\n" RESET);
        abort();
        break;

    case STACK_UNDERFLOW:
        printf(RED "StackUnderFlowError\n" RESET);
        abort();
        break;

    case DATA_NULL:
        printf(RED "Stack data is NULL pointer!\n" RESET);
        abort();
        break;

    case NON_POSITIVE_CAPACITY:
        printf(RED "Stack capacity is not positive\n" RESET);
        abort();
    
    default:
        printf(RED "Unknow error! You are seriously fucked up, man\n" RESET);
    }
}

#endif

