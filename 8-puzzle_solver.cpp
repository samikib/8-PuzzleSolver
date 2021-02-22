// Code is available at https://github.com/samikib/8-PuzzleSolver/
//

#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>

struct node
{
	std::vector<int> state; //current states
	int g = 0; //cost
	int h = 0; //heuristic value

	int f = 0;

	int depth = 0;

	node* parent;

	std::vector<node*> followers;

	void print_state()
	{
		int n = pow(state.size() + 1, .5);

		for (size_t i = 0; i < state.size(); i++)
		{
			std::cout << state[i] << " ";
			if (i%n == n-1)
			{
				std::cout << std::endl;
			}
		}
	}

	void print_expanding()
	{
		std::cout << "g(n) = " << g << " and h(n) = " << h << " is..." << std::endl;
		print_state();
	}

	int get_f()
	{
		f = g + h;
		return f;
	}

};

bool operator <(const node& n1, const node& n2)
{
	return n1.f < n2.f;
}

struct problem
{
	std::vector<int> intial_state;
	std::vector<int> goal;

	int n = 3;  //for an n x n game

	int expanded_nodes = 0;
	int max_nodes = 0;
	int depth = 0;

	std::vector<node*> found;

	
	//defines the goal state
	void define_goal()
	{
		for (size_t i = 0; i < pow(n,2)-1; i++)
		{
			goal.push_back(i + 1);
		}
		goal.push_back(0);
	}

	//"constructs" problem based on initial state and size
	void define_problem(std::vector<int> input, int size)
	{
		n = size;
		define_goal();

		for (size_t i = 0; i < input.size(); i++)
		{
			intial_state.push_back(input[i]);
		}

	}

	bool goal_test(std::vector<int> state)
	{
		for (size_t i = 0; i < state.size(); i++)
		{
			if (state[i] != goal[i])
			{
				return false;
			}
		}

		return true;
	}
	/*OPERATORS: The possible movements of the BLANK spot*/

	// move blank to the right
	node* move_right(std::vector<int> state)
	{
		int i;
		node* moved;

		//copies into moved and finds position of blank
		for (size_t k = 0; k < state.size(); k++)
		{
			if (state[k] == 0)
			{
				i = k;
			}
		}

		//checks that blank is in the left most position. swaps if not 
		if (i%n != n-1)
		{
			int temp = state[i + 1];
			state[i + 1] = state[i];
			state[i] = temp;

			moved = new node;
			moved->state = state;
		}
		else
		{
			moved = nullptr;
		}

		return moved;
	}

	// move blank to the left
	node* move_left(std::vector<int> state)
	{
		int i;
		node* moved;

		//copies into moved and finds position of blank
		for (size_t k = 0; k < state.size(); k++)
		{
			if (state[k] == 0)
			{
				i = k;
			}
		}

		//checks that blank is in the left most position. swaps if not 
		if (i%n != 0)
		{
			int temp = state[i - 1];
			state[i - 1] = state[i];
			state[i] = temp;

			moved = new node;
			moved->state = state;
		}
		else
		{
			moved = nullptr;
		}

		return moved;
	}

	// move blank up
	node* move_up(std::vector<int> state)
	{
		int i;
		node* moved;

		//copies into moved and finds position of blank
		for (size_t k = 0; k < state.size(); k++)
		{
			if (state[k] == 0)
			{
				i = k;
			}
		}

		//checks that blank is in the left most position. swaps if not 
		if (i / n != 0)
		{
			int temp = state[i - n];
			state[i - n] = state[i];
			state[i] = temp;

			moved = new node;
			moved->state = state;
		}
		else
		{
			moved = nullptr;
		}

		return moved;
	}

	// move blank down
	node* move_down(std::vector<int> state)
	{
		int i;
		node* moved;

		//copies into moved and finds position of blank
		for (size_t k = 0; k < state.size(); k++)
		{
			if (state[k] == 0)
			{
				i = k;
			}
		}

		//checks that blank is in the left most position. swaps if not 
		if (i / n != n - 1)
		{
			int temp = state[i + n];
			state[i + n] = state[i];
			state[i] = temp;

			moved = new node;
			moved->state = state;
		}
		else
		{
			moved = nullptr;
		}

		return moved;
	}

};


node* general_search(int queueing_function_choice, problem& cur);
void uniform_cost(problem& cur, node* expanding);
void AStar_Misplaced(problem& cur, node* expanding);
void AStar_Manhattan(problem& cur, node* expanding);

int smallestF(std::vector<node*> open);

