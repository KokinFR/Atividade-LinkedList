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

class ListaCircular {
    struct No {
        int valor;
        No* proximo;
        explicit No(int v) : valor(v), proximo(nullptr) {}
    };
    No* inicio = nullptr;
    No* fim = nullptr;
    int quantidade = 0;

public:
    ListaCircular() = default;
    ListaCircular(const ListaCircular&) = delete;
    ListaCircular& operator=(const ListaCircular&) = delete;

    ~ListaCircular() {
        if (!inicio) return;
        fim->proximo = nullptr; // rompe o ciclo antes de liberar os nos
        while (inicio) {
            No* antigo = inicio;
            inicio = inicio->proximo;
            delete antigo;
        }
    }

    void inserirInicio(int valor) {
        No* novo = new No(valor);
        if (!inicio) {
            inicio = fim = novo;
            novo->proximo = novo;
        } else {
            novo->proximo = inicio;
            inicio = novo;
            fim->proximo = inicio;
        }
        ++quantidade;
    }

    void inserirFim(int valor) {
        No* novo = new No(valor);
        if (!inicio) {
            inicio = fim = novo;
            novo->proximo = novo;
        } else {
            novo->proximo = inicio;
            fim->proximo = novo;
            fim = novo;
        }
        ++quantidade;
    }

    void imprimir() const {
        if (!inicio) {
            std::cout << "Lista vazia.\n";
            return;
        }
        No* atual = inicio;
        do {
            std::cout << atual->valor << " -> ";
            atual = atual->proximo;
        } while (atual != inicio);
        std::cout << "(volta ao inicio)\n";
    }

    int tamanho() const { return quantidade; }
};

int main() {
    ListaCircular lista;
    while (true) {
        std::cout << "\n=== LISTA SIMPLESMENTE ENCADEADA CIRCULAR ===\n"
                  << "1 - Inserir no inicio\n"
                  << "2 - Inserir no final\n"
                  << "3 - Imprimir lista\n"
                  << "4 - Consultar quantidade\n"
                  << "0 - Sair\n";
        int opcao = lerInteiro("Opcao: ");
        if (opcao == 0) break;
        switch (opcao) {
            case 1: lista.inserirInicio(lerInteiro("Valor: ")); break;
            case 2: lista.inserirFim(lerInteiro("Valor: ")); break;
            case 3: lista.imprimir(); break;
            case 4: std::cout << "Quantidade: " << lista.tamanho() << "\n"; break;
            default: std::cout << "Opcao invalida.\n";
        }
    }
}
