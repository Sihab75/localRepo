#include <stdio.h>
	int printNum(int n, int i) {
		if (n <= 0) {
			return 0;
		}
		printf("%d ",i);
		
		return printNum(n-1,i + 1);
	}
	int main () {
		printNum(5,1);
		return 0;
	}
