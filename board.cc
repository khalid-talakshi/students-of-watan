#include "board.h"
#include "cell.h"

using namespace std;

string Board::toLower(string s) {
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

Colour Board::toColour(string s) {
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

ResourceType Board::toRes(string s) {
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

Board::~Board() {
    delete display;
}

string Board::resourceToString(ResourceType res) {
    if (res == ResourceType::Lecture) {
        return "Lecture";
    } else if (res == ResourceType::Study) {
        return "Study";
    } else if (res == ResourceType::Lab) {
        return "Lab";
    } else if (res == ResourceType::Tutorial) {
        return "Tutorial";
    } else if (res == ResourceType::Caffeine) {
        return "Caffeine";
    } else if (res == ResourceType::None) {
        return "Netflix";
    }
}

void Board::initialize(int seed) {
    srand(seed);
    int amtTutorial = 3;
    int amtStudy = 3;
    int amtCaffeine = 4;
    int amtLab = 4;
    int amtLecture = 4;
    int amtNetflix = 1;
    int numCaffeine = 0;
    int numLab = 1;
    int numLecture = 2;
    int numStudy = 3;
    int numTutorial = 4;
    int numNetflix = 5;
    int amtResourcesRemaining = amtTutorial + amtStudy + amtCaffeine + amtLab + amtLecture + amtNetflix;
    int currentTile = 0;
    vector<int> diceSeq = createDiceRolls(seed);
    this->goosePosition = 20;
    this->currentTurn = 0;
    vertices.reserve(55);
    edges.reserve(73);
    tiles.reserve(20);
    players.reserve(5);
    while(amtResourcesRemaining > 0) {
        if (diceSeq.at(currentTile) == 7) {
            saveRes.emplace_back(7);
            Tile newTile{ResourceType::None, diceSeq.at(currentTile), currentTile};
            tiles.emplace_back(newTile);
            amtNetflix -= 1;
            amtResourcesRemaining -= 1;
            currentTile++;
        } else {
            int resourceNum = rand() % 5;
            if (resourceNum == 0) {
                if (amtCaffeine > 0) {
                    saveRes.emplace_back(0);
                    Tile newTile{ResourceType::Caffeine, diceSeq.at(currentTile), currentTile};
                    tiles.emplace_back(newTile);
                    amtCaffeine -= 1;
                    amtResourcesRemaining -= 1;
                    currentTile++;
                }
            } else if (resourceNum == 1) {
                if (amtLab > 0) {
                    saveRes.emplace_back(1);
                    Tile newTile{ResourceType::Lab, diceSeq.at(currentTile), currentTile};
                    tiles.emplace_back(newTile);
                    amtLab -= 1;
                    amtResourcesRemaining -= 1;
                    currentTile++;
                }
            } else if (resourceNum == 2) {
                if (amtLecture > 0) {
                    saveRes.emplace_back(2);
                    Tile newTile{ResourceType::Lecture, diceSeq.at(currentTile), currentTile};
                    tiles.emplace_back(newTile);
                    amtLecture -= 1;
                    amtResourcesRemaining -= 1;
                    currentTile++;
                }
            } else if (resourceNum == 3) {
                if (amtLecture > 0) {
                    saveRes.emplace_back(3);
                    Tile newTile{ResourceType::Study, diceSeq.at(currentTile), currentTile};
                    tiles.emplace_back(newTile);
                    amtLecture -= 1;
                    amtResourcesRemaining -= 1;
                    currentTile++;
                }
            } else if (resourceNum == 4) {
                if (amtTutorial > 0) {
                    saveRes.emplace_back(4);
                    Tile newTile{ResourceType::Tutorial, diceSeq.at(currentTile), currentTile};
                    tiles.emplace_back(newTile);
                    amtLab -= 1;
                    amtResourcesRemaining -= 1;
                    currentTile++;
                }
            }
        }
    }
    for (int i = 0; i < 72; i++) {
        Cell createdCell{CellType::Edge, i};
        edges.emplace_back(createdCell);
    } 
    for (int i = 0; i < 54; i++) {
        Cell createdCell{CellType::Vertex, i};
        vertices.emplace_back(createdCell);
    }
    for (int i = 0; i < 4; i++) {
        Player createdPlayer{playerMap.at(i)};
        players.emplace_back(createdPlayer);
    }
    display = new Display(tiles);
    for (int i = 0; i < 19; i++) {
        tiles.at(i).attach(display);
        for (int m = 0; m < 6; m++) {
            tiles.at(i).attach(&edges.at(edgeOfTile.at(i).at(m)));
            tiles.at(i).attach(&vertices.at(vertexOfTile.at(i).at(m)));
            edges.at(edgeOfTile.at(i).at(m)).attach(&tiles.at(i));
            vertices.at(vertexOfTile.at(i).at(m)).attach(&tiles.at(i));
        }
    } 
    for (int i = 0; i < 54; i++) {
        vertices.at(i).attach(display);
        for (int m : edgeOfVertex.at(i)) {
            vertices.at(i).attach(&edges.at(m));
        }
    }
    for (int i = 0; i < 72; i++) {
        edges.at(i).attach(display);
        for (int m : vertexOfEdge.at(i)) {
            edges.at(i).attach(&vertices.at(m));
        }
    }
}

vector<int> Board::createDiceRolls(int seed) {
    srand(seed);
    int amt2 = 1;
    int amt3 = 2;
    int amt4 = 2;
    int amt5 = 2;
    int amt6 = 2;
    int amt7 = 1;
    int amt8 = 2;
    int amt9 = 2;
    int amt10 = 2;
    int amt11 = 2;
    int amt12 = 1;
    int sum = amt2 + amt3 + amt4 + amt5 + amt6 + amt7 + amt8 + amt9 + amt10 + amt11 + amt12;
    vector<int> diceSeq = {};
    while (sum > 0) {
        int diceRoll = rand() % 11 + 2;
        if (diceRoll == 2) {
            if (amt2 > 0) {
                diceSeq.emplace_back(2);
                amt2 -= 1;
                sum -= 1;
            }
        } else if (diceRoll == 3) {
            if (amt3 > 0) {
                diceSeq.emplace_back(3);
                amt3 -= 1;
                sum -= 1;
            }
        } else if (diceRoll == 4) {
            if (amt4 > 0) {
                diceSeq.emplace_back(4);
                amt4 -= 1;
                sum -= 1;
            } 
        } else if (diceRoll == 5) {
            if (amt5 > 0) {
                diceSeq.emplace_back(5);
                amt5 -= 1;
                sum -= 1;
            } 
        } else if (diceRoll == 6) {
            if (amt6 > 0) {
                diceSeq.emplace_back(6);
                amt6 -= 1;
                sum -= 1;
            } 
        } else if (diceRoll == 7) {
            if (amt7 > 0) {
                diceSeq.emplace_back(7);
                amt7 -= 1;
                sum -= 1;
            } 
        } else if (diceRoll == 8) {
            if (amt8 > 0) {
                diceSeq.emplace_back(8);
                amt8 -= 1;
                sum -= 1;
            } 
        } else if (diceRoll == 9) {
            if (amt9 > 0) {
                diceSeq.emplace_back(9);
                amt9 -= 1;
                sum -= 1;
            } 
        } else if (diceRoll == 10) {
            if (amt10 > 0) {
                diceSeq.emplace_back(10);
                amt10 -= 1;
                sum -= 1;
            } 
        } else if (diceRoll == 11) {
            if (amt11 > 0) {
                diceSeq.emplace_back(11);
                amt11 -= 1;
                sum -= 1;
            } 
        } else if (diceRoll == 12) {
            if (amt12 > 0) {
                diceSeq.emplace_back(12);
                amt12 -= 1;
                sum -= 1;
            } 
        } 
    }
    saveDice = diceSeq;
    return diceSeq;
}

Colour Board::checkWinner() {
    for (int i = 0; i < players.size(); i++) {
        if (players.at(i).getCriteria().size() >= 10) {
            Colour returnColour = players.at(i).getColour();
            return returnColour;
        }
    }
}

Player Board::getPlayerByColour(Colour playerToGet) {
    for (int i = 0; i < players.size(); i++) {
        if (players.at(i).getColour() == playerToGet) {
            return players.at(i);
        }
    }
}

int Board::rollDice(Colour curr, bool loaded) {
    Player currentPlayer = getPlayerByColour(curr);
    return currentPlayer.rollDice(loaded);
}

void Board::distributeResources(int roll) {
    try {
        for (int i = 0; i < 19; i++) {
            tiles.at(i).distributeResources(roll);
        }
    } catch(...) {
        // TODO check for exceptions
    }
}

void Board::moveGeese(Colour currPlayer) {
    Player currentPlayer = getPlayerByColour(currPlayer);
    // check how many resources a player owns
    // if more than 10, remove half of the resources
    for (int i = 0; i < players.size(); i++) {
        if (players.at(i).getCriteria().size() >= 10) {
            int numLost = floor(players.at(i).getCriteria().size() / 2);
            // add random loss function to player object (returns a map of lost objects)
            cout << "Student " << players.at(i).getColourStr() << " loses " << to_string(numLost) << " resources to the geese. They lose:" << endl;
            // TODO output map of all resources lost
            map<ResourceType, int> mapLostResources;
            for (int i = 0; i < numLost; i++) {
                ResourceType randResource = players.at(i).loseRandomResource(1);
                map<ResourceType, int>::iterator it;
                it = mapLostResources.find(randResource);
                if (it == mapLostResources.end()) {
                    mapLostResources.emplace(randResource, 1);
                } else {
                    mapLostResources.at(randResource) += 1;
                }
            }
            for (auto &i : mapLostResources) {
                cout << to_string(i.second) << " " << resourceToString(i.first) << endl;
            }
        }
    }
    // ask player which tile to move geese to
    // move geese to tile 
    cout << "Choose where to place the GEESE." << endl;
    bool correctInput = false;
    int tileNum;
    while (!correctInput) {
        cout << "> ";
        cin >> tileNum;
        if (0 <= tileNum && tileNum < 19) {
            correctInput = true;
            for (int i = 0; i < tiles.size(); i++) {
                if (tiles.at(i).hasGoose() == true) {
                    tiles.at(i).toggleGoose();
                }
            }
            tiles.at(tileNum).toggleGoose();
        } else {
            cout << "Please choose a valid tile" << endl;
        }
    }
    // check all cells on tile to see which players own them
    vector<Colour> playersOnTileColour = tiles.at(tileNum).getPlayers();
    vector<Player> playersOnTile = {};
    for (int i = 0; i < playersOnTileColour.size(); i++) {
        playersOnTile.emplace_back(getPlayerByColour(playersOnTileColour.at(i)));
    }
    if (playersOnTile.size() > 0) {
        for (int i = 0; i < playersOnTile.size(); i++) {
            if (playersOnTile.at(i).getResourceCount() == 0) {
                playersOnTile.erase(playersOnTile.begin()+i);
            }
        }
    }
    if (playersOnTile.size() > 0) {
        cout << "Student " << currentPlayer.getColourStr() << " can choose to steal from";
        for (int i = 0; i < playersOnTile.size(); i++) {
            cout << " " << playersOnTile.at(i).getColourStr();
        }
        cout << endl;
        // currentPlayer chooses a player to steal from (can't be themselves and has to be on that cell)
        cout << ">";
        string colour;
        cin >> colour;
        // output whethere steal was successful or not
        for (int i = 0; i < playersOnTile.size(); i++) {
            if (playersOnTile.at(i).getColour() == toColour(colour)) {
                ResourceType resourceLost = playersOnTile.at(i).loseRandomResource(1);
                currentPlayer.addResources(resourceLost, 1);
                cout << "Student " << currentPlayer.getColourStr() << " steals " << resourceToString(resourceLost) << " from student " << playersOnTile.at(i).getColourStr() << endl;
            }
        }
    } else {
        cout << "Student " << currentPlayer.getColourStr() << " has no students to steal from." << endl;
    }
}

void Board::tradeResources(Colour currPlayer, Colour offPlayer, ResourceType given, ResourceType recieved) {
    Player currentPlayer = getPlayerByColour(currPlayer);
    Player offeredPlayer = getPlayerByColour(offPlayer);
    //output the proposed trade
    cout << currentPlayer.getColourStr() << " offers " << offeredPlayer.getColourStr() << " one " << resourceToString(given) << " for one " << resourceToString(recieved) << "." << endl;
    
    //ask whether offeredPlayer accepts trade
    cout << "Does " << offeredPlayer.getColourStr() << " accept this offer?" << endl; 
    string resp;
    bool validResp = false;
    while (!validResp) {
        cout << ">";
        cin >> resp;
        if (resp == "yes") {
            validResp = true;
            // take resources away from players
            currentPlayer.removeResource(given, 1);
            offeredPlayer.removeResource(recieved, 1);
            // give resources to players
            currentPlayer.addResources(recieved, 1);
            offeredPlayer.addResources(given, 1);
        } else if (resp == "no") {
            validResp = true;
        } else {
            cout << "Please choose a valid response (yes/no)" << endl;
        }
    }
}

void Board::progressCell(int cellPos, Colour currPlayer, CellType cellType, bool bypass, string buildType) {
    Player currentPlayer = getPlayerByColour(currPlayer);
    Cell cellToBuild{CellType::Vertex, 0};
    if (cellType == CellType::Vertex) {
        cellToBuild = vertices.at(cellPos);
    } else if (cellType == CellType::Edge) {
        cellToBuild = edges.at(cellPos);
    }
    if (currentPlayer.hasEnoughResources(cellToBuild, buildType) || bypass) {
        if (buildType == "complete") {
            cellToBuild.updateProgress(Progress::Assignment, bypass, &currentPlayer);
        } else if (buildType == "achieve") {
            cellToBuild.updateProgress(Progress::Goals, bypass, &currentPlayer);
        } else if (buildType == "improve" && cellToBuild.getProgress() == Progress::Assignment) {
            cellToBuild.updateProgress(Progress::Midterm, bypass, &currentPlayer);
        } else if (buildType == "improve" && cellToBuild.getProgress() == Progress::Midterm) {
            cellToBuild.updateProgress(Progress::Midterm, bypass, &currentPlayer);
        }
    }
}

ostream &operator<<(ostream &out, const Board &board) {
    out << *board.display;
}

void Board::printStatus(Colour currentPlayer) {
    Player currPlayer = getPlayerByColour(currentPlayer);
    currPlayer.printStatus();
}

void Board::printCompletion(Colour currentPlayer) {
    Player currPlayer = getPlayerByColour(currentPlayer);
    currPlayer.printCompletions();
}

void Board::save(string file, int currTurn) {
    fstream saveFile{file};
    saveFile << to_string(currTurn) << endl;
    for (int i = 0; i < 4; i++) {
        saveFile << players.at(i).getStatus() << endl;
    }
    for (int i = 0; i < 19; i++) {
        saveFile << saveRes.at(i) << " " << saveDice.at(i);
        if ( i == 18) {
            saveFile << endl;
        } else {
            saveFile << " ";
        }
    }
    if (goosePosition != 20) {
        saveFile << goosePosition;
    }
    saveFile.close();
}

int Board::load(string file) {
    fstream loadFile{file};
    string currLine;
    int index = 0;
    int currentTurn;
    while(getline(loadFile, currLine)) {
        if (index == 0) {
            currentTurn = stoi(currLine);
        } else if (index >= 1 && index <= 4) {
            int charCount = 0;
            string s;
            Player createdPlayer{playerMap.at(stoi(currLine) - 1)};
            stringstream lineStream{currLine};
            while(lineStream >> s) {
                if (charCount == 0) {
                    createdPlayer.setResource(ResourceType::Caffeine, stoi(s));
                } else if (charCount == 1) {
                    createdPlayer.setResource(ResourceType::Lab, stoi(s));
                } else if (charCount == 2) {
                    createdPlayer.setResource(ResourceType::Lecture, stoi(s));
                } else if (charCount == 3) {
                    createdPlayer.setResource(ResourceType::Study, stoi(s));
                } else if (charCount == 4) {
                    createdPlayer.setResource(ResourceType::Tutorial, stoi(s));
                } else if (s == "g") {
                    while (s != "c") {
                        createdPlayer.addGoals(stoi(s));
                        charCount++;
                    }
                } else if (s == "c") {
                    bool isPos = true;
                    int pos;
                    while (!lineStream.eof()) {
                        if (isPos) {
                            pos = stoi(s);
                            isPos = false;
                        } else {
                            if (s == "1") {
                                createdPlayer.addCriteria(pos, Progress::Assignment);
                            } else if (s == "2") {
                                createdPlayer.addCriteria(pos, Progress::Midterm);
                            } else if (s == "3") {
                                createdPlayer.addCriteria(pos, Progress::Exam);
                            }
                            isPos = true;
                        }
                    }
                }
            }
            players.emplace_back(createdPlayer);
        } else if (index == 5) {
            bool isRes = true;
            ResourceType res;
            int pos = 0;
	        string s;
            stringstream lineStream{currLine};
            while (lineStream >> s) {
                if (isRes) {
                    if (s == "0") {
                        res = ResourceType::Caffeine;
                    } else if (s == "1") {
                        res = ResourceType::Lab;
                    } else if (s == "2") {
                        res = ResourceType::Lecture;
                    } else if (s == "3") {
                        res = ResourceType::Study;
                    } else if (s == "4") {
                        res = ResourceType::Tutorial;
                    } else if (s == "5") {
                        res = ResourceType::None;
                    }
                } else {
                    Tile newTile(res, std::stoi(s), pos);
                    tiles.emplace_back(newTile);
                }
            }
        } else if (index == 6) {
            goosePosition = stoi(currLine);
        }
    }
    for (int i = 0; i < 72; i++) {
        Cell createdCell{CellType::Edge, i};
        edges.emplace_back(createdCell);
    } 
    for (int i = 0; i < 54; i++) {
        Cell createdCell{CellType::Vertex, i};
        vertices.emplace_back(createdCell);
    }
    display = new Display(tiles);
    for (int i = 0; i < 19; i++) {
        tiles.at(i).attach(display);
        for (int m = 0; m < 6; m++) {
            tiles.at(i).attach(&edges.at(edgeOfTile.at(i).at(m)));
            tiles.at(i).attach(&vertices.at(vertexOfTile.at(i).at(m)));
            edges.at(edgeOfTile.at(i).at(m)).attach(&tiles.at(i));
            vertices.at(vertexOfTile.at(i).at(m)).attach(&tiles.at(i));
        }
    } 
    for (int i = 0; i < 54; i++) {
        vertices.at(i).attach(display);
        for (int m : edgeOfVertex.at(i)) {
            vertices.at(i).attach(&edges.at(m));
        }
    }
    for (int i = 0; i < 72; i++) {
        edges.at(i).attach(display);
        for (int m : vertexOfEdge.at(i)) {
            edges.at(i).attach(&vertices.at(m));
        }
    }
    return currentTurn;
}

void  Board::loadBoard(string file) {
    fstream boardFile{file};
    bool isRes = true;
    ResourceType res;
    int pos = 0;
    string s;
    while (boardFile >> s) {
        if (isRes) {
            if (s == "0") {
                res = ResourceType::Caffeine;
            } else if (s == "1") {
                res = ResourceType::Lab;
            } else if (s == "2") {
                res = ResourceType::Lecture;
            } else if (s == "3") {
                res = ResourceType::Study;
            } else if (s == "4") {
                res = ResourceType::Tutorial;
            } else if (s == "5") {
                res = ResourceType::None;
            }
        } else {
            Tile newTile(res, std::stoi(s), pos);
            tiles.emplace_back(newTile);
        }
    }
    for (int i = 0; i < 72; i++) {
        Cell createdCell{CellType::Edge, i};
        edges.emplace_back(createdCell);
    } 
    for (int i = 0; i < 54; i++) {
        Cell createdCell{CellType::Vertex, i};
        vertices.emplace_back(createdCell);
    }
    for (int i = 0; i < 4; i++) {
        Player createdPlayer{playerMap.at(i)};
        players.emplace_back(createdPlayer);
    }
    display = new Display(tiles);
    for (int i = 0; i < 19; i++) {
        tiles.at(i).attach(display);
        for (int m = 0; m < 6; m++) {
            tiles.at(i).attach(&edges.at(edgeOfTile.at(i).at(m)));
            tiles.at(i).attach(&vertices.at(vertexOfTile.at(i).at(m)));
            edges.at(edgeOfTile.at(i).at(m)).attach(&tiles.at(i));
            vertices.at(vertexOfTile.at(i).at(m)).attach(&tiles.at(i));
        }
    } 
    for (int i = 0; i < 54; i++) {
        vertices.at(i).attach(display);
        for (int m : edgeOfVertex.at(i)) {
            vertices.at(i).attach(&edges.at(m));
        }
    }
    for (int i = 0; i < 72; i++) {
        edges.at(i).attach(display);
        for (int m : vertexOfEdge.at(i)) {
            edges.at(i).attach(&vertices.at(m));
        }
    }

    
}
