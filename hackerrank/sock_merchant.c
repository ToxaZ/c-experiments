// https://www.hackerrank.com/challenges/sock-merchant/
#include <stdio.h>

int sockMerchant(int n, int ar_count, int* ar) {
	int counts[101] = {0};
	int cnt = 0;
	int i;

	for(i=0;i<ar_count;i++){
		counts[ar[i]]++;
	}

	for(i=0;i<=100;i++){
		if(counts[i]>0){
			cnt += counts[i]/2;
		}
	}
	return cnt;
}


int main()
{
	int T[] = {10, 10, 10, 10, 20, 50};
	printf("Socks pairs: %i\n", sockMerchant(12, 3, T));
	return 0;
}
