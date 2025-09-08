#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <stdexcept>
#include <string>

using namespace std;

void gotoxy(short x, short y);
void logoBienvenida();
bool bienvenido();
int clave(int);
void menu();
void menuCargaRecetas(bool &);
void menuConsultarRecetas(bool &);
void menuSalir(bool&);
bool legajoValido(int& legajo);
bool validarLegajo(string legajo);
bool claveValida(int legajo);

int main(){
	
	int legajo = 0;
	
	system("color E9");
	logoBienvenida();
	if(bienvenido()){
		//limpar pantalla
		//ingreso para continuar
		system("cls");
		
		system("cls");
		if (legajoValido(legajo)){
			if(claveValida(legajo)) menu();
			else cout << "Alcanzo el limite de intentos (3) \n";
		}
		else cout << "Alcanzo el limite de intentos\n";
	}
	return 0;
}
void goToXY(short x, short y) {
	COORD cp = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cp);
}

void logoBienvenida(){
	//sonido bienvenida se puede sacar si no les gusta
	cout<< '\a';
	Sleep(5);
	cout<< '\a';
	cout<< '\a';
	cout<< '\a';
	//aca termina el bloque de sonido si quieren tambien se puede cambiar el ritmo
	
	
	int x = 0, y = 0;
	//funcion logo
	// Letra M
	for (int i = 0; i < 5; i++) {
		goToXY(x, y + i); cout << "#";
		goToXY(x + 4, y + i); cout << "#";
	}
	goToXY(x + 1, y + 1); cout << "#";
	goToXY(x + 2, y + 2); cout << "#";
	goToXY(x + 3, y + 1); cout << "#";
	
	x += 7; // espacio entre letras
	
	// Letra E
	for (int i = 0; i < 5; i++) goToXY(x, y + i), cout << "#";
	for (int i = 0; i < 5; i++) goToXY(x + i, y), cout << "#";
	for (int i = 0; i < 3; i++) goToXY(x + i, y + 2), cout << "#";
	for (int i = 0; i < 5; i++) goToXY(x + i, y + 4), cout << "#";
	
	x += 7;
	
	// Letra N
	for (int i = 0; i < 5; i++) {
		goToXY(x, y + i); cout << "#";
		goToXY(x + 4, y + i); cout << "#";
		goToXY(x + i, y + i); cout << "#";
	}
	
	x += 7;

	// Letra U
	for (int i = 0; i < 4; i++) {
		goToXY(x, y + i); cout << "#";
		goToXY(x + 4, y + i); cout << "#";
	}
	for (int i = 1; i < 4; i++) goToXY(x + i, y + 4), cout << "#";
	
	x += 7;
	
	// Letra T
	for (int i = 0; i < 5; i++) goToXY(x + i, y), cout << "#";
	for (int i = 1; i < 5; i++) goToXY(x + 2, y + i), cout << "#";
	
	x += 7;
	
	// Letra N (repetida)
	for (int i = 0; i < 5; i++) {
		goToXY(x, y + i); cout << "#";
		goToXY(x + 4, y + i); cout << "#";
		goToXY(x + i, y + i); cout << "#";
	}
}
bool bienvenido(){
	//VK_ESCAPE
	bool valido=false;
	cout <<endl<<endl<< "Pulse espacio para continuar";
	
	char login=_getch();
	
	while(login != VK_SPACE){
		login=_getch();
	}
	if(login == VK_SPACE){
		valido = true;
	}
	
	return valido;
}

