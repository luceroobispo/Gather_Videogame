#pragma once
#include "Entidad.h"

class Transeunte : public Entidad{
private:
	int dx;
public:
	Transeunte() {}
	Transeunte(int x, int y) : Entidad (x,y) {
		dx = 10;
		ancho = 96;
		alto = 96;
	}
	~Transeunte() {}

	int getX() { return x; }
	int getY() { return y; }
	void setX(int x) { this->x = x; }
	void setDX(int dx) { this->dx = dx; }

	void dibujar(BufferedGraphics^ buffer, Bitmap^ bmp) {
		Rectangle areaSprite = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle escalarPersonaje = Rectangle(x, y, (int)(ancho*0.7), (int)(alto * 0.7));
		buffer->Graphics->DrawImage(bmp, escalarPersonaje, areaSprite, GraphicsUnit::Pixel);
	}

	void mover(BufferedGraphics^ buffer, Bitmap^ bmp, int anchoForm) {
		if (indiceY >= 0 && indiceY < 3) { indiceY++; }
		else indiceY = 0;
		if (x + dx < 0 || x + ancho + dx > anchoForm) x = 0;
		else x += dx;
		dibujar(buffer, bmp);
	}

	Rectangle getRectanguloTranseunte() {
		return Rectangle(x, y, ancho*0.7, alto*0.7);
	}
};