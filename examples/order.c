#include "defer.h"

#include <stdio.h>

int main() {
    defer {printf("Last\n");};
    defer {printf("Second\n");};
    defer {printf("First\n");};
}
