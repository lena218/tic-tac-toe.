#include <iostream>
#include <vector>
#include <fstream>
#include "tictactoe.h"

using namespace std;


void showMenu() {
    vector<char> board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char currentPlayer = 'X';
    bool gameInProgress = false;
    
    while (true) {
        cout << "\n=== КРЕСТИКИ-НОЛИКИ ===\n";
        cout << "1. Начать новую игру\n";
        cout << "2. Начать сначала (перезапуск)\n";
        cout << "3. Загрузить игру из файла\n";
        cout << "4. Сохранить игру в файл\n";
        cout << "5. Выйти из игры\n";
        cout << "Выберите пункт меню: ";
        
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "Неверный ввод!" << endl;
            continue;
        }
        
       
        while (cin.get() != '\n');
        
        switch (choice) {
            case 1:
                startNewGame();
                gameInProgress = true;
                break;
            case 2:
                if (gameInProgress) {
                    restartGame(board, currentPlayer);
                    playGameWithParams(board, currentPlayer);
                } else {
                    cout << "Сначала начните игру (пункт 1)!\n";
                }
                break;
            case 3:
                {
                    string filename;
                    cout << "Введите имя файла для загрузки: ";
                    getline(cin, filename);
                    if (loadGame(board, currentPlayer, filename)) {
                        cout << "Игра загружена успешно!\n";
                        gameInProgress = true;
                        playGameWithParams(board, currentPlayer);
                    }
                }
                break;
            case 4:
                if (gameInProgress) {
                    string filename;
                    cout << "Введите имя файла для сохранения: ";
                    getline(cin, filename);
                    if (saveGame(board, currentPlayer, filename)) {
                        cout << "Игра сохранена успешно!\n";
                    }
                } else {
                    cout << "Сначала начните игру (пункт 1)!\n";
                }
                break;
            case 5:
                cout << "До свидания!\n";
                return;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
                break;
        }
    }
}


void drawboard(const vector<char>& board) {
    cout << "\n";
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << "\n";
    cout << "-----------\n";
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << "\n";
    cout << "-----------\n";
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << "\n";
    cout << "\n";
}


bool checkwin(const vector<char>& board, char player) {
    return (
        (board[0] == player && board[1] == player && board[2] == player) ||
        (board[3] == player && board[4] == player && board[5] == player) ||
        (board[6] == player && board[7] == player && board[8] == player) ||
        (board[0] == player && board[3] == player && board[6] == player) ||
        (board[1] == player && board[4] == player && board[7] == player) ||
        (board[2] == player && board[5] == player && board[8] == player) ||
        (board[0] == player && board[4] == player && board[8] == player) ||
        (board[2] == player && board[4] == player && board[6] == player)
    );
}


bool checkdraw(const vector<char>& board) {
    for (char cell : board) {
        if (cell != 'X' && cell != 'O') {
            return false;
        }
    }
    return true;
}


void startNewGame() {
    vector<char> board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char currentPlayer = 'X';
    cout << "Игрок X начинает первым.\n";
    playGameWithParams(board, currentPlayer);
}
void restartGame(vector<char>& board, char& currentPlayer) {
    board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    currentPlayer = 'X';
    cout << "Игра перезапущена. Игрок X начинает первым.\n";
}


void playGameWithParams(vector<char>& board, char& currentPlayer) {
    bool gameEnded = false;
    
    while (!gameEnded) {
        drawboard(board);
        
        int move;
        cout << "Игрок " << currentPlayer << ", ваш ход: ";
        
        if (!(cin >> move)) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "Неверный ввод!" << endl;
            continue;
        }
        
        if (move < 1 || move > 9) {
            cout << "Введите число от 1 до 9.\n";
            continue;
        }
        
        if (board[move - 1] == 'X' || board[move - 1] == 'O') {
            cout << "Клетка занята! Выберите другую.\n";
            continue;
        }
        
        board[move - 1] = currentPlayer;
        
        if (checkwin(board, currentPlayer)) {
            drawboard(board);
            cout << "Игрок " << currentPlayer << " победил!\n";
            gameEnded = true;
        } else if (checkdraw(board)) {
            drawboard(board);
            cout << "Ничья!\n";
            gameEnded = true;
        } else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
    

    cout << "\nНажмите Enter для возврата в меню...";
    cin.ignore();
    cin.get();
}


int playGame() {
    startNewGame();
    return 0;
}


bool saveGame(const vector<char>& board, char currentPlayer, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл для записи.\n";
        return false;
    }
    
    
    for (char cell : board) {
        file << cell << " ";
    }
    file << endl;
    
    
    file << currentPlayer << endl;
    
    file.close();
    return true;
}


bool loadGame(vector<char>& board, char& currentPlayer, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл для чтения.\n";
        return false;
    }
    

    for (int i = 0; i < 9; i++) {
        if (!(file >> board[i])) {
            cout << "Ошибка: файл поврежден или имеет неверный формат.\n";
            return false;
        }
    }
    

    if (!(file >> currentPlayer)) {
        cout << "Ошибка: не удалось загрузить информацию о текущем игроке.\n";
        return false;
    }
    
    file.close();
    return true;
}
