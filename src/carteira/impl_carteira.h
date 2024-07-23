#ifndef IMPL_CARTEIRA_H
#define IMPL_CARTEIRA_H

#include "carteira.h"

template<typename... Args>
Carteira::Carteira(int investimeno, Args... args) {
    this->montante          = investimeno;
    this->percentual_total  = 0;
    add_ativo(args...);
}

void Carteira::add_ativo(Ativo ativo) {
    // Ao adicionar um ativo, atualiza o dinheiro total investido, 
    // e tambem o somatorio das participacoes
    this->montante +=           ativo.get_valor_unit() * ativo.get_qtde();    
    this->percentual_total +=   ativo.get_part();
}

template<typename... Args>
void Carteira::add_ativo(Ativo ativo, Args... args) {
    // caso base
    add_ativo(ativo);
    // caso recursivo
    add_ativo(args...);
}

int Carteira::get_montante() {
    return this->montante;
}

int Carteira::get_all_part() {
    return this->percentual_total;
}

#endif // IMPL_CARTEIRA_H