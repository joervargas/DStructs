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
void darray_##name##_push(darray_##name *darray, data_type val) \
{ \
    if (darray->capacity == 0 || darray->size > (darray->capacity - 5)) \
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
    darray->data[darray->size] = val; \
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

#define DArray_Remove(name, data_type) \
data_type darray_##name##_remove(darray_##name *darray, size_t idx) \
{ \
    if (idx < 0 || idx >= darray->size) \
    { \
        /*TODO: exit with error*/ \
        return 0; \
    } \
    if (idx == (darray->size - 1)) \
    { return darray_##name##_pop(darray); } \
    \
    data_type val = darray->data[idx]; \
    size_t i = idx; size_t j = idx + 1; \
    while(j < darray->size) \
    { \
        darray->data[i] = darray->data[j]; \
        i += 1; j += 1; \
    } \
    darray->size = darray->size - 1; \
    return val; \
}

#define DArray_Insert(name, data_type) \
void darray_##name##_insert(darray_##name *darray, data_type val, size_t idx) \
{ \
    if (idx == (darray->size)) \
    { darray_##name##_push(darray, val); } \
    if (idx < 0 || idx >= darray->size) \
    { \
        /*TODO: exit with error*/ \
        return; \
    } \
    if (darray->capacity == 0 || darray->size > (darray->capacity - 5)) \
    { \
        if (darray->capacity == 0) darray->capacity = 5; \
        darray->capacity = darray->capacity * 2; \
        data_type* data = (data_type*)malloc(darray->capacity * darray->type_size); \
        for(int i = 0; i < idx; i++) \
        { \
            data[i] = darray->data[i]; \
        } \
        data[idx] = val; \
        for(int i = idx; i < darray->size; i++) \
        { \
            data[i + 1] = darray->data[i]; \
        } \
        free(darray->data); \
        darray->data = data; \
    } else { \
        for(int i = darray->size; i > idx; i--) \
        { \
            darray->data[i + 1] = darray->data[i]; \
        } \
        darray->data[idx] = val; \
    } \
    darray->size = darray->size + 1; \
} \

#define DArray_Append(name, data_type) \
void darray_##name##_append(darray_##name *darray, data_type *values, size_t count) \
{ \
    if(darray->capacity == 0 || (darray->size + count) > darray->capacity) \
    { \
        darray->capacity = darray->capacity + count * 2; \
        data_type* data = (data_type*)malloc(darray->capacity * darray->type_size); \
        for(int i = 0; i < darray->size; i++) \
        { \
            data[i] = darray->data[i]; \
        } \
        free(darray->data); \
        darray->data = data; \
    } \
    size_t values_index = 0; \
    for(size_t i = darray->size + 1; i < (darray->size + count); i++) \
    { \
        darray->data[i] = values[values_index]; \
        values_index = values_index + 1; \
    } \
    darray->size = darray->size + count; \
}

#define DArray_Slice(name, data_type) \
size_t darray_##name##_slice(darray_##name *darray, size_t first_idx, size_t second_idx, data_type *slice) \
{ \
    if(first_idx <= 0 || first_idx > darray->size) { *slice = 0; return 0; } \
    if(second_idx <= 0 || second_idx > darray->size) { *slice = 0; return 0; } \
    if(first_idx > second_idx) { slice = 0; return 0; } \
    if(first_idx == second_idx) \
    { \
        *slice = darray->data[first_idx]; \
        return 1; \
    } \
    size_t count = second_idx - first_idx; \
    slice = (data_type*)malloc(count * darray->type_size); \
    size_t slice_idx = 0; \
    for(size_t i = first_idx; i < second_idx; i++) \
    { \
        slice[slice_idx] = darray->data[i]; \
        slice_idx = slice_idx + 1; \
    } \
    return count; \
}

// TODO: text this
#define DArray_Slice_Insert(name, data_type) \
void darray_##name##_slice_insert(darray_##name *darray, size_t first_idx, data_type *values, size_t count) \
{ \
    if (first_idx == (darray->size)) \
    { darray_##name##_append(darray, values, count); } \
    if (first_idx < 0 || first_idx >= darray->size) \
    { \
        /*TODO: exit with error*/ \
        return; \
    } \
    if (darray->capacity == 0 || darray->size > (darray->capacity - 5)) \
    { \
        if (darray->capacity == 0) darray->capacity = 5; \
        darray->capacity = darray->capacity + count * 2; \
        data_type* data = (data_type*)malloc(darray->capacity * darray->type_size); \
        for(int i = 0; i < first_idx; i++) \
        { \
            data[i] = darray->data[i]; \
        } \
        for(int i = first_idx, j = 0; i < first_idx + count; i++, j++) \
        { \
            data[i] = values[j]; \
        } \
        for(int i = first_idx + count, j = first_idx; i < darray->size + count; i++, j++) \
        { \
            data[i] = darray->data[j]; \
        } \
        free(darray->data); \
        darray->data = data; \
    } else { \
        for(int i = darray->size + count; i > first_idx; i--) \
        { \
            darray->data[i + count] = darray->data[i]; \
        } \
        for(int i = first_idx, j = 0; i < first_idx + count; i++, j++) \
        { \
            darray->data[i] = values[j]; \
        } \
    } \
    darray->size = darray->size + count; \
}

// TODO: test this
#define DArray_Slice_Remove(name, data_type) \
size_t darray_##name##_slice_remove(darray_##name *darray, size_t first_idx, size_t second_idx, data_type* slice) \
{ \
    if(first_idx <= 0 || first_idx > darray->size) { *slice = 0; return 0; } \
    if(second_idx <= 0 || second_idx > darray->size) { *slice = 0; return 0; } \
    if(first_idx > second_idx) { slice = 0; return 0; } \
    size_t count = second_idx - first_idx; \
    if(count > darray->size) \
    { \
        count = darray->size; \
        slice = darray->data; \
        darray_##name##_free(darray); \
    } \
    if(first_idx == second_idx) \
    { \
        data_type value = darray_##name##_remove(darray, first_idx); \
        slice = &value; \
        return 1; \
    } \
    slice = (data_type*)malloc(count * darray->type_size); \
    size_t slice_idx = 0; \
    for(size_t i = first_idx; i < second_idx; i++) \
    { \
        slice[slice_idx] = darray->data[i]; \
        slice_idx = slice_idx + 1; \
    } \
    for(size_t i = second_idx; i < darray->size; i++) \
    { \
        darray->data[i - count] = darray->data[i]; \
    } \
    darray->size = darray->size - count; \
    return count; \
}

#define DArray_Declare(name, data_type) \
    DArray_Struct(name, data_type) \
    DArray_New(name, data_type) \
    DArray_Init(name, data_type) \
    DArray_Free(name, data_type) \
    DArray_Push(name, data_type) \
    DArray_Pop(name, data_type) \
    DArray_Remove(name, data_type) \
    DArray_Insert(name, data_type) \
    DArray_Append(name, data_type) \
    DArray_Slice(name, data_type) \
    DArray_Slice_Insert(name, data_type) \
    DArray_Slice_Remove(name, data_type);

#endif // DARRAY_H