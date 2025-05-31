// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

/* Release notes:
    - v0.1.0: Basic functionality.
*/

#ifndef SB_H_INCLUDED
#define SB_H_INCLUDED

#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct {
    size_t size, capacity;
    char *data;
} Sb;
bool sb_append_char(Sb *sb, int ch);
bool sb_append_str(Sb *sb, const char *str);
bool sb_concat(Sb *dest, const Sb *src);
char *sb_cstr(const Sb *sb);
void sb_destroy(Sb *sb);
inline void sb_reset(Sb *sb)
{
    sb->size = 0;
}
inline bool sb_append_null(Sb *sb)
{
    return sb_append_char(sb, '\0');
}

#endif // SB_H_INCLUDED
