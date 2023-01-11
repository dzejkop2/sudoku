#define _WIN32_WINNT 0x0500
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

char grid[9][9] = {};
char check_grid[9][9] = {};

int pos_x = 0;
int pos_y = 0;

int difficulty = 1;

void prestavka(float delay) {
    delay *= CLOCKS_PER_SEC;
    clock_t now = clock();
    while (clock() - now < delay);
}

//cout << setw(40) << s[i];    Toto mi tu nechajte, mam s tym plany a nechcel som to zabudnut loliky lol

void vypis(string s) {
    cout << setw(40);
    for (int i = 0; i < s.length(); i++) {
        cout << s[i];
        Sleep(70);
    }
    prestavka(1);
}
void credits_exit() {
    string entre = "\n \n \n \n \n \n \n \n \n \n \n \n";
    string vyrobene = "Vyrobene: \n";
    string simonko = "Simon \"Simiye\" Murin";
    string kubko1 = "Jakub \"Dzejkop\" Geleta";
    string kubko2 = "Jakub \"Mr.Papa\" Hulin\n";
    string prianie = "Prajeme ti vela stastia v zivote <3";
    system("cls"); cout << entre << setw(45);
    vypis(vyrobene);
    cout << endl;
    vypis(simonko);
    cout << endl;
    vypis(kubko1);
    cout << endl;
    vypis(kubko2);
    cout << endl;
    vypis(prianie);
    prestavka(3);
    exit(0);
}

int credits_win() {
    string entre = "\n \n \n \n \n \n \n \n \n \n \n \n";
    string grat = "Gratulujem!";
    string vyhr = "Vyhral si!";
    string konec = "Prajes si vypnut hru alebo sa vratit do menu: ";
    string jedna = "1. Vypnut"; //mic check jedna...
    string dva = "2. Menu\n"; //dva
    system("cls"); cout << entre << setw(45);
    vypis(grat);
    cout << endl;
    vypis(vyhr);
    cout << endl;
    vypis(konec);
    cout << endl;
    vypis(jedna);
    cout << endl;
    vypis(dva);
    int jednadva;
    cin >> jednadva;
    return jednadva;
}

void key_input(string instert);

