#pragma once
/*
@Hamzah(from Huang Qin): There needs to be a main function of some sort that serves as the entry point of the program.
This function will also serve as the initializer for Logic and TextManipulator classes, 1 for the former and 1 for each
.txt file for the latter, to ensure that there is only 1 brain (served by Logic class) for the entire program and 1 file
manager (served by TextManipulator Class) for each file. For a sample of the code for this initializer, refer to ComCalManager
constructor implementation. The run function it calls basically controls the runtime of the program, to keep reading inputs
and printing outputs until exit command is read, then it will terminate by exiting the function. I'm not sure how our GUI
components can be integrated with this architecture, so maybe you can consider this while designing and implementing the GUI.
Thanks!!!
*/
/***********************************************************************************************************************************************
This Main.cpp file contains the main function, which is the entry point of the ComCal program, and serves as the program's initialiser.
ComCal is a CLI input coupled with GUI display program that enables users to manage their tasks more efficiently and effectively.
It's simple database of .txt files enables advanced users to more easily and conveniently edit their tasks directly in the database.
ComCal has the following task management functionalities:
1) (Create) add <task>: Enables users to add a task to their task list in the .txt files.
2) (Retrieve) show <type> <date/time>: Enables users to display tasks from the .txt files tasks list based on <type> and <date/time> specified.
3) (Update) edit <task index> <attribute> <new content>: Enables users to edit an attribute of a task in the .txt files tasks list.
4) (Delete) del <task index>: Enables users to delete a task from the .txt files tasks list.
5) (Done/Undone) done/undo <task index>: Enables users to mark a task from the .txt files tasks list as complete/incomplete.
6) (Undo/Redo) undo/redo: Enables users to undo/redo last action performed/undone.
7) (Search) search <attribute> <content>: Enables user to search for a task from the .txt files tasks list either by wildcard(without specifying 
   any attribute) or by attribute and content specified.
*************************************************************************************************************************************************/

#include "Manipulator.h"
#include "Logic.h"
#include "Exceptions.h"

#include "Windows.h"
#include <string>
#include <iostream>
#include <ctime>

//Default file names constant string declarations:
const std::string FILENAME_TODODEFAULT = "ComCal_todo.txt";
const std::string FILENAME_DONEDEFAULT = "ComCal_done.txt";

//Default log file name constant string declarations:
const std::string FILENAME_LOGDEFAULT = "ActivityLog.txt";

//Number of file name arguments constant int declarations:
const int NOFILENAMEENTERED = 1;
const int TODOFILENAMEENTERED = 2;

//Welcome messages constant string declarations:
const std::string MESSAGE_TODODEFAULTFILENAMECONFIRMATION = "Working on default todo file: " + FILENAME_TODODEFAULT;
const std::string MESSAGE_DONEDEFAULTFILENAMECONFIRMATION = ", and default done file: " + FILENAME_DONEDEFAULT;
const std::string MESSAGE_TODOSPECIFIEDFILENAMECONFIRMATION = "Working on specified todo file: \"%s\"";
const std::string MESSAGE_DONESPECIFIEDFILENAMECONFIRMATION = ", and specified done file: \"%s\"";

ref class ComCalStarter sealed
{
public:
	ComCalStarter();
	void ComCalStarterInit(int, array<System::String^>^);
	Logic* runLogic;

private:

	void typeConversion(array<System::String^>^, const char**, int);
	void prestartCheck(Manipulator*);
	void printWelcomeMessage(std::string, std::string); //integrate this to GUI
	void run();
	std::string read(); //dont need this shit anymore, GUI will handle it
	void printOutput(std::string);

	~ComCalStarter();

};