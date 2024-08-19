#include <iostream>
using namespace std;

int n1, n2, resultado;
char operacao;

void soma();
void subtracao();
void multiplicacao();
void divisao();

void soma(){
    operacao == '+';
    resultado = n1+n2;
    cout << resultado;
}

void subtracao(){
    operacao == '-';
    resultado = n1-n2;
    cout << resultado;
}

void multiplicacao(){
    operacao == '*';
    resultado = n1*n2;
    cout << resultado;
}

void divisao(){
    operacao == '/';
    resultado = n1/n2;
    cout << resultado;
}

int main (){
    cout << "escolha a operacao desejada: " << endl;
    cin >> operacao;
    cout << "digite os numeros desejados para a operacao: " << endl;
    cin >> n1 >> n2;

    if (operacao=='+'){
    soma();
    }
    else if (operacao=='-'){
    subtracao();
    }
    else if (operacao=='*'){
    multiplicacao();
    }
    else if (operacao=='/'){
    divisao();
    }
}