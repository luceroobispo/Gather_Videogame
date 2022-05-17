#pragma once
#include "Recolector.h"
#include "Botella.h"
#include "Papel.h"
#include "Carton.h"
#include "BoteVidrio.h"
#include "BotePapel.h"
#include "BoteCarton.h"
#include "Carro.h"
#include "Ciclista.h"
#include "Transeunte.h"
#include "Vida.h"
#include "Bonus.h"
#include "Bote.h"
#include <iostream>
#include <vector>

using namespace std;

class Juego {
private:
	Recolector* recolector;
	vector<Botella*> ArrBotella;
	vector<Carton*> ArrCarton;
	vector <Transeunte*> ArrTranseunte;
	vector<Papel*> ArrPapel;
	Carro* carro1; Carro* carro2;
	Ciclista* ciclista1; Ciclista* ciclista2;
	BoteVidrio* botevidrio;
	BotePapel* botepapel;
	BoteCarton* botecarton;
	vector<Bonus*> ArrBonus;
	vector<Vida*> ArrVidas;
	vector <Bote*> ArrBote;

	//Otros
	int nivel;
	bool BotellaAgarrada, PapelAgarrada, CartonAgarrada;
	bool ObjetoAgarrado;
	int posicionXObjetoAgarrado, posicionYObjetoAgarrado;
	bool GanasteJuegoCalle, GanasteJuegoCallePuntosExtras, GanasteJuegoMar, GanasteJuegoPlaya;
	bool FinJuego;
	bool ColisionConEnemigo, colisionoConBonus;
	clock_t crono;

public:
	Juego(int nivel) {
		//Personaje principal
		recolector = new Recolector(4, 4);
		//Enemigos
		carro1 = new Carro(5 + rand() % 601 - 5, 115);
		ciclista1 = new Ciclista(5 + rand() % 101 - 5, 240);
		carro2 = new Carro(5 + rand() % 601 - 5, 420);
		ciclista2 = new Ciclista(5 + rand() % 101 - 5, 510);
		//Objetos
		switch (nivel) {
		case 1:
			//Enemigos
			carro1 = new Carro(5 + rand() % 601 - 5, 115);
			ciclista1 = new Ciclista(5 + rand() % 101 - 5, 240);
			carro2 = new Carro(5 + rand() % 601 - 5, 420);
			ciclista2 = new Ciclista(5 + rand() % 101 - 5, 510);
			//Objetos
			for (int i = 0; i < 15; i++) {
				ArrBotella.push_back(new Botella(20 + rand() % 700 - 20, 20 + rand() % 600 - 20));
			}
			botevidrio = new BoteVidrio(850, 600);
			//Vida
			ArrVidas.push_back(new Vida(750, 30));
			ArrVidas.push_back(new Vida(750+40, 30));
			ArrVidas.push_back(new Vida(750+80, 30));
			break;

		case 2:
			//Enemigos
			for (int i = 0; i < 5; i++) {
				ArrTranseunte.push_back(new Transeunte(5 + rand() % 601 - 5, 30 + rand() % 600 - 30));
			}
			//Objetos
			for (int i = 0; i < 10; i++) {
				ArrBotella.push_back(new Botella(20 + rand() % 700 - 20, 20 + rand() % 600 - 20));
			}
			for (int i = 0; i < 10; i++) {
				ArrCarton.push_back(new Carton(20 + rand() % 700 - 20, 20 + rand() % 600 - 20));
			}
			botevidrio = new BoteVidrio(850, 600);
			botecarton = new BoteCarton(25, 600);
			//Vida
			ArrVidas.push_back(new Vida(750, 30));
			ArrVidas.push_back(new Vida(750 + 40, 30));
			ArrVidas.push_back(new Vida(750 + 80, 30));
			ArrVidas.push_back(new Vida(750 + 120, 30));
			recolector->setVidas(4);
			break;

		case 3:
			//Enemigos
			for (int i = 0; i < 3; i++)
			{
				ArrBote.push_back(new Bote(5 + rand() % 601 - 5, 30 + rand() % 600 - 30));
			}

			//Objetos
			for (int i = 0; i < 5; i++) {
				ArrBotella.push_back(new Botella(20 + rand() % 700 - 20, 20 + rand() % 600 - 20));
			}
			for (int i = 0; i < 10; i++) {
				ArrCarton.push_back(new Carton(20 + rand() % 700 - 20, 20 + rand() % 600 - 20));
			}
			for (int i = 0; i < 10; i++) {
				ArrPapel.push_back(new Papel(20 + rand() % 700 - 20, 20 + rand() % 600 - 20));
			}
			botevidrio = new BoteVidrio(850, 600);
			botecarton = new BoteCarton(25, 600);
			botepapel = new BotePapel(425, 600);

			//Vida
			ArrVidas.push_back(new Vida(750, 30));
			ArrVidas.push_back(new Vida(750 + 40, 30));
			ArrVidas.push_back(new Vida(750 + 80, 30));
			ArrVidas.push_back(new Vida(750 + 120, 30));
			ArrVidas.push_back(new Vida(750 + 160, 30));
			recolector->setVidas(4);
			break;
		}


		//Otros
		crono = clock();
		BotellaAgarrada = PapelAgarrada = CartonAgarrada = false;
		ObjetoAgarrado = false;
		this->nivel = nivel;
		ColisionConEnemigo = colisionoConBonus = false;
		posicionXObjetoAgarrado = posicionYObjetoAgarrado = 0;
		GanasteJuegoCalle = GanasteJuegoCallePuntosExtras = GanasteJuegoMar = GanasteJuegoPlaya = false;
		FinJuego = false;
	}
	~Juego() {}

