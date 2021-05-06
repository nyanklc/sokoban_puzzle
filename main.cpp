#include <iostream>
#include <fstream>
#include "StackQueue2.h"

using namespace std;

// Time Spent: ~30 Hours.

// grid size, can be modified but initial data should be appropriate.
const int NumberOfRows = 6;
const int NumberOfCols = 8;

// initial state of the map in a one dimensional array.
char initialData1[] = "######  #.  .####@$#$  ##$. .$ ##    $.#########";

// maximum stackqueue size here.
const int MaxStackQueueSize = 120;

// characters representing the elements of the game.
const char player = '@';
const char target = '.';
const char playerAtTarget = '+';
const char emptyCell = ' ';
const char movableBox = '$';
const char movableBoxAtTarget = '*';
const char wall = '#';

// StackQueue class declaration (template).

template <class T>
class StackQueue
{
private:
	T stackqueuelist[MaxStackQueueSize];
	int frontindex;
	int rearindex;
	int numOfElements;
public:
	StackQueue(void);// constructor, initializing data variables.
	void push_front(const T& var);
	T pop_front();
	T pop_rear();
	bool is_full();
	bool is_empty();
	int numOfE(); // returns number of elements inside the storage.
	T get_front();
};

// StackQueue class implementation.

// just returns the T data in front
template<class T>
T StackQueue<T>::get_front()
{
	return stackqueuelist[frontindex - 1];
}

template <class T>
int StackQueue<T>::numOfE()
{
	return numOfElements;
}

template <class T>
StackQueue<T>::StackQueue(void)
{
	frontindex = 0;
	rearindex = 0;
	numOfElements = 0;
}

template <class T>
bool StackQueue<T>::is_full()
{
	return (numOfElements == MaxStackQueueSize);
}

template <class T>
bool StackQueue<T>::is_empty()
{
	return (numOfElements == 0);
}

template <class T>
void StackQueue<T>::push_front(const T& var) // stores a new element at the front of the storage
{
	if (is_full())
	{
		cerr << "stackqueue is full." << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		stackqueuelist[frontindex] = var;
		frontindex++;
		if (frontindex == MaxStackQueueSize)
			frontindex = 0;
		numOfElements++;
	}
}

template <class T>
T StackQueue<T>::pop_front() // returns the element at the front of the storage
{
	if (is_empty())
	{
		cerr << "stackqueue is empty." << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		frontindex--;
		if (frontindex == -1)   // this 'if' expression could also be written as a modulus operation on the line above
			frontindex = MaxStackQueueSize - 1;
		numOfElements--;
		return stackqueuelist[frontindex];
	}
}

template <class T>
T StackQueue<T>::pop_rear() // returns the element at the rear of the storage
{
	if (is_empty())
	{
		cerr << "stackqueue is empty." << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		int temp = rearindex; // temporary variable required to return the 'popped' element
		rearindex++;          // since rearindex is changed
		if (rearindex == MaxStackQueueSize)
			rearindex = 0;
		numOfElements--;
		return stackqueuelist[temp];
	}
}

// Sokoban class declaration.

class Sokoban
{
private:
	char data[NumberOfRows][NumberOfCols];
	int playerRow = 0;
	int playerCol = 0;
public:
	Sokoban(char* initialData = initialData1); //constructor that initializes the class from a char array.
	Sokoban(string path); //constructor that initializes the class from a text file.
	Sokoban(const Sokoban& obj); //a copy constructor.
	bool move_up();
	bool move_down();
	bool move_left();
	bool move_right();
	bool is_solved() const;
	void print_puzzle() const;
	Sokoban& operator=(const Sokoban& rhs); //copy assignment operator
};

// Sokoban class implementation.

Sokoban::Sokoban(char* initialData) // assigns the characters held in initialData to their appropriate places in data.
{
	for (int i = 0; i < NumberOfRows; i++)
	{
		for (int j = 0; j < NumberOfCols; j++)
		{
			data[i][j] = *(initialData + NumberOfCols * i + j);
			if ((data[i][j] == player) || (data[i][j] == playerAtTarget))
			{
				playerRow = i;
				playerCol = j;
			}
		}
	}
}


