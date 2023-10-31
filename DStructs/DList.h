#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>
#include <stdio.h>

#define DList_Node_Struct(name, data_type) \
typedef struct dlist_node_##name { \
    data_type data; \
    dlist_node_##name* next; \
    dlist_node_##name* prev; \
} dlist_node_##name;

#define DList_Struct(name, data_type) \
typedef struct dlist_##name { \
    dlist_node_##name* head; \
    dlist_node_##name* tail; \
    size_t type_size; \
    size_t size; \
} dlist_##name;

#define DList_Node_New(name, data_type) \
dlist_node_##name dlist_node_##name##_new(data_type data, dlist_node_##name* head, dlist_node_##name* tail) \
{ \
    dlist_node_##name node; \
    node->data = data; \
    node->head = head; \
    node->tail = tail; \
    return darray; \
}

#define DList_Node_New_Uninit(name, data_type) \
dlist_node_##name dlist_node_##name##_new_unint(dlist_node_##name* head, dlist_node_##name* tail) \
{ \
    dlist_node_##name node; \
    node->head = head; \
    node->tail = tail; \
    return darray; \
}

#define DList_New(name, data_type) \
dlist_##name dlist_##name##_new() \
{ \
    dlist_##name list; \
    list.size = 0; \
    list.type_size = sizeof(data_type); \
    list.head = list.tail = &dlist_node_##name##_new_uninit(NULL, NULL) \
    return list; \
}

#define DList_Push_Back(name, data_type) \
void dlist_##name##_push_back() \
{ \
}

#define DList_Push_Front(name, data_type) \
void dlist_##name##_push_front() \
{ \
}

#define DList_Pop_Back(name, data_type) \
dlist_node_##name## dlist_##name##_pop_back() \
{ \
}

#define DList_Pop_Front(name, data_type) \
dlist_node_##name## dlist_##name##_pop_front() \
{ \
}

#define DList_Declare(name, data_type) \
    DList_Node_Struct(name, data_type) \
    DList_Struct(name, data_type) \
    DList_Node_New(name, data_type) \
    DList_Node_New_Uninit(name, data_type) \
    DList_New(name, data_type);

#endif // DLIST_H