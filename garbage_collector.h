/*
** EPITECH PROJECT, 2024
** Self Project
** File description:
** Garbage Collector
*/

#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct s_gc_address {
    void *address;
    struct s_gc_address *next;
} gc_address_t;

typedef struct s_gc {
    size_t total;
    gc_address_t *addresses;
} gc_t;

void *gc_alloc(gc_t *gc, size_t size);

bool gc_free(gc_t *gc, void *address);

bool gc_free_all(gc_t *gc);
