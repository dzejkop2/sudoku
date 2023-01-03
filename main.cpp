#include <iostream>
#include <cstdio>
#include <ctime>
#include <Windows.h>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
//#define KEY_SPACE 32
#define KEY_ENTER 13

char grid[9][9] = {{'0','0','0','0','0','0','0','0','0'},
                    {'8','0','0','0','0','0','0','0','0'},
                    {'7','0','0','0','0','0','0','0','0'},
                    {'6','0','0','0','0','0','0','0','0'},
                    {'5','0','0','0','5','0','0','0','0'},
                    {'0','0','0','0','0','0','0','0','0'},
                    {'0','0','0','0','0','0','0','0','0'},
                    {'0','0','0','0','0','0','0','0','0'},
                    {'0','0','0','0','0','0','0','8','0'}};

char check_grid[9][9] = {};

int pos_x = 0;

int pos_y = 0;

string entre = "\n \n \n \n \n \n \n \n \n \n \n \n ";

void prestavka(float delay){
	delay *= CLOCKS_PER_SEC;
	clock_t now = clock();
	while (clock() - now < delay);
}


void key_input(string instert);

//zadavanie hodnuot do hracej plochy
void grid_insert(char a[][9] , string subor)
{  
    string line;
    vector<string> lines;
    int column = 0;
    int row = 0;
    
    srand(time(NULL));
    
    //input file stream
    ifstream file(subor);
    
    //spocita pocet riadkov v subore 
    int total_lines=0;
    while(getline(file,line))
    {
       total_lines++; 
    lines.push_back(line);  
  }
   
    //generuje nahodne cislo    
    int random_number=rand()%total_lines;

    string using_line = lines[random_number];
    for(int i=0;i<using_line.length();i++)
    {
        if(using_line[i]==';'){  
            row++;
            column=0;
        }
        else{
            //-48 pretoze davame char do int a inak to neslo
            a[row][column]= using_line[i];
            column++;
        }
    }
}

//vypisovanie plochy
void print_grid()
{   
    //vypise hornu hranicu
    for (int i = 0; i < 37; i++)
    {
        cout << "#";
    }
    cout << "\n";
    for(int f = 0; f < 3; f++)
    {
    //vypise po 3 riadkoch
    for (int i = 1; i < 6; i++)
    {        
        if (i%2 == 1){
        cout << "#";
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                cout << " " << grid[(((i+1)/2)-1)+(f*3)][j*3+k] << " |";
            }
            cout << "\b\b" << " #";
        }
        }
        else{
            cout << "#";
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    cout << "---+";
                }
                cout << "\b" << "#";
            }
        }
        cout << "\n";
    }
    for (int i = 0; i < 37; i++)
    {
    cout << "#";
    }
    cout << "\n";
    }
}

void UP()
{
    pos_y--;
    if(pos_y < 0)
    {
        pos_y = 8;
    }
    if (grid[pos_y][pos_x] == '0')
    {
        grid[pos_y][pos_x] = 'x';
    }
    if (pos_y != 8)
    {
        if (grid[pos_y + 1][pos_x] == 'x')
        {
            grid[pos_y + 1][pos_x] = '0';
            return;
        }
        else return;
    }
    else if (pos_y == 8)
    {
        if (grid[0][pos_x] == 'x')
        {
            grid[0][pos_x] = '0';
            return;
        }
        else return;
    }
}

void DOWN()
{
    pos_y++;
    if (pos_y > 8)
    {
        pos_y = 0;
    }
    if (grid[pos_y][pos_x] == '0')
    {
        grid[pos_y][pos_x] = 'x';
    }
    if (pos_y != 0)
    {
        if (grid[pos_y - 1][pos_x] == 'x')
        {
            grid[pos_y - 1][pos_x] = '0';
            return;
        }
        else return;
    }
    else if (pos_y == 0)
    {
        if (grid[8][pos_x] == 'x')
        {
            grid[8][pos_x] = '0';
            return;
        }
        else return;
    }
}

void LEFT()
{
    pos_x--;
    if (pos_x < 0)
    {
        pos_x = 8;
    }
    if (grid[pos_y][pos_x] == '0')
    {
        grid[pos_y][pos_x] = 'x';
    }
    if (pos_x != 8)
    {
        if (grid[pos_y][pos_x + 1] == 'x')
        {
            grid[pos_y][pos_x + 1] = '0';
            return;
        }
        else return;
    }
    else if (pos_x == 8)
    {
        if (grid[pos_y][0] == 'x')
        {
            grid[pos_y][0] = '0';
            return;
        }
        else return;  
    }
    
}

