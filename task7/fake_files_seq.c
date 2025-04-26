#include "stdio.h"
#include "stdlib.h"

struct node 
{
    char *filename;
    struct node *next;
};

// Fill linked list with fake incremental file names
void fill_linked_list(struct node *head, int n)
{
    struct node *current = head;
    for (int i = 0; i < n; i++)
    {
        current->filename = malloc(20);
        sprintf(current->filename, "file%d.txt", i);
        if (i < n - 1) 
        { // Only allocate a new node if it's not the last one
            current->next = malloc(sizeof(struct node));
            current = current->next;
        } 
        else 
            current->next = NULL; // Set the last node's next pointer to NULL
    }
    current->next = NULL;
}

// Free linked list
void free_linked_list(struct node *head)
{
    struct node *current = head;
    struct node *next_node;
    while (current != NULL)
    {
        next_node = current->next;
        free(current->filename);
        free(current);
        current = next_node;
    }
}

void print_linked_list(struct node *head)
{
    struct node *current = head;
    while (current != NULL)
    {
        printf("%s\n", current->filename);
        current = current->next;
    }
}

int main()
{
    int n = 100; // Number of files
    printf("n = %d\n", n);
    // Allocate memory for the linked list
    struct node *head = malloc(sizeof(struct node));
    fill_linked_list(head, n);
    // Print the file names
    print_linked_list(head);
    // Free the linked list
    free_linked_list(head);
    
    return 0;
}