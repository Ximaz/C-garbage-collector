/*
** EPITECH PROJECT, 2024
** Self Project
** File description:
** Garbage Collector
*/

#include <stdlib.h>
#include <stdbool.h>
#include "garbage_collector.h"

static bool gc_pop_front(gc_address_t **addresses, void *address)
{
    gc_address_t *current = NULL;
    gc_address_t *previous = NULL;

    if (NULL == addresses || NULL == *addresses)
        return false;
    current = *addresses;
    while (current->address != address && NULL != current->next) {
        previous = current;
        current = current->next;
    }
    if (current->address != address)
        return false;
    if (NULL == previous)
        *addresses = current->next;
    else
        previous->next = current->next;
    free(current->address);
    free(current);
    return true;
}

bool gc_free(gc_t *gc, void *address)
{
    if (NULL == gc || NULL == address)
        return false;
    if (!gc_pop_front(&gc->addresses, address))
        return false;
    --gc->total;
    return true;
}
