#ifndef ATIVO_H
#define ATIVO_H

#include "../validator/constrained_number.h"

class Ativo {
    public:
        Ativo(int valor, int quant, int part);

        int get_valor_unit();        
        int get_qtde();
        int get_part();

    private:
        // valor correspondente a menor parte de um ativo, em centavos
        Constrained_number valor_unitario;
        
        // corresponde a quantidade do ativo, ou seja, quantas menores partes sao.
        Constrained_number qtde;

        // percentual ideal para a carteira
        Constrained_number participacao;
};

#include "impl_ativo.h"

#endif // ATIVO_H