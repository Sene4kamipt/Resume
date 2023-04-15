#include <stdio.h>

int utf_prefix(char first) {
	int pos = 7;
	while(((1 & (first >> pos)) == 1) && (pos >= 3)) {
		--pos;
	}
	if ((pos >= 6)|| (pos < 3)) {
		return 0;
	}
	return 6 - pos;
}


int main(){
	char c;
    char c2;
	int not_ascii_symbols = 0;
	int ascii_symbols = 0;
	while (scanf("%c", &c)==1) {
		if (1 ^ (1 & (c >> 7))) {
			ascii_symbols+=1;
			continue;
		}
		if(utf_prefix(c) == 0) {
			printf("%d %d", ascii_symbols, not_ascii_symbols);
			return 1;
		}

		for(int i = 0; i < utf_prefix(c); ++i) {
			if (scanf("%c", &c2)==1) {
				if (((1 ^ ((c2 >> 6)%2)) & (c2 >> 7)%2) == 0) {
					printf("%d %d", ascii_symbols, not_ascii_symbols);
					return 1;
				}
			}
			else {
				printf("%d %d", ascii_symbols, not_ascii_symbols);
				return 1;
			}
		}
		not_ascii_symbols+=1;
		}
	printf("%d %d", ascii_symbols, not_ascii_symbols);
}
