#include "dicionario.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

//using namespace std;
using std::ios;
using std::cout;
using std::cin;
using std::endl;

//Construtor da Classe, inicia com quantidade 0 arquivos
Dicionario::Dicionario(){
    num_arquivos = 0;
};

//Compara as palavras
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
    //Se a palavra for igual, o metodo compare retorna i
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

//Verifica se o caractere é valido
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

//Retorna o caractere minusculo
char Dicionario::Transforma_Caractere(char c){
    char novo;
    if(c >= 'A' && c <= 'Z'){
        novo = c + ('a' - 'A');
        return novo;
    }
    return c;
}

//Utilizada para abrir os arquivos
void Dicionario::Abrir(char *arquivo){

    //Abrindo arquivo
    arquivo_atual.open(arquivo, ios::in);
    arq_atual = arquivo;
    if(!arquivo_atual){
        throw 1; // tratamento de exceção
    }
};

//Fecha o arquivo
void Dicionario::Fechar(){
    arquivo_atual.close();

}

//Insere uma palava que não existe no Dicionario
void Dicionario::Insere(Palavra nova){
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
}

void Dicionario::Leitura(){
    string linha;

    //Declarando nova palavra e inserindo o arquivo no qual ela está presente
    Palavra nova;

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

//Recebe uma linha e quebra em palavras
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
        //Normaliza a palavra
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

//Imprime a lista de arquivos que contem a palavra pesquisada
void Dicionario::Imprimir(int indice){

    for(int j = 0; j < (int)dicionario_[indice].lista_arquivos.size(); j++){
        cout << dicionario_[indice].lista_arquivos[j] << endl;
    }
    cout << endl;
}

//Gera um novo Dicionario e realiza o tratamento de exceção
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

//Busca uma palavra no Dicionário
void Dicionario::Consulta(string entrada){
    Palavra aux;
    aux.palavra = entrada;
    int indice = Busca(aux);

    if(indice == -1){
        cout << endl << "PALAVRA NAO ESTA PRESENTE NO DICIONARIO." << endl;
    }else{
        Imprimir(indice);
    }
}
