#pragma once
#include "Entidad.h"

class Papel : public Entidad
{
private:
	bool cerca;

public:
	Papel() {}
	Papel(int x, int y) : Entidad(x, y) {
		ancho = 96;
		alto = 96;
		cerca = false;
	}

	~Papel() {}

	//GETTERS
	bool getCerca() { return cerca; }

	//SETTERS
	void setCerca(bool cerca) { this->cerca = cerca; }

	void dibujar(BufferedGraphics^ buffer, Bitmap^ bmp) {
		Rectangle areaSprite = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle escalarPersonaje = Rectangle(x, y, (int)(ancho / 3), (int)(alto / 3));
		buffer->Graphics->DrawImage(bmp, escalarPersonaje, areaSprite, GraphicsUnit::Pixel);
	}
};