//
// Created by Josh Collins on 12/7/17.
//

#ifndef FINAL_RECORD_H
#define FINAL_RECORD_H

#include "recordAttribute.h"
#include <stdbool.h>


typedef struct record   {
    int vn;
    int sysid;
    int docid;
    struct record *nextVersion;
    struct record *nextRecord;
    RecordAttribute *firstAtt;
} Record;

Record *newEmptyRecord(void);
Record *newRecord(int, int, int);
Record *insertAttribute(Record *, RecordAttribute *);
void printRecord(Record *);
Record *insertNextRecord(Record *, Record *, Record *, Record *);
bool printRecordList(Record *);
void setRecordVersion(Record *, int);

#endif //FINAL_RECORD_H
