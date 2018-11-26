#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

//using namespace std;
using std::string;
using std::vector;
using std::ifstream;

typedef struct _Palavra{
    string palavra;
    vector<string> lista_arquivos;
    int contador_arquivos = 0;
} Palavra;


class Dicionario{
private:
    int num_arquivos;
    int contador_palavras = 0;
    string arq_atual;
    ifstream arquivo_atual;
    vector <Palavra> dicionario_;
public:
    Dicionario();
    void Abrir(char*);
    void Fechar();
    void Leitura();
    void Insere(Palavra);
    string Normalizar(string);
    vector<string> Quebra_Em_Palavras(string);
    int Busca(Palavra);
    bool Verifica_Caractere(char);
    char Transforma_Caractere(char);
    bool Verifica_Palavra(string);
    void Gerar_Dicionario(int, char *argv[]);
    void Imprimir(int);
    void Consulta(string);

};

