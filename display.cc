#include "display.h"

char intToChar(int i)
{
	return ('0' + i);
}

std::vector<char> createTopEdge(int vertexL, int vertexR, int edge)
{
	std::vector<char> toReturn;
	toReturn.reserve(15);
	toReturn.emplace_back('|');
	toReturn.emplace_back((vertexL / 10 != 0) ? intToChar(vertexL / 10) : ' ');
	toReturn.emplace_back(intToChar(vertexL % 10));
	toReturn.emplace_back('|');
	toReturn.emplace_back('-');
	toReturn.emplace_back('-');
	toReturn.emplace_back((edge / 10 != 0) ? intToChar(edge / 10) : ' ');
	toReturn.emplace_back(intToChar(edge % 10));
	toReturn.emplace_back('-');
	toReturn.emplace_back('-');
	toReturn.emplace_back('|');
	toReturn.emplace_back((vertexR / 10 != 0) ? intToChar(vertexR / 10) : ' ');
	toReturn.emplace_back(intToChar(vertexR % 10));
	toReturn.emplace_back('|');
	return toReturn;
}

std::vector<char> createTopEmpty()
{
	std::vector<char> toReturn;
	toReturn.reserve(15);
	toReturn.emplace_back('/');
	for (int i = 0; i < 12; i++)
	{
		toReturn.emplace_back(' ');
	}
	toReturn.emplace_back('\\');
	return toReturn;
}

std::vector<char> createPosition(int edgeL, int edgeR, int position)
{
	std::vector<char> toReturn;
	toReturn.reserve(19);
	toReturn.emplace_back((edgeL / 10 != 0) ? intToChar(edgeL / 10) : ' ');
	toReturn.emplace_back(intToChar(edgeL % 10));
	for (int i = 0; i < 13; i++)
	{
		if (i == 6)
		{
			toReturn.emplace_back((position / 10 != 0) ? intToChar(position / 10) : ' ');
		}
		else if (i == 7)
		{
			toReturn.emplace_back(intToChar(position % 10));
		}
		else
		{
			toReturn.emplace_back(' ');
		}
	}
	toReturn.emplace_back((edgeR / 10 != 0) ? intToChar(edgeR / 10) : ' ');
	toReturn.emplace_back(intToChar(edgeR % 10));
	return toReturn;
}

std::vector<char> createResource(ResourceType resource)
{
	std::vector<char> toReturn;
	toReturn.reserve(19);
	toReturn.emplace_back('/');
	for (int i = 0; i < 5; i++)
	{
		toReturn.emplace_back(' ');
	}
	if (resource == ResourceType::None)
	{
		toReturn.emplace_back('N');
		toReturn.emplace_back('E');
		toReturn.emplace_back('T');
		toReturn.emplace_back('F');
		toReturn.emplace_back('L');
		toReturn.emplace_back('I');
		toReturn.emplace_back('X');
		toReturn.emplace_back(' ');
	}
	else if (resource == ResourceType::Tutorial)
	{
		toReturn.emplace_back('T');
		toReturn.emplace_back('U');
		toReturn.emplace_back('T');
		toReturn.emplace_back('O');
		toReturn.emplace_back('R');
		toReturn.emplace_back('I');
		toReturn.emplace_back('A');
		toReturn.emplace_back('L');
	}
	else if (resource == ResourceType::Study)
	{
		toReturn.emplace_back('S');
		toReturn.emplace_back('T');
		toReturn.emplace_back('U');
		toReturn.emplace_back('D');
		toReturn.emplace_back('Y');
		toReturn.emplace_back(' ');
		toReturn.emplace_back(' ');
		toReturn.emplace_back(' ');
	}
	else if (resource == ResourceType::Caffeine)
	{
		toReturn.emplace_back('C');
		toReturn.emplace_back('A');
		toReturn.emplace_back('F');
		toReturn.emplace_back('F');
		toReturn.emplace_back('E');
		toReturn.emplace_back('I');
		toReturn.emplace_back('N');
		toReturn.emplace_back('E');
	}
	else if (resource == ResourceType::Lab)
	{
		toReturn.emplace_back('L');
		toReturn.emplace_back('A');
		toReturn.emplace_back('B');
		toReturn.emplace_back(' ');
		toReturn.emplace_back(' ');
		toReturn.emplace_back(' ');
		toReturn.emplace_back(' ');
		toReturn.emplace_back(' ');
	}
	else if (resource == ResourceType::Lecture)
	{
		toReturn.emplace_back('L');
		toReturn.emplace_back('E');
		toReturn.emplace_back('C');
		toReturn.emplace_back('T');
		toReturn.emplace_back('U');
		toReturn.emplace_back('R');
		toReturn.emplace_back('E');
		toReturn.emplace_back(' ');
	}
	for (int i = 0; i < 3; i++)
	{
		toReturn.emplace_back(' ');
	}
	toReturn.emplace_back('\\');
	return toReturn;
}

