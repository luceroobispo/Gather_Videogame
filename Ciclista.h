#pragma once
#include "Entidad.h"
enum DireccionesCi { IzquierdaCi, DerechaCi };

class Ciclista : public Entidad {
private:
	int dx;
public:
	DireccionesCi direccion;
	Ciclista() {}
	Ciclista(int x, int y): Entidad (x,y) {
		dx = 10;
		ancho = 96;
		alto = 103;
		direccion = DerechaCi;
	}
	~Ciclista() {}

	int getDX() { return dx; }
	void setDX(int dx) { this->dx = dx; }

	void dibujar(BufferedGraphics^ buffer, Bitmap^ bmp) {
		Rectangle areaSprite = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle escalarPersonaje = Rectangle(x, y, (int)(ancho * 0.7), (int)(alto * 0.7));
		buffer->Graphics->DrawImage(bmp, escalarPersonaje, areaSprite, GraphicsUnit::Pixel);
	}

	void mover(BufferedGraphics^ buffer, Bitmap^ bmp, int anchoForm) {
		switch (direccion) //Animacion de la imagen
		{
		case IzquierdaCi:
			indiceY = 0;
			if (indiceX >= 0 && indiceX < 3) { indiceX++; }
			else indiceX = 0;
			x -= dx; //Movimiento hacia la izquierda en X
			break;

		case DerechaCi:
			indiceY = 1;
			if (indiceX >= 0 && indiceX < 3) { indiceX++; }
			else indiceX = 0;
			x += dx; //Traslado hacia la derecha en Y
			break;
		}
		dibujar(buffer, bmp);
	}

	void movimientoIndependiente(BufferedGraphics^ buffer, Bitmap^ bmp, int anchoForm) {
		if (x + dx < 3 || x + dx + ancho > anchoForm - 3) {
			if (direccion == DireccionesCi::DerechaCi) {
				direccion = DireccionesCi::IzquierdaCi;
			}
			else {
				direccion = DireccionesCi::DerechaCi;
			}
		}
		mover(buffer, bmp, anchoForm);
	}
};