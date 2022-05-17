#pragma once
#include "Entidad.h"

class Botella : public Entidad 
{
private:
	bool cerca;

public:
	Botella() {}
	Botella(int x, int y) : Entidad (x, y) {
		ancho = 265;
		alto = 265;
		cerca = false;
	}

	~Botella() {}

	//GETTERS
	bool getCerca() { return cerca; }

	//SETTERS
	void setCerca(bool cerca) { this->cerca = cerca; }

	void dibujar(BufferedGraphics^ buffer, Bitmap^ bmp) {
		Rectangle areaSprite = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle escalarPersonaje = Rectangle(x, y, ancho/6, alto/6);
		buffer->Graphics->DrawImage(bmp, escalarPersonaje, areaSprite, GraphicsUnit::Pixel);
	}
};