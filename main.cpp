#include <iostream>
#include <regex>
#include <string>

using namespace std;

string variablesDefinidas[10];
int cantidaDeVariables = 0;
int q = 0;
char palabra;

bool valNum(const string& palabra);
bool valLetra(const string& palabra);
bool valNumDouble(const string& palabra);
void reconocedor(string nmb,char tipo);
void reconocedoAsig(string nmb,char tipo);
int buscador(string nmb);
string scanner(string palabra1,int &i,char &tipo);
void ingreso (string m[100], int &i);

int main(){
    string cadenaTexto[100];//Vector donde se guarda,cada cadena de texto
    string fraseIngresada, palabraRetornada;
    char tipo; //Es para definir el tipo
    int n = 0 , i; //n = veces que ingresas la cadena//i = Posicion de la letra en cada cadena 

    ingreso(cadenaTexto,n); //Retornaria el vector, llenado  y la cantidad de cadenas(n)
    for (int j = 0; j <= n; j++){
      i = q = 0;
      fraseIngresada   = cadenaTexto[j];
      palabraRetornada = scanner(fraseIngresada,i,tipo);
      if(palabraRetornada == "int" ||palabraRetornada == "float" || palabraRetornada == "double") 
      {
        do{
          reconocedor(palabraRetornada,tipo);
          palabraRetornada = scanner(fraseIngresada,i,tipo);
        }while(palabraRetornada != "$");
        reconocedor(palabraRetornada,tipo);
      }
      else if(valLetra(palabraRetornada) == true && (palabraRetornada != "int" ||palabraRetornada != "float" || palabraRetornada != "double") )
      {
         do{
          reconocedoAsig(palabraRetornada,tipo);
          palabraRetornada = scanner(fraseIngresada,i,tipo);
        }while(palabraRetornada != "$");
        reconocedoAsig(palabraRetornada,tipo);
      }

    }
    system("pause");
    return 0;
} 

//Ingreso de la cadena texto, guardando cada una en una posicion del vector 
int buscador(string nmb){
  for(int i = 0; i < cantidaDeVariables;i++){
    if(nmb == variablesDefinidas[i]){
      return 1;
    }
  }
  return 0;
}
void ingreso (string cadenaTexto[100], int &n){
    string palabra1;
    int t=0;
    cout<<"Ingrese el codigo, finalice con }:"<<endl;
    do{
        cout<<n+1<<" "; 
        getline(cin,cadenaTexto[n]);
        if(cadenaTexto[n]=="}")
          break;

        palabra1 = cadenaTexto[n];
        t = palabra1.size();
        n++;
    }while(palabra1[t-1]!='}');

}

string scanner(string palabra1, int &i, char &tipo)
{
    string palabra2, letra;
    while (palabra1[i] == ' ')
        i++;
    if (palabra1[i] >= 'a' && palabra1[i] <= 'z')
    {
        while ((palabra1[i] >= 'a' && palabra1[i] <= 'z') || (palabra1[i] >= '0' && palabra1[i] <= '9'))
        {
            letra    = palabra1[i];
            palabra2 = palabra2 + letra;
            i++;
        }
        tipo = 'I';
    }
    else if (palabra1[i] >= '0' && palabra1[i] <= '9')
    {
        while ((palabra1[i] >= '0' && palabra1[i] <= '9')|| palabra1[i] == '.')
        {
            letra = palabra1[i];
            palabra2 = palabra2 + letra;
            i++;
        }
        tipo = 'N';
    }

    else if ( palabra1[i] == '=' || palabra1[i] == '(' || palabra1[i] == ')' || palabra1[i] == ',' || palabra1[i] == ':'||palabra1[i] == '+'||palabra1[i] == '*'||palabra1[i] == '-'||palabra1[i] == '/')
    {
        letra = palabra1[i];
        palabra2 = palabra2 + letra;
        i++;
    }
    else {
      palabra2 = "$";
        tipo = 'S';
    }
    return palabra2;
}

//Validacion de los caracteres o numeros con expresiones regulares
bool valNum(const string& palabra){
  const regex expReg("[0-9]*");
  return regex_match(palabra,expReg);
}
bool valNumDouble(const string& palabra){
  const regex expReg("[0-9]+(\\.[0-9]+)?");
  return regex_match(palabra,expReg);
}
bool valLetra(const string& palabra){
  const regex expReg("[a-z0-9]*");
  return regex_match(palabra,expReg);
}

//Guia del grafo
void reconocedor (string nmb,char tipo){
  if(q != 100 && q != -1){
    switch(q){
      case 0:
        //Se tiene que crear un array para guar el tipo  y definirlo más adelante(lo hare más rato pero necesito el scanner)
        if(nmb == "int"||nmb=="float" || nmb=="double" ){
          if(nmb=="float" || nmb=="double")
          palabra='D';
          else if(nmb=="int")
            palabra='E';
          q = 1;
        }
        else
          q =-1;
      break;
      case 1:
        if(tipo == 'I'){
          variablesDefinidas[cantidaDeVariables]=nmb;
            cantidaDeVariables++;
          q = 2;
        }
        else
          q = -1;
      break;
      case 2:
        if(nmb == "="){
          q = 3;
        }
        else if(nmb == ";")
          q = 5;
        else if(nmb == ",")
          q = 1;
        else
          q = -1; 
      break;
      case 3:
      if(palabra=='E'){
        if(valNum(nmb) == true){
          q = 4;
        }}
      else if(palabra=='D'){
        if(valNumDouble(nmb) == true){
          q = 4;
        }}
        else 
          q = -1;
      break;
      case 4:
        if(nmb == ";")
          q = 5;
        else if(nmb == ",")
          q = 6 ;
        else
          q = -1;
      break;
      case 5:
        if(nmb == "$"){
          q = 100;}
        else
          q = -1;
      break;
	  case 6:
	  if (tipo == 'I')
	  {
		  q = 2;
	  }
	  else
	  	q = -1;
    }
  if(q == 100)
    cout<<"LINEA CORRECTA"<<endl;
  else if(q == -1){
    cout<<"LINEA INCORRECTA"<<endl;
       cantidaDeVariables--;
    }
  }
}
void reconocedoAsig(string nmb,char tipo){
  if(q != 100 && q != -1){
    switch(q){
      case 0:
        if(tipo == 'I' && buscador(nmb) == 1){
          q = 1;
        }
        else
          q =-1;
      break;
      case 1:
        if(nmb == "="){

          q = 2;
        }
        else
          q = -1;
      break;
      case 2:
        if(valNumDouble(nmb) == 1 ||( valLetra(nmb) == true  && buscador(nmb)==1))
        {
          q = 3;
        }
        else
          q = -1; 
      break;
      case 3:
        if(nmb == "+"||nmb == "*"||nmb == "-"||nmb == "/"||nmb == "=")
          q = 4;
        else if(nmb ==";")
          q = 5;
        else 
          q = -1;
      break;
      case 4:
        if(valNumDouble(nmb) == true || ((valLetra(nmb) == true ) && buscador(nmb)==1)){
            q = 3;
        }
        else
          q = -1;
      break;
      case 5:
        if(nmb == "$")
          q = 100;
        else
          q = -1;
      break;
          }
  if(q == 100)
    cout<<"LINEA CORRECTA"<<endl;
  else if(q == -1)
    cout<<"LINEA INCORRECTA"<<endl;
  }
}