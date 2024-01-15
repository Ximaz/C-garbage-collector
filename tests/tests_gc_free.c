/*
** EPITECH PROJECT, 2024
** Self Project
** File description:
** Garbage Collector
*/

#include <criterion/criterion.h>
#include "../garbage_collector.h"

Test(gc_free, valid_case)
{
    gc_t gc = { .total = 0, .addresses = NULL };
    size_t i = 0;
    char *my_string = NULL;

    cr_assert_eq(gc.total, 0, "Initial 'gc.total' must be equal to 0.");
    cr_assert_null(gc.addresses, "Initial 'gc.addresses' must be equal to NULL.");
    my_string = gc_alloc(&gc, 11 * sizeof(char));
    if (NULL == my_string) {
        cr_assert_eq(gc.total, 0, "If allocation failed, 'gc.total' must not change.");
        return;
    }
    cr_assert_eq(gc.total, 1, "After one allocation, 'gc.total' must be equal to 1.");
    cr_assert_not_null(gc.addresses, "After one allocatino, 'gc.addresses' must not be equal to NULL.");
    for (i = '0'; i <= '9'; ++i)
        my_string[i - '0'] = i;
    my_string[i - '0'] = 0;
    cr_assert_str_eq(my_string, "0123456789", "The allocated string should be equal to \"0123456789\".");
    cr_assert_eq(gc_free(&gc, my_string), true, "'my_string' pointer was allocated, it must be able to be free'd with no problem.");
    cr_assert_eq(gc.total, 0, "'my_string' has been free'd, so the total counter of gc must be equal to 0.");
    cr_assert_null(gc.addresses, "Nothing is stored into 'gc.addresses', it must be equal to NULL.");
}

Test(gc_free, null_ptr)
{
    gc_t gc = { .total = 0, .addresses = NULL };

    cr_assert_eq(gc.total, 0, "Initial 'gc.total' must be equal to 0.");
    cr_assert_null(gc.addresses, "Initial 'gc.addresses' must be equal to NULL.");
    cr_assert_eq(gc_free(&gc, NULL), false, "Can't free a NULL pointer.");
    cr_assert_eq(gc_free(&gc, (void *) 0x1), false, "Can't free a 0xdead as it was not allocated pointer.");
    cr_assert_eq(gc_free(NULL, (void *) 0x1), false, "Can't free a pointer from a NULL-pointer &gc.");
}

Test(gc_free, bad_pointer)
{
    gc_t gc = { .total = 0, .addresses = NULL };
    void *pointer = NULL;

    cr_assert_eq(gc.total, 0, "Initial 'gc.total' must be equal to 0.");
    cr_assert_null(gc.addresses, "Initial 'gc.addresses' must be equal to NULL.");
    pointer = gc_alloc(&gc, 11 * sizeof(char));
    cr_assert_eq(gc_free(&gc, (void *) 0x1), false, "Can't free a 0xdead as it was not allocated pointer.");
    gc_free(&gc, pointer);
}
