#pragma once
#include "Entidad.h"

class Bonus : public Entidad
{
public:
	Bonus() {}
	Bonus(int x, int y) : Entidad(x, y) {
		ancho = 242;
		alto = 242;
	}

	~Bonus() {}

	void dibujar(BufferedGraphics^ buffer, Bitmap^ bmp) {
		Rectangle areaSprite = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle escalarPersonaje = Rectangle(x, y, (int)(ancho * 0.1), (int)(alto * 0.1));
		buffer->Graphics->DrawImage(bmp, escalarPersonaje, areaSprite, GraphicsUnit::Pixel);
	}
};