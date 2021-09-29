#include "string.h"
#ifndef SPBU_C_HOMEWORKS_LIST_H
#define SPBU_C_HOMEWORKS_LIST_H

/* A List is a reference type.
 * You should use listFree to free up the string memory. */
typedef struct list* List;

/* Creates empty list. */
List listCreate();

/* Free up list memory. */
void listFree(List l);

/* Adds an element to the end of the list. */
void listPushback(List l, void* data);

/* Returns list size. */
int listSize(List l);

/* Inserts an element to list position. */
bool listInsert(List l, int position, void* data);

/* Prints list to `dst` output in format "<e1><sep><e2><sep>...".
 * You need to provide a function that formats element to string and elements separator. */
void listPrint(List l, String (*elementFormatter)(void*), char* sep, FILE* dst);

/* Converts list to string.
 * You need to provide a function that formats element to char. */
String listToString(List l, char (*elementToChar)(void* element));

/* Copies list and return new list. */
List listCpy(List l, void* (*copyNodeData)(void*));

/* Returns the index of the first occurrence of the subsequence in the list
 * or `-1` if subsequence not found. */
int listSubseqIndex(List l, List subseq, bool (*comparator)(void*, void*));

/* Deletes nodes from list. Starts from `fromPos` ends `toPos` (not include). */
bool listDeleteNodes(List l, int fromPos, int toPos);

/* Inserts list into list position. Need to provide a function that copies node data. */
bool listInsertSubseq(List l, List subseq, int position, void* (*copyNodeData)(void*));

/* Deletes from list subsequence that starts from `lseq` and ends `rseq`. */
bool listDeleteFromToSeqs(List l, List lseq, List rseq, bool (*comparator)(void*, void*));

/* Inserts sequence `seq` after first occurrence of sequence `after`. */
bool listInsertSeqAfterSeq(
    List l,
    List after,
    List seq,
    bool (*comparator)(void*, void*),
    void* (*copyNodeData)(void*));

/* Replaces first occurrence of sequence `from` to sequence `to`. */
bool listReplace(
    List l,
    List from,
    List to,
    bool (*comparator)(void*, void*),
    void* (*copyNodeData)(void*));

#endif // SPBU_C_HOMEWORKS_LIST_H