void RIGHT()
{
    pos_x++;
    if (pos_x > 8)
    {
        pos_x = 0;
    }
    if (grid[pos_y][pos_x] == '0')
    {
        grid[pos_y][pos_x] = 'x';
    }
    if (pos_x != 0)
    {
        if (grid[pos_y][pos_x - 1] == 'x')
        {
            grid[pos_y][pos_x - 1] = '0';
            return;
        }
        else return;
    }
    else if (pos_x == 0)
    {
        if (grid[pos_y][8] == 'x')
        {
            grid[pos_y][8] = '0';
            return;
        }
        else return;
    }
}

void refresh()
{
    system("cls");
    print_grid();
}

void ENTER()
{
    char insert;
    if (grid[pos_y][pos_x] == 'x')
    {
        cout << "\nZadaj hodnotu ktoru chces zadat: ";
        cin >> insert;
        if (insert == '1' or insert == '2' or insert == '3' or insert == '4' or insert == '5' or insert == '6' or insert == '7' or insert == '8' or insert == '9')
        {
            grid[pos_y][pos_x] = insert;
            if (grid[pos_y][pos_x] == check_grid[pos_y][pos_x])
            {
                refresh();
            }
            else 
            {
                grid[pos_y][pos_x] = 'x';
                refresh();
                cout << "\nZla odpoved!";
            }
        }
        else 
        {
            cout << "\nSkus znova!";
        }
    }
    else return;
}

//pozera na inputy v konzole
void key_input(string part) 
{
    char insert;
    int c = 0;
    switch((c=_getch())) {
    case KEY_UP:
        if(part=="insert")
        {
            c = 0;
            UP();
            refresh();
        }
        break;
    case KEY_DOWN:
        if(part=="insert")
        {
            c = 0;
            DOWN();
            refresh();
        }
        break;
    case KEY_LEFT:
        if(part=="insert")
        {
            c = 0;
            LEFT();
            refresh();
        }
        break;
    case KEY_RIGHT:
        if(part=="insert")
        {
            c = 0;
            RIGHT();
            refresh();
        }
        break;
    case KEY_ENTER:
        if (part=="insert")
        {
            ENTER();
        }
        c = 0;
        break;
    /*
    case KEY_SPACE:
        c = 0;
        break;
    */
    
    }
}

int menu()
{
	string subor = "Sources/layouts.txt";
    string menu[3] = {"Start", "Nastavenia", "Koniec"};
    string nastavenia[2] = {"Obtiaznost", "Dzejkop je gay(kontrola policok)"};
    string obtiaznosti[3] = {"Easy", "Medium", "Hard"};
	
    system("color 0A");
	
    
    cout << entre << setw(60)<< "Ahoj!\n";
	prestavka(2);
	system("cls"); cout << entre << setw(65) << "Vitaj v nasom sudoku!" << endl;
	prestavka(2); system("cls"); cout << entre;
	while(1)
	{
        for (int i = 0; i < 3; i++)
		{
			cout << setw(50) << i+1 << ". " << menu[i] << endl;
		}
		
		int volba;
		cin >> volba;
		switch (volba)
		{
		case 1: 
            system("cls");
			grid_insert(check_grid, subor);
            print_grid();
            while(1){
                key_input("insert");
                    }
		case 2: 
			for(int y = 0; y < 2; y++)
            
            {
                system("cls"); cout << entre << setw(50) << y+1 << ". " << nastavenia[y-1] << endl;
            }{
                int vyber;
                cin >> vyber;
                switch (vyber){
                    case 1:
                        for (int z = 0; z < 3; z++){
                            cout << setw(50) << z+1 << ". " << obtiaznosti[z] << endl;
                        }
                        int difficulty;
                        cin >> difficulty;
                        switch(difficulty){
                                case 1: 
                                    subor = "Sources/easy_layouts.txt"; 
                                case 2: 
                                    subor = "Sources/medium_layouts.txt";  
                                case 3: 
                                    subor = "Sources/hard_layouts.txt"; 
                                default: continue;
                        }
                    case 2:
                        cout << "Toto neni spravene, vypadni dzejkop"; break;
                }

            }
		case 3: 
			exit(0); break;
		default: 
			cout << "Zadajte cislo 1-3" << endl; break;
		}
	}
}

int main()
{
    menu();
}