	clock_t getcrono() {
		return ((clock() - crono) / CLOCKS_PER_SEC);
	}

	void AgregarBonus() {
		Bonus* _b = new Bonus(20 + rand() % 800 - 20, 20 + rand() % 600 - 20); //posicion random
		ArrBonus.push_back(_b);
	}

	void EliminarBonus() {
		for (unsigned int i = 0; i < ArrBonus.size(); i++) {
			ArrBonus.erase(ArrBonus.begin() + i);
		}
		colisionoConBonus = false;
	}

	void DibujarTodoCalle(BufferedGraphics^ bg, Bitmap^ bmpBote, Bitmap^ bmpVida, Bitmap^ bmpBonus) {
		bg->Graphics->DrawString("PUNTOS: " + recolector->getPuntosCalle(), gcnew Font("Goudy Stout", 12), Brushes::Black, 750, 55);
		bg->Graphics->DrawString("TIEMPO: " + getcrono() + "/120", gcnew Font("Goudy Stout", 11), Brushes::Black, 750, 75);
		botevidrio->dibujar(bg, bmpBote);
		for (unsigned int i = 0; i < ArrVidas.size(); i++) {
			ArrVidas[i]->dibujar(bg, bmpVida);
		}
		for (unsigned int i = 0; i < ArrBonus.size(); i++) {
			ArrBonus[i]->dibujar(bg, bmpBonus);
		}
	}

	void DibujarTodoPlaya(BufferedGraphics^ bg, Bitmap^ bmpBoteVidrio, Bitmap^ bmpBoteCarton, Bitmap^ bmpVida, Bitmap^ bmpBonus) {
		bg->Graphics->DrawString("PUNTOS: " + recolector->getPuntosPlaya(), gcnew Font("Goudy Stout", 12), Brushes::Black, 750, 55);
		bg->Graphics->DrawString("TIEMPO: " + getcrono() + "/180", gcnew Font("Goudy Stout", 11), Brushes::Black, 750, 75); //CAMBIAR LA VARIABLE CRONO PARA LA EL NIVEL 2
		botevidrio->dibujar(bg, bmpBoteVidrio);
		botecarton->dibujar(bg, bmpBoteCarton);
		for (unsigned int i = 0; i < ArrVidas.size(); i++) {
			ArrVidas[i]->dibujar(bg, bmpVida);
		}
		for (unsigned int i = 0; i < ArrBonus.size(); i++) {
			ArrBonus[i]->dibujar(bg, bmpBonus);
		}
	}

