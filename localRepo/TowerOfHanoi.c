#include <stdio.h>

void towerOfHanoi (int n, char source, char auxiliary, char destination) {
    if (n == 1) {
        printf("move disk 1 from %c to %c\n", source, destination);
        return;
    }
    towerOfHanoi (n-1, source, destination, auxiliary);
    printf("mode disk %d from %c to %c\n", n, source, destination);
    towerOfHanoi (n-1, auxiliary, source, destination);

}

int main () {
    int n;
    scanf("%d", &n);
    towerOfHanoi(n, 'A', 'B', 'C');
    return 0;
}