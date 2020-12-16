#include <stdio.h>
#include <cstring>//strcmp
#include <iostream>
#include <fstream>
#include <cstdlib>//randomization
#include <ctime>

using namespace std;


//make a new test from a base test
//random questoions and answers form a formated source and save in a file :newtest.txt
class  maketest{


private:

  const char drk ='#';
  int ile_odpowiedzi=4;
  char inputfile[50]="basetest.txt"; //name of file with base test
  char outputfile[50]="newtest.txt"; // name  of output test file
  fstream file_read_des; //  files's descryptor (or ifstream)
  fstream file_write_des;//output file descryptor

  string zdanie="";
  string Spytanie[10],Spoprawna[10],Sniepoprawna[10];
  char Znak;
  int pytanie=0;int poprawne=0; int niepoprawne=0;
  string wczytanadrk,tytul;
  char drkbyla='1';
  bool powtorzlos=false;
  int wylosowana,wylosowanapoprawna,wylosowananiepoprawna[10];
  string dozapisu="Nowy test";
  int Nrpytania=1;
  string odp="";
//methods
   int wylosuj(int dana);

public:
 bool zakonczprogram=false;
//methods
maketest(void);
~maketest(void);
void ustawgenerator();//ninapisna
void wykonujetest();
}; //-------------------end of class------------------
maketest::maketest(void){
cout <<"open base test file: "<<inputfile<<endl;
do{
file_read_des.open(inputfile , std::ios::in );
//ifstream file_read_des("tescik.txt"); //equvalent possibility to open the file
if (file_read_des.fail() ){
   cout <<"error open the input base test file : "<<inputfile<<endl<<"press 'x' to end or input a name of base file: "<<flush; //clean the buffer
   cin >>inputfile;
   }
if ( strcmp(inputfile,"x")==0){ zakonczprogram=true; return ;}

}while  (file_read_des.fail() );

file_write_des.open( outputfile, std::ios::out );

cout <<"open output file : "<<outputfile<<endl;

}
maketest::~maketest(void){

   cout <<endl<<"close input base file:"<<inputfile<< endl;
   file_read_des.close();
   cout <<"close output file:"<<outputfile<< endl;
   file_write_des.close();



}
//randomization
int maketest::wylosuj (int dana)
{
 return (( std::rand() % dana )+1 );
}

void maketest::wykonujetest(){// core methods
  while( !file_read_des.eof() ){//work until descryptor riches  the end of file
         file_read_des.get(Znak);

     if (Znak==drk)  {
        file_read_des>>wczytanadrk; //read entire string of directive
        //remamber all variation of qeustions
        if(drkbyla=='s'){ tytul=zdanie;  } //title of test
        if(drkbyla=='q'){ Spytanie[pytanie]=zdanie;cout<<Spytanie[pytanie];} //question
        if(drkbyla=='p'){ Spoprawna[poprawne]=zdanie;cout<<Spoprawna[poprawne];}//positiv
        if(drkbyla=='n'){ Sniepoprawna[niepoprawne]=zdanie;cout<<Sniepoprawna[niepoprawne];} //negativ
        if(drkbyla=='c'){  }//not used yet
        if(drkbyla=='s'){dozapisu=tytul;file_write_des.write( &dozapisu[0],dozapisu.length() );//save file
             }
        if ( (wczytanadrk[0]=='q'|| wczytanadrk[0]=='e')&& (drkbyla =='n'||drkbyla=='p')) {

        {
            wylosowana= wylosuj(pytanie);
            cout<<"save : " <<" question  "<<pytanie<<" random "<<wylosowana<<Spytanie[wylosowana]<<" * ";
            file_write_des<<endl<<Nrpytania<<")" <<Spytanie[wylosowana]<<endl;
            Nrpytania++;


          if(niepoprawne<3)cout<<"to little negatic answers in question: "<<pytanie;
          if (poprawne==0) cout<< "to little correct answers in question: "<<pytanie;
           // randomization of answers
           wylosowanapoprawna = wylosuj(4);

          for (int k=1;k<=ile_odpowiedzi;k++){
            switch (k){
            case 1 : odp = "a)";break;
            case 2 : odp =  "b)";break;
            case 3 : odp = "c)";break;
            case 4 : odp = "d)";break;}
            if (k==wylosowanapoprawna) {file_write_des<<odp<< Spoprawna[wylosuj(poprawne)];wylosowananiepoprawna[k]=-1;}

            else
            {

   //negative answers without repetitions

                do{
                wylosowananiepoprawna[k]=wylosuj(niepoprawne);

                powtorzlos=false;
                for (int i=1;i<k;i++)
                {

                if (wylosowananiepoprawna[i]== wylosowananiepoprawna[k]){powtorzlos=true;}

                }


                }while(powtorzlos==true);
                file_write_des<< odp<<Sniepoprawna[wylosowananiepoprawna[k]]; //write not correct answer
            }
          }

            pytanie=0;poprawne=0;niepoprawne=0;
}
         }

       cout <<drkbyla;
       drkbyla=wczytanadrk[0];

       cout<<" #:"<<wczytanadrk<<" ";
       zdanie="";//clean previus sentance


      if (wczytanadrk[0]=='q') { pytanie++; }
      if (wczytanadrk[0]=='p') { poprawne++;}
      if (wczytanadrk[0]=='n') { niepoprawne++;}



     }
     else{

        zdanie =zdanie+Znak;

        }

  }



}
//set up generator
void maketest::ustawgenerator(){
srand( time( NULL ) );
}


int main (){

maketest zrobietescik; //make object

zrobietescik.ustawgenerator();//set up generator
if (zrobietescik.zakonczprogram==false )zrobietescik.wykonujetest(); //if find a base test file make a new test

  return 0;
}
























//future make servis more possible errors and random without repetitions















/*

https://www.geeksforgeeks.org/5-different-methods-find-length-string-c/
ofstream

This data type represents the output file stream and is used to create files and to write information to files.
2

ifstream

This data type represents the input file stream and is used to read information from files.
3

fstream

This data type represents the file stream generally, and has the capabilities of both ofstream and ifstream which means it can create files, write information to files, and read information from files.

https://www.tutorialspoint.com/cplusplus/cpp_files_streams.htm

http://cpp0x.pl/kursy/Kurs-C++/Obsluga-plikow/305

*/
