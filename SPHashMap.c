//
// Created by MacBook on 2019/11/27.
//

#include "SPHashMap.h"
#include "SPArrayList.h"
#include <stdlib.h>
#include <string.h>



static
long hashCode(struct SPHashMap *t, long key){
    if(key<0)
        return -(key%t->__allcSize);
    return key%t->__allcSize;
}

static
void insertPointerToTable(struct SPHashMap *t, long key, long val){
    long pos = hashCode(t,key);
    struct SPHashNode *list = t->__list[pos];
    struct SPHashNode *newNode = (struct node*)malloc(sizeof(struct SPHashNode));
    struct SPHashNode *temp = list;
    while(temp){
        if(temp->key==key){
            temp->val = val;
            return;
        }
        temp = temp->next;
    }
    newNode->key = key;
    newNode->val = val;
    newNode->next = list;
    t->__list[pos] = newNode;
}

static
void insertStringToTable(struct SPHashMap *t, char* key, long val){
    long numberValue = 0;
    for(unsigned long i=0;i<strlen(key);i++){
        char c = *(key+i);
        numberValue += (long)c;
    }
    long pos = hashCode(t,numberValue);
    struct SPHashNode *list = t->__list[pos];
    struct SPHashNode *newNode = (struct SPHashNode*)malloc(sizeof(struct SPHashNode));
    struct SPHashNode *temp = list;
    while(temp){
        if(strcmp(temp->str,key) == 0){
            temp->val = val;
            return;
        }
        temp = temp->next;
    }
    newNode->key = (long)NULL;
    char* keyCopy = calloc(strlen(key)+1, sizeof(char));
    strcpy(keyCopy,key);
    newNode->str = keyCopy;
    newNode->val = val;
    newNode->next = list;
    t->__list[pos] = newNode;
}

static
long findValueByKey(struct SPHashMap *t, long key){
    long pos = hashCode(t,key);
    struct SPHashNode *list = t->__list[pos];
    struct SPHashNode *temp = list;
    while(temp){
        if(temp->key==key){
            return temp->val;
        }
        temp = temp->next;
    }
    return -1;
}

static
long findValueByString(struct SPHashMap *t, char* key){
    long numberValue = 0;
    for(unsigned long i=0;i<strlen(key);i++){
        char c = *(key+i);
        numberValue += (long)c;
    }
    long pos = hashCode(t,numberValue);
    struct SPHashNode *list = t->__list[pos];
    struct SPHashNode *temp = list;
    while(temp){
        char* tempKey = (char*)temp->str;
        if(strcmp(tempKey,key) == 0){
            return temp->val;
        }
        temp = temp->next;
    }
    return -1;
}

static
struct SPArrayList* allKeysInTable(struct SPHashMap *t){
    struct SPArrayList *output = SPArrayListCreator.newArrayList();
    for(int i=0;i<t->__allcSize;i++){
        struct SPHashNode *list = t->__list[i];
        struct SPHashNode *temp = list;
        while (temp){
            output->add(output,(void*)temp->key);
            temp = temp->next;
        }
    }
    return output;
}

static
struct SPArrayList* allStringsInTable(struct SPHashMap *t){
    struct SPArrayList* output = SPArrayListCreator.newArrayList();
    for(int i=0;i<t->__allcSize;i++){
        struct SPHashNode *list = t->__list[i];
        struct SPHashNode *temp = list;
        while (temp){
            if(temp->key == (long)NULL){
                output->add(output,(void*)temp->str);
            }
            temp = temp->next;
        }
    }
    return output;
}

static
int containKeyInTable(struct SPHashMap *t, long key){
    long pos = hashCode(t,key);
    struct SPHashNode *list = t->__list[pos];
    struct SPHashNode *temp = list;
    while(temp){
        if(temp->key==key){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

static
int containStrInTable(struct SPHashMap *t, char* key){
    long numberValue = 0;
    for(unsigned long i=0;i<strlen(key);i++){
        char c = *(key+i);
        numberValue += (long)c;
    }
    long pos = hashCode(t,numberValue);
    struct SPHashNode *list = t->__list[pos];
    struct SPHashNode *temp = list;
    while(temp){
        char* tempKey = temp->str;
        if(strcmp(tempKey,key) == 0){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

static
void putKeyValuePair(struct SPHashMap *map,long key, long value){
    enum SPType keyType = map->__keyType;
    if(keyType == CHAR_ARRAY){
        insertStringToTable(map,(char*)key,value);
    }
    else{
        insertPointerToTable(map,key,value);
    }
}

static
long getValueFromKey(struct SPHashMap *map,long key){
    enum SPType keyType = map->__keyType;
    if(keyType == CHAR_ARRAY){
        return findValueByString(map,(char*)key);
    }
    return findValueByKey(map,key);
}

static
int hasKeyInMap(struct SPHashMap *map,long key){
    enum SPType keyType = map->__keyType;
    if(keyType == CHAR_ARRAY){
        return containStrInTable(map,(char*)key);
    }
    return containKeyInTable(map,key);
}

static
struct SPArrayList* getAllKeysInMap(struct SPHashMap *map){
    enum SPType keyType = map->__keyType;
    if(keyType == CHAR_ARRAY){
        return allStringsInTable(map);
    }
    return allKeysInTable(map);
}

static
struct SPHashMap *createTable(enum SPType keyType){
    struct SPHashMap *t = (struct SPHashMap*)malloc(sizeof(struct SPHashMap));
    int size = 100;
    t->__keyType = keyType;
    t->__allcSize = size;
    t->__list = (struct SPHashNode**)malloc(sizeof(struct SPHashNode*)*size);
    int i;
    for(i=0;i<size;i++)
        t->__list[i] = NULL;
    t->put = &putKeyValuePair;
    t->get = &getValueFromKey;
    t->hasKey = &hasKeyInMap;
    t->keys = &getAllKeysInMap;
    return t;
}

const struct SPHashMapClass  SPHashMapCreator = {
        .newHashMap = &createTable
};