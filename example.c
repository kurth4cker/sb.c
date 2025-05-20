// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "sb.h"

int main(void)
{
    {
        Sb sb = { 0 };
        sb_append_str(&sb, "hello");
        sb_append_char(&sb, ' ');
        sb_append_str(&sb, "world");

        char *str = sb_cstr(&sb);
        assert(strcmp(str, "hello world") == 0);
        free(str);
        sb_destroy(&sb);
    }
    {
        Sb hello = { 0 };
        sb_append_str(&hello, "hello");
        Sb world = { 0 };
        sb_append_str(&world, "world");

        Sb sb = { 0 };
        sb_concat(&sb, &hello);
        sb_append_char(&sb, ' ');
        sb_concat(&sb, &world);

        char *str = sb_cstr(&sb);
        assert(strcmp(str, "hello world") == 0);
        free(str);
        sb_destroy(&sb);
        sb_destroy(&hello);
        sb_destroy(&world);
    }
}
