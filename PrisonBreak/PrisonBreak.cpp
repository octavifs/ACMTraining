// Octavi Font

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;


// Prison size.
// N = rows
// M = columns
int N, M;

// 3 boards. They hold information about accessible cells,
// checkpoints and switches respectivelly
// switches, power stations & starting cell are considered checkpoints
bool prisonBoard[15][15];
bool checkPointsBoard[15][15];
bool switchsBoard[15][15];

// 2 vars that hold the total number of checkpoints and switches
int checkPointsNum;
int switchsNum;

// Double dimension vector that holds the min distance between each point in the matrix (checkpoint or not)
vector<vector<int> > dist(225, vector<int>(225));

// Max weight of the path in the current iteration
int MAX_PATH_WEIGHT;


// This is used by the sortByWeight function. Establishes which checkPoint are the distances
// calculated from
int actualNode;

// Function used by sort(). Sorts checkpoints (ints) in a vector, based on the distance between them and
// the checkpoint defined by actualnode
// The sort is from max to min
bool sortByWeight(int i, int j)
{
	return dist[actualNode][i] > dist[actualNode][j];
}

// Breadth-First-Search algorithm. Modded to fit the problem data structure & some other performance tricks
void bfs(int root, int checkPointsNum)
{
	// We create a queue as long as the max number of nodes (cells)
	vector<int> queue(225);
	// We use this var to iterate the queue
	int k = 0;
	// We add the node to the queue
	queue[k++] = root;
	// We set the distance with itself to 0
	dist[root][root] = 0;
	// Since we only use this function for checkPoints, we add 1 to the counter
	int visitedCheckPoints = 1;

	// For all the elements in the queue
	for (int i = 0; i < k; ++i)
	{
        // We recall a node from the queue
        int vertex = queue[i];
        // And we check the distance againts their neighbour nodes
        // Which are placed up, down, right and left
		for (int j = -1; j < 2; j += 2)
		{
            // We check Y-Axis nodes. We add or substract 15 to the vertex ID
            int nVertex = vertex;
            nVertex += j * 15;
            // Now we check that the vertex exists, is not a Laser and hasn't been accessed before (dist is set to -1 by default)
            if (nVertex >= 0 && nVertex < (N*15) && prisonBoard[nVertex/15][nVertex%15] && dist[root][nVertex] < 0)
            {
            	// We update the distance from the root to this next vertex, which is, incidentally
            	// the same distance between the next vertex and the root (this speeds up the algorithm on the long run)
            	dist[root][nVertex] = dist[root][vertex] + 1;
            	//dist[nVertex][root] = dist[vertex][root] + 1;

            	// We add the new vertex to the queue
            	queue[k++] = nVertex;

            	// If the vertex is a checkPoint, we increase its counter
            	if (checkPointsBoard[nVertex/15][nVertex%15])
            	{
            		visitedCheckPoints++;
            		// If all the checkpoints have been visited, we can stop the function
            		if(visitedCheckPoints >= checkPointsNum) return;
            	}
            }

            // We repeath the same steps for the X-axis
            nVertex = vertex;
            nVertex += j;
            int diff = (nVertex % 15) - (vertex % 15);
            if (diff < 0) diff = -diff;
            if (diff == 1 && prisonBoard[nVertex/15][nVertex%15] && dist[root][nVertex] < 0)
            {
            	dist[root][nVertex] = dist[root][vertex] + 1;
            	//dist[nVertex][root] = dist[vertex][root] + 1;

            	queue[k++] = nVertex;

            	if (checkPointsBoard[nVertex/15][nVertex%15])
            	{
            		visitedCheckPoints++;
            		if(visitedCheckPoints >= checkPointsNum) return;
            	}
            }
		}
	}
}

