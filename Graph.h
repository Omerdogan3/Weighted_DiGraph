


#ifndef GRAPH_H
#define GRAPH_H


#include <utility>
#include <climits>
#include <string>
#include <vector>



class Graph
{
    static const int DEFAULT_MAX_SIZE = 10;
    static const int INF = INT_MAX;

    public:
        class Vertex
        {
            public:
                void setLabel(const std::string& newLabel)
                    { label = newLabel; }
                std::string getLabel() const
                    { return label; }

                typedef std::pair<int,Vertex> vPair;
                std::vector<vPair> edges;

            private:
                std::string label;
        };

        Graph(int newMaxSize = DEFAULT_MAX_SIZE);
        Graph(const Graph& other);
        Graph& operator=(const Graph& other);
        ~Graph();

        void insertVertex(const std::string& v);
        void insertEdge(const std::string& v1, const std::string& v2,
                        const int wt);
        bool searchVertex(const std::string& v,
                          Vertex& returnVertex) const;
        bool searchEdge(const std::string& v1, const std::string& v2,
                        int& wt) const;
        bool removeVertex(const std::string& v1);
        bool removeEdge(const std::string& v1, const std::string& v2);

        void clear();

        bool empty() const;
        bool full() const;

        void showGraph() const;

        void bfs(const std::string& src,
                 const std::string& dest) const;
        void shortestPaths(const std::string& src) const;

    private:
        int getIndex(const std::string& v) const;

        Vertex* vertexList;
        int size,
            maxSize;
};


#endif // GRAPH_H