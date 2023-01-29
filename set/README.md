#CS50 LAB 3
##CS50 23W

### Set

A 'set' is an unordered collection of _items_. The set starts empty, and grows as the caller adds one _item_ at a time. Duplicates cannot be created; requests to add a duplicate will be ignored. _Items_ cannot be removed from the set until it is deleted. _Items_ in the set are stored as (_key_, _item_) pairs, where the key is a char* and the item is a void*. There are no two items with the same key. 

### Usage

The *set* module, defined in 'set.h' and implemented in 'set.c', implements a set and exports the following functions: 

```c
set_t* set_new(void);
bool set_insert(set_t* set, const char* key, void* item);
void* set_find(set_t* set, const char* key);
void set_print(set_t* set, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item) );
void set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) );
void set_delete(set_t* set, void (*itemdelete)(void* item) );
```

### Implementation 

This set is implemented as a linked list. Items are added at the head of the linked list, and an empty bag has a head pointer of NULL. The set itself is implemented as a `struct set`, containing a pointer to the head of the list. 

Each node in the set is a `struct setNode`, which stores a `key`, an `item`, and a `next` pointer. 

To insert into the set, we create a new `setNode` and make it the head of the set linked list. If an item with the same key already exists in the set, the item will not be added. This is done with the set_insert function. 

The `set_find` method searches the set's linked list for the key given, returning true if found and false if not. 

The `set_print` method allows the user to provide an output file and print the given set to that file in a readable format. 

The `set_iterate` method allos the user to provide a function to be applied to each item in the set, then iterating through an applying the funciton to each element in the set. 

The `set_delete` method deletes the entire set, freeing all previously allocated memory, also allowing the user to input a function to be applied to each element and assist with deleting. 

### Assumptions
No major assumptions were made- the set module only requires `char*` type keys, but allows for any type of item. The main thing to be noted is that the set module will not free any memory allocated by the user themselves, so the user must adapt the function that they pass to the set_delete method to make sure that it takes care of any allocated memory without invalid reads. In my test, I leave the function I pass to set_delete empty because the test file does not allocate any memory that needs to be freed. 

### Files
*`Makefile` - compilation procedure and testing
* `set.h` - the interface 
* `set.c` - the module
* `settest.c` - the testfile 
* `testing.out` - the result of `make test &> testing.out`

### Compilation

To compile, `make`

### Testing 

`make test` compiles and runs the module and the test file, which carries out a variety of tests showing both edge cases and valid inputs. The tests demonstrates correct funciton of each method for all cases. 
See `testing.out` for test output. 
For valgrind, `myvalgrind ./settest.c`. 
