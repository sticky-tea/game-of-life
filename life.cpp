#include "life.hpp"

void life::firstGeneration(int nfield[M][M])
{
	for(int i = 0; i < M; i++)
		for(int j = 0; j < M; j++)
			field[i][j] = nfield[i][j];
}

int life::countAround(int x, int y)
{
	int count = 0;
	
	if(x-1 != -1 && field[x-1][y] == 1)
		count++;
	if(x-1 != -1 && y-1 != -1 && field[x-1][y-1] == 1)
		count++;
	if(y-1 != -1 && field[x][y-1] == 1)
		count++;
	if(x+1 != -1 && y-1 != -1 && field[x+1][y-1] == 1)
		count++;
	if(x+1 != -1 && field[x+1][y] == 1)
		count++;
	if(x+1 != -1 && y+1 != -1 && field[x+1][y+1] == 1)
		count++;
	if(y+1 != -1 && field[x][y+1] == 1)
		count++;
	if(x-1 != -1 && y+1 != -1 && field[x-1][y+1] == 1)
		count++;
		
	return count;
}

void life::nextGeneration()
{
	int tf[M][M];
	
	for(int i = 0; i < M; i++)
		for(int j = 0; j < M; j++)
			tf[i][j] = 0;
	
	int c = 0;
	
	for(int i = 0; i < M; i++)
	{
		for(int j = 0; j < M; j++)
		{
			c = countAround(i, j);
			
			if((c == 3 || c == 2) && field[i][j] == 1)
				tf[i][j] = 1;
			else if(c == 3)
				tf[i][j] = 1;
			else
				tf[i][j] = 0;
		}
	}
	
	for(int i = 0; i < M; i++)
		for(int j = 0; j < M; j++)
			field[i][j] = tf[i][j];
}