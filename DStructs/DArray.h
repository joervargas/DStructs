#ifndef DARRAY_H
#define DARRAY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define DARRAY_STRUCT(name, data_type) \
typedef struct darray_##name { \
    data_type *data; \
    size_t capacity; \
    size_t size; \
} darray_##name;

#define DARRAY_TYPEDEF(name) \
typedef darray_##name darray_##name##_t;

#define DARRAY_NEW(name, data_type) \
darray_##name darray_##name##_new() \
{ \
    darray_##name self;\
    self.capacity = 8; \
    self.size = 0; \
    self.data = malloc(self.capacity * sizeof(data_type)); \
    return self; \
}

#define DARRAY_FREE(name, data_type) \
void darray_##name##_free(darray_##name *self) \
{ \
    free(self->data); \
    self->data = NULL; \
    self->size = 0; \
    self->capacity = 0; \
}

#define DARRAY_CLEAR(name, data_type) \
void darray_##name##_clear(darray_##name *self) { \
    if (self) self->size = 0; \
}

#define DARRAY_INIT(name, data_type) \
darray_##name darray_##name##_init(data_type *data, size_t count) \
{ \
    darray_##name self; \
    self.capacity = count + 10; \
    self.size = count; \
    self.data = malloc(self.capacity * sizeof(data_type)); \
    if (!self.data) { \
        self.size = 0; \
        self.capacity = 0; \
        return self; \
    } \
    if (data && count > 0) { \
        memcpy(self.data, data, count * sizeof(data_type)); \
    } \
    return self; \
}


#define DARRAY_RESERVE(name, data_type) \
void darray_##name##_reserve(darray_##name *self, size_t new_capacity) \
{ \
    if (!self) return; \
    if (new_capacity <= self->capacity) return; \
\
    data_type *new_data = realloc(self->data, new_capacity * sizeof(data_type)); \
    if (!new_data) return; \
\
    self->data = new_data; \
    self->capacity = new_capacity; \
}

#define DARRAY_SHRINK_TO_FIT(name, data_type) \
void darray_##name##_shrink_to_fit(darray_##name *self) \
{ \
    if (!self) return; \
    if (self->capacity == self->size) return; \
\
    if (self->size == 0) { \
        free(self->data); \
        self->data = NULL; \
        self->capacity = 0; \
        return; \
    } \
\
    data_type *new_data = realloc(self->data, self->size * sizeof(data_type)); \
    if (!new_data) return; \
\
    self->data = new_data; \
    self->capacity = self->size; \
}

#define DARRAY_BEGIN(name, data_type) \
data_type* darray_##name##_begin(darray_##name *self) \
{ \
    return self ? self->data : NULL; \
}

#define DARRAY_END(name, data_type) \
data_type* darray_##name##_end(darray_##name *self) \
{ \
    return self ? self->data + self->size : NULL; \
}

#define DARRAY_RBEGIN(name, data_type) \
data_type* darray_##name##_rbegin(darray_##name *self) { \
    return self ? self->data + self->size - 1 : NULL; \
}

#define DARRAY_REND(name, data_type) \
data_type* darray_##name##_rend(darray_##name *self) { \
    return self ? self->data - 1 : NULL; \
}

#define DARRAY_AT(name, data_type) \
data_type* darray_##name##_at(darray_##name *self, size_t idx) \
{ \
    if (!self) return NULL; \
    if (idx >= self->size) return NULL; \
    return &self->data[idx]; \
}

#define DARRAY_PUSH(name, data_type) \
void darray_##name##_push(darray_##name *self, data_type val) \
{ \
    if (!self) { return; } /* null check */ \
    /* grow if needed */ \
    if (self->size == self->capacity) \
    { \
        /* double capacity */ \
        size_t new_capacity = self->capacity ? self->capacity * 2 : 8; \
        data_type* new_data = realloc(self->data, new_capacity * sizeof(data_type)); \
        /* check if realloc failed */ \
        if(!new_data) { return; } \
        self->data = new_data; \
        self->capacity = new_capacity; \
    } \
    self->data[self->size++] = val; \
}

#define DARRAY_POP(name, data_type) \
bool darray_##name##_pop(darray_##name *self, data_type *output) \
{ \
    if (!self || self->size == 0) { return false; } /* null check and empty check */ \
    if (output) { *output = self->data[self->size - 1]; } \
    self->size--; \
    return true; \
}


#define DARRAY_REMOVE(name, data_type) \
bool darray_##name##_remove(darray_##name *self, size_t idx, data_type *output) \
{ \
    if (!self) { return false; } /* null check */ \
    if (idx >= self->size) { return false; } \
    /* return removed value */ \
    if (output) { *output = self->data[idx]; } \
    /* if last element, just shrink */ \
    if (idx == self->size - 1) { self->size--; return true; } \
    /* shift elements to the left */ \
    memmove(self->data + idx, self->data + idx + 1, (self->size - idx - 1) * sizeof(data_type)); \
    self->size--; \
    return true; \
}

