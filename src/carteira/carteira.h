#ifndef CARTEIRA_H
#define CARTEIRA_H

#include <list>
#include "../ativo/ativo.h"


class Carteira {
    public:
        /* 
            O(N)
            instancia uma carteira com um aporte e N ativos 
        */
        template<typename... Args>
        Carteira(int investimeno, Args... args);

        /* 
            O(1)
            adiciona um unico ativo, 
            e tambem é o caso base para uma insercao recursiva com N ativos
        */
        void add_ativo(Ativo ativo);

        /* 
            O(N)
            insere N ativos usando recursão
        */
        template<typename... Args>
        void add_ativo(Ativo ativo, Args... args);

        /*
            O(1)
            Retorna o somatorio dos investimentos + aporte/dinheiro em caixa
        */
        int get_montante();

        /*
            O(1)
            Retorna o somatorio de partes de acoes, exemplo:
            ativo1->participacao = 50
            ativo2->participacao = 30
            ativo3->participacao = 20

            get_all_part() retora 50+30+20 -> 100
        */
        int get_all_part();
    private:
        // tudo que foi investido + aporte, em centavos
        int montante;

        // tudo que foi investido, em centavos
        int aporte;

        // somatorio de partes de acoes
        int percentual_total;

        // lista dos diferentes ativos investidos
        std::list<Ativo> ativos;
};


#include "impl_carteira.h"

#endif // CARTEIRA_H