#CS50 LAB 3
##CS50 23W

### Hashtable

A 'hashtable' is ultimately the same as a set (see `../set/README.md`), except it uses an array of sets as hashslots, allowing for greater efficiency with large collections. The set starts empty, and grows as the caller adds one _item_ at a time. Duplicates cannot be created; requests to add a duplicate will be ignored. _Items_ cannot be removed from the set until it is deleted. _Items_ in the set are stored as (_key_, _item_) pairs, where the key is a char* and the item is an `int`. There are no two counters with the same key. 

### Usage

The *hashtable* module, defined in 'hashtable.h' and implemented in 'hashtable.c', implements an array of `set*` pointers and exports the following functions: 

```c
hashtable_t* hashtable_new(const int num_slots);
bool hashtable_insert(hashtable_t* ht, const char* key, void* item);
void* hashtable_find(hashtable_t* ht, const char* key);
void hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item));
void hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) );
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item) );
```

### Implementation 

The hashtable is implemented as an array of set pointers. _Item_ keys are given to the hash function, which assigns an index based on the input string and size of the hashtable (number of slots). The item is then added at the head of the linked list of the set in its calculated hash slot. An empty hashtable's sets are initialized with a head pointer `NULL`. The hashtable itself is implemented as a `struct hashtable`, containing an array of sets and an integer that records the size of the table. The table size does not change. 

Each node in the hashtable is a `struct setNode`, which stores a `key`, an `item`, and a `next` pointer, just like a set. However, no work needs to be done with regard to these in the hashtable module beacause the hashtable module relies upon the set module to implement these. 

To insert into the hashtable, we simply give the key string to the hash function, which tells us which set of the hashtable to insert to. Then, the `set_insert` method is used to insert into that specifc set.  If an item with the same key already exists in the target set, the item will not be added again. This is done with the hashtable_insert method. 

The `hashtable_find` method searches the hashtable's array list, using the set_find method to see if the given key exists in each set. It then returns NULL if the item is not found, or the `void* item` if it is found. 

The `hashtable_print` method allows the user to provide an output file and print the given hashtable to that file in a readable format of multiple sets. 

The `hashtable_iterate` method allows the user to provide a function to be applied to each item in the hashtable, then iterating through an applying the funciton to each item in each set in the hashtable. 

The `hashtable_delete` method deletes the entire hashtable, freeing all previously allocated memory.  

### Assumptions
No major assumptions were made- the hashtable module only requires `char*` type keys. `void*` items are accepted. Again, as in set, (see the set README.md), the caller is responsible for providing any necessary `mem_free` or `free` calls in their `*itemdelete` function that is given to the hashtable_delete method-- the hashtable module will only delete any memory it allocates for itself. 

### Files
*`Makefile` - compilation procedure and testing
* `hashtable.h` - the interface 
* `hashtable.c` - the module
* `hashtabletest.c` - the testfile 
* `hash.h` - the hash function header
* `hash.c` - the hash function module
* `testing.out` - the result of `make test &> testing.out`

### Compilation

To compile, `make`

### Testing 

`make test` compiles and runs the module and the test file, which carries out a variety of tests showing both edge cases and valid inputs. The tests demonstrates correct funciton of each method for all cases. 
See `testing.out` for test output. 
For valgrind, `myvalgrind ./hashtabletest.c`. 
