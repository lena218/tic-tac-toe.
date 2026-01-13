#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <vector>
#include <string>


void drawboard(const std::vector<char>& board);
void showMenu();


bool checkwin(const std::vector<char>& board, char player);
bool checkdraw(const std::vector<char>& board);


void startNewGame(std::vector<char>& board, char& currentPlayer, bool& gameInProgress);
void playGameWithParams(std::vector<char>& board, char& currentPlayer, bool& gameInProgress);


bool saveGame(const std::vector<char>& board, char currentPlayer, const std::string& filename);
bool loadGame(std::vector<char>& board, char& currentPlayer, const std::string& filename);

#endif
