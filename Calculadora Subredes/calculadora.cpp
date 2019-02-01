
//calc subnetting clase C con array
#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

using namespace std;

void ordenar(int[], int);
int convert_octeto(string);
void calc(int, string, int[], int);

int main(){
	int num_subredes = 0; 
	int suma = 0;
	string dir_red; // Direccion de red inicial
	int octeto_final; // Es el octeto con el que vamos a operar 

	cout << endl << " Introduzca ip: ";
	cin >> dir_red;
	
	cout << endl << " Cuantas subredes desea crear: ";
	cin >> num_subredes;

	int *posicion = new int[num_subredes]; //Los arrays de tamaño variable se crean asi, si no da errores.

	for (int i = 0; i < num_subredes; i++){ 
		cout << endl << " Introduzca la cantidad de ips de la subred numero " << i + 1 << ": ";
		cin >> posicion[i];
	}
	for (int i = 0; i < num_subredes ; i++){ // Suma la cantidad de subredes
		suma += posicion[i];
	}
	
	if(suma >= (255 - (num_subredes * 2))){ // Comprueba que no se sobrepase el limite quitando 2 ips por cada nueva subred
		cout << " No se pueden asignar tantas direcciones ip.";
		exit(1);
	}

	octeto_final = convert_octeto(dir_red);
	ordenar(posicion, num_subredes);
	calc(octeto_final, dir_red, posicion, num_subredes);

	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),3);
	cout << endl << " Desarrollado por Esteban Segura. https://github.com/estse" << endl;
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),15);

	cin.ignore();
	cin.get();
	return 0;
}

void ordenar(int posicion[], int num_subredes){ // Ordenacion burbuja de mayor a menor ,,, el fallod e que no funcione con mas de 7 subredes puede estar aqui, hacer una irdenacion burbuja inversa aparte y probar con 8 elementos.
	
	int aux;
    
	for (int i = 0; i < num_subredes; i++){
		for (int j = 0; j < num_subredes-1; j++){
			if(posicion[j+1] > posicion[j]){
				aux = posicion[j];
				posicion[j] = posicion[j+1];
				posicion[j+1] = aux;
			}
		}
	}
}

int convert_octeto(string dir_red){ // Obtiene el ultimo octeto de la ip para retornarlo al main y poder operar con el.

	string delimiter = ".";
	string aux;
	int octeto;
	size_t pos;
	dir_red = dir_red + ".";
	
	while ((pos = dir_red.find(delimiter)) != std::string::npos){
    	
    	aux = dir_red.substr(0, pos);
      	
    	dir_red.erase(0, pos + delimiter.length());
	}
	
	octeto = atoi(aux.c_str());

	return octeto;
}

//POR AHORA PIDE LA IP, EL NUMERO DE SUBREDES, EL NUMERO DE IPS POR SUBRED, ORDENA DE MENOR A MAYOR LA CANTIDAD DE IPS y extrae el ultimo octeto en formato int (operable).
void calc(int octeto_final, string dir_red, int posicion[], int num_subredes){
	
	int bits_ocupados = 0;
	string prim_ip;
	string ult_ip;
	string broad_ip;
	string mascara;
	size_t found;
	int octeto2;
//Toma un primer valor del array de numero de ips y lo sustituye en n para ver cual es la potencia de 2 mas cercana mayor o igual al numero de ips pedidas
	for (int i = 0; i < num_subredes; i++)
	{
		octeto_final = octeto_final + bits_ocupados; //Para la direccion de red y primera ip

		if (log2(posicion[i]+2) <= 7 && log2(posicion[i]+2) >= 6){
			bits_ocupados = 128 ;
			mascara = "255.255.255.128";
		}

		if (log2(posicion[i]+2) <= 6 && log2(posicion[i]+2) >= 5){
			bits_ocupados = 64 ;	
			mascara = "255.255.255.192";	
		}	

		if (log2(posicion[i]+2) <= 5 && log2(posicion[i]+2) >= 4){
			bits_ocupados = 32 ;
			mascara = "255.255.255.224";
		}

		if (log2(posicion[i]+2) <= 4 && log2(posicion[i]+2) >= 3){
			bits_ocupados = 16 ;
			mascara = "255.255.255.240";
		}

		if (log2(posicion[i]+2) <= 3 && log2(posicion[i]+2) >= 2){
			bits_ocupados = 8 ;
			mascara = "255.255.255.248";
		}

		if (log2(posicion[i]+2) <= 2 && log2(posicion[i]+2) >= 1){
			bits_ocupados = 4 ;
			mascara = "255.255.255.252";
		}
		
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),10);
		cout << endl << "SUBRED " << i+1 << endl << endl;
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),1);
		cout  << " "<< "IP's SOLICITADAS: " << posicion[i];
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
		cout  << " "<< "   IP's OCUPADAS: " << bits_ocupados << endl << endl;
		 
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),15);
		octeto2 = octeto_final + bits_ocupados; //Para el broadcast y la ultima ip
		//Obtiene la direccion de red, si es la primera se deja como esta, sino se le suman los bits ocupados.
		
		if(i == 0){
			cout << "     " << "DIRECCION DE RED: " << dir_red <<  endl;
			found = dir_red.string::find_last_of(".");
			dir_red = dir_red.substr(0, found) + "." + std::to_string(octeto_final);
		}else{
			found = dir_red.string::find_last_of(".");
			dir_red = dir_red.substr(0, found) + "." + std::to_string(octeto_final);
			cout << "     " << "DIRECCION DE RED: " << dir_red <<  endl;
		}
		
		cout << "                                                                      " << endl;
		cout << "     " << "MASCARA: " << mascara << endl;
		cout << "                                                                      " << endl;
		//Obtiene la primera ip que es el resultado de sumar 1 al ultimo octeto. FUNCIONA
		found = dir_red.string::find_last_of(".");
		prim_ip = dir_red.substr(0, found) + "." + std::to_string(octeto_final+1);
		
		cout << "     " << "PRIMERA IP: "<< prim_ip <<  endl;
		
		cout << "                                                                      " << endl;
		//Obtiene la ultima ip restandole 1 a la de broadcast.FUNCIONA
		ult_ip = dir_red.substr(0, found) + "." + std::to_string(octeto2-2);
		
		cout << "     " << "ULTIMA IP: "<< ult_ip <<  endl;
		
		cout << "                                                                      " << endl;
		//Obtiene la ip de broadcast que es el resultado de restar 1 a la ultima ip. FUNCIONA
		found = dir_red.string::find_last_of(".");
		broad_ip = dir_red.substr(0, found) + "." + std::to_string(octeto2-1);
		
		cout << "     " << "BROADCAST: " << broad_ip <<  endl << endl << endl;
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),15);
	}
}
//falta calcular las mascara de subred