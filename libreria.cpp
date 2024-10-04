#include <iostream>
#include <string>
#include <vector>

using namespace std;

// verificare inoltre le funzionalità del codice e le specifiche del codice ISBN
#define DIMENSIONE_ISBN 13 // dimensione fissata per la lunghezza del codice ISBN, aiuterà in caso di modifiche future

int ISBN_corretto(string codice) {
    int i = 0;

    // iter direttamente nel ciclo for e nella fase di verifica controlla se l'indice è ancora dentro gli estremi di "codice" 
    // e verifica che ogni carattere sia una cifra compresa tra 0 e 9, estremi inclusi
    for (; i < codice.size() && codice[i] >= '0' && codice[i] <= '9'; i++);

    // ritorna 1 se ISBN corretto altrimenti 0
    if (i == codice.size())
        return 1;
    else {
        cout << "Uscito alla posizione (partendo da 1): " << ++i << " carattere che ha portato al fallimento: " << codice[i] << endl;
        return 0;
    }
}

// classe Libro
class Libro {
    public:
        string titolo;
        string autore;
        int anno_pubblicazione;
        string ISBN;
        float prezzo;

        Libro(string t, string a, int anno, string isbn, float prezzo) : titolo(t), autore(a), anno_pubblicazione(anno), ISBN(isbn), prezzo(prezzo) {}

        virtual void stampa_elemento() {
            cout << "\nDettaglio libro con codice ISBN: " << ISBN << endl;
            cout << "\tTitolo: " << titolo << "\n\tAutore: " << autore << "\n\tAnno pubblicazione: " << anno_pubblicazione << "\n\tPrezzo: " << prezzo << endl;
        }

        // restituisce il nome
        string getNome() {
            return titolo;
        }

        virtual ~Libro() {}
};

class EBook : public Libro {
    public:
        string formato;     // formato EBook
        float dimensioneMB; // dimensione in MB dell'ebook

        EBook(string t, string a, int anno, string isbn, float p, string formato, float dimensione) 
            : Libro(t, a, anno, isbn, p), formato(formato), dimensioneMB(dimensione) {}

        // override
        void stampa_elemento() override {
            cout << "\nDettaglio EBOOK con codice ISBN: " << ISBN << endl;
            cout << "\tTitolo: " << titolo << "\n\tAutore: " << autore << "\n\tAnno pubblicazione: " << anno_pubblicazione << "\n\tPrezzo: " << prezzo << "\n\tFormato: " << formato << "\n\tDimensione: " << dimensioneMB << " MB" << endl;
        }
};

/**
 * @brief Classe libreria, contiene le principali funzionalità tra cui:
 *             - visualizzazione del catalogo
 *             - dimensioni della libreria
 *             - aggiunta di un nuovo libro 
 *             - ricerca libro per ISBN
 *             - rimozione libro
 */
class Libreria {
    public:
        vector<Libro*> libreria;

        ~Libreria() {
            for (Libro* libro : libreria) {
                delete libro;
            }
        }

        int aggiungi_nuovo(Libro* libro) {   
            libreria.push_back(libro);    
            return 0;
        }

        void visualizza_catalogo() {
            if (libreria.size() == 0) {
                cout << "\nLa libreria risulta attualmente vuota\n" << endl;
            } else {
                for (Libro* l : libreria) {
                    l->stampa_elemento();
                }
            }
        }

        int dimensione() {
            return libreria.size();
        }

        void cerca_libro_titolo(string titolo) {
            for (Libro* l : libreria) {
                if (l->getNome() == titolo) {
                    l->stampa_elemento();
                    return;
                }
            }
            cout << "Libro non trovato all'interno della libreria" << endl;
        }

        void rimuovi(string isbn) {
            for (auto it = libreria.begin(); it != libreria.end(); ++it) {
                if ((*it)->ISBN == isbn) {
                    delete *it; // Dealloca la memoria
                    libreria.erase(it); // Rimuove l'elemento dal vettore
                    break;
                }
            }
        }
};

// verifica formato del prezzo
int prezzo_valido(float prezzo) {
    // TODO
    return 1;
}

// verifica se esistono altri nomi con uguali (nome, autore) oppure stesso ISBN
int presente(string nome, string autore, string ISBN) {
    // TODO
    return 0;
}

