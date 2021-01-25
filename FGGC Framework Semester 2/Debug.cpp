#include "Debug.h"

Debug::Debug()
{
}

Debug::~Debug()
{
}

void Debug::DebugMessage()
{
	static int x = 0;
	char sz[1024] = { 0 };
	sprintf_s(sz, "the number is %d \n", x);
	OutputDebugStringA(sz);
	x++;
}

void Debug::DebugMessage(std::string message)
{
	static int x = 0;
	char sz[1024] = { 0 };
	printf_s(sz, message, x);
	OutputDebugStringA(sz);
	x++;
}
