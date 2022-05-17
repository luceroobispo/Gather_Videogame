#pragma once
#include "Entidad.h"

class Vida : public Entidad
{
public:
	Vida() {}
	Vida(int x, int y) : Entidad(x, y) {
		ancho = 50;
		alto = 52;
	}

	~Vida() {}

	void dibujar(BufferedGraphics^ buffer, Bitmap^ bmp) {
		Rectangle areaSprite = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle escalarPersonaje = Rectangle(x, y, (int)(ancho * 0.5 ), (int)(alto * 0.5));
		buffer->Graphics->DrawImage(bmp, escalarPersonaje, areaSprite, GraphicsUnit::Pixel);
	}
};