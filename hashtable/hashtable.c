/* 
 * hashtable.h - header file for CS50 hashtable module
 *
 * A *hashtable* is a set of (key,item) pairs.  It acts just like a set, 
 * but is far more efficient for large collections.
 *
 * Brendan Shaw, January 2023 
 */

#ifndef __HASHTABLE_H
#define __HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "hash.h"
#include "../set/set.h"
#include "../lib/file.h"
#include "../lib/mem.h"


/**************** global types ****************/
typedef struct hashtable {
    set_t ** setTable;
    int tableSize;
}  hashtable_t;

/**************** functions ****************/

/**************** hashtable_new ****************/
//see hashtable.h for more info 
hashtable_t* hashtable_new(const int num_slots){
    if (num_slots <= 0){ //check valid args
        return NULL;
    }
    else {
        //make a new hashtable
        hashtable_t* newHashtable = malloc(sizeof(hashtable_t));
        if (newHashtable == NULL){ //check it was made correctly
            return NULL;
        }
        //initialize values
        newHashtable -> setTable = calloc(num_slots, sizeof(set_t*));
        newHashtable -> tableSize = num_slots;
        //create new sets for each hashslot 
        for (int i = 0; i < num_slots; i++){
            newHashtable -> setTable[i] = set_new();
        }
        return newHashtable;
    }
}
/**************** hashtable_insert ****************/
//see hashtable.h for more info 
bool hashtable_insert(hashtable_t* ht, const char* key, void* item){
    if (ht == NULL || key == NULL || item == NULL){ //check null args
        return false;
    }
    int index = hash_jenkins(key, ht -> tableSize);// which slot to put the item into 
    set_insert(ht -> setTable[index], key, item); //insert at the proper hash slot set 
    return true;
}


/**************** hashtable_find ****************/
//see hashtable.h for more info 
void* hashtable_find(hashtable_t* ht, const char* key){
    if (ht == NULL || key == NULL){ //check valid args
        return NULL;
    }
    int index = hash_jenkins(key, ht -> tableSize); //get index with hash 
    if (set_find(ht -> setTable[index], key) != NULL){ //check if item was found in set
        return set_find(ht -> setTable[index], key); //return pointer to item if so 
    }
    else{
        return NULL; //otherwise return null
    }
}

/**************** hashtable_print ****************/
//see hashtable.h for more info 
void hashtable_print(hashtable_t* ht, FILE* fp, 
                     void (*itemprint)(FILE* fp, const char* key, void* item)){
    if (fp == NULL){ //check null args
        return;
    }
    if (ht == NULL){ //check null hashtable 
        printf("(null)");
        return;
    }
    if (itemprint == NULL){ //print empty if no itemprint
        for (int i = 0; i < ht -> tableSize; i ++){
            printf("\n{}");
        }
        return;
    }
    else { 
        //loop through table
        for (int i = 0; i < ht -> tableSize; i ++){
            set_print(ht->setTable[i], fp, itemprint); //print each set
            printf("\n");
        }
    }
    return;
}

/**************** hashtable_iterate ****************/
//see hashtable.h for more info 
void hashtable_iterate(hashtable_t* ht, void* arg,
                       void (*itemfunc)(void* arg, const char* key, void* item) ){
    if (ht == NULL || itemfunc == NULL){ //check null args
        return; 
    }
    //loop through the table
    for (int i = 0; i < ht -> tableSize; i++){
        set_iterate(ht -> setTable[i], arg, itemfunc); //loop through each set
    }
} 
/**************** hashtable_delete ****************/
//see hashtable.h for more info 
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item) ){
    if (ht == NULL || itemdelete == NULL){ //check null args 
        return; 
    }
    //loop through the table
    for (int i = 0; i < ht -> tableSize; i++){
        //delete each set
        set_delete(ht -> setTable[i], (*itemdelete));
    }
    mem_free(ht -> setTable); //free the tableset
    mem_free(ht); //free the hashtable
    #endif
}



