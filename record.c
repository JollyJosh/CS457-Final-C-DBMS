//
// Created by Josh Collins on 12/7/17.
//

#include <stdlib.h>
#include <stdio.h>
#include "record.h"

Record *newEmptyRecord(void)    {
    Record *r = malloc(sizeof(Record));
    //Memory Check
    if(r == NULL)   {
        printf("Memory Allocation Failure for New Record Type.");
    }

    r->docid = NULL;
    r->sysid = NULL;
    r->firstAtt = NULL;
    r->nextVersion = NULL;
    r->vn = NULL;

    return r;
}

Record *newRecord(int doc, int sys, int vNum) {
    Record *r = malloc(sizeof(Record));
    //Memory Check
    if(r == NULL)   {
        printf("Memory Allocation Failure for New Record Type.");
    }
    r->docid = doc;
    r->sysid = sys;
    r->vn = vNum;
    r->nextVersion = NULL;
    r->firstAtt = NULL;

    return r;
}

Record *insertAttribute(Record *r, RecordAttribute *att)    {
    /* This function checks to see if a record has any current attributes.
     * if it does, the function will add the attribute to the end of the list.
     * If not, the function will add it as the first attribute for that record.
     */

    RecordAttribute *curr = r->firstAtt;

    if(r->firstAtt == NULL) {
        //This record currently does not have any attributes
        r->firstAtt = att;
    }
    else    {
        //This record has at least one attribute already.
        while(curr->next != NULL)   {
            //Get to the end of the list
            curr = curr->next;
        }
        //Add the attribute at the end of the list.
        curr->next = att;
    }
}


