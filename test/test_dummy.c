#include <assert.h>
#include <stdio.h>

void test_that_fails(void) {
    puts("something failed");
    assert(1);
}

int main() {
    test_that_fails();

    return 0;
}
