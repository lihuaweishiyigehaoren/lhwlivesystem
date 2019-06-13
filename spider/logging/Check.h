#pragma once

#include <cstdlib>

#define CHECK(expr) LOG_CHECK(expr)

#define CHECK_OP(expr1, op, expr2) CHECK((expr1) op (expr2))

#define CHECK_EQ(expr1, expr2) CHECK_OP(expr1, ==, expr2)
#define CHECK_NE(expr1, expr2) CHECK_OP(expr1, !=, expr2)
#define CHECK_LE(expr1, expr2) CHECK_OP(expr1, <=, expr2)
#define CHECK_LT(expr1, expr2) CHECK_OP(expr1, <, expr2)
#define CHECK_GE(expr1, expr2) CHECK_OP(expr1, >=, expr2)
#define CHECK_GT(expr1, expr2) CHECK_OP(expr1, >, expr2)

#define CHECK_NOTNULL(expr) CHECK(expr); expr

#define DCHECK(expr) DLOG_CHECK(expr)

#define DCHECK_OP(expr1, op, expr2) DCHECK(expr1 op expr2)

#define DCHECK_EQ(expr1, expr2) DCHECK_OP(expr1, ==, expr2)
#define DCHECK_NE(expr1, expr2) DCHECK_OP(expr1, !=, expr2)
#define DCHECK_LE(expr1, expr2) DCHECK_OP(expr1, <=, expr2)
#define DCHECK_LT(expr1, expr2) DCHECK_OP(expr1, <, expr2)
#define DCHECK_GE(expr1, expr2) DCHECK_OP(expr1, >=, expr2)
#define DCHECK_GT(expr1, expr2) DCHECK_OP(expr1, >, expr2)

