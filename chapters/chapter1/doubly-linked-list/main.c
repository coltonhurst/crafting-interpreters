#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------------- TYPES --------------------

/*
    The Node type represents a single node with a pointer to
    one string used in our DoublyLinkedStringList type.
*/
struct Node {
    // The previous Node
    struct Node* previous;

    // The string (on the heap), terminated with \0
    char* str;

    // The next Node
    struct Node* next;
};

/*
    The DoublyLinkedStringList type represents a list of
    strings that are in a doubly linked list.

    These functions are used to create and interact with this
    type:
    - new()
    - insert()
*/
struct DoublyLinkedStringList {
    // The first Node in the list
    struct Node* head;
};

// -------------------- FUNCTIONS --------------------

/*
    Creates and returns an empty DoublyLinkedStringList.
*/
struct DoublyLinkedStringList new() {
    struct DoublyLinkedStringList list;
    list.head = NULL;

    return list;
}

/*
    Inserts `str` as a new string to the end of the
    DoublyLinkedStringList `list`.

    Assumes `str` has the null terminating character `\0`.

    Note: this function operates on a doubly linked list,
    so while it could insert into head's previous node, currently,
    as an exercise, it traverses through the entire node list.
*/
void insert(struct DoublyLinkedStringList* list, char str[]) {
    // Get the length of `str`, add 1 because we want a null terminating character
    // which strlen() doesn't include.
    int strLen = strlen(str) + 1;

    // Allocate memory for the string so it's heap allocated.
    // I use sizeof(char) for visual consistency, even though it'll be 1.
    // Don't forget: cast the crappy void * to a char *
    //
    // Btw, malloc could fail, so we should check if heapStr == NULL, but I don't want to
    // worry about that for this little program.
    char* heapStr = (char*) malloc(sizeof(char) * strLen);

    // Fill heapStr with the char values from `str`,
    // and add the null terminating character.
    for (int i = 0; i < strLen - 1; i++) {
        heapStr[i] = str[i];
    }
    heapStr[strLen] = '\0';

    // Initialize the Node we will insert,
    // and set the `str` value.
    struct Node* n = (struct Node*) malloc(sizeof(struct Node));
    n->previous = NULL;
    n->str = heapStr;
    n->next = NULL;

    // If `head` is NULL, this will be the first node,
    // so set `head` and `n`'s pointers and return.
    if (list->head == NULL) {
        list->head = n;
        return;
    }

    // This is not the first node, so insert the new node behind head
    // If `list->head->previous == NULL`, this is the 2nd node
    if (list->head->previous == NULL) {
        n->next = list->head;
        n->previous = list->head;

        list->head->next = n;
        list->head->previous = n;
    } else {
        n->next = list->head;
        n->previous = list->head->previous;

        list->head->previous->next = n;
        list->head->previous = n;
    }

    // This is not the first node, so find the last node.
    // TRAVERSAL CODE
    /*struct Node* traversalNode = list->head;
    int keepTraversing = 1;

    while (keepTraversing) {
        if (traversalNode->next != NULL) {
            traversalNode++;
        } else {
            keepTraversing = 0;
        }
    }

    // `currentNode` should now point to the last node,
    // so "append" our new node `n`.
    traversalNode->next = n;
    n->previous = traversalNode;
    */
}

/*
    Compares two strings on the heap to see if
    they are equivalent, char by char.

    Returns 1 for true (equal), 0 for false (not equal).
*/
int eq(char* a, char* b) {
    int aLen = strlen(a);
    int bLen = strlen(b);

    if (aLen != bLen) {
        return 0;
    }

    for (int i = 0; i < aLen; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }

    return 1;
}

/*
    Find the given string in the list.
    Returns the number of matches.
*/
int find(struct DoublyLinkedStringList* list, char str[]) {
    // Escape early if list or str are bad
    if (list->head == NULL || strlen(str) == 0) {
        return 0;
    }

    struct Node* currentNode = list->head;
    int occurrences = 0;

    // Search the first node
    if (eq(str, currentNode->str)) {
        occurrences++;
    }

    // Escape case for only 1 node
    if (currentNode->next == NULL) {
        return occurrences;
    }

    // Proceed one step in the list, we know there are at
    // least 2 nodes
    currentNode = currentNode->next;

    // Loop through the remaining nodes
    while (currentNode != list->head) {
        if (eq(str, currentNode->str)) {
            occurrences++;
        }

        currentNode = currentNode->next;
    }

    return occurrences;
}

/*
    Print all nodes in the list provided.
*/
void print(struct DoublyLinkedStringList* list) {
    struct Node* currentNode = list->head;
    int count = 0;

    printf("--- PRINTING LIST ---\n");

    // Check first node
    if (currentNode == NULL) {
        printf("the list is empty...\n");
        printf("---------------------\n");
        return;
    } else {
        printf("Node #%d\n", count);
        printf("  previous: %p\n", currentNode->previous);
        printf("   current: %p\n", currentNode);
        printf("       str: ");
        for (int i = 0; i < strlen(currentNode->str); i++) {
            printf("%c", currentNode->str[i]);
        }
        printf("\n");
        printf("      next: %p\n", currentNode->next);
    }

    currentNode = currentNode->next;
    count++;

    // Print other nodes
    while (currentNode != list->head) {
        printf("Node #%d\n", count);
        printf("  previous: %p\n", currentNode->previous);
        printf("   current: %p\n", currentNode);
        printf("       str: ");
        for (int i = 0; i < strlen(currentNode->str); i++) {
            printf("%c", currentNode->str[i]);
        }
        printf("\n");
        printf("      next: %p\n", currentNode->next);

        currentNode = currentNode->next;
        count++;
    }

    printf("---------------------\n");
}

/*
    The start of our program, the main function.
*/
int main() {
    printf("Hello, world!\n\n");

    struct DoublyLinkedStringList list = new();
    insert(&list, "apple");
    insert(&list, "mango");
    insert(&list, "banana");
    insert(&list, "watermelon");
    insert(&list, "mango");
    insert(&list, "lime");

    print(&list);

    int occurrences = find(&list, "mango");
    printf("mango was found %d time(s)", occurrences);

    return 0;
}
