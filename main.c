#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "bmp.h"
#include "utils.h"
#include "utils_bmp.h"
#include "utils_pix.h"

extern const char    *help_message;
typedef unsigned char uint1_t;

enum {
    NORMAL = 0,
    QUIT   = 1,
    HELP   = 2,
    OPEN   = 3,
    FILL   = 4,
    RESIZE = 5,
    SCALE  = 6,
    CROP   = 7,
    EDIT   = 8,
    WRITE  = 9,
    LIST   = 10,
};

#define MAX_SIZE 100

int main(void) {
    // fcntl(0, F_SETFL, O_NONBLOCK);
    bmpArray  bmp_arr_val;
    bmpArray *bmp_arr = &bmp_arr_val;
    init_bmpArr(bmp_arr, 0);

    intArray  uinput_val;
    intArray *uinput = &uinput_val;
    init(uinput, 0);


    fputs("bmpEdit | type (h)elp for more information.\n", stdout);

    intArray  uinput_args_val[MAX_SIZE];
    intArray *uinput_args[MAX_SIZE];
    for (size_t i = 0; i < MAX_SIZE; ++i) { uinput_args[i] = &(uinput_args_val[i]); }
    for (size_t i = 0; i < MAX_SIZE; ++i) { init(uinput_args[i], 0); }
    uint1_t arg_count = 0;

    bool first = false;

    for (int1_t fce = 0, return_code = 0, mode = 0;; first = false) {
/**
 *  @brief
 *  Note:
 *      fce:            file currently editing
 *      return_code:
 *          0: normal
 *          1: terminate (EOF reached)
 *      mode:
 *          0:      in normal mode (not in any function)
 *          not 0:  currently in middle of prompt
 */
#define check(arg1, arg2) strEqC(uinput, #arg1) || strEqC(uinput, #arg2)
#define check_opened_file                                                                                              \
    {                                                                                                                  \
        if (!size_bmpArr(bmp_arr)) {                                                                                   \
            fprintf(stdout, "No bitmap files are currently open. Open one using the (o)pen command.\n");               \
            fcntl(0, F_SETFL, O_NONBLOCK);                                                                             \
            while (fgetc(stdin) != EOF)                                                                                \
                ;                                                                                                      \
            fcntl(0, F_SETFL, fcntl(0, F_GETFL) & (~O_NONBLOCK));                                                      \
            clear(uinput);                                                                                             \
            for (size_t i = 0; i < MAX_SIZE; ++i) { clear(uinput_args[i]); }                                           \
            continue;                                                                                                  \
        }                                                                                                              \
    }
#define stringize(arg) #arg
#define encaseBeginNoCheck(argc, arg)                                                                                  \
    if (check(argc, arg)) {                                                                                            \
        first = true;                                                                                                  \
    arg:
#define encaseBegin(argc, arg)                                                                                         \
    if (check(argc, arg)) {                                                                                            \
        first = true;                                                                                                  \
    arg:                                                                                                               \
        check_opened_file;
#define encaseEnd                                                                                                      \
    for (size_t i = 0; i < arg_count; ++i) { clear(uinput_args[i]); }                                                  \
    arg_count = 0;                                                                                                     \
    clear(uinput);                                                                                                     \
    mode = 0;                                                                                                          \
    continue;                                                                                                          \
    }
#define parseInput(var, target, argNo)                                                                                 \
    {                                                                                                                  \
        cstr         = c_str(uinput_args[argNo]);                                                                      \
        int response = sscanf(cstr, "%" #target, &var);                                                                \
        if (!response)                                                                                                 \
            fprintf(stdout, "Given input \"%s\" is not compatible with scanf target \"" #target "\".\n", cstr);        \
        free_c_str(uinput_args[argNo], cstr);                                                                          \
    }

        fputs(mode ? "...     " : "->| ", stdout);
        fflush(stdout);
        // restart:
        if (!arg_count && !mode) return_code = readLine(uinput, stdin);
        // if (strEqC(uinput, "")) {
        //     // puts("Empty");
        //     goto restart;
        //     // continue;
        // }

        // char *cstrtmp = c_str(uinput);
        // fprintf(stdout, "Input: %s\nReturn code: %d\n", cstrtmp, return_code);
        // free_c_str(uinput, cstrtmp);
        if (return_code == 1) goto quit;


        if (mode) {
            switch (mode) {
            case HELP: goto help;
            case OPEN: goto open;
            case FILL: goto fill;
            case RESIZE: goto resize;
            case SCALE: goto scale;
            case CROP: goto crop;
            case EDIT: goto edit;
            case WRITE: goto write;
            case LIST: goto list;
            case QUIT: goto quit;
            default: fprintf(stdout, "Mode %d is not defined.\n", mode); break;
            }
        }

        if (check(q, quit)) {
        quit:;
            if (return_code == 1) fputc('\n', stdout);
            break;
        }

        // if (check(h, help)) {
        // help:;
        //     fputs(help_message, stdout);
        // }

        encaseBeginNoCheck(h, help) { fputs(help_message, stdout); }
        encaseEnd;

        // if (check(o, open)) {
        // open:;
        //     char *cstr = c_str(uinput);
        //     if (access(cstr, F_OK)) {
        //         fprintf(stdout, "File with name \"%s\" not found in current directory.\n", cstr);
        //         continue;
        //     }
        //     free_c_str(uinput, cstr);
        //     resize_bmpArr(bmp_arr, size_bmpArr(bmp_arr) + 1);
        //     parse_bmp(bmp_arr->m_data + (size_bmpArr(bmp_arr) - 1), uinput);
        //     fce  = size_bmpArr(bmp_arr) - 1;
        //     mode = 0;
        // }

        encaseBeginNoCheck(o, open) {
            mode = OPEN;
            if (first && return_code == 2) goto endOfLoop;
            while (arg_count < 1) {
                return_code = readLineThroughSpaces(uinput_args[arg_count], stdin);
                ++arg_count;
                if (return_code == 1) goto quit;
                if (arg_count == 1) break;
                if (return_code == 2) { goto endOfLoop; }
            }
            char *cstr = c_str(uinput_args[0]);
            if (access(cstr, F_OK)) {
                fprintf(stdout, "File with name \"%s\" not found.\n", cstr);
                free_c_str(uinput_args[0], cstr);
                // continue;
            }
            else {
                free_c_str(uinput_args[0], cstr);
                resize_bmpArr(bmp_arr, size_bmpArr(bmp_arr) + 1);
                parse_bmp(bmp_arr->m_data + (size_bmpArr(bmp_arr) - 1), uinput_args[0]);
                fce = size_bmpArr(bmp_arr) - 1;
            }
        }
        encaseEnd;

        encaseBegin(w, write) {
            mode = OPEN;
            if (arg_count == 0 && return_code == 2) {
                write_bmp(bmp_arr->m_data + fce, &(bmp_arr->m_data[fce].filename));
            }
            else {
                if (first && return_code == 2) goto endOfLoop;
                while (arg_count < 1) {
                    return_code = readLineThroughSpaces(uinput_args[arg_count], stdin);
                    ++arg_count;
                    if (return_code == 1) goto quit;
                    if (arg_count == 1) break;
                    if (return_code == 2) { goto endOfLoop; }
                }
                char *cstr = c_str(uinput_args[0]);
                // TODO: This
                if (!access(cstr, F_OK)) {
                    fprintf(stdout, "File with name \"%s\" already exists.\n", cstr);
                    free_c_str(uinput_args[0], cstr);
                    // continue;
                }
                else {
                    free_c_str(uinput_args[0], cstr);
                    resize_bmpArr(bmp_arr, size_bmpArr(bmp_arr) + 1);
                    write_bmp(bmp_arr->m_data + (size_bmpArr(bmp_arr) - 1), uinput_args[0]);
                    fce = size_bmpArr(bmp_arr) - 1;
                }
            }
        }
        encaseEnd;

        encaseBegin(s, scale) {
            mode = SCALE;
            if (first && return_code == 2) goto endOfLoop;
            while (arg_count < 1) {
                return_code = readLine(uinput_args[arg_count], stdin);
                ++arg_count;
                if (return_code == 1) goto quit;
                if (arg_count == 1) break;
                if (return_code == 2) { goto endOfLoop; }
            }
            // char *cstr = c_str(uinput_args[0]);
            // if (access(cstr, F_OK)) {
            //     fprintf(stdout, "File with name \"%s\" not found in current directory.\n", cstr);
            //     free_c_str(uinput_args[0], cstr);
            //     // continue;
            // }
            // else {
            //     free_c_str(uinput_args[0], cstr);
            //     resize_bmpArr(bmp_arr, size_bmpArr(bmp_arr) + 1);
            //     parse_bmp(bmp_arr->m_data + (size_bmpArr(bmp_arr) - 1), uinput_args[0]);
            //     fce = size_bmpArr(bmp_arr) - 1;
            // }
            double factor;
            char  *cstr;
            parseInput(factor, lf, 0);
            scale_bmp(bmp_arr->m_data + fce, (long double)factor);
        }
        encaseEnd;

        encaseBegin(e, edit) {
            mode = EDIT;
            if (first && return_code == 2) goto endOfLoop;
            while (arg_count < 1) {
                return_code = readLine(uinput_args[arg_count], stdin);
                ++arg_count;
                if (return_code == 1) goto quit;
                if (arg_count == 1) break;
                if (return_code == 2) { goto endOfLoop; }
            }
            unsigned int new_fce;
            char        *cstr;
            parseInput(new_fce, u, 0);
            // scale_bmp(bmp_arr->m_data + fce, factor);
            if (new_fce >= size_bmpArr(bmp_arr))
                fprintf(stdout, "File #%d is not in the opened list\n", new_fce);
            else {
                fce = (int1_t)(new_fce);
            }
        }
        encaseEnd;

        // encaseBeginNoCheck(c, crop) {
        //     mode = SCALE;
        //     if (first && return_code == 2) goto endOfLoop;
        //     while (arg_count < 4) {
        //         return_code = readLine(uinput_args[arg_count], stdin);
        //         ++arg_count;
        //         if (return_code == 1) goto quit;
        //         if (arg_count == 4) break;
        //         if (return_code == 2) { goto endOfLoop; }
        //     }
        //     size_t x0, y0 factor;
        //     char *cstr;
        //     parseInput(factor, lf, 0);
        //     scale_bmp(bmp_arr->m_data + fce, factor);
        // }
        // encaseEnd;

        encaseBegin(c, crop) {
            mode = CROP;
            if (arg_count == 0 && return_code == 2) { fill_prompt(bmp_arr->m_data + fce); }
            else {
                if (first && return_code == 2) goto endOfLoop;
                while (arg_count < 4) {
                    return_code = readLine(uinput_args[arg_count], stdout);
                    ++arg_count;
                    if (return_code == 2) { goto endOfLoop; }
                    if (arg_count == 4) break;
                    if (return_code == 1) goto quit;
                }
                size_t x0, y0, x1, y1;
                char  *cstr;
                parseInput(x0, lu, 0);
                parseInput(y0, lu, 1);
                parseInput(x1, lu, 2);
                parseInput(y1, lu, 3);
                crop_bmp(bmp_arr->m_data + fce, x0, y0, x1, y1);
            }
        }
        encaseEnd;

        encaseBegin(r, resize) {
            mode = RESIZE;
            if (first && return_code == 2) goto endOfLoop;
            while (arg_count < 2) {
                return_code = readLine(uinput_args[arg_count], stdin);
                ++arg_count;
                if (return_code == 1) goto quit;
                if (arg_count == 2) break;
                if (return_code == 2) { goto endOfLoop; }
            }
            // char *cstr = c_str(uinput_args[0]);
            // if (access(cstr, F_OK)) {
            //     fprintf(stdout, "File with name \"%s\" not found in current directory.\n", cstr);
            //     free_c_str(uinput_args[0], cstr);
            //     // continue;
            // }
            // else {
            //     free_c_str(uinput_args[0], cstr);
            //     resize_bmpArr(bmp_arr, size_bmpArr(bmp_arr) + 1);
            //     parse_bmp(bmp_arr->m_data + (size_bmpArr(bmp_arr) - 1), uinput_args[0]);
            //     fce = size_bmpArr(bmp_arr) - 1;
            // }
            int   width, height;
            char *cstr;
            parseInput(width, d, 0);
            parseInput(height, d, 1);
            resize_bmp(bmp_arr->m_data + fce, width, height);
        }
        encaseEnd;

        // if (check(l, list)) {
        // list:;
        encaseBeginNoCheck(l, list) {
            for (size_t i = 0; i < size_bmpArr(bmp_arr); ++i) {
                char *cstr = c_str(&bmp_arr->m_data[i].filename);
                fprintf(stdout, "%lu:\t%s\n", i, cstr);
                // fputs(cstr, stdout);
                // fputc('\n', stdout);
                free_c_str(&bmp_arr->m_data[i].filename, cstr);
                // pop_back_cptr(&bmp_arr->m_data[i].filename);
            }
        }
        encaseEnd;
        // }

        // if (!size_bmpArr(bmp_arr)) {
        //     fprintf(stdout, "No bitmap files are currently open. Open one using the (o)pen command.\n");
        //     continue;
        // }

        encaseBegin(f, fill) {
            mode = FILL;
            if (arg_count == 0 && return_code == 2) {
                if (fill_prompt(bmp_arr->m_data + fce) < 1) goto quit;
            }
            else {
                if (first && return_code == 2) goto endOfLoop;
                while (arg_count < 5) {
                    return_code = readLine(uinput_args[arg_count], stdout);
                    ++arg_count;
                    if (return_code == 2) { goto endOfLoop; }
                    if (arg_count == 5) break;
                    if (return_code == 1) goto quit;
                }
                size_t  x0, y0, x1, y1;
                int1_t  a, r, g, b;
                int     colour;
                int1_t *colour_char = (char *)(&colour);
                char   *cstr;
                // char   *cstr = c_str(uinput_args[0]);
                // sscanf(cstr, "%lu", &x0);
                // free_c_str(uinput_args[0], cstr);
                parseInput(x0, lu, 0);
                parseInput(y0, lu, 1);
                parseInput(x1, lu, 2);
                parseInput(y1, lu, 3);
                parseInput(colour, x, 4);
                b = colour_char[0];
                g = colour_char[1];
                r = colour_char[2];
                a = colour_char[3];
                if (bmp_arr->m_data[fce].dh.bits_per_pixel >= 32) {
                    fill_num(bmp_arr->m_data + fce, x0, y0, x1, y1, a, r, g, b);
                }
                else {
                    fill_num(bmp_arr->m_data + fce, x0, y0, x1, y1, r, g, b);
                }
            }
        }
        encaseEnd;

        if (size(uinput)) {
            char *cstr = c_str(uinput);
            fprintf(stdout, "Unrecognized command: \"%s\"\n", cstr);
            free_c_str(uinput, cstr);
            clear(uinput);
        }

    // if (check(f, fill)) {
    // fill:;
    //     check_opened_file;

    //     // TODO: Check if enough args are in the string, using a split function, and if not, set mode then
    //     // continue;, without clearing the input string (uinput)
    //     // fill_num()

    //     clear(uinput);
    //     mode = 0;
    // }
    endOfLoop:;
    }

    for (size_t i = 0; i < MAX_SIZE; ++i) { dest(uinput_args[i]); }
    dest_bmpArr(bmp_arr);
    dest(uinput);
    return 0;
}

// TODO!!!!!: Fix the resize function (realloc seems to have problems when giving new addresses. Fix it.)