/* 	The goal for this Project is to create a simple two-dimensional predator-prey simulation. In this simulation the prey are ants and the pred-ators are doodlebugs. These critters live in a world composed of a 20 × 20 grid of cells. Only one critter may occupy a cell at a time. The grid is  enclosed, so a critter is not allowed to move off the edges of the world. Time is simulated in time steps. Each critter performs some action every time step.
*
*	The ants behave according to the following model:
*	Move. Every time step, randomly try to move up, down, left, or right. If the neighboring cell in the selected direction is occupied or would move the ant off the grid, then the ant stays in the current cell.
*		
*	Breed. If an ant survives for three time steps, then at the end of the time step (that is; after moving) the ant will breed. This is simulated by creat-ing a new ant in an adjacent (up, down, left, or right) cell that is empty. If there is no empty cell available, then no breeding occurs. Once an off-spring is produced, an ant cannot produce an offspring until three more time steps have elapsed.
*		
*	The doodlebugs behave according to the following model:
*	Move. Every time step, if there is an adjacent ant (up, down, left, or right), then the doodlebug will move to that cell and eat the ant. Otherwise, the doodlebug moves according to the same rules as the ant. Note that a doodlebug cannot eat other doodlebugs.
*		
*	Breed. If a doodlebug survives for eight time steps, then at the end of the time step it will spawn off a new doodlebug in the same manner as the ant.
*		
*	Starve. If a doodlebug has not eaten an ant within the last three time steps, then at the end of the third time step it will starve and die. The doodlebug should then be removed from the grid of cells.
*		
*	During one turn, all the doodlebugs should move before the ants do.
*		
*	Write a program to implement this simulation and draw the world using ASCII characters of “o” for an ant and “X” for a doodlebug or "-" for an empty space. Create a class named Organism that encapsulates basic data common to both ants and doodlebugs. This class should have a virtual function named move that is defined in the derived classes of Ant and Doodlebug. You may need additional data structures to keep track of which critters have moved.
*		
*	Initialize the world with 5 doodlebugs and 100 ants. After each time step, prompt the user to press Enter to move to the next time step. You should see a cyclical pattern between the population of predators and prey, although random perturbations may lead to the elimination of one or both species.
*/

#include <iostream>
#include <time.h> 
#include <vector>
#include <string>

const int grid_width = 20;
const int grid_height = 20;
const int ants_init_num = 100;
const int doodlebugs_init_num = 5;

using namespace std;

struct position {
	int x;
	int y;
};

int generateRandomNumber(int begining, int end);
position getUpdatedDirection(position currentPosition, int direction);

class Organism
{
public:
	Organism();
	virtual void move();
	virtual void breed();
	virtual char getMarker() const;
private:
	char marker;
};

Organism::Organism()
{
	marker = '-';
}

void Organism::move()
{
	cout << "Move function" << endl;
}

void Organism::breed()
{
	cout << "Breed function" << endl;
}


char Organism::getMarker() const
{
	return marker;
}

class World
{
	friend class Ant;
	friend class Doodlebug;
public:
	World() {};
	~World();
	int getCurrentStep();
	void initializeOrganisms();
	void fillGrid(string type, int size);
	void displayGrid();
	void incrementStep();
	void updateGrid();
	void updateBugs(char marker);
private:
	int currentStep = 0;
	Organism* bugs[grid_width][grid_height];
};

World::~World()
{
	for (int i = 0; i < grid_width; i++)
	{
		for (int j = 0; j < grid_height; j++)
		{
			delete[] bugs[i][j];
		}
	}
}

void World::initializeOrganisms() 
{
	for (int i = 0; i < grid_width; i++)
	{
		for (int j = 0; j < grid_height; j++)
		{
			bugs[i][j] = new Organism;
		}
	}
}

void World::displayGrid()
{
	for (int i = 0; i < grid_width; i++)
	{
		for (int j = 0; j < grid_height; j++)
		{
			cout << bugs[i][j]->getMarker() << "  ";
		}
		cout << endl;
	}
}

void World::incrementStep()
{
	currentStep += 1;
}

int World::getCurrentStep()
{
	return currentStep;
}

void World::updateGrid()
{
	updateBugs('X');
	updateBugs('o');
}

