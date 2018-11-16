#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "dicionario.h"


using namespace std;

int main(){
    Dicionario la_vamos_nos;
    la_vamos_nos.Abrir("kinglear.txt");
    la_vamos_nos.Imprimir();
}
