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
void dlist_##name##_node_free_chain_after(dlist_##name##_node* self, size_t* count) \
{ \
    if(self->next) { dlist_##name##_node_free_chain_after(self->next, count); } \
    dlist_##name##_node_free(self); \
    if(count) { *count += 1; } \
} \

#define DList_Node_Free_Chain_Before(name, data_type) \
void dlist_##name##_node_free_chain_before(dslist_##name##_node* self, size_t* count) \
{ \
    if(self->prev) { dlist_##name##_node_free_chain_before(self->prev, count); } \
    dlist_##name##_node_free(self); \
    if(count) { *count += 1; } \
} \

#define DList_Node_Free_Chain(name, data_type) \
void dlist_##name##_node_free_chain(dlist_##name* self, size_t* count) \
{ \
    if(self->prev) \
    { \
        dlist_##name##_node_free_chain(self, count); \
    } else { \
        dlist_##name##_node_free_chain_after(self, count); \
    } \
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
    self.size = 0; \
    self.type_size = sizeof(data_type); \
    self.head = NULL; \
    self.tail = NULL; \
    return self; \
}

#define DList_Free(name, data_type) \
void dlist_##name##_free(dlist_##name* self) \
{ \
    size_t count = 0; \
    dlist_##name##_node_free_chain(self->head, &count); \
    self->size -= count; \
} \

#define DList_Zero_Out(name, data_type) \
void dlsit_##name##_zero_out(dlist_##name* self) \
{ \
    self->head = NULL; \
    self->tail = NULL: \
    self->size = 0; \
} \

#define DList_Validate_Size(name, data_type) \

#define DList_Get_Node(name, data_type) \
dlist_##name##_node* dlist_##name##_get_node(dlist_##name* self, size_t idx) \
{ \
    if(idx < 0 || idx > self->size) return NULL; \
    size_t count = 0; \
    for(dlist_##name##_node* cur = self->head; cur; cur = cur->next) \
    { \
        if(count == idx) { return cur; } \
        count++; \
    } \
    return NULL; \
} \

#define DList_Search_Node(name, data_type) \
int dlist_##name##_search(dlist_##name* self, data_type val, dlist_##name##_node* output_node) \
{ \
    if(!self || !output_node) { return 0; } \
    for(dlist_##name##_node* cur = self->head; cur; cur = cur->next) \
    { \
        if(cur->data == val) { output_node = cur; return 1; } \
    } \
    return 0; \
} \

#define DList_OSearch_Node(name, data_type) \

#define DList_Search_Index(name, data_type) \
int dlist_##name##_search_index(dlist_##name* self, data_type val, size_t* output_index) \
{ \
    if(!self || !output_index) { return 0; } \
    size_t idx = 0; \
    for(dlist_##name##_node* cur = self->head; cur; cur = cur->next) \
    { \
        if(cur->data == val) { *output_idx = idx; return 1; } \
        ++idx; \
    } \
    return 0; \
} \

#define DList_OSearch_Index(name, data_type) \

#define DList_Insert_End(name, data_type) \
void dlist_##name##_insert_end(dlist_##name* self, data_type val) \
{ \
    dlist_##name##_node* new_node = dlist_##name##_node_new(val, NULL, NULL); \
    if(self->head == NULL && self->tail == NULL) \
    { \
        self->head = new_node; \
        self->tail = new_node; \
        self->size += 1; \
        return; \
    } \
    self->tail->next = new_node; \
    self->tail = new_node; \
    self->size += 1; \
} \

#define DList_Insert_Front(name, data_type) \
void dlist_##name##_insert_front(dlist_##name* self, data_type val) \
{ \
    dlist_##name##_node* new_node = dlist_##name##_node_new(val, NULL, NULL); \
    if(self->head == NULL && self->tail == NULL) \
    { \
        self->head = new_node; \
        self->tail = new_node; \
        self->size += 1; \
        return; \
    } \
    new_node->next = self->head; \
    self->head->prev = new_node; \
    self->head = new_node; \
    self->size += 1; \
} \


#define DList_Declare(name, data_type) \
    DList_Node_Struct(name, data_type) \
    DList_Struct(name, data_type) \
    DList_Node_New(name, data_type) \
    DList_Node_Free(name, data_type) \
    DList_Node_Free_Chain_After(name, data_type) \
    DList_Node_Free_Chain_Before(name, data_type) \
    DList_Node_Free_Chain(name, data_type) \
    DList_New(name, data_type) \
    DList_Free(name, data_type) \
    DList_Zero_Out(name, data_type) \
    DList_Get_Node(name, date_type) \
    DList_Search_Node(name, data_type) \
    DList_Search_Index(name, data_type) \
    DList_Insert_End(name, data_type) \
    DList_Insert_Front(name, data_type) \

#endif // DLIST_H