#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/ativo/ativo.h"
#include "../src/carteira/carteira.h"
#include "../src/validator/constrained_number.h"

TEST_CASE("Teste de validator") {
    Constrained_number number_with_restrictions;
    number_with_restrictions.non_negative();
    number_with_restrictions = 5;
    REQUIRE(number_with_restrictions.validate() == true);

    number_with_restrictions = -1; // nao segue as restricoes
    REQUIRE(number_with_restrictions.validate() == false);

    number_with_restrictions.clear(); // nao tem mais restricoes
    REQUIRE(number_with_restrictions.validate() == true);

    Constrained_number number_without_value;
    number_without_value.positive();
    number_without_value.non_negative();

    REQUIRE(number_without_value.validate() == false);
}

TEST_CASE("Teste de instancia da classe Ativo") {
    try {
        Ativo ativo_falho(-1, 10, 15);
    } catch (const exception& e) {
        REQUIRE(typeid(e) == typeid(invalid_argument));
    }
    Ativo ativo1(100, 10, 5);
    Ativo ativo2(200, 20, 10);
    Ativo ativo3(1, 2, 3);

    // teste ativo1
    // valor_unitario: 100
    // qtde desse ativo: 10
    // valor investido: 100*10 = 1000
    // participacao ideal: 5
    REQUIRE(ativo1.get_valor_unit() == 100);
    REQUIRE(ativo1.get_qtde() == 10);
    REQUIRE(ativo1.get_part() == 5);

    // teste ativo2
    // valor_unitario: 200
    // qtde desse ativo: 20
    // valor investido: 200*20 = 4000
    // participacao ideal: 10
    REQUIRE(ativo2.get_valor_unit() == 200);
    REQUIRE(ativo2.get_qtde() == 20);
    REQUIRE(ativo2.get_part() == 10);

    // teste ativo3
    // valor_unitario: 1
    // qtde desse ativo: 2
    // valor investido: 1*2 = 2
    // participacao ideal: 3
    REQUIRE(ativo3.get_valor_unit() == 1);
    REQUIRE(ativo3.get_qtde() == 2);
    REQUIRE(ativo3.get_part() == 3);    

    SECTION("Teste de instancia da classe Carteira") {
        Carteira carteira1(0, ativo1, ativo2, ativo3);
        Carteira carteira2(10, ativo2, ativo3);

        REQUIRE(carteira1.get_all_part() == 18);
        REQUIRE(carteira2.get_all_part() == 13);

        REQUIRE(carteira1.get_montante() == 5002);
        REQUIRE(carteira2.get_montante() == 4012);

        // teste para dizer quanto investir em cada ativo
        
    }
}