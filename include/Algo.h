#ifndef _ALGO_H_
#define _ALGO_H_

#include "Grammar_t.h"
#include <string>
#include <vector>
#include <set>

struct Situation_t;

class Algo {
public:
    Algo() = default;

    Algo(const char* fileName);

    ~Algo() = default;

    bool predict(const std::string& word);

    void Scan(const std::string& word, int id);

    void Predict(int id);

    void Complete(int id);

private:
    void _init(const std::string& word);

    Situation_t _getFinalSituation() const;

private:
    std::vector<std::vector<Situation_t>> situations;
    Grammar_t _gram;
};

struct Situation_t {
public:
    Situation_t() = default;

    Situation_t(const Grammar_t::Rule_t& rule, int dotId, int index) : 
                _rule(rule), _dotId(dotId), _index(index) {}

    Situation_t(const Situation_t& other) : 
                _rule(other._rule), _dotId(other._dotId), _index(other._index) {}

    ~Situation_t() = default;

    bool operator==(const Situation_t& r) const;

    Situation_t move() const;

    bool isDotLast() const;

    bool isToNotTerminal() const;

    char getNext() const;

    Grammar_t::Rule_t getRule() const;

    int getIndex() const;

private:
    Grammar_t::Rule_t _rule;
    int _dotId;
    int _index;
};

#endif