std::vector<char> createDiceRoll(int vertexL, int vertexR, int diceRoll)
{
	std::vector<char> toReturn;
	toReturn.reserve(25);
	toReturn.emplace_back('|');
	toReturn.emplace_back((vertexL / 10 != 0) ? intToChar(vertexL / 10) : ' ');
	toReturn.emplace_back(intToChar(vertexL % 10));
	toReturn.emplace_back('|');
	for (int i = 0; i < 16; i++)
	{
		if (i == 7)
		{
			toReturn.emplace_back((diceRoll / 10 != 0) ? intToChar(diceRoll / 10) : ' ');
		}
		else if (i == 8)
		{
			toReturn.emplace_back(intToChar(diceRoll % 10));
		}
		else
		{
			toReturn.emplace_back(' ');
		}
	}
	toReturn.emplace_back('|');
	toReturn.emplace_back((vertexR / 10 != 0) ? intToChar(vertexR / 10) : ' ');
	toReturn.emplace_back(intToChar(vertexR % 10));
	toReturn.emplace_back('|');
	return toReturn;
}

std::vector<char> createHasGeese(bool hasGeese)
{
	std::vector<char> toReturn;
	toReturn.reserve(19);
	toReturn.emplace_back('\\');
	for (int i = 0; i < 16; i++)
	{
		if (hasGeese && (i == 6))
		{
			toReturn.emplace_back('G');
		}
		else if (hasGeese && (i == 7 || i == 8 || i == 10))
		{
			toReturn.emplace_back('E');
		}
		else if (hasGeese && (i == 9))
		{
			toReturn.emplace_back('S');
		}
		else
		{
			toReturn.emplace_back(' ');
		}
	}
	toReturn.emplace_back('/');
	return toReturn;
}

std::vector<char> createMidEmpty(int edgeL, int edgeR)
{
	std::vector<char> toReturn;
	toReturn.reserve(19);
	toReturn.emplace_back((edgeL / 10 != 0) ? intToChar(edgeL / 10) : ' ');
	toReturn.emplace_back(intToChar(edgeL % 10));
	for (int i = 0; i < 13; i++)
	{
		toReturn.emplace_back(' ');
	}
	toReturn.emplace_back((edgeR / 10 != 0) ? intToChar(edgeR / 10) : ' ');
	toReturn.emplace_back(intToChar(edgeR % 10));
	return toReturn;
}

std::vector<char> createLowEmpty()
{
	std::vector<char> toReturn;
	toReturn.reserve(15);
	toReturn.emplace_back('\\');
	for (int i = 0; i < 12; i++)
	{
		toReturn.emplace_back(' ');
	}
	toReturn.emplace_back('/');
	return toReturn;
}

std::vector<char> createLowEdge(int vertexL, int vertexR, int edge)
{
	return createTopEdge(vertexL, vertexR, edge);
}

TileDisplay createTileDisplay(Tile& tile)
{
	int position = tile.getPosition();
	ResourceType resource = tile.getResource();
	int diceRoll = tile.getRoll();
	bool hasGeese = tile.hasGoose();

	int vertex1 = vertexOfTile[position][0];
	int vertex2 = vertexOfTile[position][1];
	int vertex3 = vertexOfTile[position][2];
	int vertex4 = vertexOfTile[position][3];
	int vertex5 = vertexOfTile[position][4];
	int vertex6 = vertexOfTile[position][5];
	int edge1 = edgeOfTile[position][0];
	int edge2 = edgeOfTile[position][1];
	int edge3 = edgeOfTile[position][2];
	int edge4 = edgeOfTile[position][3];
	int edge5 = edgeOfTile[position][4];
	int edge6 = edgeOfTile[position][5];

	TileDisplay tileDisplay;
	tileDisplay.topEdge = createTopEdge(vertex1, vertex2, edge1);
	tileDisplay.topEmpty = createTopEmpty();
	tileDisplay.position = createPosition(edge2, edge3, position);
	tileDisplay.resource = createResource(resource);
	tileDisplay.diceRoll = createDiceRoll(vertex3, vertex4, diceRoll);
	tileDisplay.hasGeese = createHasGeese(hasGeese);
	tileDisplay.midEmpty = createMidEmpty(edge4, edge5);
	tileDisplay.lowEmpty = createLowEmpty();
	tileDisplay.lowEdge = createLowEdge(vertex5, vertex6, edge6);
	return tileDisplay;
}

