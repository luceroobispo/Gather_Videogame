#pragma once
#include <iostream>
using namespace System::Drawing;

class Entidad {
protected:
	int x, y;
	int ancho, alto;
	int indiceX, indiceY;

public:
	Entidad() {}
	Entidad(int x, int y) {
		this->x = x;
		this->y = y;
		indiceX = 0;
		indiceY = 0;
	}
	~Entidad() {}

	int getX() { return x; }
	int getY() { return y; }
	int getAncho() { return ancho; }
	int getAlto() { return alto; }
	void setX(int x) { this->x= x; }
	void setY(int y) { this->y= y; }

	virtual void dibujar(BufferedGraphics^ buffer, Bitmap^ bmp) {};

	Rectangle getRectangulo() {
		if (ancho == 96 && alto == 96) return Rectangle(x, y, (int)(ancho / 3), (int)(alto / 3)); //rectangulo de los desechos y botes de basura
		else
			if (ancho == 242 && alto == 242) return Rectangle (x, y, (int)(ancho * 0.1), (int)(alto * 0.1)); //rectangulo del bonus
			else
				if (ancho==265 && alto==265) return Rectangle(x, y, (int)(ancho / 6), (int)(alto / 6)); //rectangulo de la botella
				else
					if (ancho==96 && alto==103) return Rectangle(x, y, (int) (ancho * 0.8), (int) (alto * 0.8)); //rectangulo del ciclista
					else
						return Rectangle(x, y, ancho, alto);
	}
};