#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Given a sequence of n boxes build the highest possible tower from this sequence
// obeying the rule that a box b may be put on the top of a box a only if b follows a in the
// sequence and none of the dimensions of the base of the box b exceeds the corresponding
// dimension of the box a. Note that there are two ways of putting each box (assume that
// boxes cannot be turned upside down or put on the side).

// Input
// The first line contains an integer z (1 < z < 2-10) - the number of data sets.
// Each data set is as follows:
// The first line contains a number n (1 <= n <= 4000000) - the number of the boxes in the sequence.
// Each of the next n lines contains 3 integers, the first two denoting the sizes of the base and the third the high of each box, separated by a space.

// Output
// The highest possible height of the tower that can be built from the given sequence of boxes.

class Box
{
public:
	Box(int _x, int _y, int _h)
	{
		x = _x;
		y = _y;
		h = _h;
	}
	int x;
	int y;
	int h;

	bool operator<=(const Box &b)
	{
		if (x <= b.x && y <= b.y)
			return true;
		if (x <= b.y && y <= b.x)
			return true;
		return false;
	}

	friend std::ostream &operator<<(std::ostream &stream, const Box &b);
};

std::ostream &operator<<(std::ostream &stream, const Box &b)
{
	stream << b.x << "/" << b.y << "/" << b.h << "\n";
	return stream;
}

int getHighestTower(vector<Box> *boxes, vector<int> *highestTower)
{
	int n = (boxes->size());

	// vector pointing to the highest tower that can be built from the sequence of boxes
	highestTower->push_back((*boxes)[0].h);
	for (int i = 1; i < boxes->size(); i++)
	{
		int max = (*boxes)[i].h;
		for (int j = i - 1; j >= 0; j--)
		{
			// if the box i can be put on the top of the box j and the height of the tower built from the box j is higher than the current max
			if ((*boxes)[i] <= (*boxes)[j] && (*highestTower)[j] + (*boxes)[i].h > max)
				max = (*highestTower)[j] + (*boxes)[i].h;
		}

		highestTower->push_back(max);
	}

	int res = 0;
	for (int i = 0; i < highestTower->size(); i++)
	{
		if ((*highestTower)[i] > res)
			res = (*highestTower)[i];
	}

	return res;
}

void printBoxes(vector<Box> *boxes)
{
	cout << "\nBoxes:\n";
	for (int i = 0; i < boxes->size(); i++)
	{
		cout << (*boxes)[i];
	}
}

int main()
{
	vector<Box> boxes;
	vector<int> highestTower;

	int z, n;
	cin >> z;
	while (z)
	{
		boxes.clear();
		highestTower.clear();

		cin >> n;
		for (int i = 0; i < n; i++)
		{
			int x, y, h;
			cin >> x >> y >> h;
			boxes.push_back(Box(x, y, h));
		}
		cout << getHighestTower(&boxes, &highestTower) << "\n";
		z--;
	}
	return 1;
}