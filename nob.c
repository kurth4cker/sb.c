// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdlib.h>

#define NOB_EXPERIMENTAL_DELETE_OLD
#define NOB_IMPLEMENTATION
#include "nob.h"

int main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);

    Nob_Cmd cmd = { 0 };
    {
        const char *cc = getenv("CC");
        if (cc == NULL) {
            cc = "cc";
        }
        nob_cmd_append(&cmd, cc);
    }
    nob_cmd_append(&cmd, "-std=c99", "-pedantic");
    nob_cmd_append(&cmd, "-Wall", "-Wextra", "-Werror");
    nob_cc_output(&cmd, "example");
    nob_cc_inputs(&cmd, "sb.c", "example.c");
    if (!nob_cmd_run_sync_and_reset(&cmd)) {
        exit(EXIT_FAILURE);
    }
}
