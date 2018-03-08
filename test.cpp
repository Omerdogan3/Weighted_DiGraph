#include <iostream>
#include <string>
#include "Graph.h"

using namespace std;


void print_help();


int main()
{
    Graph graph(100);
    Graph::Vertex vertex;
    string v1, v2;
    int wt;
    char cmd;

    print_help();

    while (true)
    {
        cout << endl;
        graph.showGraph();

        cout << endl
             << "Enter command:" << endl;
        cin >> cmd;
        cout << endl;

        switch (cmd)
        {
            case '+':
                cin >> v1;
                graph.insertVertex(v1);
                cout << "Inserting vertex" << endl;
                break;

            case '=':
                cin >> v1 >> v2 >> wt;
                graph.insertEdge(v1, v2, wt);
                break;

            case '-':
                cin >> v1;
                if (graph.removeVertex(v1))
                    cout << "Vertex removed" << endl;
                else
                    cout << "Vertex not found" << endl;
                break;

            case '#':
                cin >> v1 >> v2;
                if (graph.removeEdge(v1, v2))
                    cout << "Edge removed" << endl;
                else
                    cout << "Edge not found" << endl;
                break;

            case '?':
                cin >> v1;
                if (graph.searchVertex(v1, vertex))
                    cout << "Vertex found" << endl;
                else
                    cout << "Vertex not found" << endl;
                break;

            case '!':
                cin >> v1 >> v2;
                if (graph.searchEdge(v1, v2, wt))
                    cout << "Weight = " << wt << endl;
                else
                    cout << "Edge not found" << endl;
                break;

            case 'c':
                graph.clear();
                break;

            case 'e':
                if (graph.empty())
                    cout << "Graph empty" << endl;
                else
                    cout << "Graph not empty" << endl;
                break;

            case 'f':
                if (graph.full())
                    cout << "Graph full" << endl;
                else
                    cout << "Graph not full" << endl;
                break;

            case 'b':
                cin >> v1 >> v2;
                cout << "Performing BFS:" << endl;
                graph.bfs(v1, v2);
                break;

            case 's':
                cin >> v1;
                cout << "Shortest paths from source:" << endl;
                graph.shortestPaths(v1);
                break;

            case 'h':
                print_help();
                break;

            case 'q':
                return 0;

            default:
                cout << "Invalid command" << endl;
        }
    }

    return 0;
}


void print_help()
{
    cout << endl
         << "+ v :          insert vertex\n"
         << "= v1 v2 wt :   insert edge\n"
         << "- v :          remove vertex\n"
         << "# v1 v2 :      remove edge\n"
         << "? v :          search vertex\n"
         << "! v1 v2 :      search edge\n"
         << "c :            clear graph\n"
         << "e :            empty?\n"
         << "f :            full?\n"
         << "b v1 v2 :      perform bfs\n"
         << "s v :          shortest paths\n"
         << endl;
}