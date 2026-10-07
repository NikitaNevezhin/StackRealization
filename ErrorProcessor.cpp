#ifndef ERROR_PROCESSOR_CPP

#define ERROR_PROCESSOR_CPP

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <iostream>

#include "PrintColor.h"

enum ERROR_STATUS
{
    OKAY = 0,
    CALLOC_FAILURE = 1,
    REALLOC_FAILURE = 1 << 1,
    STACK_OVERFLOW = 1 << 2,
    STACK_UNDERFLOW = 1 << 3,
    DATA_NULL = 1 << 4,
    NON_POSITIVE_CAPACITY = 1 << 5,
    STACK_NULL = 1 << 6,
    STRUCT_CANARY_CHANGED = 1 << 7,
    DATA_CANARY_CHANGED = 1 << 8
};

const char*     GetErrorString      (ERROR_STATUS err_status);

void            PrintError          (ERROR_STATUS err_status, ERROR_STATUS error, bool* first);

void            PrintAllErrors      (ERROR_STATUS err_status);

void            ProcessError        (ERROR_STATUS ErrorStatus);


const char* GetErrorString(ERROR_STATUS err_status) 
{
    switch (err_status) 
    {
        case STACK_NULL:            return RED "STACK_NULL" RESET;

        case OKAY:                  return GREEN "OKAY" RESET;

        case CALLOC_FAILURE:        return RED "CALLOC_FAILURE" RESET;

        case REALLOC_FAILURE:       return RED "REALLOC_FAILURE" RESET;

        case STACK_OVERFLOW:        return RED "STACK_OVERFLOW" RESET;

        case STACK_UNDERFLOW:       return RED "STACK_UNDERFLOW" RESET;

        case DATA_NULL:             return RED "DATA_NULL" RESET;

        case NON_POSITIVE_CAPACITY: return RED "NON_POSITIVE_CAPACITY" RESET;

        case STRUCT_CANARY_CHANGED: return RED "STRUCT_CANARY_CHANGED" RESET;

        case DATA_CANARY_CHANGED:   return RED "DATA_CANARY_CHANGED" RESET;

        default:                    return RED "You are seriously fucked up, man" RESET;
    }
}

void PrintError(ERROR_STATUS err_status, ERROR_STATUS error, bool* first)  // PrintAllErrors helper function
{
    if (err_status & error)
    {   
        if (*first)
            *first = false;
        
        else
            printf(RED " | " RESET);
        
        printf("%s", GetErrorString(error)); // %s was added as I had warning saying direct using of function in string is unsafe
    }

    return;
}

void PrintAllErrors(ERROR_STATUS err_status)
{
    if (err_status == OKAY)
    {
        printf(GREEN "Stack is OKAY\n" RESET);
        return;
    }

    bool first = true;

    PrintError(err_status, STACK_NULL, &first);
    PrintError(err_status, CALLOC_FAILURE, &first);
    PrintError(err_status, REALLOC_FAILURE, &first);
    PrintError(err_status, STACK_OVERFLOW, &first);
    PrintError(err_status, STACK_UNDERFLOW, &first);
    PrintError(err_status, DATA_NULL, &first);
    PrintError(err_status, NON_POSITIVE_CAPACITY, &first);
    PrintError(err_status, STRUCT_CANARY_CHANGED, &first);
    PrintError(err_status, DATA_CANARY_CHANGED, &first);

}

void ProcessError(ERROR_STATUS err_status)
{
    if (err_status == OKAY) return;
    if (err_status & STACK_NULL)            printf(RED "Error: Stack pointer is NULL\n" RESET);
    if (err_status & CALLOC_FAILURE)        printf(RED "Error: Could not allocate memory with calloc\n" RESET);
    if (err_status & REALLOC_FAILURE)       printf(RED "Error: Could not reallocate memory with realloc\n" RESET);
    if (err_status & STACK_OVERFLOW)        printf(RED "Error: StackOverFlowError\n" RESET);
    if (err_status & STACK_UNDERFLOW)       printf(RED "Error: StackUnderFlowError\n" RESET);
    if (err_status & DATA_NULL)             printf(RED "Error: Stack data is NULL pointer!\n" RESET);
    if (err_status & NON_POSITIVE_CAPACITY) printf(RED "Error: Stack capacity is not positive\n" RESET);
    if (err_status & STRUCT_CANARY_CHANGED) printf(RED "Error: Struct canary value is changed.\n" RESET);
    if (err_status & DATA_CANARY_CHANGED)   printf(RED "Error: Stack data canary value is changed.\n" RESET);

    return;
}

#endif