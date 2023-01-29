/* 
 * set.c - CS50 'set' module for Lab 3
k*
 * see set.h for more information.
 *
 * Author: Brendan Shaw, 2023 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "../lib/mem.h"


/**************** local types ****************/
typedef struct setNode {
    void* item;
    char* key; 
    struct setNode *next;
} setNode_t;

/***************local functions****************/
static setNode_t* setNodeNew(void* item,const char* key);
/**************** global types ****************/
typedef struct set {
    struct setNode *head; 
} set_t;

/**************** functions ****************/

/**************** set_new ****************/
//see set.h for more info. 

set_t* set_new(void){
    set_t* set = mem_malloc(sizeof(set_t)); //allocate mem
    if (set == NULL){ //make sure mem was allocated
        return NULL;
    }
    else{ //otherwise initialize the head and return the set
        set -> head = NULL;
        return set;
    }
}

/**************** set_insert ****************/
//see set.h for more info. 

bool set_insert(set_t* set, const char* key, void* item){
    if (set != NULL && key != NULL && item != NULL) {
        //loop through the set's nodes
        for (setNode_t* currentNode = set -> head; currentNode != NULL; currentNode = currentNode->next) {
            //check for key match and abort if already exists
            if (strcmp(currentNode -> key, key) == 0){
                return false;
            }
        }
        //otherwise, make a new node, set its next to be the head, and then make the new node the head
        setNode_t* newNode = setNodeNew(item,key);
        newNode -> next = set -> head;
        set -> head = newNode;
        return true;
    }
    return false;
}

/**************** setNodenew ****************/
//see set.h for more info

static setNode_t* setNodeNew(void* item, const char* key){
    setNode_t* node = mem_malloc(sizeof(setNode_t)); //alloc memory for the new node
    if (node == NULL){ //check for success
        return NULL; 
    }
    else { //if success, initialize the node's item and key, making a copy of the key in memory for use by the module
        node -> item = item; 
        node -> next = NULL;
        node -> key = mem_malloc(sizeof(char)*strlen(key) + 1);
        strcpy(node -> key, (char*) key); 
        return node;
   }
}
/**************** set_find ****************/
//see set.h for more info
void* set_find(set_t* set, const char* key){
    if (set != NULL && key != NULL) {
        //loop through the set
        for (setNode_t* currentNode = set -> head; currentNode != NULL; currentNode = currentNode -> next){
            if (strcmp(currentNode -> key, key) == 0){ //if the node exists, return it
                return currentNode -> item;
            }
        }
    }
    //otherwise return null
    return NULL;
}
/**************** set_print ****************/
//see set.h for more info
void set_print(set_t* set, FILE* fp, 
               void (*itemprint)(FILE* fp, const char* key, void* item) ){
    if (fp != NULL) {
        if (set != NULL) {
            fputc('{', fp);
            //loop through the set and apply the print function to each node
            for (setNode_t* node = set -> head; node != NULL; node = node -> next){
                if (itemprint != NULL) {
                    (*itemprint)(fp, node -> key, node -> item);
                    fputc(',', fp);

                }
            }
            fputc('}', fp);
        }
        else {
            fputs("(null)", fp); //print this if the file exists but the set doesn't
        }
    }
}


/**************** set_iterate ****************/
//see set.h for more info
void set_iterate(set_t* set, void* arg,
                 void (*itemfunc)(void* arg, const char* key, void* item) ){
    if (set != NULL && itemfunc != NULL) {
        //loop through the set and apply itemfunc to each node
        for (setNode_t* node = set->head; node != NULL; node = node->next) {
            (*itemfunc)(arg, node -> key, node -> item); 
        }
    }
}

/**************** set_delete ****************/
//see set.h for more into

void set_delete(set_t* set, void (*itemdelete)(void* item) ){
  if (set != NULL && itemdelete != NULL) {
    //loop through the set
    for (setNode_t* node = set -> head; node != NULL; ) {
      (*itemdelete)(node -> item);      // delete node's item
      mem_free(node -> key);            // free the key
      setNode_t* next = node -> next;     // remember what comes next
      mem_free(node);                   // free the node
      node = next;                      // and move on to next
    }
    mem_free(set);                      //free the set itself
  }

#ifdef MEMTEST
#endif
   return;
}


