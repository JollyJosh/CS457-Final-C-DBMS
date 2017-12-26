//
// Created by Josh Collins on 12/7/17.
//

#ifndef FINAL_RECORDATTRIBUTE_H
#define FINAL_RECORDATTRIBUTE_H

typedef struct recordAttribute  {
    char *name;
    int value;
    struct recordAttribute *next;
} RecordAttribute;

RecordAttribute *newRecordAtt(char *, int);

#endif //FINAL_RECORDATTRIBUTE_H
