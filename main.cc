#include "board.h"
#include "cell.h"
#include "display.h"
#include "observer.h"
#include "phase.h"
#include "player.h"
#include "subject.h"
#include "tile.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <exception>

using namespace std;

string filename = "";
int zeroASCII = 48;
int nineASCII = 57;
int seed = 0;

string toLower(string s) {
	string toReturn = "";
	for (char& c : s) {
		string r(1, c);
		if (c <= 'Z' && c >= 'A') {
			r = string(1, c - ('A' - 'a'));
		}	
		toReturn.append(r);
	}
	return toReturn;
}

void saveEOF(Board& board, int currentTurn) {
	board.save("backup.sv", currentTurn);
}


bool is_int(string& s) {
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] >= zeroASCII && s[i] <= nineASCII) {
			continue;
		} else {
			return false;
		}
	}
	return true;
}

string toString(Colour colour) {
    if (colour == Colour::Blue) {
        return "Blue";
    } else if (colour == Colour::Red) {
        return "Red";
    } else if (colour == Colour::Orange) {
        return "Orange";
    } else if (colour == Colour::Yellow) {
        return "Yellow";
    } else if (colour == Colour::NoColour) {
        return "No Colour";
    }
}

void beginning_game(Board& board) {
    string location;
    int location_int;
    vector<Colour> players;
    players.emplace_back(Colour::Blue);
    players.emplace_back(Colour::Red);
    players.emplace_back(Colour::Orange);
    players.emplace_back(Colour::Yellow);
    players.emplace_back(Colour::Yellow);
    players.emplace_back(Colour::Orange);
    players.emplace_back(Colour::Red);
    players.emplace_back(Colour::Blue);
    for (int i = 0; i < 8; ++i) {
        cout << board;
        cout << "Student " << toString(players[i]) << ", where do you want to complete an Assignment?" << endl;
        while(true) {
            cout << "> ";
            if (!(cin >> location)) {
                exit(0);
            }
            if (is_int(location) == false) {
                cout << "Invalid command." << endl;
                continue;
            }
            location_int = stoi(location);
            if (location_int > 53) {
                cout << "You cannot build here." << endl;
                continue;
            }
            board.progressCell(location_int, players[i], CellType::Vertex, true, "complete");
            break;
        }
    }
    cout << board;
}

void beginning_turn(Board& board, int turn);
void ending_turn(Board& board, int turn);
bool ending_game(Board& board, string colour);

bool turn(Board& board, int turn = 0) {
    int counter = turn;
    Colour winnerColour = Colour::NoColour;
    while (true) {
        int current_turn = counter % 4;
        winnerColour = board.checkWinner();//check if correct
        if (winnerColour != Colour::NoColour) {
            break;
        }
        beginning_turn(board, current_turn);
        ending_turn(board, current_turn);
        ++counter;
    }
    return ending_game(board, toString(winnerColour));
}

void beginning_turn(Board& board, int turn) {
    string command;
    vector<Colour> players;
    players.emplace_back(Colour::Blue);
    players.emplace_back(Colour::Red);
    players.emplace_back(Colour::Orange);
    players.emplace_back(Colour::Yellow);
    cout << "Student " << toString(players.at(turn));
    cout << "'s turn." << endl;
    board.printStatus(players.at(turn));
    bool loaded = false;
    while (true) {
        cout << "> ";
        if(!(cin >> command)) {
            saveEOF(board, turn);
            throw ExceptionEOF();
        }
        if (command == "load") {
            loaded = true;
            continue;
        }
        if (command == "fair") {
            loaded = false;
            continue;
        }
        if (command == "roll") {
            int rollRes = board.rollDice(players.at(turn), loaded);//check if correct
            if (rollRes == 7) {
                board.moveGeese(players.at(turn));
            } else {
                board.distributeResources(rollRes);
            }
            break;
        }
        else {
            cout << "Invalid command." << endl;
            continue;
        }
    }
    return;
}

ResourceType toRes(string s) {
	if (toLower(s) == "caffeine") {
		return ResourceType::Caffeine;
	} else if (toLower(s) == "lecture") {
		return ResourceType::Lecture;
	} else if (toLower(s) == "lab") {
		return ResourceType::Lab;
	} else if (toLower(s) == "study") {
		return ResourceType::Study;
	} else if (toLower(s) == "tutorial") {
		return ResourceType::Tutorial;
	} else {
		return ResourceType::None;
	}
}

Colour toColour(string s) {
    s = toLower(s);
    if (s == "blue") {
        return Colour::Blue;
    } else if (s == "orange") {
        return Colour::Orange;
    } else if (s == "yellow") {
        return Colour::Yellow;
    } else if (s == "red") {
        return Colour::Red;
    } else {
        return Colour::NoColour;
    }
}

