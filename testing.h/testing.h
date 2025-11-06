#ifndef TESTING_H
#define TESTING_H

#if !defined TESTING_IMPL
    #define  TESTING_IMPL 1
#endif

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

extern size_t tests_passed;
extern size_t tests_failed;
extern bool tests_print_success;
extern const char* tests_current;

void tests_arg_parse(int* argc, const char*** argv);
void tests_reset();
void TEST_BEGIN(const char* name);
bool _test_assertion(const char* file, const char* function, int line, bool expr, const char* format, ...);
bool _test_array(const char* file, const char* function, int line, const void* a1, const void* a2, size_t elem_size, size_t len1, size_t len2, const char* expression);
bool _test_eqi(const char* file, const char* function, int line, long long a, long long b, const char* raw_expression);
int tests_end();

#define TEST(expr)      _test_assertion(__FILE__, __FUNCTION__, __LINE__, (expr), "%s", #expr)
#define TEST_PASS(...)  _test_assertion(__FILE__, __FUNCTION__, __LINE__, true , __VA_ARGS__)
#define TEST_FAIL(...)  _test_assertion(__FILE__, __FUNCTION__, __LINE__, false, __VA_ARGS__)
#define TEST_ARRAY(a1, a2, n1, n2)   _test_array(__FILE__, __FUNCTION__, __LINE__, (a1), (a2), (sizeof((a1)[0])), (n1), (n2), #a1 " === " #a2)
#define TEST_EQI(a, b)  _test_eqi(__FILE__, __FUNCTION__, __LINE__, (a), (b), #a " == " #b)
#define REQUIRE(expr)   (_test_assertion(__FILE__, __FUNCTION__, __LINE__, (expr), "%s", #expr) || (exit(tests_end()), 0))


#define MAXOF(a, b)     (((a) > (b)) ? (a) : (b))
#define MINOF(a, b)     (((a) < (b)) ? (a) : (b))
#define ARRAY_LENGTH(x) (sizeof ((x)) / sizeof ((x)[0]))



/// ----- Implementation -----
#if TESTING_IMPL
#include <stdarg.h>
size_t tests_passed = 0;
size_t tests_failed = 0;
bool tests_print_success = true;
const char* tests_current = NULL;
void TEST_BEGIN(const char* name) {
    tests_current = name;
}
bool _test_eqi(const char* file, const char* function, int line, long long a, long long b, const char* raw_expression) {
    bool expr = a == b;
    return _test_assertion(file, function, line, expr, "%s  [%lld %s %lld]", raw_expression, a, expr ? "==" : "!=", b);
}

bool _test_assertion(const char* file, const char* function, int line, bool expr, const char* format, ...) {
    // Simplify file paths
    // const char* f1 = strrchr(file, '/');
    // const char* f2 = strrchr(file, '\\');
    // file = f1 ? (f2 ? (f2 > f1 ? f2 : f1) : f1) + 1
    //         : (f2 ? f2 + 1 : file);

    if(expr) {
        tests_passed++;
        if(tests_print_success) {
            fprintf(stderr, "+pass  %s:%d %s(): ", file, line, function);
            if (tests_current) fprintf(stderr, "in '%s': ", tests_current);
            va_list args;
            va_start(args, format);
            vfprintf(stderr, format, args);
            va_end(args);
            fprintf(stderr, "\n");
        }
    } else {
        tests_failed++;
        fprintf(stderr, "-FAIL  %s:%d %s(): ", file, line, function);
        if (tests_current) fprintf(stderr, "in '%s': ", tests_current);
        va_list args;
        va_start(args, format);
        vfprintf(stderr, format, args);
        va_end(args);
        fprintf(stderr, "\n");
    }
    return expr;
}
bool _test_array(const char* file, const char* function, int line, const void* a1, const void* a2, size_t elem_size, size_t len1, size_t len2, const char* expression) {
    bool match = len1 == len2 && memcmp(a1, a2, elem_size * len1) == 0;
    if(!_test_assertion(file, function, line, match, "%s", expression)) {
        fprintf(stderr, "  a1 [%zu]: ", len1);
        for(size_t i = 0; i < MINOF(len1, 99u); i++) fprintf(stderr, " %02x", ((const unsigned char*)a1)[i]);
        fprintf(stderr, "\n  a2 [%zu]: ", len2);
        for(size_t i = 0; i < MINOF(len2, 99u); i++) fprintf(stderr, " %02x", ((const unsigned char*)a2)[i]);
        fprintf(stderr, "\n");
    }
    return match;
}
void tests_reset() {
    tests_passed = 0;
    tests_failed = 0;
}
int tests_end() {
    printf("=================================\n");
    size_t total = tests_passed + tests_failed;
    size_t percent = (total == 0) ? 0 : (100 * tests_passed / total);
    printf("Passed  %3zu / %3zu   %3zu%%\n", tests_passed, total, percent);
    return tests_failed > 0;
}
void tests_arg_parse(int* argc, const char*** argv) {
    while(*argc > 1) {
        if(strcmp((*argv)[1], "-v") == 0) {
            tests_print_success = true;
        } else if(strcmp((*argv)[1], "-q") == 0) {
            tests_print_success = false;
        } else {
            break;
        }
        (*argc)--;
        (*argv)++;
    }
}
#endif

#endif
