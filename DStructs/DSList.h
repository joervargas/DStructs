#ifndef DSLIST_H
#define DSLIST_H

#include <stdlib.h>
#include <stdio.h>

#include "DStructs_Utils.h"

#define DSList_Node_Struct(name, data_type) \
typedef struct dslist_node_##name { \
    data_type data; \
    struct dslist_node_##name* next; \
} dslist_node_##name;


#define DSList_Node_New(name, data_type) \
dslist_node_##name* dslist_node_##name##_new(data_type data, dslist_node_##name* next) \
{ \
    dslist_node_##name* node = malloc(sizeof(dslist_node_##name)); \
    node->data = data; \
    node->next = next; \
    return node; \
}

#define DSList_Node_Free(name, data_type) \
void dslist_node_##name##_free(dslist_node_##name* node) \
{ \
    node->next = NULL; \
    free(node); \
    node = NULL; \
}

#define DSList_Node_Free_Chain(name, data_type) \
void dslist_node_##name##_free_chain(dslist_node_##name* node, size_t* count) \
{ \
    if(node->next) { dslist_node_##name##_free_chain(node->next, count); } \
    dslist_node_##name##_free(node); \
    if(count) { *count += 1; } \
} \

#define DSList_Struct(name, data_type) \
typedef struct dslist_##name { \
    dslist_node_##name* head; \
    dslist_node_##name* tail; \
    size_t type_size; \
    size_t size; \
} dslist_##name;

#define DSList_New(name, data_type) \
dslist_##name dslist_##name##_new(data_type val, dslist_node_##name* head, dslist_node_##name* tail) \
{ \
    dslist_##name dslist; \
    dslist.head = head; \
    dslist.tail = tail; \
    dslist.type_size = sizeof(data_type); \
    dslist.size = 0; \
    return dslist; \
}

#define DSList_Free(name, data_type) \
void dslist_##name##_free(dslist_##name* dslist) \
{ \
    size_t count = 0; \
    dslist_node_##name##_free_chain(dslist->head, &count); \
    dslist->size -= count; \
} \

#define DSList_Insert_End(name, data_type) \
void dslist_##name##_insert_end(dslist_##name *dslist, data_type val) \
{ \
    dslist_node_##name* new_node = dslist_node_##name##_new(val, NULL); \
    if(dslist->head == NULL && dslist->tail == NULL) \
    { \
        dslist->head = new_node; \
        dslist->tail = new_node; \
        dslist->size += 1; \
        return; \
    } \
    dslist->tail->next = new_node; \
    dslist->tail = new_node; \
    dslist->size += 1; \
}

#define DSList_Insert_Front(name, data_type) \
void dslist_##name##_insert_front(dslist_##name *dslist, data_type val) \
{ \
    dslist_node_##name* new_node = dslist_node_##name##_new(val, NULL); \
    if(dslist->head == NULL && dslist->tail == NULL) \
    { \
        dslist->head = new_node; \
        dslist->tail = new_node; \
        dslist->size += 1; \
        return; \
    } \
    dslist_node_##name* old_head = dslist->head; \
    dslist->head = new_node; \
    dslist->head->next = old_head; \
    dslist->size += 1; \
} \