//zafarbi nasledujuci text podla zadanej farby
void color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void setpos(int x, int y)
{
    COORD CursorPosition;
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

//zadavanie hodnuot do hracej plochy
void grid_insert(char a[][9], char a_check[][9], string subor)
{
    string line;
    vector<string> lines;
    int column = 0;
    int row = 0;

    srand(time(NULL));

    //input file stream
    ifstream file(subor);

    //spocita pocet riadkov v subore 
    int total_lines = 0;
    while (getline(file, line))
    {
        total_lines++;
        lines.push_back(line);
    }

    //generuje nahodne cislo    
    int random_number = rand() % total_lines;

    string using_line = lines[random_number];
    //zapisovanie do hracieho pola
    for (int i = 0; i < 89; i++)
    {
        if (using_line[i] == ';') {
            row++;
            column = 0;
        }
        else {
            //-48 pretoze davame char do int a inak to neslo [opravene :( bude mi to chybat]
            a[row][column] = using_line[i];
            column++;
        }
    }
    column = 0;
    row = 0;
    //zapisovanie do kontrolneho pola
    for (int i = 94; i < using_line.length(); i++)
    {
        if (using_line[i] == ';') {
            row++;
            column = 0;
        }
        else {
            a_check[row][column] = using_line[i];
            column++;
        }
    }
}

void vypis_vyzvu()
{
    cout << "Pre vybratie policka stlacte ";
    color(6);
    cout << "\"ENTER\"";
}

void sudoku(int a)
{
    color(a);
    cout << "\n\t########\n";
    cout << "\t#";
    color(8);
    cout << "Sudoku";
    color(a);
    cout << "#" << "\t|| ";
    if (difficulty == 1)
    {
        color(10);
        cout << "Easy";
    }
    else if (difficulty == 2)
    {
        color(6);
        cout << "Medium";
    }
    else
    {
        color(4);
        cout << "Hard";
    }
    color(a);
    cout << " ||\n";
    cout << "\t########\n\n";
}

//vypisovanie plochy
void print_grid()
{
    sudoku(9);
    color(9);
    //vypise hornu hranicu
    for (int i = 0; i < 37; i++)
    {
        cout << "#";
    }
    cout << "\n";
    for (int f = 0; f < 3; f++)
    {
        //vypise po 3 riadkoch
        for (int i = 1; i < 6; i++)
        {
            if (i % 2 == 1) {
                cout << "#";
                for (int j = 0; j < 3; j++)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        //zafarbi poziciu hraca
                        if ((((i + 1) / 2) - 1) + (f * 3) == pos_y && (j * 3 + k) == pos_x)
                        {
                            color(12);
                            cout << " " << grid[(((i + 1) / 2) - 1) + (f * 3)][j * 3 + k];
                            color(9);
                            cout << " |";
                        }
                        else if (grid[(((i + 1) / 2) - 1) + (f * 3)][j * 3 + k] == '0')
                        {
                            cout << "   |";
                        }
                        else if (grid[(((i + 1) / 2) - 1) + (f * 3)][j * 3 + k] == 'x')
                        {
                            color(12);
                            cout << " " << 'x' << " |";
                            color(9);
                        }
                        else
                        {
                            color(7);
                            cout << " " << grid[(((i + 1) / 2) - 1) + (f * 3)][j * 3 + k];
                            color(9);
                            cout << " |";
                        }
                    }
                    cout << "\b\b" << " #";
                }
            }
            else {
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
    setpos(45, 13);
    vypis_vyzvu();
    setpos(0, 25);
}

void UP()
{
    pos_y--;
    if (pos_y < 0)
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

bool check_win()
{
    for (int i = 0; i < 9; i++)
    {
        for (int b = 0; b < 9; b++)
        {
            if (grid[i][b] != '0' && grid[i][b] != 'x')
            {
                continue;
            }
            else return false;
        }
    }
    return true;
}

void refresh()
{
    check_win();
    system("cls");
    print_grid();
}

void ENTER()
{
    int insert;
    if (grid[pos_y][pos_x] == 'x')
    {
        cout << "Zadaj hodnotu ktoru chces zadat: "; color(11);
        cin >> insert; color(7);
        if (insert > 0 && insert <= 9)
        {
            grid[pos_y][pos_x] = insert + 48; // 48 incident kde plujeme int do charu, neni to najlepsie riesenie ale je to lahsie ;)
            if (grid[pos_y][pos_x] == check_grid[pos_y][pos_x])
            {
                refresh();
            }
            else
            {
                grid[pos_y][pos_x] = 'x';
                refresh();
                cout << "Zla odpoved!\n";
            }
        }
        else
        {
            cout << "Skus znova!\n";
        }
    }
    else return;
}

//pozera na inputy v konzole
void key_input(string part)
{
    char insert;
    int c = 0;
    switch ((c = _getch())) {
    case KEY_UP:
        if (part == "insert")
        {
            c = 0;
            UP();
            refresh();
        }
        break;
    case KEY_DOWN:
        if (part == "insert")
        {
            c = 0;
            DOWN();
            refresh();
        }
        break;
    case KEY_LEFT:
        if (part == "insert")
        {
            c = 0;
            LEFT();
            refresh();
        }
        break;
    case KEY_RIGHT:
        if (part == "insert")
        {
            c = 0;
            RIGHT();
            refresh();
        }
        break;
    case KEY_ENTER:
        if (part == "insert")
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

void uvitanie() {
    system("color 9");
    string entre = "\n \n \n \n \n \n \n \n \n \n \n \n";
    cout << entre << setw(50) << "Ahoj!\n";
    prestavka(1);
    system("cls"); cout << entre << setw(53) << "Vitaj v nasom sudoku!" << endl;
    prestavka(1); system("cls");
}

int menu()
{
    string subor = "Sources/easy_layouts.txt";
    string menu[3] = { "Start", "Nastavenia", "Koniec" };
    string nastavenia[2] = { "Obtiaznost", "Work in progress(kontrola policok)" };
    string obtiaznosti[3] = { "Easy", "Medium", "Hard" };
    string entre = "\n \n \n \n \n \n \n \n \n \n \n \n";
    ///////////////////////////////////////
    system("color 9");
    while (1)
    {
        system("cls");
        cout << entre;
        for (int i = 0; i < 3; i++)
        {
            cout << setw(40) << i + 1 << ". " << menu[i] << endl;
        }

        int volba;
        cout << "Zadaj cislo od 1 do 3: ";
        cin >> volba;
        switch (volba)
        {
        case 1:
            bool win;
            system("cls");
            grid_insert(grid, check_grid, subor);
            print_grid();
            while (1)
            {
                check_win();
                if (check_win() == true)
                {
                    int jednadva = credits_win();
                    if (jednadva == 1)
                    {
                        exit(0);
                    }
                    else if (jednadva == 2)
                    {
                        system("cls");
                        cout << entre;
                        return 1;
                    }


                }
                else {
                    key_input("insert");
                    continue;
                }
            }
        case 2:
            system("cls");
            cout << entre;
            for (int y = 0; y < 2; y++)
            {
                cout << setw(40) << y + 1 << ". " << nastavenia[y] << endl;
            }
            {
                int vyber;
                cin >> vyber;
                switch (vyber) {
                case 1:
                    system("cls");
                    cout << entre;
                    for (int z = 0; z < 3; z++) {
                        cout << setw(40) << z + 1 << ". " << obtiaznosti[z] << endl;
                    }
                    int diff;
                    cin >> diff;
                    switch (diff)
                    {
                    case 1:
                        subor = "Sources/easy_layouts.txt";
                        difficulty = 1;
                        system("cls");
                        cout << entre << setw(53) << "Nastavil si difficulty Easy";
                        prestavka(1);
                        system("cls");
                        cout << entre;
                        continue;
                    case 2:
                        subor = "Sources/medium_layouts.txt";
                        difficulty = 2;
                        system("cls");
                        cout << entre << setw(53) << "Nastavil si difficulty Medium";
                        prestavka(1);
                        system("cls");
                        cout << entre;
                        continue;
                    case 3:
                        subor = "Sources/hard_layouts.txt";
                        difficulty = 3;
                        system("cls");
                        cout << entre << setw(53) << "Nastavil si difficulty Hard";
                        prestavka(1);
                        system("cls");
                        cout << entre;
                        continue;
                    case 4:
                        system("cls");
                        cout << entre;
                        int jednadva;
                        jednadva = credits_win(); system("cls"); cout << entre;
                        if (jednadva == 1)
                        {
                            credits_exit(); exit(0);
                        }
                        else if (jednadva == 2) {
                            cout << entre;
                            return 1;
                        }

                        continue;
                    default: continue;
                    }
                case 2:
                    cout << "Toto neni spravene, vypadni dzejkop"; return 1;
                }

            }
        case 3:
            credits_exit(); break;
        default:
            cout << "Zadajte cislo 1-3" << endl;
        }
    }
}

int main()
{
    system("MODE 90,32");
    SetWindowLong(GetConsoleWindow(), GWL_STYLE, GetWindowLong(GetConsoleWindow(), GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
    uvitanie();
    while (1) {
        menu();
        system("cls");
    }
}