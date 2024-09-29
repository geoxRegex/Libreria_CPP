
#include <iostream>
#include <string>

using namespace std;

#define DIMENSIONE_ISBN 13

int ISBN_corretto(string codice){
    int i=0;


    // iter direttamente nel ciclo for e nella fase di verifica controlla se l'indice è ancora dentro gli estremi di "codice" 
    // e verfica che ogni carattere sia una cifra compresa tra 0 e 9, estremi inclusi
    for(; i<codice.size() && codice[i]>='0' && codice[i]<='9'; i++);
    

    // ritorna 1 se ISBN corretto altrimenti 0
    if(i==codice.size())
        return 1;
    else {
        cout<<"Uscito alla posizone(partendo da 1): "<<++i<<" carattere che ha portato al fallimento: "<<codice[i]<<endl;
        return 0;
    }

}

int main(){
    string codice;

    cout<<"Inserisci un codice ISBN di sole 13 cifre: ";
    cin>>codice;

    if(codice.size() == DIMENSIONE_ISBN && ISBN_corretto(codice))
        cout<<"Codice inserito: "<< codice << " risulta corretto";
    else  
        cout<<"Codice inserito: "<< codice << " errato!";
    
    
    return 0;
}