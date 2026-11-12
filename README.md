# Atividade - Listas Encadeadas em C++

Implementacao de tres exercicios de Estrutura de Dados usando **ponteiros e alocacao dinamica**, sem `std::list` ou `std::vector` para representar as listas.

## Exercicios

| Arquivo | Estrutura | Operacoes |
| --- | --- | --- |
| `lista_simples.cpp` | Lista simplesmente encadeada de inteiros | Inserir no inicio e fim, imprimir, contar, buscar e remover por valor |
| `lista_dupla.cpp` | Lista duplamente encadeada de alunos | Cadastrar nome/idade no inicio e fim, remover no inicio e fim, listar |
| `lista_circular.cpp` | Lista simplesmente encadeada circular de inteiros | Inserir no inicio e fim, imprimir e contar |

Cada arquivo e um programa independente e possui um menu interativo.

## Compilar e executar

Requer um compilador C++17, como g++ (MinGW no Windows ou GCC no Linux).

```bash
g++ -std=c++17 -Wall -Wextra -pedantic lista_simples.cpp -o lista_simples
g++ -std=c++17 -Wall -Wextra -pedantic lista_dupla.cpp -o lista_dupla
g++ -std=c++17 -Wall -Wextra -pedantic lista_circular.cpp -o lista_circular
```

No Linux ou macOS:

```bash
./lista_simples
./lista_dupla
./lista_circular
```

No Windows (PowerShell):

```powershell
.\lista_simples.exe
.\lista_dupla.exe
.\lista_circular.exe
```

Execute cada programa separadamente. Os menus aceitam numeros inteiros validos e permitem sair com a opcao 0.

## Detalhes de implementacao

- **Lista simples:** cada no tem `valor` e `proximo`; a remocao elimina a primeira ocorrencia do valor informado.
- **Lista dupla:** cada no armazena `nome`, `idade`, `anterior` e `proximo`; os ponteiros `inicio` e `fim` sao atualizados nas insercoes e remocoes.
- **Lista circular:** o ultimo no sempre aponta ao primeiro (`fim->proximo == inicio`); o percurso da impressao para ao voltar ao inicio.
- As tres classes liberam os nos alocados ao terminar a execucao e tratam listas vazias e listas com um unico elemento.
