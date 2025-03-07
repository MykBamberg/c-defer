#include "defer.h"

#include <stdio.h>

int main() {
    int num = 0;

    {
        defer {num = 2;};
        num = 1;
    }

    printf("Number: %d\n", num);
}
