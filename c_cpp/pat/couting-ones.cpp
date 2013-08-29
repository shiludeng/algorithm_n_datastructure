#include <stdio.h>

int tens[] = {
	1, // 0 
	10, 
	100, 
	1000, 
	10000, 
	100000, 
	1000000, 
	10000000, 
	100000000, 
	1000000000 
};


// n=a9a8a7...a0
// ai = 0, Hi * 10^i
// ai > 1, (Hi + 1) * 10^i
// ai == 1, Hi * 10^i + Li + 1
int countOnes(int n) {
	int res = 0;
	int Hi, Li, ai;

	for (int i = 0; i <= 9; i++) {
		Li = n % tens[i];
		if (i == 9) {
			Hi = 0;
		} else {
			Hi = n / tens[i + 1];
		}
		ai = n / tens[i] % 10; 

		res += Hi * tens[i];
		if (ai == 1) {
			res += Li + 1;
		} else if (ai > 1) {
			res += tens[i];
		}
	}
	return res;
}

int main() {
	int n;
	while (-1 != scanf("%d", &n)) {
		printf("%d\n", countOnes(n));
	}
}