	void DibujarTodoMar(BufferedGraphics^ bg, Bitmap^ bmpBoteVidrio, Bitmap^ bmpBoteCarton, Bitmap^ bmpBotePapel, Bitmap^ bmpVida, Bitmap^ bmpBonus) {
		bg->Graphics->DrawString("PUNTOS: " + recolector->getPuntosMar(), gcnew Font("Goudy Stout", 12), Brushes::Black, 750, 55); //CAMBIAR LA VARIABLE CRONO PARA LA EL NIVEL 3
		bg->Graphics->DrawString("TIEMPO: " + getcrono() + "/240", gcnew Font("Goudy Stout", 11), Brushes::Black, 750, 75);
		botevidrio->dibujar(bg, bmpBoteVidrio);
		botecarton->dibujar(bg, bmpBoteCarton);
		botepapel->dibujar(bg, bmpBotePapel);
		for (unsigned int i = 0; i < ArrVidas.size(); i++) {
			ArrVidas[i]->dibujar(bg, bmpVida);
		}
		for (unsigned int i = 0; i < ArrBonus.size(); i++) {
			ArrBonus[i]->dibujar(bg, bmpBonus);
		}
	}

	void moverTodoCalle(BufferedGraphics^ buffer, Bitmap^ bmpR, Bitmap^ bmpC, Bitmap^ bmpCi, Bitmap^ bmpBotella, int anchoform, int altoform) {
		if (BotellaAgarrada == true) ObjetoAgarrado = true;
		else ObjetoAgarrado = false;

		recolector->mover(buffer, bmpR, anchoform, altoform, ObjetoAgarrado);  // si tiene un objeto agarrado, el recolector se vuelve mas lento
		for (unsigned int i = 0; i < ArrBotella.size(); i++) {
			if (ArrBotella[i]->getCerca() == false) ArrBotella[i]->dibujar(buffer, bmpBotella);
			else
				if (ArrBotella[i]->getCerca() == true && ColisionConEnemigo == true) {
					ArrBotella[i]->setCerca(false);
					BotellaAgarrada = false;
					ArrBotella[i]->setX(posicionXObjetoAgarrado);
					ArrBotella[i]->setY(posicionYObjetoAgarrado);
					ArrBotella[i]->dibujar(buffer, bmpBotella);
				}
				else
					if (ArrBotella[i]->getCerca() == true && ColisionConEnemigo == false) {
						ArrBotella[i]->setX(recolector->getX() + 7);
						ArrBotella[i]->setY(recolector->getY() + 7);
						ArrBotella[i]->dibujar(buffer, bmpBotella);
					}
		}

		if (colisionoConBonus == false) {
			carro1->movimientoIndependiente(buffer, bmpC, anchoform);
			carro2->movimientoIndependiente(buffer, bmpC, anchoform);
			ciclista1->movimientoIndependiente(buffer, bmpCi, anchoform);
			ciclista2->movimientoIndependiente(buffer, bmpCi, anchoform);
		}
		else
		{
			carro1->dibujar(buffer, bmpC);
			carro2->dibujar(buffer, bmpC);
			ciclista1->dibujar(buffer, bmpCi);
			ciclista2->dibujar(buffer, bmpCi);
		}
	}
	void moverTodoPlaya(BufferedGraphics^ buffer, Bitmap^ bmpR, Bitmap^ bmpT, Bitmap^ bmpBotella, Bitmap^ bmpCarton, int anchoform, int altoform) {
		if (BotellaAgarrada == true || CartonAgarrada == true) ObjetoAgarrado = true;
		else ObjetoAgarrado = false;

		recolector->mover(buffer, bmpR, anchoform, altoform, ObjetoAgarrado);
		for (unsigned int i = 0; i < ArrBotella.size(); i++) {
			if (ArrBotella[i]->getCerca() == false) ArrBotella[i]->dibujar(buffer, bmpBotella);
			else
				if (ArrBotella[i]->getCerca() == true && ColisionConEnemigo == true) {
					ArrBotella[i]->setCerca(false);
					BotellaAgarrada = false;
					ArrBotella[i]->setX(posicionXObjetoAgarrado);
					ArrBotella[i]->setY(posicionYObjetoAgarrado);
					ArrBotella[i]->dibujar(buffer, bmpBotella);
				}
				else
					if (ArrBotella[i]->getCerca() == true && ColisionConEnemigo == false) {
						ArrBotella[i]->setX(recolector->getX() + 7);
						ArrBotella[i]->setY(recolector->getY() + 7);
						ArrBotella[i]->dibujar(buffer, bmpBotella);
					}
		}

		for (unsigned int i = 0; i < ArrCarton.size(); i++) {
			if (ArrCarton[i]->getCerca() == false) ArrCarton[i]->dibujar(buffer, bmpCarton);
			else
				if (ArrCarton[i]->getCerca() == true && ColisionConEnemigo == true) {
					ArrCarton[i]->setCerca(false);
					CartonAgarrada = false;
					ArrCarton[i]->setX(posicionXObjetoAgarrado);
					ArrCarton[i]->setY(posicionYObjetoAgarrado);
					ArrCarton[i]->dibujar(buffer, bmpCarton);
				}
				else
					if (ArrCarton[i]->getCerca() == true && ColisionConEnemigo == false) {
						ArrCarton[i]->setX(recolector->getX() + 7);
						ArrCarton[i]->setY(recolector->getY() + 7);
						ArrCarton[i]->dibujar(buffer, bmpCarton);
					}
		}

		if (colisionoConBonus==false) {
			for (unsigned int i = 0; i < ArrTranseunte.size(); i++) {
				ArrTranseunte[i]->mover(buffer, bmpT, anchoform);
			}
		}
		else
		{
			for (unsigned int i = 0; i < ArrTranseunte.size(); i++) {
				ArrTranseunte[i]->dibujar(buffer, bmpT);
			}
		}
		
	}

