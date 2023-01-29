/* 
 * settest.c - test program for CS50 set module
 *
 * Author: Brendan Shaw
 * CS50- 23W
 * 
 * Input: the testfile is currently configured to run with hard-coded names, so no input is needed. 
 *    However, the set module can accept stdin or any other file pointer. 
 * Output: the testfile is currently configured to output to stdout, but 
 * 
 * Use makefile for compile and test. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "../lib/file.h"
#include "../lib/mem.h"


void printWords(FILE* fp, const char* key, void* item);
static void itemcount(void* arg, const char* key, void* item);
void deleteWord(void* item); 

int main(){
  set_t* set1 = NULL;           // one set
  set_t* set2 = NULL;           // another set
  int setcount = 0;             // number of names found in a bag

  printf("Create first set...\n");
  set1 = set_new();
  if (set1 == NULL) {
    fprintf(stderr, "set_new failed for set1\n");
    return 1;
  }
  printf("\nTest with null set, good item...\n");
  set_insert(NULL, "name1", "Dartmouth");
  printf("test with null item...\n");
  set_insert(set1, "name2", NULL); 
  printf("test with null set, null item...\n");
  set_insert(NULL, "name 3", NULL);
  printf("test with null key, good item");
  set_insert(set1, NULL, "Dartmouth");
  printf("test with null set, null key, null item");
  set_insert(NULL, NULL, NULL);
  printf("test with null set and null key");
  set_insert(NULL, NULL, "Dartmouth");
  printf("test with null key and null item");
  set_insert(set1, NULL, "Dartmouth");

  printf("\nCount (should be zero): ");
  set_iterate(set1, &setcount, itemcount);
  printf("%d\n", setcount);

  printf("\nTesting set_insert...Inserting three items.\n");
  set_insert(set1, "item1", "cat");
  set_insert(set1, "item2", "dog"); 
  set_insert(set1, "item3", "tree"); 
  printf("\nThe set:\n");
  set_print(set1, stdout, printWords); 

  setcount = 0;
  set_iterate(set1, &setcount, itemcount);
  printf("\n\nTesting iterator: Count (should be 3): ");
  printf("%d", setcount);
  setcount = 0;
  printf("\nTesting iterator with null set: (should print 0 because itemfunc will not be used): ");
  set_iterate(set2, &setcount, itemcount);
  printf("%d", setcount);
  setcount = 0;
  printf("\nTesting iterator with invalid itemfunc: (should print 0 again): ");
  set_iterate(set2, &setcount, NULL);
  printf("%d", setcount);
  printf("\nTesting print with null itemfunc: (should print empty set): ");
  set_print(set1, stdout, NULL);
  printf("\nTesting print with null file: (should print nothing): ");
  set_print(set1, NULL, printWords);
  printf("\nTesting print with null set: (should print (null)): ");
  set_print(NULL, stdout, printWords);
  printf("\nPrinting Correctly: ");
  set_print(set1, stdout, printWords);

  printf("\n\nMake a new set");
  set2 = set_new();
  if (set2 == NULL) {
    fprintf(stderr, "set_new failed for set2\n");
    return 2;
  }
  printf("Put item Shay with key name1 and item Aidan withe key name2 in the set: \n");
  set_insert(set2, "name1", "Shay");
  set_insert(set2, "name2", "Aidan"); 
  set_print(set2, stdout, printWords);

  printf("\nTesting adding a duplicate key");
  if (set_insert(set2, "name2", "Aidan") == false){
    printf("\nDuplicate found, add prevented. ");
  }
  else {
    printf("\n set_add error: duplicate was not recognized. The set currently: "); 
  }
  printf("\nThe set after attempting to add duplicate: Should still be {Aidan,Shay,}:");
  set_print(set2, stdout, printWords);

  printf("\nTesting set_find with key in set (should find \"Aidan\"): Found item ");
  printf("%s", (char*)set_find(set2, "name2"));
  printf("\nTesting set_find with key not in set: Found item (should be (null)) ");
  printf("%s", (char*)set_find(set2, "name5"));
  printf("\nTesting set_find with null set (should print (null)): ");
  printf("%s", (char*)set_find(NULL, "name2"));
  printf("\nTesting set_find with null key (should print (null)): ");
  printf("%s", (char*)set_find(set2, NULL)); 
  printf("\nCount items in the new set- should be 2:"); 
  setcount = 0;
  set_iterate(set2, &setcount, itemcount);
  printf("%d\n", setcount); 
  printf("\nPrint the set: should have Shay, Aidan\n"); 
  set_print(set2, stdout, printWords);
  printf("\n");

  printf("\ndelete the sets...\n");
  set_delete(set1, deleteWord);
  set_delete(set2, deleteWord);
  return 0;
}

//tests to see if the item exists, if so it prints that item to the given outfile
//written for use by only this testfile- must be changed for individual needs 
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

//if the item and input argument both exist, the function increments the input argument. 
static void itemcount(void* arg, const char* key, void* item)
{
  int* nitems = arg;

    if (nitems != NULL && item != NULL){
        (*nitems)++;
    }
}

//delete a word 
void deleteWord(void* item)
{
  //nothing is included in this function because we have not malloc'd for the items- system allocs and frees the char* on its own. 
}