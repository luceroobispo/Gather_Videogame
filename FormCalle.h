#pragma once
#include <iostream>
#include "Juego.h"
namespace GatherJuego {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;

	public ref class FormCalle : public System::Windows::Forms::Form
	{
	private:
		Juego* j;
		Bitmap^ fondoCalle;
		Bitmap^ imgjugador;
		Bitmap^ imgciclista;
		Bitmap^ imgbotella;
		Bitmap^ imgBoteVidrio;
		Bitmap^ Carro;
		Bitmap^ Vida;
		Bitmap^ Bonus;
		SoundPlayer^ Sonido;
		int contAparicionBonus, contEliminacionBonus;

	private: System::Windows::Forms::Timer^ timerEliminarBonusCalle;
	private: System::Windows::Forms::Timer^ timerAparacionBonusCalle;

	public:
		FormCalle(Juego * j) {
			srand(time(NULL));
			InitializeComponent();
			this->j = j;
			imgjugador = gcnew Bitmap("Recolector.png");
			imgciclista = gcnew Bitmap("Ciclista.png");
			fondoCalle = gcnew Bitmap("Calle.jpeg");
			imgbotella = gcnew Bitmap("Botella.png");
			imgBoteVidrio = gcnew Bitmap("Bote_vidrio.png");
			Carro = gcnew Bitmap("Carro.png");
			Vida = gcnew Bitmap("Vida.png");
			Bonus = gcnew Bitmap("Bonus.png");
			Sonido = gcnew SoundPlayer("Musica.WAV");
			contAparicionBonus = contEliminacionBonus = 0;
		}

	protected:
		~FormCalle()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ timer1;
	protected:
	private: System::ComponentModel::IContainer^ components;

	private:


#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(FormCalle::typeid));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timerEliminarBonusCalle = (gcnew System::Windows::Forms::Timer(this->components));
			this->timerAparacionBonusCalle = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &FormCalle::timer1_Tick);
			// 
			// timerEliminarBonusCalle
			// 
			this->timerEliminarBonusCalle->Interval = 10000;
			this->timerEliminarBonusCalle->Tick += gcnew System::EventHandler(this, &FormCalle::timerEliminarBonusCalle_Tick);
			// 
			// timerAparacionBonusCalle
			// 
			this->timerAparacionBonusCalle->Enabled = true;
			this->timerAparacionBonusCalle->Interval = 20000;
			this->timerAparacionBonusCalle->Tick += gcnew System::EventHandler(this, &FormCalle::timerAparacionBonusCalle_Tick);
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1282, 953);
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"FormCalle";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"NIVEL 1: CALLE";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FormCalle::FormCalle_FormClosing);
			this->Load += gcnew System::EventHandler(this, &FormCalle::FormCalle_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &FormCalle::FormCalle_KeyDown);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &FormCalle::FormCalle_KeyPress);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &FormCalle::FormCalle_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ g = this->CreateGraphics();
		BufferedGraphicsContext^ espacio = BufferedGraphicsManager::Current;
		BufferedGraphics^ buffer = espacio->Allocate(g, this->ClientRectangle);

		int ancho, alto;
		ancho = (int)g->VisibleClipBounds.Width;
		alto = (int)g->VisibleClipBounds.Height;
		
		buffer->Graphics->DrawImage(fondoCalle, 0, 0, ancho, alto);
		buffer->Graphics->DrawImage(Carro, ancho / 2, alto / 2, 0, 0);
		buffer->Graphics->DrawImage(imgjugador, ancho/2, alto / 2, 0, 0);
		buffer->Graphics->DrawImage(imgciclista, ancho / 2, alto / 2, 0, 0);
	
		j->ColisionRecolectorEnemigosCalle();
		j->ColisionRecolectorBoteVidrios();
		j->ColisionBonusRecolector();
		j->DibujarTodoCalle(buffer, imgBoteVidrio, Vida, Bonus);
		j->moverTodoCalle(buffer, imgjugador, Carro, imgciclista, imgbotella, ancho, alto);
		j->setSiColisionoConEnemigo(false);

		buffer->Render(g);

		delete buffer;
		delete espacio;
		delete g;

		if (j->FinDelJuego() == true) {
			this->timer1->Enabled = false;
			MessageBox::Show("PERDISTE EL PRIMER NIVEL" + "\n" +
				"Te has quedado sin vidas" + "\n" +
				"Puntos del primer nivel: " + j->getRecolector()->getPuntosCalle() + "\n" +
				"Puntos totales: " + j->getRecolector()->getPuntosTotales() + "\n");
			this->Close();
		}

		if (j->GanasteElJuegoCallePuntosExtras() == true) {
			this->timer1->Enabled = false;
			MessageBox::Show("GANASTE EL PRIMER NIVEL" + "\n" +
							 "Recogiste todas las 15 botellas" + "\n" +
							 "Puntos del primer nivel: " + j->getRecolector()->getPuntosCalle() + "\n" +
							 "Puntos totales: " + j->getRecolector()->getPuntosTotales() + "\n");
			this->Close();
		}

		if (j->getcrono() == 120) {
			this->timer1->Enabled = false;
			if (j->GanasteElJuegoCalle() == true) {
				MessageBox::Show("GANASTE EL PRIMER NIVEL" + "\n" +
								 "Recogiste las 10 botellas" + "\n" +
								 "Puntos del primer nivel: " + j->getRecolector()->getPuntosCalle() + "\n" +
								 "Puntos totales: " + j->getRecolector()->getPuntosTotales() + "\n");
			}
			if (j->GanasteElJuegoCalle() == false) {
				MessageBox::Show("SE ACABO EL TIEMPO" + "\n" +
								 "PERDISTE EL PRIMER NIVEL" + "\n" +
								 "Puntos del primer nivel: " + j->getRecolector()->getPuntosCalle() + "\n" +
								 "Puntos totales: " + j->getRecolector()->getPuntosTotales() + "\n");
			}
			Sonido->Stop();
			this->Close();
		}
	}
	private: System::Void FormCalle_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
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
	private: System::Void FormCalle_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		j->getRecolector()->direccion = DireccionesR::Ninguna;
	}

	private: System::Void FormCalle_Load(System::Object^ sender, System::EventArgs^ e) {
		Sonido->PlayLooping();
	}

    private: System::Void FormCalle_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		switch (e->KeyChar)
		{
		case 'E': //Agarrar la botella mas cerca y con la que hallas colisionado
			if (j->getBotellaAgarrada()== false) j->ColisionRecolectorObjetos_1();
			break;
		default:
			break;
		}
    }

	private: System::Void FormCalle_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		Sonido->Stop();
	}
	
	private: System::Void timerEliminarBonusCalle_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (contEliminacionBonus <= 5) { //5 bonus
			j->EliminarBonus();
			contEliminacionBonus++;
		}
		else
			if (contEliminacionBonus == 6) { 
				j->EliminarBonus();
			}
		this->timerEliminarBonusCalle->Enabled = false;
	}
	private: System::Void timer2_Tick(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void timerAparacionBonusCalle_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (contAparicionBonus <= 5) { //5 bonus
			j->AgregarBonus();
			contAparicionBonus++;
		}
		else
			if (contAparicionBonus == 6) {
				this->timerAparacionBonusCalle->Enabled = false;
			}
		this->timerEliminarBonusCalle->Enabled = true;
	}
};
}
