


#include <iostream>
#include <queue>
#include "Graph.h"

using namespace std;



Graph::Graph(int newMaxSize)
{
    size = 0;
    maxSize = newMaxSize;
    vertexList = new Vertex [maxSize];
}


Graph::Graph(const Graph& other)
{
    *this = other;
}


Graph& Graph::operator=(const Graph& other)
{
    if (this == &other)
        return *this;

    if (!empty())
        delete[] vertexList;

    size = other.size;
    maxSize = other.maxSize;
    vertexList = new Vertex [maxSize];

    for (int i = 0; i < size; i++)
        vertexList[i] = other.vertexList[i];

    return *this;
}


Graph::~Graph()
{
    delete[] vertexList;
}


void Graph::insertVertex(const string& v)
{
    if (full())
        return;

    Vertex newVertex;
    newVertex.setLabel(v);

    for (int i = 0; i < size; i++)
    {
        if (newVertex.getLabel() == vertexList[i].getLabel())
        {
            vertexList[i] = newVertex;
            return;
        }
    }

    vertexList[size] = newVertex;
    size++;
}


void Graph::insertEdge(const string& v1, const string& v2, const int wt)
{
    int idx = getIndex(v1);
    if (idx == -1) return;

    Vertex vtx;

    if (searchVertex(v2, vtx))
    {
        for (unsigned i = 0;
             i < vertexList[idx].edges.size();
             i++)
        {
            if (v2 == vertexList[idx].edges[i].second.getLabel())
            {
                vertexList[idx].edges[i].first = wt;
                return;
            }
        }

        vertexList[idx].edges.push_back(make_pair(wt, vtx));
    }
}


bool Graph::searchVertex(const string& v, Vertex& returnVertex) const
{
    for (int i = 0; i < size; i++)
    {
        if (v == vertexList[i].getLabel())
        {
            returnVertex = vertexList[i];
            return true;
        }
    }

    return false;
}


bool Graph::searchEdge(const string& v1, const string& v2, int& wt) const
{
    int idx1 = getIndex(v1),
        idx2 = getIndex(v2);

    if (idx1 == -1 || idx2 == -1)
        return false;

    for (auto i : vertexList[idx1].edges)
    {
        if (v2 == i.second.getLabel())
        {
            wt = i.first;
            return true;
        }
    }

    return false;
}


bool Graph::removeVertex(const string& v)
{
    int idx = getIndex(v);

    if (idx == -1)
        return false;

    for (int i = idx; i < size-1; i++)
        vertexList[i] = vertexList[i+1];

    size--;

    for (int i = 0; i < size; i++)
    {
        for (unsigned j = 0;
             j < vertexList[i].edges.size();
             j++)
        {
            if (v == vertexList[i].edges[j].second.getLabel())
            {
                swap(vertexList[i].edges[0],
                     vertexList[i].edges[j]);

                vertexList[i].edges.erase(vertexList[i].edges.begin());
            }
        }
    }

    return true;
}


bool Graph::removeEdge(const string& v1, const string& v2)
{
    int idx1 = getIndex(v1),
        idx2 = getIndex(v2);

    if (idx1 == -1 || idx2 == -1)
        return false;

    vertexList[idx1].edges.erase(vertexList[idx1].edges.begin()
                                    + idx2);
    return true;
}


void Graph::clear()
{
    delete[] vertexList;
    vertexList = new Vertex [maxSize];
    size = 0;
}


bool Graph::empty() const
{
    return (size == 0);
}


bool Graph::full() const
{
    return (size == maxSize);
}


void Graph::showGraph() const
{
    if (empty())
    {
        cout << "Empty Graph" << endl;
        return;
    }


    cout << "Vertex list:" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << '\t' << i << '\t'
             << vertexList[i].getLabel() << endl;
    }
    cout << endl;

    cout << "Adjacency list:" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << '\t' << vertexList[i].getLabel();

        for (auto j : vertexList[i].edges)
        {
            cout << " --> [" << j.second.getLabel()
                 << ", " << j.first << ']';
        }
        cout << endl;
    }
}


void Graph::bfs(const string& src, const string& dest) const
{
    int src_idx = getIndex(src),
        dest_idx = getIndex(dest);

    if (src_idx == -1 ||
        dest_idx == -1)
        return;

    queue<int> q;
    vector<bool> visited(size, false);

    q.push(src_idx);
    visited[src_idx] = true;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        cout << ' ' << vertexList[u].getLabel() << endl;

        if (u == dest_idx)
            return;

        for (auto i : vertexList[u].edges)
        {
            int v = getIndex(i.second.getLabel());

            if (!visited[v])
            {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}


void Graph::shortestPaths(const string& src) const
{
    priority_queue< pair<int,int>,
                    vector<pair<int,int> >,
                    greater<pair<int,int> > > pq;

    vector<int> dist(size, INF);
    vector<bool> visited(size, false);

    int src_idx = getIndex(src);
    if (src_idx == -1) return;

    dist[src_idx] = 0;
    visited[src_idx] = true;
    pq.push(make_pair(0, src_idx));

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        for (auto i : vertexList[u].edges)
        {
            string s = i.second.getLabel();
            int v = getIndex(s);
            int wt = i.first;

            if ((!visited[v]) &&
                (dist[v] > dist[u] + wt))
            {
                dist[v] = dist[u] + wt;
                visited[v] = true;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        cout << '\t' << vertexList[i].getLabel();
        if (dist[i] == INF)
            cout << '\t' << "INF" << endl;
        else
            cout << '\t' << dist[i] << endl;
    }
    cout << endl;
}


int Graph::getIndex(const string& v) const
{
    for (int i = 0; i < size; i++)
        if (v == vertexList[i].getLabel())
            return i;

    return -1;
}