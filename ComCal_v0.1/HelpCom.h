#pragma once

#include "Command.h"

class HelpCom : public Command {
public:
	HelpCom(Manipulator*, Manipulator*);
	~HelpCom(void);

	/*
	Name:executeInput
	Type: Method
	Purpose: Executes input received - prepares string of help sheet based on specified command, and returns this
	string.
	*/
	std::string executeInput(std::string);
};