Display::Display(std::vector<Tile> tiles)
{
	for (auto& tile : tiles)
	{
		this->theDisplay.emplace_back(createTileDisplay(tile));
	}
}

void Display::updateProgress(int tile, int cell, Colour colour, Progress progress)
{
	char colourChar;
	if (colour == Colour::Blue)
	{
		colourChar =  'B';
	}
	else if (colour == Colour::Red)
	{
		colourChar = 'R';
	}
	else if (colour == Colour::Orange)
	{
		colourChar = 'O';
	}
	else if (colour == Colour::Yellow)
	{
		colourChar = 'Y';
	}
	
	if (progress == Progress::Goals)
	{
		char progressChar = 'A';
		if (cell == 0)
		{
			this->theDisplay[tile].topEdge[6] = colourChar;
			this->theDisplay[tile].topEdge[7] = progressChar;
		}
		else if (cell == 1)
		{
			this->theDisplay[tile].position[0] = colourChar;
			this->theDisplay[tile].position[1] = progressChar;
		}
		else if (cell == 2)
		{
			this->theDisplay[tile].position[14] = colourChar;
			this->theDisplay[tile].position[15] = progressChar;
		}
		else if (cell == 3)
		{
			this->theDisplay[tile].midEmpty[0] = colourChar;
			this->theDisplay[tile].midEmpty[1] = progressChar;
		}
		else if (cell == 4)
		{
			this->theDisplay[tile].midEmpty[14] = colourChar;
			this->theDisplay[tile].midEmpty[15] = progressChar;
		}
		else if (cell == 5)
		{
			this->theDisplay[tile].lowEdge[6] = colourChar;
			this->theDisplay[tile].lowEdge[7] = progressChar;
		}
	}
	else
	{
		char progressChar;
		if (progress == Progress::Assignment)
		{
			progressChar = 'A';
		}
		else if (progress == Progress::Midterm)
		{
			progressChar = 'M';
		}
		else if (progress == Progress::Exam)
		{
			progressChar = 'E';
		}

		if (cell == 0)
		{
			this->theDisplay[tile].topEdge[1] = colourChar;
			this->theDisplay[tile].topEdge[2] = progressChar;
		}
		else if (cell == 1)
		{
			this->theDisplay[tile].topEdge[11] = colourChar;
			this->theDisplay[tile].topEdge[12] = progressChar;
		}
		else if (cell == 2)
		{
			this->theDisplay[tile].diceRoll[1] = colourChar;
			this->theDisplay[tile].diceRoll[2] = progressChar;
		}
		else if (cell == 3)
		{
			this->theDisplay[tile].diceRoll[21] = colourChar;
			this->theDisplay[tile].diceRoll[22] = progressChar;
		}
		else if (cell == 4)
		{
			this->theDisplay[tile].lowEdge[1] = colourChar;
			this->theDisplay[tile].lowEdge[2] = progressChar;
		}
		else if (cell == 5)
		{
			this->theDisplay[tile].lowEdge[11] = colourChar;
			this->theDisplay[tile].lowEdge[12] = progressChar;
		}
	}
}

