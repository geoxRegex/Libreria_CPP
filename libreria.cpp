#include <iostream>
#include <string>
#include <vector>


using namespace std;



// verificare inoltre le funzionalità del codice e le specifiche del codice ISBN
#define DIMENSIONE_ISBN 13 // dimensione fissata per la lunghezza del codice ISBN, aiuterà in caso di modifiche future

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



/**
 * @brief necessari i controlli su tutto quello che viene inserito e fatto
 * ISBN formato da 13 cifre, nessun carattere alfabetico ed è necessario che sia univoco
 */
class Libro{
    public:
        string titolo;
        string autore;
        int anno_pubblicazione;
        string ISBN;
        float prezzo;

        Libro(string t, string a, int anno, string isbn, float prezzo): titolo(t), autore(a), anno_pubblicazione(anno), ISBN(isbn), prezzo(prezzo){}
            

        // restituisce il nome
        string getNome(){
            return titolo;
        }


        void stampa(){
            cout<<"\nDettaglio libro con condice ISBN: "<< ISBN<< endl;
            cout<<"\tTitolo: "<< titolo << "\n\tAutore: "<< autore << "\n\tanno pubblicazione: "<< anno_pubblicazione<<"\n\tprezzo: "<< prezzo <<endl; 
        }


};

class Libreria{
    public:

        vector<Libro> libreria;

        int aggiungi_nuovo(Libro libro){   
            
            libreria.push_back(libro);    
            
            return 0;

        }

        void visualizza_catalogo(){

            if ( libreria.size() == 0 ){
                cout<<"\nLa libreria risulta attualmente vuota\n"<<endl;
            }
            else {
                for(Libro l : libreria){
                    l.stampa();
                }
            }
        }

        int dimensione(){
            return libreria.size();
        }

        // funzione dedicata alla ricerca di un libro nella libreria, stampa se viene trovato il libro altrimenti viene 
        // visualizzato un messaggio che indica che il libro non è presente all'interno della libreria
        void cerca_libro(string titolo){
            string s;
            int i;
            for (i=0; i < libreria.size(); i++ ){
                if  ( libreria[i].getNome() == titolo){
                    libreria[i].stampa();
                    break;
                }
            }
            cout<<"Libro non trovato all'interno della libreria"<<endl;
        }

        int rimuovi(string isbn){
            // TODO
            // funzione da implementare per rimuovere il libro tramite il codice ISBN

            return 0;
        }

    private: 
};


// verifica formato del prezzo
int prezzo_valido(float prezzo){

    // TODO
    return 1;
}


// verifica se esistono altri nomi con uguali (nome, autore) oppure stesso ISBN
int presente(string nome, string autore, string ISBN){
    // TODO
    
    return 0;
}


void modifica_info_con_ISBN(Libreria l){

}




string ricerca_titolo_autore(Libreria l){
    
    
    return "";
}
/**
 * @brief funzione dedicata alla rimozione del libro, scegliere se rimozione da fare per titolo + autore oppure in modo piu' corretto tramite codice isbn
 * 
 */
void rimuovi_libro(Libreria l){
    int scelta =0, elimina=0;
    string isbn="", titolo, autore;
    do{
    cout<<"Scegliere se rimuovere un libro tramite: "<<endl;
    cout<< "  1.Titolo e autore"<<endl;
    cout<< "  2.Codice ISBN"<<endl;
    cout<< "  3.Uscire dal menu' per la rimozione libri"<<endl;
    cin>>scelta;


    switch (scelta){
        case 1: 
            cout<<"Inserire titolo del libro da rimuovere: ";
            cin>>titolo;
            cout<<"Inserire autore del libro da rimuovere: ";
            cin>>autore;
            isbn = ricerca_titolo_autore(l);

            if( !isbn.empty() ){
                cout<<"Trovato libro con codice ISBN: "<<isbn<< " sei sicuro di voler rimuovere il libro dalla liberia? [1 = Si, 0= No ]: ";
                cin>> elimina;
                if(elimina){
                    l.rimuovi(isbn);
                }
            }
        default:
            cout<<"Selezione sbagliata"<<endl;
            break;
    }
    }while(scelta != 3);


    

}


