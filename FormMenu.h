#pragma once
#include "FormCalle.h" //NIVEL 1
#include "FormPlaya.h" //NIVEL 2
#include "FormMar.h" //NIVEL 3
#include "FormInstrucciones.h"
#include "FormReglas.h"
#include "FormCreditos.h"
#include "Juego.h"

namespace GatherJuego {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class FormMenu : public System::Windows::Forms::Form
	{
	private:
		Bitmap^ FondoMenu;

	public:
		FormMenu(void)
		{
			InitializeComponent();
			FondoMenu = gcnew Bitmap("Fondo.png");
		}

	protected:
		~FormMenu()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btnInstrucciones;
	private: System::Windows::Forms::Button^ btnIniciar;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Button^ btnReglas;

	private: System::Windows::Forms::Button^ btnCreditos;

	private: System::ComponentModel::IContainer^ components;

	private:


#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->btnInstrucciones = (gcnew System::Windows::Forms::Button());
			this->btnIniciar = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->btnReglas = (gcnew System::Windows::Forms::Button());
			this->btnCreditos = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btnInstrucciones
			// 
			this->btnInstrucciones->BackColor = System::Drawing::Color::White;
			this->btnInstrucciones->Font = (gcnew System::Drawing::Font(L"Ravie", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnInstrucciones->Location = System::Drawing::Point(836, 759);
			this->btnInstrucciones->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btnInstrucciones->Name = L"btnInstrucciones";
			this->btnInstrucciones->Size = System::Drawing::Size(379, 52);
			this->btnInstrucciones->TabIndex = 1;
			this->btnInstrucciones->Text = L"Instrucciones";
			this->btnInstrucciones->UseVisualStyleBackColor = false;
			this->btnInstrucciones->Click += gcnew System::EventHandler(this, &FormMenu::btnInstrucciones_Click);
			// 
			// btnIniciar
			// 
			this->btnIniciar->BackColor = System::Drawing::Color::White;
			this->btnIniciar->Font = (gcnew System::Drawing::Font(L"Ravie", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnIniciar->Location = System::Drawing::Point(465, 729);
			this->btnIniciar->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btnIniciar->Name = L"btnIniciar";
			this->btnIniciar->Size = System::Drawing::Size(355, 52);
			this->btnIniciar->TabIndex = 2;
			this->btnIniciar->Text = L"Iniciar";
			this->btnIniciar->UseVisualStyleBackColor = false;
			this->btnIniciar->Click += gcnew System::EventHandler(this, &FormMenu::btnIniciar_Click);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &FormMenu::timer1_Tick);
			// 
			// btnReglas
			// 
			this->btnReglas->BackColor = System::Drawing::Color::White;
			this->btnReglas->Font = (gcnew System::Drawing::Font(L"Ravie", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnReglas->Location = System::Drawing::Point(66, 759);
			this->btnReglas->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btnReglas->Name = L"btnReglas";
			this->btnReglas->Size = System::Drawing::Size(379, 52);
			this->btnReglas->TabIndex = 3;
			this->btnReglas->Text = L"Reglas";
			this->btnReglas->UseVisualStyleBackColor = false;
			this->btnReglas->Click += gcnew System::EventHandler(this, &FormMenu::button1_Click);
			// 
			// btnCreditos
			// 
			this->btnCreditos->BackColor = System::Drawing::Color::White;
			this->btnCreditos->Font = (gcnew System::Drawing::Font(L"Ravie", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCreditos->Location = System::Drawing::Point(465, 785);
			this->btnCreditos->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btnCreditos->Name = L"btnCreditos";
			this->btnCreditos->Size = System::Drawing::Size(355, 54);
			this->btnCreditos->TabIndex = 4;
			this->btnCreditos->Text = L"Creditos";
			this->btnCreditos->UseVisualStyleBackColor = false;
			this->btnCreditos->Click += gcnew System::EventHandler(this, &FormMenu::button2_Click);
			// 
			// FormMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->ClientSize = System::Drawing::Size(1282, 953);
			this->Controls->Add(this->btnCreditos);
			this->Controls->Add(this->btnReglas);
			this->Controls->Add(this->btnIniciar);
			this->Controls->Add(this->btnInstrucciones);
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"FormMenu";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MENU";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btnInstrucciones_Click(System::Object^ sender, System::EventArgs^ e) {
		FormInstrucciones^ FrmInstrucciones = gcnew FormInstrucciones();
		this->Visible = false;
		FrmInstrucciones->ShowDialog();
		this->Visible = true;
		delete FrmInstrucciones;
	}
	private: System::Void btnIniciar_Click(System::Object^ sender, System::EventArgs^ e) {
		Juego* nivel1 = new Juego(1);
		FormCalle^ FrmCalle = gcnew FormCalle(nivel1); //le pasamos el juego
		this->Visible = false;
		//NIVEL 1: CALLE
		FrmCalle->ShowDialog();
		
		if (nivel1->GanasteElJuegoCalle() == true || nivel1->GanasteElJuegoCallePuntosExtras()==true) {
			//NIVEL 2: PLAYA
			Juego* nivel2 = new Juego(2);
			FormPlaya^ FrmPlaya = gcnew FormPlaya(nivel2); //le pasamos el juego
			nivel2->getRecolector()->setPuntosTotales(nivel1->getRecolector()->getPuntosTotales());
			FrmPlaya->ShowDialog();

			if (nivel2->GanasteElJuegoPlaya() == true) {
				Juego* nivel3 = new Juego(3);
				FormMar^ FrmMar = gcnew FormMar(nivel3); //le pasamos el juego
				nivel3->getRecolector()->setPuntosTotales(nivel2->getRecolector()->getPuntosTotales());
				FrmMar->ShowDialog();
				this->Visible = true;
				delete FrmMar;
			}
			else
			{
			//	NIVEL 3: MAR
			this->Visible = true;
			}
			delete FrmPlaya;
		}
		else
		{
			this->Visible = true;
		}

		delete FrmCalle;
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		FormReglas^ FrmReglas = gcnew FormReglas();
		this->Visible = false;
		FrmReglas->ShowDialog();
		this->Visible = true;
		delete FrmReglas;
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		FormCreditos^ FrmCreditos = gcnew FormCreditos();
		this->Visible = false;
		FrmCreditos->ShowDialog();
		this->Visible = true;
		delete FrmCreditos;
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ gr = this->CreateGraphics();
		BufferedGraphicsContext^ bgc = BufferedGraphicsManager::Current;
		BufferedGraphics^ bg = bgc->Allocate(gr, this->ClientRectangle);
		bg->Graphics->Clear(Color::White);

		int ancho, alto;
		ancho = (int)gr->VisibleClipBounds.Width;
		alto = (int)gr->VisibleClipBounds.Height;

		bg->Graphics->DrawImage(FondoMenu, 0, 0, ancho, alto);

		bg->Render(gr);

		delete bg;
		delete bgc;
		delete gr;
	}
};
}
