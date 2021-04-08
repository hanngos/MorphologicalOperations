#include "MyForm.h"
#include <stdio.h>
#include <iostream>
#include <windows.h>

using namespace System;
using namespace std;

[STAThreadAttribute]

void main() {
	
	/*Windows::Forms::Application::Run(gcnew JAProjekt::MyForm());*/

	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	JAProjekt::MyForm form;
	Application::Run(%form);

}