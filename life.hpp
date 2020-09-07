const int M = 50;

class life
{
private:
	int field[M][M];
	
	int countAround(int x, int y);
public:
	void firstGeneration(int nfield[M][M]);
	void nextGeneration();
	
	auto getField() {return this->field;};
};