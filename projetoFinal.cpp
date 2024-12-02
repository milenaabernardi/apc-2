#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

// Estruturas de dados
struct Jogo {
    string nome;
    string plataforma;
    int ano;
    int popularidade;
};

struct Desenvolvedor {
    string nome;
    vector<string> jogos;
};

// Prototipação
void cadastrarJogo(vector<Jogo>& jogos);
void registrarDesenvolvedor(map<string, Desenvolvedor>& desenvolvedores, vector<Jogo>& jogos);
void buscarJogo(const vector<Jogo>& jogos);
void ordenarJogos(vector<Jogo>& jogos);
void listarJogos(const vector<Jogo>& jogos);
void relatorioPorDecada(const vector<Jogo>& jogos, int decadaAtual = 0);
void menu();

// Funções principais
int main() {
    vector<Jogo> jogos;
    map<string, Desenvolvedor> desenvolvedores;

    int opcao;
    do {
        menu();
        cin >> opcao;
        cin.ignore();
        switch (opcao) {
            case 1: cadastrarJogo(jogos); break;
            case 2: registrarDesenvolvedor(desenvolvedores, jogos); break;
            case 3: buscarJogo(jogos); break;
            case 4: ordenarJogos(jogos); break;
            case 5: listarJogos(jogos); break;
            case 6: relatorioPorDecada(jogos); break;
            case 0: cout << "\nSaindo...\n"; break;
            default: cout << "\nOpção inválida.\n";
        }
    } while (opcao != 0);

    return 0;
}

// Exibe o menu
void menu() {
    cout << "\n--- Sistema de Gerenciamento de Acervo de Jogos Eletrônicos ---\n";
    cout << "1. Cadastrar Jogo\n";
    cout << "2. Registrar Desenvolvedor\n";
    cout << "3. Buscar Jogo\n";
    cout << "4. Ordenar Jogos\n";
    cout << "5. Listar Jogos\n";
    cout << "6. Relatório por Década\n";
    cout << "0. Sair\n";
    cout << "Escolha uma opção: ";
}

// Cadastra um jogo
void cadastrarJogo(vector<Jogo>& jogos) {
    cout << "\n";
    Jogo jogo;
    cout << "Nome do jogo: ";
    getline(cin, jogo.nome);
    cout << "Plataforma: ";
    getline(cin, jogo.plataforma);
    cout << "Ano de lançamento: ";
    cin >> jogo.ano;
    cout << "Popularidade (0 a 10): ";
    cin >> jogo.popularidade;

    // Validação da popularidade
    if (jogo.popularidade < 0) jogo.popularidade = 0;
    if (jogo.popularidade > 10) jogo.popularidade = 10;

    cin.ignore();
    jogos.push_back(jogo);
    cout << "\nJogo cadastrado com sucesso!\n";
}

// Registra um desenvolvedor e atribui jogos a ele
void registrarDesenvolvedor(map<string, Desenvolvedor>& desenvolvedores, vector<Jogo>& jogos) {
    cout << "\n";
    Desenvolvedor dev;
    cout << "Nome do desenvolvedor: ";
    getline(cin, dev.nome);
    string jogo;
    cout << "Digite o nome dos jogos desenvolvidos por ele (digite 'fim' para terminar):\n";
    while (true) {
        getline(cin, jogo);
        if (jogo == "fim") break;
        dev.jogos.push_back(jogo);
    }
    desenvolvedores[dev.nome] = dev;
    cout << "\nDesenvolvedor registrado com sucesso!\n";
}

// Busca jogos pelo nome ou ano de lançamento
void buscarJogo(const vector<Jogo>& jogos) {
    cout << "\nBuscar por (1: Nome, 2: Ano): ";
    int opcao;
    cin >> opcao;
    cin.ignore();

    if (opcao == 1) {
        string nome;
        cout << "\nNome do jogo: ";
        getline(cin, nome);
        for (const auto& jogo : jogos) {
            if (jogo.nome == nome) {
                cout << "\nEncontrado: " << jogo.nome << ", " << jogo.plataforma << ", " << jogo.ano << "\n";
                return;
            }
        }
    } else if (opcao == 2) {
        int ano;
        cout << "\nAno de lançamento: ";
        cin >> ano;
        for (const auto& jogo : jogos) {
            if (jogo.ano == ano) {
                cout << "\nEncontrado: " << jogo.nome << ", " << jogo.plataforma << ", " << jogo.ano << "\n";
            }
        }
    }
    cout << "\nJogo não encontrado.\n";
}

