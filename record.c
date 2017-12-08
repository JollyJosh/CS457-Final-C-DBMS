//
// Created by Josh Collins on 12/7/17.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "record.h"

Record *newEmptyRecord(void)    {
    Record *r = malloc(sizeof(Record));
    //Memory Check
    if(r == NULL)   {
        printf("Memory Allocation Failure for New Record Type.");
    }

    r->docid = 0;
    r->sysid = 0;
    r->firstAtt = NULL;
    r->nextVersion = NULL;
    r->nextRecord = NULL;
    r->vn = 0;

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
    r->nextRecord = NULL;
    r->firstAtt = NULL;

    return r;
}

void setRecordVersion(Record *r, int ver)   {
    r->vn = ver;
}

Record *insertNextRecord(Record *head, Record *toBeAdded, Record *prev, Record *start)   {
    /* This function is what maintains the list of top level records.
     * A couple of things to note about this function.
     * The first check is to see if it finds a match on doc id
     * if so it increases the version and supplements itself as the new top level record (make for easier printing
     * later. Also checks for no match and appends at the end if not.
     */

    if(prev == NULL)    {
        start = head;
    }

    //Found a match for docID
    if(head->docid == toBeAdded->docid) {
        //Update version
        setRecordVersion(toBeAdded, head->vn + 1);
        toBeAdded->nextVersion = head;
        toBeAdded->nextRecord = head->nextRecord;
        //Check to see if this is the first record if so update head (in main) if not set prev pointer
        if(prev == NULL)    {
            start = toBeAdded;
        }
        else    {
            prev->nextRecord = toBeAdded;
        }
        return start;
    }

    //Ran out of records with no match; add to end of list
    if(head->nextRecord == NULL)    {
        head->nextRecord = toBeAdded;
        return start;
    }

    //This was neither the last record or a match; recur down list
    return insertNextRecord(head->nextRecord, toBeAdded, head, start);
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

void printRecord(Record *r) {
    /* This function will print a record as well as all of the current attributes,
     * that that record contains.
     */

    RecordAttribute *curr = r->firstAtt;

    //Print the record's data
    printf("DocID: %i, SysID: %i, Version Number: %i \n", r->docid, r->sysid, r->vn);

    //Loop through the attributes list and print its data
    while(curr != NULL) {
        printf("    Attribute Name: %s, Attribute Value: %i \n", curr->name, curr->value);
        curr = curr->next;
    }

}

void printRecordList(Record *head)  {
    /* This function will print the entire list of records from the beginning record to the
     * end of the list. Meaning if the first record is passed, it will print all the records in the
     * list, if the second is passed it will be from that record on by looping through the version list.
     */

    while(head != NULL) {
        printVersionList(head);
        head = head->nextRecord;
    }

}

void printVersionList(Record *first)    {
    /* This function will print the entire version list of a head version pointer
     */

    while(first != NULL)    {
        printRecord(first);
        printf("\n");
        first = first->nextVersion;
    }

}


