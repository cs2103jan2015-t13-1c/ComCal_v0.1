#include "ComCalStarter.h"
#include "MonthForm.h"
#include <msclr\marshal_cppstd.h>
#include <msclr\marshal.h>

ComCalStarter::ComCalStarter(){
	void;
}

void ComCalStarter::ComCalStarterInit(int numOfArg, array<System::String^>^ fileNames){
	std::string todoFileName;
	std::string doneFileName;

	const char** argVec;

	typeConversion(fileNames, argVec, numOfArg);

	if (numOfArg == NOFILENAMEENTERED) {
		todoFileName = FILENAME_TODODEFAULT;
		doneFileName = FILENAME_DONEDEFAULT;
	}
	else if (numOfArg == TODOFILENAMEENTERED) {
		todoFileName = argVec[1];
		doneFileName = FILENAME_DONEDEFAULT;
	}
	else {
		todoFileName = argVec[1];
		doneFileName = argVec[2];
	}

	Manipulator* todoTMPtr;
	Manipulator* doneTMPtr;
	Logic* logPtr;

	todoTMPtr = new TextManipulator(todoFileName);
	doneTMPtr = new TextManipulator(doneFileName);

//	prestartCheck(todoTMPtr);
//	prestartCheck(doneTMPtr);
//	printWelcomeMessage(todoFileName, doneFileName); //transfer this to the GUI

	logPtr = new Logic(todoTMPtr, doneTMPtr);
	runLogic = logPtr;

//	run(); // GUI will manage this, needa change this

	delete todoTMPtr;
	delete doneTMPtr;
	delete logPtr;

	//system("pause");

	return;
}

void ComCalStarter::typeConversion(array<System::String^>^ fileNames, const char** strFilesNames, int numOfSpecifiedFiles){

	msclr::interop::marshal_context^ context = gcnew msclr::interop::marshal_context();
	for (int i = 0; i < numOfSpecifiedFiles; i++){
		strFilesNames[i] = context->marshal_as<const char*>(fileNames[i]);

		context = nullptr;
	}

}

ComCalStarter::~ComCalStarter(){
}

//remove this function as it will be carried out in the app by itself
void ComCalStarter::run() {
	std::string userInput;
	std::string output;
	bool isTerminate;

	do {
		try {
			userInput = read(); // not useable anymore cus reading will be done in the GUI
			isTerminate = runLogic->executeCommand(userInput, output);
			printOutput(output);
		}
		catch (std::exception& exception) {
			std::cout << exception.what() << std::endl << std::endl;
			if (exception.what() == TASKERROR_INVALIDSTRINGFORMAT || exception.what() == TASKERROR_INVALIDTYPECODE || exception.what() == TASKERROR_INCORRECTEMPTYATTRIBUTESYMBOL || exception.what() == TASKERROR_NODESCRIPTION || exception.what() == TASKERROR_INVALIDDATETIME || exception.what() == TASKERROR_INVALIDDATE || exception.what() == TASKERROR_INVALIDTIME || exception.what() == TASKERROR_INCORRECTTYPECODE || exception.what() == TASKERROR_MDAYOUTOFRANGELEAPFEB || exception.what() == TASKERROR_MDAYOUTOFRANGENONLEAPFEB || exception.what() == TASKERROR_MDAYOUTOFRANGE30DAYMONTH || exception.what() == TASKERROR_MDAYOUTOFRANGE31DAYMONTH || exception.what() == TASKERROR_MONTHOUTOFRANGE || exception.what() == TASKERROR_HOUROUTOFRANGE || exception.what() == TASKERROR_MINOUTOFRANGE) {
				std::cout << "TEXT FILE IS CORRUPTED. PLEASE CHECK ActivityLog.txt FOR DETAILS." << std::endl;
				isTerminate = true;
			}
			else {
				isTerminate = false;
			}
		}
	} while (!isTerminate);

	return;
}

//Unuseable anymore cus reading will be done in GUI level
std::string ComCalStarter::read(void) {
	std::string userInput;

	getline(std::cin, userInput);

	if (userInput == "") {
		throw exceptionInputNoCommand;
	}

	return userInput;
}

//output message will be returned to the feedback GUI instead
//change this to return a string -> string will be converted to String^ then placed
void ComCalStarter::printOutput(std::string output) {
	std::cout << output << std::endl;
}

void ComCalStarter::prestartCheck(Manipulator* tmPtr) {
	std::ofstream logFile;
	time_t timeNow;
	tm timeNowtm;
	time(&timeNow);
	char timeString[50];

	localtime_s(&timeNowtm, &timeNow);
	strftime(timeString, 50, "%a, %d %b %Y, %I:%M%p", &timeNowtm);

	logFile.open(FILENAME_LOGDEFAULT, std::ios::app);
	logFile << "\nPre-start Check for " << tmPtr->getFileName() << " started on: " << timeString << std::endl;

	try {
		tmPtr->sort();
		logFile << "Pre-start Check completed with no error\n." << std::endl;
		logFile.close();
	}
	catch (std::exception& exception) {
//		std::cout << "PRE-START CHECK FAILED. " << tmPtr->getFileName() << " IS CORRUPTED. PLEASE CHECK ActivityLog.txt FOR DETAILS." << std::endl;
		logFile << "PRE-START CHECK FAILED. SEE ABOVE FOR DETAILS.\n" << std::endl;

		logFile.close();

		//system("pause");
		exit(0);
	}
}


//remove this function
//change this function, feed string to the feedback message bar
void ComCalStarter::printWelcomeMessage(std::string todoFileName, std::string doneFileName) {
	char buffer[255];
	
	std::string output;

	if (todoFileName != FILENAME_TODODEFAULT) {
		sprintf_s(buffer, MESSAGE_TODOSPECIFIEDFILENAMECONFIRMATION.c_str(), todoFileName);
	}
	output = buffer;
	std::cout << "[" << output;

	if (doneFileName != FILENAME_DONEDEFAULT) {
		sprintf_s(buffer, MESSAGE_DONESPECIFIEDFILENAMECONFIRMATION.c_str(), doneFileName);
	}
	output = buffer;
	std::cout << output << "]\n\n";

	return;
}
