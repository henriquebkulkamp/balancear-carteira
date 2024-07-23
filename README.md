# Balanceador De Carteira
Este script ajuda a alocar um aporte financeiro em uma carteira de ativos, sugerindo a quantidade e valor a ser investido em cada ativo para atingir ou manter a alocação percentual desejada.

### Funcionalidades:
- Insere informações de N ativos (percentual desejado da carteira, valor unitário de um ativo e quantidade de ativos possuidos).
- Calcula e sugere quanto investir em cada ativo com base em um aporte fornecido.
- Mantém ou ajusta a alocação percentual desejada da carteira.

### Requisitos
- Linguagem de programação: C++
- Compilador C++ (g++, ou outros)

### Instalação
- Clone o repositório:
```
git clone https://github.com/seuusuario/seurepositorio.git
```
- Navegue até o diretório do projeto:
```
cd seurepositorio
```

### Uso
- Compile o script:
```
g++ -o alocacao_investimentos script.cpp
```
- Execute o script:
```
./alocacao_investimentos
```

### Exemplos de Entrada
- Insira a quantidade de ativos diferentes.
- Para cada ativo, forneça:
    - Percentual ideal do ativo na carteira
    - Valor equivalene a um ativo
    - Quantidades de ativos possuidos
- Insita o valor do aporte

### Exemplo de Uso
```
Número de ativos: 3
Ativo 1: 50%, valor unitário: 100, quantidade atual: 10
Ativo 2: 30%, valor unitário: 50, quantidade atual: 20
Ativo 3: 20%, valor unitário: 150, quantidade atual: 5
Aporte: 1000
```

### Saída sugerida:
```
Invista 500 em Ativo 1, 300 em Ativo 2, 200 em Ativo 3.
```

### Detalhes do Funcionamento
Veja [DETALHES.md](DETALHES.md) para uma descrição aprofundada dos algoritmos implementados e das decisões de design.

### Contribuição
- Fork o projeto.
- Crie uma branch para sua feature (git checkout -b feature/nome-da-feature).
- Commit suas mudanças (git commit -am 'Adicionei uma nova feature').
- Push para a branch (git push origin feature/nome-da-feature).
- Crie um novo Pull Request.

### Licença
Este projeto está licenciado sob a Licença MIT - veja o arquivo [LICENSE](LICENSE) para mais detalhes.

O arquivo 'catch.hpp' incluido no repositório está liscenciado sob a Boost Software Liscense 1.0. Veja o arquivo [LICENSE_1_0.txt](LICENSE_1_0.txt) para mais detalhes.

### Autor
Henrique Bloemer Kulkamp (https://github.com/henriquebkulkamp/)
