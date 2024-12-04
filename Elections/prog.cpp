#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

// Program that will count the number of seats won by each party in the elections. 
// We have n parties and s seats, the parties are numbered with consecutive numbers in [n] (starting from 1). 
// The seats are distributed using the d'Hondt method.
// The method works as follows. After all the votes have been counted, successive quotients are calculated for each party. 
// The party with the largest quotient wins one seat, and its quotient is recalculated. 
// This is repeated until the required number of seats is filled. The formula for the quotient is
// quotient = votes/(seats + 1)
// where:
// • votes is the total number of votes that party received,
// • seats is the number of seats that party has been allocated so far, initially O for all parties.
// In the case of a tie, the seat goes to the party with the smallest number.

// Input
// The first line contains integer z (1 <= z <= 2*10^9) - the number of data sets. 
// Each data set is as follows:
// The first line contains number n - the number of parties and number s - the number of seats (1 <= n, s <= 4000000).
// The next line contains n integers with the number of votes received by subsequent parties, separated by a space.


// Output
// The total number of seats obtained by each party, separated by a space.

class Party
{
	public:
	
	int number;
	int currentVotes;
	int seats;
    int initialVotes;
	
	Party(int num, int v, int s, int i)
	{
		number = num;
		currentVotes = v;
		seats = s;
        initialVotes = i;
	}
	
	bool operator>(const Party &p) const;
    friend ostream& operator<<(ostream& out, const Party &p)
    {
        out << "( " << p.number << " " << p.currentVotes << " " << p.seats << " )";
        return out;
    }
};

bool Party::operator>(const Party &p) const
{
    if(p.number == 0)
        return true;


	else if(initialVotes * (p.seats + 1) > p.initialVotes * (seats + 1))
    {
        return true;
    }
		
	
	else if(p.initialVotes * (seats + 1) > initialVotes * (p.seats + 1))
	{
        return false;
    }
	
	else if(number < p.number)
    {
        return true;
    }
		
	
	else
    {
         return false;
    }
		
}

class Heap
{
	public:
	vector<Party> Parties;
	int size;
	void add(Party p);
	void downHeap(int index);
	Heap();
};

Heap::Heap()
{
	size = 0;
	Parties.push_back(Party(-2,-2,-2, -2));
}

void Heap::add(Party p)
{
	size++;
	int i = size;
	Parties.push_back(p);
	if(Parties[i] > Parties[i/2])
	{
		int actual = i;
       
		while(1)
		{   
			if(actual == 1)
				break;
			
			if(Parties[actual/2] > Parties[actual])
				break;
			
			Party temp = Party(Parties[actual].number, Parties[actual].currentVotes, Parties[actual].seats, Parties[actual].initialVotes);
			Parties[actual] = Parties[actual/2];
			Parties[actual/2] = temp;
			actual = actual/2;
		}
	}
}

void Heap::downHeap(int index)
{
    int swap = 0;
	int actual = index;
	while(1)
	{
		if(2* actual > size)
			break;
		
		if(Parties[actual] > Parties[2*actual] && Parties[actual] > Parties[2*actual + 1])
			break;
		
		swap = 0;
		
            
		if(Parties[2* actual] > Parties[2*actual + 1])
			swap = 2*actual;
		else
			swap = 2*actual + 1;
		
		Party temp = Party(Parties[actual].number, Parties[actual].currentVotes, Parties[actual].seats, Parties[actual].initialVotes);
		Parties[actual] = Parties[swap];
		Parties[swap] = temp;
		actual = swap;
	}
}


int main()
{
	int z, n, s;
	
	cin >> z;
	
	while(z)
	{
        Heap PartyHeap;
        vector<int> seats;
		cin >> n >> s;
		for(int i = 0; i < n; i++)
		{
			int p;
			cin >> p;
			PartyHeap.add(Party(i + 1, p, 0, p));
            seats.push_back(0);
		}

		seats.push_back(0);
        
		while(s > 0)
		{
			PartyHeap.Parties[1].seats++;
            seats[PartyHeap.Parties[1].number] += 1;
			PartyHeap.Parties[1].currentVotes = (PartyHeap.Parties[1].initialVotes/(PartyHeap.Parties[1].seats + 1));
            PartyHeap.downHeap(1);
			s--;
		}

		for(int i = 1; i <= PartyHeap.size; i++)
			cout << seats[i] << " ";
		
		cout << endl;
        z--;
	}
	return 0;
}