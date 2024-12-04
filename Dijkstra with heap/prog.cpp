#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#define INF 100000 

// Dijkstra algorithm with heap

using namespace std;

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
    int dist;
    Edge* first_edge;
    int heap_position;

    Vertex(int i)
    {
        heap_position = i;
        isInS = false;
        dist = INF;
        first_edge = nullptr;
    }

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

    bool operator<(Vertex& v) 
    {
        if (v.isInS == true)
            return true;
        
        if (this->isInS == true)
            return false;

        if (this->dist < v.dist)
            return true;

        return false;
    }
};


class WeightedGraph
{
public:
    vector<Vertex> vertices;
    vector<int> heap;
    int order;

    WeightedGraph(int n)
    {
        vertices = vector<Vertex>();
        heap = vector<int>(n);
        for(int i = 0; i < n; i++)
        {
            vertices.push_back(Vertex(i));
            heap[i] = i;
        }
        order = n;
    }

    void addEdge(int u, int v, int w)
    {
        vertices[u].addEdge(w, v);
    }

    void upHeap(int idx)
    {
       if (idx == 0)
        {
            return;
        }

        int parent = (idx - 1) / 2;

        if (vertices[heap[idx]] < vertices[heap[parent]])
        {
            std::swap(heap[idx], heap[parent]);
            std::swap(vertices[heap[idx]].heap_position, vertices[heap[parent]].heap_position);
            upHeap(parent);
        }
    }
    
    void downHeap(int idx)
    {
        if (idx == order-1)
        {
            return;
        }

        int left = idx * 2 + 1;
        int right = idx * 2 + 2;
        int swap = idx;

        if (right < order)
        {
            if (vertices[heap[right]] < vertices[heap[swap]])
            {
                swap = right;
            }
        }
        if (left < order)
        {
            if (vertices[heap[left]] < vertices[heap[swap]])
            {
                swap = left;
            }
        }

        if (swap != idx)
        {
            std::swap(heap[idx], heap[swap]);
            std::swap(vertices[heap[idx]].heap_position, vertices[heap[swap]].heap_position);
            downHeap(swap);
        }
    }

    int dijkstra()
    {
        vertices[0].dist = 0;
        vertices[0].isInS = true;
        Vertex current = vertices[0];
        downHeap(0);

        while(1)
        {
            Edge* edge = current.first_edge;
            
            while(edge != nullptr)
            {
                if(vertices[edge->neighbor].dist > current.dist + edge->weight && !vertices[edge->neighbor].isInS)
                {
                    vertices[edge->neighbor].dist = current.dist + edge->weight;
                    upHeap(vertices[edge->neighbor].heap_position);
                }
                edge = edge->next;
            }

            if(vertices[heap[0]].isInS)
                break;
            
            vertices[heap[0]].isInS = true;
            current = vertices[heap[0]];
            downHeap(0);
        }

        if(vertices[order - 1].dist == INF)
            return -1;

        else
            return vertices[order - 1].dist;
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
