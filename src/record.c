//
// Created by Josh Collins on 12/7/17.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <memory.h>
#include "record.h"

Record *newRecordWithoutDoc(int sys,int vNum)   {
    Record *r = malloc(sizeof(Record));

    //Memory Check
    if(r == NULL)   {
        printf("Memory Allocation Failure for New Record Type.");
    }

    r->docid = 0;
    r->sysid = sys;
    r->vn = vNum;
    r->nextRecord = NULL;
    r->nextVersion = NULL;
    r->firstAtt = NULL;

    return r;
}

void setDocID(Record *r, int docID)    {
    r->docid = docID;
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

RecordAttribute *insertAttribute(Record *r, RecordAttribute *att)    {
    /* This function checks to see if a record has any current attributes.
     * if it does, the function will add the attribute to the end of the list.
     * If not, the function will add it as the first attribute for that record.
     */

    RecordAttribute *curr = r->firstAtt;

    if(r->firstAtt == NULL) {
        //This record currently does not have any attributes
        r->firstAtt = att;
        return r->firstAtt;
    }
    else    {
        //This record has at least one attribute already.
        while(curr->next != NULL)   {
            //Get to the end of the list
            curr = curr->next;
        }
        //Add the attribute at the end of the list.
        curr->next = att;
        return curr->next;
    }

}

void printRecord(FILE *fp, Record *r) {
    /* This function will print a record as well as all of the current attributes,
     * that that record contains.
     */

    RecordAttribute *curr = r->firstAtt;

    //Print the record's data
//    printf("DocID: %i, SysID: %i, Version Number: %i \n", r->docid, r->sysid, r->vn);
    fprintf(fp, "vn: %i sysid: %i DocID: %i ", r->vn, r->sysid, r->docid);

    //Loop through the attributes list and print its data
    while(curr != NULL) {
        fprintf(fp, "%s: %i ", curr->name, curr->value);
        curr = curr->next;
    }

}

void printRecordList(FILE *fp, Record *head)  {
    /* This function will print the entire list of records from the beginning record to the
     * end of the list. Meaning if the first record is passed, it will print all the records in the
     * list, if the second is passed it will be from that record on by looping through the version list.
     */

    while(head != NULL) {
        printVersionList(fp, head);
        head = head->nextRecord;
    }

}

void printVersionList(FILE *fp, Record *first)    {
    /* This function will print the entire version list of a head version pointer
     */

    while(first != NULL)    {
        printRecord(fp, first);
        fprintf(fp, "\n");
        first = first->nextVersion;
    }

}

int countWithField(Record *head,char *field)    {
    int count = 0;

    while(head != NULL) {
        if(recordHaveAttribute(head, field))    {
            count++;
            head = head->nextRecord;
        }
        else {
            head = head->nextRecord;
        }
    }

    return count;
}

int recordHaveAttribute(Record *r,char *field)  {


    while(r->firstAtt != NULL) {
        if (strcmp(r->firstAtt->name, field) == 0) {
            return 1;
        } else {
            r->firstAtt = r->firstAtt->next;
        }
    }

    return 0;

}

int countWithFieldAll(Record *head,char *field) {
    int count = 0;

    Record *currRoot = head;

    while(head != NULL) {

        while(currRoot != NULL) {
            if(recordHaveAttribute(currRoot, field))    {
                count++;
                currRoot = currRoot->nextVersion;
            }
            else    {
                currRoot = currRoot->nextVersion;
            }
        }
        head = head->nextRecord;
        currRoot = head;
    }

    return count;
}

int countWithFieldVers(Record *head,int ver, char *field)   {
    int count = 0;

    Record *currRoot = head;

    while(head != NULL) {

        while(currRoot != NULL) {

            if(currRoot->vn != ver) {
                currRoot = currRoot->nextVersion;
            }

            else    {
                if(recordHaveAttribute(currRoot, field))    {
                    count++;
                    break;
                }
                currRoot = currRoot->nextVersion;
            }
        }

        head = head->nextRecord;
        currRoot = head;
    }

    return count;
}