// Ordena os jogos por critério
void ordenarJogos(vector<Jogo>& jogos) {
    cout << "\nOrdenar por (1: Nome, 2: Ano, 3: Popularidade): ";
    int criterio;
    cin >> criterio;
    cin.ignore();

    if (criterio == 1) {
        sort(jogos.begin(), jogos.end(), [](const Jogo& a, const Jogo& b) {
            return a.nome < b.nome;
        });
    } else if (criterio == 2) {
        sort(jogos.begin(), jogos.end(), [](const Jogo& a, const Jogo& b) {
            return a.ano < b.ano;
        });
    } else if (criterio == 3) {
        sort(jogos.begin(), jogos.end(), [](const Jogo& a, const Jogo& b) {
            return a.popularidade > b.popularidade;
        });
    }
    cout << "\nJogos ordenados com sucesso!\n";
}

// Lista todos os jogos ou permite filtrar
void listarJogos(const vector<Jogo>& jogos) {
    cout << "\nListar por (1: Todos, 2: Nome, 3: Ano, 4: Popularidade): ";
    int opcao;
    cin >> opcao;
    cin.ignore();

    if (opcao == 1) {
        cout << "\nJogos cadastrados:\n";
        for (const auto& jogo : jogos) {
            cout << "- " << jogo.nome << " (" << jogo.ano << ", Popularidade: " << jogo.popularidade << ")\n";
        }
    } else if (opcao == 2) {
        // Ordenar por nome (crescente)
        cout << "\nJogos por ordem alfabética:\n";
        vector<Jogo> ordenados = jogos;
        sort(ordenados.begin(), ordenados.end(), [](const Jogo& a, const Jogo& b) {
            return a.nome < b.nome;
        });
        for (const auto& jogo : ordenados) {
            cout << "- " << jogo.nome << " (" << jogo.ano << ", Popularidade: " << jogo.popularidade << ")\n";
        }
    } else if (opcao == 3) {
        // Ordenar por ano (mais novo para o mais velho)
        cout << "\nJogos por ordem de lançamento (mais novo para o mais velho):\n";
        vector<Jogo> ordenados = jogos;
        sort(ordenados.begin(), ordenados.end(), [](const Jogo& a, const Jogo& b) {
            return a.ano > b.ano; // Ordem decrescente
        });
        for (const auto& jogo : ordenados) {
            cout << "- " << jogo.nome << " (" << jogo.ano << ", Popularidade: " << jogo.popularidade << ")\n";
        }
    } else if (opcao == 4) {
        // Ordenar por popularidade (maior para menor)
        cout << "\nJogos por popularidade (maior para menor):\n";
        vector<Jogo> ordenados = jogos;
        sort(ordenados.begin(), ordenados.end(), [](const Jogo& a, const Jogo& b) {
            return a.popularidade > b.popularidade; // Ordem decrescente
        });
        for (const auto& jogo : ordenados) {
            cout << "- " << jogo.nome << " (Popularidade: " << jogo.popularidade << ", Ano: " << jogo.ano << ")\n";
        }
    } else {
        cout << "\nOpção inválida.\n";
    }
}

// Gera um relatório recursivo por década
void relatorioPorDecada(const vector<Jogo>& jogos, int decadaAtual) {
    if (decadaAtual == 0) { // Primeira chamada: calcular a década inicial
        int menorAno = jogos.empty() ? 0 : jogos[0].ano;
        for (const auto& jogo : jogos) {
            if (jogo.ano < menorAno) menorAno = jogo.ano;
        }
        relatorioPorDecada(jogos, (menorAno / 10) * 10);
        return;
    }

    // Filtra os jogos da década atual
    vector<Jogo> daDecada;
    for (const auto& jogo : jogos) {
        if (jogo.ano >= decadaAtual && jogo.ano < decadaAtual + 10) {
            daDecada.push_back(jogo);
        }
    }

    // Exibe os jogos da década atual
    if (!daDecada.empty()) {
        cout << "\nJogos da década de " << decadaAtual << ":\n";
        for (const auto& jogo : daDecada) {
            cout << "- " << jogo.nome << " (" << jogo.ano << ")\n";
        }
    }

    // Próxima década
    if (!daDecada.empty() || decadaAtual < 2020) { // Terminar no futuro próximo
        relatorioPorDecada(jogos, decadaAtual + 10);
    }
}
