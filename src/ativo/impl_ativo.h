#ifndef IMPL_ATIVO_H
#define IMPL_ATIVO_H

#include "ativo.h"


Ativo::Ativo(int valor, int quant, int part) {
    this->valor_unitario    = valor;
    this->qtde              = quant;
    this->participacao      = part;

    // adiciona as restricoes que cada valor deve ter

    // os 3 inteiros devem ser positivos
    this->valor_unitario.positive();
    this->qtde.positive();
    this->participacao.positive();

    // verifica se as restricoes estao sendo seguidas
    if (!this->valor_unitario.validate()) 
        throw invalid_argument("this ativo->valor_unitario did not follow the constraints");
        
    if (!this->qtde.validate()) 
        throw invalid_argument("this ativo->qtde did not follow the constraints");

    if (!this->participacao.validate()) 
        throw invalid_argument("this ativo->participacao did not follow the constraints");
}

int Ativo::get_valor_unit() {
    return this->valor_unitario.get_value();
}

int Ativo::get_qtde() {
    return this->qtde.get_value();
}

int Ativo::get_part() {
    return this->participacao.get_value();
}

#endif // IMPL_ATIVO_H