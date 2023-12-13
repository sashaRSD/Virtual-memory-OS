#include "Header.h"
#include <iostream>

using namespace std;

int main()
{
	int i = 1;
	char lang[] = "98765432109876543210";
	char lang2[] = "01234567890123456789";

	int h1 = AllocMemory(2000);
	printf("\n Dump n%i \n", i++);
	DumpMemory();
	WriteMemory(h1, 0, 20, &lang);
	printf("\n Dump n%i \n", i++);
	DumpMemory();

	int h2 = AllocMemory(2000);
	printf("\n Dump n%i \n", i++);
	DumpMemory();
	WriteMemory(h2, 1, 20, &lang);
	printf("\n Dump n%i \n", i++);
	DumpMemory();

	int h3 = AllocMemory(4000);
	printf("\n Dump n%i \n", i++);
	DumpMemory();
	WriteMemory(h3, 2, 20, &lang2);
	printf("\n Dump n%i \n", i++);
	DumpMemory();

	FreeMemory(h1);
	FreeMemory(h2);
	printf("\n Dump n%i \n", i++);
	DumpMemory();

	int h4 = AllocMemory(2000);
	printf("\n Dump n%i \n", i++);
	DumpMemory();
	WriteMemory(h4, 3, 20, &lang);
	printf("\n Dump n%i \n", i++);
	DumpMemory();

	int h5 = AllocMemory(3000);
	printf("\n Dump n%i \n", i++);
	DumpMemory();
	WriteMemory(h5, 4, 20, &lang);
	printf("\n Dump n%i \n", i++);
	DumpMemory();

	return 0;
}