// https://www.hackerrank.com/challenges/counting-valleys/
#include <stdio.h>

int countingValleys(int n, char* s) {
    int prev_position = 0;
    int position = 0 ;
    int valleys_cnt = 0;
    int i;

    for (i=0; s[i] != 0; i++){
        prev_position = position;
        switch(s[i]) {
            case 'U':
                position += 1;
                break;
            case 'D':
                position += -1;
                break;
        }
        if (position == 0 && prev_position < 0)
            valleys_cnt++;
    }
    return valleys_cnt;
}

int main()
{
    printf("counting %i\n", countingValleys(8, "DDUUDDUDUUUD"));
    return 0;
}