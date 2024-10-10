#pragma once
#include <iostream>
#include <fstream>
#include <limits>
#include <windows.h>
#include <locale>

using namespace std;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printtitle(){
    setlocale(LC_ALL, "en_US.UTF-8");
    system("cls");
    string menu_ascii[] = {
        "   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
        "   *  ___   __  __     _     ___   _____       _     ___     _     ___   _____   __  __   ___   _  _   _____   ___  *",
        "   * / __| |  \\/  |   /_\\   | _ \\ |_   _|     /_\\   | _ \\   /_\\   | _ \\ |_   _| |  \\/  | | __| | \\| | |_   _| / __| *",
        "   * \\__ \\ | |\\/| |  / _ \\  |   /   | |      / _ \\  |  _/  / _ \\  |   /   | |   | |\\/| | | _|  | .` |   | |   \\__ \\ *",
        "   * |___/ |_|  |_| /_/ \\_\\ |_|_\\   |_|     /_/ \\_\\ |_|   /_/ \\_\\ |_|_\\   |_|   |_|  |_| |___| |_|\\_|   |_|   |___/ *",
        "   *                                                                                                                *",
        "   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"
    };
    gotoxy(50,5);
    cout<<endl;
    for (int i = 0; i < 7; i++) {
        cout << menu_ascii[i] << endl;
    }
}

void printtitle1(){
    setlocale(LC_ALL, "en_US.UTF-8");
    system("cls");
    string menu_ascii[] = {
        "   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
        "   *  ___   __  __     _     ___   _____       _     ___     _     ___   _____   __  __   ___   _  _   _____   ___  *",
        "   * / __| |  \\/  |   /_\\   | _ \\ |_   _|     /_\\   | _ \\   /_\\   | _ \\ |_   _| |  \\/  | | __| | \\| | |_   _| / __| *",
        "   * \\__ \\ | |\\/| |  / _ \\  |   /   | |      / _ \\  |  _/  / _ \\  |   /   | |   | |\\/| | | _|  | .` |   | |   \\__ \\ *",
        "   * |___/ |_|  |_| /_/ \\_\\ |_|_\\   |_|     /_/ \\_\\ |_|   /_/ \\_\\ |_|_\\   |_|   |_|  |_| |___| |_|\\_|   |_|   |___/ *",
        "   *                                                                                                                *",
        "   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"
    };
    gotoxy(50,2);
    cout<<endl;
    for (int i = 0; i < 7; i++) {
        cout << menu_ascii[i] << endl;
    }
}

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}