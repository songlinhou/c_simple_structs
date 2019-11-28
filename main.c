#include "SPArrayList.h"
#include "SPHashMap.h"
#include <stdio.h>    // for printf

#define class struct // fake class in c

int main() {
    int data_int[6] = { 11, 22, 33, 44, 55, 66 };
    float data_float[6] = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f };


    printf("\n------------- array list test 1-----------------\n");
    // save the value directly.

    class SPArrayList* intList = SPArrayListCreator.newArrayList(INT); // specify the stored
    intList->add(intList, (void*)data_int[0]);
    intList->add(intList, (void*)data_int[1]);
    intList->add(intList, (void*)data_int[2]);
    intList->add(intList, (void*)data_int[3]);

    for(int i=0; i < intList->count; i++){
        int value = (int)intList->get(intList, i);
        printf("\n value at index %d = %d\n",i,value);
    }

    printf("\n is 33 in the list? answer=%d",intList->contain(intList,(void*)33));
    printf("\nindex of %d is at pos %d",data_int[1],intList->indexOf(intList,(void*)data_int[1]));


    printf("\n------------- array list test 2-----------------\n");
    // save the pointer.
    class SPArrayList* floatList = SPArrayListCreator.newArrayList(FLOAT);
    floatList->add(floatList, &data_float[0]);
    floatList->add(floatList, &data_float[1]);
    floatList->add(floatList, &data_float[2]);
    floatList->add(floatList, &data_float[3]);

    for(int i=0; i < floatList->count; i++){
        float value = *((float *)floatList->get(floatList, i));
        printf("\n value at index %d = %f\n",i,value);
    }

    printf("\n------------- array list test 3-----------------\n");
    class SPArrayList* strList = SPArrayListCreator.newArrayList(CHAR_ARRAY);
    strList->add(strList,"this is first");
    strList->add(strList,"this is second");
    strList->add(strList,"this is third");
    strList->add(strList,"this is fourth");

    for(int i=0; i < strList->count; i++){
        char* value = (char *)strList->get(strList, i);
        printf("\n value at index %d = %s\n",i,value);
    }


    printf("\n------------- hashmap test 1-----------------\n");
    // example of using integers as keys
    class SPHashMap* intMap = SPHashMapCreator.newHashMap(INT); // specify the key type
    intMap->put(intMap,1,(long)"one");
    intMap->put(intMap,2,(long)"two");
    intMap->put(intMap,3,(long)"three");

    char* result = (char*)intMap->get(intMap,1);
    printf("\nresult=%s\n",result);

    class SPArrayList* intKeys = intMap->keys(intMap);
    for(int i=0;i < intKeys->count;i++){
        int key = (int)intKeys->get(intKeys,i);
        printf("\nkey=%d,value=%s\n",key,(char*)intMap->get(intMap,key));
    }

    printf("\n------------- hashmap test 2-----------------\n");
    // example of using char* as keys
    class SPHashMap* strMap = SPHashMapCreator.newHashMap(CHAR_ARRAY); // specify the key type
    strMap->put(strMap,(long)"one",1);
    strMap->put(strMap,(long)"two",2);
    strMap->put(strMap,(long)"three",3);
    strMap->put(strMap,(long)"four",4);

    int result2 = (int)strMap->get(strMap,(long)"one");
    printf("\nresult=%d\n",result2);

    class SPArrayList* strKeys = strMap->keys(strMap);
    for(int i=0;i < strKeys->count;i++){
        char* key = (char*)strKeys->get(strKeys,i);
        printf("\nkey=%s,value=%d\n",key,(int)strMap->get(strMap,(long)key));
    }
    return 0;
}