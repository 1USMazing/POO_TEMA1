#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/*Tema 1. Clasa ”Numar_Complex”
- membrii privati pentru partea reala si partea imaginara (double);
- constructori pentru initializare si copiere;
- destructor (în cazul alocarii statice, se seteaza dimensiunea vectorului la zero, iar în
cazul alocarii dinamice, se dezaloca zona de memorie utilizata);
- metode publice pentru setat/furnizat partea reala si partea imaginara;
- metoda publica de afisare (sub forma &quot;a&quot;, &quot;i*a&quot;, &quot;-i*a&quot;, &quot;a+i*b&quot;, &quot;a-i*b&quot;);
- metoda publica pentru determinarea modulului unui numar complex;
- suma a doua numere complexe, implementata prin supraincarcarea op +;
- produsul a doua numere complexe, implementat prin supraincarcarea op *;
- împărțirea a doua numere complexe, implementata prin supraincarcarea op /.
- metoda publica sqrt pentru furnizarea radicalului de ordinul 2 al unui complex.
Sa se realizeze un program de rezolvare a ecuatiei de ordinul doi cu coeficienti complecsi.*/

class Numar_Complex
{
    double parte_reala;
    double parte_imaginara;
    friend istream& operator>> (istream &, Numar_Complex& );

public:
    vector<Numar_Complex> Numere;

//Declarare constructor initializare
    Numar_Complex(double pr=0, double pi=0)
    {
        parte_reala=pr;
        parte_imaginara=pi;
    }

//Declarare constructor copiere
    Numar_Complex(const Numar_Complex &C)
    {
        parte_reala=C.parte_reala;
        parte_imaginara=C.parte_imaginara;
    }

//Declarare Destructor
    ~Numar_Complex()
    {
        Numere.clear();
    }

    double GetParteReala()
    {
        return parte_reala;
    }

    double GetParteImaginara()
    {
        return parte_imaginara;
    }


    double GetModul()
    {using std::sqrt;
        return sqrt(pow(parte_imaginara, 2) + pow(parte_reala, 2));
    }

//Supraincarcarea op +
    Numar_Complex operator + (const Numar_Complex &obj)
    {
        Numar_Complex rezultat;

        rezultat.parte_reala=parte_reala + obj.parte_reala;
        rezultat.parte_imaginara=this->parte_imaginara+obj.parte_imaginara;

        return rezultat;
    }

// (a + bi)(c + di) = ac -bd + i(bc+ad)
//Supraincarcarea op *
    Numar_Complex operator * (const Numar_Complex &obj)
    {
        Numar_Complex rezultat;

        rezultat.parte_reala=this->parte_reala*obj.parte_reala - this->parte_imaginara*obj.parte_imaginara;
        rezultat.parte_imaginara=this->parte_imaginara*obj.parte_reala+this->parte_reala*obj.parte_imaginara;

        return rezultat;
    }

//Supraincarcarea op /

