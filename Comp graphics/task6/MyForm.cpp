#include "MyForm.h"
#include "Clip.h"
#include "Matrix.h"
#include "Transform.h"
#include "Figure.h"
#include <vector>
#include <fstream>
#include <sstream>
using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Kartashov::MyForm form;
	Application::Run(% form);
}

