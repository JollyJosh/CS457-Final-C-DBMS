//
// Created by Josh Collins on 12/7/17.
//

#ifndef FINAL_RECORD_H
#define FINAL_RECORD_H

#include "recordAttribute.h"

typedef struct record   {
    int vn;
    int sysid;
    int docid;
    struct record *nextVersion;
    RecordAttribute *firstAtt;
} Record;

Record *newEmptyRecord(void);
Record *newRecord(int, int, int);
Record *insertAttribute(Record *, RecordAttribute *);

#endif //FINAL_RECORD_H
