#include <iostream>
#include <cstdio>
#include <ctime>
#include <Windows.h>
#include <iomanip>
#include <stdlib.h>

using namespace std;

void prestavka(int delay){
	delay *= CLOCKS_PER_SEC;
	clock_t now = clock();
	while (clock() - now < delay);
}

int main()
{
	string menu[3] = { "Start", "Nastavenia", "Koniec" };
	
	system("color 0A");
	cout << setw(60) << "Ahoj!\n";
	prestavka(2);
	system("cls"); cout << setw(65) << "Vitaj v nasom sudoku!" << endl;
	prestavka(2); system("cls");
	while(1)
	{
		for (int i = 0; i < 3; i++)
		{
			cout << setw(60) << i+1 << ". " << menu[i] << endl;
		}
		
		int volba;
		cin >> volba;
		switch (volba)
		{
		case 1: 
			//start, tu sa spusti hra to pridame ked bude spravene sudoku; break;
		case 2: 
			//nastavenia, tu sa nastavia rozne veci, to este domyslime; break;
		case 3: 
			exit(0); break;
		default: 
			cout << "Zadajte cislo 1-3" << endl; break;
		}
	}
}