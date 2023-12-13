#include "Header.h"
#include <stdio.h>
#include <cstdlib>


#define SizeOfMemory 10000
#define SizeOfVirtualMemory 20000
#define SizeOfPage 1000

char Memory[SizeOfMemory];
char VirtualMemory[SizeOfVirtualMemory];//?

int handle_num = 1;
int free_block = 29;

struct Page{
	int handle;
	int logical_number;
	int score; 
};
Page PAr[30];

int VirtualShift(int VirtualPage)
{
	int MinScore = 10000;
	int i, RealPage, FreeVirtual;

	for (i = 0; i < 10; i++)
	{
		if (PAr[i].score < MinScore) { MinScore = PAr[i].score; RealPage = i; }
	}

	for (FreeVirtual = 10; FreeVirtual < 30; FreeVirtual++)
	{ if (PAr[FreeVirtual].handle == 0) break;}

	for (i = 0; i < SizeOfPage; i++)
	{
		VirtualMemory[FreeVirtual*SizeOfPage + i] = Memory[RealPage*SizeOfPage + i];
		Memory[RealPage*SizeOfPage + i] = VirtualMemory[VirtualPage*SizeOfPage + i];
		VirtualMemory[VirtualPage*SizeOfPage + i] = 0;
	}
	PAr[FreeVirtual] = PAr[RealPage];
	PAr[RealPage] = PAr[VirtualPage];
	PAr[VirtualPage].handle = 0;
	PAr[VirtualPage].logical_number = 0;
	PAr[VirtualPage].score = 0;
	return RealPage;
}

void InitMemory()
{

}

int AllocMemory(int Size)
{
	if ((Size <= 0) || (Size > SizeOfMemory) || (Size > free_block*SizeOfPage))
	{ printf("Error allocate memory = %i!\n",Size); return 0; }
	int i = 0;
	int logic_num = 1;
	while (Size > 0)
	{
		if (PAr[i].handle == 0)
		{
			PAr[i].handle = handle_num;
			PAr[i].logical_number = logic_num++;
			Size = Size - SizeOfPage;
			if (i < 10) for (int j = i * SizeOfPage; j < (i + 1) * SizeOfPage; j++)
			{
				Memory[j] = 0;
			}	
			else for (int j = (i-10) * SizeOfPage; j < ((i-10) + 1) * SizeOfPage; j++)
			{
				VirtualMemory[j] = 0;
			}
		}
		if (i < 30) i++;
		else if (Size > 0) return 0;
	}
	free_block = free_block - (logic_num -1);
	return handle_num++;
}

int FreeMemory(int HandleDelete)
{
	if (HandleDelete <= 0 || HandleDelete >= handle_num)
	{ printf("Error free memory. Handle = %i!\n", HandleDelete); exit(1); return 0; }
	for (int i = 0; i < 30; i++)
	{
		if (PAr[i].handle == HandleDelete)
		{
			PAr[i].handle = 0;
			PAr[i].logical_number = 0;
			free_block++;
		}
	}
	return 1;
}

int WriteMemory(int MemoryHandle, int Offset, int Size, void* Data)
{
	if (MemoryHandle <= 0 || MemoryHandle >= handle_num || Offset < 0 || Size < 0)
	{printf("Error write memory!\n"); exit(1); return 0;}
	char* data = (char*)Data;
	char* mem = 0;
	int tmp_number = 1;
	for (int i = 0; (i < 30) && (Size > 0); i++)
	{
		if ((PAr[i].handle == MemoryHandle) && (PAr[i].logical_number == tmp_number))
		{
			tmp_number++;
			if (i < 10)
			{
				PAr[i].score++;
				if (Offset < SizeOfPage)
				{
					mem = &Memory[i*SizeOfPage];
					if (Offset>0) for (i = 0; i < Offset; i++) *mem++ = '#';
					for (int j = 0; (j < SizeOfPage - Offset) && (Size > 0); j++)
					{
						*mem++ = *data++;
						Size--;
					}
				}
				else Offset = Offset - SizeOfPage;
			}
			else
			{
				if (Offset < SizeOfPage)
				{
					int RealPage = VirtualShift(i);
					PAr[RealPage].score++;
					mem = &Memory[RealPage*SizeOfPage];
					if (Offset > 0) for (i = 0; i < Offset; i++) *mem++ = '#';
					for (int j = 0; (j < SizeOfPage - Offset) && (Size > 0); j++)
					{
						*mem++ = *data++;
						Size--;
					}
				}
				else Offset = Offset - SizeOfPage;
			}
			i = 0;

		}
	}
	return 1;
}

int ReadMemory(int MemoryHandle, int Offset, int Size, void* Data)
{
	if (MemoryHandle <= 0 || MemoryHandle >= handle_num || Offset < 0 || Size < 0)
	{printf("Error write memory. Handle = %i!\n", MemoryHandle); return 0;}
	char* data = (char*)Data;
	char* mem = 0;
	int tmp_number = 1;
	for (int i = 0; (i < 30) && (Size > 0); i++)
	{
		if ((PAr[i].handle == MemoryHandle) && (PAr[i].logical_number == tmp_number))
		{
			tmp_number++;
			if (i < 10)
			{
				PAr[i].score++;
				if (Offset < SizeOfPage)
				{
					mem = &Memory[i*SizeOfPage + Offset];
					for (int j = 0; (j < SizeOfPage - Offset) && (Size > 0); j++)
					{
						*data++ = *mem++;
						Size--;
					}
				}
				else Offset = Offset - SizeOfPage;
			}
			else
			{
				if (Offset < SizeOfPage)
				{
					int RealPage = VirtualShift(i);
					PAr[RealPage].score++;
					mem = &Memory[RealPage*SizeOfPage + Offset];
					for (int j = 0; (j < SizeOfPage - Offset) && (Size > 0); j++)
					{
						*data++ = *mem++;
						Size--;
					}
				}
				else Offset = Offset - SizeOfPage;
			}
			i = 0;
		}
	}
	return 1;
}

void DumpMemory()
{
	char data[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int kol_vo = 0;
	int tmp = 1;

	for (int i = 1; i < handle_num; i++)
	{
		printf("H: %i P: ", i);
		for (int num_str = 0; num_str < 30; num_str++)
		{
			if ((PAr[num_str].handle == i) && (PAr[num_str].logical_number == tmp))
			{
				if (tmp == 1)
				{
					for (int j = 0; j < 10; j++)
					{
					if (num_str < 10) data[j] = Memory[num_str*SizeOfPage + j];
					else data[j] = VirtualMemory[num_str*SizeOfPage + j];
					}
				}
				kol_vo++;
				tmp++;
				printf("%i ", num_str);
				num_str = 0;
			}
		}
		printf("S:%i M:", kol_vo*SizeOfPage);
		if(kol_vo > 0) for (int j = 0; j < 10; j++) printf("%c", data[j]);
		printf("\n");
		kol_vo = 0;
		tmp = 1;

	}
}
