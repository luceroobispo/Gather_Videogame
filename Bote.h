#pragma once
#include "Entidad.h"

class Bote : public Entidad {
private:
	int dx;
public:
	Bote() {}
	Bote(int x, int y) : Entidad(x, y) {
		dx = 15;
		ancho = 96;
		alto = 96;
	}
	~Bote() {}

	void setX(int x) { this->x = x; }
	void setDX(int dx) { this->dx = dx; }

	void dibujar(BufferedGraphics^ buffer, Bitmap^ bmp) {
		Rectangle areaSprite = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle escalarPersonaje = Rectangle(x, y, ancho, alto);
		buffer->Graphics->DrawImage(bmp, escalarPersonaje, areaSprite, GraphicsUnit::Pixel);
	}

	void mover(BufferedGraphics^ buffer, Bitmap^ bmp, int anchoForm) {
		if (indiceY >= 0 && indiceY < 4) { indiceY++; }
		else indiceY = 0;
		if (x + dx < 1 || x + ancho + dx > anchoForm - 1) x = 0;
		else x += dx;
		dibujar(buffer, bmp);
	}

	Rectangle getRectanguloBote() {
		return Rectangle(x, y, ancho, alto);
	}
};