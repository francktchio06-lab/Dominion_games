// exercice1
/*  

le main.cpp ne compile pas parcequ"il y'a un appel multiple 
de .hpp le compilateur ne sait  pas  lequel appelé


#ifndef POINT_HPP
#DEFINE POINT_HPP
struct Point{ int x,y;};

#ENDIF

le main renvoie 2+1*2+1=5

partie  B// sur les espaces de nomages et l'interprétation 
du code en générales


on a un global i et une variable  global total;
variable  locale i qui appartient  à  A;
 0 // pas vraiment mais une valeur  par défaut
 i loca du main orend la valeur 1
 int local de {} que je vais appelé B prend la valeur 2  



 ** exercice 3 
 1 impossible un ointeur non constant  ne peut pas pointer sur une valeur vosntznte
 r3  ointent vers x  
 en java  on ne devrait  pas utilisé les  delete  et les new  car java  utilise les  c
 carbages  collector pour gérr la mémoire et donc remplacer les delete 


 123 153 157 
 nno car les caleurs  par défaut apparaissent à la fin de la fonction
 int reduire(int (*op)(int,int ), const int t[],iny n,int init){
    r=init,
    for(int j=0;j<n;j++) r=op(r,t[j]);
    return r;}
    avec un un tableau t={1,2,3} on a  r=0;r=6
    r=-6
     daclarons n pointeur de fonctions;
      int  (*fp)(int,int)
      *fp=somme;
      cout<< fp(5,6);
*/
/*
  exercice 2 
  class Chaine{
    char  * data ;
    int len;
    static int nb ;
    public :
        //chaine (const char* s=""){
                len =len(s);
                data = new  char[len+1];
                strcp(data,s);
                 }
        // constructeur copie
         chaine ( const chaine& s){
            len =s.len;
            data= new  char[len+1];
            stcp(data,s.data);}
 
        ~chaine(){
            delete [] data;}
        
        Chaine&  operator=( const chaine& c){
            if(&this!=c) {
                    }}



        #include "Chaine.hpp"
#include <cstring>
#include <string>
using namespace std;
int Chaine::nb = 0;
Chaine::Chaine(const char* s) : len(strlen(s)) {
    data = new char[len + 1];
    strcpy(data, s);
    nb++;
}
Chaine::Chaine(const Chaine& c) : len(c.len) {
    data = new char[len + 1];
    strcpy(data, c.data);
    nb++;
}
Chaine::~Chaine() { delete[] data; nb--; }
Chaine& Chaine::operator=(const Chaine& c) {
    if (this != &c) {
        char* nouveau = new char[c.len + 1];
        strcpy(nouveau, c.data);
        delete[] data;
        data = nouveau;
        len = c.len;
    }
    return *this;
}
Chaine& Chaine::operator+=(const Chaine& c) {
Exercices de C++ : entraînement à l’écrit
Page 17 of 31
Exercices de C++ : entraînement à l’écrit
char* nouveau = new char[len + c.len + 1];
strcpy(nouveau, data);
strcat(nouveau, c.data);
delete[] data;
data = nouveau;
len += c.len;
return *this;
}
char& Chaine::operator[](int i) {
if (i < 0 || i >= len) throw IndiceInvalide();
return data[i];
}
const char& Chaine::operator[](int i) const {
if (i < 0 || i >= len) throw IndiceInvalide();
return data[i];
}
Chaine operator+(const Chaine& a, const Chaine& b) {
Chaine r(a);
r += b;
return r;
}
bool operator==(const Chaine& a, const Chaine& b) {
return strcmp(a.c_str(), b.c_str()) == 0;
}
ostream& operator<<(ostream& os, const Chaine& c) { return os << c.c_str(); }
istream& operator>>(istream& is, Chaine& c) {
string mot;
if (is >> mot) c = Chaine(mot.c_str());
return is;
}


1 elle complime la premire utilise le constructeur  de copie ,la  deuxiele 



C(ab);
cc(a);
=;
cc(ab) , cc(!), ab! D(ab!)
ab!
c(xy); cc(xy), =

4
d(xy)
d(xy)
d
dès qu'on supprime le constructuer de copie b=a affecte l'addresse de a à b puis à la fin du programme il supprime a qui supprime automatiquement b vu qu'il pointen vers le même object

 */
/* exercice 3
 donnons la sortie complete

 composant A B  C ~C ~B ~A ~composant 
 A 
 c::f A::g  ~A
 composant A B
 composant  A B::f A::g 
 A::f A::g;
B::g, A::g 
 ~b ~A ~composant 

vehicule tereste marin amhibie 
navigue deplacer
navigue et deplacer 

class forme{
    public :
        virtual double aire() const =0;
        vitual double perimetre() const =0;
        virtual void affihcer const{
        std::cout<< "aire"<< aire()<< " perimetre="<< perimetre();}
          };
class cercle: public forme{
    double r;
    public :
        Cercle (double r): r(r){
        }
        double aire() const { return 3.14*r*r};
        double  perimetre () const  {return 3.14*2*r;}

        }

    
        }
        class rectangle : public  forme{
            double l,h;
                public:
                }


    0  lock(v2) lockv3 0k3 coyt fin2  unlock v3 unlock v1
    k=1 : lock(v2) lov(v3) fi2 introuvable unlock v3 unlock v2
    k=2  lock(v2) lock (v3) fi2 erreur 
    k=3  lock v2 lock v3  fi2 autre

    cout.width(8); cout.fill('*');
cout << 42 << "|" << 7 << endl;
cout.fill(' '); cout.width(0); cout.precision(3);
cout << 3.14159 << " " << 1234.5678 << endl;
cout.setf(ios::hex, ios::basefield);
cout << 255 << " " << 16 << endl;
cout.setf(ios::dec, ios::basefield);
istringstream in("12 abc 7");
int a = -1, b = -1, c = -1;
in >> a; cout << a << " " << in.good() << in.fail() << endl;
in >> b; cout << b << " " << in.good() << in.fail() << endl;
in >> c; cout << c << " " << in.good() << in.fail() << endl;
in.clear(); in.ignore(4); in >> c; cout << c << endl;

*/