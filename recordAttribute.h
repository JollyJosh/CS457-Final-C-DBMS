//
// Created by Josh Collins on 12/7/17.
//

#ifndef FINAL_RECORDATTRIBUTE_H
#define FINAL_RECORDATTRIBUTE_H

typedef struct recordAttribute  {
    char * name;
    int value;
    struct recordAttribute *next;
} RecordAttribute;

RecordAttribute *newEmptyRecordAtt(void);
RecordAttribute *newRecordAtt(char *, int);
void setRecordAttNext(RecordAttribute *, RecordAttribute *);
void setRecordAttName(RecordAttribute *,char *);
void setRecordAttVal(RecordAttribute *, int);

#endif //FINAL_RECORDATTRIBUTE_H
