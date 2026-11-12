#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

int lerInteiro(const std::string& mensagem) {
    while (true) {
        std::cout << mensagem;
        std::string linha;
        if (!std::getline(std::cin, linha)) {
            std::cout << "\nEntrada encerrada.\n";
            std::exit(0);
        }
        std::istringstream entrada(linha);
        int numero;
        char extra;
        if ((entrada >> numero) && !(entrada >> extra)) return numero;
        std::cout << "Digite um numero inteiro valido.\n";
    }
}

class ListaDupla {
    struct No {
        std::string nome;
        int idade;
        No* anterior;
        No* proximo;
        No(const std::string& n, int i)
            : nome(n), idade(i), anterior(nullptr), proximo(nullptr) {}
    };
    No* inicio = nullptr;
    No* fim = nullptr;

public:
    ListaDupla() = default;
    ListaDupla(const ListaDupla&) = delete;
    ListaDupla& operator=(const ListaDupla&) = delete;

    ~ListaDupla() {
        while (inicio) {
            No* antigo = inicio;
            inicio = inicio->proximo;
            delete antigo;
        }
    }

    void inserirInicio(const std::string& nome, int idade) {
        No* novo = new No(nome, idade);
        novo->proximo = inicio;
        if (inicio) inicio->anterior = novo;
        else fim = novo;
        inicio = novo;
    }

    void inserirFim(const std::string& nome, int idade) {
        No* novo = new No(nome, idade);
        novo->anterior = fim;
        if (fim) fim->proximo = novo;
        else inicio = novo;
        fim = novo;
    }

    bool removerInicio() {
        if (!inicio) return false;
        No* antigo = inicio;
        inicio = inicio->proximo;
        if (inicio) inicio->anterior = nullptr;
        else fim = nullptr;
        delete antigo;
        return true;
    }

    bool removerFim() {
        if (!fim) return false;
        No* antigo = fim;
        fim = fim->anterior;
        if (fim) fim->proximo = nullptr;
        else inicio = nullptr;
        delete antigo;
        return true;
    }

    void imprimir() const {
        if (!inicio) {
            std::cout << "Nenhum aluno cadastrado.\n";
            return;
        }
        for (No* atual = inicio; atual; atual = atual->proximo)
            std::cout << "Nome: " << atual->nome << " | Idade: " << atual->idade << "\n";
    }
};

std::string lerNome() {
    while (true) {
        std::cout << "Nome do aluno: ";
        std::string nome;
        if (!std::getline(std::cin, nome)) std::exit(0);
        if (nome.find_first_not_of(" \t") != std::string::npos) return nome;
        std::cout << "O nome nao pode ficar vazio.\n";
    }
}

int lerIdade() {
    while (true) {
        int idade = lerInteiro("Idade: ");
        if (idade >= 0) return idade;
        std::cout << "A idade nao pode ser negativa.\n";
    }
}

int main() {
    ListaDupla lista;
    while (true) {
        std::cout << "\n=== LISTA DUPLAMENTE ENCADEADA (ALUNOS) ===\n"
                  << "1 - Inserir aluno no inicio\n"
                  << "2 - Inserir aluno no final\n"
                  << "3 - Remover aluno do inicio\n"
                  << "4 - Remover aluno do final\n"
                  << "5 - Listar alunos\n"
                  << "0 - Sair\n";
        int opcao = lerInteiro("Opcao: ");
        if (opcao == 0) break;
        switch (opcao) {
            case 1:
            case 2: {
                std::string nome = lerNome();
                int idade = lerIdade();
                if (opcao == 1) lista.inserirInicio(nome, idade);
                else lista.inserirFim(nome, idade);
                std::cout << "Aluno cadastrado.\n";
                break;
            }
            case 3:
                std::cout << (lista.removerInicio() ? "Primeiro aluno removido.\n" : "Lista vazia.\n");
                break;
            case 4:
                std::cout << (lista.removerFim() ? "Ultimo aluno removido.\n" : "Lista vazia.\n");
                break;
            case 5: lista.imprimir(); break;
            default: std::cout << "Opcao invalida.\n";
        }
    }
}