	void moverTodoMar(BufferedGraphics^ buffer, Bitmap^ bmpR, Bitmap^ bmpBotella, Bitmap^ bmpCarton, Bitmap^ bmpPapel, Bitmap^ Bote, int anchoform, int altoform) {
		if (BotellaAgarrada == true || CartonAgarrada == true || PapelAgarrada == true) ObjetoAgarrado = true;
		else ObjetoAgarrado = false;

		recolector->mover(buffer, bmpR, anchoform, altoform, ObjetoAgarrado);
		for (unsigned int i = 0; i < ArrBotella.size(); i++) {
			if (ArrBotella[i]->getCerca() == false) ArrBotella[i]->dibujar(buffer, bmpBotella);
			else
				if (ArrBotella[i]->getCerca() == true && ColisionConEnemigo == true) {
					ArrBotella[i]->setCerca(false);
					BotellaAgarrada = false;
					ArrBotella[i]->setX(posicionXObjetoAgarrado);
					ArrBotella[i]->setY(posicionYObjetoAgarrado);
					ArrBotella[i]->dibujar(buffer, bmpBotella);
				}
				else
					if (ArrBotella[i]->getCerca() == true && ColisionConEnemigo == false) {
						ArrBotella[i]->setX(recolector->getX() + 7);
						ArrBotella[i]->setY(recolector->getY() + 7);
						ArrBotella[i]->dibujar(buffer, bmpBotella);
					}
		}

		for (unsigned int i = 0; i < ArrCarton.size(); i++) {
			if (ArrCarton[i]->getCerca() == false) ArrCarton[i]->dibujar(buffer, bmpCarton);
			else
				if (ArrCarton[i]->getCerca() == true && ColisionConEnemigo == true) {
					ArrCarton[i]->setCerca(false);
					CartonAgarrada = false;
					ArrCarton[i]->setX(posicionXObjetoAgarrado);
					ArrCarton[i]->setY(posicionYObjetoAgarrado);
					ArrCarton[i]->dibujar(buffer, bmpCarton);
				}
				else
					if (ArrCarton[i]->getCerca() == true && ColisionConEnemigo == false) {
						ArrCarton[i]->setX(recolector->getX() + 7);
						ArrCarton[i]->setY(recolector->getY() + 7);
						ArrCarton[i]->dibujar(buffer, bmpCarton);
					}
		}

		for (unsigned int i = 0; i < ArrPapel.size(); i++) {
			if (ArrPapel[i]->getCerca() == false) ArrPapel[i]->dibujar(buffer, bmpPapel);
			else
				if (ArrPapel[i]->getCerca() == true && ColisionConEnemigo == true) {
					ArrPapel[i]->setCerca(false);
					PapelAgarrada = false;
					ArrPapel[i]->setX(posicionXObjetoAgarrado);
					ArrPapel[i]->setY(posicionYObjetoAgarrado);
					ArrPapel[i]->dibujar(buffer, bmpPapel);
				}
				else
					if (ArrPapel[i]->getCerca() == true && ColisionConEnemigo == false) {
						ArrPapel[i]->setX(recolector->getX() + 7);
						ArrPapel[i]->setY(recolector->getY() + 7);
						ArrPapel[i]->dibujar(buffer, bmpPapel);
					}
		}

		if (colisionoConBonus == false) {
			for (unsigned int i = 0; i < ArrBote.size(); i++) {
				ArrBote[i]->mover(buffer, Bote, anchoform);
			}
		}
		else
		{
			for (unsigned int i = 0; i < ArrBote.size(); i++) {
				ArrBote[i]->dibujar(buffer, Bote);
			}
		}
	}