void ending_turn(Board& board, int turn) {
    int location_int;
    string command;
    vector<Colour> players;
    players.emplace_back(Colour::Blue);
    players.emplace_back(Colour::Red);
    players.emplace_back(Colour::Orange);
    players.emplace_back(Colour::Yellow);
    while (true) {
        cout << "> ";
        if(!(cin >> command)) {
            saveEOF(board, (turn + 1) % 4);
            throw ExceptionEOF();
        }
        if (command == "board") {
            cout << board;
            continue;
        }
        if (command == "status") {
            board.printStatus(players[0]);
            board.printStatus(players[1]);
            board.printStatus(players[2]);
            board.printStatus(players[3]);
            continue;
        }
        if (command == "criteria") {
            board.printCompletion(players[turn]);
            continue;
        }
        if (command == "achieve") {
            string location;
            if(!(cin >> location)) {
                saveEOF(board, (turn + 1) % 4);
                throw ExceptionEOF();
            }
            if (is_int(location) == false) {
                cout << "Invalid command." << endl;
                continue;
            }
            location_int = stoi(location);
            if (location_int > 71) {
                cout << "You cannot build here." << endl;
                continue;
            }
            board.progressCell(location_int, players.at(turn), CellType::Edge, false, "achieve");
            continue;
        }
        if (command == "complete") {
            string location;
            if(!(cin >> location)) {
                saveEOF(board, (turn + 1) % 4);
                throw ExceptionEOF();
            }
            if (is_int(location) == false) {
                cout << "Invalid command." << endl;
                continue;
            }
            location_int = stoi(location);
            if (location_int > 53) {
                cout << "You cannot build here." << endl;
                continue;
            }
            board.progressCell(location_int, players.at(turn), CellType::Vertex, false, "complete");
            continue;
        }
        if (command == "improve") {
            string location;
            if(!(cin >> location)) {
                saveEOF(board, (turn + 1) % 4);
                throw ExceptionEOF();
            }
            if (is_int(location) == false) {
                cout << "Invalid command." << endl;
                continue;
            }
            location_int = stoi(location);
            if (location_int > 53) {
                cout << "You cannot build here." << endl;
                continue;
            }
            board.progressCell(location_int, players.at(turn), CellType::Vertex, false, "improve");
            continue;
        }
        if (command == "trade") {
            string target;
            string give;
            string take;
            if(!(cin >> target >> give >> take)) {
                saveEOF(board, (turn + 1) % 4);
                throw ExceptionEOF();
            }
            bool invalid = target != "Blue" || target != "Red" || target != "Orange" || target != "Yellow";
            if (invalid || target == toString(players.at(turn))) { //does trade check to see whether it's trading with itself?
                cout << "Invalid command." << endl;
                continue;
            }
            if (give != "CAFFEINE" || give != "LAB" || give != "LECTURE" || give != "STUDY" || give != "TUTORIAL") {
                cout << "Invalid command." << endl;
                continue;
            }
            if (take != "CAFFEINE" || take != "LAB" || take != "LECTURE" || take != "STUDY" || take != "TUTORIAL") {
                cout << "Invalid command." << endl;
                continue;
            }
            board.tradeResources(players.at(turn), toColour(target), toRes(give), toRes(take));
            continue;
        }
        if (command == "save") {
            string file;
            if(!(cin >> file)) {
                saveEOF(board, (turn + 1) % 4);
                throw ExceptionEOF();
            }
            board.save(file, turn + 1 % 4);
            continue;
        }
        if (command == "help") {
            cout << "Valid commands:" << endl;
            cout << "board" << endl;
            cout << "status" << endl;
            cout << "criteria" << endl;
            cout << "achieve <goal>" << endl;
            cout << "complete <criterion>" << endl;
            cout << "improve <criterion>" << endl;
            cout << "trade <colour> <give> <take>" << endl;
            cout << "next" << endl;
            cout << "save <file>" << endl;
            cout << "help" << endl;
            continue;
        }
        if (command == "next") {
            break;
        }
        else {
            cout << "Invalid command." << endl;
            continue;
        } //do we need an else since we use if continue
    }
    return;
}

bool ending_game(Board& board, string colour) {
    string answer;
    cout << "Congratulations! " << colour << " has won!" << endl;
    cout << "Would you like to play again?" << endl;
    while (true) {
        cout << "> ";
        if(!(cin >> answer)) {
            saveEOF(board, 0);
            throw ExceptionEOF();
        }
        if (answer == "yes") {
            return true;
        }
        if (answer == "no") {
            return false;
        }
        else {
            cout << "Invalid command." << endl;
            continue;
        }
    }
}

int main (int argc, char* argv[]) {
    bool play = true;
    while (play){
        Board board; //default constructor
        try{
            if (argc == 1) {
                board.initialize(seed);
                beginning_game(board);
                play = turn(board);
            } else if (argc == 2) {
                    if (string(argv[1]) != "-seed") {
                    cout << "Invalid Game Settings" << endl;
                    exit(1);
                    }
                    board.initialize(seed); //this initializes a board without a seed number. This will always spawn the same board.
                    beginning_game(board);
                    play = turn(board);
            } else if (argc == 3) {
                if (string(argv[1]) == "-seed") {
                    string seedString = argv[2];
                    if (!is_int(seedString)) {
                        cout << "Invalid Game Settings" << endl;
                        exit(1);
                    } else {
                        string seedString = argv[2];
                        seed = stoi(seedString);
                        board.initialize(seed); //this initializes a board with a seed number.
                        beginning_game(board);
                        play = turn(board);
                    }
                } else if (string(argv[1]) == "-load") {
                    filename = argv[2];
                    int currentTurn = board.load(filename); //this initializes a board with a load file.
                    play = turn(board, currentTurn);
                } else if (string(argv[1]) == "-board") {
                    filename = argv[2];
                    board.loadBoard(filename); //this initializes a board with a board file.
                    beginning_game(board);
                    play = turn(board);
                } else {
                    cout << "Invalid Game Settings" << endl;
                    exit(1);
                }
            } else {
                cout << "Invalid Game Settings" << endl;
                exit(1);
            }
        } catch (ExceptionEOF& e){
            exit(1);
        }
        
    }
}