Sokoban::Sokoban(string path) // reads the data from a text file and assigns to the data array.
{
	char dummy;
	ifstream file;
	file.open(path);
	for (int i = 0; i < NumberOfRows; i++)
	{
		for (int j = 0; j < NumberOfCols; j++)
		{
			file >> noskipws >> data[i][j];
			if ((data[i][j] == player) || (data[i][j] == playerAtTarget))
			{
				playerRow = i;
				playerCol = j;
			}
		}
		file >> noskipws >> dummy;
	}

	file.close();
}

Sokoban::Sokoban(const Sokoban& obj) // Makes the necessary assignments when an instance is initialized as a copy of another instance of the class Sokoban.
{
	for (int i = 0; i < NumberOfRows; i++)
	{
		for (int j = 0; j < NumberOfCols; j++)
		{
			data[i][j] = obj.data[i][j];
			if ((data[i][j] == player) || (data[i][j] == playerAtTarget))
			{
				playerRow = i;
				playerCol = j;
			}
		}
	}
}

Sokoban& Sokoban::operator=(const Sokoban& rhs) // Makes the necessary assignments when an instance is copied from another instance of the class Sokoban.
{
	for (int i = 0; i < NumberOfRows; i++)
	{
		for (int j = 0; j < NumberOfCols; j++)
		{
			data[i][j] = rhs.data[i][j];
			if ((data[i][j] == player) || (data[i][j] == playerAtTarget))
			{
				playerRow = i;
				playerCol = j;
			}
		}
	}
	return *this;
}

void Sokoban::print_puzzle() const // prints the current state of the data array.
{
	for (int i = 0; i < NumberOfRows; i++)
	{
		for (int j = 0; j < NumberOfCols; j++)
		{
			cout << data[i][j] << " ";
		}
		cout << endl;
	}
}

bool Sokoban::is_solved() const // returns true if all the target locations turned into target locations with boxes on them
{
	for (int i = 0; i < NumberOfRows; i++)
	{
		for (int j = 0; j < NumberOfCols; j++)
		{
			if ((data[i][j] == target) || (data[i][j] == playerAtTarget))
				return false;
		}
	}
	return true;
}

