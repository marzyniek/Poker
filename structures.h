#include "constants.h"

#ifndef STRUCTURES_H
#define STRUCTURES_H

struct card {
    int value;
    int suit;
};

typedef enum
{
    INPUT_OK,
    INPUT_ERROR,
    INPUT_EOF
} process_output_value;

typedef void (*CompareFunctionPointer)(int *, int *, struct card *, int *);


#endif