int clave(int legajo){
	//se puede implementar arreglos para no tener tantas variables
	int d1 = legajo/10000;
	int d2 = (legajo/100)%10;
	int d3 = (((legajo/10)/10)%10);
	int d4 = ((legajo/10)%10);
	int d5 = (legajo%10);
	
	
	int N = d1*100 + d2*10 + d5;
	
	int sumaUltimos3 = d3*100+d4*10+d5;
	int sumaPrimos = 0;
	
	int year;
	int limite;
	
	time_t timestamp = time(&timestamp);
	struct tm datetime = *localtime(&timestamp);
	
	year= 1900 + datetime.tm_year;
	limite=((year/10)%10);
	limite= limite * 10 + year%10;
	
	//i empieza en 2 i tiene que ser menor que limite
	int i=2;
	int k=2;
	while(i<limite){
		bool esPrimo = true;
		while(k<=i/2 and esPrimo){
			if (i%k == 0) esPrimo = false;
			k++;
		}
		if (esPrimo) sumaPrimos += i;
		i++;
		k=2;
	}
	//contraseña = (N + suma_de_primos) * 1000 + ultimos_3_digitos_del_legajo
	return ((N + sumaPrimos) * 1000 + sumaUltimos3);
}
void menu(){
	char opcion;
	bool finalizar = false;
	bool salir = false;
	
	system("cls");
	
	do {
		 finalizar = false;
		 salir = false;
	cout<<"Recetario Familiar"<<endl;
	cout<<"=================="<<endl;
	cout<<"1. Cargar Recetas "<<endl;
	cout<<"2. Consultar Recetarias"<<endl;
	cout<<"X. Salir de la aplicacion"<<endl;
	cout<<endl<<"Ingrese una opcion: ";
	cin >> opcion; 
	while (opcion != '1' and opcion != '2' and opcion != 'X' and opcion != 'x'){
		cout<<"Opcion invalida, intente nuevamente: ";
		cin>>opcion;
	}
		switch(opcion){
		case '1':
			system("cls");
			menuCargaRecetas(finalizar);
			break;
		case '2':
			system("cls");
			menuConsultarRecetas(finalizar);
			break;
		case 'X':
		case 'x':
			system("cls");
			if(!salir) menuSalir(salir);
			break;
		}
	}while (!finalizar and !salir);
}
void menuCargaRecetas(bool & finalizar){
	char opcionElegida;
	bool finalizarBucle = false;
	
	system("cls");
	
	cout << "Menú Carga de Recetas" << endl;      
	cout << "==========================" << endl;         
	cout << "1.- Cargar por Tipo de Plato" << endl;       
	cout << "2.- Cargar por Ingredientes" << endl;       
	cout << "3.- Cargar Receta Individual" << endl;       
	cout << "4.- Cargar Receta de Tradición Familiar" << endl;         
	cout << "5.- Cargar por Región de Origen" << endl;        
	cout << "X.- Volver al menú principal" << endl;
	
	cout<<"Ingrese opcion: ";
	cin>>opcionElegida;
	
	while(!finalizarBucle){
		
		switch(opcionElegida){
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
			finalizarBucle = true;
			finalizar = true;
			system ("cls");
			cout<<"Funcionalidad en desarrollo"<<endl;
			break;
		case 'x':
		case 'X':
			system("cls");
			finalizarBucle = true;
			break;
		default:
		cout<<"Opcion invalida, intente nuevamente: ";
		cin>>opcionElegida;
		break;
	}
}
}
void menuConsultarRecetas(bool & finalizar){
	bool terminarBucle = false;
	char opcionSeleccionada;
	
	system("cls");

	cout << "Menú de Consultas" << endl;        
	cout << "==========================" << endl;          
	cout << "1.- Recetas por Tipo de Plato" << endl;         
	cout << "2.- Recetas por Ingrediente" << endl;       
	cout << "3.- Recetas Favoritas del Usuario" << endl;        
	cout << "X.- Volver al menú principal" << endl;           
	cout<<"Ingrese opcion: ";
	cin >> opcionSeleccionada;
	
	while(!terminarBucle){
		switch(opcionSeleccionada){
		case '1':
		case '2':
		case '3':
			terminarBucle = true;
			finalizar = true;
			system ("cls");
			cout<<"Funcionalidad en desarrollo"<<endl;
			break;
		case 'x':
		case 'X':
			system("cls");
			terminarBucle = true;
			break;
		default:
			cout<<"Opcion invalida, intente nuevamente: ";
			cin>>opcionSeleccionada;
			break;
		}
	}
}
void menuSalir(bool& salir){
	
	char opcionIndicada;
	bool termino = false;
	
	system("cls");
	
	cout<<"Desea confirmar la salida?"<<endl;
	cout << "==========================" << endl; 
	cout<<"1. Volver al menu principal"<<endl;
	cout<<"2. Salir de la aplicacion"<<endl;
	cout<<"Ingrese opcion: ";
	cin>>opcionIndicada;

	while(!termino){		
		switch (opcionIndicada){
		case '1':
			system("cls");
			termino = true;
			break;
		case '2':
			system("cls");
			cout<<"Gracias por utilizar nuestra aplicacion :)"<<endl;
			salir = true;
			termino = true;
			break;
		default:
			cout<<"Opcion invalida, intente nuevamente: ";
			cin>>opcionIndicada;
			break;
		}
	}
}

bool validarLegajo(string legajo){
	
	bool result = false;
	

	if(legajo.length() == 5 && legajo[0] != 0){
		result = true;
		
		for(int i = 0; i < 5; i++){
			if(legajo[i]<48 || legajo[i]>57){
				
				cout<<"Errore en el caracter i = "<<i<<" : "<<legajo[i]<<endl;
				result = false;
			}
		}
		
	}
	
	return result;
	
}
bool legajoValido(int& legajo){
	
	int cont = 0;
	string str_legajo;
	bool result = false;
	
	do{
		
		cout << "Ingrese numero de legajo: ";
		cout << "Los legajos validos son numeros de 5 cifras en el rango [10000..99999]" <<endl;
			
			cin>>str_legajo;
			
			if(!validarLegajo(str_legajo)){
				cout<<"\n\nNumero de legajo invalido \n";
			}
			else result = true;
			
			cont++;
		
	}while(!result && cont < 3);
	
	if(result == true) legajo = stoi(str_legajo);
	
	return result;
	
}

bool claveValida(int legajo){
	
	int password, cont = 0;
	bool result = false;
	
	do{
		
		cout << "Ingrese su clave: ";
		cin>>password;
		
		if(password!=clave(legajo)){
			cout<<"\n\nclave invalida, ingrese nuevamente\n";
			cont++;
			cout<<"Intentos restantes: " << (3-cont) <<endl;
		}
		else result = true;
		
		cin.clear();
		cin.ignore();
		
	}while(!result && cont < 3);
	
	return result;
}