void World::updateBugs(char marker)
{
	for (int i = 0; i < grid_width; i++)
	{
		for (int j = 0; j < grid_height; j++)
		{
			if (bugs[i][j]->getMarker() == marker)
			{
				bugs[i][j]->move();
			}
		}
	}

	for (int i = 0; i < grid_width; i++)
	{
		for (int j = 0; j < grid_height; j++)
		{
			if (bugs[i][j]->getMarker() == marker)
			{
				bugs[i][j]->breed();
			}
		}
	}
}

class Ant : public Organism
{
public:
	Ant(World& world, int x, int y, bool freshlyBred = false);
	char getMarker() const;
	void move();
	void breed();
private:
	bool freshlyBred;
	bool recentlyMoved;
	char marker;
	int breedingCount;
	int x;
	int y;
	World* world;
};

Ant::Ant(World& newWorld, int newX, int newY, bool newFreshlyBred)
{
	marker = 'o';
	x = newX;
	y = newY;
	world = &newWorld;
	breedingCount = 0;
	freshlyBred = newFreshlyBred;
	recentlyMoved = false;
}

char Ant::getMarker() const
{
	return marker;
}

void Ant::move()
{
	if (recentlyMoved == true)
	{
		recentlyMoved = false;
		return;
	}

	position oldPosition;
	oldPosition.x = x;
	oldPosition.y = y;

	position updatedPosition;
	updatedPosition.x = x;
	updatedPosition.y = y;

	int direction = generateRandomNumber(0, 3);
	updatedPosition = getUpdatedDirection(oldPosition, direction);

	if (
		updatedPosition.x >= 0 && updatedPosition.x < grid_width &&
		updatedPosition.y >= 0 && updatedPosition.y < grid_height &&
		world->bugs[updatedPosition.x][updatedPosition.y]->getMarker() == '-'
		)
	{
		if (oldPosition.x < updatedPosition.x || oldPosition.y < updatedPosition.y)
		{
			recentlyMoved = true;
		}

		x = updatedPosition.x;
		y = updatedPosition.y;
		world->bugs[updatedPosition.x][updatedPosition.y] = this;
		world->bugs[oldPosition.x][oldPosition.y] = new Organism;
	}
}

void Ant::breed()
{
	if (freshlyBred == true)
	{
		freshlyBred = false;
		return;
	}

	if (breedingCount == 3)
	{
		position updatedPosition;
		position oldPosition;
		oldPosition.x = x;
		oldPosition.y = y;

		for (int i = 0; i < 4; i++)
		{
			updatedPosition = getUpdatedDirection(oldPosition, i);
			if (
				updatedPosition.x >= 0 && updatedPosition.x < grid_width &&
				updatedPosition.y >= 0 && updatedPosition.y < grid_height &&
				world->bugs[updatedPosition.x][updatedPosition.y]->getMarker() == '-'
				)
			{				
				bool hasBeenBred = false;
				if (oldPosition.x < updatedPosition.x || oldPosition.y < updatedPosition.y)
				{
					hasBeenBred = true;
				}
				world->bugs[updatedPosition.x][updatedPosition.y] = new Ant(*world, updatedPosition.x, updatedPosition.y, hasBeenBred);
				break;
			}
		}

		breedingCount = 0;
		return;
	}

	breedingCount++;
}

class Doodlebug : public Organism
{
public:
	Doodlebug(World& world, int x, int y, bool freshlyBred = false);
	char getMarker() const;
	void breed();
	void move();

private:
	bool freshlyBred;
	bool recentlyMoved;
	char marker;
	int x;
	int y;
	int starveCount;
	int breedingCount;
	World* world;
};

Doodlebug::Doodlebug(World& newWorld, int newX, int newY, bool newFreshlyBred)
{
	marker = 'X';
	x = newX;
	y = newY;
	world = &newWorld;
	breedingCount = 0;
	freshlyBred = newFreshlyBred;
	recentlyMoved = false;
	starveCount = 0;
}

char Doodlebug::getMarker() const
{
	return marker;
}

