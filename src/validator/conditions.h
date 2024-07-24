#ifndef VALIDADOR_CONDITIONS_H
#define VALIDADOR_CONDITIONS_H

#include <iostream>
#include <list>
#include <functional>

using namespace std;

template<typename T>
class Conditions {
    protected:
        T value;
        list<function<bool(T)>> conditions;
        bool valid = false;

    public:
        T get_value() {
            return value;
        }

        Conditions& operator=(T new_value) {
            this->valid = true;
            this->value = new_value;
            return *this;
        }

        virtual void clear() {
            this->conditions.clear();
        }

        virtual bool validate() {
            // caso nao tenha atribuido nenhum valor a value
            if (this->valid == false) return false;

            for (const auto& condition : conditions) {
                if (!condition(this->value)) {
                    // executar caso que de errado
                    return false;
                }
            }

            return true;
        }

};

#endif // VALIDADOR_CONDITIONS_H