int main()
{
	problem puzzle;
	std::vector<int> input;
	int num;


	std::cout << "Welcome to Samiha Kibria's 8-puzzle solver." << std::endl << std::endl
		<< "Enter your puzzle, represent blank with a 0"<< std::endl;

	for (size_t i = 0; i < 3; i++)
	{
		std::cout<< std::endl << "Enter row " << i+1 << ", separate numbers with spaces: ";

		std::cin >> num;
		input.push_back(num);

		std::cin >> num;
		input.push_back(num);

		std::cin >> num;
		input.push_back(num);
	}

	puzzle.define_problem(input, 3);


	std::cout << std::endl << "Enter choice of algorithm:" << std::endl
		<< "     1. Uniform Cost Search" << std::endl
		<< "     2. A* with Misplaced Tile heuristic" << std::endl
		<< "     3. A* with Manhattan distance heuristic" << std::endl;

	std::cin >> num;

	node* solution = general_search(num, puzzle);
	if (solution == nullptr)
	{
		std::cout<< "No solution to this initial state exists. Must solve by swapping tiles.";
	}
	else
	{
		std::stack<node*> steps;
		node* p = solution;
		while (p->parent!= nullptr)
		{
			steps.push(p);
			p = p->parent;
		}

		std::cout << "Expanding: " << std::endl;
		steps.top()->print_state();
		steps.pop();

		while (steps.size() > 1)
		{
			std::cout << " The best state to expand with ";
			steps.top()->print_expanding();
			steps.pop();
		}

		std::cout << "\nGoal has been reached!\n"
			<< "To solve this problem the search algorithm expanded a total of " << puzzle.expanded_nodes << ".\n"
			<< "The maximum number of nodes in the queue at any one time was " << puzzle.max_nodes << ".\n"
			<< "The depth of the goal node was " << puzzle.depth << ".";
	}



	return 0;
}


node* general_search(int queueing_function_choice, problem& cur)
{
	std::vector<node*> open;

	node* start = new node;
	for (size_t i = 0; i < cur.intial_state.size(); i++)
	{
		start->state.push_back(cur.intial_state[i]);
	}

	start->parent = nullptr;

	open.push_back(start);
	
	while (!open.empty())
	{
		node* p = new node;
		int smallest = smallestF(open);
		p = open[smallest];
		cur.depth = p->depth;

		if (cur.goal_test(p->state))
		{
			return p;
		}

		if (queueing_function_choice == 1)
		{
			uniform_cost(cur, p);
		}
		if (queueing_function_choice == 2)
		{
			AStar_Misplaced(cur, p);

		}
		if (queueing_function_choice == 3)
		{
			AStar_Manhattan(cur,p);
		}

		if (open.size() > cur.max_nodes)
		{
			cur.max_nodes = open.size();
		}

		open.erase(open.begin() + smallest);

		cur.found.push_back(p);

		for (size_t i = 0; i < p->followers.size(); i++)
		{
			open.push_back(p->followers[i]);
		}
		
		if (open.empty())
		{
			return nullptr;
		}

	}

}

void uniform_cost(problem& cur, node* expanding)
{
	//getting all possible nodes	
	expanding->followers.push_back(cur.move_right(expanding->state));
	expanding->followers.push_back(cur.move_down(expanding->state));
	expanding->followers.push_back(cur.move_left(expanding->state));
	expanding->followers.push_back(cur.move_up(expanding->state));

	//check that expansion in a direction is allowed
	for (size_t i = 0; i < expanding->followers.size(); i++)
	{
		//check valid direction
		if (expanding->followers[i] == nullptr)
		{
			expanding->followers.erase(expanding->followers.begin() + i);
			i--;
		}		
	}

	//check node isnt a repeat
	for (size_t i = 0; i < expanding->followers.size(); i++)
	{

		for (size_t t = 0; t < cur.found.size(); t++)
		{
			int match = 0;

			for (size_t n = 0; n < cur.found[t]->state.size(); n++)
			{
				if (cur.found[t]->state[n] == expanding->followers[i]->state[n])
				{
					match++;
				}
			}

			if (match == 9)
			{
				expanding->followers.erase(expanding->followers.begin() + i);
				i--;
				break;
			}
		}
	}

	//adding valid nodes
	for (size_t i = 0; i < expanding->followers.size(); i++)
	{
		expanding->followers[i]->parent = expanding;
		//one move -> g = g of prev +1
		expanding->followers[i]->g = expanding->g+1;

		//set h
		expanding->followers[i]->h = 0;

		//calculate f
		expanding->followers[i]->get_f();

		expanding->followers[i]->depth = expanding->depth + 1;

		cur.expanded_nodes++;
		cur.found.push_back(expanding->followers[i]);
	}

}

