// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "sb.h"

static bool sb__init_if_needed(Sb *sb)
{
    if (sb->data != NULL) {
        return true;
    }
    const size_t initial_capacity = 16;
    sb->data = calloc(initial_capacity, sizeof(*sb->data));
    if (sb->data == NULL) {
        return false;
    }
    sb->capacity = initial_capacity;
    return true;
}

static bool sb__reserve(Sb *sb, size_t extra_space)
{
    assert(sb->data != NULL);
    assert(sb->capacity > 0);
    size_t new_capacity = sb->capacity;
    while (new_capacity < sb->size + extra_space) {
        new_capacity *= 2;
    }

    if (new_capacity > sb->capacity) {
        char *data = realloc(sb->data, sizeof(*data) * new_capacity);
        if (data == NULL) {
            return false;
        }
        sb->data = data;
        sb->capacity = new_capacity;
    }
    return true;
}

void sb_destroy(Sb *sb)
{
    sb->capacity = 0;
    if (sb->data != NULL) {
        free(sb->data);
    }
}

bool sb_append_char(Sb *sb, int ch)
{
    if (!sb__init_if_needed(sb) || !sb__reserve(sb, 1)) {
        return false;
    }
    sb->data[sb->size] = ch;
    sb->size++;
    return true;
}

bool sb_append_str(Sb *sb, const char *str)
{
    const size_t str_len = strlen(str);
    for (size_t i = 0; i < str_len; i++) {
        if (!sb_append_char(sb, str[i])) {
            return false;
        }
    }
    return true;
}

bool sb_concat(Sb *sb, const Sb *src)
{
    if (!sb__init_if_needed(sb) || !sb__reserve(sb, src->size)) {
        return false;
    }
    memcpy(sb->data + sb->size, src->data, src->size);
    sb->size += src->size;
    return true;
}

char *sb_cstr(const Sb *sb)
{
    char *str = malloc(sizeof(*str) * (sb->size + 1));
    if (str == NULL) {
        return NULL;
    }
    memcpy(str, sb->data, sb->size);
    str[sb->size] = '\0';
    return str;
}
