#include <iostream>

int lerInteiro(const char* mensagem) {
    int numero;
    while (true) {
        std::cout << mensagem;
        if (std::cin >> numero) {
            std::cin.ignore(10000, '\n');
            return numero;
        }
        if (std::cin.eof()) return 0;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Digite um numero inteiro valido.\n";
    }
}

class ListaDupla {
    struct No {
        char nome[100];
        int idade;
        No* anterior;
        No* proximo;
        No(const char* n, int i) : idade(i), anterior(nullptr), proximo(nullptr) {
            int j = 0;
            while (n[j] != '\0' && j < 99) {
                nome[j] = n[j];
                ++j;
            }
            nome[j] = '\0';
        }
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

    void inserirInicio(const char* nome, int idade) {
        No* novo = new No(nome, idade);
        novo->proximo = inicio;
        if (inicio) inicio->anterior = novo;
        else fim = novo;
        inicio = novo;
    }

    void inserirFim(const char* nome, int idade) {
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

void lerNome(char nome[100]) {
    while (true) {
        std::cout << "Nome do aluno: ";
        std::cin.getline(nome, 100);
        if (!std::cin) {
            if (std::cin.eof()) { nome[0] = '\0'; return; }
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Nome muito longo (maximo 99 caracteres).\n";
            continue;
        }
        bool preenchido = false;
        for (int i = 0; nome[i] != '\0'; ++i)
            if (nome[i] != ' ' && nome[i] != '\t') preenchido = true;
        if (preenchido) return;
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
                char nome[100];
                lerNome(nome);
                if (!std::cin && std::cin.eof()) return 0;
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
