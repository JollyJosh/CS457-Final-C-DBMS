#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "recordAttribute.h"
#include "record.h"

int main() {


/*
 +    This is the code to read in the data, conduct the versioning of multiple records,
 +    and create a three deminsional linked list cube structure that acts as a list of
 +    unique records, which have a list of versions with the same docID, which has a list
 +    of attribute nodes attached to it.
 +
 +    ================================ R E A D  I N  D A T A =============================
 +*/

    FILE *fp = fopen("/Users/joshcollins/cs457/Final/data.txt", "r");

    /* Variables for setting ID's and VN's */
    int vn = 1, sysID = 1;

    if(fp == NULL)  {
        fprintf(stderr, "File could not be open for reading.");
        exit(1);
    }

    char ch;
    Record *head;

    while(!(feof(fp))) {

        Record *nuRecord = newRecordWithoutDoc(sysID++, vn);

        while (!(feof(fp))) {
            ch = getc(fp);
            if (ch == '\n') {
                break;
            }
            ungetc(ch, fp);

            char *attributeName = malloc(sizeof(char) * 250);
            char attributeValue[250] = {0};
            int i1 = 0, i2 = 0;

            while (!(feof(fp))) {
                ch = getc(fp);
                if (ch == ':') {
                    break;
                }
                attributeName[i1++] = ch;
            }

            while (!(feof(fp))) {
                ch = getc(fp);
                if (ch == ' ') {
                    break;
                }
                if (ch == '\n') {
                    ungetc(ch, fp);
                    break;
                }
                attributeValue[i2++] = ch;
            }

            int attributeNum;
            //Converts a char array to its int value
            sscanf(attributeValue, "%d", &attributeNum);

            //----Debug------
            //printf("%s \n", attributeName);
            //printf("%d \n\n", attributeNum);

            if (strcmp(attributeName, "DocID") == 0) {
                //This is a docID
                setDocID(nuRecord, attributeNum);
//                printRecord(nuRecord);
            } else {
                //This is an attribute
                RecordAttribute *ra = newRecordAtt(attributeName, attributeNum);
                insertAttribute(nuRecord, ra);
            }


        }

        if (head == NULL) {
            //Need to make head
            head = nuRecord;
        } else {
            //Head already exists
            head = insertNextRecord(head, nuRecord, NULL, NULL);
        }

    }

    printRecordList(head);


    fclose(fp);
/*
    ================================ E N D  R E A D=============================
*/





    return 0;
}



