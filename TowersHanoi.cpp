#include <iostream>
#include <string>

using namespace std;

class HanoiStack //Stack that holds number of disks in a column, size of each disk.
{
private:

	struct Disk
	{
		int size;
		Disk *next;
	};

	Disk *top;

public:
	HanoiStack()
	{
		top = NULL;
	}


	void push(int);
	void pop(int &);
	bool isEmpty();
	void display();
};


int main()
{
	int catchVar = 0, tempCatch, tempCatch2;
	int startingDiscs = 0;
	int columnFrom = 0, columnTo = 0;
	bool winCondition = false;
	bool isEmpty;
	HanoiStack stack[3]; //1 stack for each column.

	while (startingDiscs > 10 || startingDiscs < 3) //Input validation for the number of starting discs.
	{
		cout << "You must have at least 3 starting discs and no more than 10.";
		cout << "How many discs would you like to start the puzzle with?" << endl;
		cin >> startingDiscs;
	}

	cout << "Each disk is represented by a number, indicating it's size. 5 is the smallest disk, while 1 is the largest." << endl;

	int numDiscs[3] {startingDiscs, 0, 0};

	for (int count = 0; count < startingDiscs; count++) //Populates first stack with number of correct disks.
	{
		stack[0].push(count + 1);
	}

	cout << "The discs in column 1 are " << endl;
	stack[0].display();
	cout << "The discs in column 2 are " << endl;
	stack[1].display();
	cout << "The discs in column 3 are " << endl;
	stack[2].display();

	cout << "Enter the column number you wish to move a disc from:" << endl;
	cin >> columnFrom;
	while (columnFrom > 3 || columnFrom <= 0) //Input validation for entering correct column, reappears throughout.
	{
		cout << "You must enter 1, 2, or 3 when selecting your column number." << endl;
		cout << "Enter the column number you wish to move a disc from:" << endl;
		cin >> columnFrom;
	}
	columnFrom--;
	
	cout << "Enter the column number you wish to move the disc to:" << endl;
	cin >> columnTo;
	while (columnTo > 3 || columnTo <= 0)
	{
		cout << "You must enter 1, 2, or 3 when selecting your column number." << endl;
		cout << "Enter the column number you wish to move a disc from:" << endl;
		cin >> columnTo;
	}
	columnTo--;

	stack[columnFrom].pop(catchVar); //Pop's the stack from the first column, populates the to column.
	tempCatch = catchVar;
	numDiscs[columnFrom]--;
	stack[columnTo].push(tempCatch);
	numDiscs[columnTo]++;

	while (winCondition != true)
	{
		cout << "The discs in column 1 are " << endl;
		stack[0].display();
		cout << "The discs in column 2 are " << endl;
		stack[1].display();
		cout << "The discs in column 3 are " << endl;
		stack[2].display();

		cout << "Enter the column number you wish to move a disc from:" << endl;
		cin >> columnFrom;
		while (columnFrom > 3 || columnFrom <= 0)
		{
			cout << "You must enter 1, 2, or 3 when selecting your column number." << endl;
			cout << "Enter the column number you wish to move a disc from:" << endl;
			cin >> columnFrom;
		}
		columnFrom--;

		cout << "Enter the column number you wish to move the disc to:" << endl;
		cin >> columnTo;
		while (columnTo > 3 || columnTo <= 0)
		{
			cout << "You must enter 1, 2, or 3 when selecting your column number." << endl;
			cout << "Enter the column number you wish to move a disc from:" << endl;
			cin >> columnTo;
		}
		columnTo--;

		stack[columnFrom].pop(catchVar);
		tempCatch = catchVar;
		numDiscs[columnFrom]--;

		isEmpty = stack[columnTo].isEmpty();
		if (isEmpty == true) //If the to stack is empty, populates it automatically and reiterates the loop.
		{
			stack[columnTo].push(catchVar);
			numDiscs[columnTo]++;
			continue;
		}

		else
		{
			stack[columnTo].pop(catchVar);
			tempCatch2 = catchVar;
			numDiscs[columnTo]--;
		}

		while (tempCatch < tempCatch2) //Pops both values and compares them, in order to determine if the player is choosing a larger disk to place on a smaller on.
		{
			stack[columnFrom].push(tempCatch); //Resets to original values.
			numDiscs[columnFrom]++;
			stack[columnTo].push(catchVar);
			numDiscs[columnTo]--;
			
			cout << "You cannot place a larger disc on top of a smaller disc." << endl;
			cout << "The discs in column 1 are " << endl;
			stack[0].display();
			cout << "The discs in column 2 are " << endl;
			stack[1].display();
			cout << "The discs in column 3 are " << endl;
			stack[2].display();

			cout << "Enter the column number you wish to move a disc from:" << endl;
			cin >> columnFrom;
			while (columnFrom > 3 || columnFrom <= 0)
			{
				cout << "You must enter 1, 2, or 3 when selecting your column number." << endl;
				cout << "Enter the column number you wish to move a disc from:" << endl;
				cin >> columnFrom;
			}
			columnFrom--;

			cout << "Enter the column number you wish to move the disc to:" << endl;
			cin >> columnTo;
			while (columnTo > 3 || columnTo <= 0)
			{
				cout << "You must enter 1, 2, or 3 when selecting your column number." << endl;
				cout << "Enter the column number you wish to move a disc from:" << endl;
				cin >> columnTo;
			}
			columnTo--;

			stack[columnFrom].pop(catchVar); //Repopulates, pops again to compare again.
			tempCatch = catchVar;
			numDiscs[columnFrom]--;
			stack[columnTo].pop(catchVar);
			tempCatch2 = catchVar;
			numDiscs[columnTo]++;
		}

		stack[columnTo].push(catchVar); //Pushes new values if validated.
		stack[columnTo].push(tempCatch);
	}



	return 0;
}

void HanoiStack::display() //Displays values of the stack.
{
	Disk *nodePtr;

	nodePtr = top;

	while (nodePtr)
	{
		cout << nodePtr->size << endl;
		nodePtr = nodePtr->next;
	}
}

void HanoiStack::push(int num) //Pushes size into stack, create new node.
{
	Disk *newNode = NULL;

	newNode = new Disk;
	newNode->size = num;

	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}

	else
	{
		newNode->next = top;
		top = newNode;
	}
}

void HanoiStack::pop(int &num) //Pops stack, removes node.
{
	Disk *temp = NULL;

	if (isEmpty())
	{
		cout << "The column is empty." << endl;
	}

	else
	{
		num = top->size;
		temp = top->next;
		delete top;
		top = temp;
	}
}

bool HanoiStack::isEmpty() //Determines if a column is empty.
{
	bool status;

	if (!top)
	{
		status = true;
	}

	else
	{
		status = false;
	}

	return status;
}
