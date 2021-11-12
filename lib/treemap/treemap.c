#include "../../lib/commonUtils/numericOperations.h"
#include "../../lib/list/list.h"
#include <stdio.h>
#include <stdlib.h>

#include "../stack/stack.h"
#include "treemap.h"

struct Node {
    Value key;
    Value value;
    Node* left;
    Node* right;
    int height;
};

Node* nodeCreate(Value key, Value value)
{
    Node* node = malloc(sizeof(Node));

    node->key = key;
    node->value = value;
    node->left = node->right = NULL;
    node->height = 1;

    return node;
}

void nodeFree(Node* node)
{
    free(node);
}

Value nodeGetKey(Node* node)
{
    return node->key;
}

Value nodeGetValue(Node* node)
{
    return node->value;
}

void nodeRecursiveFree(Node* node)
{
    if (!node)
        return;

    if (node->left)
        nodeRecursiveFree(node->left);

    if (node->right)
        nodeRecursiveFree(node->right);

    nodeFree(node);
}

static int nodeHeight(Node* node)
{
    return node ? node->height : 0;
}

/* T1, T2, T3 and T4 are subtrees.
    y                                 x
   / \       Right Rotation          / \
  x   T3    - - - - - - - >        T1   y
 / \        < - - - - - - -            / \
T1  T2       Left Rotation            T2  T3
*/
Node* nodeRightRotate(Node* y)
{
    Node* x = y->left;
    Node* t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    x->height = max(nodeHeight(x->left), nodeHeight(x->right)) + 1;

    return x;
}

Node* nodeLeftRotate(Node* x)
{
    Node* y = x->right;
    Node* t2 = y->left;

    y->left = x;
    x->right = t2;

    x->height = max(nodeHeight(x->left), nodeHeight(x->right)) + 1;
    y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;

    return y;
}

int nodeGetBalanceFactor(Node* node)
{
    return node ? nodeHeight(node->left) - nodeHeight(node->right) : 0;
}

Node* nodeBalance(Node* node)
{
    int balanceFactor = nodeGetBalanceFactor(node);

    // LL Rotate
    if (balanceFactor > 1 && nodeGetBalanceFactor(node->left) >= 0)
        return nodeRightRotate(node);

    // RR Rotate
    if (balanceFactor < -1 && nodeGetBalanceFactor(node->right) <= 0)
        return nodeLeftRotate(node);

    // LR Rotate
    if (balanceFactor > 1 && nodeGetBalanceFactor(node->left) < 0) {
        node->left = nodeLeftRotate(node->left);
        return nodeRightRotate(node);
    }

    // RL Rotate
    if (balanceFactor < -1 && nodeGetBalanceFactor(node->right) > 0) {
        node->right = nodeRightRotate(node->right);
        return nodeLeftRotate(node);
    }

    return node;
}

void nodeInOrderPrint(Node* node, FILE* destination)
{
    if (!node)
        return;

    nodeInOrderPrint(node->left, destination);

    fprintf(destination, "(");
    print(node->key, destination);
    fprintf(destination, ",");
    print(node->value, destination);
    fprintf(destination, ") ");

    nodeInOrderPrint(node->right, destination);
}

Node* nodePut(Node* node, Value key, Value value, Comparator comparator)
{
    if (!node)
        return nodeCreate(key, value);

    switch (comparator(key, node->key)) {
    case -1:
        node->left = nodePut(node->left, key, value, comparator);
        break;
    case 1:
        node->right = nodePut(node->right, key, value, comparator);
        break;
    default:
        node->value = value;
        return node;
    }

    node->height = 1 + max(nodeHeight(node->left), nodeHeight(node->right));

    return nodeBalance(node);
}

Node* nodeFindMin(Node* node)
{
    Node* currentNode = node;

    while (currentNode && currentNode->left)
        currentNode = currentNode->left;

    return currentNode;
}

Node* nodeFindMax(Node* node)
{
    Node* currentNode = node;

    while (currentNode && currentNode->right)
        currentNode = currentNode->right;

    return currentNode;
}

Node* nodeDelete(Node* node, Value key, Comparator comparator)
{
    if (!node)
        return node;

    switch (comparator(key, node->key)) {
    case -1:
        node->left = nodeDelete(node->left, key, comparator);
        break;
    case 1:
        node->right = nodeDelete(node->right, key, comparator);
        break;
    default:
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;

            if (!temp) {
                temp = node;
                node = NULL;
            } else
                *node = *temp;

            nodeFree(temp);
        } else {
            Node* temp = nodeFindMin(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = nodeDelete(node->right, temp->key, comparator);
        }
    }

    if (!node)
        return node;

    node->height = max(nodeHeight(node->left), nodeHeight(node->right)) + 1;

    return nodeBalance(node);
}

