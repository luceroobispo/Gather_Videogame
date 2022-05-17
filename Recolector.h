#pragma once
#include "Entidad.h"
enum DireccionesR { Ninguna, Abajo, Arriba, Izquierda, Derecha };

class Recolector : public Entidad {
private:
	int dx, dy;
	int vidas;
	int puntosTotales;
	int puntosCalle;
	int puntosPlaya;
	int puntosMar;
	DireccionesR ultimaTecla;
public:
	
	DireccionesR direccion;
	Recolector() {}
	Recolector(int x, int y) : Entidad(x,y) {
		dx = dy = 0;
		vidas = 3;
		puntosTotales = 0;
		puntosCalle = 0;
		puntosPlaya = 0;
		puntosMar = 0;
		ultimaTecla = Abajo;
		direccion = Ninguna;
		ancho = 54; //864 entre 16
		alto = 54; //54
	}
	~Recolector() {}

	//GETTERS
	int getVidas() { return vidas; }
	int getPuntosTotales() { return puntosTotales; }
	int getPuntosCalle() { return puntosCalle; }
	int getPuntosPlaya() { return puntosPlaya; }
	int getPuntosMar() { return puntosMar; }

	//SETTERS
	void setVidas(int vidas) { this->vidas = vidas; }
	void setPuntosTotales(int puntosTotales) { this->puntosTotales = puntosTotales; }
	void setPuntosCalle(int puntosCalle) { this->puntosCalle = puntosCalle; }
	void setPuntosPlaya(int puntosPlaya) { this->puntosPlaya = puntosPlaya; }
	void setPuntosMar (int puntosMar) { this->puntosMar = puntosMar; }

	void AumentarPuntosCalle() { puntosCalle++; }
	void AumentarPuntosPlaya() { puntosPlaya++; }
	void AumentarPuntosMar() { puntosMar++; }
	void AumentarPuntosTotales() { puntosTotales++; }

	void dibujar(BufferedGraphics^ buffer, Bitmap^ bmp) {
		Rectangle areaSprite = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle escalarPersonaje = Rectangle(x, y, (int)(ancho*0.9), (int)(alto*0.9));
		buffer->Graphics->DrawImage(bmp, escalarPersonaje, areaSprite, GraphicsUnit::Pixel);
		x += dx;
		y += dy;
	}

	void mover(BufferedGraphics^ buffer, Bitmap^ bmp, int anchoform, int altoform, bool conf) {
		switch (direccion) //Animacion de la imagen
		{
		case Arriba:
			if (indiceX >= 4 && indiceX < 7) { indiceX++; }
			else indiceX = 4;
			if (y + dy <= 3 || y + alto + dy > altoform - 3) dy *= -1;
			else if (conf == false) dy = -25;
			else dy = -15;//Movimiento hacia arriba en Y
			dx = 0;
			ultimaTecla = Arriba;
			break;

		case Abajo:
			if (indiceX >= 0 && indiceX < 3) { indiceX++; }
			else indiceX = 0;
			if (y + dy < 3 || y + alto + dy > altoform - 3) dy *= -1;
			else if (conf == false)dy = 25;
			else dy = 15; //Movimiento hacia abajo en Y
			dx = 0;
			ultimaTecla = Abajo;
			break;

		case Izquierda:
			if (indiceX >= 8 && indiceX < 11) { indiceX++; }
			else indiceX = 8;
			if (x + dx < 3 || x + ancho + dx > anchoform - 3) dx *= -1;
			else if (conf == false)dx = -25;
			else dx = -15; //Movimiento hacia la izquierda en X
			dy = 0;
			ultimaTecla = Izquierda;
			break;

		case Derecha:
			if (indiceX >= 12 && indiceX < 15) { indiceX++; }
			else indiceX = 12;
			if (x + dx <= 3 || x + ancho + dx > anchoform - 3) dx *= -1;
			else if (conf == false)dx = 25;
			else dx = 15; //Traslado hacia la derecha en X
			dy = 0;
			ultimaTecla = Derecha;
			break;

		case Ninguna:
			dx = 0;
			dy = 0;
			switch (ultimaTecla)
			{
			case Arriba:
				indiceX = 4;
				break;
			case Abajo:
				indiceX = 0;
				break;
			case Izquierda:
				indiceX = 8;
				break;
			case Derecha:
				indiceX = 12;
				break;
			}
			break;
		}
		dibujar(buffer, bmp);
	}
};
