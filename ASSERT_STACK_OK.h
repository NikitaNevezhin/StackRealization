#ifndef ASSERT_STACK_OK_H

#define ASSERT_STACK_OK_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ErrorProcessor.cpp"
#include "FloatTools.cpp"
#include "Stack.cpp"
#include "PrintColor.h"

    
#define ASSERT_STACK_OK(stk)                                                                    \
    do                                                                                          \
    {                                                                                           \
        ERROR_STATUS stack_status = StackVerify(stk);                                                    \
        if (stack_status != OKAY)                                                               \
        {                                                                                       \
            STACK_DUMP(stk, stack_status);                                                      \
            ProcessError(stack_status);                                                         \
        }                                                                                       \
    } while (0);
    
// do-while construction was used in order to use ASSERT_STACK_OK twice. 
// Before there was a problem of stack_status redefinition
// Now I've learned that inside while and for construction we have our own local variables
// Which can only be viewed inside the construction
// So now when using ASSERT_STACK_OK twice we just create two while-local variables stack_status
// And they do not redefine each other. 
// Thank you, random dude from StackOverFlow, who had the same problem as me

#endif
