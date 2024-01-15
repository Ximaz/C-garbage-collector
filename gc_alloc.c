/*
** EPITECH PROJECT, 2024
** Self Project
** File description:
** Garbage Collector
*/

#include <stdlib.h>
#include <stdbool.h>
#include "garbage_collector.h"

static bool gc_push_front(gc_address_t **addresses, void *address)
{
    gc_address_t *node = malloc(sizeof(gc_address_t));

    if (NULL == node)
        return false;
    node->address = address;
    node->next = *addresses;
    *addresses = node;
    return true;
}

void *gc_alloc(gc_t *gc, size_t size)
{
    void *address = NULL;

    if (NULL == gc)
        return NULL;
    address = malloc(size);
    if (NULL == address)
        return NULL;
    if (!gc_push_front(&gc->addresses, address)) {
        free(address);
        return NULL;
    }
    ++gc->total;
    return address;
}
