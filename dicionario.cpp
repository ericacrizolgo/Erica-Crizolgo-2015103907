#include "dicionario.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool compara(Palavra a,Palavra b){
    if(a.palavra < b.palavra){
        return true;
    }else{
        return false;
    }
}

Dicionario::Dicionario(){
    num_arquivos = 0;
};

string Dicionario::Normalizar(string palavra){
    string nova_palavra;
    nova_palavra.clear();

    for(int i = 0; i < palavra.length(); i++){
        if(Verifica_Caractere(palavra[i])){
            nova_palavra.push_back(Transforma_Caractere(palavra[i]));
        }
    }
    return nova_palavra;
}

bool Dicionario::Verifica_Caractere(char c){
    if(c >= 'a' && c <= 'z'){
        return true;
    }
    if(c >= 'A' && c <= 'Z'){
        return true;
    }
    if(c >= '0' && c <= '9'){
        return true;
    }
    return false;
}

char Dicionario::Transforma_Caractere(char c){
    char novo;
    if(c >= 'A' && c <= 'Z'){
        novo = c + ('a' - 'A');
        return novo;
    }
    return c;
}

void Dicionario::Abrir(char *arquivo){
    ifstream texto;
    texto.open(arquivo, ios::in);
    string linha;
    int i = 0;
    Palavra nova;
    nova.lista_arquivos.push_back(arquivo);
    while(!texto.eof()){
        getline(texto,linha);
        int inicio = 0, fim = 0;
        i++;
        string palavra;
        //cout << linha << endl;
        while(fim != (linha.length() + 1)){
            fim = linha.find_first_of(" ",inicio);
            if(fim == -1){
                fim = linha.length() + 1;
            }

            palavra = linha.substr(inicio,fim - inicio);
            palavra = Normalizar(palavra);
            nova.palavra = palavra;

            inicio = fim+1;



            if(Verifica_Palavra(palavra)){

                if(binary_search(dicionario_.begin(),dicionario_.end(),nova,compara)){
                    //cout << "achouuu" << endl;
                }else{
                    dicionario_.push_back(nova);
                    contador_palavras++;
                    sort(dicionario_.begin(), dicionario_.end(),compara);
                }
                //cout << palavra << endl;
            }
        }

    }

    texto.close();
};

bool Dicionario::Verifica_Palavra(string palavra){
    if(palavra.empty()){
        return false;
    }
    return true;
}

void Dicionario::Imprimir(){
    for(int i = 0; i < contador_palavras; i++){
        cout << dicionario_[i].palavra << endl;
    }
    cout << contador_palavras << endl;
}
