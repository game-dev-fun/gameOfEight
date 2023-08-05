#include<iostream>
#include<string>
#include<cctype>


//Two players can play this game
enum class Player
{
	Player_one,
	Player_two
};

//main loop of the game
void playGame();

//player chooses a number except the last player choice
int chosenNum(int lastPlayerChoice = 0);

//prints the appropriate choices the player has
std::string validNumString(int lastPlayerChoice = 0);

//prints which players turn it is
void playerTurn(Player player);

//check if there is a winner yet
bool checkWinner(int& initial, int choosen, Player player);

//prints the player that won
void printWinner(Player player);

//changes the player turn
Player changePlayer(Player player);

//takes y or n as char input and return true if y else false
bool replayGame();

//calls playGame and once the game is over, it calls replayGame to see if players wants to replay
void gameOfEight();


void printInstructions();

int main()
{
	gameOfEight();
	return 0;
}

void printInstructions()
{
	std::cout << "Welcome to the Game of Eight. It's a two player game. The game starts with an initial number 8 and the player 1 starts where the player 1 can choose from 1, 2 or 3 which is referred to as a chosen number. The chosen number will be subtracted from initial number and then it's player 2 turn. Player 2 can choose from 1, 2, or 3 but except the player 1 choice. If the initial number becomes 0 on your turn then you win and if it becomes less than 0 then the opponent wins.\n\n";
}

void gameOfEight()
{
	printInstructions();
	bool replay{ false };
	do
	{
		playGame();
		replay = replayGame();
	} while (replay);
}

bool replayGame()
{
	bool cinFail{ false };
	bool wrongChar{ false };
	char input{};
	constexpr int CHARS_IGNORE{ 256 };
	do
	{
		std::cout << "Do you want to replay the game(y or n): ";
		std::cin >> input;
		cinFail = std::cin.fail();
		if (cinFail)
		{
			std::cout << "Please enter a valid character.\n";
			std::cin.clear();
			std::cin.ignore(CHARS_IGNORE, '\n');
		}
		else
		{
			input = std::tolower(input);
			wrongChar = !(input == 'y' || input == 'n');
			if (wrongChar)
			{
				std::cout << "Please enter y or n.\n";
			}
		}
	} while (cinFail || wrongChar);
	return input == 'y';
}

void printWinner(Player player)
{
	if (player == Player::Player_one)
	{
		std::cout << "Player 1 won!\n";
	}
	else
	{
		std::cout << "Player 2 won!\n";
	}
}

void playerTurn(Player player)
{
	if (player == Player::Player_one)
	{
		std::cout << "Player 1 turn.\n";
	}
	else
	{
		std::cout << "Player 2 turn.\n";
	}
}

Player changePlayer(Player player)
{
	if (player == Player::Player_one)
	{
		player = Player::Player_two;
	}
	else
	{
		player = Player::Player_one;
	}
	return player;
}

bool checkWinner(int& initial, int choosen, Player player)
{
	initial -= choosen;
	if (initial == 0)
	{
		printWinner(player);
		return true;
	}
	else if (initial < 0)
	{
		printWinner(changePlayer(player));
		return true;
	}
	return false;
}

void playGame()
{
	int initialNum{ 8 };
	Player player{ Player::Player_one };
	int chosen{};
	bool gameOver{ false };
	do
	{
		std::cout << "Initial number is: " << initialNum << '\n';
		playerTurn(player);
		chosen = chosenNum(chosen);
		gameOver = checkWinner(initialNum, chosen, player);
		player = changePlayer(player);
	} while (!gameOver);

}

int chosenNum(int lastPlayerChoice)
{
	bool cinFail{ false };
	bool wrongChoice{ false };
	int chosen{};
	constexpr int CHARS_IGNORE{ 256 };
	do
	{
		std::cout << validNumString(lastPlayerChoice);
		std::cin >> chosen;
		cinFail = std::cin.fail();
		if (cinFail)
		{
			std::cout << "Please enter a valid int.\n";
			std::cin.clear();
			std::cin.ignore(CHARS_IGNORE, '\n');
		}
		else
		{
			wrongChoice = !(chosen >= 1 && chosen <= 3 && chosen != lastPlayerChoice);
			if (wrongChoice)
			{
				std::cout << "Wrong int.\n";
			}
		}

	} while (cinFail || wrongChoice);
	return chosen;
}

std::string validNumString(int lastPlayerChoice)
{
	std::string str{"Please enter "};
	switch (lastPlayerChoice)
	{
	case 0:
		str += "1, 2 or 3: ";
		break;
	case 1:
		str += "2 or 3: ";
		break;
	case 2:
		str += "1 or 3: ";
		break;
	case 3:
		str += "1 or 2: ";
	}
	return str;
}