	void ColisionRecolectorEnemigosCalle() {
		//Ciclistas
		if (ciclista1->getRectangulo().IntersectsWith(recolector->getRectangulo())) {
			recolector->setX(4);
			recolector->setY(4);
			ColisionConEnemigo = true;
			recolector->setVidas(recolector->getVidas() - 1);
			for (int i = 0; i < 1; i++)
			{
				ArrVidas.erase(ArrVidas.begin() + i);
			}
		}
		if (ciclista2->getRectangulo().IntersectsWith(recolector->getRectangulo())) {
			recolector->setX(4);
			recolector->setY(4);
			ColisionConEnemigo = true;
			recolector->setVidas(recolector->getVidas() - 1);
			for (int i = 0; i < 1; i++)
			{
				ArrVidas.erase(ArrVidas.begin() + i);
			}
		}
		//Carros
		if (carro1->getRectangulo().IntersectsWith(recolector->getRectangulo())) {
			recolector->setX(4);
			recolector->setY(4);
			ColisionConEnemigo = true;
			recolector->setVidas(recolector->getVidas() - 1);
			for (int i = 0; i < 1; i++)
			{
				ArrVidas.erase(ArrVidas.begin() + i);
			}
		}
		if (carro2->getRectangulo().IntersectsWith(recolector->getRectangulo())) {
			recolector->setX(4);
			recolector->setY(4);
			ColisionConEnemigo = true;
			recolector->setVidas(recolector->getVidas() - 1);
			for (int i = 0; i < 1; i++)
			{
				ArrVidas.erase(ArrVidas.begin() + i);
			}
		}
	}

	void ColisionRecolectorEnemigosPlaya() {
		for (unsigned int i = 0; i < ArrTranseunte.size(); i++)
		{
			if (ArrTranseunte[i]->getRectanguloTranseunte().IntersectsWith(recolector->getRectangulo())) {
				recolector->setX(4);
				recolector->setY(4);
				ColisionConEnemigo = true;
				recolector->setVidas(recolector->getVidas() - 1);
				for (int i = 0; i < 1; i++)
				{
					ArrVidas.erase(ArrVidas.begin() + i);
				}
			}
		}
	}

	void ColisionRecolectorEnemigosMar() {
		for (unsigned int i = 0; i < ArrBote.size(); i++)
		{
			if (ArrBote[i]->getRectanguloBote().IntersectsWith(recolector->getRectangulo())) {
				recolector->setX(4);
				recolector->setY(4);
				ColisionConEnemigo = true;
				recolector->setVidas(recolector->getVidas() - 1);
				for (int i = 0; i < 1; i++) {
					ArrVidas.erase(ArrVidas.begin() + i);
				}
			}
		}
	}

