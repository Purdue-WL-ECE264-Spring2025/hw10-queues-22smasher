#include "linked_list.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
struct list_node *new_node(size_t value) 
{
  struct list_node* node = (struct list_node*)malloc(sizeof(struct list_node));
  node -> value = value;
  node -> next = NULL;
  return node;
}

void insert_at_head(struct linked_list *list, size_t value) 
{
  struct list_node* node = new_node(value);
  (node -> next) = (list -> head);
  (list -> head) = node;
}

void insert_at_tail(struct linked_list *list, size_t value) 
{
  struct list_node* node = new_node(value);
  if (list -> head == NULL)
  {
    list -> head = node;
    return;
  }
  struct list_node* temp = (list -> head);
  while (temp -> next != NULL)
  {
    temp = (temp -> next);
  }
  temp -> next = node;
}

size_t remove_from_head(struct linked_list *list) 
{
   struct list_node* temp = list -> head;
   list -> head = temp -> next;
   size_t output = temp -> value;
   free(temp);
   return(output);
}

size_t remove_from_tail(struct linked_list *list)
{
    struct list_node* temp = list->head;
    size_t output = 0;
    if (temp == NULL)  
    {
        return 0;
    }
    
    if (temp->next == NULL)
    {
        output = temp->value;
        free(temp);
        list->head = NULL;
        return output;
    }
    
    while (temp->next->next != NULL)
    {
        temp = temp->next;
    }
    
    output = temp->next->value; 
    struct list_node* last = temp->next;  
    free(last);  
    temp->next = NULL;  
    return output;
}

void free_list(struct linked_list list)
{
    struct list_node* current = list.head;
    struct list_node* next;
    
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  if (fp == NULL)
  {
    printf("Cannot open file");
    return;
  }
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
void testing() {
FILE *fptr = fopen("testing.txt", "w");
struct linked_list list;
list.head = NULL;
insert_at_tail(&list, 5);
insert_at_tail(&list, 3);
dump_list(fptr, list);
fclose(fptr);
return;
}

// int main()
// {
//   testing();
// }