# DStructs

Header only library for creating Data Structures in C.
Work in progress.

- Create DataStructures in C quickly.
- Header only. Use only what you need. Headers found in DStructs folder.
- Easy to use.


## Example

**DArray** is a dynamically allocated array. Like vector in c++. Can be found in ***DArray.h*** 

    // DArray_Declare(name, data_type)
>   Where **name** is the identifier to add to the data structure.
>   Where **data_type** is the data type this data structure will work with.

    // int example
    DArray_Declare(i, int);
>   Creates the struct ***darray_i*** along with functions to create, pop, push and free ***darray_i***

    darray_i ivalues = darray_i_new(); // creates a new and empty darray_i
    darray_i_push(&ivalues, 23); // pushes a value at the end of the provided darray_i
    int val = darray_i_pop(&ivalues); // returns the value at the end of darray_i and removes it from data[]
    darray_i_free(&ivalues); // frees all allocated memory

>   darray_i has members size, capacity, type_size, and data[]. <br>
>   - data: an array of data_type. In this example int.
>   - size: the size of the data array. (Number of elements)
>   - capacity: the size of the allocated memory.
>   - type_size: size of the data_type. In this example sizeof(int)

    for(int = 0; i < darray_i.size; i++)
    {
        printf("%d\n", darray.data[i]);
    }