	void ColisionRecolectorObjetos_1() {
		float distanciaTotal, distanciax, distanciay;
		float distanciamenor = 1000.0;

		//Encontrar la distancia menor entre las botellas y el recolector
		for (unsigned int i = 0; i < ArrBotella.size(); i++) {
			distanciax = (recolector->getX() + ((float)recolector->getAncho() / 2)) - (ArrBotella[i]->getX() + ((float)ArrBotella[i]->getAncho() / 2));
			distanciay = (recolector->getY() + ((float)recolector->getAlto() / 2)) - (ArrBotella[i]->getY() + ((float)ArrBotella[i]->getAlto() / 2));
			distanciaTotal = distanciax + distanciay;
			if ((distanciaTotal <= distanciamenor) && ArrBotella[i]->getRectangulo().IntersectsWith(recolector->getRectangulo())) {
				distanciamenor = distanciaTotal;
				ArrBotella[i]->setCerca(true);
				posicionXObjetoAgarrado = ArrBotella[i]->getX();
				posicionYObjetoAgarrado = ArrBotella[i]->getY();
				for (unsigned int j = 0; j < ArrBotella.size(); j++) {
					if (j != i) { ArrBotella[j]->setCerca(false); }
				}
				BotellaAgarrada = true;
			}
		}
	}

	void ColisionRecolectorObjetos_2() {
		float distanciaTotal, distanciax, distanciay;
		float distanciamenor = 1000.0;

		//Encontrar la distancia menor entre las botellas y el recolector
		for (unsigned int i = 0; i < ArrBotella.size(); i++) {
			distanciax = (recolector->getX() + ((float)recolector->getAncho() / 2)) - (ArrBotella[i]->getX() + ((float)ArrBotella[i]->getAncho() / 2));
			distanciay = (recolector->getY() + ((float)recolector->getAlto() / 2)) - (ArrBotella[i]->getY() + ((float)ArrBotella[i]->getAlto() / 2));
			distanciaTotal = distanciax + distanciay;
			if ((distanciaTotal <= distanciamenor) && ArrBotella[i]->getRectangulo().IntersectsWith(recolector->getRectangulo())) {
				distanciamenor = distanciaTotal;
				ArrBotella[i]->setCerca(true);
				posicionXObjetoAgarrado = ArrBotella[i]->getX();
				posicionYObjetoAgarrado = ArrBotella[i]->getY();
				for (unsigned int j = 0; j < ArrBotella.size(); j++) {
					if (j != i) { ArrBotella[j]->setCerca(false); }
				}
				BotellaAgarrada = true;
			}
		}

		//Encontrar la distancia menor entre las cartones y el recolector
		for (unsigned int i = 0; i < ArrCarton.size(); i++) {
			distanciax = (recolector->getX() + ((float)recolector->getAncho() / 2)) - (ArrCarton[i]->getX() + ((float)ArrCarton[i]->getAncho() / 2));
			distanciay = (recolector->getY() + ((float)recolector->getAlto() / 2)) - (ArrCarton[i]->getY() + ((float)ArrCarton[i]->getAlto() / 2));
			distanciaTotal = distanciax + distanciay;
			if ((distanciaTotal <= distanciamenor) && ArrCarton[i]->getRectangulo().IntersectsWith(recolector->getRectangulo())) {
				distanciamenor = distanciaTotal;
				ArrCarton[i]->setCerca(true);
				posicionXObjetoAgarrado = ArrCarton[i]->getX();
				posicionYObjetoAgarrado = ArrCarton[i]->getY();
				for (unsigned int j = 0; j < ArrCarton.size(); j++) {
					if (j != i) { ArrCarton[j]->setCerca(false); }
				}
				CartonAgarrada = true;

				//Hacer que el recolector no agarre botellas
				BotellaAgarrada = false;
				for (unsigned int j = 0; j < ArrBotella.size(); j++) {
					if (ArrBotella[j]->getCerca() == true) ArrBotella[j]->setCerca(false);
				}
			}
		}
	}

