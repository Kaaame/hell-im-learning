#include <iostream>
#include <string>
#include <windows.h>
#include <unordered_map>
//175 duration is good, 500 frqu is good for line, 700 for dot

using namespace std;

int main()
{
	Beep(700,175);
	Sleep(20);
	Beep(500,175);
}
