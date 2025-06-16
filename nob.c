// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdlib.h>

#define NOB_EXPERIMENTAL_DELETE_OLD
#define NOB_IMPLEMENTATION
#include "vendor/nob.h"

static void
setup_cc_and_cflags(Nob_Cmd *cmd)
{
    const char *cc = getenv("CC");
    if (cc == NULL) {
        #if defined(__unix__) || defined(__APPLE__)
            cc = "cc";
        #elif defined(_WIN32)
            cc = "cl";
        #endif
    }
    nob_cmd_append(cmd, cc);

    #if defined(__unix__) || defined(__APPLE__)
        nob_cmd_append(cmd, "-std=c99", "-pedantic");
        nob_cmd_append(cmd, "-g");
        nob_cmd_append(cmd, "-Wall", "-Wextra", "-Werror");
    #elif defined(_WIN32)
        nob_cmd_append(cmd, "/nologo", "/std:c17");
        nob_cmd_append(cmd, "/W4");
    #endif
}

int main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);

    bool test = false;
    // bool help = false;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "test") == 0) {
            test = true;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "help") == 0) {
            // help = true;
        }
    }

    Nob_Cmd cmd = { 0 };

    setup_cc_and_cflags(&cmd);
    nob_cc_output(&cmd, "example");
    nob_cc_inputs(&cmd, "sb.c", "example.c");
    if (!nob_cmd_run_sync_and_reset(&cmd)) {
        exit(EXIT_FAILURE);
    }

    if (test) {
        nob_cmd_append(&cmd, "./example");
        if (!nob_cmd_run_sync_and_reset(&cmd)) {
            exit(EXIT_FAILURE);
        }
    }
}
