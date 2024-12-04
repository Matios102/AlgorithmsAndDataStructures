#include <iostream>
#include <vector>

using namespace std;

// Implement a data structure ds which maintains a set S of n integers and answers the queries whether S contains at least ki elements greater or equal to x.

// Input
// The first line contains integer z (1 <= z <= 2*10^9) - the number of data sets.
// Each data set is as follows:
// The first line contains the number n (1 <= n <= 10000) denoting the size of the set S and the number q of queries.
// The second line contains n elements of the set S, separated by space.
// Each of the next q lines contains two numbers k and x determining the subsequent queries.

// Output
// For each query k x you should output YES if the set S contains at least k elements
// greater or equal to x and NO otherwise.

class Heap
{
public:
  vector<int> nums;
  int size;
  int elements;
  void add(int num);
  Heap();
  int count(int index, int k, int x);
};

int Heap::count(int index, int k, int x)
{
    if (index > size)
        return 0;

    if (nums[index] >= x && elements < k)
    {
        elements++;
        return count(index * 2, k, x) + 1 + count(index * 2 + 1, k, x);
    } 
	else
	{
    	return 0;
    }
}


Heap::Heap()
{
	elements = 0;
    size = 0;
    nums.push_back(-10000);
}

void Heap::add(int num)
{
    size++;
    int i = size;
    nums.push_back(num);

    if (nums[i] > nums[i / 2])
    {
        int actual = i;

        while (1)
        {
            if (actual == 1)
                break;

            if (nums[actual / 2] > nums[actual])
                break;

            int temp = nums[actual];

            nums[actual] = nums[actual / 2];
            nums[actual / 2] = temp;
            actual = actual / 2;
        }
    }
}


class DS
{
public:
    Heap heap;
    DS(vector<int> &inval); //should work in time O(n)
    ~DS();
    bool compare(int k, int x); // should work in time O(k)
};

DS::DS(vector<int> &inval)
{
    for (int i = 0; i < inval.size(); i++)
    {
        heap.add(inval[i]);
    }
}

DS::~DS()
{
    // Destructor implementation (if needed)
}

bool DS::compare(int k, int x)
{
    heap.elements = 0;
	if(heap.count(1,k,x) >= k)
		return true;

	else
		return false;
}

int main()
{
    int z;
    cin >> z;
    while (z)
    {
        int n, q;
        vector<int> val;
        cin >> n >> q;
        for (int i = 1; i <= n; i++)
        {
            int x;
            cin >> x;
            val.push_back(x);
        }
        DS ds = DS(val);
        while (q)
        {
            int x, k;
            cin >> k >> x;
            if (ds.compare(k, x))
                cout << "YES\n";
            else
                cout << "NO\n";
            q--;
        }
        z--;
    }
}