struct TreeMap {
    Node* head;
    Comparator comparator;
};

TreeMap* treeMapCreate(Comparator comparator)
{
    TreeMap* treeMap = malloc(sizeof(TreeMap));

    treeMap->head = NULL;
    treeMap->comparator = comparator;

    return treeMap;
}

void treeMapFree(TreeMap* treeMap)
{
    nodeRecursiveFree(treeMap->head);
    free(treeMap);
}

void treeMapPut(TreeMap* treeMap, Value key, Value value)
{
    treeMap->head = nodePut(treeMap->head, key, value, treeMap->comparator);
}

void treeMapPrint(TreeMap* treeMap, FILE* destination)
{
    nodeInOrderPrint(treeMap->head, destination);
}

void treeMapDelete(TreeMap* treeMap, Value key)
{
    treeMap->head = nodeDelete(treeMap->head, key, treeMap->comparator);
}

Value treeMapGet(TreeMap* treeMap, Value key)
{
    Node* currentNode = treeMap->head;

    while (currentNode) {
        if (treeMap->comparator(currentNode->key, key) == 0)
            break;
        currentNode = treeMap->comparator(currentNode->key, key) == -1 ? currentNode->right : currentNode->left;
    }

    if (currentNode)
        return currentNode->value;

    return wrapNone();
}

bool treeMapHasKey(TreeMap* treeMap, Value key)
{
    Value value = treeMapGet(treeMap, key);

    return isNone(value) ? false : true;
}

Value treeMapGetMaximum(TreeMap* treeMap)
{
    Node* maxNode = nodeFindMax(treeMap->head);

    return maxNode ? maxNode->key : wrapNone();
}

Value treeMapGetMinimum(TreeMap* treeMap)
{
    Node* minNode = nodeFindMin(treeMap->head);

    return minNode ? minNode->key : wrapNone();
}

Value treeMapGetUpperBound(TreeMap* treeMap, Value key)
{
    Node* currentNode = treeMap->head;
    Node* previousFound = NULL;

    while (currentNode) {
        switch (treeMap->comparator(currentNode->key, key)) {
        case 1:
            previousFound = currentNode;
            currentNode = currentNode->left;
            break;
        default:
            currentNode = currentNode->right;
            break;
        }
    }

    return previousFound ? previousFound->key : wrapNone();
}

Value treeMapGetLowerBound(TreeMap* treeMap, Value key)
{
    Node* currentNode = treeMap->head;
    Node* previousFound = NULL;

    while (currentNode) {
        switch (treeMap->comparator(currentNode->key, key)) {
        case -1:
            currentNode = currentNode->right;
            break;
        default:
            previousFound = currentNode;
            currentNode = currentNode->left;
            break;
        }
    }

    return previousFound ? previousFound->key : wrapNone();
}

struct TreeMapIterator {
    Stack* stack;
};

TreeMapIterator* treeMapIteratorCreate(TreeMap* treeMap)
{
    TreeMapIterator* treeMapIterator = malloc(sizeof(TreeMapIterator));

    treeMapIterator->stack = stackCreate();

    Node* currentNode = treeMap->head;
    while (currentNode) {
        stackPush(treeMapIterator->stack, wrapPointer(currentNode));
        currentNode = currentNode->left;
    }

    return treeMapIterator;
}

void treeMapIteratorFree(TreeMapIterator* treeMapIterator)
{
    stackShallowFree(treeMapIterator->stack);
    free(treeMapIterator);
}

bool treeMapIteratorHasElement(TreeMapIterator* treeMapIterator)
{
    return !stackIsEmpty(treeMapIterator->stack);
}

Node* treeMapIteratorGetNext(TreeMapIterator* treeMapIterator)
{
    Node* result = getPointer(stackPop(treeMapIterator->stack));
    Node* currentNode = result;

    if (result->right) {
        currentNode = currentNode->right;
        while (currentNode) {
            stackPush(treeMapIterator->stack, wrapPointer(currentNode));
            currentNode = currentNode->left;
        }
    }

    return result;
}

List treeMapToSortedList(TreeMap* treeMap)
{
    List list = listCreate(free);

    TreeMapIterator* treeMapIterator = treeMapIteratorCreate(treeMap);

    while (treeMapIteratorHasElement(treeMapIterator)) {

    }

    treeMapIteratorFree(treeMapIterator);
}

TreeMap*
treeMapJoin(TreeMap* map, TreeMap* another)
{
}
