#include <stdio.h>
#include <stdint.h>

int find_number(char symbol){
    int number = symbol - '0';
	if (symbol >= 'A') {
		number -= 'A' - '9' - 1;
	}
	if (symbol >= 'a') {
		number -= 'a' - 'Z' - 1;
	}
	return number;
}


char find_char(int number){
	char c = '0' + number;
	if (c > '9'){
		c += 'A' - '9' - 1;
	}
	if (c > 'Z') {
		c += 'a' - 'Z' - 1;
	}
	return c;
}

int main(){
    uint64_t our_set =0;
    uint64_t input_set = 0;
    char c;
    while(scanf("%c", &c) == 1){
        if (c == '&'){
            our_set &=input_set;
            input_set = 0;
        }
        else if (c == '|'){
            our_set|=input_set;
            input_set = 0;
        }
        else if (c == '^'){
            our_set^=input_set;
            input_set=0;
        }
        else if(c == '~'){
            our_set = ~our_set;
            input_set=0;
        }
        else{
            input_set |= (1lu << find_number(c));
        }
    }
    for(int pos = 0; pos < 62; ++pos){
		if(1 & (our_set >> pos)) {
			printf("%c", find_char(pos));
		}
	}
}

