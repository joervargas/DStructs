#ifndef DSLIST_H
#define DSLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "DStructs_Utils.h"

#define DSList_Node_Struct(name, data_type) \
typedef struct dslist_##name##_node { \
    data_type data; \
    struct dslist_##name##_node* next; \
} dslist_##name##_node;


#define DSList_Node_New(name, data_type) \
dslist_##name##_node* dslist_##name##_node_new(data_type data, dslist_##name##_node* next) \
{ \
    dslist_##name##_node* self = malloc(sizeof(dslist_##name##_node)); \
    self->data = data; \
    self->next = next; \
    return self; \
}

#define DSList_Node_Free(name, data_type) \
void dslist_##name##_node_free(dslist_##name##_node* self) \
{ \
    self->next = NULL; \
    free(self); \
    self = NULL; \
}

#define DSList_Node_Free_Chain(name, data_type) \
void dslist_##name##_node_free_chain(dslist_##name##_node* self, size_t* count) \
{ \
    if(self->next) { dslist_##name##_node_free_chain(self->next, count); } \
    dslist_##name##_node_free(self); \
    if(count) { *count += 1; } \
} \

#define DSList_Struct(name, data_type) \
typedef struct dslist_##name { \
    dslist_##name##_node* head; \
    dslist_##name##_node* tail; \
    size_t type_size; \
    size_t size; \
} dslist_##name;

#define DSList_New(name, data_type) \
dslist_##name dslist_##name##_new() \
{ \
    dslist_##name self; \
    self.head = NULL; \
    self.tail = NULL; \
    self.type_size = sizeof(data_type); \
    self.size = 0; \
    return self; \
}

#define DSList_Free(name, data_type) \
void dslist_##name##_free(dslist_##name* self) \
{ \
    size_t count = 0; \
    dslist_##name##_node_free_chain(self->head, &count); \
    self->size -= count; \
} \

#define DSList_Zero_Out(name, data_type) \
void dslist_##name##_zero_out(dslist_##name* self) \
{ \
    self->head = NULL; \
    self->tail = NULL; \
    self->size = 0; \
} \

