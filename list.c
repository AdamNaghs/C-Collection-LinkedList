#include "list.h"
#include <stdlib.h>
#include <string.h>

List *list_new(size_t data_size, void (*free_data)(void *data))
{
    List *list = malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    list->data_size = data_size;
    list->free_data = free_data;
    return list;
}

void list_free(List *list)
{
    ListNode *node = list->head;
    while (node)
    {
        ListNode *next = node->next;
        if (list->free_data)
        {
            list->free_data(node->data);
        }
        free(node->data);
        free(node);
        node = next;
    }
    free(list);
}

void list_push_back(List *list, void *data)
{
    ListNode *node = malloc(sizeof(ListNode));
    node->data = malloc(list->data_size);
    memcpy(node->data, data, list->data_size);
    node->prev = list->tail;
    node->next = NULL;
    if (list->tail)
    {
        list->tail->next = node;
    }
    list->tail = node;
    if (!list->head)
    {
        list->head = node;
    }
    list->length++;
}

void list_push_front(List *list, void *data)
{
    ListNode *node = malloc(sizeof(ListNode));
    node->data = malloc(list->data_size);
    memcpy(node->data, data, list->data_size);
    node->prev = NULL;
    node->next = list->head;
    if (list->head)
    {
        list->head->prev = node;
    }
    list->head = node;
    if (!list->tail)
    {
        list->tail = node;
    }
    list->length++;
}

void list_pop_back(List *list, void *dest)
{
    if (!list->tail)
    {
        return;
    }
    ListNode *node = list->tail;
    memcpy(dest, node->data, list->data_size);
    list->tail = node->prev;
    if (list->tail)
    {
        list->tail->next = NULL;
    }
    else
    {
        list->head = NULL;
    }
    free(node->data);
    free(node);
    list->length--;
}

void list_pop_front(List *list, void *dest)
{
    if (!list->head)
    {
        return;
    }
    ListNode *node = list->head;
    memcpy(dest, node->data, list->data_size);
    list->head = node->next;
    if (list->head)
    {
        list->head->prev = NULL;
    }
    else
    {
        list->tail = NULL;
    }
    free(node->data);
    free(node);
    list->length--;
}


void list_insert(List *list, size_t index, void *data)
{
    if (index == 0)
    {
        list_push_front(list, data);
        return;
    }
    if (index == list->length)
    {
        list_push_back(list, data);
        return;
    }
    if (index >= list->length)
    {
        return;
    }
    ListNode *node = list->head;
    for (size_t i = 0; i < index; i++)
    {
        node = node->next;
    }
    ListNode *new_node = malloc(sizeof(ListNode));
    new_node->data = malloc(list->data_size);
    memcpy(new_node->data, data, list->data_size);
    new_node->prev = node->prev;
    new_node->next = node;
    node->prev->next = new_node;
    node->prev = new_node;
    list->length++;
}

void list_remove(List *list, size_t index)
{
    if (index == 0)
    {
        list_pop_front(list, NULL);
        return;
    }
    if (index == list->length - 1)
    {
        list_pop_back(list, NULL);
        return;
    }
    if (index >= list->length)
    {
        return;
    }
    ListNode *node = list->head;
    for (size_t i = 0; i < index; i++)
    {
        node = node->next;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    if (list->free_data)
    {
        list->free_data(node->data);
    }
    free(node->data);
    free(node);
    list->length--;
}

void list_get(List *list, size_t index, void *dest)
{
    if (index >= list->length)
    {
        return;
    }
    ListNode *node = list->head;
    for (size_t i = 0; i < index; i++)
    {
        node = node->next;
    }
    memcpy(dest, node->data, list->data_size);
}

void list_set(List *list, size_t index, void *data)
{
    if (index >= list->length)
    {
        return;
    }
    ListNode *node = list->head;
    for (size_t i = 0; i < index; i++)
    {
        node = node->next;
    }
    memcpy(node->data, data, list->data_size);
}