#include "stdio.h"
#include "stdlib.h"
#include "omp.h"

struct node 
{
    int num;
    struct node *next;
};

// Append a new node to the linked list
void append_linked_list(struct node *head, int num)
{
    struct node *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = malloc(sizeof(struct node));
    current->next->num = num;
    current->next->next = NULL;
}

// Free linked list
void free_linked_list(struct node *head)
{
    struct node *current = head;
    struct node *next_node;
    while (current != NULL)
    {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

// void print_linked_list(struct node *head)
// {
//     struct node *current = head;

//     #pragma omp parallel
//     {
//         #pragma omp single
//         {
//             // Print the thread creating the tasks
//             printf("Criando tarefas na thread %d\n", omp_get_thread_num());
//             while (current != NULL)
//             {
//                 struct node *node_copy = current;
//                 #pragma omp task firstprivate(node_copy)
//                 {
//                     printf("Processando %s na thread %d\n", node_copy->filename, omp_get_thread_num());
//                 }
//                 current = current->next;
//             }
//             // Wait for all tasks to finish
//             #pragma omp taskwait
//         }
//     }
// }

int main()
{
    int n = 100; // Number of files
    int num_threads = 2; // Number of threads
    printf("n = %d\n", n);
    // Allocate memory for the 2 linked lists
    struct node *head0 = malloc(sizeof(struct node));
    struct node *head1 = malloc(sizeof(struct node));
    // Set the number of threads

    
    // Initialize OpenMP locks for the two linked lists
    omp_lock_t lock0, lock1;
    omp_init_lock(&lock0);
    omp_init_lock(&lock1);

    #pragma omp parallel
    {
        unsigned int seed = omp_get_thread_num(); // Use thread-specific seed for rand_r
        #pragma omp for
        for (int i = 0; i < n; i++)
        {
            // Decide which linked list to insert into
            struct node *head = (rand_r(&seed) % 2 == 0) ? head0 : head1;

            // Lock the appropriate linked list before appending
            if (head == head0) {
                omp_set_lock(&lock0);
                append_linked_list(head, i);
                omp_unset_lock(&lock0);
            } else {
                omp_set_lock(&lock1);
                append_linked_list(head, i);
                omp_unset_lock(&lock1);
            }
        }
    }

    // Destroy the locks after use
    omp_destroy_lock(&lock0);
    omp_destroy_lock(&lock1);

    // Print the linked lists
    struct node *current = head0;
    printf("Linked list 0:\n");
    while (current != NULL)
    {
        printf("%d ", current->num);
        current = current->next;
    }
    printf("\n");
    current = head1;
    printf("Linked list 1:\n");
    while (current != NULL)
    {
        printf("%d ", current->num);
        current = current->next;
    }
    printf("\n");
    
    // Free linked lists
    free_linked_list(head0);
    free_linked_list(head1);

    return 0;
}