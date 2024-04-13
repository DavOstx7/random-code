#include <stdio.h>
#include <stdlib.h>

/* these are MY solutions so it might not be perfect */

typedef struct node {
    int val;
    struct node * next;
} node_t;

void print_list(node_t * head) {
    node_t * current = head;

    while (current != NULL) {
        printf("%d->", current->val);
        current = current->next;
    }
    printf("null\n");
}

void push_end(node_t * head, int val) {
    // it's not this function responsibility to make sure head isn't null - we could do that in that case we make head a signle node//
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = (node_t *) malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}

void push_start(node_t ** head, int val){
    node_t * new_node; //automatically equals to null//
    new_node = (node_t *) malloc(sizeof(node_t));

    new_node->val = val;
    new_node->next = *head;
    *head = new_node;
}

int pop_start(node_t ** head){
    if((*head) == NULL){
        return -1;
    }
    node_t * new_head = (*head)->next;
    int retval = (*head)->val;

    free(*head);

    *head = new_head;
    return retval;
}

int pop_end(node_t **head){
    if((*head) == NULL){
        return -1;
    }

    int retval;

    if((*head)->next == NULL){
        retval = (*head)->val;
        free(*head);
        *head = NULL; //the address of NULL pointers is always 0//.
        return retval;
    }
    node_t * current = *head;

    while (current->next->next != NULL){
        current = current->next;
    }

    retval = current->next->val;
    free(current->next);
    current->next = NULL;
    return retval;
}

int remove_by_index(node_t **head, int index){
    if (head == NULL || *head == NULL){
        return -1;
    }

    if (index == 0){
        return pop_start(head);
    }

    node_t *current = *head;

    for (int i = 0; i < index -1; i++)
    {
        if(current == NULL){
            return -1;
        }
        current = current->next;
    }
    
    if (current == NULL || current->next == NULL){
        return -1;
    }

    node_t *link_to = current->next->next;
    int retval = current->next->val;
    free(current->next);
    current->next = link_to;
    return retval;
}

void remove_by_value_first(node_t **head, int value){
    if (head == NULL || *head == NULL){
        return;
    }

    if ((*head)->val == value){
        pop_start(head);
        return;
    }

    node_t *current = *head;
    while (current->next != NULL){
        if (current->next->val == value){
            node_t *link_to = current->next->next;
            free(current->next);
            current->next = link_to;
            return;
        }
        current = current->next;
    }
}

void remove_by_value_all(node_t **head, int value){
    if (head == NULL || *head == NULL){
        return;
    }

    while ((*head)->val == value){
        pop_start(head);
    }
    
    node_t *current = *head;
    node_t *link_to;
    while (current->next != NULL){
        if (current->next->val == value){
            link_to = current->next->next;
            free(current->next);
            current->next = link_to;
        } else{
            current = current->next;
        }
    }
}

int main(){
    node_t * head = NULL;
    head = (node_t *) malloc(sizeof(node_t));
    if (head == NULL) {
        return 1;
    }

    head->val = 1;
    head->next = NULL;
    head->next = (node_t *) malloc(sizeof(node_t));
    head->next->val = 2;
    head->next->next = NULL;
    printf("[1] default:\n");
    print_list(head);

    printf("[2] pushing 10 at the start:\n");
    push_start(&head, 10);
    print_list(head);

    printf("[3] pushing 7 at the end:\n");
    push_end(head, 7);
    print_list(head);

    printf("[4] popping the first one:\n");
    int ret = pop_start(&head);
    //printf("ret = %d\n", ret);
    print_list(head);

    printf("[5] popping the last one:\n");
    pop_end(&head);
    print_list(head);

    printf("[6] pushing 32 at the end:\n");
    push_end(head, 32);
    print_list(head);

    printf("[7] pushing 9 at the end:\n");
    push_end(head, 9);
    print_list(head);

    printf("[8] removing index 4 (not possible):\n");
    remove_by_index(&head, 4);
    print_list(head);

    printf("[9] removing index 3:\n");
    remove_by_index(&head, 3);
    print_list(head);

    printf("[10] removing value first 11 (not possible):\n");
    remove_by_value_first(&head, 11);
    print_list(head);

    printf("[11] removing value first 32:\n");
    remove_by_value_first(&head, 32);
    print_list(head);
    
    printf("[12] updating linked list:\n");
    push_start(&head, 5);
    push_start(&head, 5);
    push_end(head, 5);
    push_end(head, 5);
    print_list(head);

    printf("[13] removing value all 5's:\n");
    remove_by_value_all(&head, 5);
    print_list(head);
    return 0;
}