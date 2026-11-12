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

class ListaSimples {
    struct No {
        int valor;
        No* proximo;
        explicit No(int v) : valor(v), proximo(nullptr) {}
    };
    No* inicio = nullptr;
    No* fim = nullptr;
    int quantidade = 0;

public:
    ListaSimples() = default;
    ListaSimples(const ListaSimples&) = delete;
    ListaSimples& operator=(const ListaSimples&) = delete;

    ~ListaSimples() {
        while (inicio) {
            No* antigo = inicio;
            inicio = inicio->proximo;
            delete antigo;
        }
    }

    void inserirInicio(int valor) {
        No* novo = new No(valor);
        novo->proximo = inicio;
        inicio = novo;
        if (!fim) fim = novo;
        ++quantidade;
    }

    void inserirFim(int valor) {
        No* novo = new No(valor);
        if (fim) fim->proximo = novo;
        else inicio = novo;
        fim = novo;
        ++quantidade;
    }

    void imprimir() const {
        if (!inicio) {
            std::cout << "Lista vazia.\n";
            return;
        }
        for (No* atual = inicio; atual; atual = atual->proximo) {
            std::cout << atual->valor;
            if (atual->proximo) std::cout << " -> ";
        }
        std::cout << " -> NULL\n";
    }

    int tamanho() const { return quantidade; }

    bool buscar(int valor) const {
        for (No* atual = inicio; atual; atual = atual->proximo)
            if (atual->valor == valor) return true;
        return false;
    }

    bool remover(int valor) {
        No* atual = inicio;
        No* anterior = nullptr;
        while (atual && atual->valor != valor) {
            anterior = atual;
            atual = atual->proximo;
        }
        if (!atual) return false;
        if (anterior) anterior->proximo = atual->proximo;
        else inicio = atual->proximo;
        if (fim == atual) fim = anterior;
        delete atual;
        --quantidade;
        return true;
    }
};

int main() {
    ListaSimples lista;
    while (true) {
        std::cout << "\n=== LISTA SIMPLESMENTE ENCADEADA ===\n"
                  << "1 - Inserir no inicio\n"
                  << "2 - Inserir no final\n"
                  << "3 - Imprimir lista\n"
                  << "4 - Consultar quantidade\n"
                  << "5 - Buscar valor\n"
                  << "6 - Remover valor\n"
                  << "0 - Sair\n";
        int opcao = lerInteiro("Opcao: ");
        if (opcao == 0) break;
        switch (opcao) {
            case 1: lista.inserirInicio(lerInteiro("Valor: ")); break;
            case 2: lista.inserirFim(lerInteiro("Valor: ")); break;
            case 3: lista.imprimir(); break;
            case 4: std::cout << "Quantidade: " << lista.tamanho() << "\n"; break;
            case 5: {
                int v = lerInteiro("Valor a buscar: ");
                std::cout << (lista.buscar(v) ? "Valor encontrado.\n" : "Valor nao encontrado.\n");
                break;
            }
            case 6: {
                int v = lerInteiro("Valor a remover: ");
                std::cout << (lista.remover(v) ? "Valor removido.\n" : "Valor nao encontrado.\n");
                break;
            }
            default: std::cout << "Opcao invalida.\n";
        }
    }
}
