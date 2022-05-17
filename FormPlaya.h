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

	public ref class FormPlaya : public System::Windows::Forms::Form
	{
	private:
		Juego* j;
		Bitmap^ fondoPlaya;
		Bitmap^ imgjugador;
		Bitmap^ imgtranseunte;
		Bitmap^ imgbotella;
		Bitmap^ imgcarton;
		Bitmap^ imgBoteVidrio;
		Bitmap^ imgBoteCarton;
		Bitmap^ Vida;
		Bitmap^ Bonus;
		SoundPlayer^ Sonido;
		int contAparicionBonus, contEliminacionBonus;

	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Timer^ timerAparicionBonus;
	private: System::Windows::Forms::Timer^ timerEliminacionBonus;

	public:
		FormPlaya(Juego * j){
			InitializeComponent();
			this->j = j;
			fondoPlaya = gcnew Bitmap("Playa.jpg");
			imgjugador = gcnew Bitmap("Recolector.png");
			imgtranseunte = gcnew Bitmap("Transeunte.png");
			imgbotella = gcnew Bitmap("Botella.png");
			imgcarton = gcnew Bitmap("Carton.png");
			imgBoteVidrio = gcnew Bitmap("Bote_vidrio.png");
			imgBoteCarton = gcnew Bitmap("Bote_carton.png");
			Vida = gcnew Bitmap("Vida.png");
			Bonus = gcnew Bitmap("Bonus.png");
			Sonido = gcnew SoundPlayer("Musica.WAV");
			contAparicionBonus = contEliminacionBonus = 0;
		}

	protected:
		~FormPlaya()
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
			this->timer1->Tick += gcnew System::EventHandler(this, &FormPlaya::timer1_Tick);
			// 
			// timerAparicionBonus
			// 
			this->timerAparicionBonus->Enabled = true;
			this->timerAparicionBonus->Interval = 20000;
			this->timerAparicionBonus->Tick += gcnew System::EventHandler(this, &FormPlaya::timerAparicionBonus_Tick);
			// 
			// timerEliminacionBonus
			// 
			this->timerEliminacionBonus->Interval = 10000;
			this->timerEliminacionBonus->Tick += gcnew System::EventHandler(this, &FormPlaya::timerEliminacionBonus_Tick);
			// 
			// FormPlaya
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1282, 953);
			this->Name = L"FormPlaya";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"NIVEL 2: PLAYA";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FormPlaya::FormPlaya_FormClosing);
			this->Load += gcnew System::EventHandler(this, &FormPlaya::FormPlaya_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &FormPlaya::FormPlaya_KeyDown);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &FormPlaya::FormPlaya_KeyPress);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &FormPlaya::FormPlaya_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ gr = this->CreateGraphics();
		BufferedGraphicsContext^ bgc = BufferedGraphicsManager::Current;
		BufferedGraphics^ bg = bgc->Allocate(gr, this->ClientRectangle);

		int ancho, alto;
		ancho = (int)gr->VisibleClipBounds.Width;
		alto = (int)gr->VisibleClipBounds.Height;

		bg->Graphics->DrawImage(fondoPlaya, 0, 0, ancho, alto);
		bg->Graphics->DrawImage(imgjugador, ancho / 2, alto / 2, 0, 0);
		bg->Graphics->DrawImage(imgtranseunte, ancho / 2, alto / 2, 0, 0);

		j->ColisionRecolectorEnemigosPlaya();
		j->ColisionRecolectorBoteVidrios();
		j->ColisionRecolectorBoteCarton();
		j->ColisionBonusRecolector();
		j->DibujarTodoPlaya(bg, imgBoteVidrio, imgBoteCarton, Vida, Bonus);
		j->moverTodoPlaya(bg, imgjugador, imgtranseunte, imgbotella, imgcarton, ancho, alto);
		j->setSiColisionoConEnemigo(false);

		bg->Render(gr);

		delete bg; //buffer
		delete bgc;
		delete gr; //grafico

		if (j->FinDelJuego() == true) { //si perdio todas sus vidas
			this->timer1->Enabled = false;
			MessageBox::Show("PERDISTE EL SEGUNDO NIVEL" + "\n" +
				"Te has quedado sin vidas" + "\n" +
				"Puntos del segundo nivel: " + j->getRecolector()->getPuntosPlaya() + "\n" +
				"Puntos totales: " + j->getRecolector()->getPuntosTotales() + "\n");
			this->Close();
		}

		if (j->GanasteElJuegoPlaya() == true) { //si reciclo todo
			this->timer1->Enabled = false;
			MessageBox::Show("GANASTE EL SEGUNDO NIVEL" + "\n" +
				"Recogiste las 10 botellas y los 10 cartones" + "\n" +
				"Puntos del segundo nivel: " + j->getRecolector()->getPuntosPlaya() + "\n" +
				"Puntos totales: " + j->getRecolector()->getPuntosTotales() + "\n");
			this->Close();
		}

		if (j->getcrono() == 180 && j->GanasteElJuegoPlaya() == false) { //si se acabo el tiempo y no reciclo todo
			this->timer1->Enabled = false;
			MessageBox::Show("SE ACABO EL TIEMPO" + "\n" +
							 "PERDISTE EL SEGUNDO NIVEL" + "\n" +
							 "Puntos del segundo nivel: " + j->getRecolector()->getPuntosPlaya() + "\n" +
							 "Puntos totales: " + j->getRecolector()->getPuntosTotales() + "\n");
			
			this->Close();
		}
	}
	private: System::Void FormPlaya_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
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
	private: System::Void FormPlaya_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		switch (e->KeyChar)
		{
		case 'E': //Agarrar la botella mas cerca y con la que hallas colisionado
			if (j->getBotellaAgarrada() == false && j->getCartonAgarrado()==false) j->ColisionRecolectorObjetos_2();
			break;
		default:
			break;
		} 
	}
	private: System::Void FormPlaya_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		j->getRecolector()->direccion = DireccionesR::Ninguna;
	}
	private: System::Void FormPlaya_Load(System::Object^ sender, System::EventArgs^ e) {
		Sonido->PlayLooping();
	}

	private: System::Void FormPlaya_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
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
