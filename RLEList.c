#include "RLEList.h"
#include <stdlib.h>
#include <stdio.h>

//------------------------Helper Functions------------------------------

RLEListResult addNewCharacter(RLEList current, char value);

//----------------------------------------------------------------------

struct RLEList_t{
    char letter;
    int appearances;
    struct RLEList_t* nextLetter;
};


RLEList RLEListCreate() {
    RLEList newList = (struct RLEList_t *)malloc(sizeof(*newList));
    if (!newList) {
        return NULL;
    }

    newList->letter = '\0';
    newList->appearances = 0;
    newList->nextLetter = NULL;

    return newList;
}


void RLEListDestroy(RLEList list) {
    //Free dynamically allocated memory
    while (list) {
        RLEList toDelete = list;
        list = list->nextLetter;
        free(toDelete);
    }
}


RLEListResult RLEListAppend(RLEList list, char value) {
    //If null arguments received return output accordingly
    if ((!list) || (!value)) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    //Initiate new pointer to linked list
    RLEList current = list;

    //Jump to the last character in linked list
    while (current->nextLetter) {
        current = current->nextLetter;
    }

    //If the last character is the same as the given value, count the new appearance
    if (current->letter == value) {
        current->appearances += 1;
    }
    //Else, create new node for linked list
    else {
        return addNewCharacter(current, value);
    }

    //The addition was completed successfully
    return RLE_LIST_SUCCESS;
}


RLEListResult addNewCharacter(RLEList current, char value)
{
    //If this is the first character being added
    if ((current->letter == '\0') && (current->appearances == 0)) {
        current->letter = value;
        current->appearances = 1;
    }
    //Otherwise, create node for new letter
    else {
        RLEList newLetter = RLEListCreate();
        if (!newLetter) {
            return RLE_LIST_OUT_OF_MEMORY;
        }
        newLetter->letter = value;
        newLetter->appearances = 1;
        current->nextLetter = newLetter;
    }

    //The addition was completed successfully
    return RLE_LIST_SUCCESS;
}


RLEListResult RLEListRemove(RLEList list, int index) {
    //If null arguments received return output accordingly
    if (!list) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (index <= 0) {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    //Initiate new pointers to linked list
    RLEList current = list;
    RLEList previous = NULL;

    //Go to letter with requested index
    while ((current->appearances <= index) && (current->nextLetter) && (index > 0)) {
        index -= current->appearances;
        previous = current;
        current = current->nextLetter;
    }

    //If the requested index was found, remove node
    if ((index <= 0) || (current->appearances > index)) {
        if (current->appearances == 1) {
            if (current != list) {
                previous->nextLetter = current->nextLetter;
            }
            free(current);
        }
        else {
            current->appearances -= 1;
        }
    }
    //Otherwise, return result accordingly
    else {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    //The removal was completed successfully
    return RLE_LIST_SUCCESS;
}


char RLEListGet(RLEList list, int index, RLEListResult *result) {
    //If null arguments received return output accordingly
    if ((!list) && (result)) {
        *result = RLE_LIST_NULL_ARGUMENT;
    }
    else if ((index <= 0) && (result)) {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    else if ((list) && (index > 0)) {
        //Initiate new pointer to linked list
        RLEList current = list;

        //Go to letter with requested index
        while ((current->appearances <= index) && (current->nextLetter) && (index > 0)) {
            index -= current->appearances;
            current = current->nextLetter;
        }

        //If the requested index was found, return the requested character
        if ((index <= 0) || (current->appearances > index)) {
            if (result) {
                *result = RLE_LIST_SUCCESS;
            }
            return current->letter;
        }
        //Otherwise, return result accordingly
        if (result) {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
    }
    return 0;
}


int RLEListSize(RLEList list) {
    //If null arguments received return output accordingly
    if (!list) {
        return -1;
    }

    //Initiate linked list size and pointer
    int size = 0;
    RLEList current = list;

    //Count number of letters in linked list
    while (current) {
        size += current->appearances;
        current = current->nextLetter;
    }

    //Return size of linked list
    return size;
}


RLEListResult RLEListMap(RLEList list, MapFunction map_function) {
    //If null arguments received return output accordingly
    if ((!list) || (!map_function)) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    //Initiate new pointer to linked list
    RLEList current = list;

    //Change characters in linked list according to the function received
    while (current) {
        current->letter = map_function(current->letter);
        current = current->nextLetter;
    }

    //The mapping was completed successfully
    return RLE_LIST_SUCCESS;
}




//------------------------TO DELETE------------------------------

char* RLEListExportToString(RLEList list, RLEListResult* result) {
    //Calculate list size
    int size = RLEListSize(list);

    //If null arguments received return output accordingly
    if ((!list) || (size < 0)) {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }

    //Initiate new pointer to linked list, string variable for output and index for string
    RLEList current = list;
    char* outputString = (char*)malloc(sizeof(char)*size);
    int index = 0;

    //Create output string
    while (current) {
        for (int i = 0; i < current->appearances; i++) {
            outputString[index] = current->letter;
            index++;
        }
        current = current->nextLetter;
    }

    //The printing was completed successfully
    *result = RLE_LIST_SUCCESS;
    return outputString;
}