#include <iostream>
#include <cstring>
using namespace std;
/// Clasa Librarie: permite adăgarea a mai multor cărți prin operatorul +=
class Carte {
private:
    char *Titlu;
    char *Autor;
    int An_aparitie;
public:
    Carte(const char *titlu_ , const char *autor_,  int an_aparitie); ///Constructor
    Carte();///Default Constructor
    Carte(const Carte &book1); ///Copy Constructor
    void SetTitlu(const char *titlu_); ///SETTER
    char *GetTitlu()const;///GETTER
    void SetAutor(const char *autor_);
    char *GetAutor()const;
    void SetAnaparitie( int an);
    int GetAnaparitie()const;
    void Citire();
    Carte& operator = (Carte const &book); ///Operator de atribuiere !CARTE&!
    friend bool  operator == (Carte const &book, Carte const &book2);///Operator de egalitate
    friend bool operator !=(Carte const &book, Carte const &book2);///Operator de diferenta
    friend istream& operator >> (istream& is, Carte  &book);///Citire
    friend ostream& operator<< (ostream& os,  Carte const &book);///Afisare
    ~Carte();///Destructor
};
class Librarie{
    int nr;///Pentru a stii cate elemente sunt in vector
    Carte **listaCarte = new Carte*[100];
public:
    Librarie(int nr_,Carte *listaCarte_[]){
        this->nr = nr_;
        for(int i = 0; i < nr_ ; i++){
            this->listaCarte[i] = listaCarte_[i];
        }
    }
    int GetNr(){
        return nr;
    }
    void SetNr(int nr_){
        nr = nr_;
    }
    void Afisare_lista(){
        for(int i = 0; i < nr; i++){
            cout<<*listaCarte[i];
        }
    }
    void Cautare();
    Librarie &operator+=(const Librarie &lib1){
        ///De intrebat
            unsigned int Nr_Carti = nr + lib1.nr;
            listaCarte = (Carte**) realloc(listaCarte, Nr_Carti * sizeof(Carte));
            int j = 0;
            for (int i = nr; i < Nr_Carti; i ++)
                listaCarte[i] = lib1.listaCarte[j ++];
            nr = Nr_Carti;
            return *this;
        }
    ~Librarie();
};

Carte::Carte(const char *titlu_, const char *autor_, const int an_aparitie) {
    this->Titlu = new char[strlen(titlu_)+1];
    strcpy(this->Titlu,titlu_);

    this->Autor = new char[strlen(autor_)+1];
    strcpy(this->Autor,autor_);

    An_aparitie = an_aparitie;
}
Carte::Carte(const Carte &book1) {
    this->Titlu = new char[strlen(book1.Titlu)+1];
    strcpy(this->Titlu,book1.Titlu);

    this->Autor = new char[strlen(book1.Autor)+1];
    strcpy(this->Autor,book1.Autor);

    An_aparitie = book1.An_aparitie;
}
Carte::Carte() {
    delete [] Titlu;
    delete [] Autor;///Am schimbat la astea 3

    char *buff = new char[100];
    this->Titlu =new char[strlen(buff)+1];
    strcpy(this->Titlu,buff);
    this->Autor =new char[strlen(buff)+1];
    strcpy(this->Autor,buff);
    An_aparitie = 0;
}
void Carte::SetTitlu(const char *titlu_) {
    this ->Titlu = new char[strlen(titlu_)+1];
    strcpy(this->Titlu,titlu_);
}
char *Carte::GetTitlu()const{
    return Titlu;
}
void Carte::SetAutor(const char* autor_){
    Autor = new char[strlen(autor_)+1];
    strcpy(this->Autor,autor_);
}
char *Carte::GetAutor()const{
    return Autor;
}
void Carte::SetAnaparitie(const int an) {
    An_aparitie = an;
}
int Carte::GetAnaparitie() const{
    return An_aparitie;
}
Carte& Carte::operator = (const Carte& book) {
    if(this != &book){
        SetTitlu(book.Titlu);
        SetAutor(book.Autor);
    }
    this->An_aparitie = book.An_aparitie;
    return *this;
}
bool operator ==(const Carte& book , const Carte& book2){
    return (*book.Autor == *book2.Autor && *book.Titlu == *book2.Titlu && book.An_aparitie == book2.An_aparitie);
}
bool operator !=( const Carte& book, const Carte& book2){
    return (book.Autor != book2.Autor || book.Titlu != book2.Titlu || book.An_aparitie != book2.An_aparitie);
}

ostream& operator <<(ostream& os, const Carte &book){
    os<<book.Autor<<' '<<book.Titlu<<' '<<book.An_aparitie<<endl;
    return os;
}
istream& operator >>(istream& is, Carte& book){
    cout<<"Citire Autor"<<endl;
    char buff[255];
    cin>>buff;
    book.Autor = new char[strlen(buff)+2];
    strcpy(book.Autor,buff);
    cout<<"Citire Titlu"<<endl;
    cin>>buff;
    book.Titlu = new char[strlen(buff)+2];
    strcpy(book.Titlu,buff);
    cout<<"Citire an_aparitie"<<endl;
    cin>>book.An_aparitie;
}
Carte::~Carte() {
    delete [] Titlu;
    delete [] Autor;
}

