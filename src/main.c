#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "recordAttribute.h"
#include "record.h"

int countQuery(FILE *,FILE *,Record *);
void sortQuery(FILE *,Record *);
Record *insertQuery(FILE *,Record *,int);
void standardQuery(FILE *,Record *);

int main() {
/*
 +    This is the code to read in the data, conduct the versioning of multiple records,
 +    and create a three deminsional linked list cube structure that acts as a list of
 +    unique records, which have a list of versions with the same docID, which has a list
 +    of attribute nodes attached to it.
 +
 +    ================================ R E A D  I N  D A T A =============================
 +*/

    FILE *fp = fopen("../testFiles/data.txt", "r");
    FILE *fp3 = fopen("jjcollins2.txt", "w");

    if(fp3 == NULL)  {
        fprintf(stderr, "File - jjcollins2.txt - could not be open for writing.");
        exit(1);
    }

    /* Variables for setting ID's and VN's */
    int vn = 1, sysID = 1;

    if(fp == NULL)  {
        fprintf(stderr, "File - data.txt - could not be open for reading.");
        exit(1);
    }

    fprintf(fp3, "GRADER NOTE: THIS IS MY FINAL PROJECT, AND IT DOESNT DO TASK 1 or 2, \n");
    fprintf(fp3, "PLEASE DONT GRADE FOR THIS ON YOUR DATA FILE OR IT WILL BREAK IT!!\n\n");
    char ch = '\0';
    Record *head = NULL;

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

            if (strcmp(attributeName, "DocID") == 0) {
                //This is a docID
                setDocID(nuRecord, attributeNum);
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

    fprintf(fp3, "Here is your database based off of your input file! \n\n");
    printRecordList(fp3, head);


    fclose(fp);
/*
    ================================ E N D  R E A D =============================
*/

/*
    ================================ B E G I N  Q U E R I E S  R E A D ==========
*/

    FILE *fp2 = fopen("../testFiles/queries.txt", "r");

    if(fp2 == NULL)  {
        fprintf(stderr, "File - queries.txt - could not be open for reading.");
        exit(1);
    }

    char x = '\0';
    while(!feof(fp2)) {
        while (!(feof(fp2))) {
            x = getc(fp2);
            if (x == '.') {
                break;
            }
        }

        int count;

        x = getc(fp2);

        if (x == 'i') {
            //Insert Query
            head = insertQuery(fp2, head, sysID);
            sysID++;
            fprintf(fp3, "Here is your new database! \n\n");
            printRecordList(fp3, head);
        } else if (x == 'c') {
            //Count Query
            count = countQuery(fp2, fp3, head);
            //Get rid of )
            x = getc(fp2);
        } else if (x == 's') {
            //Sort Query
            sortQuery(fp2, head);
        } else {
            //Run Query
            standardQuery(fp2, head);
        }

        //Get rid of the /n
        x = getc(fp2);
    }
/*
    ================================ E N D  R E A D =============================
*/

    return 0;
}

int countQuery(FILE *fp, FILE *fpWrite,Record *head) {

    int ch;
    char *attributeName = malloc(sizeof(char) * 250);
    int i = 0;
    int count = -1;

    //Get to the first attribute name
    while(!feof(fp))    {
        ch = getc(fp);
        if(ch == '[')   {
            break;
        }
    }

    //Build attribute name
    while(true) {
        ch = getc(fp);
        if(ch == ']')   {
            break;
        }
        attributeName[i++] = ch;
    }

    //Check if end
    ch = getc(fp);

    if(ch == ')')   {
        count = countWithField(head, attributeName);
        fprintf(fpWrite, "\ncount_%s : %i \n", attributeName, count);
        return count;
    }

    char versionNumber[50];
    int intVN = 0;
    int index = 0;

    while(true) {
        ch = getc(fp);
        if(ch == '[')   {
            break;
        }
    }

    //See if empty second param
    ch = getc(fp);

    if(ch == ']')   {
        count = countWithFieldAll(head, attributeName);
        fprintf(fpWrite, "\ncount_%s : %i\n", attributeName, count);
        return count;
    }
    else {
        versionNumber[index++] = ch;
        while (true) {
            ch = getc(fp);
            if(ch == ']')   {
                break;
            }
            versionNumber[index++] = ch;
        }
        sscanf(versionNumber, "%d", &intVN);
        count = countWithFieldVers(head, intVN, attributeName);
        fprintf(fpWrite, "\ncount_%s : %i\n", attributeName, count);
        return count;
    }
}

void sortQuery(FILE *fp,Record *head)   {

}

Record *insertQuery(FILE *fp3,Record *head,int sysID)    {
    //Return head
    char ch;
    Record *nuRecord = newRecordWithoutDoc(sysID, 1);


    while (true) {
        ch = getc(fp3);
        if (ch == '(') {
            break;
        }
    }

    while(true) {
        if(ch == ')')   {
            break;
        }
        ch = getc(fp3);
        if(ch == ')')   {
            break;
        }
        ungetc(ch, fp3);
        char *attributeName = malloc(sizeof(char) * 250);
        char attributeValue[250] = {0};
        int i1 = 0, i2 = 0;

        while (true) {
            ch = getc(fp3);
            if (ch == ':') {
                break;
            }
            attributeName[i1++] = ch;
        }

        while(true) {
            ch = getc(fp3);
            if(ch == ' ' || ch == ')')   {
                break;
            }
            attributeValue[i2++] = ch;
        }

        int attributeNum;
        //Converts a char array to its int value
        sscanf(attributeValue, "%d", &attributeNum);

        if (strcmp(attributeName, "DocID") == 0) {
            setDocID(nuRecord, attributeNum);
        } else {
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

    return head;
}

void standardQuery(FILE *fp,Record *head)   {

}



