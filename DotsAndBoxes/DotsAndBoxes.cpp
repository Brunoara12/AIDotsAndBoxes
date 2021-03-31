#include "DotsAndBoxes.h"



void DotsAndBoxes::initVariables()
{
	this->window = nullptr;
	dotsX = dotsY = 3;
	dotOffset = 150;
	topOffset = 100;
	marginOffset = 150;
	dotR = 30.f;
	screenW = screenH = (dotOffset * (dotsX - 1)) + marginOffset;
	screenH += topOffset;
}

void DotsAndBoxes::initGameVar()
{
	eState = Turn::Player1;
	p1 = new Player("p1", sf::Color::Cyan);
	p2 = new Player("p2", sf::Color::Magenta);

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

DotsAndBoxes::DotsAndBoxes()
{
	initVariables();
	initGameVar();
	initUI();
	initWindow();
	initDots();
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
	case sf::Event::MouseButtonReleased:
		if (ev.mouseButton.button == sf::Mouse::Right)
		{

			for (auto d : board[0][0]->dotsInBox)
			{
				std::cout << d->getCoord().first << " " << d->getCoord().second << "\n";
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

										// Create Line From each other
										Line* tmpLine = new Line(dotOffset, marginOffset, topOffset, dotR);

										// Create box if Player completes it
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
										if (!boxClosed)
										{
											std::cout << "changing state\n";
											if (eState == Turn::Player1)
												setPlayerTurn(Turn::Player2);
											else if (eState == Turn::Player2)
												setPlayerTurn(Turn::Player1);
										}

										tmpLine->connectPair(connectP);
										linesBoard.push_back(tmpLine);

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

	std::cout << getPlayerTurn()->getScore() << std::endl;
	updateBoxes();

	// Pulsate Dot if Selected
	if (connectP.first)
		connectP.first->update();
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
		}
	}
}

void DotsAndBoxes::renderLines()
{
	for (Line* l : linesBoard)
	{
		window->draw(*l->getLine());
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