    Numar_Complex operator / (const Numar_Complex &obj)
    {
        Numar_Complex rezultat;

        double a=this->parte_reala;
        double b=this->parte_imaginara;
        double c=obj.parte_reala;
        double d=obj.parte_imaginara;

        rezultat.parte_reala=(a*c + b*d)/(pow(c,2)+pow(d,2));
        rezultat.parte_imaginara=(c*b - a*d)/(pow(c,2)+pow(d,2));

        return rezultat;

    }

// z = a + b*i
// r = x + y*i

//r*r=z => x^2 - y^2 + 2*x*y*i= a+b*i
//abs(r*r)=abs(z) =>
//x^2 + y^2= sqrt(a^2+ b^2)

//x^2 - y^2=a
//x*y=b/2
//x^2 + y^2=sqrt(a^2+ b^2)

//x^2 - y^2=a
//x^2 + y^2=sqrt(a^2+ b^2)
// => 2*x^2=a + sqrt(a^2 + b^2)
// =>x^2=(a + sqrt(a^2 + b^2))/2
// =>x=+-sqrt((a + sqrt(a^2 + b^2))/2)
//y^2=sqrt(a^2+ b^2)-x^2
// => y=+-sqrt(sqrt(a^2+ b^2)-x^2)

//r1=sqrt((a + sqrt(a^2 + b^2))/2)+ i*sqrt(sqrt(a^2+ b^2)-x^2)
//r2=-sqrt((a + sqrt(a^2 + b^2))/2)- i*sqrt(sqrt(a^2+ b^2)-x^2)

Numar_Complex sqrt()
    {
        using std::sqrt;
        Numar_Complex rez;

        double a=parte_reala;
        double b=parte_imaginara;


        if(b!=0)
    {
            if(b>=0)
            {
                rez.parte_reala=sqrt( (a + sqrt(pow(a,2)+pow(b,2))) /2);
                rez.parte_imaginara=sqrt(sqrt(pow(a,2)+pow(b,2))-pow(rez.parte_reala,2));
            }
            else
            {
                rez.parte_reala=sqrt( (a + sqrt(pow(a,2)+pow(b,2))) /2);
                rez.parte_imaginara=-sqrt(sqrt(pow(a,2)+pow(b,2))-pow(rez.parte_reala,2));
            }
    }
        else if (b==0)
        {
            if(a>=0)
            {rez.parte_reala=sqrt(a);
            rez.parte_imaginara=0;
            }

            else
            {
                rez.parte_reala=0;
                rez.parte_imaginara=sqrt(-a);
            }
        }

        return rez;
    }

    void Citire_Numere()
        {

            double pr, pi;

            for (int i=0; i<3; i++)
            {
                Numar_Complex Nr;
                cin>>Nr;

                Numere.push_back(Nr);
            }
        }
};

ostream &operator<< (ostream &out, Numar_Complex &c)
    {
        double pi;
        string semn;

        if(c.GetParteImaginara()<0) {pi=abs(c.GetParteImaginara()); semn="-";}
        else {pi=c.GetParteImaginara(); semn=" + ";}


        if(c.GetParteImaginara()==0) out<<c.GetParteReala();

        else if(c.GetParteReala()==0)
        {
            if(semn==" + ")out<<"i*"<<pi;
            else out<<semn<<"i*"<<pi;
        }

        else {out<<c.GetParteReala()<<semn<<"i*"<<pi;}
        return out;
    }

istream& operator>> (istream &in, Numar_Complex& c)
{
   cout<<"Partea reala este: ";
   in>>c.parte_reala;

   cout<<"Partea imaginara este: ";
   in>>c.parte_imaginara;
   return in;
}

int main()
{

   Numar_Complex z;
   cout<<"Pentru functia: ax^2 + bx + c = 0, dati valorile coeficientilor complecsi."<<endl;
   z.Citire_Numere();

   Numar_Complex a=z.Numere[0];
   Numar_Complex b=z.Numere[1];
   Numar_Complex c=z.Numere[2];

   cout<<"Functia este: ";

   if(a.GetParteReala()!=0 && a.GetParteImaginara()!=0){cout<<"(";  cout<<a;   cout<<")x^2 + ";}
   else {cout<<a; cout<<"x^2 + ";}

   if(b.GetParteReala()!=0 && b.GetParteImaginara()!=0){cout<<"(";  cout<<b;   cout<<")x + ";}
   else {cout<<b; cout<<"x + ";}

   if(c.GetParteReala()!=0 && c.GetParteImaginara()!=0){cout<<c;   cout<<" = 0"<<endl;}
   else {cout<<c; cout<<" = 0"<<endl;}

   Numar_Complex b_patrat=b*b;

   Numar_Complex patru(4,0);
   Numar_Complex minus(-1, 0);

   Numar_Complex ac=(minus*patru)*(a*c);

   Numar_Complex delta=b_patrat+ac;

   Numar_Complex rad_delta=delta.sqrt();

   Numar_Complex numa=(minus*b)+(minus*rad_delta);

   Numar_Complex numi=patru.sqrt()*a;

   Numar_Complex x1=numa / numi;
   cout<<"x1 = "; cout<<x1; cout<<endl;

   Numar_Complex num=(minus*b)+rad_delta;

   Numar_Complex x2=num / numi;
   cout<<"x2 = "; cout<<x2; cout<<endl;

}
