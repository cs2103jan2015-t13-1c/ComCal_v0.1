#include "MonthForm.h"
#include "ComCalStarter.h"

using namespace ComCal_v01;
using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^> ^ fileNames) {

	int numOfSpecifiedFiles = fileNames->Length;

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	ComCal_v01::MonthForm form(numOfSpecifiedFiles, fileNames);
	Application::Run(%form);

	return 0;
}

