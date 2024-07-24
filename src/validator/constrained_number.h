#ifndef VALIDATOR_CONSTRAINED_NUMBER_H
#define VALIDATOR_CONSTRAINED_NUMBER_H

#include "conditions.h"

class Constrained_number : public Conditions<int> {
public:
    using Conditions::operator=;
    Constrained_number() : Conditions<int>() {}

    void positive() {
        this->conditions.push_back([](int n) { return n > 0; });
    }

    void non_negative() {
        this->conditions.push_back([](int n) { return n >= 0; });
    }
};

#endif // VALIDATOR_CONSTRAINED_NUMBER_H