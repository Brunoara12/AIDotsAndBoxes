#include "DotsAndBoxes.h"



std::ostream& operator<<(std::ostream& os, Box const& m) {
	return os << m.boxCoord.first << "," << m.boxCoord.second << std::endl;
}

void DotsAndBoxes::debugBoxColor()
{
	if (longChainV)
	{
		int i = 0;
		for (auto xB : ListOfChains)
		{
			if (i == arrRandColor.size())
				i = 0;
			for (Box* yB : xB)
			{
				yB->D_setColor(arrRandColor[i]);
			}
			i++;
		}
	}
	else
	{
		for (auto xB : ListOfChains)
		{
			for (Box* yB : xB)
			{
				yB->D_setColor(sf::Color::Red);
			}
		}
	}
		
	if (ChainV2)
	{
		int i = 0;
		for (auto xB : ListOfChains2)
		{
			if (i == arrRandColor.size())
				i = 0;
			for (Box* yB : xB)
			{
				yB->D_setColor(sf::Color::Yellow);
			}
			i++;
		}
	}
	else
	{
		
		for (auto xB : ListOfChains2)
		{
			for (Box* yB : xB)
			{
				yB->D_setColor(sf::Color::Red);
			}
		}
	}

}

void DotsAndBoxes::jointBoxColor()
{
	if (jointBoxV)
	{
		for (Box* j : ListofJoints)
		{

			j->J_setColor(sf::Color::White);

		}
	}
	else
	{
		for (Box* j : ListofJoints)
		{
			j->J_setColor(sf::Color::Red);
		}
	}
}

void DotsAndBoxes::testScreen1()
{
	updateHLine(0, 0);
	updateHLine(3, 0);
	updateHLine(1, 1);
	updateHLine(2, 1);
	updateHLine(1, 2);
	updateHLine(0, 2);
	updateHLine(0, 3);
	updateHLine(1, 3);
	updateHLine(2, 3);
	updateHLine(1, 4);
	updateHLine(2, 4);
	updateHLine(3, 4);

	updateVLine(0, 0);
	updateVLine(2, 0);
	updateVLine(4, 0);
	updateVLine(0, 1);
	updateVLine(3, 1);
	updateVLine(4, 1);
	updateVLine(3, 2);
	updateVLine(4, 2);
	updateVLine(0, 3);
	updateVLine(4, 3);
}

void DotsAndBoxes::initVariables(int xDots, int yDots)
{
	valenceT = false;
	longChainV = false;
	ChainV2 = false;
	ChainV1 = false;
	jointBoxV = false;
	arrRandColor.push_back(sf::Color(52, 26, 217));
	arrRandColor.push_back(sf::Color(197, 1, 112));
	arrRandColor.push_back(sf::Color(220, 172, 237));
	arrRandColor.push_back(sf::Color(183, 215, 2));
	arrRandColor.push_back(sf::Color(117, 53, 217));
	arrRandColor.push_back(sf::Color(92, 103, 47));
	arrRandColor.push_back(sf::Color(129, 156, 139));
	arrRandColor.push_back(sf::Color(117, 48, 24));
	arrRandColor.push_back(sf::Color(5, 21, 74));
	arrRandColor.push_back(sf::Color(1, 221, 23));
	arrRandColor.push_back(sf::Color(125, 196, 232));
	arrRandColor.push_back(sf::Color(166, 88, 208));
	arrRandColor.push_back(sf::Color(182, 120, 27));
	arrRandColor.push_back(sf::Color(238, 83, 111));
	arrRandColor.push_back(sf::Color(165, 20, 39));
	arrRandColor.push_back(sf::Color(38, 64, 215));
	arrRandColor.push_back(sf::Color(166, 242, 146));
	arrRandColor.push_back(sf::Color(162, 199, 139));
	arrRandColor.push_back(sf::Color(20, 110, 51));
	arrRandColor.push_back(sf::Color(76, 84, 170));


	this->window = nullptr;
	dotsX = xDots;
	dotsY = yDots;
	dotOffset = 150;
	topOffset = 100;
	marginOffset = 150;
	dotR = 30.f;
	screenW = (dotOffset * (dotsX - 1)) + marginOffset;
	screenH = (dotOffset * (dotsY - 1)) + marginOffset + topOffset;
}

void DotsAndBoxes::initGameVar()
{
	eState = Turn::Player1;
	p1 = new Player("p1", sf::Color::Cyan, false);
	//p2 = new Player("p2", sf::Color::Magenta, false);
	p2 = new Player("ai2", sf::Color::Magenta, true);

	maxPoints = (dotsX - 1) * (dotsY - 1);
}

void DotsAndBoxes::initUI()
{
	sf::Font* font = new sf::Font();
	if (!font->loadFromFile("Roboto-Regular.ttf"))
		std::cout << "LOAD PROBLEM" << std::endl;
	p1Score = new sf::Text(p1->getName() + "'s Score:" + std::to_string(p1->getScore()), *font, 24);
	p2Score = new sf::Text(p2->getName() + "'s Score:" + std::to_string(p2->getScore()), *font, 24);

	//std::cout << std::to_string(p1->getScore() << std::endl;

	ScoreTurnBox = sf::RectangleShape(sf::Vector2f(screenW - 30.f, 100.f));
	TurnColorBox = sf::RectangleShape(sf::Vector2f(70.f, 70.f));
	ScoreTurnBox.setPosition(15.f, 15.f);
	TurnColorBox.setPosition(30.f, 30.f);
	p1Score->setPosition(115.f, 30.f);
	p2Score->setPosition(115.f, 60.f);
	p1Score->setFillColor(sf::Color::Black);
	p2Score->setFillColor(sf::Color::Black);

	ScoreTurnBox.setFillColor(sf::Color::White);
	ScoreTurnBox.setOutlineThickness(3.f);
	ScoreTurnBox.setOutlineColor(sf::Color(50, 50, 50, 255));
	TurnColorBox.setFillColor(getPlayerTurn()->color);

	p1Score->setStyle(sf::Text::Bold);

	// Win Box
	WinBox = sf::RectangleShape(sf::Vector2f(screenW - 30.f, screenH - 30.f));
	WinBox.setPosition(sf::Vector2f(15.f, 15.f));
	WinBox.setFillColor(sf::Color::White);
	WinBox.setOutlineColor(sf::Color(50, 50, 50, 255));
	WinBox.setOutlineThickness(3.f);

	// Win Text
	WinText = new sf::Text("", *font, 50);
	WinText->setPosition(sf::Vector2f(screenW / 2 - 100, screenH / 2 - 50));


}

