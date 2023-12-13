#include "Header.h"
#include <stdio.h>
#include <cstdlib>
#define SizeOfMemory 10000

char Memory[SizeOfMemory];
int HandleGenerator = 1;

struct Block {
	int adr;
	int size;
	int handle;
};
Block BAr[30];

void InitMemory()
{
}

int AllocMemory(int Size)
{
	if ((Size > SizeOfMemory) || (Size <= 0)) return 0;
	int i = 0;
	int used_size = 0;
	while (BAr[i].handle)
	{
		used_size += BAr[i].size;
		if (i != 29) i++; 
		else return 0;
	}
	if (Size <= (SizeOfMemory - used_size))
	{
		BAr[i].handle = HandleGenerator++;
		BAr[i].size = Size;
		BAr[i].adr = used_size;
		return BAr[i].handle;
	}
	else {
		int free = SizeOfMemory - used_size;
		printf("\n No memory for blok size: %i, free: %i\n",Size, free); 
		exit(1);
		}
}

void FreeMemory(int MemoryHandle)
{

	int i = 0;
	while (BAr[i].handle != MemoryHandle) i++;
	BAr[i].handle = -1;
	for (int j = BAr[i].adr; j < BAr[i].adr + BAr[i].size; j++) Memory[j] = 0;

	printf("\n Delete \n");
	DumpMemory();

	Block del;
	int j = 0;
	for (int i = 0; BAr[i].handle && i < 30; i++)
	{
		if (BAr[i].handle == -1)
		{
			del = BAr[i];
			while (BAr[j].handle)
			{
				if ((j >= i) && (j != 29)) BAr[j] = BAr[j + 1];
				if (BAr[j].adr > del.adr) BAr[j].adr = BAr[j].adr - del.size;
				if (j != 29) j++;
				else break;
			}
			for (del.adr; del.adr < SizeOfMemory - del.size; del.adr++) Memory[del.adr] = Memory[del.adr + del.size];
			for (int i=0; i < del.adr; i++) Memory[SizeOfMemory - del.size] = 0;
		}
	}

}

int WriteMemory(int MemoryHandle, int Offset, int Size, void* Data)
{
	int i = 0;
	char *mem;
	char* data = (char*)Data;
	while (BAr[i].handle != MemoryHandle) i++;
	if ((i == 30) || (BAr[i].handle != MemoryHandle)) return 1;
	if ((Offset + Size) > BAr[i].size) return 1;

	if (Offset == 0) mem = &Memory[BAr[i].adr+Offset];
	else { mem = &Memory[BAr[i].adr]; 
		for (i = 0; i < Offset; i++) *mem = '#';
		}
	for (i = 0; i < Size; i++) *mem++ = *data++;
	return 0;
}

int ReadMemory(int MemoryHandle, int Offset, int Size, void* Data)
{
	int i = 0;
	char* data = (char*)Data;
	while (BAr[i].handle != MemoryHandle) i++;
	if ((i == 30) && (BAr[i].handle != MemoryHandle)) return 1;
	if ((Offset + Size) > BAr[i].size) Size = BAr[i].size - Offset;
	char* mem = &Memory[BAr[i].adr + Offset];
	for (i = 0; i < Size; i++) *data++ = *mem++;
	return 0;
}

void DumpMemory()
{
	char busy[] = "Yes";
	char busy2[] = "No";
	char data[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	for (int i = 0; BAr[i].handle; i++)
	{
		if (BAr[i].handle == -1)
		printf("H: %i Adr: %i Size: %i %s ", BAr[i].handle, BAr[i].adr, BAr[i].size, busy2);
		else
			printf("H: %i Adr: %i Size: %i %s ", BAr[i].handle, BAr[i].adr, BAr[i].size, busy);

		ReadMemory(BAr[i].handle, 0, 10, data);
		for (int j = 0; data[j] && j<10; j++) printf("%c", data[j]);
		printf("\n");

	}
}
