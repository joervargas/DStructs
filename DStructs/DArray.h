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
    darray_##name self;\
    self.capacity = 10; \
    self.size = 0; \
    self.type_size = sizeof(data_type); \
    self.data = malloc(self.capacity * self.type_size); \
    return self; \
}

#define DArray_Free(name, data_type) \
void darray_##name##_free(darray_##name *self) \
{ \
    free(self->data); \
    self->data = NULL; \
    self->size = 0; \
    self->capacity = 0; \
}

#define DArray_Init(name, data_type) \
darray_##name darray_##name##_init(data_type* data, size_t count) \
{ \
    darray_##name self;\
    self.capacity = count + 10; \
    self.size = count; \
    self.type_size = sizeof(data_type); \
    self.data = malloc(self.capacity * self.type_size); \
    for(int i = 0; i < count; i++) \
    { \
        self.data[i] = data[i]; \
    } \
    return self; \
}

#define DArray_Push(name, data_type) \
void darray_##name##_push(darray_##name *self, data_type val) \
{ \
    if (self->capacity == 0 || self->size > (self->capacity - 5)) \
    { \
        if (self->capacity == 0) self->capacity = 5; \
        self->capacity = self->capacity * 2; \
        data_type* data = malloc(self->capacity * self->type_size); \
        for(int i = 0; i < self->size; i++) \
        { \
            data[i] = self->data[i]; \
        } \
        free(self->data); \
        self->data = data; \
    } \
    self->data[self->size] = val; \
    self->size = self->size + 1; \
}

#define DArray_Pop(name, data_type) \
int darray_##name##_pop(darray_##name *self, data_type *output) \
{ \
    if (self == NULL) return 0; \
    if (self->size == 0) return 0; \
    if (output != NULL) { *output = self->data[self->size - 1]; } \
    self->data[self->size - 1] = 0; \
    self->size = self->size - 1; \
    return 1; \
}


#define DArray_Remove(name, data_type) \
int darray_##name##_remove(darray_##name *self, size_t idx, data_type *output) \
{ \
    if (idx == (self->size - 1)) { return darray_##name##_pop(self, output); } \
    if (self == NULL) { return 0; } \
    if (idx < 0 || idx >= self->size) { return 0; } \
    if (output != NULL) { *output = self->data[idx]; } \
    size_t i = idx; size_t j = idx + 1; \
    while(j < self->size) \
    { \
        self->data[i] = self->data[j]; \
        i += 1; j += 1; \
    } \
    self->size = self->size - 1; \
    return 1; \
}

#define DArray_Insert(name, data_type) \
int darray_##name##_insert(darray_##name *self, size_t idx, data_type val) \
{ \
    if (self == NULL) { return 0; } \
    if (idx < 0 || idx >= self->size) { return 0; } \
    if (idx == (self->size)) { darray_##name##_push(self, val); return 1; } \
    if (self->capacity == 0 || self->size > (self->capacity - 5)) \
    { \
        if (self->capacity == 0) self->capacity = 5; \
        self->capacity = self->capacity * 2; \
        data_type* data = malloc(self->capacity * self->type_size); \
        for(int i = 0; i < idx; i++) \
        { \
            data[i] = self->data[i]; \
        } \
        data[idx] = val; \
        for(int i = idx; i < self->size; i++) \
        { \
            data[i + 1] = self->data[i]; \
        } \
        free(self->data); \
        self->data = data; \
    } else { \
        for(int i = self->size + 1; i > idx; i--) \
        { \
            self->data[i] = self->data[i - 1]; \
        } \
        self->data[idx] = val; \
    } \
    self->size = self->size + 1; \
    return 1; \
}

#define DArray_Append(name, data_type) \
void darray_##name##_append(darray_##name *self, data_type *values, size_t count) \
{ \
    if(self->capacity == 0 || (self->size + count) > self->capacity) \
    { \
        self->capacity = self->capacity + count * 2; \
        data_type* data = malloc(self->capacity * self->type_size); \
        for(int i = 0; i < self->size; i++) \
        { \
            data[i] = self->data[i]; \
        } \
        free(self->data); \
        self->data = data; \
    } \
    size_t values_index = 0; \
    for(size_t i = self->size; i < (self->size + count); i++) \
    { \
        self->data[i] = values[values_index]; \
        values_index = values_index + 1; \
    } \
    self->size = self->size + count; \
}

#define DArray_Slice(name, data_type) \
int darray_##name##_slice(darray_##name *self, size_t first_idx, data_type *slice, size_t slice_size) \
{ \
    if(self == NULL || slice == NULL) { return 0; } \
    if(first_idx < 0 || first_idx > self->size) { return 0; } \
    if(slice_size == 0 || first_idx + slice_size > self->size) { return 0; } \
    if(slice_size == 1) \
    { \
        slice[0] = self->data[first_idx]; \
        return 1; \
    } \
    for(size_t i = 0; i < slice_size; i++) \
    { \
        slice[i] = self->data[first_idx + i]; \
    } \
    return 1; \
}

#define DArray_Slice_Insert(name, data_type) \
int darray_##name##_slice_insert(darray_##name *self, size_t first_idx, data_type *slice, size_t slice_size) \
{ \
    if (self == NULL || slice == NULL) { return 0; } \
    if (first_idx < 0 || first_idx > self->size) { return 0; } \
    if (first_idx == (self->size)) { darray_##name##_append(self, slice, slice_size); return 1; } \
    if (self->capacity == 0 || self->size > (self->capacity - 5)) \
    { \
        if (self->capacity == 0) self->capacity = 5; \
        self->capacity = self->capacity + slice_size * 2; \
        data_type* data = malloc(self->capacity * self->type_size); \
        for(int i = 0; i < first_idx; i++) \
        { \
            data[i] = self->data[i]; \
        } \
        for(int i = first_idx, j = 0; i < first_idx + slice_size; i++, j++) \
        { \
            data[i] = slice[j]; \
        } \
        for(int i = first_idx + slice_size, j = first_idx; i < self->size + slice_size; i++, j++) \
        { \
            data[i] = self->data[j]; \
        } \
        free(self->data); \
        self->data = data; \
    } else { \
        for(int i = self->size + slice_size; i > first_idx; i--) \
        { \
            self->data[i + slice_size] = self->data[i]; \
        } \
        for(int i = first_idx, j = 0; i < first_idx + slice_size; i++, j++) \
        { \
            self->data[i] = slice[j]; \
        } \
    } \
    self->size = self->size + slice_size; \
    return 1; \
}

#define DArray_Slice_Remove(name, data_type) \
int darray_##name##_slice_remove(darray_##name *self, size_t first_idx, data_type* slice, size_t slice_size) \
{ \
    if(self == NULL) { return 0; } \
    if(first_idx < 0 || first_idx > self->size) { return 0; } \
    if(first_idx + slice_size > self->size) { return 0; } \
    if(slice_size > self->size) { return 0; } \
    if(slice == NULL || slice_size == 1) \
    { \
        int result = darray_##name##_remove(self, first_idx, slice); \
        return result; \
    } \
    size_t slice_idx = 0; \
    for(size_t i = first_idx; i < first_idx + slice_size; i++) \
    { \
        slice[slice_idx] = self->data[i]; \
        slice_idx = slice_idx + 1; \
    } \
    for(size_t i = first_idx + slice_size; i < self->size; i++) \
    { \
        self->data[i - slice_size] = self->data[i]; \
    } \
    self->size = self->size - slice_size; \
    return 1; \
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
    DArray_Slice_Remove(name, data_type)

#endif // DARRAY_H