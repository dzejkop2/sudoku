#include <iostream>
#include <cstdio>
#include <ctime>
#include <Windows.h>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

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
//cekuje pri lahsiej obtiaznosti cekovania(cekuje input s uz dokoncenym sudoku)
bool check_easy()
{

} 

//cekuje relativne input pouzivatela
bool check_input()
{
    
}

void insert_numbers()
{
    int x;
    int y;
    int hodnota;
    cout << "zadaj hodnotu x: ";
    cin >> x; cout << "\n";
    cout << "zadaj hodnout y: ";
    cin >> y ; cout << "\n";
    cout << "zadaj hodnotu ktoru chces vlozit: ";
    cin >> hodnota; cout << "\n";
    grid[x - 1][y - 1] = hodnota;
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

int main()
{
    grid_insert(check_grid);
    for (int i = 0; i < 10; i++)
    {
        print_grid();
        insert_numbers();
    }
}