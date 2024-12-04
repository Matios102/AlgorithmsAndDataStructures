#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#define INF 100000 

using namespace std;

// Your task is to implement Dijkstra's algorithm which finds the shortest path in a weighted directed graph with n vertices and m edges.

// Input
// The first line contains integer z (1 <= z <= 2*10^9) - the number of data sets.
// Each data set is as follows:
// The first line contains number n (1 <= n <= 1000) of vertices and number m (1 <= m <= 1000000) of edges of the input graph. 
// Each of the remaining lines contains three numbers u v and w representing an oriented edge of weight w (1 <= w <= 1000) oriented from u to v.

// Output
// The weight of the shortest path from vertex 0 to vertex n - 1 (-1 in the case when such a path does not exist).

class Edge
{
public:
    int weight;
    int neighbor;
    Edge* next;
    
    Edge(int _weight, int _neighbor)
    {
        this->weight = _weight;
        this->neighbor = _neighbor;
        this->next = nullptr;
    }
};

class Vertex
{
public:
    bool isInS;
    int id;
    int dist;
    Edge* first_edge;

    Vertex()
    {
        isInS = false;
        dist = INF;
        first_edge = nullptr;
    }

    void addEdge(int weight, int destination)
    {
        if(first_edge == nullptr)
            first_edge = new Edge(weight, destination);

        else
        {
            Edge* current = first_edge;
            while(current->next != nullptr)
                current = current->next;

            current->next = new Edge(weight, destination);
        }
        
    }
    
};

class WeightedGraph
{
public:
    vector<Vertex> vertices;
    int order;

    WeightedGraph(int n)
    {
        order = n;
        vertices = vector<Vertex>(n);
        for(int i = 0; i < n; i++)
            vertices[i].id = i;
    }

    void addEdge(int u, int v, int w)
    {
        vertices[u].addEdge(w, v);
    }
    
    bool isEdge(int id_from, int id_to)
    {
        if(vertices[id_from].first_edge == nullptr)
            return false;

        else
        {
            Edge* current = vertices[id_from].first_edge;

            while(current != nullptr)
            {
                if(current->neighbor == id_to)
                    return true;

                current = current->next;
            }
        }
        return false;
    }

    int dijkstra()
    {
        vertices[0].dist = 0;
        vertices[0].isInS = true;
        Vertex current = vertices[0];

        while(1)
        {
            Edge* edge = current.first_edge;
            while(edge != NULL)
            {
                if(vertices[edge->neighbor].dist > current.dist + edge->weight)
                    vertices[edge->neighbor].dist = current.dist + edge->weight;

                edge = edge->next;  
            }

            int smallest_id = 0;
            int smallest_dist = INF;
            bool everyInS = true;

            for(int i = 1; i < order; i++)
            {

                if(vertices[i].isInS == false)
                    everyInS = false;

                
                if(vertices[i].dist <  smallest_dist && vertices[i].isInS == false)
                {
                    smallest_id = i;
                    smallest_dist = vertices[i].dist;
                }
            }

            if(everyInS)
                break;

            if(smallest_dist == INF)
                break;

            vertices[smallest_id].isInS = true;
            current = vertices[smallest_id];
            
        }
            if(vertices[order -1].dist == INF)
                return -1;
            
            else
                return vertices[order -1].dist;
        }
};


int main()
{
    int z, n, m;

    cin >> z;

    while (z)
    {
        cin >> n >> m;
        WeightedGraph graph(n);

        while (m)
        {
            int u, v, w;
            cin >> u >> v >> w;

            graph.addEdge(u, v, w);
            m--;
        }

        cout << graph.dijkstra() << endl;
        z--;
    }

    return 0;
}