void Librarie::Cautare() {
        char *buff = new char[100];
        cout<<"Cautare carte sau dupa titlu, introduceti una din ele:"<<endl;
        cin>>buff;
        cout<<buff<<endl;
        int ok = 0;
        for(int i = 0; i < nr; i++){
            if(strcmp(listaCarte[i]->GetAutor(),buff) == 0){
                cout<<"Este autorul cartii ["<<i+1<< "]"<<endl;
                ok++;
            }
            if(strcmp(listaCarte[i]->GetTitlu(), buff) == 0){
                cout<<"Este titlul cartii ["<<i+1<<"]"<<endl;
                ok++;
            }
        }
        if(ok == 0){cout<<"Nu exista acest autor/titlu"<<endl;}
}
Librarie::~Librarie() {
    for(int i = 0; i < nr; i++){
        delete listaCarte[i];
    }
    delete listaCarte;
}
int main() {
    int cnt;
    while(1){
    //system("Color 0A");
    cout<< "Pentru a initializa doua carti si a testa functiile de initializare/citire/copiere/atribuire/==/!= apasa [1]"<< endl;
    cout << "Pentru a se realiza citirea si afisarea a n carti [2]" << endl;
    cout << "Pentru a initializa o libararie apasa [3] " << endl;
    cout << "Pentru a iesi introduceti [100]" << endl;
    cout << endl << "Alegerea:";
    cin >> cnt;
    switch (cnt) {
        case 1: {
            int func = 0;
            Carte book("Capra cu trei iezi", "Ion Creanga", 1837);
            cout << "Cartea nr 1: " << book;
            Carte book2("Moby Dick", "Herman Melville", 1851);
            cout << "Cartea nr 2:" << book2;
            cout
                    << "Pentru a Reciti Titlul, Autorul si Anul in prima carte apasati [1] sau pentru a doua carte apasati [2] "
                    << endl;
            cout << "Pentru a Copia continutul din Cartea 1 in Cartea 3 apasati [3]" << endl;
            cout << "Pentru a Atribui elmentele din Cartea2 in Cartea1 apasati [4] " << endl;
            cin >> func;
            if (func == 1) {
                cin >> book;
                cout << "Cartea nr 1: " << book << endl;
            }
            if (func == 2) {
                cin >> book2;
                cout << "Cartea nr 2: " << book2 << endl;
            }
            if (func == 3) {
                Carte book3(book);
                cout << "Cartea 3 :" << book3;
            }
            if (func == 4) {
                book = book2;
                cout << "Cartea 1 :" << book;
            }
            cout << "Pentru a vedea daca Cartea 1 si Cartea 2 sunt la fel apasati [5] sau [6] pentru a inchide" << endl;
            cin >> func;
            if (func == 5) {
                if (book == book2) {
                    cout << "Cartile sunt la fel" << endl;
                } else {
                    cout << "Cartile nu sunt la fel" << endl;
                }
            }
            if (func == 6) {
                return 0;
            }
        }
        case 2: {
            int n;
            cout << "Nr de elemente ale listei de carti: ";
            cin >> n;
            Carte **lista = new Carte *[n];
            for (int i = 0; i < n; ++i) {
                lista[i] = new Carte("Default", "Default", 0);
            }
            for (int i = 0; i < n; i++) {
                cout << "Cartea nr [" << i + 1 << "]" << endl;
                cin >> *lista[i];
            }
            for (int i = 0; i < n; i++) {
                cout << "Cartea nr [" << i + 1 << "] ";
                cout << *lista[i];
            }
            //Stergere din memorie
            for (int i = 0; i < n; i++) {
                delete lista[i];
            }
            delete[] lista;
            break;
        }
        case 3: {

            int n;
            cout << "Numarul de carti din libarie" << endl;
            cin >> n;
            Carte **lista = new Carte *[n];
            for (int i = 0; i < n; ++i) {
                lista[i] = new Carte("Default", "Default", 0);
            }
            for (int i = 0; i < n; i++) {
                cout << "Cartea nr [" << i + 1 << "]" << endl;
                cin >> *lista[i];
            }
            for (int i = 0; i < n; i++) {
                cout << "Cartea nr [" << i + 1 << "] ";
                cout << *lista[i];
            }
            Librarie lib1(n, lista);
            int func = 0;
            cout << "Daca doriti sa vedeti toate elementele din librarie apasati [1]: " << endl;
            cout << "Daca doriti sa cautati un element specific apasati [2]: " << endl;
            cout << "Daca doriti sa mai adaugati un element += [3]" << endl;
            cin >> func;
            if (func == 1) {
                lib1.Afisare_lista();
                break;
            }
            if (func == 2) {
                lib1.Cautare();
                break;
            }
            if (func == 3) {
                ///Adaugare prin +=
                Librarie lib2(n, lista);
                lib2.Afisare_lista();
                lib1 += lib2;
                lib1.Afisare_lista();
            }
            for (int i = 0; i < n; i++) {
                delete lista[i];
            }
            delete[] lista;
            break;}

        case 100: {
            break;
        }
    }
    break;
    }
    fflush(stdin);
    return 0;
}
