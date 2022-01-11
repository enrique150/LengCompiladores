#include <iostream>
#include <regex>
#include <string>

using namespace std;

string variablesDefinidas[10];
int cantidaDeVariables = 0;
//Casos para el while
int t=0;
//Casos para el condicional
int u=0;
int q = 0;
char palabra;

//Pila usada
struct Nodo{
    string dato;
    Nodo *siguiente;
};

void agregarPila (Nodo *&,string);
void sacarPila (Nodo *&,string);
bool valNum(const string& palabra);
bool valLetra(const string& palabra);
bool valNumDouble(const string& palabra);
void reconocedor(string nmb,char tipo);
void reconocedoAsig(string nmb,char tipo);
int buscador(string nmb);
string scanner(string palabra1,int &i,char &tipo);
void ingreso (string m[100], int &i);

//Reconocedor cout y cin
void reconocedorcco(string nmb, char tipo);
void reconocedorcci(string nmb, char tipo);

//Reconocedor While 

void reconocedorWhile(string nmb, char tipo,Nodo *&pila);

//Reconocedor ifelse
void reconocedorifelse(string nmb, char tipo,Nodo *&pila1);


int main(){
    Nodo *pila=NULL;
    Nodo *pila1=NULL;
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
      else if(palabraRetornada == "cout")
      {
          do{
            reconocedorcco(palabraRetornada,tipo);
            palabraRetornada = scanner(fraseIngresada,i,tipo);
        }while(palabraRetornada != "$");
        reconocedorcco(palabraRetornada,tipo);
      }
      else if(palabraRetornada == "cin")
      {
          do{
            reconocedorcci(palabraRetornada,tipo);
            palabraRetornada = scanner(fraseIngresada,i,tipo);
        }while(palabraRetornada != "$");
        reconocedorcci(palabraRetornada,tipo);
      }

     else if(palabraRetornada=="while"||palabraRetornada == "endwhile"){
        do{
            reconocedorWhile(palabraRetornada,tipo,pila);
            palabraRetornada = scanner(fraseIngresada,i,tipo);
        }while(palabraRetornada != "$");
        reconocedorWhile(palabraRetornada,tipo,pila);
      }

      else if(palabraRetornada=="if"||palabraRetornada == "else"||palabraRetornada == "endif"){
        do{
            reconocedorifelse(palabraRetornada,tipo,pila1);
            palabraRetornada = scanner(fraseIngresada,i,tipo);
        }while(palabraRetornada != "$");
        reconocedorifelse(palabraRetornada,tipo,pila1);
      }

      else if(valLetra(palabraRetornada) == true && (palabraRetornada != "int" ||palabraRetornada != "float" || palabraRetornada != "double" || palabraRetornada != "cout"|| palabraRetornada != "cin"|| palabraRetornada != "while"|| palabraRetornada != "endwhile"|| palabraRetornada != "if"|| palabraRetornada != "else"|| palabraRetornada != "endif") )
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

    else if ( palabra1[i] == '(' || palabra1[i] == ')' || palabra1[i] == ',' || palabra1[i] == ':'||palabra1[i] == '+'||palabra1[i] == '*'||palabra1[i] == '-'||palabra1[i] == '/'||palabra1[i] == ';')
    {
        letra = palabra1[i];
        palabra2 = palabra2 + letra;
        i++;
    }
    else if( palabra1[i]=='<' ||palabra1[i] =='>'){
        int contCout = 0;
        int contCin = 0;
        while ((palabra1[i] == '<' && contCout != 2)||(palabra1[i]=='>'&&contCin !=2))
        {
            if (palabra1[i] == '<')
                contCout++;

            if (palabra1[i] == '>')
                contCin++;

            letra = palabra1[i];
            palabra2 = palabra2 + letra;
            i++;
        }
      
    }
    else if( palabra1[i]=='=' ||palabra1[i] =='!'){
        int contwhile = 0;
        while (((palabra1[i] == '='||palabra1[i]=='!') && contwhile != 2))
        {
            if (palabra1[i] == '=')
                contwhile++;

            if (palabra1[i] == '!')
                contwhile++;

            letra = palabra1[i];
            palabra2 = palabra2 + letra;
            i++;
        }
    }
    else if( palabra1[i]=='|' ||palabra1[i] =='&'){
        int conto = 0;
        int conty = 0;
        while ((palabra1[i] == '|' && conto!= 2)||(palabra1[i]=='&'&&conty!=2))
        {
            if (palabra1[i] == '|')
                conto++;

            if (palabra1[i] == '&')
                conty++;

            letra = palabra1[i];
            palabra2 = palabra2 + letra;
            i++;
        }
      
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
        if(nmb == ";"){
          q = 5;}
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
    cout<<"LINEA CORRECTA INICIALIZAR"<<endl;
  else if(q == -1){
    cout<<"LINEA INCORRECTA INICIALIZAR"<<endl;
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
    cout<<"LINEA CORRECTA ASIGNACION "<<endl;
  else if(q == -1)
    cout<<"LINEA INCORRECTA ASIGNACION"<<endl;
  }
}
void reconocedorcco(string nmb, char tipo){
    if(q != 100 && q != -1){
        switch(q){
        case 0:
            
            if(nmb == "cout"){
                q = 1;
            }
            else
                q =-1;
        break;
        case 1:
            
            if(nmb == "<<"){

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
            
            if(nmb == "+"||nmb == "*"||nmb == "-"||nmb == "/")
                q = 4;
            else if(nmb ==";")
                q = 5;
            else if(nmb == "<<")
                q = 2;
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
        cout<<"LINEA CORRECTA COUT"<<endl;
    else if(q == -1)
        cout<<"LINEA INCORRECTA COUT"<<endl;
    }   
}
void reconocedorcci(string nmb, char tipo){
if(q != 100 && q != -1){
        switch(q){
        case 0:
            if(nmb == "cin"){
                q = 1;
            }
            else
                q =-1;
        break;
        case 1:
            
            if(nmb == ">>"){

            q = 2;
            }
            else
            q = -1;
        break;
        case 2:
            
            if( valLetra(nmb) == true  && buscador(nmb)==1)
            {
            q = 3;
            }
            else
            q = -1; 
        break;
        case 3:
            
            if(nmb == ">>")
                q = 4;
            else if(nmb ==";")
                q = 5;
            else 
                q = -1;
        break;
        case 4:
            
            if( ((valLetra(nmb) == true ) && buscador(nmb)==1)){
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
        cout<<"LINEA CORRECTA CIN"<<endl;
    else if(q == -1)
        cout<<"LINEA INCORRECTA CIN"<<endl;
    }  
}

void reconocedorWhile(string nmb, char tipo,Nodo *&pila){
  if(t!= -1){
        switch(t){
        case 0:
            if(tipo == 'I' && nmb == "while"&& pila==NULL){
                t = 1;
                agregarPila(pila,nmb);
            }
            else
                t =-1;
        break;
       
      case 1:
      if(nmb=="(")
        t=2;
      else 
        t=-1;
      break;
      case 2:
        if((tipo == 'I' && buscador(nmb) == 1)||( valNumDouble(nmb) == true )){
          t = 3;
        }
        else
          t=-1;
      break;
      case 3:
        if(nmb == "=="|| nmb == "!="|| nmb == "<"|| nmb == ">"){
          t = 4;
        }
        else
          t = -1;
      break;
      case 4:
        if(valNumDouble(nmb) == 1 ||( valLetra(nmb) == true  && buscador(nmb)==1))
        {
          t = 5;
        }
       
        else
          t = -1; 
      break;
      case 5:
        if(nmb == "+"||nmb == "*"||nmb == "-"||nmb == "/"||nmb == "=")
          t = 4;
        else if(nmb =="||"||nmb =="&&")
          t= 2;
        else if(nmb==")")
          t=6;
        else 
          t = -1;
      break;
       case 6:
            if(tipo == 'I' && nmb == "while"&& pila!=NULL){
                t = 1;
                agregarPila(pila,nmb);
            }
            else if(tipo == 'I' && nmb == "endwhile"&& pila->dato=="while"){
                t = 7;
                sacarPila(pila,pila->dato);
            }
            else if(nmb == "$"){
              t=6;
            }
            else
              t = -1;
        break;

          case 7:
            if(tipo == 'I' && nmb == "endwhile"&& pila->dato=="while"){
               t=7;
              sacarPila(pila,pila->dato);
            }
            else if(tipo == 'I' && nmb == "while"&& pila!=NULL){
                t = 1;
                agregarPila(pila,nmb);
            }
            else if(pila == NULL && nmb == "$"){
              cout<<"LINEA CORRECTA WHILE"<<endl;
              if(pila == NULL)
                t=0;  
            }

            else if(nmb == "$"){
              cout<<"LINEA CORRECTA WHILE"<<endl;
              if(pila == NULL)
                t=0;  
            }
            else
            t = -1;
            break;
            }
    if(t == -1)
     cout<<"LINEA INCORRECTA WHILE"<<endl;
    }
}

void reconocedorifelse(string nmb, char tipo,Nodo *&pila1){
  if(u!= -1){
    switch(u){
      case 0:
        if(tipo == 'I' && nmb == "if"&& pila1==NULL){
          u = 1;
          agregarPila(pila1,nmb);
        }
        else
          u =-1;
      break;
    
      case 1:
        if(nmb=="(")
          u=2;
        else 
          u=-1;
      break;

      case 2:
        if((tipo == 'I' && buscador(nmb) == 1)||( valNumDouble(nmb) == true )){
          u= 3;
        }
        else
          u=-1;
      break;

      case 3:
        if(nmb == "=="|| nmb == "!="|| nmb == "<"|| nmb == ">"){
          u = 4;
        }
        else
          u = -1;
      break;

      case 4:
        if(valNumDouble(nmb) == 1 ||( valLetra(nmb) == true  && buscador(nmb)==1)){
          u = 5;
        }
        else
          u = -1; 
      break;

      case 5:
        if(nmb == "+"||nmb == "*"||nmb == "-"||nmb == "/"||nmb == "=")
          u = 4;
        else if(nmb =="||"||nmb =="&&")
          u= 2;
        else if(nmb==")")
          u=6;
        else 
          u = -1;
      break;
      
      case 6:
        if(tipo == 'I' && nmb == "if"&& pila1!=NULL){
          u = 1;
          agregarPila(pila1,nmb);
        }

        else if(tipo == 'I' && nmb == "else"&& pila1->dato=="if"){
            u = 7;
            agregarPila(pila1,nmb);
        }

        else if( nmb == "$"){
            u=6;  
        }
        
        else if(tipo == 'I' && nmb == "endif"&& pila1->dato=="if"){
          u=8;
          sacarPila(pila1,pila1->dato);
        }
        else
          u = -1;
        break;

      case 7:
        if( nmb == "$"){
            u=7;  
        }
         else if(tipo == 'I' && nmb == "endif"&& pila1->dato=="else"){
          u=8;
          sacarPila(pila1,pila1->dato);
          sacarPila(pila1,pila1->dato);
        }
        else if(tipo == 'I' && nmb == "if"&& pila1!=NULL){
          u = 1;
          agregarPila(pila1,nmb);
        }

        else
          u = -1;
        break;
      case 8:
      if(tipo == 'I' && nmb == "if"&& pila1!=NULL){
          u = 1;
          agregarPila(pila1,nmb);
        }  
        else if(tipo == 'I' && nmb == "endif"&& pila1->dato=="if"){
          u=8;
          sacarPila(pila1,pila1->dato);
        } 
        else if(tipo == 'I' && nmb == "endif"&& pila1->dato=="else"){
          u=8;
          sacarPila(pila1,pila1->dato);
          sacarPila(pila1,pila1->dato);
        }
        else if(pila1 == NULL || nmb == "$"){
              cout<<"LINEA CORRECTA CONDICIONAL"<<endl;
              if(pila1 == NULL)
              u=0;  
            }
            else
            u = -1;
            break;
            }
    if(u == -1)
     cout<<"LINEA INCORRECTA"<<endl;
    }
}

void agregarPila (Nodo *&pila,string d){
    Nodo*nuevo_nodo=new Nodo();
    nuevo_nodo->dato=d;
    nuevo_nodo->siguiente=pila;
    pila=nuevo_nodo; 
}

void sacarPila (Nodo *&pila,string d){
    Nodo*aux= pila;
    d=aux->dato;
    pila=aux->siguiente;
    delete aux;
}