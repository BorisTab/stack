#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include "stack.h"

#define DEBUG

enum errorsCode {
    TESTS_FAILED = 10,
};


/*!
	@file
    @brief My stack
*/

int tests();

bool stackPushChecker(Stack_t *stk, stkElem_t value);

bool stackPopChecker(Stack_t *stk, stkElem_t awaitPopedValue);

int main() {
//    Stack_t intStack = {};
//    if (stackConstruct(&intStack)) return STACK_CONSTRUCT_FAILED;
//    intStack.name = "intStack";
//
//    for (int i = 0; i <= 10; i++) {
//        stackPush(&intStack, i);
//    }
//    int popedVar = 5;
//    if (stackPop(&intStack, &popedVar)) return STACK_EMPTY;
//    if (stackPop(&intStack, &popedVar)) return STACK_EMPTY;
//
//    stackDump(&intStack);
//    stackDestruct(&intStack);

//    __uint32_t a = hash((const __uint8_t *) &intStack.data, intStack.maxDataSize, 100);

    int failedTests = tests();
    if (failedTests) {
        printf("\n%d tests failed\n", failedTests);
        return TESTS_FAILED;
    }

    return 0;
}

int tests() {
    Stack_t intStack = {};
    if (stackConstruct(&intStack)) return STACK_CONSTRUCT_FAILED;
    intStack.name = "intStack";

    int errors = 0;

    printf("1 ");
    !stackPushChecker(&intStack, 5) ? errors++ : NULL;

    printf("2 ");
    !stackPushChecker(&intStack, 0) ? errors++ : NULL;

    printf("3 ");
    !stackPushChecker(&intStack, 223677653) ? errors++ : NULL;

    printf("4 ");
    !stackPopChecker(&intStack, 223677653) ? errors++ : NULL;

    printf("5 ");
    !stackPopChecker(&intStack, 0) ? errors++ : NULL;

    printf("6 ");
    !stackPopChecker(&intStack, 5) ? errors++ : NULL;

    printf("7 ");
    !stackPopChecker(&intStack, 0) ? errors++ : NULL;

    printf("8 ");
    !stackPushChecker(&intStack, 56) ? errors++ : NULL;

    if (errors == 0) stackDump(&intStack);
//    stackDump(&intStack);
    stackDestruct(&intStack);
    return errors;
}

bool stackPushChecker(Stack_t *stk, stkElem_t value) {
    size_t size = stk->size;

    stackPush(stk, value);
    if (stk->size != size + 1 || stk->data[stk->size] != value || stk->err != 0) {
        printf("Error:\n"
               "Test failed:\n"
               "      size = %ld\n"
               "await size = %ld\n"
               "pushed value = %d\n"
               " await value = %d\n", stk->size, size + 1, stk->data[stk->size], value);
        stackDump(stk);
        return false;
    }

    printf("success\n");
    return true;
}

bool stackPopChecker(Stack_t *stk, stkElem_t awaitPopedValue) {
    size_t size = stk->size;
    int popedValue = 0;

    stackPop(stk, &popedValue);
    if (size == 0 && stk->size != 0 && popedValue != 0) {
        printf ("Pop form empty stack");
        return false;
    }

    if (size == 0 && stk->size == 0 && popedValue == 0) {
        printf("success\n");
        return true;
    }

    if (stk->size != size - 1 || stk->data[stk->size + 1] != 'Z' || popedValue != awaitPopedValue || stk->err != 0) {
        printf("Error:\n"
               "Test failed:\n"
               "      size = %ld\n"
               "await size = %ld\n"
               "poped value = %d\n"
               " await value = %d\n", stk->size, size - 1, popedValue, awaitPopedValue);
        stackDump(stk);
        return false;
    }

    printf("success\n");
    return true;
}
