#ifndef ATIVO_H
#define ATIVO_H

class Ativo {
    public:
        Ativo(int valor, int quant, int part);

        int get_valor_unit();
        int get_qtde();
        int get_part();

    private:
        // valor correspondente a menor parte de um ativo, em centavos
        int valor_unitario;
        
        // corresponde a quantidade do ativo, ou seja, quantas menores partes sao.
        int qtde;

        // percentual ideal para a carteira
        int participacao;
};

#include "impl_ativo.h"

#endif // ATIVO_H