void Display::notify(Subject<Phase> &notifier)
{
	if (notifier.getPhase().phase == TurnPhase::MoveGeese)
	{
		int position = notifier.getPhase().position;
		bool hasGeese = notifier.getPhase().hasGeese;
		this->theDisplay[position].hasGeese = createHasGeese(hasGeese);
	}
	else if (notifier.getPhase().phase == TurnPhase::Progress)
	{
		int cellPosition = notifier.getPhase().position;
		Colour progressColour = notifier.getPhase().currentPlayer;
		Progress progressType = notifier.getPhase().cellProgress;

		if(progressType == Progress::Goals)
		{
			for (int tile = 0; tile < 19; tile++)
			{
				for (int e = 0; e < 6; e++)
				{
					if (edgeOfTile[tile][e] == cellPosition)
					{
						this->updateProgress(tile, e, progressColour, progressType);
					}
				}
			}
		}
		else
		{
			for (int tile = 0; tile < 19; tile++)
			{
				for (int v = 0; v < 6; v++)
				{
					if (vertexOfTile[tile][v] == cellPosition)
					{
						this->updateProgress(tile, v, progressColour, progressType);
					}
				}
			}
		}
	}
}

void printSpace(std::ostream &out, int n)
{
	for (int i = 0; i < n; i++)
	{
		out << ' ';
	}
}

void printLine(std::ostream &out, std::vector<char> vec)
{
	for (char c : vec)
	{
		out << c;
	}
}

std::vector<char> popBack(std::vector<char> vec, int n)
{
	for (int i = 0; i < n; i++)
	{
		vec.pop_back();
	}
	return vec;
}

void printTop(std::ostream &out, TileDisplay tile0, TileDisplay tile1, TileDisplay tile2)
{
	printSpace(out, 35);
	printLine(out, tile0.topEdge);
	out << std::endl;

	printSpace(out, 35);
	printLine(out, tile0.topEmpty);
	out << std::endl;
	
	printSpace(out,33);
	printLine(out, tile0.position);
	out << std::endl;
	
	printSpace(out, 33);
	printLine(out, tile0.resource);
	out << std::endl;


	printSpace(out, 20);
	printLine(out, popBack(tile1.topEdge, 4));
	printLine(out, popBack(tile0.diceRoll, 4));
	printLine(out, tile2.topEdge);
	out << std::endl;
	
	printSpace(out, 20);
	printLine(out, popBack(tile1.topEmpty, 1));
	printLine(out, popBack(tile1.hasGeese, 1));
	printLine(out, tile2.topEmpty);
	out << std::endl;
	
	printSpace(out, 18);
	printLine(out, popBack(tile1.position, 2));
	printLine(out, popBack(tile1.midEmpty, 2));
	printLine(out, tile2.position);
	out << std::endl;
	
	printSpace(out, 18);
	printLine(out, popBack(tile1.resource, 1));
	printLine(out, popBack(tile1.lowEmpty, 1));
	printLine(out, tile2.resource);
	out << std::endl;
}

void printUpperMiddle(std::ostream &out, TileDisplay tile0, TileDisplay tile1, TileDisplay tile2, TileDisplay tile3, TileDisplay tile4)
{
	printSpace(out, 5);
	printLine(out, popBack(tile2.topEdge, 4));
	printLine(out, popBack(tile0.diceRoll, 4));
	printLine(out, popBack(tile3.topEdge, 4));
	printLine(out, popBack(tile1.diceRoll, 4));
	printLine(out, tile4.topEdge);
	out << std::endl;

	printSpace(out, 5);
	printLine(out, popBack(tile2.topEmpty, 1));
	printLine(out, popBack(tile0.hasGeese, 1));
	printLine(out, popBack(tile3.topEmpty, 1));
	printLine(out, popBack(tile1.hasGeese, 1));
	printLine(out, tile4.topEmpty);
	out << std::endl;

	printSpace(out, 3);
	printLine(out, popBack(tile2.position, 2));
	printLine(out, popBack(tile0.midEmpty, 2));
	printLine(out, popBack(tile3.position, 2));
	printLine(out, popBack(tile1.midEmpty, 2));
	printLine(out, tile4.position);
	out << std::endl;

	printSpace(out, 3);
	printLine(out, popBack(tile2.resource, 1));
	printLine(out, popBack(tile0.lowEmpty, 1));
	printLine(out, popBack(tile3.resource, 1));
	printLine(out, popBack(tile1.lowEmpty, 1));
	printLine(out, tile4.resource);
	out << std::endl;
}

