#pragma once

namespace GatherJuego {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class FormReglas : public System::Windows::Forms::Form
	{
	private:
		Bitmap^ Reglas;
	public:
		FormReglas(void)
		{
			InitializeComponent();
			Reglas = gcnew Bitmap("Reglas.png");
		}

	protected:
		~FormReglas()
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
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &FormReglas::timer1_Tick);
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1282, 953);
			this->Name = L"FormReglas";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"REGLAS";
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

		bg->Graphics->DrawImage(Reglas, 0, 0, ancho, alto);

		bg->Render(gr);

		delete bg;
		delete bgc;
		delete gr;
	}
	};
}