void DotsAndBoxes::initWindow()
{
	this->videoM.height = screenH;
	this->videoM.width = screenW;

	this->window = new sf::RenderWindow(this->videoM, "Dots And Boxes", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
	//this->window->setKeyRepeatEnabled(false);
}

void DotsAndBoxes::initDots()
{
	for (int i = 0; i < dotsX; i++)
	{
		std::vector<Dot*> tmp;
		for (int j = 0; j < dotsY; j++)
		{
			Dot* tmpDot = new Dot(dotR, i, j);
			tmpDot->getDot()->setOutlineColor(sf::Color::Cyan);
			tmpDot->getDot()->setOutlineThickness(1.f);
			tmpDot->getDot()->setPosition(float(marginOffset / 2 + (dotOffset * i)), float(topOffset + marginOffset / 2 + (dotOffset * j)));
			tmp.push_back(tmpDot);
		}
		dotBoard.push_back(tmp);
	}


	//dotBoard[0][0]->setSelected(true);
}

void DotsAndBoxes::initLines()
{
	// Horizontal Lines
	for (int i = 0; i < dotsX - 1; i++)
	{
		std::vector<Line*> tmp;
		for (int j = 0; j < dotsY; j++)
		{
			Line* tmpLine = new Line(dotOffset, marginOffset, topOffset, dotR, i, j);
			// Horizontal
			sf::Vector2f startPos = sf::Vector2f(float(marginOffset / 2 + (dotOffset * i)), float(topOffset + marginOffset / 2 + (dotOffset * j)));
			tmpLine->getLine()->setPosition(startPos);
			tmp.push_back(tmpLine);
		}
		H_linesBoard.push_back(tmp);
	}

	// Vertical Lines
	for (int i = 0; i < dotsX; i++)
	{
		std::vector<Line*> tmp;
		for (int j = 0; j < dotsY - 1; j++)
		{
			Line* tmpLine = new Line(dotOffset, marginOffset, topOffset, dotR, i, j);
			// Vertical
			sf::Vector2f startPos = sf::Vector2f(float(marginOffset / 2 + (dotOffset * i)), float(topOffset + marginOffset / 2 + (dotOffset * j)));
			tmpLine->getLine()->setPosition(startPos);
			tmpLine->getLine()->rotate(90.f);
			tmp.push_back(tmpLine);
		}
		V_linesBoard.push_back(tmp);
	}
}

void DotsAndBoxes::initBoxes()
{
	for (int i = 0; i < dotsX - 1; i++)
	{
		std::vector<Box*> tmp;
		for (int j = 0; j < dotsY - 1; j++)
		{
			std::vector<Dot*> dTmp;
			dTmp.push_back(dotBoard[i][j]);
			dTmp.push_back(dotBoard[i][j + 1]);
			dTmp.push_back(dotBoard[i + 1][j]);
			dTmp.push_back(dotBoard[i + 1][j + 1]);

			Box* tmpBox = new Box(dotOffset, marginOffset, topOffset, i, j, dTmp);
			tmp.push_back(tmpBox);
		}
		board.push_back(tmp);
	}
}



int DotsAndBoxes::resultValenceFromLine(Play p)
{
	int valenceLeft = 5;
	int valenceRight = 5;
	int valenceUp = 5;
	int valenceDown = 5;
	if (p.x < 0 || p.y < 0)
		return 5;
	if (p.d == 'V') // V
	{
		if (p.x >= dotsX || p.y >= dotsY - 1)
			return 5;
		if (p.x - 1 >= 0)
		{
			// Left Box of Line Exit
			valenceLeft = board[p.x - 1][p.y]->valence - 1;
		}
		if (p.x < dotsX - 1)
		{
			// Right Box of Line Exit
			valenceRight = board[p.x][p.y]->valence - 1;
		}
		//std::cout << "L:" << valenceLeft << ", ";
		//std::cout << "R:" << valenceRight << "\n";
		return std::min(valenceLeft, valenceRight);
	}
	else // H
	{
		if (p.x >= dotsX - 1 || p.y >= dotsY)
			return 5;
		if (p.y - 1 >= 0)
		{
			// Up Box of Line Exit
			valenceUp = board[p.x][p.y - 1]->valence - 1;
		}
		if (p.y < dotsY - 1)
		{
			// Down Box of Line Exit
			valenceDown = board[p.x][p.y]->valence - 1;
		}
		//std::cout << "U:" << valenceUp << ", ";
		//std::cout << "D:" << valenceDown << "\n ";
		return std::min(valenceUp, valenceDown);
	}


}

bool DotsAndBoxes::placeRandLineDown()
{
	int Dx = -1;
	int Dy = -1;
	if (!checkIfVFull() && rand() % 2 == 0) // Vert
	{
		do
		{
			if (rand() % 2 == 0)
				Dx = LastTurn.x + rand() % dotsX;
			else
				Dx = LastTurn.x - rand() % dotsX;

			if (rand() % 2 == 0)
				Dy = LastTurn.x + rand() % dotsY;
			else
				Dy = LastTurn.x - rand() % dotsY;


		} while (resultValenceFromLine(Play{ 'V',Dx,Dy }) < 2 || !updateVLine(Dx, Dy));
		return true;
	}
	else if (!checkIfHFull())
	{
		do
		{
			if (rand() % 2 == 0)
				Dx = LastTurn.x + rand() % dotsX;
			else
				Dx = LastTurn.x - rand() % dotsX;

			if (rand() % 2 == 0)
				Dy = LastTurn.x + rand() % dotsY;
			else
				Dy = LastTurn.x - rand() % dotsY;
		} while (resultValenceFromLine(Play{ 'H',Dx,Dy }) < 2 || !updateHLine(Dx, Dy)); // Horiz
		return true;
	}
	return false;
}

bool DotsAndBoxes::checkIfVFull()
{
	for (auto xL : V_linesBoard)
	{
		for (Line* yL : xL)
		{
			if (!yL->completed)
				return false;
		}
	}
	return true;
}

bool DotsAndBoxes::checkIfHFull()
{
	for (auto xL : H_linesBoard)
	{
		for (Line* yL : xL)
		{
			if (!yL->completed)
				return false;
		}
	}
	return true;
}

bool DotsAndBoxes::checkBoxesComplete()
{
	bool boxClosed = false;
	for (auto xB : board)
	{
		for (Box* yB : xB)
		{
			if (!yB->confirmed && yB->checkBoxComplete())
			{
				yB->playerCompleted(getPlayerTurn());
				boxClosed = true;
			}
		}
	}
	return boxClosed;
}

bool DotsAndBoxes::checkIfJoint(Box* b)
{
	int valence = b->valence;
	bool neighHasVal2 = true;
	//std::cout << "checking Joint:" << valence << std::endl;
	if (valence == 3 || valence == 4)
	{
		int boxCoordx = b->boxCoord.first;
		int boxCoordy = b->boxCoord.second;
		//std::cout << "CHECKING BOX: " << boxCoordx << ", " << boxCoordy << std::endl;
		if (!H_linesBoard[boxCoordx][boxCoordy]->completed) // Top Line
		{
			if (boxCoordy - 1 < 0) // Out of Bounds
			{
				neighHasVal2 = false;
			}
			else if (board[boxCoordx][boxCoordy - 1]->valence == 2)
			{
				neighHasVal2 = neighHasVal2 && true;
			}
			else
			{
				neighHasVal2 = false;
			}
		}
		if (!H_linesBoard[boxCoordx][boxCoordy + 1]->completed) // Botoom Line
		{
			if (boxCoordy + 1 >= dotsY - 1) // Out of Bounds
			{
				neighHasVal2 = false;
			}
			else if (board[boxCoordx][boxCoordy + 1]->valence == 2)
			{
				neighHasVal2 = neighHasVal2 && true;
			}
			else
			{
				neighHasVal2 = false;
			}
		}
		if (!V_linesBoard[boxCoordx][boxCoordy]->completed) // Left Line
		{
			if (boxCoordx - 1 < 0) // Out of Bounds
			{
				neighHasVal2 = false;
			}
			else if (board[boxCoordx - 1][boxCoordy]->valence == 2)
			{
				neighHasVal2 = neighHasVal2 && true;
			}
			else
			{
				neighHasVal2 = false;
			}
		}
		if (!V_linesBoard[boxCoordx + 1][boxCoordy]->completed) // RightLine
		{
			if (boxCoordx + 1 >= dotsX - 1) // Out of Bounds
			{
				neighHasVal2 = false;
			}
			else if (board[boxCoordx + 1][boxCoordy]->valence == 2)
			{
				neighHasVal2 = neighHasVal2 && true;
			}
			else
			{
				neighHasVal2 = false;
			}
		}
		if (neighHasVal2)
		{
			std::cout << "JOINT\n";
			ListofJoints.push_back(b);
		}
		return neighHasVal2;
	}


	neighHasVal2 = false;
	return neighHasVal2;
}

Control DotsAndBoxes::checkWhoHasControl()
{
	int numDots = dotsX * dotsY;
	int numLongChain = ListOfChains.size();
	if (numDots % 2 == 0) // even
		if (numLongChain % 2 == 0) //even
			return Control::p1;
		else // odd
			return Control::p2;
	else // odd
		if (numLongChain % 2 == 0) //even
			return Control::p2;
		else // odd
			return Control::p1;
}

bool DotsAndBoxes::doubleDealChain(Play p)
{
	std::cout << "NUM CHAINS: " << ListOfChains.size() << std::endl;
	for (std::vector<Box*> chains : ListOfChains)
	{
		std::cout << "CHAIN: " << std::endl;
		Box* b = chains[0];
		b->printBoxChain(b);
		for (Box* b : chains)
		{
			std::cout << *b;
		}
	}
	Box* leftBox = nullptr;
	Box* rightBox = nullptr;
	Box* upBox = nullptr;
	Box* downBox = nullptr;
	if (p.x < 0 || p.y < 0)
		return false;
	if (p.d == 'V') // V
	{
		if (p.x >= dotsX || p.y >= dotsY - 1)
			return false;
		if (p.x - 1 >= 0)
		{
			// Left Box of Line Exit
			leftBox = board[p.x - 1][p.y];
		}
		if (p.x < dotsX - 1)
		{
			// Right Box of Line Exit
			rightBox = board[p.x][p.y];
		}
		//std::cout << "L:" << valenceLeft << ", ";
		//std::cout << "R:" << valenceRight << "\n";
		if (leftBox == nullptr)
		{
			doubleCrossHelp(rightBox, true);
		}
		else if (rightBox == nullptr)
		{
			doubleCrossHelp(leftBox, false);
		}
		else
		{
			std::cout << "Y" << std::endl;
			std::cout << "Left:" << *leftBox << "Right:" << *rightBox->prev;
			if (leftBox == rightBox->next)
			{
				int leftPath = leftBox->numBoxBackwards(leftBox);
				int rightPath = rightBox->numBoxForward(rightBox);
				std::cout << "leftP: " << leftPath << "rightP: " << rightPath << std::endl;

				if (leftPath < rightPath)
				{
					Box* currB = leftBox;
					std::cout << "TEST:\n";
					while (currB->numBoxBackwards(currB) >= 0)
					{
						std::cout << *currB;
						closeBox(currB);
						currB = currB->prev;
					}
					
					// Double Cross
					doubleCrossHelp(rightBox, true);
				}
				else
				{
					Box* currB = rightBox;
					while (currB->numBoxForward(currB) >= 0)
					{
						closeBox(currB);
						currB = currB->next;
					}
					// Double Cross
					doubleCrossHelp(leftBox, false);
				}
			}
		}
		return true;
	}
	else // H
	{
		if (p.x >= dotsX - 1 || p.y >= dotsY)
			return 5;
		if (p.y - 1 >= 0)
		{
			// Up Box of Line Exit
			upBox = board[p.x][p.y - 1];
		}
		if (p.y < dotsY - 1)
		{
			// Down Box of Line Exit
			downBox = board[p.x][p.y];
		}

		if (upBox == nullptr)
		{
			doubleCrossHelp(downBox, false);
		}
		else if (downBox == nullptr)
		{
			doubleCrossHelp(upBox, true);	
		}
		else
		{
			if (upBox == downBox->next)
			{
				int upPath = upBox->numBoxForward(upBox);
				int downPath = downBox->numBoxBackwards(downBox);

				if (upPath < downPath)
				{
					Box* currB = upBox;
					while (currB->numBoxForward(currB) >= 0)
					{
						closeBox(currB);
						currB = currB->next;
					}
					// Double Cross
					doubleCrossHelp(downBox, false);
				}
				else
				{
					Box* currB = downBox;
					while (currB->numBoxBackwards(currB) >= 0)
					{
						closeBox(currB);
						currB = currB->prev;
					}
					// Double Cross
					doubleCrossHelp(upBox, true);
				}
			}
			else if (upBox == downBox->prev)
			{
				int upPath = upBox->numBoxBackwards(upBox);
				int downPath = downBox->numBoxForward(downBox);

				if (upPath < downPath)
				{
					Box* currB = upBox;
					while (currB->numBoxBackwards(currB) >= 0)
					{
						closeBox(currB);
						currB = currB->prev;
					}
					// Double Cross
					doubleCrossHelp(downBox, true);
				}
				else
				{
					Box* currB = downBox;
					while (currB->numBoxForward(currB) >= 0)
					{
						closeBox(currB);
						currB = currB->next;
					}
					// Double Cross
					doubleCrossHelp(upBox, false);
				}
			}
		}

		//std::cout << "U:" << valenceUp << ", ";
		//std::cout << "D:" << valenceDown << "\n ";
		return true;
	}
}

void DotsAndBoxes::closeBox(Box* b)
{
	int boxCoordx = b->boxCoord.first;
	int boxCoordy = b->boxCoord.second;
	if (!H_linesBoard[boxCoordx][boxCoordy]->completed) // Top Line
	{
		updateHLine(boxCoordx, boxCoordy);
	}
	else if (!H_linesBoard[boxCoordx][boxCoordy + 1]->completed) // Botoom Line
	{
		updateHLine(boxCoordx, boxCoordy + 1);
	}
	else if (!V_linesBoard[boxCoordx][boxCoordy]->completed) // Left Line
	{
		updateVLine(boxCoordx, boxCoordy);
	}
	else // RightLine
	{
		updateVLine(boxCoordx + 1, boxCoordy);
	}
}

void DotsAndBoxes::doubleCrossHelp(Box* b, bool forward)
{
	Box* currB = b;
	Box* nextB;
	int boxCoordx = 0;
	int boxCoordy = 0;
	if (forward)
	{
		while (currB->numBoxForward(currB) >= 2)
		{
			closeBox(currB);
			currB = currB->next;
		}
		nextB = currB->next;
		boxCoordx = nextB->boxCoord.first;
		boxCoordy = nextB->boxCoord.second;
	}
	else
	{
		while (currB->numBoxBackwards(currB) >= 2)
		{
			closeBox(currB);
			currB = currB->prev;
		}
		nextB = currB->prev;
		boxCoordx = nextB->boxCoord.first;
		boxCoordy = nextB->boxCoord.second;
	}
	
	// Give Double-Cross
	
	if (!H_linesBoard[boxCoordx][boxCoordy]->completed && boxCoordy - 1 < 0) // Top Line
	{
		updateHLine(boxCoordx, boxCoordy);
	}
	else if (!H_linesBoard[boxCoordx][boxCoordy + 1]->completed && boxCoordy + 1 >= dotsY - 1) // Botoom Line
	{
		updateHLine(boxCoordx, boxCoordy + 1);
	}
	else if (!V_linesBoard[boxCoordx][boxCoordy]->completed && boxCoordx - 1 < 0) // Left Line
	{
		updateVLine(boxCoordx, boxCoordy);
	}
	else if (!V_linesBoard[boxCoordx + 1][boxCoordy]->completed && boxCoordx + 1 >= dotsX - 1) // RightLine
	{
		updateVLine(boxCoordx + 1, boxCoordy);
	}
}

void DotsAndBoxes::clearChain()
{
	for (auto chain : ListOfChains)
	{
		int chainLen = 0;
		int sndChain = 0;
		bool reverse = false;
		int reversePx = 0;
		int reversePy = 0;
		for (Box* b : chain)
		{
			b->chainLen = 0;
			b->next = nullptr;
			b->prev = nullptr;
			b->D_setColor(sf::Color::Red);
		}
	}
	ListOfChains.clear();
}

void DotsAndBoxes::checkBoardForChains()
{
	for (int i = 0; i < dotsX - 1; i++)
	{
		std::vector<Box*> chain;
		int s = 0;
		for (int j = 0; j < dotsY - 1; j++)
		{
			if (board[i][j]->valence == 2 && !board[i][j]->visited)
			{
				s = chainHelper(i, j, chain);

				if (i + 1 < dotsX - 1 && !board[i + 1][j]->visited) // Check Right
				{
					if (!V_linesBoard[i + 1][j]->completed) // Empty line between Boxes
					{
						//std::cout << "1+ RIGHT\n";
						s += chainHelper(i + 1, j, chain);
					}
				}
				if (j + 1 < dotsY - 1 && !board[i][j + 1]->visited) // Check Down
				{
					if (!H_linesBoard[i][j + 1]->completed) // Empty line between Boxes
					{
						//std::cout << "down: " << *board[i][j + 1];
						//std::cout << "Down is clear\n";
						//std::cout << "1+ DOWN\n";
						s += chainHelper(i, j + 1, chain);
					}
				}
				if (j - 1 >= 0 && !board[i][j - 1]->visited) // Check Up
				{
					if (!H_linesBoard[i][j]->completed) // Empty line between Boxes
					{
						//std::cout << "1+ UP\n";
						s += chainHelper(i, j - 1, chain);
					}
				}
				if (i - 1 >= 0 && !board[i - 1][j]->visited) // Check Left
				{
					if (!V_linesBoard[i][j]->completed) // Empty line between Boxes
					{
						//std::cout << "1+ LEFT\n";
						s += chainHelper(i - 1, j, chain);
					}
				}
			}
			if (s > 2 && chain.size() > 0)
				ListOfChains.push_back(chain);
			else if (s == 2 && chain.size() > 0)
				ListOfChains2.push_back(chain);
			else if (s == 1 && chain.size() > 0)
				ListOfChains1.push_back(chain);
			chain.clear();
			//std::cout << "S: " << s << std::endl;
		}

	}

	for (auto chain : ListOfChains)
	{
		int chainLen = 0;
		int sndChain = 0;
		bool reverse = false;
		int reversePx = -1;
		int reversePy = -1;
		for (Box* b : chain)
		{
			std::cout << "REVERSE: " << reverse << std::endl;
			if (chainLen == 0)
			{
				if (!H_linesBoard[b->boxCoord.first][b->boxCoord.second + 1]->completed && !V_linesBoard[b->boxCoord.first + 1][b->boxCoord.second]->completed) // Corner Case
				{
					reverse = true;
					reversePx = b->boxCoord.first;
					reversePy = b->boxCoord.second + 1;
					if (b->boxCoord.first + 1 == dotsX - 1 || board[b->boxCoord.first+1][b->boxCoord.second]->valence > 2)
					{
						b->prev = chain[chainLen + 1];
						b->next = nullptr;
					}
					else 
					{
						b->next = chain[chainLen + 1];
						b->next->prev = b;
						b->prev = nullptr;
					}
				}
				else 
				{
					b->next = chain[chainLen + 1];
					b->next->prev = b;
					b->prev = nullptr;
				}
			}
			else if (chain.size() - 1 > chainLen && chain[chainLen + 1]->boxCoord.first != reversePx && chain[chainLen + 1]->boxCoord.second != reversePy)
			{
				b->next = chain[chainLen + 1];
				b->next->prev = b;
				b->next->next = nullptr;
				//std::cout << "prev: " << *b->prev << "curr: " << *b << "next: " << *b->next << "next->prev: " << *b->next->prev << std::endl;

			}

			if (reverse && b->boxCoord.first == reversePx && b->boxCoord.second == reversePy)
			{
				if (chain.size() - 1 > chainLen)
				{
					reversePx = chain[chainLen + 1]->boxCoord.first;
					reversePy = chain[chainLen + 1]->boxCoord.second;
				}
				if (sndChain == 0)
					b->next = chain[sndChain];
				else
					b->next = chain[chainLen - 1];
				b->next->prev = b;
				sndChain++;
			}
			chainLen++;
			b->chainLen = chain.size();
		}
	}

	for (auto chain : ListOfChains2)
	{
		int chainLen = 0;
		int sndChain = 0;
		bool reverse = false;
		int reversePx = -1;
		int reversePy = -1;
		for (Box* b : chain)
		{
			std::cout << "REVERSE: " << reverse << std::endl;
			if (chainLen == 0)
			{
				if (!H_linesBoard[b->boxCoord.first][b->boxCoord.second + 1]->completed && !V_linesBoard[b->boxCoord.first + 1][b->boxCoord.second]->completed) // Corner Case
				{
					reverse = true;
					reversePx = b->boxCoord.first;
					reversePy = b->boxCoord.second + 1;
					if (b->boxCoord.first + 1 == dotsX - 1 || board[b->boxCoord.first + 1][b->boxCoord.second]->valence > 2)
					{
						b->prev = chain[chainLen + 1];
						b->next = nullptr;
					}
					else
					{
						b->next = chain[chainLen + 1];
						b->next->prev = b;
						b->prev = nullptr;
					}
				}
				else
				{
					b->next = chain[chainLen + 1];
					b->next->prev = b;
					b->prev = nullptr;
				}
			}
			else if (chain.size() - 1 > chainLen && chain[chainLen + 1]->boxCoord.first != reversePx && chain[chainLen + 1]->boxCoord.second != reversePy)
			{
				b->next = chain[chainLen + 1];
				b->next->prev = b;
				b->next->next = nullptr;
				//std::cout << "prev: " << *b->prev << "curr: " << *b << "next: " << *b->next << "next->prev: " << *b->next->prev << std::endl;

			}

			if (reverse && b->boxCoord.first == reversePx && b->boxCoord.second == reversePy)
			{
				if (chain.size() - 1 > chainLen)
				{
					reversePx = chain[chainLen + 1]->boxCoord.first;
					reversePy = chain[chainLen + 1]->boxCoord.second;
				}
				if (sndChain == 0)
					b->next = chain[sndChain];
				else
					b->next = chain[chainLen - 1];
				b->next->prev = b;
				sndChain++;
			}
			chainLen++;
			b->chainLen = chain.size();
		}
	}

	for (auto xB : board)
	{
		for (Box* yB : xB)
		{
			yB->visited = false;

		}
	}
}




int DotsAndBoxes::chainHelper(int x, int y, std::vector<Box*>& chain)
{
	int size = 0;
	Box* currBox = board[x][y];
	//std::cout << "CURR:" << *currBox;
	if (currBox->valence == 2 && !currBox->visited)
	{
		//std::cout << *currBox << "Checking Adj\n";
		currBox->visited = true;
		chain.push_back(currBox);
		if (x + 1 < dotsX - 1 && !board[x + 1][y]->visited) // Check Right
		{
			if (!V_linesBoard[x + 1][y]->completed) // Empty line between Boxes
			{
				//std::cout << "1+ RIGHT\n";
				size = 1 + chainHelper(x + 1, y, chain);
				return size;
			}
		}
		if (y + 1 < dotsY - 1 && !board[x][y + 1]->visited) // Check Down
		{
			if (!H_linesBoard[x][y + 1]->completed) // Empty line between Boxes
			{
				//std::cout << "down: " << *board[x][y + 1];
				//std::cout << "Down is clear\n";
				//std::cout << "1+ DOWN\n";
				size = 1 + chainHelper(x, y + 1, chain);
				return size;
			}
		}
		if (y - 1 >= 0 && !board[x][y - 1]->visited) // Check Up
		{
			if (!H_linesBoard[x][y]->completed) // Empty line between Boxes
			{
				//std::cout << "1+ UP\n";
				size = 1 + chainHelper(x, y - 1, chain);
				return size;
			}
		}
		if (x - 1 >= 0 && !board[x - 1][y]->visited) // Check Left
		{
			if (!V_linesBoard[x][y]->completed) // Empty line between Boxes
			{
				//std::cout << "1+ LEFT\n";
				size = 1 + chainHelper(x - 1, y, chain);
				return size;
			}
		}
		return 1;
	}
	return size;
}

int DotsAndBoxes::checkBoxForValence(int x)
{
	int numBox = 0;
	for (auto xB : board)
	{
		for (Box* yB : xB)
		{
			if (yB->valence == x)
				numBox++;
		}
	}
	return numBox;
}

bool DotsAndBoxes::checkEndgame()
{
	bool EndGame = true;
	for (Box* b : ListofJoints)
		b->J_setColor(sf::Color::Red);
	ListofJoints.clear();
	//std::cout << "checking end game\n";
	for (auto xB : board)
	{
		for (Box* yB : xB)
		{
			if (yB->valence > 2)
				if (!checkIfJoint(yB))
					EndGame = false;

		}
	}
	return EndGame;
}

bool DotsAndBoxes::checkForFree()
{
	for (auto xB : board)
	{
		for (Box* yB : xB)
		{
			if (yB->valence == 1)
			{
				int boxCoordx = yB->boxCoord.first;
				int boxCoordy = yB->boxCoord.second;
				if (!H_linesBoard[boxCoordx][boxCoordy]->completed) // Top Line
				{
					updateHLine(boxCoordx, boxCoordy);
				}
				else if (!H_linesBoard[boxCoordx][boxCoordy + 1]->completed) // Botoom Line
				{
					updateHLine(boxCoordx, boxCoordy + 1);
				}
				else if (!V_linesBoard[boxCoordx][boxCoordy]->completed) // Left Line
				{
					updateVLine(boxCoordx, boxCoordy);
				}
				else // RightLine
				{
					updateVLine(boxCoordx + 1, boxCoordy);
				}
				return true;

			}
		}
	}
	return false;
}

DotsAndBoxes::DotsAndBoxes(int xDots, int yDots)
{
	initVariables(xDots, yDots);
	initGameVar();
	initUI();
	initWindow();
	initDots();
	initLines();
	initBoxes();
}

DotsAndBoxes::~DotsAndBoxes()
{
	delete this->window;
}

const bool DotsAndBoxes::running() const
{
	return window->isOpen();
}

void DotsAndBoxes::setPlayerTurn(Turn t)
{
	eState = t;
}

Player* DotsAndBoxes::getPlayerTurn()
{
	switch (eState)
	{
	case Player1:
		return p1;
	case Player2:
		return p2;
	case Start:
		return nullptr;
	default:
		return nullptr;

	}
}

void DotsAndBoxes::updateMousePositions()
{
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(mousePosWindow);
}

void DotsAndBoxes::printMousePos()
{

	std::cout << "Mouse pos: " << mousePosWindow.x << " " << mousePosWindow.y << "\n";
}

bool DotsAndBoxes::updateVLine(int x, int y)
{
	// Check in bounds
	if (x < 0 || x >= dotsX)
	{
		return false;
	}
	if (y < 0 || y >= dotsY - 1)
	{
		return false;
	}

	if (!V_linesBoard[x][y]->completed)
	{
		V_linesBoard[x][y]->connectLine();
		// Update Valence of Box
		if (x - 1 >= 0)
		{
			// Left Box of Line Exit
			board[x - 1][y]->valence--;
		}
		if (x < dotsX - 1)
		{
			// Right Box of Line Exit
			board[x][y]->valence--;
		}
		return true;
	}

	return false;
}

bool DotsAndBoxes::updateHLine(int x, int y)
{
	// Check in bounds
	if (x < 0 || x >= dotsX - 1)
	{
		return false;
	}
	if (y < 0 || y >= dotsY)
	{
		return false;
	}

	if (!H_linesBoard[x][y]->completed)
	{
		H_linesBoard[x][y]->connectLine();

		// Update Valence of Box
		if (y - 1 >= 0)
		{
			// Up Box of Line Exit
			board[x][y - 1]->valence--;
		}
		if (y < dotsY - 1)
		{
			// Down Box of Line Exit
			board[x][y]->valence--;
		}
		return true;
	}

	return false;
}

void DotsAndBoxes::pollEvents()
{

	// Event Types
	switch (ev.type)
	{
	case sf::Event::Closed:
		window->close();
		break;
	case sf::Event::KeyPressed:
		if (ev.key.code == sf::Keyboard::Escape)
			window->close();
		break;
	case sf::Event::KeyReleased:
		if (ev.key.code == sf::Keyboard::L)
		{
			longChainV = true;
			ChainV2= false;
			ChainV1 = false;
		}
		if (ev.key.code == sf::Keyboard::V)
			valenceT = !valenceT;
		if (ev.key.code == sf::Keyboard::J)
			jointBoxV = !jointBoxV;
		if (ev.key.code == sf::Keyboard::T)
		{
			ChainV2 = true;
			longChainV = false;
			ChainV1 = false;
		}
		if (ev.key.code == sf::Keyboard::O)
		{
			ChainV1 = true;
			longChainV = false;
			ChainV2 = false;
		}
		if (ev.key.code == sf::Keyboard::C)
		{
			ChainV1 = false;
			longChainV = false;
			ChainV2 = false;
		}
		if (ev.key.code == sf::Keyboard::Num1)
		{
			testScreen1();
			debugUpdateBoard = true;
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (ev.mouseButton.button == sf::Mouse::Right)
		{

			for (auto d : board[0][0]->dotsInBox)
			{
				//std::cout << d->getCoord().first << " " << d->getCoord().second << "\n";
			}
			// Reset
			if (connectP.first)
			{
				connectP.first->setSelected(false);
				if (!connectP.first->checkCompleted())
					connectP.first->setColor(sf::Color::White);
				connectP = std::make_pair(nullptr, nullptr);
			}
		}
		break;
	default:
		break;
	}

}

void DotsAndBoxes::updateUI()
{
	switch (eState)
	{
	case Turn::Player1:
		TurnColorBox.setFillColor(p1->color);
		p1Score->setStyle(sf::Text::Bold);
		p2Score->setStyle(sf::Text::Regular);
		p1Score->setString(p1->getName() + "'s Score:" + std::to_string(p1->getScore()));
		p2Score->setString(p2->getName() + "'s Score:" + std::to_string(p2->getScore()));
		break;
	case Turn::Player2:
		TurnColorBox.setFillColor(p2->color);
		p1Score->setStyle(sf::Text::Regular);
		p2Score->setStyle(sf::Text::Bold);
		p1Score->setString(p1->getName() + "'s Score:" + std::to_string(p1->getScore()));
		p2Score->setString(p2->getName() + "'s Score:" + std::to_string(p2->getScore()));
		break;
	case Turn::Start:
		break;
	default:
		break;
	}
}

void DotsAndBoxes::updateBoxes()
{
	debugBoxColor();
	jointBoxColor();
	for (auto xB : board)
	{
		for (Box* yB : xB)
		{
			yB->update();
		}
	}
}

void DotsAndBoxes::updateLines()
{

}

void DotsAndBoxes::updateDots()
{
	if(debugUpdateBoard)
	{
		clearChain();
		checkBoardForChains();
		std::cout << "NUM CHAINS: " << ListOfChains.size() << std::endl;
		for (std::vector<Box*> chains : ListOfChains)
		{
			checkBoxesComplete();
			std::cout << "CHAIN: " << std::endl;
			Box* b = chains[0];
			b->printBoxChain(b);
			for (Box* b : chains)
			{
				std::cout << *b;
			}
		}
		debugUpdateBoard = false;
	}
	if (eState == Turn::Player2 && p2->isAI && !p2->thinking) // p2 is Ai and is done thinking
	{
		bool boxClosed = false;
		//std::cout << "AI2 Played\n";
		bool endGame = checkEndgame();
		//updateVLine(0, 0);
		if (endGame)
		{
			std::cout << "END GAME REACHED\n";

			boxClosed = !doubleDealChain(LastTurn);
			checkBoxesComplete();

			std::cout << "box closed: " << boxClosed << std::endl;
		}
		else
		{
			boxClosed = checkForFree();
			boxClosed = checkBoxesComplete();
		}
		if (!boxClosed && !endGame)
		{
			int numBox2 = checkBoxForValence(2);
			//std::cout << "VALENCE 2 = " << numBox2 << std::endl;

			if (numBox2 < (dotsX * dotsY) / 2)
			{
				placeRandLineDown();
			}


	
		}

		clearChain();
		checkBoardForChains();
		std::cout << "NUM LONG CHAINS : " << ListOfChains.size() << std::endl;
		for (std::vector<Box*> chains : ListOfChains)
		{
			std::cout << "CHAIN: " << std::endl;
			Box* b = chains[0];
			b->printBoxChain(b);
			for (Box* b : chains)
			{
				std::cout << *b;
			}
		}
		std::cout << "NUM 2 CHAINS : " << ListOfChains2.size() << std::endl;
		for (std::vector<Box*> chains : ListOfChains2)
		{
			std::cout << "CHAIN: " << std::endl;
			Box* b = chains[0];
			b->printBoxChain(b);
			for (Box* b : chains)
			{
				std::cout << *b;
			}
		}
		if (!boxClosed)
		{
			setPlayerTurn(Turn::Player1);
			p2->thinking = true;
		}
		else
		{
			p2->thinking = false;
		}
	}

	if (ev.type == ev.MouseButtonReleased && ev.mouseButton.button == sf::Mouse::Left)
	{
		for (int i = 0; i < dotsX; i++)
		{
			for (int j = 0; j < dotsY; j++)
			{
				if (dotBoard[i][j]->getDot()->getGlobalBounds().contains(mousePosView))
				{
					// If Pair is not full
					if (!(connectP.first && connectP.second))
					{
						if (!connectP.first)
						{
							connectP.first = dotBoard[i][j];
							connectP.first->getDot()->setFillColor(sf::Color::Black);
							connectP.first->setSelected(true);
							std::cout << connectP.first->getDot()->getOrigin().x << " " << connectP.first->getDot()->getOrigin().x;
							//connectP.first->getDot()->setScale(1.2f,1.2f);
						}
						else
						{
							// Checks if same Dot
							if (!dotBoard[i][j]->checkSame(connectP.first))
							{
								// Checks if already connected to selected Dot
								if (!connectP.first->checkConnection(dotBoard[i][j]))
								{
									// Checks if could possibly connect to selected Dot
									bool isPair = connectP.first->checkPair(dotBoard[i][j]);
									if (isPair)
									{
										std::cout << "Pair\n";

										connectP.second = dotBoard[i][j];
										connectP.second->getDot()->setFillColor(sf::Color::Black);

										// Add Connected Pair to each other
										connectP.first->addPair(connectP.second);
										connectP.second->addPair(connectP.first);

										// Connect Line between two points
										// Vertical
										if (connectP.first->getCoord().first == connectP.second->getCoord().first)
										{
											int x = connectP.first->getCoord().first;
											int y = std::min(connectP.first->getCoord().second, connectP.second->getCoord().second);
											updateVLine(x, y);
											LastTurn = { 'V', x, y };
										}
										else // Horizontal
										{
											int x = std::min(connectP.first->getCoord().first, connectP.second->getCoord().first);
											int y = connectP.first->getCoord().second;
											updateHLine(x, y);
											LastTurn = { 'H', x, y };
										}



										// Create box if Player completes it
										bool boxClosed = false;
										boxClosed = checkBoxesComplete();

										if (!boxClosed)
										{
											std::cout << "changing state\n";
											if (eState == Turn::Player1 && p2->isAI)
											{
												p2->thinking = false;
												setPlayerTurn(Turn::Player2);
											}
											else if (eState == Turn::Player2)
											{
												setPlayerTurn(Turn::Player1);
											}
										}


										// Reset
										connectP.first->setSelected(false);
										connectP = std::make_pair(nullptr, nullptr);

									}
									else // Not Pair
									{
										std::cout << "Not Pair\n";

									}
								}
								else
								{
									std::cout << "already connected!\n";
								}
							}
						}
					}
				}
			}
		}


	}

}

void DotsAndBoxes::update()
{
	// Event Polling
	while (window->pollEvent(ev))
	{
		pollEvents();

		// Mouse Position
		updateMousePositions();
		//printMousePos();

		updateUI();
		updateLines();
		updateDots();
	}

	//std::cout << getPlayerTurn()->getScore() << std::endl;
	updateBoxes();

	// Pulsate Dot if Selected
	if (connectP.first)
		connectP.first->update();

	//dotBoard[0][0]->update();
}

void DotsAndBoxes::renderUI()
{
	window->draw(ScoreTurnBox);
	window->draw(TurnColorBox);
	window->draw(*p1Score);
	window->draw(*p2Score);

	if (p1->getScore() + p2->getScore() == maxPoints)
	{
		window->draw(WinBox);
		if (p1->getScore() == p2->getScore())
		{
			WinText->setString("This game \nis a Tie!");
			WinText->setFillColor(sf::Color::Black);
		}
		else
		{
			WinText->setString((p1->getScore() < p2->getScore() ? p2->getName() : p1->getName()) + std::string(" Wins!"));
			WinText->setFillColor(p1->getScore() < p2->getScore() ? p2->color : p1->color);
		}
		window->draw(*WinText);
	}
}

void DotsAndBoxes::renderBoxes()
{
	for (auto xB : board)
	{
		for (Box* yB : xB)
		{
			window->draw(*yB->getBox());
			if (longChainV || ChainV2 || ChainV1)
				window->draw(*yB->D_getBox());
			if (jointBoxV)
				window->draw(*yB->J_getBox());
			if (valenceT)
				window->draw(*yB->getText());
		}
	}
}

void DotsAndBoxes::renderLines()
{
	for (auto xL : H_linesBoard)
	{
		for (Line* yL : xL)
			window->draw(*yL->getLine());
	}
	for (auto xL : V_linesBoard)
	{
		for (Line* yL : xL)
			window->draw(*yL->getLine());
	}
}

void DotsAndBoxes::renderDots()
{
	for (auto xD : dotBoard)
	{
		for (Dot* yD : xD)
		{
			window->draw(*yD->getDot());
		}
	}
}



void DotsAndBoxes::render()
{

	window->clear(sf::Color(255, 0, 0, 255));	// Clear Frame


	// Draw Game Objects
	renderBoxes();
	renderLines();
	renderDots();

	renderUI();


	window->display(); // Display Render Frame
}
