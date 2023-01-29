/* 
 * counterstest.c - test program for CS50 set module
 *
 * Author: Brendan Shaw, January 2023
 *
 * Input: Testfile is currently configured to run off of hard-coded inputs, so no file input is needed. However, the module does work with file input or stdin
 * Output: Testfile is currently configured to output to stdout, but the module works with any file output, and the test may be edited to do so as well. 
 * 
 * Use makefile for compile and test. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
#include "../lib/file.h"
#include "../lib/mem.h"


static void itemcount(void* arg, const int key, const int count);

int main(){
    counters_t* myCounters1 = NULL; //initialize two counters to null
    counters_t* myCounters2 = NULL;

    printf("\nTesting invalid counter add- null counters (should print empty counters): "); 
    counters_add(NULL, 5);
    counters_print(myCounters1, stdout);
    printf("\nInitializing the counter and adding 1: ");
    myCounters1 = counters_new();
    counters_add(myCounters1, 1); 
    counters_print(myCounters1, stdout);
    printf("\nTesting invalid counter add- negative key (should be the same as above): "); 
    counters_add(myCounters1, -1);
    counters_print(myCounters1, stdout);
    printf("\nTesting counter add- duplicate key (should print {1:2,}): "); 
    counters_add(myCounters1, 1);
    counters_print(myCounters1, stdout);

    printf("\nMaking a new counters with 1, 2, and 3:");
    myCounters2 = counters_new();
    counters_add(myCounters2, 1);
    counters_add(myCounters2, 2);
    counters_add(myCounters2, 3);
    counters_print(myCounters2, stdout);
    printf("\n");
    printf("\nTesting counters_get with null counters (should print 0):");
    printf("%d", counters_get(NULL, 1));
    printf("\nTesting counters_get with non-existent key (should print 0):");
    printf("%d", counters_get(myCounters2, 9));
    printf("\nTesting counters_get with valid key (should print 1):");
    printf("%d", counters_get(myCounters2, 2));

    printf("\n\nTesting counters_set with null counter- should print false: ");
    if(counters_set(NULL, 1, 5)== false){
        printf("false");
    }
    printf("\nTesting counters_set with invalid key- should print false: ");
    if(counters_set(myCounters1, 5, 5)== false){
        printf("false");
    }
    printf("\nTesting counters_set with invalid counter value- should print false: ");
    if(counters_set(myCounters1, 1, -1)== false){
        printf("false");
    }
    printf("\nPrinting counter again to show no changes were made by get: ");
    counters_print(myCounters2, stdout);

    printf("\nTesting counters_print with NULL fp- should print nothing: ");
    counters_print(myCounters2, NULL);
    printf("\nTesting counters_print with NULL counters- should print nothing: ");
    counters_print(NULL, stdout);

    printf("\n\nTesting counters_iterate with NULL counters- (should be 0)");
    int counterCount = 0;
    counters_iterate(NULL, &counterCount, itemcount);
    printf("\nNumber of counters found by iterator: %d", counterCount);
    printf("\nTesting counters_iterate with NULL itemfunc- (should be 0)");
    counterCount = 0;
    counters_iterate(myCounters2, &counterCount, NULL);
    printf("\nNumber of counters found by iterator: %d", counterCount);
    printf("\nTesting valid counters_iterate- (should be 3)");
    counterCount = 0;
    counters_iterate(myCounters2, &counterCount, itemcount);
    printf("\nNumber of counters found by iterator: %d", counterCount);

    counters_delete(myCounters1);
    counters_delete(myCounters2);

}

//itemcount function written specifically for testing counters_iterator- increments and returns number of items. Can be altered for other use.
static void itemcount(void* arg, const int key, const int count)
{
  int* nitems = arg;

    if (nitems != NULL && count >= 0){
        (*nitems)++;
    }
}

