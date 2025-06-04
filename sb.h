// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

/* Release notes:
    - v0.2.0:
        Added functions:
            - sb_append_null()
            - sb_reset()

    - v0.1.0: Basic functionality.
*/

// TODO: add header documentation

#ifndef SB_H_INCLUDED
#define SB_H_INCLUDED

#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>

// Main structure. Zero initialization is valid. So you can directly use it
// with all functions.
typedef struct {
    size_t size, capacity;
    char *data;
} Sb;
// Append given char.
bool sb_append_char(Sb *sb, int ch);

// Append given string. Note that there is no trailing null is appended to Sb.
bool sb_append_str(Sb *sb, const char *str);

// Concat two Sb's.
bool sb_concat(Sb *dest, const Sb *src);

// Return a dynamically allocated C string representation of Sb.
char *sb_cstr(const Sb *sb);

// Free internal data structures. (sb.data)
void sb_destroy(Sb *sb);

// Reset size to zero.
inline void sb_reset(Sb *sb)
{
    sb->size = 0;
}

// Append null to the sb. You can now use sb.data as a C string.
inline bool sb_append_null(Sb *sb)
{
    return sb_append_char(sb, '\0');
}

#endif // SB_H_INCLUDED
