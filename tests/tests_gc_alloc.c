/*
** EPITECH PROJECT, 2024
** Self Project
** File description:
** Garbage Collector
*/

#include <criterion/criterion.h>
#include "../garbage_collector.h"

Test(gc_alloc, valid_case)
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
    gc_free(&gc, my_string);
}

Test(gc_alloc, null_ptr)
{
    gc_t gc = { .total = 0, .addresses = NULL };
    char *my_string = NULL;

    cr_assert_eq(gc.total, 0, "Initial 'gc.total' must be equal to 0.");
    cr_assert_null(gc.addresses, "Initial 'gc.addresses' must be equal to NULL.");
    my_string = gc_alloc(NULL, 11 * sizeof(char));
    cr_assert_null(my_string, "If 'gc_t *gc' is NULL, nothing must be allocated and NULL must be returned.");
}

Test(gc_alloc, addresses_positions)
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
    gc_free(&gc, str1);
    gc_free(&gc, str2);
    gc_free(&gc, str3);
}
