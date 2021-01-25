#pragma once

#include <string>
#include <Windows.h>
#include <string>

class Debug {

private:

public:
	Debug();
	~Debug();
	void DebugMessage();
	void DebugMessage(std::string message);
};