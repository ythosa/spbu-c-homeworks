#include "string.h"
#ifndef SPBU_C_HOMEWORKS_LIST_H
#define SPBU_C_HOMEWORKS_LIST_H

/* A List is a reference type.
 * You should use listFree to free up the List memory. */
typedef struct List* List;

/* Creates empty List. */
List listCreate(void (*freeNodeData)(void*));

/* Free up List memory. */
void listFree(List list);

/* Adds an Element to the end of the List. */
void listPushback(List list, void* data);

/* Returns List size. */
int listSize(List list);

/* Prints List to `destination` output in format "<e1><separator><e2><separator>...".
 * You need to provide a function that formats Element to String and elements separator. */
void listPrint(List list, String (*formatElementData)(void*), String separator, FILE* destination);

/* Converts List to String.
 * You need to provide a function that formats Element to char. */
String listToString(List list, char (*convertElementToChar)(void* element));

/* Copies List and return new List. */
List listCopy(List list, void* (*copyNodeData)(void*));

/* Returns the index of the first occurrence of the subsequence in the List
 * or `-1` if subsequence not found. */
int listSubsequenceIndex(List list, List subsequence, bool (*compareNodeData)(void*, void*));

/* Deletes nodes from List. Starts from `fromIndex` ends `toIndex` (not include). */
bool listDeleteNodes(List list, int fromIndex, int toIndex);

/* Inserts List into List position. Need to provide a function that copies Node data. */
bool listInsertSequence(List list, List sequence, int position, void* (*copyNodeData)(void*));

/* Deletes from List subsequence that starts from `fromSequence` and ends `bySequence`. */
bool listDeleteFromSequenceBySequence(
    List list,
    List fromSequence,
    List bySequence,
    bool (*compareNodeData)(void*, void*));

/* Inserts sequence `sequence` sequenceAfter first occurrence of sequence `sequenceAfter`. */
bool listInsertSequenceAfterSequence(
    List list,
    List sequenceAfter,
    List sequence,
    bool (*compareNodeData)(void*, void*),
    void* (*copyNodeData)(void*));

/* Replaces first occurrence of sequence `sequenceToBeReplaced` to sequence `sequenceReplaceWith`. */
bool listReplaceSequence(
    List list,
    List sequenceToBeReplaced,
    List sequenceReplaceWith,
    bool (*compareNodeData)(void*, void*),
    void* (*copyNodeData)(void*));

/* A ListIterator is a reference type.
 * You should use `listIteratorFree` to free up the `ListIterator` memory. */
typedef struct ListIterator* ListIterator;

/* Creates list iterator for list. */
ListIterator listIteratorCreate(List list);

/* Free up list iterator memory. */
void listIteratorFree(ListIterator listIterator);

/* Returns next element of list. */
void* listIteratorGetNext(ListIterator listIterator);

/* Returns true if list has next element, otherwise - false. */
bool listIteratorHasMore(ListIterator listIterator);

#endif // SPBU_C_HOMEWORKS_LIST_H
