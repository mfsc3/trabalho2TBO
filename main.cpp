#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

vector<int> failure_function(const string &padrao);

vector<int> kmp(const vector<char> &texto, const string &padrao);

int main(){

    vector<char> texto = {'a', 'b', 'c', 'a', 'c', 'd', 'a', 'b', 'c', 'd', 'a', 'b', 'c', 'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd', 'b', 'c', 'a'};

    string padrao = {'a', 'b', 'c', 'd'};

    vector<int> resultado = kmp(texto, padrao);

    for(int i = 0; i < resultado.size(); i++){
        cout << resultado[i] << "\n";
    }

    return 0;
}

/*
a b c d 

a b a b c d 
0 0 
i   j

a r a r a q u a r a 
0 0 1 2 3 0
0 1 2 3 4 5 6 7 8 9
      i   j

aux = 1
i = 3
j = 5
*/

vector<int> failure_function(const string &padrao){
    int i = 0, j = 0;

    vector<int> aux(padrao.size(), 0);

    aux[i] = 0;

    for(j = 1; j < padrao.size(); j++){
        if(padrao[j] == padrao[i]){
            aux[j] = ++i;
        }
        else{
            if(i != 0){
                i = aux[i - 1];
                j--;
            }
            else{
                aux[j] = 0; 
            }
        }
    }

    return aux;
}

vector<int> kmp(const vector<char> &texto, const string &padrao){
    int indice_padrao = 0;
    int i = 0;
    vector<int> vetor_falha = failure_function(padrao);
    vector<int> indices_ocorrencia;
    while(i < texto.size()){

        while(i < texto.size() && indice_padrao < padrao.size() && texto[i] == padrao[indice_padrao]){
            indice_padrao++;
            i++;
        }
        
        if(indice_padrao == padrao.size()){
            indices_ocorrencia.push_back(i - padrao.size());
            indice_padrao = vetor_falha[--indice_padrao]; 
        }
        else{
            if(indice_padrao > 0){
                indice_padrao = vetor_falha[--indice_padrao]; 
            }
            else{
                i++;
            }
        }
    }

    return indices_ocorrencia;
}