#pragma once
#include "Entidad.h"

class BoteVidrio : public Entidad
{
public:
	BoteVidrio() {}
	BoteVidrio(int x, int y) : Entidad (x,y) {
		alto = 96;
		ancho = 96;
	}
	~BoteVidrio() {}

	void dibujar(BufferedGraphics^ buffer, Bitmap^ bmp) {
		Rectangle areaSprite = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle escalarPersonaje = Rectangle(x, y, (int)(ancho * 0.8), (int)(alto * 0.8));
		buffer->Graphics->DrawImage(bmp, escalarPersonaje, areaSprite, GraphicsUnit::Pixel);
	}
};