//
// Created by MacBook on 2019/11/27.
//

#ifndef SIMPLECSTRUCTURES_SPHASHMAP_H
#define SIMPLECSTRUCTURES_SPHASHMAP_H

#include "SPArrayList.h"

struct SPHashNode{
    long key;
    long val;
    char* str;
    struct SPHashNode *next;
};

struct SPHashMap{
    struct SPHashNode **__list;
    int __allcSize;
    enum SPType __keyType;
    void (*put)(struct SPHashMap* self, long key, long value);
    long (*get)(struct SPHashMap* self, long key);
    int (*hasKey)(struct SPHashMap* self, long key);
    struct SPArrayList* (*keys)(struct SPHashMap* self);
};

extern const struct SPHashMapClass {
    struct SPHashMap* (*newHashMap)();
} /*ListProxy*/ SPHashMapCreator;

#endif //SIMPLECSTRUCTURES_SPHASHMAP_H
