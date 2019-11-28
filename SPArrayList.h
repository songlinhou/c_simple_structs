//
// Created by MacBook on 2019/11/23.
//

#ifndef SIMPLECSTRUCTURES_SPARRAYLIST_H
#define SIMPLECSTRUCTURES_SPARRAYLIST_H
#include <stddef.h> // for size_t
enum SPType{
    CHAR,

    SIGNED_CHAR,
    UNSIGNED_CHAR,

    SHORT,
    SHORT_INT,
    SIGNED_SHORT,
    SIGNED_SHORT_INT,

    UNSIGNED_SHORT,
    UNSIGNED_SHORT_INT,

    INT,
    SIGNED,
    SIGNED_INT,

    UNSIGNED,
    UNSIGNED_INT,

    LONG,
    LONG_INT,

    SIGNED_LONG,
    SIGNED_LONG_INT,

    LONG_LONG,
    LONG_LONG_INT,

    SIGNED_LONG_LONG,
    SIGNED_LONG_LONG_INT,

    FLOAT,
    DOUBLE,
    LONG_DOUBLE,

    STRUCT,
    POINTER,

    CHAR_ARRAY
};

struct SPArrayList{
    long* __contents;
    int __allcLength;
    int count;
    void * (*get)(struct SPArrayList* self, int index);
    void (*add)(struct SPArrayList* self, void* data);
    int (*contain)(struct SPArrayList* self, void* data);
    int (*indexOf)(struct SPArrayList* self, void* data);
    enum SPType __dataType;
};

extern const struct SPArrayListClass {
    struct SPArrayList* (*newArrayList)();
} /*ListProxy*/ SPArrayListCreator;


#endif //SIMPLECSTRUCTURES_SPARRAYLIST_H
