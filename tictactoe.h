#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <vector>
#include <string>

// Функции отображения
void drawboard(const std::vector<char>& board);
void showMenu();

// Функции проверки состояния игры
bool checkwin(const std::vector<char>& board, char player);
bool checkdraw(const std::vector<char>& board);

// Основные игровые функции
int playGame();
void startNewGame();
void restartGame(std::vector<char>& board, char& currentPlayer);
void playGameWithParams(std::vector<char>& board, char& currentPlayer); // <-- добавлено

// Функции работы с файлами
bool saveGame(const std::vector<char>& board, char currentPlayer, const std::string& filename);
bool loadGame(std::vector<char>& board, char& currentPlayer, const std::string& filename);

#endif