// Battery minimizer algorithm. It's a variant of a Depth-First-Search
// Calculates the least weight path wihout recharging in a depth-first-search approach
// (first calculate a solution, then others. If they are not good enough, discard them).
void battery_minimizer(int vertex, int pathWeight, int maxPathWeight, vector<int> unvisitedCheckPoints, int visitedSwitchs)
{	
	// If we have visited all the switchs, end algorithm run
	if (visitedSwitchs >= switchsNum)
	{
		// If maxPathWeight of the run is less than MAX_PATH_WEIGHT, save new maxPathWeight
		if (maxPathWeight < MAX_PATH_WEIGHT)
		{
			MAX_PATH_WEIGHT = maxPathWeight;
		}
		return;
	}

	// First we sort the unVisitedCheckPoints vector. Last elements are nearest the vertex
	// Remember that, to use this, we needed to set up the global variable actualNode accordingly
	actualNode = vertex;
	sort(unvisitedCheckPoints.begin(), unvisitedCheckPoints.end(), sortByWeight);
	// We erase the last element, which is the current node (variable vertex), with weight 0
	unvisitedCheckPoints.pop_back();
	
	// We prepare a nextPathWeight variable and a counter
	int nextPathWeight;
	int i = 1;

	// While the counter is smaller than the number of checkpoints, and for a max of 15 checkpoints check
	// Here, we can make the max number of checkpoints to check smaller, reducing the span of the algorithm
	// but the solution might be wrong of the number of too small. I think that a number of 5 or so should be safe enough
	while( i <= unvisitedCheckPoints.size() && i < 6)
	{	// A variable to check whether we are checking a switch or not
		bool isSwitch = false;
		// We access a node from the vector
		int nextCheckPoint = unvisitedCheckPoints[unvisitedCheckPoints.size() - i];
		// The new path weight is the sum of the previous one + the dist between vertex and this nextCheckPoint
		nextPathWeight = pathWeight + dist[vertex][nextCheckPoint];
		// If the new path weight might be a better solution that what we already have
		if (nextPathWeight < MAX_PATH_WEIGHT)
		{
			// Check if we are at a switch
			isSwitch = switchsBoard[nextCheckPoint/15][nextCheckPoint%15];

			// This means we are at a energy pool 
			if (!isSwitch)
			{
				// We make recursive calls to the algorithm with the new pathweights, or maxPathWeights if they have changed
				if(nextPathWeight > maxPathWeight)
				{
					battery_minimizer(nextCheckPoint, 0, nextPathWeight, unvisitedCheckPoints, visitedSwitchs);
				}
				else
				{
					battery_minimizer(nextCheckPoint, 0, maxPathWeight, unvisitedCheckPoints, visitedSwitchs);
				}
			}
			// This means we are at a switch
			else
			{	// We make recursive calls to the algorithm with the new pathweights, or maxPathWeights if they have changed
				if(nextPathWeight > maxPathWeight)
				{
					battery_minimizer(nextCheckPoint, nextPathWeight, nextPathWeight, unvisitedCheckPoints, visitedSwitchs+1);
				}
				else
				{
					battery_minimizer(nextCheckPoint, nextPathWeight, maxPathWeight, unvisitedCheckPoints, visitedSwitchs+1);
				}
			}
		}
		i++;
	}

}

int main()
{
	// Variables to hold actual checkPoint and startPoint
	int checkPoint;
	int startPoint;

	// We save board size
	cin >> N >> M;
	// If its not 0
	while ( N && M)
	{
		// Reset max path weight to a really big number
		MAX_PATH_WEIGHT = 10000000;
		// Reset checkPoints vector
		vector<int> checkPoints;
		// Reset checkPointsNum
		checkPointsNum = 0;
		// Reset switchsNum
		switchsNum = 0;
		// Reset dist vector to -1
		for (int i = 0; i < 225; ++i)
			for (int j = 0; j < 225; ++j)
				dist[i][j] = -1;

		// Reset boards
		for (int i = 0; i < 15; ++i)
		{
			for (int j = 0; j < 15; ++j)
			{
				prisonBoard[i][j] = false;
				checkPointsBoard[i][j] = false;
				switchsBoard[i][j] = false;
			}
		}

		char cell;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				// We save the board input
				cin >> cell;
                
				if (cell != 'D')
				{
					prisonBoard[i][j] = true;
					// The checkPoint ID is in absolute numbers, that is, as if we were holding all the info in a 1D array
					checkPoint = i*15 + j;
					// If the cell is not empty, then it's a checkpoint
					if (cell != 'S')
                    {
                        checkPointsBoard[i][j] = true;
                        checkPoints.push_back(checkPoint);
                        checkPointsNum++;
                    }
                    // If it has an F, then it's the startPoint
					if (cell == 'F') startPoint = checkPoint;
					// IF it has an Y, then it's a switch
					if (cell == 'Y')
					{
						switchsNum++;
						switchsBoard[i][j] = true;
					}
				}
			}
		}

		// Compute distance table for all vertexs
		for (int i = 0; i < checkPointsNum; ++i)
		{
			bfs(checkPoints[i], checkPointsNum);
		}

		// Check if there is an unreacheable switch
		bool unreacheable = false;
		for (int i = 0; i < checkPointsNum; ++i)
		{
			if(dist[startPoint][checkPoints[i]] < 0 && switchsBoard[checkPoints[i]/15][checkPoints[i]%15])
			{
				unreacheable = true;
				cout << -1 << endl;
				break;
			}
		}

		// Compute most battery efficient path (if solution is possible). Output min battery size
		if (!unreacheable)
		{
			actualNode = startPoint;
			sort(checkPoints.begin(), checkPoints.end(), sortByWeight);
			// If there is any unreacheable power station, we erase it from the checkpoint list
			while(dist[startPoint][checkPoints.back()] < 0)
				checkPoints.pop_back();

			battery_minimizer(startPoint, 0, 0, checkPoints, 0);
			cout << MAX_PATH_WEIGHT << endl;
		}

		// We record input for next test
		cin >> N >> M;
	}
}