void AStar_Misplaced(problem& cur, node* expanding)
{
	//getting all possible nodes	
	expanding->followers.push_back(cur.move_right(expanding->state));
	expanding->followers.push_back(cur.move_down(expanding->state));
	expanding->followers.push_back(cur.move_left(expanding->state));
	expanding->followers.push_back(cur.move_up(expanding->state));

	//check that expansion in a direction is allowed
	for (size_t i = 0; i < expanding->followers.size(); i++)
	{
		//check valid direction
		if (expanding->followers[i] == nullptr)
		{
			expanding->followers.erase(expanding->followers.begin() + i);
			i--;
		}
	}

	//check node isnt a repeat
	for (size_t i = 0; i < expanding->followers.size(); i++)
	{

		for (size_t t = 0; t < cur.found.size(); t++)
		{
			int match = 0;

			for (size_t n = 0; n < cur.found[t]->state.size(); n++)
			{
				if (cur.found[t]->state[n] == expanding->followers[i]->state[n])
				{
					match++;
				}
			}

			if (match == 9)
			{
				expanding->followers.erase(expanding->followers.begin() + i);
				i--;
				break;
			}
		}
	}

	//adding valid nodes
	for (size_t i = 0; i < expanding->followers.size(); i++)
	{
		expanding->followers[i]->parent = expanding;
		//one move -> g = g of prev +1
		expanding->followers[i]->g = expanding->g + 1;

		//calculate h by counting wrong positions
		int summ = 0;

		for (size_t k = 0; k < expanding->followers[i]->state.size(); k++)
		{
			if (k != expanding->followers[i]->state[k] - 1)
			{
				summ++;
			}
		}

		expanding->followers[i]->h = summ;

		//calculate f
		expanding->followers[i]->get_f();

		expanding->followers[i]->depth = expanding->depth + 1;

		cur.expanded_nodes++;
		cur.found.push_back(expanding->followers[i]);
	}

}

void AStar_Manhattan(problem& cur, node* expanding)
{
	//getting all possible nodes	
	expanding->followers.push_back(cur.move_right(expanding->state));
	expanding->followers.push_back(cur.move_down(expanding->state));
	expanding->followers.push_back(cur.move_left(expanding->state));
	expanding->followers.push_back(cur.move_up(expanding->state));

	//check that expansion in a direction is allowed
	for (size_t i = 0; i < expanding->followers.size(); i++)
	{
		//check valid direction
		if (expanding->followers[i] == nullptr)
		{
			expanding->followers.erase(expanding->followers.begin() + i);
			i--;
		}
	}

	//check node isnt a repeat
	for (size_t i = 0; i < expanding->followers.size(); i++)
	{

		for (size_t t = 0; t < cur.found.size(); t++)
		{
			int match = 0;

			for (size_t n = 0; n < cur.found[t]->state.size(); n++)
			{
				if (cur.found[t]->state[n] == expanding->followers[i]->state[n])
				{
					match++;
				}
			}

			if (match == 9)
			{
				expanding->followers.erase(expanding->followers.begin() + i);
				i--;
				break;
			}
		}
	}

	//adding valid nodes
	for (size_t i = 0; i < expanding->followers.size(); i++)
	{
		expanding->followers[i]->parent = expanding;
		//one move -> g = g of prev +1
		expanding->followers[i]->g = expanding->g + 1;

		//calculate h by going through each position in state and finding distance from proper distance
		int summ = 0;

		for (size_t k = 0; k < expanding->followers[i]->state.size(); k++)
		{
			//the row and column of state[k]
			int rowpos = k / cur.n;
			int colpos = k % cur.n;

			//state[k]'s intended position
			int rowk = (expanding->followers[i]->state[k] - 1) / cur.n;
			int colk = (expanding->followers[i]->state[k] - 1) % cur.n;


			if (expanding->followers[i]->state[k] != 0)
			{
				summ = summ + abs(rowpos - rowk) + abs(colpos - colk);
			}
		}

		expanding->followers[i]->h = summ;

		//calculate f
		expanding->followers[i]->get_f();

		expanding->followers[i]->depth = expanding->depth + 1;

		cur.expanded_nodes++;
		cur.found.push_back(expanding->followers[i]);
	}
}

int smallestF(std::vector<node*> open)
{
	int min = open[0]->f;
	int pos = 0;

	for (size_t i = 0; i < open.size(); i++)
	{
		if (open[i]->f < min)
		{
			min = open[i]->f;
			pos = i;
		}
	}

	return pos;
}
