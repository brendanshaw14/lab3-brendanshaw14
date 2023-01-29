/* 
 * hashtable.c - test program for CS50 hashtable module
 *
 * Author: Brendan Shaw: CS50 23W
 * 
 * Inputs/Outputs this file is made with hardcoded inputs, but the module accepts any file pointer inputs or outputs. 
 *
 * Compile: the makefile included compiles automatically.  
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "hash.h"
#include "../set/set.h"
#include "../lib/file.h"
#include "../lib/mem.h"

void deleteWord(void* item);
void printWords(FILE* fp, const char* key, void* item);
static void itemcount(void* arg, const char* key, void* item);

int main(){
    hashtable_t* myHashtable1 = hashtable_new(3);
    hashtable_t* myHashtable2 = hashtable_new(8);
    //insert tests
    printf("Testing hashtable_insert with null ht- should be false: ");
    if (!hashtable_insert(NULL, "name1", "brendan")){
        printf("False");
    }
    printf("\nTesting hashtable_insert with null key- should be false: ");
    if (!hashtable_insert(myHashtable1, NULL, "brendan")){
        printf("False");
    }
    printf("\nTesting hashtable_insert with null item- should be false: ");
    if (!hashtable_insert(myHashtable1, "name1", NULL)){
        printf("False");
    }
    printf("\nTesting hashtable_insert with valid parameters- should be true:");
    if (hashtable_insert(myHashtable1, "name1", "brendan")){
        printf("True");
    }
    printf("\nPrinting hashtable- should have only two empty slots and (name1, brendan)\n");
    hashtable_print(myHashtable1, stdout, printWords);
    //find tests
    printf("\nTesting hashtable_find with NULL hashtable- (should be (null)): ");
    printf("Found %s", (char*)hashtable_find(NULL, "name1"));    
    printf("\nTesting hashtable_find with NULL key- (should be (null)): ");
    printf("Found %s", (char*)hashtable_find(myHashtable1, NULL));
    printf("\nTesting hashtable_find with non-existent key- (should be (null)): ");
    printf("Found %s", (char*)hashtable_find(myHashtable1, "name5"));
    printf("\nTesting hashtable_find with \"name1\"- (should be brendan): ");
    printf("Found %s", (char*)hashtable_find(myHashtable1, "name1"));

    //print tests
    printf("\nMaking a new hashtable with some more items in it for print demos:");
    hashtable_insert(myHashtable2, "item1", "chill");
    hashtable_insert(myHashtable2, "item2", "histo");
    hashtable_insert(myHashtable2, "item3", "words");
    hashtable_insert(myHashtable2, "item4", "tinySearch");
    hashtable_insert(myHashtable2, "item5", "hashtable");
    hashtable_insert(myHashtable2, "item6", "set");
    hashtable_insert(myHashtable2, "item7", "counters");

    printf("\nTesting print with null fp- should print nothing: ");
    hashtable_print(myHashtable2, NULL, printWords);
    printf("\nTesting print with null ht- should print (null): ");
    hashtable_print(NULL, stdout, printWords);
    printf("\nTesting print with null itemprint- should print empty hashtable: ");
    hashtable_print(myHashtable2, stdout, NULL);
    printf("\nTesting valid print- should print full hashtable: ");
    hashtable_print(myHashtable2, stdout, printWords);

    //iterate tests: 
    int count = 0; 
    printf("\nTesting hashtable_iterate with null ht- should print 0:)");
    hashtable_iterate(NULL, &count, itemcount);
    printf("\nFound: %d items", count);
    count = 0; 
    printf("\nTesting hashtable_iterate with null itemfunc- should print 0:)");
    hashtable_iterate(myHashtable2, &count, NULL);
    printf("\nFound: %d items", count);
    count = 0; 
    printf("\nTesting hashtable_iterate with valid inputs- should print 7:");
    hashtable_iterate(myHashtable2, &count, itemcount);
    printf("\nFound: %d items", count);

    //delete the tables
    hashtable_delete(myHashtable1, deleteWord);
    hashtable_delete(myHashtable2, deleteWord);
} 

//printwords for use in this context only- alterations may need to be made for outside use
void printWords(FILE* fp, const char* key, void* item){
    if (item == NULL){
        fprintf(fp, "(null)");
    }
    else {
        fprintf(fp, "(");
        fprintf(fp, "%s,%s", key, (char*) item);
        fprintf(fp, ")");
    }
}
//delete a word 
void deleteWord(void* item)
{
    //if (item != NULL){
        //mem_free(item);
    //}
}
//increment nitems and return
static void itemcount(void* arg, const char* key, void* item)
{
  int* nitems = arg;

    if (nitems != NULL && item != NULL){
        (*nitems)++;
    }
}