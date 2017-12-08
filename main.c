#include <stdio.h>
#include "recordAttribute.h"
#include "record.h"

int main() {


//  If you want to see the ugliest debug code ever, look no further!

    int vn = 1, sysid = 0, docid = 0;

    //Record 1
    RecordAttribute *attribute1 = newRecordAtt("Badge", 1234);
    Record *record1 = newRecord(++docid, ++sysid, vn);
    insertAttribute(record1, attribute1);
    RecordAttribute *attribute2 = newRecordAtt("Phone", 865);
    insertAttribute(record1, attribute2);
    RecordAttribute *attribute3 = newRecordAtt("Badge", 9876);
    insertAttribute(record1, attribute3);
    printRecord(record1);

    Record *head = record1;

    //Record 2
    RecordAttribute *attribute11 = newRecordAtt("Area", 341);
    RecordAttribute *attribute12 = newRecordAtt("Key", 82471);
    Record *record2 = newRecord(++docid, ++sysid, vn);
    insertAttribute(record2, attribute11);
    insertAttribute(record2, attribute12);
    printf("\n");
    printRecord(record2);

    //Record 3
    RecordAttribute *attribute111 = newRecordAtt("Num", 412);
    RecordAttribute *attribute122 = newRecordAtt("Badge", 444);
    Record *record3 = newRecord(docid, ++sysid, vn);
    insertAttribute(record3, attribute111);
    insertAttribute(record3, attribute122);
    printf("\n");
    printRecord(record3);

    //Record 4
    RecordAttribute *attribute1111 = newRecordAtt("Num", 512);
    RecordAttribute *attribute1222 = newRecordAtt("Badge", 829);
    Record *record4 = newRecord(docid, ++sysid, vn);
    insertAttribute(record4, attribute1111);
    insertAttribute(record4, attribute1222);
    printf("\n");
    printRecord(record4);

    //Record 5
    RecordAttribute *attribute11111 = newRecordAtt("Num", 112);
    RecordAttribute *attribute12222 = newRecordAtt("Badge", 812443);
    Record *record5 = newRecord(1, ++sysid, vn);
    insertAttribute(record5, attribute11111);
    insertAttribute(record5, attribute12222);
    printf("\n");
    printRecord(record5);

    //Record 6
    RecordAttribute *attribute111111 = newRecordAtt("Num", 173553);
    RecordAttribute *attribute122222 = newRecordAtt("Badge", 851443);
    Record *record6 = newRecord(1, ++sysid, vn);
    insertAttribute(record6, attribute111111);
    insertAttribute(record6, attribute122222);
    printf("\n");
    printRecord(record6);

    //Insert the records and make sure to reset the head each update

    head = insertNextRecord(head, record2, NULL, NULL);
    head = insertNextRecord(head, record3, NULL, NULL);
    head = insertNextRecord(head, record4, NULL, NULL);
    head = insertNextRecord(head, record5, NULL, NULL);
    head = insertNextRecord(head, record6, NULL, NULL);

    printf("\n =========================== \n");
    printRecordList(head);


    return 0;
}