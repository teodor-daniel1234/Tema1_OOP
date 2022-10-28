#include <iostream>
#include <cstring>
using namespace std;
///https://oop.octav.cc/tema1/
/// Clasa Librarie: permite adăgarea a mai multor cărți prin operatorul +=
///căutarea unei cărți după titlu / autor
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
    char *GetTitlu();///GETTER
    void SetAutor(const char *autor_);
    char *GetAutor();
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
    Carte *colectie;
    int nr;
public:
    Librarie(Carte const &librarie){

    }

    //friend bool operator +=();
};

Carte::Carte(const char *titlu_, const char *autor_, const int an_aparitie) {
    this->Titlu = new char[strlen(titlu_)+1];
    strcpy(this->Titlu,titlu_);
    this->Autor = new char[strlen(autor_)+1];
    strcpy(this->Autor,autor_);
    An_aparitie = an_aparitie;
}
Carte::Carte(const Carte &book1) {
    Titlu = book1.Titlu;
    Autor = book1.Autor;
    An_aparitie = book1.An_aparitie;
}
Carte::Carte() {
    char *buff = "cel mai lung titlu posibil deoarce nu exista titlu mai lung de atat";
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
char *Carte::GetTitlu() {
    return Titlu;
}
void Carte::SetAutor(const char* autor_){
    Autor = new char[strlen(autor_)+1];
    strcpy(this->Autor,autor_);
}
char *Carte::GetAutor() {
    return Autor;
}
void Carte::SetAnaparitie(const int an) {
    An_aparitie = an;
}
int Carte::GetAnaparitie() const{
    return An_aparitie;
}
///DE intrebat
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
int main(){

    int n;
    cout<<"Cate elemente vrei: ";
    cin>>n;
    Carte **lista = new Carte * [n];
    for(int i = 0; i < n; i++){
         lista[i] = new Carte("Default","Default",2) ;
    }
    for(int i = 0; i < n; i++){
        cout<<"Elementul nr "<<i+1<<endl;
        cin>>*lista[i];
    }
    //lista[1] = lista[0]; 
    for(int i = 0; i < n; i++){
       cout<<*lista[i];
    }
    Carte a("Default","Default",2);
    Carte b("A","B",3);
    a = *lista[0];
    cout<<a;
    ///Dealocarea memoriei
    for(int i = 0; i < n; i++){
        delete lista[i];
    }
    delete lista;

    return 0;
}
