#include <unistd.h>
#include "bmp.h"

extern const char *help_message;

int main(void) {

    // // FILE *f = fopen("../rainbow copy.bmp", "r");
    // // FILE *f = fopen("../rgb.bmp", "rb");
    // FILE *f = fopen("/home/twistingcamel/programs/kmitl/c++/bmpReader/rainbow.bmp", "rb");
    // // FILE *f = fopen("/home/twistingcamel/programs/kmitl/c++/bmpReader/rainbow.bmp", "rb");
    // // FILE *f = fopen("/home/twistingcamel/programs/kmitl/c++/bmpReader/trial.txt", "rb");
    // // intArray read()
    // printf("%p\n", f);


    // Bmp bmp1;
    // init_bmp(&bmp1);

    // // init_pix(&bmp1.pixels, 0);
    // // init(&bmp1.whole_str, 0);

    // // init(&bmp1.whole_str, 1000000);
    // // resize(&bmp1.whole_str, 0);

    // parse(&bmp1, f);
    // intArray black;
    // init(&black, 3);
    // for (size_t i = 0; i < 3; ++i) { black.m_data[i] = 0; }
    // // fill(&bmp1, 100, 100, 101, 101, &black, (char)(127));

    // intArray str1;
    // init(&str1, 10);
    // strcpy(str1.m_data, "Hello");

    // // fprint(&str1, stdout);
    // // intArray a;
    // // init(&a, 0);
    // // for (size_ut i = 1; i < 10000; ++i) { resize(&a, i); }
    // // for (size_ut i = 0; i < 10000; ++i) { resize(&a, 10000 - i); }
    // // for (size_ut i = 0; i < 200000; ++i) { concatEq(&a, &str1); }
    // // resize(&a, 10);
    // // fprint(&a, stdout);
    // // fprintf(stdout, "%c", '\n');
    // // for (size_ut i = 0; i < 20; ++i) { concatEq(&a, &str1); }
    // // fprint(&a, stdout);
    // // fprintf(stdout, "%c", '\n');

    // // fprint(&a, stdout);

    // // dest_pix(&bmp1.pixels);
    // // dest(&bmp1.whole_str);

    // intArray file_name;
    // init(&file_name, 0);
    // strAssignC(&file_name, "../zBitmap.bmp");
    // fill_prompt(&bmp1);

    // // fill(&bmp1, 5, 15);

    // // resize_bmp(&bmp1, 0.5L);

    // write_bmp(&bmp1, &file_name);

    // dest(&file_name);

    // dest_bmp(&bmp1);

    // dest(&black);
    // // dest(&a);
    // dest(&str1);
    // fclose(f);
    // return 0;

    Bmp  bmp_val;
    Bmp *bmp = &bmp_val;
    init_bmp(bmp);

    intArray  uinput_val;
    intArray *uinput = &uinput_val;
    init(uinput, 0);

    // strAssignC(uinput, "/home/twistingcamel/programs/kmitl/c++/bmpReader/rgb.bmp");

    // parse_bmp(bmp, uinput);

    // // fill_num(bmp, 0, 0, 1, 1, 0x90, 0xff, 0xff, 0xff);

    // scale_bmp(bmp, 100.0L);

    // strAssignC(uinput, "/home/twistingcamel/programs/kmitl/c++/bmpReader/zBitmap2.bmp");

    // write_bmp(bmp, uinput);

    fputs("bmpEdit | type (h)elp for more information.\n", stdout);

    for (int1_t file_open_count = 0, return_code = 0, mode = 0;;) {
        /**
         *  @brief
         *  Note:
         *      Mode 0: no file opened; ask user for file
         *      Mode 1: file buffer active
         *
         */
        fputs("->| ", stdout);
        return_code = readLine(uinput, stdin);
        if (return_code || strEqC(uinput, "q") || strEqC(uinput, "quit")) {
            fputc('\n', stdout);
            break;
        }
        if (strEqC(uinput, "h") || strEqC(uinput, "help")) { fputs(help_message, stdout); }

        // fputs("->| ", stdout);
        // readLine(uinput, stdin);

#define check_opened_file

        if (strEqC(uinput, "o") || strEqC(uinput, "open")) {
            // fputs("Enter the name of the bmp file to edit:\t", stdout);
            // if()
            if (access(c_str(uinput), F_OK)) {
                fprintf(stdout, "File with name \"%s\" not found in current directory.\n", c_str(uinput));
                continue;
            }
            parse_bmp(bmp, uinput);
            mode = 1;
        }
        else if (mode == 1) {
            fputs("Enter operation:\t", stdout);
        }
    }
}

// TODO!!!!!: Fix the resize function (realloc seems to have problems when giving new addresses. Fix it.)