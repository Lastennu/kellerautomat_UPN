#define _POSIX_C_SOURCE 200809L

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int kellerautomat(char stepMode, char *word);

static void run_case(const char *word, int expected_result) {
    printf("Testing word: %s, Output: ", word);
    int result = kellerautomat(0, (char *)word);
    assert(result == expected_result);
}

int main(void) {
    run_case("1", 0);
    run_case("12+", 0);
    run_case("23*", 0);
    run_case("123++", 0);
    run_case("48+3*", 0);
    run_case("34+62+89+43+***", 0);
    run_case("31+78+987+1214++7++++++", 0);
    run_case("345++5678++++", 0);

    run_case("+12", 1);
    run_case("1+", 1);
    run_case("12", 1);
    run_case("13++", 1);
    run_case("34+*", 1);
    run_case("8+9+7*2*", 1);

    printf("All kellerautomat tests passed.\n");
    return 0;
}
