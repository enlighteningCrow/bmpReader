#include <unistd.h>
#include "bmp.h"
#include "utils.h"
#include "utils_bmp.h"
#include "utils_pix.h"

extern const char *help_message;

int main(void) {
    bmpArray  bmp_arr_val;
    bmpArray *bmp_arr = &bmp_arr_val;
    init_bmpArr(bmp_arr, 0);

    intArray  uinput_val;
    intArray *uinput = &uinput_val;
    init(uinput, 0);


    fputs("bmpEdit | type (h)elp for more information.\n", stdout);

    for (int1_t fce = 0, return_code = 0, mode = 0;;) {
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
        // #define check_opened_file                                                                                              \
//     {                                                                                                                  \
//         if (!size_bmpArr(bmp_arr)) {                                                                                   \
//             fprintf(stdout, "No bitmap files are currently open. Open one using the (o)pen command.\n");               \
//             continue                                                                                                   \
//         }                                                                                                              \
//     }


        fputs(mode ? "...     " : "->| ", stdout);
        return_code = readLine(uinput, stdin);
        if (return_code || check(q) || check(quit)) {
        quit:
            fputc('\n', stdout);
            break;
        }
        if (check(h, help)) {
        help:
            fputs(help_message, stdout);
        }


        if (check(o, open)) {
        open:
            if (access(c_str(uinput), F_OK)) {
                fprintf(stdout, "File with name \"%s\" not found in current directory.\n", c_str(uinput));
                continue;
            }
            resize_bmpArr(bmp_arr, size(bmp_arr) + 1);
            parse_bmp(bmp_arr->m_data + (size(bmp_arr) - 1), uinput);
            fce  = size(bmp_arr) - 1;
            mode = 0;
        }
        if (check(l, list)) {
        list:
            for (size_t i = 0; i < size_bmpArr(bmp_arr); ++i) { fputs(c_str(&bmp_arr->m_data[fce].filename), stdout); }
            fputc('\n', stdout);
        }
        if (!size_bmpArr(bmp_arr)) {
            fprintf(stdout, "No bitmap files are currently open. Open one using the (o)pen command.\n");
            continue
        }
        if (check(f, fill)) {
        fill:
            // TODO: Check if enough args are in the string, using a split function, and if not, set mode then
            // continue;, without clearing the input string (uinput)
            // fill_num()
        }
    }
}

// TODO!!!!!: Fix the resize function (realloc seems to have problems when giving new addresses. Fix it.)