int aggiungi_libro(Libreria l){
    string nome, autore, ISBN;
    int anno;
    float prezzo;

    cout<<"Indicare il nome del libro: ";
    cin>> nome;

    cout<<"Indicare l'autore del libro: ";
    cin>> autore;


    cout<<"Indicare l'anno di pubblicazione: ";
    cin>> anno;

    cout<<"Indicare il prezzo del libro da pubblicare: ";
    cin>>prezzo;



    cout<<"Indicare codice ISBN (13 cifre): ";
    cin>>ISBN;


    /**  effettuo un controllo su tutto ovvero:
     *      isbn: codice deve essere lungo 13 cifre
     *      prezzo valido: float quindi numero reale con la virgola (punto nella notazione usata)
     *      univocita': non devono esserci altri libri con stesso (titolo, autore) oppure (ISBN) 
     * 
     */
    


    /**  
     * Inserimento del nuovo libro all'interno della libreria se:
     *         ISBN corretto (vedi regole)
     *         prezzo valido (float)
     *         il libro non è presente all'interno della liberia (stesso autore e stesso nome)
     */ 
    if(ISBN_corretto(ISBN) && prezzo_valido(prezzo) && !presente(nome, autore, ISBN) ){
        
        l.aggiungi_nuovo(Libro(nome, autore, anno, ISBN, prezzo));
        
        cout<<"Inserimento del nuovo libro nella libreria avvenuto correttamente"<<endl;
        

    }   

    return 0;
};


// funzione dedicata alla stampa del menu principale
void stampa_menu_principale(){

    cout<<"\nMenu' iniziale, scegliere l'operazione e inserire il valore corrispondente:"<<endl;
    cout<<"  1.Accesso menu per inserire un libro nella libreria"<<endl;
    cout<<"  2.Modifica le informazioni di un libro dato il codicd ISBN"<<endl;
    cout<<"  3.Rimuovere un libro dal catalogo"<<endl;
    cout<<"  4.Visualizzare le informazioni di un libro"<<endl;
    cout<<"  5.Visualizzre i dettagli di tutti i libri"<<endl;
    cout<<"  6. Chiudere il programma"<<endl;
    cout<<"\n\tScelta:  ";
}

// passaggio di 
void popola_libreria(Libreria &l){
    l.aggiungi_nuovo(Libro("Il Nome della Rosa", "Umberto Eco", 1980, "978-8806174238", 12.99));
    l.libreria.emplace_back(Libro("1984", "George Orwell", 1949, "978-0451524935", 9.99));
    l.libreria.emplace_back(Libro("Il Signore degli Anelli", "J.R.R. Tolkien", 1954, "978-0261102385", 22.99));
}



int main(){
    int scelta = 0;
    Libreria nuova_libreria;
    string titolo;
    /**
     * @brief variabile scelta, necessaria per poter leggere da std input un intero per poter effettuare le operazioni con l'utente
     * 
     */


    popola_libreria(nuova_libreria);


    cout<<"Dimensione attuale della libreria: "<<nuova_libreria.dimensione()<<endl;
    do{

        stampa_menu_principale();
        
        cin>>scelta;
        switch(scelta){
            case 1:  
                aggiungi_libro(nuova_libreria);
                break;
            case 2:
                // possibile mettere la condizione in un if per stampare a video una conferma della modifica del libro o se errore indicare l'errore 
                // modifica_isbn(nuova); // aggiungere la funzione che deve modificare il dato all'interno della libreria
                break;
            case 3: 
                rimuovi_libro(nuova_libreria);
                break;
            case 4: 
                if ( ! nuova_libreria.libreria.empty() ){
                cout<<"\nInserire il titolo del libro da cercare: ";
                cin>>titolo;
                nuova_libreria.cerca_libro(titolo);
                }else {
                    cout<<"\nLa libreria risulta essere vuota\n"<<endl;
                }
                break;
            case 5: 
                nuova_libreria.visualizza_catalogo();
                break;
            case 6:
                cout<<"\nSpegnimento del programma...\n"<<endl;
                break;
            default:
                continue;
        }
    }while(scelta!=6);
    
    

    return 0;
}