#pragma once
#include "Juego.h"
namespace GatherJuego {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;

	public ref class FormMar : public System::Windows::Forms::Form
	{
	private:
		Juego* j;
		Bitmap^ Bote;
		Bitmap^ fondoMar;
		Bitmap^ imgjugador;
		Bitmap^ imgtranseunte;
		Bitmap^ imgbotella;
		Bitmap^ imgcarton;
		Bitmap^ imgpapel;
		Bitmap^ imgBoteVidrio;
		Bitmap^ imgBoteCarton;
		Bitmap^ imgBotePapel;
		Bitmap^ Vida;
		Bitmap^ Bonus;
		SoundPlayer^ Sonido;
		int contAparicionBonus, contEliminacionBonus;

	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Timer^ timerAparicionBonus;
	private: System::Windows::Forms::Timer^ timerEliminacionBonus;

	public:
		FormMar(Juego * j)
		{
			InitializeComponent();
			this->j = j;
			fondoMar = gcnew Bitmap("Mar.jpeg");
			imgjugador = gcnew Bitmap("Recolector.png");
			imgtranseunte = gcnew Bitmap("Transeunte.png");
			imgbotella = gcnew Bitmap("Botella.png");
			imgcarton = gcnew Bitmap("Carton.png");
			imgpapel = gcnew Bitmap("Papel.png");
			imgBoteVidrio = gcnew Bitmap("Bote_vidrio.png");
			imgBoteCarton = gcnew Bitmap("Bote_carton.png");
			imgBotePapel = gcnew Bitmap("Bote_papel.png");
			Vida = gcnew Bitmap("Vida.png");
			Bonus = gcnew Bitmap("Bonus.png");
			Bote = gcnew Bitmap("Bote.png");
			Sonido = gcnew SoundPlayer("Musica.WAV");
			contAparicionBonus = contEliminacionBonus = 0;
		}

	protected:
		~FormMar()
		{
			if (components)
			{
				delete components;
			}
		}
	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timerAparicionBonus = (gcnew System::Windows::Forms::Timer(this->components));
			this->timerEliminacionBonus = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &FormMar::timer1_Tick);
			// 
			// timerAparicionBonus
			// 
			this->timerAparicionBonus->Enabled = true;
			this->timerAparicionBonus->Interval = 20000;
			this->timerAparicionBonus->Tick += gcnew System::EventHandler(this, &FormMar::timerAparicionBonus_Tick);
			//
			// timerEliminacionBonus
			// 
			this->timerEliminacionBonus->Interval = 10000;
			this->timerEliminacionBonus->Tick += gcnew System::EventHandler(this, &FormMar::timerEliminacionBonus_Tick);
			// 
			// FormMar
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1282, 953);
			this->Name = L"FormMar";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"NIVEL 3: MAR";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FormMar::FormMar_FormClosing);
			this->Load += gcnew System::EventHandler(this, &FormMar::FormMar_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &FormMar::FormMar_KeyDown);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &FormMar::FormMar_KeyPress);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &FormMar::FormMar_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ gr = this->CreateGraphics();
		BufferedGraphicsContext^ bgc = BufferedGraphicsManager::Current;
		BufferedGraphics^ bg = bgc->Allocate(gr, this->ClientRectangle);
		bg->Graphics->Clear(Color::White);

		int ancho, alto;
		ancho = (int)gr->VisibleClipBounds.Width;
		alto = (int)gr->VisibleClipBounds.Height;

		bg->Graphics->DrawImage(fondoMar, 0, 0, ancho, alto);
		bg->Graphics->DrawImage(imgjugador, ancho / 2, alto / 2, 0, 0);

		j->ColisionRecolectorEnemigosMar();
		j->ColisionRecolectorBoteVidrios();
		j->ColisionRecolectorBoteCarton();
		j->ColisionRecolectorBotePapel();
		j->ColisionBonusRecolector();
		j->DibujarTodoMar(bg, imgBoteVidrio, imgBoteCarton, imgBotePapel, Vida, Bonus);
		j->moverTodoMar(bg, imgjugador, imgbotella, imgcarton, imgpapel, Bote, ancho, alto);
		j->setSiColisionoConEnemigo(false);

		bg->Render(gr);

		delete bg;
		delete bgc;
		delete gr;

		if (j->FinDelJuego() == true) { //si perdio todas sus vidas
			this->timer1->Enabled = false;
			MessageBox::Show("PERDISTE EL TERCER NIVEL" + "\n" +
				"Te has quedado sin vidas" + "\n" +
				"Puntos del tercer nivel: " + j->getRecolector()->getPuntosMar() + "\n" +
				"Puntos totales: " + j->getRecolector()->getPuntosTotales() + "\n");
			this->Close();
		}

		if (j->GanasteElJuegoMar() == true) { //si reciclo todo
			this->timer1->Enabled = false;
			MessageBox::Show("GANASTE EL TERCER NIVEL" + "\n" +
				"Recogiste las 5 botellas, los 10 cartones y los 10 papeles" + "\n" +
				"Puntos del tercer nivel: " + j->getRecolector()->getPuntosMar() + "\n" +
				"Puntos totales: " + j->getRecolector()->getPuntosTotales() + "\n");
			this->Close();
		}

		if (j->getcrono() == 240 && j->GanasteElJuegoMar() == false) { //si se acabo el tiempo y no reciclo todo
			this->timer1->Enabled = false;
			MessageBox::Show("SE ACABO EL TIEMPO" + "\n" +
				"PERDISTE EL TERCER NIVEL" + "\n" +
				"Puntos del tercer nivel: " + j->getRecolector()->getPuntosMar() + "\n" +
				"Puntos totales: " + j->getRecolector()->getPuntosTotales() + "\n");

			this->Close();
		}
	}
	private: System::Void FormMar_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		j->getRecolector()->direccion = DireccionesR::Ninguna;
	}
	private: System::Void FormMar_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode)
		{
		case Keys::Left:
			j->getRecolector()->direccion = DireccionesR::Izquierda;
			break;
		case Keys::Right:
			j->getRecolector()->direccion = DireccionesR::Derecha;
			break;
		case Keys::Up:
			j->getRecolector()->direccion = DireccionesR::Arriba;
			break;
		case Keys::Down:
			j->getRecolector()->direccion = DireccionesR::Abajo;
			break;
		}
	}
	private: System::Void FormMar_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		switch (e->KeyChar)
		{
		case 'E': //Agarrar la botella mas cerca y con la que hallas colisionado
			if (j->getBotellaAgarrada() == false && j->getCartonAgarrado()==false && j->getPapelAgarrado()==false) j->ColisionRecolectorObjetos_3();
			break;
		default:
			break;
		}
	}
	private: System::Void FormMar_Load(System::Object^ sender, System::EventArgs^ e) {
		Sonido->PlayLooping();
	}
	private: System::Void FormMar_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		Sonido->Stop();
	}
	private: System::Void timerEliminacionBonus_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (contEliminacionBonus <= 5) { //5 bonus
			j->EliminarBonus();
			contEliminacionBonus++;
		}
		else
			if (contEliminacionBonus == 6) {
				j->EliminarBonus();
			}
		this->timerEliminacionBonus->Enabled = false;
	}

	private: System::Void timerAparicionBonus_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (contAparicionBonus <= 5) { //5 bonus
			j->AgregarBonus();
			contAparicionBonus++;
		}
		else
			if (contAparicionBonus == 6) {
				this->timerAparicionBonus->Enabled = false;
			}
		this->timerEliminacionBonus->Enabled = true;
	}
	
};
}
