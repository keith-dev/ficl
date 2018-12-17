/*
** stub main for testing Ficl
** $Id: main.c,v 1.2 2010/09/10 09:01:28 asau Exp $
*/
/*
** Copyright (c) 1997-2001 John Sadler (john_sadler@alum.mit.edu)
** All rights reserved.
**
** Get the latest Ficl release at http://ficl.sourceforge.net
**
** I am interested in hearing from anyone who uses Ficl. If you have
** a problem, a success story, a defect, an enhancement request, or
** if you would like to contribute to the Ficl release, please
** contact me by email at the address above.
**
** L I C E N S E  and  D I S C L A I M E R
** 
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
**
** THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
** DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
** OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
** LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
** OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
** SUCH DAMAGE.
*/

#include <stdio.h>
#include <stdlib.h>
#include "ficl.h"

#ifdef FICL_WANT_LIBEDIT
  #include <editline.h>

  #if FICL_WANT_LIBEDIT > 1
    #include <unistd.h>
    #include <string.h>
    #include <errno.h>
    #include <histedit.h>

    static char * prompt(EditLine *e);

    static void save_history(History* hist, HistEvent* ev);
    static void restore_history(History* hist, HistEvent* ev);
  #endif
#endif

int main(int argc, char **argv)
{
    int returnValue = 0;
    char buffer[256];
    ficlVm *vm;
    ficlSystem *system;
    char *input;
#ifdef FICL_WANT_LIBEDIT
  #if FICL_WANT_LIBEDIT > 1
    int inputlen;
    EditLine *el;
    History *hist;
    HistEvent ev;

    el = el_init(argv[0], stdin, stdout, stderr);
    el_set(el, EL_PROMPT, &prompt);
    el_set(el, EL_EDITOR, "emacs");

    hist = history_init();
    if (hist)
    {
        history(hist, &ev, H_SETSIZE, 800);
        restore_history(hist, &ev);
        el_set(el, EL_HIST, history, hist);
    }
  #endif
#endif

    system = ficlSystemCreate(NULL);
    ficlSystemCompileExtras(system);
    vm = ficlSystemCreateVm(system);

    returnValue = ficlVmEvaluate(vm, ".ver .( " __DATE__ " ) cr quit");

    /*
    ** load files specified on command-line
    */
    if (argc  > 1)
    {
        snprintf(buffer, sizeof(buffer), ".( loading %s ) cr load %s\n cr", argv[1], argv[1]);
        returnValue = ficlVmEvaluate(vm, buffer);
    }

    while (returnValue != FICL_VM_STATUS_USER_EXIT)
    {
#ifdef FICL_WANT_LIBEDIT
  #if FICL_WANT_LIBEDIT == 1
        input = readline(FICL_PROMPT);
        if (!input) break;
  #else
        input = (char*)el_gets(el, &inputlen);
        if (inputlen == 0) break;
        if (hist) history(hist, &ev, H_ENTER, input);
  #endif
#else
        fputs(FICL_PROMPT, stdout);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;
        input = buffer;
#endif

        returnValue = ficlVmEvaluate(vm, input);
    }
    printf("\n");

    ficlSystemDestroy(system);

#ifdef FICL_WANT_LIBEDIT
  #if FICL_WANT_LIBEDIT > 1
    save_history(hist, &ev);
    history_end(hist);
    el_end(el);
  #endif
#endif

    return 0;
}

#ifdef FICL_WANT_LIBEDIT
  #if FICL_WANT_LIBEDIT > 1
    #ifndef MAXPATHLEN
    #define MAXPATHLEN 1024
    #endif

    static char* filename_history;
    static char* build_filename_history();

    char* prompt(EditLine *e) {
        return FICL_PROMPT;
    }

    char* build_filename_history() {
        size_t len;
        char* buf;
        char* ret;
        char* env = getenv("HOME");
        char filename[] = "/.ficl_history";

        if (env) {
            len = strlen(env) + sizeof(filename);
            buf = calloc(len, sizeof(char));
            strcpy(buf, env);
            strcat(buf, filename);
            return buf;
        }
        else {
            len = MAXPATHLEN + sizeof(filename);
            buf = calloc(len, sizeof(char));
            ret = getcwd(buf, len);
            if (ret == NULL) {
                free(buf);
                return NULL;
            }
            len = strlen(buf) + 1;
            return realloc(buf, len);
        }
    }

    void save_history(History* hist, HistEvent* ev) {
        if (!hist || !ev)
            return;
        if (!filename_history && !((filename_history = build_filename_history())))
            return;

        history(hist, ev, H_SAVE, filename_history);
    }

    void restore_history(History* hist, HistEvent* ev) {
        if (!hist || !ev)
            return;
        if (!filename_history && !((filename_history = build_filename_history())))
            return;

        history(hist, ev, H_LOAD, filename_history);

        free(filename_history);
        filename_history = NULL;
    }
  #endif
#endif
