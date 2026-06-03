#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;
class Ordinateur
{
   private:
     ///Déclaration des propriétés de la class
     string id;
     string se;
     int capacite;
     static int compteur;
     static string file;
   public:
     ///Déclaration des fonctions membres de la class
     Ordinateur();
     Ordinateur(string );
     Ordinateur(string ,int);
     void save();
     void del();
     void update();
     void searchOrdi();
     void afficher();
     static void getComputers();
     static int getCurrentId();

};
///Définition des attributs static
string Ordinateur::file="data.csv";
int Ordinateur::compteur=Ordinateur::getCurrentId();;
///Définition des fonctions membres
Ordinateur::Ordinateur(){}
Ordinateur::Ordinateur(string id){
 this->id=id;
}
Ordinateur::Ordinateur(string se,int capacite){
    ostringstream os;
    os<<"G6PC"<<setfill('0')<<setw(3)<<++Ordinateur::compteur;
    this->id= os.str();
    this->se=se;
    this->capacite=capacite;

}
void Ordinateur::afficher()
{
    cout << "========================"<<endl;
    cout << "=Id: "<<id<<endl;
    cout << "=Systeme Exp.: "<<se<<endl;
    cout << "=Capacite: "<<capacite<<endl;
    cout << "========================"<<endl;
}

void Ordinateur::save()
{
    ofstream flux(Ordinateur::file,ios::out|ios::app);;
    if(flux)
    {
      flux<<id<< ";"<< se<< ";"<< capacite<<endl;
      flux.close();
      cout << "\t {## Enregistrement reussi! ##}"<<endl;
    }
    else
    {
      cout << "\t {## Impossible d'ouvrir le fichier! ##}"<<endl;
    }
}
int Ordinateur::getCurrentId()
{
    ifstream flux(Ordinateur::file,ios::in);
    string line,lineCopy="G6PC000";
    if(flux)
    {
       while(getline(flux,line))
       {
           lineCopy=line;
       }
    }
    return stoi(lineCopy.substr(4,3));

}

void Ordinateur::del()
{
    ifstream flux(Ordinateur::file,ios::in);
    string line,data="";
    bool found=false;
    if(flux)
    {
        while(getline(flux,line))
        {
            if(id!=line.substr(0,7))
            {
                data += line + "\n";
            }
            else
            {
                found=true;
            }
        }
        flux.close();

    }
    else
        cout << "\t{## Impossible d'ouvrir le fichier ##}\n";
    ofstream fluxSortie;
    if(found)
    {
       fluxSortie.open(Ordinateur::file,ios::out|ios::trunc);
       fluxSortie<<data;
       fluxSortie.close();
        cout << "\t{## Suppression effectuee avec succes ##}\n";
    }
    else
        cout << "\t{## Ordinateur introuvable ##}\n";
}

void Ordinateur::update()
{
    ifstream flux(Ordinateur::file,ios::in);
    string line,data="";
    bool found=false;
    if(flux)
    {
        while(getline(flux,line))
        {
            if(id!=line.substr(0,7))
            {
                data += line + "\n";
            }
            else
            {
                found=true;
                cout << "Donner le systeme d'exploitation >> ";
                cin>>se;
                cout << "Donner la capacité >> ";
                cin>>capacite;
                data +=line.substr(0,7)+ ";";
                data +=se + ";";
                data +=to_string(capacite) + "\n";
            }
        }
        flux.close();

    }
    else
        cout << "\t{## Impossible d'ouvrir le fichier ##}\n";
    ofstream fluxSortie;
    if(found)
    {
       fluxSortie.open(Ordinateur::file,ios::out|ios::trunc);
       fluxSortie<<data;
       fluxSortie.close();
        cout << "\t{## Modification effectuee avec succes ##}\n";
    }
    else
        cout << "\t{## Ordinateur introuvable ##}\n";
}

void Ordinateur::searchOrdi()
{
    ifstream flux(Ordinateur::file,ios::in);
    string line;
    bool found=false;
    if(flux)
    {
        while(getline(flux,line))
        {
            if(id==line.substr(0,7))
            {
                found=true;
                break;
            }
        }
        flux.close();

    }
    else
        cout << "\t{## Impossible d'ouvrir le fichier ##}\n";
    if(found)
    {
        cout << line<<endl;
    }
    else
        cout << "\t{## Ordinateur introuvable ##}\n";
}

void Ordinateur::getComputers()
{
    ifstream flux(Ordinateur::file,ios::in);
    string line;
    bool found=false;
    if(flux)
    {
        while(getline(flux,line))
        {
            cout << line<<endl;
            found=true;
        }
        flux.close();

    }
    else
        cout << "\t{## Impossible d'ouvrir le fichier ##}\n";
    if(!found)
        cout << "\t{## Liste vide ##}\n";
}
class App
{
    public:
        static void run();
    private:
        static void save();
        static void liste();
        static void del();
        static void update();
        static void searchOrdi();
};
 void App::run()
 {
     int choix;
     do
     {
       system("cls");
       cout << "======================\n";
        cout << "1-Ajouter\n";
        cout << "2-liste\n";
       cout << "======================\n";
       cout << "Entrer le choix >>";

       while(!(cin>>choix))
       {
           cout << "Syntaxe Error\n";
           cout << "veuillez saisir un entier >>";
           cin.clear();
           cin.ignore(255,'\n');

       }
       switch(choix)
       {
           case 1:
             App::save();
             system("pause");
             break;
          case 2:
             App::liste();
             system("pause");
             break;
            default :cout << "choix incorrect\n";
       }

     }while(choix!=6);
 }
 void App::save()
 {
     string se;
     int capacite;
     cout << "##ENREGISTREMENT D'UN ORDINATEUR##\n";
     cout << "Donner le systeme >>";
     cin>>se;
     cout << "Donner la capacite >>";
     cin>>capacite;
     Ordinateur (se,capacite).save();
 }
 void App::liste()
 {
     cout << "##LISTE DES ORDINATEURS##\n";
     Ordinateur::getComputers();
 }
int main()
{
    App::run();
    return 0;
}