#define DARRAY_INSERT(name, data_type) \
bool darray_##name##_insert(darray_##name *self, size_t idx, data_type val) \
{ \
    if (!self) { return false; } /* null check */ \
    if ( idx > self->size) { return false; } /* out of bounds check */ \
    /* grow if needed */ \
    if (self->size == self->capacity) \
    { \
        size_t new_capacity = self->capacity ? self->capacity * 2 : 8; \
        data_type* new_data = realloc(self->data, new_capacity * sizeof(data_type)); \
        if(!new_data) { return false; } \
        self->data = new_data; \
        self->capacity = new_capacity; \
    } \
    /* shift elements to the right */ \
    memmove(self->data + idx + 1, self->data + idx, (self->size - idx) * sizeof(data_type)); \
    /* insert the new value */ \
    self->data[idx] = val; \
    self->size += 1; \
    return true; \
}

#define DARRAY_APPEND(name, data_type) \
void darray_##name##_append(darray_##name *self, data_type *values, size_t count) \
{ \
    if(!self || !values || count == 0) { return; } \
    /* grow if needed */ \
    size_t required_capacity = self->size + count; \
    if(required_capacity > self->capacity) \
    { \
        size_t new_capacity = self->capacity ? self->capacity * 2 : 8; \
        while(new_capacity < required_capacity) { new_capacity *= 2; } \
        data_type* new_data = realloc(self->data, new_capacity * sizeof(data_type)); \
        if(!new_data) { return; } \
        self->data = new_data; \
        self->capacity = new_capacity; \
    } \
    /* append the new values */ \
    memcpy(self->data + self->size, values, count * sizeof(data_type)); \
    self->size += count; \
}

#define DARRAY_SLICE(name, data_type) \
bool darray_##name##_slice(darray_##name *self, size_t first_idx, data_type *slice, size_t slice_size) \
{ \
    if (!self || !slice) return false; \
    if (first_idx + slice_size > self->size) return false; \
    memcpy(slice, self->data + first_idx, slice_size * sizeof(data_type)); \
    return true; \
}

#define DARRAY_SLICE_INSERT(name, data_type) \
bool darray_##name##_slice_insert(darray_##name *self, size_t first_idx, data_type *slice, size_t slice_size) \
{ \
    if (!self || !slice) { return false; } \
    if ( first_idx > self->size) { return false; } \
    /* if inserting at the end, just append */ \
    if (first_idx == (self->size)) { darray_##name##_append(self, slice, slice_size); return true; } \
    /* grow if needed */ \
    size_t required_capacity = self->size + slice_size; \
    if(required_capacity > self->capacity) \
    { \
        size_t new_capacity = self->capacity ? self->capacity * 2 : 8; \
        while(new_capacity < required_capacity) { new_capacity *= 2; } \
        data_type* new_data = realloc(self->data, new_capacity * sizeof(data_type)); \
        if(!new_data) { return false; } \
        self->data = new_data; \
        self->capacity = new_capacity; \
    }\
    /* shift elements to the right */ \
    memmove(self->data + first_idx + slice_size, self->data + first_idx, (self->size - first_idx) * sizeof(data_type)); \
    /* insert the new values */ \
    memcpy(self->data + first_idx, slice, slice_size * sizeof(data_type)); \
    self->size += slice_size; \
    return true; \
}

#define DARRAY_SLICE_REMOVE(name, data_type) \
bool darray_##name##_slice_remove(darray_##name *self, size_t first_idx, data_type* slice, size_t slice_size) \
{ \
    if(!self) { return false; } \
    if(first_idx >= self->size) { return false; } \
    if(slice_size == 0 || first_idx + slice_size > self->size) { return false; } \
    /* copy the slice to output if provided */ \
    if(slice) { memcpy(slice, self->data + first_idx, slice_size * sizeof(data_type)); } \
    /* shift elements to the left */ \
    memmove(self->data + first_idx, self->data + first_idx + slice_size, (self->size - first_idx - slice_size) * sizeof(data_type)); \
    self->size -= slice_size; \
    return true; \
}

#define DARRAY_DECLARE(name, data_type) \
    DARRAY_STRUCT(name, data_type) \
    DARRAY_TYPEDEF(name) \
    DARRAY_NEW(name, data_type) \
    DARRAY_FREE(name, data_type) \
    DARRAY_CLEAR(name, data_type) \
    DARRAY_INIT(name, data_type) \
    DARRAY_RESERVE(name, data_type) \
    DARRAY_SHRINK_TO_FIT(name, data_type) \
    DARRAY_BEGIN(name, data_type) \
    DARRAY_END(name, data_type) \
    DARRAY_RBEGIN(name, data_type) \
    DARRAY_REND(name, data_type) \
    DARRAY_AT(name, data_type) \
    DARRAY_PUSH(name, data_type) \
    DARRAY_POP(name, data_type) \
    DARRAY_REMOVE(name, data_type) \
    DARRAY_INSERT(name, data_type) \
    DARRAY_APPEND(name, data_type) \
    DARRAY_SLICE(name, data_type) \
    DARRAY_SLICE_INSERT(name, data_type) \
    DARRAY_SLICE_REMOVE(name, data_type)

#endif // DARRAY_H