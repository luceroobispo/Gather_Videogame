#pragma once
#include "iostream"
#include "fstream"
#include "vector"
#include "Jugador.h"
class Ranking
{
private:
	vector<Jugador*> ranking;
public:
	Ranking() {}
	~Ranking() {}
	vector <Jugador*>getranking()
	{
		return this->ranking;
	}
	void setranking(vector<Jugador*> ranking)
	{
		this->ranking = ranking;
	}
	void agregar_elemento(Jugador* jugador)
	{
		ranking.push_back(jugador);
	}
	void ordenar_ranking()
	{
		for (int i = 0; i < ranking.size(); i++)
		{
			for (int j = 0; j < ranking.size(); j++)
			{
				if (ranking[j]->getpuntos() > ranking[j + 1]->getpuntos())
				{
					Jugador temp;
					temp.setpuntos(ranking[j]->getpuntos());
					temp.setnombre(ranking[j]->getnombre());
					ranking[j] = ranking[j + 1];
					ranking[j + 1]->setpuntos(temp.getpuntos());
					ranking[j + 1]->setnombre(temp.getnombre());
				}
			}
		}
	}
	void guardar_partida()
	{
		ofstream file_ranking;
		file_ranking.open("ranking.txt", ios::out);

		int cant_jugadores;
		cant_jugadores = ranking.size();

		if (file_ranking.is_open()) {
			file_ranking << cant_jugadores << endl;
			for (int i = 0; i < ranking.size(); i++)
			{
				file_ranking << ranking[i]->getnombre() << endl;
				file_ranking << ranking[i]->getpuntos() << endl;
			}
		}
		file_ranking.close();
	}
	void cargar_partida() {
		ifstream file_ranking;
		file_ranking.open("ranking.txt", ios::in);
		int cant_jugadores;
		string jugador;
		int puntos;
		Ranking* arrTempRanking = new Ranking();

		if (file_ranking.is_open()) {
			file_ranking >> cant_jugadores;
			for (int i = 0; i < cant_jugadores; i++) {
				file_ranking >> jugador;
				file_ranking >> puntos;
				Jugador* jugadorTemp = new Jugador(jugador, puntos);
				arrTempRanking->agregar_elemento(jugadorTemp);
			}
			setranking(arrTempRanking->getranking());

			file_ranking.close();
		}
	}
};