#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>
#include <stdio.h>

#define DList_Node_Struct(name, data_type) \
typedef struct dlist_##name##_node { \
    data_type data; \
    struct dlist_##name##_node* next; \
    struct dlist_##name##_node* prev; \
} dlist_##name##_name;

#define DList_Node_New(name, data_type) \
dlist_##name##_node* dlist_##name##_node_new(data_type data, dlist_##name##_node* next, dlist_##name##_node* prev) \
{ \
    dlist_##name##_node* self = malloc(sizeof(dlist_##name##_node)); \
    self->data = data; \
    self->next = next; \
    self->prev = prev; \
    return self; \
}

#define DList_Node_Free(name, data_type) \
void dlist_##name##_node_free(dlist_##name##_node* self) \
{ \
    self->next = NULL; \
    self->prev = NULL; \
    free(self); \
    self = NULL; \
} \

#define DList_Node_Free_Chain_After(name, data_type) \
void dlist_##name##_node_free_chain_after(dslist_node_##name* node, size_t* count) \
{ \
    if(node->next) { dlist_##name##_node_free_chain(node->next, count); } \
    dlist_##name##_node_free(node); \
    if(count) { *count += 1; } \
} \

#define DList_Struct(name, data_type) \
typedef struct dlist_##name { \
    dlist_##name##_node* head; \
    dlist_##name##_node* tail; \
    size_t type_size; \
    size_t size; \
} dlist_##name;

#define DList_New(name, data_type) \
dlist_##name dlist_##name##_new() \
{ \
    dlist_##name self; \
    list.size = 0; \
    list.type_size = sizeof(data_type); \
    list.head = list.tail = &dlist_##name##_node##_new_uninit(NULL, NULL) \
    return list; \
}

#define DList_Insert_End(name, data_type) \
void dlist_##name##_insert_end() \
{ \
}

#define DList_Insert_Front(name, data_type) \
void dlist_##name##_insert_front() \
{ \
}


#define DList_Declare(name, data_type) \
    DList_Node_Struct(name, data_type) \
    DList_Struct(name, data_type) \
    DList_Node_New(name, data_type) \
    DList_Node_Free_Chain_After(name, data_type) \
    DList_New(name, data_type) \

#endif // DLIST_H