#include "dicionario.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

Dicionario::Dicionario(){
    num_arquivos = 0;
};

bool compara(Palavra a,Palavra b){
    if(a.palavra < b.palavra){
        return true;
    }else{
        return false;
    }
}

//Função realizar a busca linear no vetor de palavras
int Dicionario::Busca(Palavra nova){
  int i = 0;
  for(i = 0; i < contador_palavras; i++){
    //Se a palavra for igual, o metodo compare retorna 0
    if(!dicionario_[i].palavra.compare(nova.palavra)){
      return i;
    }
  }
  return -1;
}

//O metodo normalizar deixar as palavras dentro do padrão
string Dicionario::Normalizar(string palavra){
    string nova_palavra;
    nova_palavra.clear();

    for(int i = 0; i < (int) palavra.length(); i++){
        if(Verifica_Caractere(palavra[i])){
            nova_palavra.push_back(Transforma_Caractere(palavra[i]));
        }
    }
    return nova_palavra;
}

//verifica se o caractere é valido
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

//retorna o caractere minusculo
char Dicionario::Transforma_Caractere(char c){
    char novo;
    if(c >= 'A' && c <= 'Z'){
        novo = c + ('a' - 'A');
        return novo;
    }
    return c;
}

void Dicionario::Abrir(char *arquivo){

    //Abrindo arquivo
    arquivo_atual.open(arquivo, ios::in);
    arq_atual = arquivo;
    if(!arquivo_atual){
        throw 1;
    }
};

void Dicionario::Fechar(){
    arquivo_atual.close();

}

void Dicionario::Insere(Palavra nova){
    //if(Verifica_Palavra(palavra)){
        int indice = Busca(nova);
        if(indice == -1){
            nova.lista_arquivos.push_back(arq_atual);
            dicionario_.push_back(nova);
            contador_palavras++;
        }else{
            sort(dicionario_[indice].lista_arquivos.begin(),dicionario_[indice].lista_arquivos.end());
            if(!binary_search(dicionario_[indice].lista_arquivos.begin(),dicionario_[indice].lista_arquivos.end(), arq_atual)){
                dicionario_[indice].lista_arquivos.push_back(arq_atual);
            }
        }
    //}
}

void Dicionario::Leitura(){
    string linha;

    //Declarando nova palavra e inserindo o arquivo no qual ela está presente
    Palavra nova;
    //nova.lista_arquivos.push_back(arquivo);

    // Enquanto nao chega no fim do arquivo é feita a leitura e tratamento de linha por linha
    while(!arquivo_atual.eof()){
        Palavra nova;
        getline(arquivo_atual,linha);
        vector<string> colecao = Quebra_Em_Palavras(linha);

        for(int i = 0; i < (int)colecao.size(); i++){
            nova.palavra = colecao[i];
            Insere(nova);
        }
    }
}

vector<string> Dicionario::Quebra_Em_Palavras(string linha){
    int inicio = 0, fim = 0;
    vector<string> resultado;


    while(fim != (int)(linha.length() + 1)){
        string palavra;

        fim = linha.find_first_of(" ",inicio);
        if(fim == -1){
            fim = linha.length() + 1;
        }

        palavra = linha.substr(inicio,fim - inicio);
        palavra = Normalizar(palavra);

        resultado.push_back(palavra);

        inicio = fim+1;

    }

    return resultado;
}

bool Dicionario::Verifica_Palavra(string palavra){
    if(palavra.empty()){
        return false;
    }
    return true;
}

void Dicionario::Imprimir(int indice){
    //cout << dicionario_[indice].palavra << "\t";
    for(int j = 0; j < (int)dicionario_[indice].lista_arquivos.size(); j++){
        cout << dicionario_[indice].lista_arquivos[j] << endl;
    }
    cout << endl;
}

void Dicionario::Gerar_Dicionario(int quantidade_arquivos, char *argv[]){
    for(int i = 1; i < quantidade_arquivos; i++){
        try{
            Abrir(argv[i]);
        }catch(int arquivo_nao_existe){
            cout << "FALHA EM ABRIR ARQUIVO: " << argv[i] << endl;
            continue;
        }

        Leitura();
        Fechar();
    }
    sort(dicionario_.begin(),dicionario_.end(),compara);
}

void Dicionario::Consulta(string entrada){
    Palavra aux;
    aux.palavra = entrada;
    int indice = Busca(aux);

    if(indice == -1){
        cout << "PALAVRA NÂO ESTA PRESENTE NO DICIONARIO" << endl;
    }else{
        Imprimir(indice);
    }
}
