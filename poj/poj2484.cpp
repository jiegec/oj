#include <stdio.h>

int n;

int main() {
    while(scanf("%d",&n) && n) {
        if (n <= 2 )
            printf("Alice\n");
        else
            printf("Bob\n");
    }
}
