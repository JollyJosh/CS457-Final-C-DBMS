//
// Created by Josh Collins on 12/7/17.
//

#include "recordAttribute.h"
#include <stdio.h>
#include <stdlib.h>

RecordAttribute *newRecordAtt(char *nme, int val)   {
    RecordAttribute *r = malloc(sizeof(RecordAttribute));
    //Memory failure check
    if(r == NULL)   {
        printf("Memory Allocation Failure in malloc of RecordAttribute.");
    }

    r->name = nme;
    r->value = val;
    r->next = NULL;

    return r;
}