	void ColisionRecolectorObjetos_3() {
		float distanciaTotal, distanciax, distanciay;
		float distanciamenor = 1000.0;

		//Encontrar la distancia menor entre las botellas y el recolector
		for (unsigned int i = 0; i < ArrBotella.size(); i++) {
			distanciax = (recolector->getX() + ((float)recolector->getAncho() / 2)) - (ArrBotella[i]->getX() + ((float)ArrBotella[i]->getAncho() / 2));
			distanciay = (recolector->getY() + ((float)recolector->getAlto() / 2)) - (ArrBotella[i]->getY() + ((float)ArrBotella[i]->getAlto() / 2));
			distanciaTotal = distanciax + distanciay;
			if ((distanciaTotal <= distanciamenor) && ArrBotella[i]->getRectangulo().IntersectsWith(recolector->getRectangulo())) {
				distanciamenor = distanciaTotal;
				ArrBotella[i]->setCerca(true);
				posicionXObjetoAgarrado = ArrBotella[i]->getX();
				posicionYObjetoAgarrado = ArrBotella[i]->getY();
				for (unsigned int j = 0; j < ArrBotella.size(); j++) {
					if (j != i) { ArrBotella[j]->setCerca(false); }
				}
				BotellaAgarrada = true;
			}
		}

		//Encontrar la distancia menor entre las cartones y el recolector
		for (unsigned int i = 0; i < ArrCarton.size(); i++) {
			distanciax = (recolector->getX() + ((float)recolector->getAncho() / 2)) - (ArrCarton[i]->getX() + ((float)ArrCarton[i]->getAncho() / 2));
			distanciay = (recolector->getY() + ((float)recolector->getAlto() / 2)) - (ArrCarton[i]->getY() + ((float)ArrCarton[i]->getAlto() / 2));
			distanciaTotal = distanciax + distanciay;
			if ((distanciaTotal <= distanciamenor) && ArrCarton[i]->getRectangulo().IntersectsWith(recolector->getRectangulo())) {
				distanciamenor = distanciaTotal;
				ArrCarton[i]->setCerca(true);
				posicionXObjetoAgarrado = ArrCarton[i]->getX();
				posicionYObjetoAgarrado = ArrCarton[i]->getY();
				for (unsigned int j = 0; j < ArrCarton.size(); j++) {
					if (j != i) { ArrCarton[j]->setCerca(false); }
				}
				CartonAgarrada = true;

				//Hacer que el recolector no agarre botellas
				BotellaAgarrada = false;
				for (unsigned int j = 0; j < ArrBotella.size(); j++) {
					if (ArrBotella[j]->getCerca() == true) ArrBotella[j]->setCerca(false);
				}
			}
		}

		//Encontrar la distancia menor entre las cartones y el recolector
		for (unsigned int i = 0; i < ArrPapel.size(); i++) {
			distanciax = (recolector->getX() + ((float)recolector->getAncho() / 2)) - (ArrPapel[i]->getX() + ((float)ArrPapel[i]->getAncho() / 2));
			distanciay = (recolector->getY() + ((float)recolector->getAlto() / 2)) - (ArrPapel[i]->getY() + ((float)ArrPapel[i]->getAlto() / 2));
			distanciaTotal = distanciax + distanciay;
			if ((distanciaTotal <= distanciamenor) && ArrPapel[i]->getRectangulo().IntersectsWith(recolector->getRectangulo())) {
				distanciamenor = distanciaTotal;
				ArrPapel[i]->setCerca(true);
				posicionXObjetoAgarrado = ArrPapel[i]->getX();
				posicionYObjetoAgarrado = ArrPapel[i]->getY();
				for (unsigned int j = 0; j < ArrPapel.size(); j++) {
					if (j != i) { ArrPapel[j]->setCerca(false); }
				}
				PapelAgarrada = true;

				//Hacer que el recolector no agarre botellas y cartones
				BotellaAgarrada = false;
				CartonAgarrada = false;
				for (unsigned int j = 0; j < ArrBotella.size(); j++) {
					if (ArrBotella[j]->getCerca() == true) ArrBotella[j]->setCerca(false);
				}
				for (unsigned int j = 0; j < ArrCarton.size(); j++) {
					if (ArrCarton[j]->getCerca() == true) ArrCarton[j]->setCerca(false);
				}
			}
		}
	}

