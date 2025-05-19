// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdlib.h>

#define NOB_EXPERIMENTAL_DELETE_OLD
#define NOB_IMPLEMENTATION
#include "vendor/nob.h"

enum os {
    OS_UNIX,
    OS_WINDOWS,
};
#if defined(__unix__) || defined(__APPLE__)
enum os OS = OS_UNIX;
#elif defined(_WIN32)
enum os OS = OS_WINDOWS;
#endif

static void
setup_cc_and_cflags(Nob_Cmd *cmd)
{
    const char *cc = getenv("CC");
    if (cc == NULL) {
        if (OS == OS_UNIX) {
            cc = "cc";
        } else {
            cc = "cl";
        }
    }
    nob_cmd_append(cmd, cc);

    if (OS == OS_UNIX) {
        nob_cmd_append(cmd, "-std=c99", "-pedantic");
        nob_cmd_append(cmd, "-Wall", "-Wextra", "-Werror");
    } else {
        nob_cmd_append(cmd, "/nologo", "/std:c17");
        nob_cmd_append(cmd, "/W4");
    }
}

int main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);

    Nob_Cmd cmd = { 0 };
    setup_cc_and_cflags(&cmd);
    nob_cc_output(&cmd, "example");
    nob_cc_inputs(&cmd, "sb.c", "example.c");
    if (!nob_cmd_run_sync_and_reset(&cmd)) {
        exit(EXIT_FAILURE);
    }
}