#define DSList_Insert_At(name, data_type) \
int dslist_##name##_insert_at(dslist_##name *dslist, size_t idx, data_type val) \
{ \
    if(idx < 0 && idx > dslist->size) return 0; \
    if(idx == 0) { dslist_##name##_insert_front(dslist, val); return 1; } \
    if(idx == dslist->size) { dslist_##name##_insert_end(dslist, val); return 1; } \
    \
} \

#define DSList_Remove_End(name, data_type) \
void dslist_##name##_remove_end(dslist_##name *dslist, data_type *output) \
{ \
    if(dslist == NULL) return; \
    if(output) { *output = dslist->tail->data; } \
    if(dslist->head == dslist->tail) \
    { \
        dslist_node_##name##_free(dslist->tail); \
        dslist->head = NULL; \
        dslist->tail = NULL; \
        dslist->size = 0; \
        return; \
    } \
    dslist_node_##name* prev = NULL; \
    for(dslist_node_##name* cur = dslist->head; cur != NULL; cur = cur->next) \
    { \
        if(cur == dslist->tail) \
        { \
            prev->next = NULL; \
            dslist->tail = prev; \
            dslist->size -= 1; \
            dslist_node_##name##_free(cur); \
            return; \
        } \
        prev = cur; \
    } \
} \

#define DSList_Remove_Front(name, data_type) \
void dslist_##name##_remove_front(dslist_##name *dslist, data_type *output) \
{ \
    if(dslist == NULL) return; \
    if(output) { *output = dslist->head->data; } \
    if(dslist->head == dslist->tail) \
    { \
        dslist_node_##name##_free(dslist->head); \
        dslist->head = NULL; \
        dslist->tail = NULL; \
        dslist->size = 0; \
        return; \
    } \
    dslist_node_##name node* = dslist->head; \
    dslist->head = node->next; \
    dslist_node_##name##_free(node); \
    dslist->size -= 1; \
} \

#define DSList_Swap(name, data_type) \
void dslist_##name##_swap(dslist_##name *dslist, dslist_node_##name *first, dslist_node_##name *second) \
{ \
    if(first == NULL || second == NULL) return; \
    if(first == dslist->tail) return; \
    if(first == dslist->head) \
    { \
        dslist_node_##name temp = *first; \
        first->next = second->next; \
        second->next = first; \
        dslist->head = second; \
        return; \
    } \
    dslist_node_##name* prev = NULL; \
    for(dslist_node_##name* cur = dslist->head; cur != NULL; cur = cur->next) \
    { \
        if(cur == first) \
        { \
            first->next = second->next; \
            prev->next = second; \
            second->next = first; \
            if(dslist->tail == second) { dslist->tail = first; } \
            return; \
        } \
        prev = cur; \
    } \
} \

#define DSList_Get_Node(name, data_type) \
dslist_node_##name* dslist_##name##_get_node(dslist_##name *dslist, size_t idx) \
{ \
    size_t count = 0; \
    for(dslist_node_##name* cur = dslist->head; cur != NULL; cur = cur->next) \
    { \
        if(count == idx) { return cur; } \
        count++; \
    } \
    return NULL; \
} \

#define DSList_Search_Node(name, data_type) \
int dslist_##name##_search(dslist_##name *dslist, data_type val, dslist_node_##name* output_node) \
{ \
    if(!dslist || !output_node) { return 0; } \
    for(dslist_node_##name* cur = dslist->head; cur != NULL; cur = cur->next) \
    { \
        if(cur->data == val) { output_node = cur; return 1; } \
    } \
    return 0; \
} \

#define DSList_OSearch_Node(name, data_type) \
int dslist_##name##_osearch(dslist_##name *dslist, data_type val, dslist_node_##name** output_node) \
{ \
    if(!dslist || !output_node) { return 0; } \
    dslist_node_##name* prev = NULL; \
    for(dslist_node_##name* cur = dslist->head; cur != NULL; cur = cur->next) \
    { \
        if(cur->data == val) \
        { \
            *output_node = cur; \
            if(!prev) { return 1; } \
            dslist_##name##_swap(dslist, prev, cur); \
            return 1; \
        } \
        prev = cur; \
    } \
    return 0; \
} \

#define DSList_Search_Index(name, data_type) \
int dslist_##name##_search_index(dslist_##name *dslist, data_type val, size_t* output_idx) \
{ \
    if(!dslist || !output_idx) { return 0; } \
    size_t idx = 0; \
    for(dslist_node_##name* cur = dslist->head; cur != NULL; cur = cur->next) \
    { \
        if(cur->data == val) { *output_idx = idx; return 1;  } \
        ++idx; \
    } \
    return 0; \
} \

#define DSList_OSearch_Index(name, data_type) \
int dslist_##name##_osearch_index(dslist_##name *dslist, data_type val, size_t* output_idx) \
{ \
    if(!dslist || !output_idx) { return 0; } \
    size_t idx = 0; \
    dslist_node_##name* prev = NULL; \
    for(dslist_node_##name* cur = dslist->head; cur != NULL; cur = cur->next, idx++) \
    { \
        if(cur->data == val) \
        { \
            if(!prev) { *output_idx = idx; return 1; } \
            dslist_##name##_swap(dslist, prev, cur); \
            *output_idx = idx - 1; \
            return 1; \
        } \
        prev = cur; \
    } \
    return 0; \
} \

#define DSList_To_Array(name, data_type) \
int dslist_##name##_to_array(dslist_##name *dslist, data_type** output, size_t* count) \
{ \
    if(dslist == NULL) return 0; \
    dslist_node_##name* cur = dslist->head; \
    *output = malloc(dslist->size * sizeof(data_type)); \
    for(size_t i = 0; i < dslist->size; i++) \
    { \
        (*output)[i] = cur->data; \
        cur = cur->next; \
    } \
    if(count != NULL) { *count = dslist->size; } \
    return 1; \
} \

// TODO: Test this
#define DSList_From_Array(name, data_type) \
dslist_##name dslist_##name##_from_array(data_type* input, size_t count) \
{ \
    dslist_##name output = dslist_##name##_new(); \
    for(size_t i = 0; i < *count; i++) \
    {  \
        dslist_##name##_insert_end(output, input[i]); \
    } \
} \

#define DSList_Declare(name, data_type) \
    DSList_Node_Struct(name, data_type) \
    DSList_Node_New(name, data_type) \
    DSList_Node_Free(name, data_type) \
    DSList_Node_Free_Chain(name, data_type) \
    DSList_Struct(name, data_type) \
    DSList_New(name, data_type) \
    DSList_Free(name, data_type) \
    DSList_Insert_End(name, data_type) \
    DSList_Insert_Front(name, data_type) \
    DSList_Remove_End(name, data_type) \
    DSList_Remove_Front(name, data_type) \
    DSList_Swap(name, data_type) \
    DSList_Get_Node(name, data_type) \
    DSList_Search_Node(name, data_type) \
    DSList_OSearch_Node(name, data_type) \
    DSList_Search_Index(name, data_type) \
    DSList_OSearch_Index(name, data_type) \
    DSList_To_Array(name, data_type) \
    DSList_From_Array(name, data_type) \

#endif // DSLIST_H