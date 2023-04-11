#include "Algo.h"
#include <iostream>

#define DBG(x) std::cout<<#x<<' '<<x<<std::endl

Algo::Algo(const char* fileName) {
    _gram = Grammar_t(fileName);
}

bool Algo::predict(const std::string& word) {
    situations.clear();
    situations.resize(word.size() + 1);
    situations[0].emplace_back(
        Grammar_t::Rule_t('$', std::string(1, _gram.startNotTerminal())),
        0,
        0
    );
    Grammar_t::Rule_t rulee('$', std::string(1, _gram.startNotTerminal()));

    _init(word);
    Situation_t finalSituation = Situation_t(
        Grammar_t::Rule_t('$', std::string(1, _gram.startNotTerminal())),
        1,
        0
    );

    for (const auto& st : situations[word.size()]) {
        if (finalSituation == st) {
            return true;
        }
    }
    return false;
}

void Algo::Scan(const std::string& word, int id) {
    if (id == 0) {
        return;
    }
    for (const auto& situation : situations[id - 1]) {
        if (situation.isToNotTerminal() || situation.isDotLast()) {
            continue;
        }
        if (word[id - 1] == situation.getNext()) {
            bool ok = true;
            for (const auto& sit : situations[id]) {
                if (sit == situation.move()) {
                    ok = false;
                }
            }
            if (ok) {
                situations[id].emplace_back(situation.move());
            }
        }
    }
}

void Algo::Complete(int id) {
    std::vector<Situation_t> st(situations[id]);
    for (const auto& situation : st) {
        if (situation.isDotLast()) {
            for (const auto& prev : situations[situation.getIndex()]) {
                if (prev.isToNotTerminal() && prev.getNext() == situation.getRule().from()) {
                    bool ok = true;
                    for (const auto& sit : situations[id]) {
                        if (sit == prev.move()) {
                            ok = false;
                        }
                    }
                    if (ok) {
                        situations[id].emplace_back(prev.move());
                    }
                }
            }
        }
    }
}

void Algo::Predict(int id) {
    std::vector<Situation_t> st(situations[id]);
    for (const auto& situation : st) {
        if (situation.isToNotTerminal()) {
            for (const auto& rule : _gram.getRules(situation.getNext())) {
                bool ok = true;
                for (const auto& sit : situations[id]) {
                    if (sit == Situation_t(rule, 0, id)) {
                        ok = false;
                    }
                }
                if (ok) {
                    situations[id].emplace_back(Situation_t(rule, 0, id));
                }
            }
        }
    }
}

void Algo::_init(const std::string& word) {
    for (size_t i = 0; i < word.size() + 1; ++i) {
        Scan(word, i);
        int len = situations[i].size();
        // std::cout << i << ' ' << len << std::endl;

        while (true) {
            Complete(i);
            Predict(i);

            if (len == situations[i].size()) {
                break;
            } else {
                len = situations[i].size();
            }
        }
    }
}

Grammar_t::Rule_t Situation_t::getRule() const {
    return _rule;
}

int Situation_t::getIndex() const { 
    return _index; 
}

Situation_t Situation_t::move() const { 
    return Situation_t(_rule, _dotId + 1, _index); 
}

bool Situation_t::operator==(const Situation_t& r) const {
    return r._rule == _rule && r._index == _index && r._dotId == _dotId;
}

bool Situation_t::isDotLast() const {
    return _dotId == _rule.to().size();
}

bool Situation_t::isToNotTerminal() const {
    return !isDotLast() && Grammar_t::isNotTerminal(_rule.to()[_dotId]);
}

char Situation_t::getNext() const {
    return _rule.to()[_dotId];
}
