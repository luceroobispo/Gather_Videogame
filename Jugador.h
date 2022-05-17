#pragma once
#include "string"
using namespace std;
class Jugador
{
private:
	int puntos;
	string nombre;
public:
	Jugador() {}
	Jugador(string nombre, int puntos) {
		this->nombre = nombre;
		this->puntos = puntos;
	}
	~Jugador() {}
	int getpuntos() { return puntos; }
	string getnombre() { return nombre; }
	void setpuntos(int puntos) { this->puntos = puntos; }
	void setnombre(string nombre) { this->nombre = nombre; }
};