void modifica_info_con_ISBN(Libreria& libreria) {
    string isbn;
    bool trovato = false;
    int i, selezione;
    string titolo, autore;
    float prezzo;
    cout << "Inserire il codice ISBN: ";
    cin >> isbn;

    for (i = 0; i < libreria.libreria.size() && !trovato; i++) {
        if (isbn == libreria.libreria[i]->ISBN) {
            trovato = true;
        }
    }
    if (trovato) {
        cout << "Indicare cosa si vuole modificare: " << endl;
        cout << " 1. Titolo" << endl;
        cout << " 2. Autore" << endl;
        cout << " 3. Prezzo" << endl;
        cin >> selezione;

        switch (selezione) {
            case 1:
                cout << "Indicare il nuovo titolo: ";
                cin >> titolo;
                libreria.libreria[i - 1]->titolo = titolo;
                break;
            case 2:
                cout << "Indicare il nuovo autore: ";
                cin >> autore;
                libreria.libreria[i - 1]->autore = autore;
                break;
            case 3:
                cout << "Indicare il nuovo prezzo: ";
                cin >> prezzo;
                libreria.libreria[i - 1]->prezzo = prezzo;
                break;
            default:
                cout << "\nErrore nella selezione, ripetere l'operazione dall'inizio";
                break;
        }
    }
}

/**
 * @brief funzione dedicata alla rimozione del libro, scegliere se rimozione da fare per titolo + autore oppure in modo più corretto tramite codice isbn
 */
void rimuovi_libro(Libreria& l) {
    int selezione = 0, elimina = 0;
    string isbn;
    cout << "Indicare il codice ISBN del libro da rimuovere: ";
    cin >> isbn;

    if (!isbn.empty()) {
        cout << "Trovato libro con codice ISBN: " << isbn << " sei sicuro di voler rimuovere il libro dalla libreria? [1 = Si, 0 = No]: ";
        cin >> elimina;

        if (elimina == 1) {
            l.rimuovi(isbn);
        }
    }
}

int aggiungi_libro(Libreria& l) {
    string nome, autore, ISBN;
    int anno;
    float prezzo;

    cout << "Indicare il nome del libro: ";
    cin >> nome;

    cout << "Indicare l'autore del libro: ";
    cin >> autore;

    cout << "Indicare l'anno di pubblicazione: ";
    cin >> anno;

    cout << "Indicare il prezzo del libro da pubblicare: ";
    cin >> prezzo;

    cout << "Indicare codice ISBN (13 cifre): ";
    cin >> ISBN;

    /**  
     * Inserimento del nuovo libro all'interno della libreria se:
     *         ISBN corretto (stringa di 13 cifre)
     *         prezzo valido (float)
     *         il libro non è presente all'interno della libreria (stesso autore e stesso nome)
     */ 
    if (ISBN_corretto(ISBN) && prezzo_valido(prezzo) && !presente(nome, autore, ISBN)) {
        l.aggiungi_nuovo(new Libro(nome, autore, anno, ISBN, prezzo));
        cout << "Inserimento del nuovo libro nella libreria avvenuto correttamente" << endl;
    }
    return 0;
}


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
    l.aggiungi_nuovo(new Libro("Il Nome della Rosa", "Umberto Eco", 1980, "9788806174238", 12.99));
    l.aggiungi_nuovo(new Libro("1984", "George Orwell", 1949, "9780451524935", 9.99));
    l.aggiungi_nuovo(new Libro("Il Signore degli Anelli", "J.R.R. Tolkien", 1954, "9780261102385", 22.99));
    l.aggiungi_nuovo(new EBook("Il Signore degli Anelli", "J.R.R. Tolkien", 1954, "9780261102385", 12.99, "EPUB", 2.5));
    l.aggiungi_nuovo(new EBook("1984", "George Orwell", 1949, "9780451524935", 8.99, "PDF", 1.2));
    l.aggiungi_nuovo(new EBook("Il Codice Da Vinci", "Dan Brown", 2003, "9780307474278", 10.99, "MOBI", 3.0));
    l.aggiungi_nuovo(new EBook("Harry Potter e la Pietra Filosofale", "J.K. Rowling", 1997, "9780747532699", 9.99, "AZW", 2.8));
    l.aggiungi_nuovo(new EBook("Orgoglio e Pregiudizio", "Jane Austen", 1813, "9780141439518", 7.99, "PDF", 1.5));
}



void ciclo_menu(Libreria nuova_libreria){
    int scelta = 0;
    string titolo;

    cout<<"Dimensione attuale della libreria: "<<nuova_libreria.dimensione()<<endl;

    do{

        stampa_menu_principale();
        
        cin>>scelta;
        switch(scelta){
            case 1:  
                aggiungi_libro(nuova_libreria);
                break;
            case 2:
                modifica_info_con_ISBN(nuova_libreria);
                break;
            case 3: 
                rimuovi_libro(nuova_libreria);
                break;
            case 4: 
                if ( ! nuova_libreria.libreria.empty() ){
                cout<<"\nInserire il titolo del libro da cercare: ";
                cin>>titolo;
                nuova_libreria.cerca_libro_titolo(titolo);
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
 
}




int main(){
    
    Libreria nuova_libreria;
    
    popola_libreria(nuova_libreria);

    ciclo_menu(nuova_libreria);


    return 0;
}