#define DSLIST_Validate_Size(name, data_type) \
int dslist_##name##_validate_size(dslist_##name* self, bool b_should_update) \
{ \
    int validation_status = 1; \
    size_t count = 0; \
    for(dslist_##name##_node* cur = self->head; cur; cur = cur->next) \
    { \
        if(count > self->size) \
        { \
            if(b_should_update && cur->next == NULL) \
            { \
                self->size = count; \
                self->tail = cur; \
            } \
            validation_status = 0; \
        } \
        count += 1; \
    } \
    return validation_status; \
} \

#define DSList_Swap(name, data_type) \
void dslist_##name##_swap(dslist_##name *self, dslist_##name##_node *first, dslist_##name##_node *second) \
{ \
    if(first == NULL || second == NULL) return; \
    if(first == self->tail) return; \
    if(first == self->head) \
    { \
        dslist_##name##_node temp = *first; \
        first->next = second->next; \
        second->next = first; \
        self->head = second; \
        return; \
    } \
    dslist_##name##_node* prev = NULL; \
    for(dslist_##name##_node* cur = self->head; cur != NULL; cur = cur->next) \
    { \
        if(cur == first) \
        { \
            first->next = second->next; \
            prev->next = second; \
            second->next = first; \
            if(self->tail == second) { self->tail = first; } \
            return; \
        } \
        prev = cur; \
    } \
} \

#define DSList_Insert_End(name, data_type) \
void dslist_##name##_insert_end(dslist_##name *self, data_type val) \
{ \
    dslist_##name##_node* new_node = dslist_##name##_node_new(val, NULL); \
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
}

#define DSList_Insert_Front(name, data_type) \
void dslist_##name##_insert_front(dslist_##name *self, data_type val) \
{ \
    dslist_##name##_node* new_node = dslist_##name##_node_new(val, self->head); \
    if(self->head == NULL && self->tail == NULL) \
    { \
        self->head = new_node; \
        self->tail = new_node; \
        self->size += 1; \
        return; \
    } \
    dslist_##name##_node* old_head = self->head; \
    self->head = new_node; \
    self->head->next = old_head; \
    self->size += 1; \
} \

#define DSList_Insert_At(name, data_type) \
int dslist_##name##_insert_at(dslist_##name *self, size_t idx, data_type val) \
{ \
    if(idx < 0 || idx > self->size) return 0; \
    if(idx == 0) { dslist_##name##_insert_front(self, val); return 1; } \
    if(idx == self->size) { dslist_##name##_insert_end(self, val); return 1; } \
    size_t index = 0; \
    dslist_##name##_node* prev = NULL; \
    for(dslist_##name##_node* cur = self->head; cur; cur = cur->next) \
    { \
       if(index == idx) \
       { \
            dslist_##name##_node* node = dslist_##name##_node_new(val, cur); \
            prev->next = node; \
            self->size += 1; \
            return 1; \
       } \
       index +=1; \
       prev = cur; \
    } \
    return 0; \
} \

#define DSList_Remove_End(name, data_type) \
void dslist_##name##_remove_end(dslist_##name *self, data_type *output) \
{ \
    if(self == NULL) return; \
    if(output) { *output = self->tail->data; } \
    if(self->head == self->tail) \
    { \
        dslist_##name##_node_free(self->tail); \
        self->head = NULL; \
        self->tail = NULL; \
        self->size = 0; \
        return; \
    } \
    dslist_##name##_node* prev = NULL; \
    for(dslist_##name##_node* cur = self->head; cur != NULL; cur = cur->next) \
    { \
        if(cur == self->tail) \
        { \
            prev->next = NULL; \
            self->tail = prev; \
            self->size -= 1; \
            dslist_##name##_node_free(cur); \
            return; \
        } \
        prev = cur; \
    } \
} \

#define DSList_Remove_Front(name, data_type) \
void dslist_##name##_remove_front(dslist_##name *self, data_type *output) \
{ \
    if(self == NULL) return; \
    if(output) { *output = self->head->data; } \
    if(self->head == self->tail) \
    { \
        dslist_##name##_node_free(self->head); \
        self->head = NULL; \
        self->tail = NULL; \
        self->size = 0; \
        return; \
    } \
    dslist_##name##_node* node = self->head; \
    self->head = node->next; \
    dslist_##name##_node_free(node); \
    self->size -= 1; \
} \

#define DSList_Remove_At(name, data_type) \
int dslist_##name##_remove_at(dslist_##name *self, size_t idx, data_type* output) \
{ \
    if(self == NULL) { return 0; } \
    if( idx < 0 || idx > self->size ) {} \
    if( idx == 1 ) { dslist_##name##_remove_front(self, output); return 1; } \
    if( idx == self->size ) { dslist_##name##_remove_end(self, output); return 1; } \
    size_t index = 0; \
    dslist_##name##_node* prev = NULL; \
    for(dslist_##name##_node* cur = self->head; cur; cur = cur->next) \
    { \
        if(index == idx) \
        { \
            prev->next = cur->next; \
            dslist_##name##_node_free(cur); \
            self->size -=1; \
            return 1; \
        } \
        index += 1; \
        prev = cur; \
    } \
    return 0; \
} \

#define DSList_Get_Node(name, data_type) \
dslist_##name##_node* dslist_##name##_get_node(dslist_##name *self, size_t idx) \
{ \
    size_t count = 0; \
    for(dslist_##name##_node* cur = self->head; cur != NULL; cur = cur->next) \
    { \
        if(count == idx) { return cur; } \
        count++; \
    } \
    return NULL; \
} \

#define DSList_Search_Node(name, data_type) \
int dslist_##name##_search(dslist_##name *self, data_type val, dslist_##name##_node* output_node) \
{ \
    if(!self || !output_node) { return 0; } \
    for(dslist_##name##_node* cur = self->head; cur != NULL; cur = cur->next) \
    { \
        if(cur->data == val) { output_node = cur; return 1; } \
    } \
    return 0; \
} \

#define DSList_OSearch_Node(name, data_type) \
int dslist_##name##_osearch(dslist_##name *self, data_type val, dslist_##name##_node** output_node) \
{ \
    if(!self || !output_node) { return 0; } \
    dslist_##name##_node* prev = NULL; \
    for(dslist_##name##_node* cur = self->head; cur != NULL; cur = cur->next) \
    { \
        if(cur->data == val) \
        { \
            *output_node = cur; \
            if(!prev) { return 1; } \
            dslist_##name##_swap(self, prev, cur); \
            return 1; \
        } \
        prev = cur; \
    } \
    return 0; \
} \

#define DSList_Search_Index(name, data_type) \
int dslist_##name##_search_index(dslist_##name *self, data_type val, size_t* output_idx) \
{ \
    if(!self || !output_idx) { return 0; } \
    size_t idx = 0; \
    for(dslist_##name##_node* cur = self->head; cur != NULL; cur = cur->next) \
    { \
        if(cur->data == val) { *output_idx = idx; return 1;  } \
        ++idx; \
    } \
    return 0; \
} \

#define DSList_OSearch_Index(name, data_type) \
int dslist_##name##_osearch_index(dslist_##name *self, data_type val, size_t* output_idx) \
{ \
    if(!self || !output_idx) { return 0; } \
    size_t idx = 0; \
    dslist_##name##_node* prev = NULL; \
    for(dslist_##name##_node* cur = self->head; cur != NULL; cur = cur->next, idx++) \
    { \
        if(cur->data == val) \
        { \
            if(!prev) { *output_idx = idx; return 1; } \
            dslist_##name##_swap(self, prev, cur); \
            *output_idx = idx - 1; \
            return 1; \
        } \
        prev = cur; \
    } \
    return 0; \
} \

#define DSList_Append(name, data_type) \
void dslist_##name##_append(dslist_##name* self, dslist_##name* append_data) \
{ \
   if(self->head == NULL && self->tail == NULL) \
   { \
        self->head = append_data->head; \
        self->tail = append_data->tail; \
        self->size = append_data->size; \
        return; \
    } \
    self->tail->next = append_data->head; \
    self->size += append_data->size; \
    self->tail = append_data->tail; \
    dslist_##name##_zero_out(append_data); \
} \

#define DSList_Prepend(name, data_type) \
void dslist_##name##_prepend(dslist_##name* self, dslist_##name* other) \
{ \
    if(self->head == NULL && self->tail == NULL) \
   { \
        self->head = other->head; \
        self->tail = other->tail; \
        self->size = other->size; \
        return; \
    } \
    other->tail->next = self->head; \
    self->size += other->size; \
    self->head = other->head; \
    dslist_##name##_zero_out(other); \
} \

#define DSList_Emplace(name, data_type) \
int dslist_##name##_emplace(dslist_##name* self, dslist_##name* other, size_t index) \
{ \
   if(self == NULL || other == NULL) { return 0; } \
   if(index < 0 || index > self->size) { return 0; } \
   if(index == 0) { dslist_##name##_prepend(self, other); return 1; } \
   if(index == self->size - 1) { dslist_##name##_append(self, other); return 1; } \
   dslist_##name##_node* node = dslist_##name##_get_node(self, index); \
   if(!node) { return 0; } \
   other->tail->next = node->next; \
   node->next = other->head; \
   self->size += other->size; \
   dslist_##name##_zero_out(other); \
   return 1; \
} \

#define DSList_To_Array(name, data_type) \
int dslist_##name##_to_array(dslist_##name *self, data_type** output, size_t* count) \
{ \
    if(self == NULL) return 0; \
    dslist_##name##_node* cur = self->head; \
    *output = malloc(self->size * self->type_size); \
    for(size_t i = 0; i < self->size; i++) \
    { \
        (*output)[i] = cur->data; \
        cur = cur->next; \
    } \
    if(count != NULL) { *count = self->size; } \
    return 1; \
} \

#define DSList_From_Array(name, data_type) \
dslist_##name dslist_##name##_from_array(const data_type* input, size_t count) \
{ \
    dslist_##name output = dslist_##name##_new(); \
    for(size_t i = 0; i < count; i++) \
    {  \
        dslist_##name##_insert_end(&output, input[i]); \
    } \
    return output; \
} \

#define DSList_Insert_Array_Front(name, data_type) \
void dslist_##name##_insert_array_front(dslist_##name* self, data_type** arr, size_t count) \
{ \
    dslist_##name other = dslist_##name##_from_array(*arr, count); \
    dslist_##name##_prepend(self, &other); \
} \

#define DSList_Insert_Array_End(name, data_type) \
void dslist_##name##_insert_array_end(dslist_##name* self, data_type** arr, size_t count) \
{ \
    dslist_##name other = dslist_##name##_from_array(*arr, count); \
    dslist_##name##_append(self, &other); \
} \

#define DSList_Insert_Array_At(name, data_type) \
int dslist_##name##_insert_array_at(dslist_##name* self, data_type** arr, size_t count, size_t index) \
{ \
    if(self == NULL || arr == NULL) { return 0; } \
    if(index == 0) { dslist_##name##_insert_array_front(self, arr, count); return 1; } \
    if(index == self->size - 1) { dslist_##name##_insert_array_end(self, arr, count); return 1; } \
    dslist_##name other = dslist_##name##_from_array(*arr, count); \
    dslist_##name##_emplace(self, &other, index); \
    return 1; \
} \


#define DSList_Declare(name, data_type) \
    DSList_Node_Struct(name, data_type) \
    DSList_Node_New(name, data_type) \
    DSList_Node_Free(name, data_type) \
    DSList_Node_Free_Chain(name, data_type) \
    DSList_Struct(name, data_type) \
    DSList_New(name, data_type) \
    DSList_Free(name, data_type) \
    DSList_Zero_Out(name, data_type) \
    DSLIST_Validate_Size(name, data_type) \
    DSList_Swap(name, data_type) \
    DSList_Insert_End(name, data_type) \
    DSList_Insert_Front(name, data_type) \
    DSList_Remove_End(name, data_type) \
    DSList_Remove_Front(name, data_type) \
    DSList_Get_Node(name, data_type) \
    DSList_Search_Node(name, data_type) \
    DSList_OSearch_Node(name, data_type) \
    DSList_Search_Index(name, data_type) \
    DSList_OSearch_Index(name, data_type) \
    DSList_Append(name, data_type) \
    DSList_Prepend(name, data_type) \
    DSList_Emplace(name, data_type) \
    DSList_To_Array(name, data_type) \
    DSList_From_Array(name, data_type) \
    DSList_Insert_Array_Front(name, data_type) \
    DSList_Insert_Array_End(name, data_type) \
    DSList_Insert_Array_At(name, data_type) \

#endif // DSLIST_H