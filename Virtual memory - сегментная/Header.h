#pragma once
void InitMemory();
int AllocMemory(int);
int FreeMemory(int);
int WriteMemory(int, int, int, void*);
int ReadMemory(int, int, int, void*);
void DumpMemory();