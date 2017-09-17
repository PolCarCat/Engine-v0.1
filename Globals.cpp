#include <windows.h>
#include <stdio.h>
#include "Utilities.h"

void log(const char file[], int line, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);
	va_end(ap);
	sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);
	OutputDebugString(tmp_string2);
}

int clip(int value, int minimum, int maximum) {
	return max(minimum, min(value, maximum));
}

float clip(float value, int minimum, int maximum) {
	return max(minimum, min(value, maximum));
}

void TEST() {
	DynamicList<int> list;
	list.push(0);
	list.push(10);

	int i = list[0];
	int j = list[1];
}