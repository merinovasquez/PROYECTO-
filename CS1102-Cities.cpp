#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <list>
#include <vector>
#include "City.h"

//1.-inicio:Para map
#include <string>
#include <utility>
#include <map>
//1.-fin:Para map
using namespace std;

void showMenu();
void initializeSeed();
void selection(int);
City addCity();
void deleteCity();
void listTop100();
void listLess10Meters();
void calculateAverageDistance();
void getLongestDistance();
void getShortestDistance();
void listCitiesByStatus();
void changeCityStatus();

void getListFromFile();
void setListToFile();

static list <City> cities;
static list <City>::iterator it;

//2.-inicio:Para map
typedef pair<string, char> componente;
map<string, char> directorio;
//2.-fin:Para map

int main()
{
	string option;
	initializeSeed();
	showMenu();
	cout << endl << endl << "- Opcion: ";
	
	while (true) {
		
		cin >> option;
		system("clear");
		bool saber = isdigit(option[0]);
		showMenu();
		if (saber) {
			selection(option[0]);
			setListToFile();
			cout << endl << endl << "- Opcion: ";
		}
		else 
			cout << "**** Por favor ingrese una opcion valida ****" << endl << "- Opcion: ";		

		if (option[0] == '0') break;
	}
    return 0;
}

void showMenu(){
    
    cout << endl;
	cout << "|--------------------------------------------------------|" << endl;
	cout << "|Menu                                                    |" << endl;
	cout << "|~ ~ ~                                                   |" << endl;
	cout << "|1. Agregar una nueva posicion                           |" << endl;
	cout << "|2. Eliminar una posicion por nombre                     |" << endl;
	cout << "|3. Listar los 100 primeros puntos                       |" << endl;
	cout << "|4. Listar los puntos ubicados a menos de 10 metros      |" << endl;
	cout << "|5. Calcular la distancia promedio entre cada punto      |" << endl;
	cout << "|6. Determinar la distancia entre los puntos mas lejanos |" << endl;
	cout << "|7. Determinar la distancia mas corta entre los puntos   |" << endl;
	cout << "|8. Listar las ciudades por un estado                    |" << endl;
	cout << "|9. Cambiar el estado de una ciudad                      |" << endl;
	cout << "|0. Salir                                                |" << endl;
	cout << "|--------------------------------------------------------|" << endl;
}

void initializeSeed() {
	getListFromFile();
}

void selection(int option)
{
	switch (option){
	case 49: addCity(); break;
	case 50: deleteCity(); break;
	case 51: listTop100(); break;
	case 52: listLess10Meters(); break;
	case 53: calculateAverageDistance(); break;
	case 54: getLongestDistance(); break;
	case 55: getShortestDistance(); break;
	case 56: listCitiesByStatus(); break;
	case 57: changeCityStatus(); break;
	}
}

City addCity() {
	string name;
	float x, y;
	char c;
	cout << "- Ingrese el nombre de la ciudad a crear: "; cin >> name;
	cout << "- Ingrese la coordenada X: "; cin >> x;
	cout << "- Ingrese la coordenada Y: "; cin >> y;
	cout << "- Ingrese el estado: "; cin >> c;
	
	City addedA(name, x, y, c);
	cities.push_back(addedA);
    //inicio:map-inserta datos
    directorio.insert( componente(name, c));
    //fin:map-inserta datos

	return addedA;
}

void deleteCity() {
	string cityName, name;
	cout << "- Ingrese el nombre de la ciudad a eliminar: "; cin >> name;
	//inicio:mapverifica existencia de archivo
    string s=name;
    map<string, char>::iterator p = directorio.find(s);
    if(p!=directorio.end())
    {
    //fin.map-verifica exitencia de registro
        for (it = cities.begin(); it != cities.end(); ++it) {
		    cityName = (*it).getName();
		    if (name.compare(cityName) == 0) {
			    cities.erase(it);
                directorio.erase(s);			    
			    return;
		    }
	    }
   	//inicio:mapverifica existencia de archivo
    }else{
          cout << s << " no esta en el directorio.\n";
          system("pause");
          return;
    }
    //fin.map-verifica exitencia de registro
}

void listTop100() {
	int i = 0;
	for (it = cities.begin(); it != cities.end() && i < 100; ++it) {
		(*it).print();
		i++;
	}
}

void listLess10Meters() {
	for (it = cities.begin(); it != cities.end(); ++it)
		if ((*it).getDistance() < 10)
			(*it).print();	
}

void calculateAverageDistance() {
	float sum = 0;
	for (it = cities.begin(); it != cities.end(); ++it) {
		sum += (*it).getDistance();
	}
	cout << "- Distancia promedio de los puntos es: " << sum / cities.size() << endl;
}

void getLongestDistance() {
	float longest = numeric_limits<float>::min();
	for (list <City>::iterator it_i = cities.begin(); it_i != cities.end(); ++it_i) {
		for (list <City>::iterator it_j = cities.begin(); it_j != cities.end(); ++it_j)
			if ((*it_i).getDistanceByCity(*it_j) > longest)
				longest = (*it_i).getDistanceByCity(*it_j);
	}
	cout << "- Distancia mas lejana entre ciudades: " << longest << endl;
}

void getShortestDistance() {
	float shortest = numeric_limits<float>::max();
	for (list <City>::iterator it_i = cities.begin(); it_i != cities.end(); ++it_i) {
		for (list <City>::iterator it_j = cities.begin(); it_j != cities.end(); ++it_j)
			if ((*it_i).getDistanceByCity(*it_j) < shortest && (*it_i).getDistanceByCity(*it_j) > 0)
				shortest = (*it_i).getDistanceByCity(*it_j);
	}
	cout << "- Distancia mas cercana entre ciudades: " << shortest << endl;
}

void listCitiesByStatus() {
	char status;
	cout << "- Ingrese el estado de la ciudad a listar: "; cin >> status;
	for (it = cities.begin(); it != cities.end(); ++it)		
		if ((*it).getStatus() == status)
			(*it).print();
	return;
}

void changeCityStatus() {
	char status;
	string name, cityName;
	cout << "- Ingrese el nombre de la ciudad a modificar: "; cin >> name;
	cout << endl << "- Ingrese el nuevo estado: "; cin >> status;
	
	for (it = cities.begin(); it != cities.end(); ++it) {
		cityName = (*it).getName();
		if (name.compare(cityName) == 0) {
			(*it).setStatus(status);
			return;
		}
	}
}

void getListFromFile() {
	ifstream file("Ciudades.txt");
	string name, line;
	float x, y;
	char c;
	
	if (file.is_open()) {
		cities.clear();
		while (getline(file, name, ','))
		{
			getline(file, line, ',');
			x = atof(line.c_str());
			getline(file, line, ',');
			y = atof(line.c_str());
			getline(file, line, '\n');
			c = line[0];
			City add(name, x, y, c);
			cities.push_back(add);
            //inicio:map-Inicializa con datos
            directorio.insert( componente(name, c));
            //fin:map-Inicializa con datos
		}
	}
	else cout << "No se pudo abrir el archivo de ciudades (Ciudades.csv)" << endl;
	file.close();
}

void setListToFile() {
	ofstream file("Ciudades.txt");
	string name, line;
	float x, y;
	char c;

	if (file.is_open()) {
		for (it = cities.begin(); it != cities.end(); ++it)
			file << (*it).getName() << ',' << (*it).getX() << ',' << (*it).getY() << ',' << (*it).getStatus() << endl;
	}
	file.close();
}


