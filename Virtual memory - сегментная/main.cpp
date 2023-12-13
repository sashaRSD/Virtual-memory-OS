#include "Header.h"
#include <iostream>

int main()
{
	int i = 1;
	char lang[] = "98765432109876543210";
	char lang2[] = "01234567890123456789";
	char lang3[20];

	printf(" Dump n%i \n", i++);
	int h1 = AllocMemory(10000);
	int h2 = AllocMemory(2500);
	DumpMemory();

	printf("\n Dump n%i \n", i++);
	WriteMemory(h1, 3, 20, &lang);
	WriteMemory(h2, 1, 20, &lang);
	DumpMemory();

	printf("\n Dump n%i \n", i++);
	printf(" Read: ");
	ReadMemory(h1, 2, 20, &lang3);
	for (int j = 0; j < 20; j++) printf("%c", lang3[j]);
	printf("\n");
	DumpMemory();

	printf("\n Dump n%i \n", i++);
	int h3 = AllocMemory(4900);
	WriteMemory(h3, 0, 20, &lang2);
	DumpMemory();

	printf("\n Dump n%i \n", i++);
	FreeMemory(h3);
	DumpMemory();

	printf("\n Dump n%i \n", i++);
	int h4 = AllocMemory(1900);
	WriteMemory(h4, 2, 20, &lang2);
	DumpMemory();

	printf("\n Dump n%i \n", i++);
	int h5 = AllocMemory(3500);
	WriteMemory(h5, 3, 20, &lang2);
	DumpMemory();

	printf("\n Dump n%i \n", i++);
	int h6 = AllocMemory(9700);
	WriteMemory(h6, 2, 20, &lang);
	DumpMemory();

	printf("\n Dump n%i \n", i++);
	int h7 = AllocMemory(850);
	DumpMemory();

	return 0;
}