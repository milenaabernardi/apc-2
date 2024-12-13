#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <windows.h> // usar o sleep
#include <cassert> // usar o assert
using namespace std;

struct Jogo {
    string nome;
    string plataforma;
    string genero;
    int ano;
    int popularidade;
    float nota;
};

void limparTela();
void cadastrarJogo(vector<Jogo>& jogos);
void buscarJogo(const vector<Jogo>& jogos);
void ordenarJogos(vector<Jogo>& jogos);
void listarJogos(const vector<Jogo>& jogos);
void relatorioPorDecada(const vector<Jogo>& jogos, int decadaAtual = 0);
void menu();
void pausar();

// função para limpar o terminal
void limparTela() {
    system("cls");
}

// função para deixar com aspecto de "delay"
void pausar() {
    Sleep(2000);
}

// função para verificar se a entrada é um número inteiro
bool einteiro(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// função para verificar se a entrada é um número float
bool efloat(const string& str) {
    bool ponto = false;
    for (char c : str) {
        if (c == '.' && !ponto) {
            ponto = true;
        } else if (!isdigit(c)) {
            return false;
        }
    }
    return ponto;
}

// função para ler um número inteiro com verificação
int lerinteiro() {
    string entrada;
    while (true) {
        getline(cin, entrada);
        if (einteiro(entrada)) {
            return stoi(entrada);
        } else {
            cout << "Entrada invalida. Por favor, digite um numero inteiro: ";
        }
    }
}

// função para ler um número float com verificação
float lerFloat() {
    string entrada;
    while (true) {
        getline(cin, entrada);
        try {
            float resultado = stof(entrada);
            if (resultado >= 0 && resultado <= 10) {
                return resultado;
            } else {
                cout << "Nota deve ser entre 0 e 10. Tente novamente: ";
            }
        } catch (const invalid_argument&) {
            cout << "Entrada invalida. Por favor, digite um numero valido entre 0 e 10: ";
        }
    }
}

// função para garantir que o ano tenha 4 dígitos e seja válido
int lerAno() {
    string entrada;
    while (true) {
        cout << "Ano de lancamento: ";
        getline(cin, entrada);
        
        if (entrada.length() == 4 && einteiro(entrada)) {
            int ano = stoi(entrada);
            if (ano >= 1900 && ano <= 2100) { 
                return ano;
            } else {
                cout << "Ano fora do intervalo permitido. Tente novamente.\n";
            }
        } else {
            cout << "Ano invalido. Deve ter 4 digitos. Tente novamente.\n";
        }
    }
}

int main() {
    vector<Jogo> jogos;

    int opcao;
    do {
        menu();
        cin >> opcao;
        cin.ignore();
        assert(opcao >= 0 && opcao <= 5);  // verificação para estar dentro do intervalo permitido

        switch (opcao) {
            case 1: cadastrarJogo(jogos); break;
            case 2: buscarJogo(jogos); break;
            case 3: ordenarJogos(jogos); break;
            case 4: listarJogos(jogos); break;
            case 5: relatorioPorDecada(jogos); break;
            case 0: 
                cout << "\nSaindo...\n";
                pausar();
                break;
            default: cout << "\nOpcao invalida.\n";
        }
    } while (opcao != 0);

    return 0;
}

void menu() {
    limparTela();
    cout << "\n";
    cout << "-----------------------------------------------------------";
    cout << "\n| Sistema de Gerenciamento de Acervo de Jogos Eletronicos |\n";
    cout << "-----------------------------------------------------------";
    cout << "\n";
    cout << "\n";
    cout << "1. Cadastrar Jogo\n";
    cout << "2. Buscar Jogo\n";
    cout << "3. Ordenar Jogos\n";
    cout << "4. Listar Jogos\n";
    cout << "5. Relatorio por Decada\n";
    cout << "0. Sair\n";
    cout << "Escolha uma opcao: ";
}

// cadastrar um jogo
void cadastrarJogo(vector<Jogo>& jogos) {
    limparTela();
    char opcao;
    do {
        cout << "Cadastro de jogos\n";
        Jogo jogo;
        cout << "\n";
        cout << "Nome do jogo: ";
        getline(cin, jogo.nome);
        cout << "Plataforma: ";
        getline(cin, jogo.plataforma);
        cout << "Genero: ";
        getline(cin, jogo.genero);

        jogo.ano = lerAno();

        cout << "Popularidade (0 a 10): ";
        jogo.popularidade = lerinteiro(); 

        while (jogo.popularidade < 0 || jogo.popularidade > 10) {
            cout << "Popularidade deve ser entre 0 e 10. Tente novamente: ";
            jogo.popularidade = lerinteiro();
        }

        cout << "Nota (0 a 10): ";
        jogo.nota = lerFloat(); 

        while (jogo.nota < 0 || jogo.nota > 10) {
            cout << "Nota deve ser entre 0 e 10. Tente novamente: ";
            jogo.nota = lerFloat();
        }

        jogos.push_back(jogo);
        cout << "\nJogo cadastrado com sucesso!\n";

        cout << "\nDeseja cadastrar outro jogo? (S/N): ";
        cin >> opcao;
        cin.ignore();
        opcao = toupper(opcao);
    } while (opcao == 'S');
}

// buscar jogos pelo nome ou ano de lancamento
void buscarJogo(const vector<Jogo>& jogos) {
    char opcao;
    do {
        cout << "\nBuscar por (1: Nome, 2: Ano): ";
        int opcaoBusca;
        cin >> opcaoBusca;
        cin.ignore();

        bool jogoEncontrado = false;

        if (opcaoBusca == 1) {
            string nome;
            cout << "\nNome do jogo: ";
            getline(cin, nome);
            for (const auto& jogo : jogos) {
                if (jogo.nome == nome) {
                    cout << "\nEncontrado: " << jogo.nome << ", " << jogo.plataforma << ", " << jogo.ano << "\n";
                    jogoEncontrado = true;
                    break;
                }
            }
        } else if (opcaoBusca == 2) {
            int ano;
            // Remover a mensagem "Ano de lançamento" aqui
            ano = lerAno(); 
            for (const auto& jogo : jogos) {
                if (jogo.ano == ano) {
                    cout << "\nEncontrado: " << jogo.nome << ", " << jogo.plataforma << ", " << jogo.ano << "\n";
                    jogoEncontrado = true; 
                }
            }
        }

        if (!jogoEncontrado) {
            cout << "\nJogo nao encontrado.\n";
        }

        cout << "\nDeseja voltar ao menu? (S): ";
        cin >> opcao;
        cin.ignore();
    } while (opcao == 'S');
}

// ordenação os jogos por criterio
void ordenarJogos(vector<Jogo>& jogos) {
    char opcao;
    do {
        cout << "\nOrdenar por (1: Nome, 2: Ano, 3: Popularidade, 4: Nota): ";
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
        } else if (criterio == 4) {
            sort(jogos.begin(), jogos.end(), [](const Jogo& a, const Jogo& b) {
                return a.nota > b.nota;
            });
        }

        // Exibir a lista de jogos ordenados
        cout << "\nJogos ordenados com sucesso!\n";
        for (const auto& jogo : jogos) {
            cout << "- " << jogo.nome << " (Ano: " << jogo.ano << ", Popularidade: " << jogo.popularidade << ", Nota: " << jogo.nota << ")\n";
        }

        cout << "\nDeseja voltar ao menu? (S): ";
        cin >> opcao;
        cin.ignore();
    } while (opcao == 'S');
}

