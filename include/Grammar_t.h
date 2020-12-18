#ifndef _GRAMMAR_T_H_
#define _GRAMMAR_T_H_

#include <string>
#include <vector>
#include <map>

class Grammar_t {
public:
    struct Rule_t;

public:
    Grammar_t() = default;

    Grammar_t(const char* fileName);

    ~Grammar_t() = default;

    void addRule(const std::string& rule);

    void addRule(const Rule_t& rule);

    std::vector<Rule_t> getRules(char sym);

    static bool isTerminal(char sym) { return 'a' <= sym && sym <= 'z' || '1' == sym; }

    static bool isNotTerminal(char sym) { return 'A' <= sym && sym <= 'Z'; }

    char startNotTerminal() const;

private:
    char _startNotTerminal;
    std::map<char, std::vector<Rule_t>> _rules;
};

struct Grammar_t::Rule_t {
public:
    Rule_t() = default;

    Rule_t(const Rule_t& otherRule) : _from(otherRule._from), _to(otherRule._to) {}

    Rule_t(char from, const std::string& to) : _from(from), _to(to) {}

    ~Rule_t() = default;

    bool operator==(const Rule_t& r) const;

    char from() const;

    std::string to() const;

private:
    char _from;
    std::string _to;
};

#endif
