#ifndef _LIST_H
#define _LIST_H

#include <stdint.h>

typedef struct ListNode {
    struct ListNode *prev;
    struct ListNode *next;
    void *data;
} ListNode;

typedef struct List {
    ListNode *head;
    ListNode *tail;
    size_t length;
    size_t data_size;
    void (*free_data)(void *data);
} List;

/**
 * @brief Suitable for primative data types or structures that do not require a custom free function.
*/
#define LIST(type) list_new(sizeof(type),NULL)   

/**
 * @brief Free data allocated by malloc
 * 
 * @details Single de
 * 
 * @param data 
 */
void list_generic_free(void *data);

/**
 * @brief Initialize a new List.
 * 
 * @param data_size sizeof(data_type)
 * @param free_data NULL if no custom free function is required.
 * @return List* 
 */
List* list_new(size_t data_size, void (*free_data)(void *data));

/**
 * @brief Free the List and all its elements.
 * 
 * @param list 
 */
void list_free(List *list);

void list_push_back(List *list, void *data);

void list_push_front(List *list, void *data);

void list_pop_back(List *list, void* dest);

void list_pop_front(List *list, void* dest);

void list_insert(List *list, size_t index, void *data);

void list_remove(List *list, size_t index);

void list_get(List *list, size_t index, void* dest);

void list_set(List *list, size_t index, void *data);

#endif /* _LIST_H */