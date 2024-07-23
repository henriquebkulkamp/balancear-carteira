#ifndef IMPL_ATIVO_H
#define IMPL_ATIVO_H

#include "ativo.h"


Ativo::Ativo(int valor, int quant, int part) {
    this->valor_unitario    = valor;
    this->qtde              = quant;
    this->participacao      = part;
}

int Ativo::get_valor_unit() {
    return this->valor_unitario;
}

int Ativo::get_qtde() {
    return this->qtde;
}

int Ativo::get_part() {
    return this->participacao;
}

#endif // IMPL_ATIVO_H