#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <math.h>
#include "tile.h"
#include "display.h"
#include "player.h"
#include "observer.h"
#include "phase.h"
#include "maps.h"

// Board will handle lost resources if player has more than 10 resources

class Board {
        std::vector<Cell> vertices;
        std::vector<Cell> edges;
        std::vector<Tile> tiles;
        std::vector<Player> players;
        std::vector<int> saveDice;
        std::vector<int> saveRes;
        
        Display *display = nullptr;
        int goosePosition; //on initialization will start at position 20 outside the board
        int currentTurn; // can be 0, 1, 2, or 3 
        public:
                ~Board();
                Player getPlayerByColour(Colour playerToGet);
                Colour checkWinner();
                void initialize(int seed);
                int rollDice(Colour curr, bool loaded);
                void distributeResources(int roll);
                void moveGeese(Colour currPlayer);
                void tradeResources(Colour currPlayer, Colour offPlayer, ResourceType given, ResourceType recieved);
		void progressCell(int cellPos, Colour currPlayer, CellType cellType, bool bypass, std::string buildType);
                friend std::ostream &operator<<(std::ostream &out, const Board &board);
                std::string resourceToString(ResourceType res);
                void printStatus(Colour currentPlayer);
                void printCompletion(Colour currentPlayer);
                void save(std::string file, int currTurn);
                int load(std::string file);
                void loadBoard(std::string file);
                Colour toColour(std::string s);
                ResourceType toRes(std::string s);
                std::string toLower(std::string s);
                std::vector<int> createDiceRolls(int seed);
        private:
		
};
#endif
