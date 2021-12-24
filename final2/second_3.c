#include "../lib/doublyLinkedList/doubly_linked_list.h"
#include "stdio.h"

void readNumbersFromFileToList(FILE* inputStream, List list)
{
    int inputNumber = 0;
    while (fscanf(inputStream, "%d", &inputNumber) != EOF)
        listPushback(list, inputNumber);
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("You need to provide input file path in args!\n");

        return 0;
    }

    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        printf("Invalid input file path!\n");

        return 0;
    }

    List list = listCreate();
    readNumbersFromFileToList(inputFile, list);
    fclose(inputFile);

    if (listIsSymmetric(list))
        printf("List is symmetric!\n");
    else
        printf("List isn't symmetric :(\n");

    listFree(list);
}
