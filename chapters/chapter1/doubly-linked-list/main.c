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

    // Copy str to heapStr
    strcpy(heapStr, str);

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
    if (strcmp(str, currentNode->str) == 0) {
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
        if (strcmp(str, currentNode->str) == 0) {
            occurrences++;
        }

        currentNode = currentNode->next;
    }

    return occurrences;
}

/*
    Find the given string in the list,
    and remove the first occurrence.
*/
void delete(struct DoublyLinkedStringList* list, char str[]) {
    // Escape early if list or str are bad
    if (list->head == NULL || strlen(str) == 0) {
        return;
    }

    struct Node* currentNode = list->head;

    // If there is only one node in the list,
    // check it.
    if (currentNode->next == NULL) {
        // If it matches, remove it
        if (strcmp(str, currentNode->str) == 0) {
            free(currentNode->str);
            free(currentNode);
            list->head = NULL;
            return;
        }
    }

    // Handle special case where there are only two nodes
    // in the list. Check both in that case.
    if (currentNode->next->next == currentNode) {
        // see if the first node matches
        if (strcmp(str, currentNode->str) == 0) {
            // Remove the current and leave the other
            list->head = currentNode->next;
            list->head->next = NULL;
            list->head->previous = NULL;
            free(currentNode->str);
            free(currentNode);
            return;
        }
        // see if the 2nd node matches
        else if (strcmp(str, currentNode->next->str) == 0) {
            // Remove the next and leave the current
            list->head->next = NULL;
            list->head->previous = NULL;
            free(currentNode->next->str);
            free(currentNode->next);
            return;
        }
    }

    // At this point, all we know is there are >= 3 nodes
    // in the list. None have been checked yet.
    // Check the first
    if (strcmp(str, currentNode->str) == 0) {
        list->head = currentNode->next;
        currentNode->previous->next = currentNode->next;
        currentNode->next->previous = currentNode->previous;

        free(currentNode->str);
        free(currentNode);
        return;
    }

    // Increment so we start this search with the 2nd node
    currentNode = currentNode->next;

    // Search
    while (currentNode != list->head) {
        if (strcmp(str, currentNode->str) == 0) {
            currentNode->previous->next = currentNode->next;
            currentNode->next->previous = currentNode->previous;
            free(currentNode->str);
            free(currentNode);
            return;
        }
        currentNode = currentNode->next;
    }
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
        printf("       str: %s\n", currentNode->str);
        printf("      next: %p\n", currentNode->next);
    }

    currentNode = currentNode->next;
    count++;

    // Print other nodes
    while (currentNode != list->head) {
        printf("Node #%d\n", count);
        printf("  previous: %p\n", currentNode->previous);
        printf("   current: %p\n", currentNode);
        printf("       str: %s\n", currentNode->str);
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
    printf("mango was found %d time(s)\n", occurrences);

    printf("... eating one mango\n");
    delete(&list, "mango");

    int occurrencesAgain = find(&list, "mango");
    printf("mango was found %d time(s)", occurrencesAgain);

    return 0;
}