// lista todos os jogos ou permite filtrar pela sua preferência
void listarJogos(const vector<Jogo>& jogos) {
    char opcao;
    do {
        cout << "\nListar por (1: Todos, 2: Nome, 3: Ano, 4: Popularidade, 5: Nota): ";
        int opcaoListar;
        cin >> opcaoListar;
        cin.ignore();

        if (opcaoListar == 1) {
            cout << "\nJogos cadastrados:\n";
            for (const auto& jogo : jogos) {
                cout << "- " << jogo.nome << " (" << jogo.ano << ", Popularidade: " << jogo.popularidade << ", Nota: " << jogo.nota << ")\n";
            }
        } else if (opcaoListar == 2) {
            cout << "\nJogos por nome:\n";
            vector<Jogo> ordenados = jogos;
            sort(ordenados.begin(), ordenados.end(), [](const Jogo& a, const Jogo& b) {
                return a.nome < b.nome;
            });
            for (const auto& jogo : ordenados) {
                cout << "- " << jogo.nome << " (" << jogo.ano << ", Popularidade: " << jogo.popularidade << ", Nota: " << jogo.nota << ")\n";
            }
        } else if (opcaoListar == 3) {
            cout << "\nJogos por ano (mais recente para mais antigo):\n";
            vector<Jogo> ordenados = jogos;
            sort(ordenados.begin(), ordenados.end(), [](const Jogo& a, const Jogo& b) {
                return a.ano > b.ano;
            });
            for (const auto& jogo : ordenados) {
                cout << "- " << jogo.nome << " (" << jogo.ano << ", Popularidade: " << jogo.popularidade << ", Nota: " << jogo.nota << ")\n";
            }
        } else if (opcaoListar == 4) {
            cout << "\nJogos por popularidade (maior para menor):\n";
            vector<Jogo> ordenados = jogos;
            sort(ordenados.begin(), ordenados.end(), [](const Jogo& a, const Jogo& b) {
                return a.popularidade > b.popularidade;
            });
            for (const auto& jogo : ordenados) {
                cout << "- " << jogo.nome << " (Popularidade: " << jogo.popularidade << ", Ano: " << jogo.ano << ", Nota: " << jogo.nota << ")\n";
            }
        } else if (opcaoListar == 5) {
            cout << "\nJogos por nota (maior para menor):\n";
            vector<Jogo> ordenados = jogos;
            sort(ordenados.begin(), ordenados.end(), [](const Jogo& a, const Jogo& b) {
                return a.nota > b.nota;
            });
            for (const auto& jogo : ordenados) {
                cout << "- " << jogo.nome << " (Nota: " << jogo.nota << ", Ano: " << jogo.ano << ", Popularidade: " << jogo.popularidade << ")\n";
            }
        } else {
            cout << "\nOpcao invalida.\n";
        }

        cout << "\nDeseja voltar ao menu? (S): ";
        cin >> opcao;
        cin.ignore();
    } while (opcao == 'S');
}

// gera um relatório recursivo por década
void relatorioPorDecada(const vector<Jogo>& jogos, int decadaAtual) {
    char opcao;
    do {
        if (decadaAtual == 0) {
            int menorAno = jogos.empty() ? 0 : jogos[0].ano;
            for (const auto& jogo : jogos) {
                if (jogo.ano < menorAno) menorAno = jogo.ano;
            }
            relatorioPorDecada(jogos, (menorAno / 10) * 10);
            return;
        }

        vector<Jogo> daDecada;
        for (const auto& jogo : jogos) {
            if (jogo.ano >= decadaAtual && jogo.ano < decadaAtual + 10) {
                daDecada.push_back(jogo);
            }
        }

        if (!daDecada.empty()) {
            cout << "\nJogos da decada de " << decadaAtual << ":\n";
            for (const auto& jogo : daDecada) {
                cout << "- " << jogo.nome << " (" << jogo.ano << ")\n";
            }
        }

        if (!daDecada.empty() || decadaAtual < 2020) {
            relatorioPorDecada(jogos, decadaAtual + 10);
        }

        cout << "\nDeseja voltar ao menu? (S): ";
        cin >> opcao;
        cin.ignore();
    } while (opcao == 'S');
}
