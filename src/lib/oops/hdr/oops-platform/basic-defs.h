#pragma once

#include <string>

#include "oops-platform/compats.h"

#define KNRM "\x1B[0m"
#define KBLD "\x1B[1m"
#define KULN "\x1B[4m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

#define OOPS_BANNER "Copyright (c) 2017 D. Mackay. All rights reserved.\n"

extern "C" void dbg2 (const char * funcName, const char * fmt, ...);
extern "C" SPECNORETURN void fatalError2 (const char * funcName,
                                          const char * fmt, ...) ATTRNORETURN;
extern "C" void oopsMsg2 (const char * fmt, ...);

/* Thank you to Richard Hansen for a standards-compliant way of doing this:
 * http://stackoverflow.com/a/11172679
 */

#define dbg(...) dbg2 (PRINTFUNCNAME, FIRST (__VA_ARGS__) REST (__VA_ARGS__))
#define fatalError(...)                                                        \
    fatalError2 (PRINTFUNCNAME, FIRST (__VA_ARGS__) REST (__VA_ARGS__))
#define oopsMsg(...) oopsMsg2 (FIRST (__VA_ARGS__) REST (__VA_ARGS__))

/* expands to the first argument */
#define FIRST(...) FIRST_HELPER (__VA_ARGS__, throwaway)
#define FIRST_HELPER(first, ...) first

/*
 * if there's only one argument, expands to nothing.  if there is more
 * than one argument, expands to a comma followed by everything but
 * the first argument.  only supports up to 9 arguments but can be
 * trivially expanded.
 */
#define REST(...) REST_HELPER (NUM (__VA_ARGS__), __VA_ARGS__)
#define REST_HELPER(qty, ...) REST_HELPER2 (qty, __VA_ARGS__)
#define REST_HELPER2(qty, ...) REST_HELPER_##qty (__VA_ARGS__)
#define REST_HELPER_ONE(first)
#define REST_HELPER_TWOORMORE(first, ...) , __VA_ARGS__
#define NUM(...)                                                               \
    SELECT_10TH (__VA_ARGS__, TWOORMORE, TWOORMORE, TWOORMORE, TWOORMORE,      \
                 TWOORMORE, TWOORMORE, TWOORMORE, TWOORMORE, ONE, throwaway)
#define SELECT_10TH(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) a10

using std::string;