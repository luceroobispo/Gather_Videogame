#pragma once
#include "Entidad.h"
enum DireccionesC { IzquierdaC, DerechaC };

class Carro : public Entidad {
private:
	int dx;
public:
	DireccionesC direccion;
	Carro() {}
	Carro(int x, int y) : Entidad(x,y) {
		direccion = IzquierdaC;
		dx = 20;
		ancho = 66;
		alto = 64;
	}
	~Carro() {}

	int getDX() { return dx; }
	void setDX(int dx) { this->dx = dx; }

	void dibujar(BufferedGraphics^ buffer, Bitmap^ bmp) {
		Rectangle areaSprite = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle escalarPersonaje = Rectangle(x, y, (int)(ancho*1.8), (int)(alto*1.8));
		buffer->Graphics->DrawImage(bmp, escalarPersonaje, areaSprite, GraphicsUnit::Pixel);
	}

	void mover(BufferedGraphics^ buffer, Bitmap^ bmp, int anchoForm) {
		switch (direccion) //Animacion de la imagen
		{
		case IzquierdaC:
			indiceY = 0;
			if (indiceX >= 0 && indiceX < 3) { indiceX++; }
			else indiceX = 0;
			x -= dx; //Movimiento hacia la izquierda en X
			break;

		case DerechaC:
			indiceY = 1;
			if (indiceX >= 0 && indiceX < 3) { indiceX++; }
			else indiceX = 0;
			x += dx; //Traslado hacia la derecha en Y
			break;
		}
		dibujar(buffer, bmp);
	}

	void movimientoIndependiente(BufferedGraphics^ buffer, Bitmap^ bmp, int anchoForm) {
		if (x + dx <= 10 || x + dx + ancho > anchoForm - 10) {
			if (direccion == DireccionesC::DerechaC) {
				direccion = DireccionesC::IzquierdaC;
			}
			else {
				direccion = DireccionesC::DerechaC;
			}
		}
		mover(buffer,bmp,anchoForm);
	}
};