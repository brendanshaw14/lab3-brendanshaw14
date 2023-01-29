/* 
 * counters.c - CS50 counters module: see header file for more info 
 *
 *  
 * Author: Brendan Shaw, January 2023 
 */

#ifndef __COUNTERS_H
#define __COUNTERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
#include "../lib/mem.h"
#include <stdbool.h>


/**************** local types ****************/
typedef struct counter {
    int key;
    int count; 
    struct counter *next;
} counter_t;

/**************** global types ****************/
typedef struct counters { // opaque to users of the module
    struct counter *head; 
} counters_t;

/**************** functions ****************/

/**************** FUNCTION ****************/
//see counters.h for more info  

counters_t* counters_new(void){
    counters_t* counters = mem_malloc(sizeof(counters_t)); //malloc for the counters
    if (counters == NULL){ //check for success
        return NULL;
    }
    else{ //if success, initialize head and return the counters
        counters -> head = NULL;
        return counters;
    }
}

/**************** counters_add ****************/
// see counters.h for more info 

int counters_add(counters_t* ctrs, const int key){
    if (ctrs != NULL && key >= 0){ //check valid counters and key
        //loop thorugh counters
        for (counter_t* currentCounter = ctrs -> head; currentCounter != NULL; currentCounter = currentCounter -> next) {
            //if the current counter's key = the new key, increment the counter and return the value after increment. 
            if (currentCounter -> key == key){ 
                currentCounter -> count ++;
                return currentCounter -> count;
            }
        }
        //otherwise, make a new counter with the input key, starting with a count of 1
        counter_t* newCounter = mem_malloc(sizeof(counter_t));
        newCounter -> key = key;
        newCounter -> count = 1;
        newCounter -> next = ctrs -> head;
        ctrs -> head = newCounter;
        return 1;
    }
    return 0;
}
/**************** counters_get ****************/
int counters_get(counters_t* ctrs, const int key){
    if (ctrs == NULL || key < 0){ //check for null or invalid input, return 0 if so
        return 0;
    }
    //loop thorugh counters
    for (counter_t* counter = ctrs -> head; counter != NULL; counter = counter -> next) {
        if (counter -> key == key){
            return counter -> count; //return the count if found
        }
    }
    return 0; //return 0 if not found
}

/**************** counters_set ****************/
// see counters.h for more info 

bool counters_set(counters_t* ctrs, const int key, const int count){
    if (ctrs != NULL && key >= 0 && count >= 0){ //check valid counters, key, and count
        //loop through the counters
        for (counter_t* counter = ctrs -> head; counter != NULL; counter = counter -> next) {
            //if the counter already exists, set it's count value to the argument value provided
            if (counter -> key == key){
                counter -> count = count;
                return true;
            }
        }
        //otherwise, make a new counter, initializing its count to the input argument, and add it to the counters set. 
        counter_t* newCounter = mem_malloc(sizeof(counter_t));
        newCounter -> key = key;
        newCounter -> count = count;
        newCounter -> next = ctrs -> head;
        ctrs -> head = newCounter;
        return true; 
    }    
    return false;
}
/**************** counters_print ****************/
//see counters.h for more info
void counters_print(counters_t* ctrs, FILE* fp){
    if (fp != NULL){ //check null file 
        if (ctrs == NULL){ //check null counters
            printf("(null)");
        }
        else{ //print the counters
            printf("{");
            for (counter_t* counter = ctrs -> head; counter != NULL; counter = counter -> next) {
                printf("%d:%d,", counter -> key, counter -> count);
            }
            printf("}");
        }
    }        
}

/**************** counters_iterate ****************/
//see counters.h for more info.
void counters_iterate(counters_t* ctrs, void* arg, 
                      void (*itemfunc)(void* arg, 
                                       const int key, const int count)){
    if (ctrs != NULL && itemfunc != NULL){ //check valid args
        //loop through counters, applying function to each
        for (counter_t* counter = ctrs -> head; counter != NULL; counter = counter -> next){
            (*itemfunc)(arg, counter -> key, counter -> count);
        }
    }
}
                                       
/**************** counters_delete ****************/
// see counters.h for more info 
void counters_delete(counters_t* ctrs){
    if (ctrs != NULL) { //check valid args
        //loop through counters
        for (counter_t* counter = ctrs -> head; counter != NULL;) {
            counter_t* next = counter -> next;     // remember what comes next
            mem_free(counter);                     // free mem of the counter  
            counter = next;                    
        }
    mem_free(ctrs);                                // free the mem of the counters struct 
  }
}

#endif // __COUNTERS_H
