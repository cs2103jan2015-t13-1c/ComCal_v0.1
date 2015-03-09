#include "MonthForm.h"
#include "ComCalStarter.h"
#include <msclr\marshal_cppstd.h>
#include <msclr\marshal.h>

using namespace ComCal_v01;
using namespace System;
using namespace System::Windows::Forms;

MonthForm::MonthForm(int argc, array<String^>^ argv)
{
	InitializeComponent();

	_startComCal = gcnew ComCalStarter();
	_startComCal->ComCalStarterInit(argc, argv);
}

std::string MonthForm::convertStrTostr(String^ userInput){
	std::string strInput;

	strInput = msclr::interop::marshal_as<std::string>(userInput);

	return strInput;
}

System::Void MonthForm::userEnter(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e){
	std::string feedBackMessage;
	String^ feedBack;

	if (e->KeyCode == Keys::Enter){
		_startComCal->runLogic->executeCommand(convertStrTostr(userInputBox->Text), feedBackMessage);

		feedBack = msclr::interop::marshal_as<String^>(feedBackMessage);
		userInputBox->Text = nullptr;
	}
}
