#include "list.h"
#include <stdlib.h>
#include <assert.h>

void test_list_new(void)
{
    List *list = list_new(sizeof(int), NULL);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(list->length == 0);
    assert(list->data_size == sizeof(int));
    assert(list->free_data == NULL);
    list_free(list);
}

void test_list_push_back(void)
{
    List *list = list_new(sizeof(int), NULL);
    int data = 42;
    list_push_back(list, &data);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    assert(list->length == 1);
    assert(*(int *)list->head->data == 42);
    assert(*(int *)list->tail->data == 42);
    list_free(list);
}

void test_list_push_front(void)
{
    List *list = list_new(sizeof(int), NULL);
    int data = 42;
    list_push_front(list, &data);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    assert(list->length == 1);
    assert(*(int *)list->head->data == 42);
    assert(*(int *)list->tail->data == 42);
    list_free(list);
}

void test_list_pop_back(void)
{
    List *list = list_new(sizeof(int), NULL);
    int data = 42;
    list_push_back(list, &data);
    int dest;
    list_pop_back(list, &dest);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(list->length == 0);
    assert(dest == 42);
    list_free(list);
}

void test_list_pop_front(void)
{
    List *list = list_new(sizeof(int), NULL);
    int data = 42;
    list_push_back(list, &data);
    int dest;
    list_pop_front(list, &dest);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(list->length == 0);
    assert(dest == 42);
    list_free(list);
}

void test_list_insert(void)
{
    List *list = list_new(sizeof(int), NULL);
    int data = 42;
    list_push_back(list, &data);
    int data2 = 43;
    list_insert(list, 0, &data2);
    assert(list->length == 2);
    assert(*(int *)list->head->data == 43);
    assert(*(int *)list->tail->data == 42);
    list_free(list);
}

void test_list_remove(void)
{
    List *list = list_new(sizeof(int), NULL);
    int data = 42;
    list_push_back(list, &data);
    int data2 = 43;
    list_push_back(list, &data2);
    list_remove(list, 0);
    assert(list->length == 1);
    assert(*(int *)list->head->data == 43);
    assert(*(int *)list->tail->data == 43);
    list_free(list);
}

void test_list_get(void)
{
    List *list = list_new(sizeof(int), NULL);
    int data = 42;
    list_push_back(list, &data);
    int dest;
    list_get(list, 0, &dest);
    assert(dest == 42);
    list_free(list);
}

void test_list_set(void)
{
    List *list = list_new(sizeof(int), NULL);
    int data = 42;
    list_push_back(list, &data);
    int data2 = 43;
    list_set(list, 0, &data2);
    assert(*(int *)list->head->data == 43);
    list_free(list);
}




int main(void)
{
    test_list_new();
    test_list_push_back();
    test_list_push_front();
    test_list_pop_back();
    test_list_pop_front();
    test_list_insert();
    test_list_remove();
    test_list_get();
    test_list_set();
    return 0;
}