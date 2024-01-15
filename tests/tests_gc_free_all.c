/*
** EPITECH PROJECT, 2024
** Self Project
** File description:
** Garbage Collector
*/

#include <criterion/criterion.h>
#include "../garbage_collector.h"

Test(gc_free_all, valid_case)
{
    gc_t gc = { .total = 0, .addresses = NULL };
    char *str1 = NULL;
    char *str2 = NULL;
    char *str3 = NULL;

    cr_assert_eq(gc.total, 0, "Initial 'gc.total' must be equal to 0.");
    cr_assert_null(gc.addresses, "Initial 'gc.addresses' must be equal to NULL.");
    str1 = gc_alloc(&gc, 11 * sizeof(char));
    str2 = gc_alloc(&gc, 11 * sizeof(char));
    str3 = gc_alloc(&gc, 11 * sizeof(char));
    cr_assert_eq(gc.total, 3, "'gc.total' must be equal to 3 as 3 allocations were made.");
    cr_assert_eq(str3, gc.addresses->address, "Third allocation must be in the front.");
    cr_assert_eq(str2, gc.addresses->next->address, "Second allocation must be in the middle.");
    cr_assert_eq(str1, gc.addresses->next->next->address, "First allocation must be in the back.");
    cr_assert_eq(gc_free_all(&gc), true, "ALl free'd must have successfully be executed.");
}

Test(gc_free_all, null_ptr)
{
    gc_t gc = { .total = 0, .addresses = NULL };

    cr_assert_eq(gc.total, 0, "Initial 'gc.total' must be equal to 0.");
    cr_assert_null(gc.addresses, "Initial 'gc.addresses' must be equal to NULL.");
    cr_assert_eq(gc_free_all(NULL), false, "Can't free a pointer from a NULL-pointer &gc.");
}
