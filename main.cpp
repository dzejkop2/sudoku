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

int grid[9][9] = {{0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0}};

int check_grid[9][9] = {};

int pos_x = 0;

int pos_y = 0;

//cekuje pri lahsiej obtiaznosti cekovania(cekuje input s uz dokoncenym sudoku)
bool check_easy()
{

} 

//cekuje relativne input pouzivatela
bool check_input()
{
    
}

//zadavanie hodnuot do hracej plochy
void grid_insert(int a[][9])
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
            a[row][column]= using_line[i] - 48;
            column++;
        }
    }
}

//vypisovanie plochy
void print_grid()
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
}

//pozera na inputy v konzole - posuvanie sipkami
void key_input(string part) 
{
    int c = 0;
    switch((c=getch())) {
    case KEY_UP:
        if(part=="insert")
        {
            //cout << "up";
            pos_y--;
            if(pos_y < 0)
            {
                pos_y = 8;
            }
        }
        break;
    case KEY_DOWN:
        if(part=="insert")
        {
            //cout << "down";
            pos_y++;
            if (pos_y > 8)
            {
                pos_y = 0;
            }
        }
        break;
    case KEY_LEFT:
        if(part=="insert")
        {
            //cout << "left";
            pos_x++;
            if (pos_x > 8)
            {
                pos_x = 0;
            }
        }
        break;
    case KEY_RIGHT:
        if(part=="insert")
        {
            //cout << "right";
            pos_x--;
            if (pos_x < 0)
            {
                pos_x = 8;
            }
        }
        break;
    default:
        c = 0;
        break;
    }
}
void insert_numbers(int x, int y)
{
    //int hodnota = 0;
    key_input("insert");
    cout << pos_x << "\n" << pos_y << "\n";
    //grid[x][y] = hodnota;
}

int main()
{
    int pos_x = 0;
    int pos_y = 0;
    grid_insert(check_grid);
    while(1){
        print_grid();
        system("cls");
        //insert_numbers(pos_x,pos_y);
    }
    
}