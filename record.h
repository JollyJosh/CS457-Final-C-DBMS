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
Record *newRecordWithoutDoc(int, int);
void setDocID(Record *, int);
Record *insertAttribute(Record *, RecordAttribute *);
void printRecord(FILE *,Record *);
Record *insertNextRecord(Record *, Record *, Record *, Record *);
void printRecordList(FILE *,Record *);
void printVersionList(FILE *,Record *);
void setRecordVersion(Record *, int);
int countWithField(Record *,char *);
int recordHaveAttribute(Record *,char *);
int countWithFieldAll(Record *,char *);
int countWithFieldVers(Record *,int,char *);

#endif //FINAL_RECORD_H
