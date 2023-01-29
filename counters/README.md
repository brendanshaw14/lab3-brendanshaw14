#CS50 LAB 3
##CS50 23W

### Counters

A 'counters' is ultimately the same as a set (see `../set/README.md`). The set starts empty, and grows as the caller adds one _item_ at a time. Duplicates cannot be created; requests to add a duplicate will be ignored. _Items_ cannot be removed from the set until it is deleted. _Items_ in the set are stored as (_key_, _item_) pairs, where the key is a char* and the item is an `int`. There are no two counters with the same key.  

### Usage

The *counters* module, defined in 'counters.h' and implemented in 'counters.c', implements a set of counters and exports the following functions: 

```c
counters_t* counters_new(void);
int counters_add(counters_t* ctrs, const int key);
int counters_get(counters_t* ctrs, const int key);
bool counters_set(counters_t* ctrs, const int key, const int count);
void counters_print(counters_t* ctrs, FILE* fp);
void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count));
void counters_delete(counters_t* ctrs);
```

### Implementation 

The counters are implemented as a linked list. Counters are added at the head of the linked list, and an empty counters has a head pointer of NULL. The counters itself is implemented as a `struct counters`, containing a pointer to the head counter of the list. 

Each node in the set is a `struct counter`, which stores a `key`, a `count`, and a `next` pointer. 

To insert into the set, we create a new `counter` and make it the head of the set linked list. If an item with the same key already exists in the counter set, the item will not be added again, but rather its value will be incremented by 1. This is done with the counters_add function. 

The `counters_get` method searches the counters's linked list for the key given, returning 0 if the counter doesn't exist, and returning the value of the counter if it does exist.  

The `counters_set` function takes an input of a key, returning false if the key does not exist, and returning true after setting the counter with the input key to the value of the input count. 

The `counters_print` method allows the user to provide an output file and print the given counters to that file in a readable format. 

The `counters_iterate` method allows the user to provide a function to be applied to each item in the counter, then iterating through an applying the funciton to each counter in the set. 

The `counters_delete` method deletes the entire counter set. 

### Assumptions
No major assumptions were made- the counters module only requires `int` type keys and count values. 

### Files
*`Makefile` - compilation procedure and testing
* `counters.h` - the interface 
* `counters.c` - the module
* `counterstest.c` - the testfile 
* `testing.out` - the result of `make test &> testing.out`

### Compilation

To compile, `make`

### Testing 

`make test` compiles and runs the module and the test file, which carries out a variety of tests showing both edge cases and valid inputs. The tests demonstrates correct funciton of each method for all cases. 
See `testing.out` for test output. 
For valgrind, `myvalgrind ./counterstest.c`. 
