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

char grid[9][9] = {{'9','0','0','0','0','0','0','0','0'},
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

void prestavka(float delay){
	delay *= CLOCKS_PER_SEC;
	clock_t now = clock();
	while (clock() - now < delay);
}

//cekuje pri lahsiej obtiaznosti cekovania(cekuje input s uz dokoncenym sudoku)
bool check_easy()
{

} 

//cekuje relativne input pouzivatela
bool check_input()
{
    
}

//zadavanie hodnuot do hracej plochy
void grid_insert(char a[][9])
{  
    string line;
    vector<string> lines;
    int column = 0;
    int row = 0;
    
    srand(time(NULL));
    
    //input file stream
    ifstream file("Sources/layouts.txt");
    
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
/*void print_grid()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << " + " << "-";
        }
        cout << " + \n";
        for (int j = 0; j < 9; j++)
        {   
            cout << " | " << grid[i][j];
        }
        cout << " | \n";
    }
    for (int j = 0; j < 9; j++)
    {
        cout << " + " << "-";
    }
    cout << " + \n";
}*/
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

//pozera na inputy v konzole - posuvanie sipkami
void key_input(string part) 
{
    int c = 0;
    switch((c=_getch())) {
    case KEY_UP:
        if(part=="insert")
        {
            pos_y--;
            if(pos_y < 0)
            {
                pos_y = 8;
            }
        }
        c = 0;
        break;
    case KEY_DOWN:
        if(part=="insert")
        {
            pos_y++;
            if (pos_y > 8)
            {
                pos_y = 0;
            }
        }
        c = 0;
        break;
    case KEY_LEFT:
        if(part=="insert")
        {
            pos_x--;
            if (pos_x < 0)
            {
                pos_x = 8;
            }
        }
        c = 0;
        break;
    case KEY_RIGHT:
        if(part=="insert")
        {
            pos_x++;
            if (pos_x > 8)
            {
                pos_x = 0;
            }
        }
        c = 0;
        break;
    default:
        c = 0;
        system("cls");
        print_grid();
        break;
    }
}
void insert_numbers()
{
    int last_pos_x = 0;
    int last_pos_y = 0;
    char last_char;
    
    last_pos_x = pos_x; 
    last_pos_y = pos_y;
    last_char = grid[pos_x][pos_y];

    key_input("insert");
    //cout << pos_x << "\n" << pos_y << "\n";
    grid[pos_y][pos_x] = 'x';
    grid[last_pos_y][last_pos_x] = last_char;

    //grid[x][y] = hodnota;
    //int hodnota = 0;
}

int main()
{
    grid_insert(check_grid);
    print_grid();
    while(1){
        insert_numbers();
    }
    
}