void Doodlebug::breed()
{
	if (freshlyBred == true)
	{
		freshlyBred = false;
		return;
	}

	if (breedingCount == 8)
	{
		position updatedPosition;
		position oldPosition;
		oldPosition.x = x;
		oldPosition.y = y;

		for (int i = 0; i < 4; i++)
		{
			updatedPosition = getUpdatedDirection(oldPosition, i);

			if (
				updatedPosition.x >= 0 && updatedPosition.x < grid_width &&
				updatedPosition.y >= 0 && updatedPosition.y < grid_height &&
				world->bugs[updatedPosition.x][updatedPosition.y]->getMarker() == '-'
				)
			{
				bool hasBeenBred = false;
				if (oldPosition.x < updatedPosition.x || oldPosition.y < updatedPosition.y)
				{
					hasBeenBred = true;
				}
				world->bugs[updatedPosition.x][updatedPosition.y] = new Doodlebug(*world, updatedPosition.x, updatedPosition.y, hasBeenBred);
				break;
			}
		}
		breedingCount = 0;
		return;
	}

	breedingCount++;
}

void Doodlebug::move()
{
	starveCount++;
	if (recentlyMoved == true)
	{
		recentlyMoved = false;
		return;
	}

	position oldPosition;
	oldPosition.x = x;
	oldPosition.y = y;

	position updatedPosition;
	updatedPosition.x = x;
	updatedPosition.y = y;

	for (int i = 0; i < 4; i++)
	{
		updatedPosition = getUpdatedDirection(oldPosition, i);

		if (
			updatedPosition.x >= 0 && updatedPosition.x < grid_width &&
			updatedPosition.y >= 0 && updatedPosition.y < grid_height &&
			world->bugs[updatedPosition.x][updatedPosition.y]->getMarker() == 'o'
			)
		{
			if (oldPosition.x < updatedPosition.x || oldPosition.y < updatedPosition.y)
			{
				recentlyMoved = true;
			}

			x = updatedPosition.x;
			y = updatedPosition.y;

			world->bugs[updatedPosition.x][updatedPosition.y] = this;
			world->bugs[oldPosition.x][oldPosition.y] = new Organism;

			starveCount = 0;
			break;
		}
	}

	if (starveCount == 4)
	{
		int oldX = this->x;
		int oldY = this->y;
		World* world = this->world;
		delete[] (world->bugs[oldX][oldY]);
		world->bugs[oldX][oldY] = new Organism;
	}
}

void World::fillGrid(string type, int size)
{
	for (int i = 0; i < size; i++)
	{
		while (true)
		{
			int x = generateRandomNumber(0, grid_width - 1);
			int y = generateRandomNumber(0, grid_height - 1);

			if (bugs[x][y]->getMarker() == '-')
			{
				if (type == "ant")
				{
					bugs[x][y] = new Ant(*this, x, y);
				}
				else if (type == "doodlebug")
				{
					bugs[x][y] = new Doodlebug(*this, x, y);
				}
				break;
			}
		}
	}
}

int main()
{
	srand(time(NULL));

	World world;

	world.initializeOrganisms();
	
	world.fillGrid("ant", ants_init_num);
	world.fillGrid("doodlebug", doodlebugs_init_num);

	world.displayGrid();

	string enter;

	do
	{
		cout << endl << "Press enter to move to the next step" << endl;
		cout << "Current step: " << world.getCurrentStep() << endl;
		getline(cin, enter);

		world.updateGrid();

		world.displayGrid();

		world.incrementStep();

	} while (enter.length() == 0);
	return 0;
}

int generateRandomNumber(int begining, int end)
{
	return begining + (rand() % (end - begining + 1));
}

position getUpdatedDirection(position currentPosition, int direction)
{
	position updatedPosition;
	switch (direction)
	{
	// up
	case 0:
		updatedPosition.y = currentPosition.y - 1;
		updatedPosition.x = currentPosition.x;
		break;
	// right
	case 1:
		updatedPosition.x = currentPosition.x + 1;
		updatedPosition.y = currentPosition.y;
		break;
	// up
	case 2:
		updatedPosition.y = currentPosition.y + 1;
		updatedPosition.x = currentPosition.x;
		break;
	// left
	case 3:
		updatedPosition.x = currentPosition.x - 1;
		updatedPosition.y = currentPosition.y;
		break;
	}
	return updatedPosition;
}
