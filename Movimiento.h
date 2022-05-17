#pragma once

enum Direcciones { Ninguna, Izquierda, Derecha, Arriba, Abajo };

class Movimiento {
private:
public:
	Direcciones ultimaTecla;
	Direcciones direccion;
	Movimiento() {
		ultimaTecla = Abajo;
		direccion = Ninguna;
	}
	~Movimiento(){}
};