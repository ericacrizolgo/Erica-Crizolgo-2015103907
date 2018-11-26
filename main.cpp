#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "dicionario.h"

using std::cin;
using std::cout;
using std::endl;
//using namespace std;

int main(int argc, char *argv[]){

    Dicionario la_vamos_nos;
    la_vamos_nos.Gerar_Dicionario(argc,argv);

    cout << "\t\tINDICE INVERTIDO" << endl;
    string entrada;
    int opt = -1;

    while(1){
        do{

            cout << "OPCOES:" << endl;
            cout << "1.CONSULTA" << endl;
            cout << "2.SAIR" << endl;
            cin >> opt;
            setbuf(stdin,NULL);
            cin.clear();


        }while(opt >= 2 && opt <= 1);

        switch(opt){
            case 1:
                cout << "INSIRA PALAVRA: ";
                setbuf(stdin,NULL);
                getline(cin,entrada);
                entrada = la_vamos_nos.Normalizar(entrada);
                la_vamos_nos.Consulta(entrada);
                cout << endl;
            break;

            case 2:
                return 0;
            break;
        }
    }
}
