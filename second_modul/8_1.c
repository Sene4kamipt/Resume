#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

int main(int args, char* argv[]) {
	int in = open(argv[1], O_RDONLY);
	int curr_value;
    int r =1;
	uint32_t next_pointer;
    int flag =0;
	if (read(in, &curr_value, sizeof(curr_value)) <= 0) {
        return 0;
    }
	read(in, &next_pointer, 4);
	while (next_pointer > 0) {
		printf("%d ", curr_value);
		lseek(in, next_pointer, SEEK_SET);
		read(in, &curr_value, sizeof(curr_value));
		flag = read(in, &next_pointer, 4);
	}
	printf("%d", curr_value);;
	return 0;
}
