#include "FormMenu.h"

using namespace System;
using namespace Windows::Forms;
using namespace GatherJuego;//GatherJuego es el nombre del proyecto
void main() {
	Application::EnableVisualStyles();
	Application::Run(gcnew GatherJuego::FormMenu); //GatherJuego es el nombre del proyecto
}