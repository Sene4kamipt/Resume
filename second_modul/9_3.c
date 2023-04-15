#include <libgen.h>
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
    char full_name[PATH_MAX];
    char linked_name[PATH_MAX];
    struct stat st;
    char* end;
    while (fgets(file_name, PATH_MAX, stdin)) {
        end = memchr(file_name, '\n', PATH_MAX);
        if (end != NULL) {
            *end = '\0';
        } 
        if ((lstat(file_name, &st) != -1)&&(S_ISREG(st.st_mode))) {
            strcpy(linked_name, "link_to_");
            strcat(linked_name, basename(file_name));
            symlink(file_name, linked_name);
        }
        else{
             if ((lstat(file_name, &st) != -1)&&(S_ISLNK(st.st_mode))) {
                 realpath(file_name, full_name);
                 puts(full_name);
             }
        }
    }
    return 0;
}
