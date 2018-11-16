#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef struct _Palavra{
    string palavra;
    vector<string> lista_arquivos;
    int contador_arquivos = 0;

} Palavra;


class Dicionario{
private:
    int num_arquivos;
    int contador_palavras = 0;
    vector <string> arquivos;
    vector <Palavra> dicionario_;
public:
    Dicionario();
    void Abrir(char*);

    bool Verifica_Caractere(char);
    char Transforma_Caractere(char);
    bool Verifica_Palavra(string);
    string Normalizar(string);
    void Imprimir();
};
