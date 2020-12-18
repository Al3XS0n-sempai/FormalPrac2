#ifndef _RULE_T_H_
#define _RULE_T_H_

#include <string>
#include <vector>
#include "Symbol_t.h"

struct Rule_t {
public:
    Rule_t() = default;

    Rule_t(char from, const std::string& to);

    ~Rule_t() = default;

public:
    Symbol_t _from;
    std::vector<Symbol_t> _to;
};

#endif
