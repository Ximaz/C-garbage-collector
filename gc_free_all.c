/*
** EPITECH PROJECT, 2024
** Self Project
** File description:
** Garbage Collector
*/

#include <stdlib.h>
#include <stdbool.h>
#include "garbage_collector.h"

bool gc_free_all(gc_t *gc)
{
    gc_address_t *current = NULL;
    gc_address_t *next = NULL;

    if (NULL == gc)
        return false;
    current = gc->addresses;
    while (NULL != current) {
        next = current->next;
        if (NULL != current->address)
            free(current->address);
        free(current);
        current = next;
        --gc->total;
    }
    return 0 == gc->total;
}
