# DStructs

Header only library for creating Data Structures in C.
Work in progress.

- Create Data Structures in C quickly.
- Header only. Use only what you need. Headers found in DStructs folder.
- Easy to use.

## **DArray** 
***DArray*** is a dynamically allocated stack style array. Like vector in C++. Can be found in ***DArray.h*** 

    DArray_Declare(name, data_type);
>   Where **name** is the identifier to give to the data structure.<br>
>   Where **data_type** is the data type this data structure will work with.


For example a float DArray is declared as follows

    DArray_Declare(f, float);
>   Creates the struct ***darray_f*** along with functions to create, pop, push and free ***darray_f***

>   darray_f will have members size, capacity, type_size, and data[]. <br>
>   - data: an array of data_type. In this example float.
>   - size: the size_t count of values in the data array. (Number of elements)
>   - capacity: the size_t count of the allocated memory available.
>   - type_size: size of the data_type in bytes. In this example sizeof(float)
<br><br>

    darray_f fvalues = darray_f_new();
> Creates a new and empty darray_f. Dynamically allocates memory.

    darray_f ivalues = darray_f_init(float* data, size_t count)
> Creates a new populated darray_f struct with values copied from float* data of size_t count. Dynamically allocates memory.

    darray_f_free(darray_f *darray);
> Frees all allocated memory

    darray_f_push(darray_f *darray, data_type val);
> Pushes a val at the end of the provided darray_f

    int result = darray_f_pop(darray_f *darray, float *output);
> Removes the last value of darray_f->data. <br>
 If an output pointer is given, the value is stored there. <br>
 Returns 0 on failure 1 on success.

    int result = darray_f_remove(darray_f *darray, size_t idx, float *output)
> Removes the value at the given index. <br>
 If an output pointer is supplied, the value is stored there. <br>
 Returns 0 on failure, 1 on success.

    int result = darray_f_insert(darray_f *darray, size_t idx, float val)
> Inserts a value at the given index (idx). <br>
Returns 0 on failure, 1 on success

    darray_f_append(darray_f *darray, float *values, size_t count);
> Appends an array of data_type (float in this example) with a count of size_t to the end of darray->data. <br>

    int result = darray_f_slice(darray_f *darray, size_t first_idx, float *slice, size_t slice_size);
> Copies a slice of values from darray->data to an array of data_type (float in this example) at the index (first_idx). <br> Returns 0 on failure, 1 on success.

    int result = darray_f_slice_insert(darray_f *darray, size_t first_idx, float *slice, size_t slice_size);
> Inserts an array (slice) of data_type (float in this example) into darray->data at index (first_idx). <br> Returns 0 on failure, 1 on success.

    int darray_f_slice_remove(darray_f *darray, size_t first_idx, float* slice, size_t slice_size);
> Removes a slice of values from darray->data  and puts them in an array (slice) if provided. <br> Returns 0 on failure, 1 on success.
<br><br>

## **DSList**
***DSList*** is a singally-linked list. Can be found in ***DSList.h*** 

    DSList_Declare(name, data_type);
>   Where **name** is the identifier to give to the data structure.<br>
>   Where **data_type** is the data type this data structure will work with.

For example a float DSList is declared as follows

    DSList_Declare(f, float);
>   Creates the struct ***dslist_f*** along with functions to create insert, search, and free ***dslist_f***. It will also create a corresponding node structure ***dslist_node_f***.

>  **dslist_f**
>   - darray_f will have members size, type_size, and head and tail nodes of type ***dslist_node_f***. <br>
>   - head: **dslist_node_f** node at the beginning of a list.
>   - tail: **dslist_node_f** node at the end of a list.
>   - size: the size_t count of values in the singly linked list. (Number of elements).
>   - type_size: size of the data_type in bytes. In this example sizeof(float).
<br><br>

>  **dslist_node_f**
>   - dslist_node_f will have a data field and a next node.
>   - data: a field of data_type(float in this example).
>   - next: **dslist_node_f** that points to the next node in the list chain.
<br>