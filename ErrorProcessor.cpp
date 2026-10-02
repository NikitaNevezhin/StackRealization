#ifndef ERROR_PROCESSOR_CPP

#define ERROR_PROCESSOR_CPP

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <iostream>

#include "PrintColor.h"

const char*     GetErrorString      (int err_status);

void            ProcessError        (int ErrorStatus);

enum ERROR_STATUSES
{
    OKAY = 1,
    CALLOC_FAILURE = -1,
    REALLOC_FAILURE = -2,
    STACK_OVERFLOW = -3,
    STACK_UNDERFLOW = -4,
    DATA_NULL = -5,
    NON_POSITIVE_CAPACITY = -6,
    STACK_NULL = -7,
    STRUCT_CANARY_CHANGED = -8,
    DATA_CANARY_CHANGED = -9
};

const char* GetErrorString(int err_status) 
{
    switch (err_status) 
    {
        case OKAY:                  return "OKAY";

        case CALLOC_FAILURE:        return "CALLOC_FAILURE";

        case REALLOC_FAILURE:       return "REALLOC_FAILURE";

        case STACK_OVERFLOW:        return "STACK_OVERFLOW";

        case STACK_UNDERFLOW:       return "STACK_UNDERFLOW";

        case DATA_NULL:             return "DATA_NULL";

        case NON_POSITIVE_CAPACITY: return "NON_POSITIVE_CAPACITY";

        case STRUCT_CANARY_CHANGED: return "STRUCT_CANARY_CHANGED";

        case DATA_CANARY_CHANGED:   return "DATA_CANARY_CHANGED";

        default:                    return "You are seriously fucked up, man";
    }
}

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

    case STRUCT_CANARY_CHANGED:
        printf(RED "Struct canary value is changed.\n" RESET);
        abort();

    case DATA_CANARY_CHANGED:
        printf(RED "Stack data canary value is changed.\n" RESET);
        abort();
    
    default:
        printf(RED "Unknow error! You are seriously fucked up, man\n" RESET);
    }
}

#endif

