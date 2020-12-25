#include "Grammar_t.h"
#include <iostream>
#include <cstring>

#define BUFFER_SIZE 1000

Grammar_t::Grammar_t(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    int countOfRules = 0;
    fscanf(file, "%d", &countOfRules);
    for (int i = 0; i < countOfRules; ++i) {
        std::string rule;
        char buffer[BUFFER_SIZE];
        fscanf(file, "%s", buffer);
        rule = buffer;
        addRule(rule);
    }
    fscanf(file, "%c", &_startNotTerminal);
    fscanf(file, "%c", &_startNotTerminal);
    fclose(file);
}

void Grammar_t::addRule(const std::string& rule) {
    char from = rule[0];
    std::string to = "";
    for (size_t i = 3; i < rule.size(); ++i) {
        if (rule[i] == '|') {
            addRule(Rule_t(from, to));
            to = "";
        } else {
            if (rule[i] != EPSILON) {
                to += rule[i];
            }
        }
    }
    addRule(Rule_t(from ,to));
}

void Grammar_t::addRule(const Rule_t& rule) {
    _rules[rule.from()].emplace_back(rule);
}

char Grammar_t::startNotTerminal() const {
    return _startNotTerminal;
}

std::vector<Grammar_t::Rule_t> Grammar_t::getRules(char sym) {
    return _rules[sym];
}

bool Grammar_t::Rule_t::operator==(const Rule_t& r) const {
    return r._from == _from && r._to == _to;
}

char Grammar_t::Rule_t::from() const {
    return _from;
}

std::string Grammar_t::Rule_t::to() const {
    return _to;
}
