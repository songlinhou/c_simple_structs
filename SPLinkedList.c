#include "SPLinkedList.h"
#include <assert.h> // for assert
// #include <stddef.h> // for NULL, size_t, they are already included in list.h
#include <stdlib.h> // for calloc, free
#include <string.h> // for memcpy

// Using "static" prevents these functions from being exposed outside.

static void
destroy(struct SPLinkedList* self)
{
    for (struct Node* cur = self->head ; cur != NULL ;) {
        struct Node* next = cur->next;
        free(cur->data);
        free(cur);
        cur = next;
    }
    self->head = self->cursor = NULL;
}

static void
append(struct SPLinkedList* self, void* data, size_t size) {
    struct Node* n = (struct Node*)calloc(1, sizeof(struct Node));
    assert(n);

    n->next = NULL;
    n->data = calloc(1, size);
    assert(n->data);
    memcpy(n->data, data, size);

    if (!self->head) { // The list is empty.
        assert(!self->cursor); // cursor = head = NULL now.
        self->head = n;
    } else {
        assert(self->cursor);
        self->cursor->next = n;
    }
    self->cursor = n;
}

static void
prepend(struct SPLinkedList* self, void* data, size_t size) {
    struct Node* n = (struct Node*)calloc(1, sizeof(struct Node));
    assert(n);

    n->next = self->head;
    n->data = calloc(1, size);
    assert(n->data);
    memcpy(n->data, data, size);

    self->head = n;
    if(!self->cursor) { // The list is empty before inserting value.
        self->cursor = n;
    }
}

static void
traverse(struct SPLinkedList* self, Callback func)
{
    for (struct Node* cur = self->head ; cur != NULL ; cur = cur->next) {
        func(cur);
    }
}

static struct SPLinkedList
newLinkedList()
{
    return (struct SPLinkedList) {
            .head = NULL,
            .cursor = NULL,
            .destroy = (void*) &destroy,
            .append = (void*) &append,
            .prepend = (void*) &prepend,
            .traverse = (void*) &traverse
    };
}
/*ListProxy*/

const struct ListClass  ListCreator = {
        .newLinkedList = &newLinkedList,
};