void printLowerMiddle(std::ostream &out, TileDisplay tile0, TileDisplay tile1, TileDisplay tile2, TileDisplay tile3, TileDisplay tile4)
{
	printLine(out, popBack(tile0.diceRoll, 4));
	printLine(out, popBack(tile3.topEdge, 4));
	printLine(out, popBack(tile1.diceRoll, 4));
	printLine(out, popBack(tile4.topEdge, 4));
	printLine(out, tile2.diceRoll);
	out << std::endl;

	printSpace(out, 3);
	printLine(out, popBack(tile0.hasGeese, 1));
	printLine(out, popBack(tile3.topEmpty, 1));
	printLine(out, popBack(tile1.hasGeese, 1));
	printLine(out, popBack(tile4.topEmpty, 1));
	printLine(out, tile2.hasGeese);
	out << std::endl;

	printSpace(out, 3);
	printLine(out, popBack(tile0.midEmpty, 2));
	printLine(out, popBack(tile3.position, 2));
	printLine(out, popBack(tile1.midEmpty, 2));
	printLine(out, popBack(tile4.position, 2));
	printLine(out, tile2.midEmpty);
	out << std::endl;

	printSpace(out, 5);
	printLine(out, popBack(tile0.lowEmpty, 1));
	printLine(out, popBack(tile3.resource, 1));
	printLine(out, popBack(tile1.lowEmpty, 1));
	printLine(out, popBack(tile4.resource, 1));
	printLine(out, tile2.lowEmpty);
	out << std::endl;
}

void printBottom(std::ostream &out, TileDisplay tile0, TileDisplay tile1, TileDisplay tile2, TileDisplay tile3, TileDisplay tile4, TileDisplay tile5)
{
	printSpace(out, 5);
	printLine(out, popBack(tile0.lowEdge, 4));
	printLine(out, popBack(tile3.diceRoll, 4));
	printLine(out, popBack(tile1.lowEdge, 4));
	printLine(out, popBack(tile4.diceRoll, 4));
	printLine(out, tile2.lowEdge);
	out << std::endl;


	printSpace(out, 18);
	printLine(out, popBack(tile3.hasGeese, 1));
	printLine(out, popBack(tile5.topEmpty, 1));
	printLine(out, tile4.hasGeese);
	out << std::endl;

	printSpace(out, 18);
	printLine(out, popBack(tile3.midEmpty, 2));
	printLine(out, popBack(tile5.position, 2));
	printLine(out, tile4.midEmpty);
	out << std::endl;

	printSpace(out, 20);
	printLine(out, popBack(tile3.lowEmpty, 1));
	printLine(out, popBack(tile5.resource, 1));
	printLine(out, tile4.lowEmpty);
	out << std::endl;

	printSpace(out, 20);
	printLine(out, popBack(tile3.lowEdge, 4));
	printLine(out, popBack(tile5.diceRoll, 4));
	printLine(out, tile4.lowEdge);
	out << std::endl;


	printSpace(out, 33);
	printLine(out, tile5.hasGeese);
	out << std::endl;

	printSpace(out, 33);
	printLine(out, tile5.midEmpty);
	out << std::endl;

	printSpace(out, 35);
	printLine(out, tile5.lowEmpty);
	out << std::endl;

	printSpace(out, 35);
	printLine(out, tile5.lowEdge);
	out << std::endl;
}

std::ostream &operator<<(std::ostream &out, const Display &display)
{
	printTop(out, display.theDisplay[0], display.theDisplay[1], display.theDisplay[2]);
	printUpperMiddle(out, display.theDisplay[1], display.theDisplay[2], display.theDisplay[3], display.theDisplay[4], display.theDisplay[5]);
	printLowerMiddle(out, display.theDisplay[3], display.theDisplay[4], display.theDisplay[5], display.theDisplay[6], display.theDisplay[7]);
	printUpperMiddle(out, display.theDisplay[6], display.theDisplay[7], display.theDisplay[8], display.theDisplay[9], display.theDisplay[10]);
	printLowerMiddle(out, display.theDisplay[8], display.theDisplay[9], display.theDisplay[10], display.theDisplay[11], display.theDisplay[12]);
	printUpperMiddle(out, display.theDisplay[11], display.theDisplay[12], display.theDisplay[13], display.theDisplay[14], display.theDisplay[15]);
	printLowerMiddle(out, display.theDisplay[13], display.theDisplay[14], display.theDisplay[15], display.theDisplay[16], display.theDisplay[17]);
	printBottom(out, display.theDisplay[13], display.theDisplay[14], display.theDisplay[15], display.theDisplay[16], display.theDisplay[17], display.theDisplay[18]);

	return out;
}
