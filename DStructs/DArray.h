#ifndef DARRAY_H
#define DARRAY_H

#include <stdlib.h>
#include <stdio.h>

#define DArray_Struct(name, data_type) \
typedef struct darray_##name { \
    data_type *data; \
    size_t type_size; \
    size_t capacity; \
    size_t size; \
} darray_##name;

#define DArray_New(name, data_type) \
darray_##name darray_##name##_new() \
{ \
    darray_##name darray;\
    darray.capacity = 10; \
    darray.size = 0; \
    darray.type_size = sizeof(data_type); \
    darray.data = (data_type*)malloc(darray.capacity * darray.type_size); \
    return darray; \
}

#define DArray_Free(name, data_type) \
void darray_##name##_free(darray_##name *darray) \
{ \
    free(darray->data); \
    darray->size = 0; \
    darray->capacity = 0; \
}

#define DArray_Init(name, data_type) \
darray_##name darray_##name##_init(data_type* data, size_t count) \
{ \
    darray_##name darray;\
    darray.capacity = count + 10; \
    darray.size = count; \
    darray.type_size = sizeof(data_type); \
    darray.data = (data_type*)malloc(darray.capacity * darray.type_size); \
    for(int i = 0; i < count; i++) \
    { \
        darray.data[i] = data[i]; \
    } \
    return darray; \
}

#define DArray_Push(name, data_type) \
void darray_##name##_push(darray_##name *darray, data_type d) \
{ \
    if (darray->size > (darray->capacity - 5)) \
    { \
        if (darray->capacity == 0) darray->capacity = 5; \
        darray->capacity = darray->capacity * 2; \
        data_type* data = (data_type*)malloc(darray->capacity * darray->type_size); \
        for(int i = 0; i < darray->size; i++) \
        { \
            data[i] = darray->data[i]; \
        } \
        free(darray->data); \
        darray->data = data; \
    } \
    darray->data[darray->size] = d; \
    darray->size = darray->size + 1; \
}

#define DArray_Pop(name, data_type) \
data_type darray_##name##_pop(darray_##name *darray) \
{ \
    data_type d = darray->data[darray->size - 1]; \
    darray->data[darray->size - 1] = 0; \
    darray->size = darray->size - 1; \
    return d; \
}

// #define DArray_Get(name, data_type) \
// data_type darray_##name##_get(darray_##name *darray, unsigned int idx) \
// { \
//     /* TODO: Panic if not in range */ \
//     return darray->data[idx]; \
// } 

#define DArray_Declare(name, data_type) \
    DArray_Struct(name, data_type) \
    DArray_New(name, data_type) \
    DArray_Init(name, data_type) \
    DArray_Free(name, data_type) \
    DArray_Push(name, data_type) \
    DArray_Pop(name, data_type);

#endif // DARRAY_H