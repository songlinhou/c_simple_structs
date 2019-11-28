//
// Created by MacBook on 2019/11/23.
//

#include "SPArrayList.h"
#include <stdlib.h>
#include <string.h>


int getDatatypeLength(enum SPType type){
    switch (type){
        case CHAR:
        case SIGNED_CHAR:
        case UNSIGNED_CHAR:
            return sizeof(char);
        case SHORT:
        case SHORT_INT:
        case SIGNED_SHORT:
        case SIGNED_SHORT_INT:
        case UNSIGNED_SHORT:
        case UNSIGNED_SHORT_INT:
            return sizeof(short);
        case INT:
        case SIGNED:
        case SIGNED_INT:
        case UNSIGNED:
        case UNSIGNED_INT:
            return sizeof(int);
        case LONG:
        case LONG_INT:
        case SIGNED_LONG:
        case SIGNED_LONG_INT:
            return sizeof(long);
        case LONG_LONG:
        case LONG_LONG_INT:
        case SIGNED_LONG_LONG:
        case SIGNED_LONG_LONG_INT:
            return sizeof(long long);
        case FLOAT:
            return sizeof(float);
        case DOUBLE:
            return sizeof(double);
        case LONG_DOUBLE:
            return sizeof(long double);
        //case STRUCT:
        case POINTER:
        default:
            return sizeof(long);
    };
}

static void SPArrayList_Add_Value(struct SPArrayList* list,void* data){
    list->count += 1;
    if(list->count > list->__allcLength){
        list->__allcLength *= 2;
        list->__contents = (long*)realloc((void*)list->__contents, list->__allcLength * sizeof(long));
    }
    list->__contents[list->count - 1] = (long)data;
}

static void* SPArrayList_Get_Value_By_Index(struct SPArrayList* list,int index){
    if(index < 0 || index >= list->count){
        return NULL;
    }
    return (void*)list->__contents[index];
}

static
int isItemInList(struct SPArrayList* list,long data){
    for(int i=0;i<list->count;i++){
        if(list->__contents[i] == data){
            return 1;
        }
    }
    return 0;
}

static
int isStringInList(struct SPArrayList* list,const char* data){
    for(int i=0;i<list->count;i++){
        char* str = (char*)list->__contents[i];
        if(strcmp(str,data) == 0){
            return 1;
        }
    }
    return 0;
}



static
int isInList(struct SPArrayList* list,void* data){
    if(list->__dataType == CHAR_ARRAY){
        return isStringInList(list,data);
    }
    return isItemInList(list,(long)data);
}

static
int indexOfStringInList(struct SPArrayList* list,const char* data){
    for(int i=0;i<list->count;i++){
        char* str = (char*)list->__contents[i];
        if(strcmp(str,data) == 0){
            return i;
        }
    }
    return -1;
}

static
int indexOfItemInList(struct SPArrayList* list,long item){
    for(int i=0;i<list->count;i++){
        long data = (long)list->__contents[i];
        if(data == item){
            return i;
        }
    }
    return -1;
}


static
int indexOf(struct SPArrayList* list,void* data){
    if(list->__dataType == CHAR_ARRAY){
        return indexOfStringInList(list,(char*)data);
    }
    return indexOfItemInList(list,(long)data);
}

static struct SPArrayList* createArrayList(enum SPType type){
    struct SPArrayList* list = (struct SPArrayList*)calloc(1, sizeof(struct SPArrayList));
    list->__allcLength = 5;
    list->__contents = (long*)calloc(list->__allcLength, sizeof(long));
    list->count = 0;
    list->__dataType = type;
    list->add = (void*)&SPArrayList_Add_Value;
    list->get = (void*)&SPArrayList_Get_Value_By_Index;
    list->contain = (void*)&isInList;
    list->indexOf = (void*)&indexOf;
    return list;
}



const struct SPArrayListClass  SPArrayListCreator = {
        .newArrayList = &createArrayList
};