// movement methods' implementation.
bool Sokoban::move_up()
{
	// checking if the move is possible according to the rules of the game.
	if (data[playerRow - 1][playerCol] == wall)
	{
		cout << "this move is not possible" << endl;
		print_puzzle();
		return false;
	}
	else if (((data[playerRow - 1][playerCol] == movableBox) || (data[playerRow - 1][playerCol] == movableBoxAtTarget)) && ((data[playerRow - 2][playerCol] == movableBox) || (data[playerRow - 2][playerCol] == movableBoxAtTarget)))
	{
		cout << "this move is not possible" << endl;
		print_puzzle();
		return false;
	}
	else if (((data[playerRow - 1][playerCol] == movableBox) || (data[playerRow - 1][playerCol] == movableBoxAtTarget)) && (data[playerRow - 2][playerCol] == wall))
	{
		cout << "this move is not possible" << endl;
		print_puzzle();
		return false;
	}
	// moving the player and changing the data values accordingly.
	// this part is probably difficult to read, but it just checks the blocks where the player is on, the one above it, and the one above it,
	// then makes the adjustments on the data array.
	// different cases according to the block above the player, and checks if the player is standing on a target block too.
	// checks if the puzzle is solved every time a successful move is done.
	else
	{   // just moving the player. (moving the player and pushing the box part is below)
		if (data[playerRow - 1][playerCol] == target) // if the block above the player is a target
		{
			if (data[playerRow][playerCol] == playerAtTarget) // checking if the player is standing on a target block
			{
				data[playerRow][playerCol] = target;
				data[playerRow - 1][playerCol] = playerAtTarget;
				playerRow--;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
			else
			{
				data[playerRow][playerCol] = emptyCell;
				data[playerRow - 1][playerCol] = playerAtTarget;
				playerRow--;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
		}
		else if (data[playerRow - 1][playerCol] == emptyCell) // if the block above player is an empty cell.
		{
			if (data[playerRow][playerCol] == playerAtTarget)
			{
				data[playerRow][playerCol] = target;
				data[playerRow - 1][playerCol] = player;
				playerRow--;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
			else
			{
				data[playerRow][playerCol] = emptyCell;
				data[playerRow - 1][playerCol] = player;
				playerRow--;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
		}
		// moving the player and pushing the box above.
		else if (data[playerRow - 1][playerCol] == movableBox) // if the block above the player is a movable box.
		{
			if (data[playerRow][playerCol] == playerAtTarget)
			{
				data[playerRow][playerCol] = target;
				data[playerRow - 1][playerCol] = player;
				if (data[playerRow - 2][playerCol] == target) data[playerRow - 2][playerCol] = movableBoxAtTarget;
				else data[playerRow - 2][playerCol] = movableBox;
				playerRow--;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
			else
			{
				data[playerRow][playerCol] = emptyCell;
				data[playerRow - 1][playerCol] = player;
				if (data[playerRow - 2][playerCol] == target) data[playerRow - 2][playerCol] = movableBoxAtTarget;
				else data[playerRow - 2][playerCol] = movableBox;
				playerRow--;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
		}
		else if (data[playerRow - 1][playerCol] == movableBoxAtTarget) // if the block above the player is a movable box at a target location.
		{
			if (data[playerRow][playerCol] == playerAtTarget)
			{
				data[playerRow][playerCol] = target;
				data[playerRow - 1][playerCol] = playerAtTarget;
				if (data[playerRow - 2][playerCol] == target) data[playerRow - 2][playerCol] = movableBoxAtTarget;
				else data[playerRow - 2][playerCol] = movableBox;
				playerRow--;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
			else
			{
				data[playerRow][playerCol] = emptyCell;
				data[playerRow - 1][playerCol] = playerAtTarget;
				if (data[playerRow - 2][playerCol] == target) data[playerRow - 2][playerCol] = movableBoxAtTarget;
				else data[playerRow - 2][playerCol] = movableBox;
				playerRow--;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
		}
		// if this block runs during run-time, this means that something's wrong.
		// this is just an indicator for me to know where to look for.
		else
		{
			cerr << "check move_up function, there is an error" << endl;
			exit(EXIT_FAILURE);
		}
		return true;
	}
}

// other movement methods are implemented similarly to move_up method with
// some minor changes such as row-column indexes of the data array.
bool Sokoban::move_down()
{

	if (data[playerRow + 1][playerCol] == wall)
	{
		cout << "this move is not possible" << endl;
		print_puzzle();
		return false;
	}
	else if (((data[playerRow + 1][playerCol] == movableBox) || (data[playerRow + 1][playerCol] == movableBoxAtTarget)) && ((data[playerRow + 2][playerCol] == movableBox) || (data[playerRow + 2][playerCol] == movableBoxAtTarget)))
	{
		cout << "this move is not possible" << endl;
		print_puzzle();
		return false;
	}
	else if (((data[playerRow + 1][playerCol] == movableBox) || (data[playerRow + 1][playerCol] == movableBoxAtTarget)) && (data[playerRow + 2][playerCol] == wall))
	{
		cout << "this move is not possible" << endl;
		print_puzzle();
		return false;
	}
	else
	{
		if (data[playerRow + 1][playerCol] == target)
		{
			if (data[playerRow][playerCol] == playerAtTarget)
			{
				data[playerRow][playerCol] = target;
				data[playerRow + 1][playerCol] = playerAtTarget;
				playerRow++;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
			else
			{
				data[playerRow][playerCol] = emptyCell;
				data[playerRow + 1][playerCol] = playerAtTarget;
				playerRow++;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
		}
		else if (data[playerRow + 1][playerCol] == emptyCell)
		{
			if (data[playerRow][playerCol] == playerAtTarget)
			{
				data[playerRow][playerCol] = target;
				data[playerRow + 1][playerCol] = player;
				playerRow++;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
			else
			{
				data[playerRow][playerCol] = emptyCell;
				data[playerRow + 1][playerCol] = player;
				playerRow++;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
		}

		else if (data[playerRow + 1][playerCol] == movableBox)
		{
			if (data[playerRow][playerCol] == playerAtTarget)
			{
				data[playerRow][playerCol] = target;
				data[playerRow + 1][playerCol] = player;
				if (data[playerRow + 2][playerCol] == target) data[playerRow + 2][playerCol] = movableBoxAtTarget;
				else data[playerRow + 2][playerCol] = movableBox;
				playerRow++;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
			else
			{
				data[playerRow][playerCol] = emptyCell;
				data[playerRow + 1][playerCol] = player;
				if (data[playerRow + 2][playerCol] == target) data[playerRow + 2][playerCol] = movableBoxAtTarget;
				else data[playerRow + 2][playerCol] = movableBox;
				playerRow++;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
		}
		else if (data[playerRow + 1][playerCol] == movableBoxAtTarget)
		{
			if (data[playerRow][playerCol] == playerAtTarget)
			{
				data[playerRow][playerCol] = target;
				data[playerRow + 1][playerCol] = playerAtTarget;
				if (data[playerRow + 2][playerCol] == target) data[playerRow + 2][playerCol] = movableBoxAtTarget;
				else data[playerRow + 2][playerCol] = movableBox;
				playerRow++;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
			else
			{
				data[playerRow][playerCol] = emptyCell;
				data[playerRow + 1][playerCol] = playerAtTarget;
				if (data[playerRow + 2][playerCol] == target) data[playerRow + 2][playerCol] = movableBoxAtTarget;
				else data[playerRow + 2][playerCol] = movableBox;
				playerRow++;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
		}
		else
		{
			cerr << "check move_down function, there is an error" << endl;
			exit(EXIT_FAILURE);
		}
		return true;
	}
}

bool Sokoban::move_left()
{

	if (data[playerRow][playerCol - 1] == wall)
	{
		cout << "this move is not possible" << endl;
		print_puzzle();
		return false;
	}
	else if (((data[playerRow][playerCol - 1] == movableBox) || (data[playerRow][playerCol - 1] == movableBoxAtTarget)) && ((data[playerRow][playerCol - 2] == movableBox) || (data[playerRow][playerCol - 2] == movableBoxAtTarget)))
	{
		cout << "this move is not possible" << endl;
		print_puzzle();
		return false;
	}
	else if (((data[playerRow][playerCol - 1] == movableBox) || (data[playerRow][playerCol - 1] == movableBoxAtTarget)) && (data[playerRow][playerCol - 2] == wall))
	{
		cout << "this move is not possible" << endl;
		print_puzzle();
		return false;
	}
	else
	{
		if (data[playerRow][playerCol - 1] == target)
		{
			if (data[playerRow][playerCol] == playerAtTarget)
			{
				data[playerRow][playerCol] = target;
				data[playerRow][playerCol - 1] = playerAtTarget;
				playerCol--;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
			else
			{
				data[playerRow][playerCol] = emptyCell;
				data[playerRow][playerCol - 1] = playerAtTarget;
				playerCol--;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
		}
		else if (data[playerRow][playerCol - 1] == emptyCell)
		{
			if (data[playerRow][playerCol] == playerAtTarget)
			{
				data[playerRow][playerCol] = target;
				data[playerRow][playerCol - 1] = player;
				playerCol--;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
			else
			{
				data[playerRow][playerCol] = emptyCell;
				data[playerRow][playerCol - 1] = player;
				playerCol--;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
		}

		else if (data[playerRow][playerCol - 1] == movableBox)
		{
			if (data[playerRow][playerCol] == playerAtTarget)
			{
				data[playerRow][playerCol] = target;
				data[playerRow][playerCol - 1] = player;
				if (data[playerRow][playerCol - 2] == target) data[playerRow][playerCol - 2] = movableBoxAtTarget;
				else data[playerRow][playerCol - 2] = movableBox;
				playerCol--;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
			else
			{
				data[playerRow][playerCol] = emptyCell;
				data[playerRow][playerCol - 1] = player;
				if (data[playerRow][playerCol - 2] == target) data[playerRow][playerCol - 2] = movableBoxAtTarget;
				else data[playerRow][playerCol - 2] = movableBox;
				playerCol--;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
		}
		else if (data[playerRow][playerCol - 1] == movableBoxAtTarget)
		{
			if (data[playerRow][playerCol] == playerAtTarget)
			{
				data[playerRow][playerCol] = target;
				data[playerRow][playerCol - 1] = playerAtTarget;
				if (data[playerRow][playerCol - 2] == target) data[playerRow][playerCol - 2] = movableBoxAtTarget;
				else data[playerRow][playerCol - 2] = movableBox;
				playerCol--;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
			else
			{
				data[playerRow][playerCol] = emptyCell;
				data[playerRow][playerCol - 1] = playerAtTarget;
				if (data[playerRow][playerCol - 2] == target) data[playerRow][playerCol - 2] = movableBoxAtTarget;
				else data[playerRow][playerCol - 2] = movableBox;
				playerCol--;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
		}
		else
		{
			cerr << "check move_left function, there is an error" << endl;
			exit(EXIT_FAILURE);
		}
		return true;
	}
}

bool Sokoban::move_right()
{
	if (data[playerRow][playerCol + 1] == wall)
	{
		cout << "this move is not possible" << endl;
		print_puzzle();
		return false;
	}
	else if (((data[playerRow][playerCol + 1] == movableBox) || (data[playerRow][playerCol + 1] == movableBoxAtTarget)) && ((data[playerRow][playerCol + 2] == movableBox) || (data[playerRow][playerCol + 2] == movableBoxAtTarget)))
	{
		cout << "this move is not possible" << endl;
		print_puzzle();
		return false;
	}
	else if (((data[playerRow][playerCol + 1] == movableBox) || (data[playerRow][playerCol + 1] == movableBoxAtTarget)) && (data[playerRow][playerCol + 2] == wall))
	{
		cout << "this move is not possible" << endl;
		print_puzzle();
		return false;
	}
	else
	{
		if (data[playerRow][playerCol + 1] == target)
		{
			if (data[playerRow][playerCol] == playerAtTarget)
			{
				data[playerRow][playerCol] = target;
				data[playerRow][playerCol + 1] = playerAtTarget;
				playerCol++;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
			else
			{
				data[playerRow][playerCol] = emptyCell;
				data[playerRow][playerCol + 1] = playerAtTarget;
				playerCol++;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
		}
		else if (data[playerRow][playerCol + 1] == emptyCell)
		{
			if (data[playerRow][playerCol] == playerAtTarget)
			{
				data[playerRow][playerCol] = target;
				data[playerRow][playerCol + 1] = player;
				playerCol++;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
			else
			{
				data[playerRow][playerCol] = emptyCell;
				data[playerRow][playerCol + 1] = player;
				playerCol++;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
		}

		else if (data[playerRow][playerCol + 1] == movableBox)
		{
			if (data[playerRow][playerCol] == playerAtTarget)
			{
				data[playerRow][playerCol] = target;
				data[playerRow][playerCol + 1] = player;
				if (data[playerRow][playerCol + 2] == target) data[playerRow][playerCol + 2] = movableBoxAtTarget;
				else data[playerRow][playerCol + 2] = movableBox;
				playerCol++;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
			else
			{
				data[playerRow][playerCol] = emptyCell;
				data[playerRow][playerCol + 1] = player;
				if (data[playerRow][playerCol + 2] == target) data[playerRow][playerCol + 2] = movableBoxAtTarget;
				else data[playerRow][playerCol + 2] = movableBox;
				playerCol++;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
		}
		else if (data[playerRow][playerCol + 1] == movableBoxAtTarget)
		{
			if (data[playerRow][playerCol] == playerAtTarget)
			{
				data[playerRow][playerCol] = target;
				data[playerRow][playerCol + 1] = playerAtTarget;
				if (data[playerRow][playerCol + 2] == target) data[playerRow][playerCol + 2] = movableBoxAtTarget;
				else data[playerRow][playerCol + 2] = movableBox;
				playerCol++;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
			else
			{
				data[playerRow][playerCol] = emptyCell;
				data[playerRow][playerCol + 1] = playerAtTarget;
				if (data[playerRow][playerCol + 2] == target) data[playerRow][playerCol + 2] = movableBoxAtTarget;
				else data[playerRow][playerCol + 2] = movableBox;
				playerCol++;
				cout << "move successful." << endl;
				print_puzzle();
				if (is_solved())
				{
					cout << "PUZZLE IS SOLVED!" << endl;

				}
			}
		}
		else
		{
			cerr << "check move_right function, there is an error" << endl;
			exit(EXIT_FAILURE);
		}
		return true;
	}
}

// main function, initializes instances for the classes above and
// loops until the program terminates somehow, takes keyboard inputs.
int main()
{
	// the text file must have NumberOfRows rows, NumberOfCols columns, and white spaces should be correctly in place
	// otherwise the constructor doesn't read it correctly.
	string pth = "Sample_puzzle.txt";

	Sokoban sokob(pth); // "Sokoban sokob(initialData1);" to use the constructor that uses an array to initialize the instance


	// change the below line to StackQueue for stack/queue.
	// StackQueue2 is doubly linked list.
	StackQueue2<Sokoban> stackQ;


	sokob.print_puzzle();     // prints the initial state
	stackQ.push_front(sokob); // adds the first element to the storage
	char inp;
	while (1)
	{
		cin >> inp;
		if (toupper(inp) == 'W')
		{
			if (sokob.move_up())    // if sokob.move_up() returns true, it moves the player and prints the new state of the map
				stackQ.push_front(sokob); // pushes the new state into storage
		}
		else if (toupper(inp) == 'S')   // similar to above
		{
			if (sokob.move_down())
				stackQ.push_front(sokob);
		}
		else if (toupper(inp) == 'A')
		{
			if (sokob.move_left())
				stackQ.push_front(sokob);
		}
		else if (toupper(inp) == 'D')
		{
			if (sokob.move_right())
				stackQ.push_front(sokob);
		}
		else if (toupper(inp) == 'Z')
		{
			if (stackQ.numOfE() == 1)   // if 'z' is inputted on the initial state or after a replay
			{
				cerr << "no movement is done yet." << endl;
				sokob.print_puzzle();
				continue;
			}
			cout << endl;
			cout << "undoing the last move" << endl;
			stackQ.pop_front();         // undoes the last move, but doesn't print the previous state
			sokob = stackQ.get_front(); // this is where the copy assignment operator comes in handy
			sokob.print_puzzle();       // prints the state of the map
		}
		else if (toupper(inp) == 'R')
		{
			cout << endl;
			cout << "replaying all the moves" << endl;
			Sokoban tempSokob = sokob;  // a temporary instance to return to where we left off after the replay
			int temp = stackQ.numOfE();
			for (int i = 0; i < temp; i++)  // stackQ.numOfE() decreases with each pop_rear, that's why a temporary integer is used
			{
				stackQ.pop_rear().print_puzzle(); // prints the data from the bottom of the stack/queue
				cout << endl;
			}
			cout << "current state: " << endl;
			sokob = tempSokob;  // recovers the state before replay is done
			stackQ.push_front(sokob);
			sokob.print_puzzle();
		}

	}

	return 0;
}
