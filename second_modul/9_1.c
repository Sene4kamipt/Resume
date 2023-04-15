#include <fcntl.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    char file_name[PATH_MAX];
    struct stat st;
    char* end;
    while (fgets(file_name, PATH_MAX, stdin)) {
        end = memchr(file_name, '\n', PATH_MAX);
        if (end != NULL) {
            *end = '\0';
        }
        int file = open(file_name, O_RDONLY);
        if ((file > 0) && (fstat(file, &st) != -1) && ((st.st_mode & S_IXUSR) != 0)) {
            if (lseek(file, 0, SEEK_END) < 2) {
                puts(file_name);
                continue;
            }
            lseek(file, 0, SEEK_SET);
            char check_interpretator[2];
            if (read(file, check_interpretator, 2) == -1) {
                puts(file_name);
                continue;
            }
            if ((check_interpretator[0] == '#') && (check_interpretator[1] == '!')) {
                char interpretator_name[PATH_MAX];
                struct stat st_inter;
                if (read(file, interpretator_name, PATH_MAX) == -1) {
                    puts(file_name);
                    continue;
                }
                end = memchr(interpretator_name, '\n', PATH_MAX);
                if (end != NULL) {
                    *end = '\0';
                }
                if ((stat(interpretator_name, &st_inter) == -1) ||((st_inter.st_mode & S_IXUSR) == 0)) {
                    puts(file_name);
                }
            } 
            else {
                lseek(file, 0, SEEK_SET);
                char check_ELF[4];
                if (read(file, check_ELF, 4) == -1) {
                    puts(file_name);
                    continue;
                }
                if (!((check_ELF[0] == 0x7f) && (check_ELF[1] == 'E') && (check_ELF[2] == 'L') && (check_ELF[3] == 'F'))) {
                    puts(file_name);
                }
            }
        }
    }
    return 0;
}
