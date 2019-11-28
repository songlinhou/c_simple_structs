//
// Created by MacBook on 2019/11/23.
//

#ifndef SIMPLECSTRUCTURES_SPLINKEDLIST_H
#define SIMPLECSTRUCTURES_SPLINKEDLIST_H

#ifndef LIST_H
#define LIST_H

#include <stddef.h> // for size_t

struct Node {
    void* data; // Any data type can be stored in this node
    struct Node* next;
};

typedef void (*Callback)(struct Node* node);
struct SPLinkedList {
    struct Node* head;
    struct Node* cursor;

    void (* const destroy)(struct SPLinkedList* self);
    void (* const append)(struct SPLinkedList* self, void* data, size_t size);
    void (* const prepend)(struct SPLinkedList* self, void* data, size_t size);
    void (* const traverse)(struct SPLinkedList* self, Callback func);
};

extern const struct ListClass {
    struct SPLinkedList (*newLinkedList)();
} /*ListProxy*/ ListCreator;

#endif // LIST_H

#endif //SIMPLECSTRUCTURES_SPLINKEDLIST_H