	void ColisionRecolectorBoteVidrios() {
		if (botevidrio->getRectangulo().IntersectsWith(recolector->getRectangulo())) {
			//Reciclar -> Eliminar la botella
			for (unsigned int i = 0; i < ArrBotella.size(); i++) {
				if (ArrBotella[i]->getCerca() == true) ArrBotella.erase(ArrBotella.begin() + i);
			}

			//SumarPuntos
			if (BotellaAgarrada == true) {
				BotellaAgarrada = false;
				if (nivel == 1) recolector->AumentarPuntosCalle();
				if (nivel == 2) recolector->AumentarPuntosPlaya();
				if (nivel == 3) recolector->AumentarPuntosMar();
				recolector->AumentarPuntosTotales();
			}
		}
	}

	void ColisionRecolectorBoteCarton() {
		if (botecarton->getRectangulo().IntersectsWith(recolector->getRectangulo())) {
			//Reciclar -> Eliminar el carton
			for (unsigned int i = 0; i < ArrCarton.size(); i++) {
				if (ArrCarton[i]->getCerca() == true) ArrCarton.erase(ArrCarton.begin() + i);
			}

			//SumarPuntos
			if (CartonAgarrada == true) {
				CartonAgarrada = false;
				if (nivel == 2) recolector->AumentarPuntosPlaya();
				if (nivel == 3) recolector->AumentarPuntosMar();
				recolector->AumentarPuntosTotales();
			}
		}
	}

	void ColisionRecolectorBotePapel() {
		if (botepapel->getRectangulo().IntersectsWith(recolector->getRectangulo())) {
			//Reciclar -> Eliminar el papel
			for (unsigned int i = 0; i < ArrPapel.size(); i++) {
				if (ArrPapel[i]->getCerca() == true) ArrPapel.erase(ArrPapel.begin() + i);
			}

			//SumarPuntos
			if (PapelAgarrada == true) {
				PapelAgarrada = false;
				if (nivel == 3) recolector->AumentarPuntosMar();
				recolector->AumentarPuntosTotales();
			}
		}
	}

	void ColisionBonusRecolector() {
		for (unsigned int i = 0; i < ArrBonus.size(); i++) {
			if (ArrBonus[i]->getRectangulo().IntersectsWith(recolector->getRectangulo())) {
				ArrBonus.erase(ArrBonus.begin() + i);
				colisionoConBonus = true;
			}
		}
	}

	bool FinDelJuego() {
		if (recolector->getVidas() == 0) return FinJuego = true;
		else return FinJuego = false;
	}

	bool GanasteElJuegoCalle() {
		if (recolector->getVidas() > 0 && recolector->getPuntosCalle() >= 5) return GanasteJuegoCalle = true;
		else return GanasteJuegoCalle = false;
	}

	bool GanasteElJuegoCallePuntosExtras() {
		if (recolector->getVidas() > 0 && recolector->getPuntosCalle() == 15) return GanasteJuegoCallePuntosExtras = true;
		else return GanasteJuegoCallePuntosExtras = false;
	}

	bool GanasteElJuegoPlaya() {
		if (recolector->getVidas() > 0 && recolector->getPuntosPlaya() >= 5) return GanasteJuegoPlaya = true;
		else return GanasteJuegoPlaya = false;
	}

	bool GanasteElJuegoMar() {
		if (recolector->getVidas() > 0 && recolector->getPuntosMar() >= 5) return GanasteJuegoMar = true;
		else return GanasteJuegoMar = false;
	}

	void setSiColisionoConEnemigo(bool ColisionConEnemigo) { this->ColisionConEnemigo = ColisionConEnemigo; }
	bool getBotellaAgarrada() { return BotellaAgarrada; }
	bool getCartonAgarrado() { return CartonAgarrada; }
	bool getPapelAgarrado() { return PapelAgarrada; }
	Recolector* getRecolector() { return recolector; }
};
