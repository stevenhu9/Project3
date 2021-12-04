//
// Created by Alexa Cole on 11/18/21.
//
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<map>
#include<iterator>
#include <climits>

#ifndef ADJACENCYLIST_GRAPH_H
#define ADJACENCYLIST_GRAPH_H

//Using the Graph API seen within the Graphs Implementation and Traversal as a template


//MAKE A DIRECTED GRAPH
//taken from StepIk 8.2.2 in order to be used for implemented Dijkstra's SP algorithm

//Making the edges directed with weight (GPS's employ a similar method)
struct Edge {
    int src, dest, weight;
    Edge(int _src, int _dest, int _weight) {src = _src; dest = _dest; weight = _weight;}
};

class Graph {
private:
    //Graph Data Structure
    std::map<int, std::vector<std::pair<int, int>>> graph;

public:
    Graph();
    Graph(int V); //Creates graph with v vertices
    int V(); //Returns number of vertices
    int E(); //Returns number of edges

    //will be adjusting methods to fit the data we are utilizing
    //all code taken from StePik 7.1.2 to be modified
    void insertEdge(int from, int to, int weight) {
        graph[from].push_back(std::make_pair(to, weight));
        if(graph.find(to)==graph.end())
            graph[to] = {};
    }
    bool isEdge(int from, int to) {
        std::vector<std::pair<int, int>> v = graph[from];
        for(std::pair<int, int> p : v) {
            if(p.first == to && p.second != 0)
                return true;
        }
        return false;
    }
    int getWeight(int from, int to) {
        std::vector<std::pair<int, int>> v = graph[from];
        for(std::pair<int, int> p : v) {
            if (p.first == to && p.second != 0)
                return p.second;
        }
    }
    std::vector<int> getAdjacent(int vertex) {
        std::vector<int> adj;
        std::vector<std::pair<int, int>> v = graph[vertex];
        for(std::pair<int, int> p : v) {
            adj.push_back(p.first);
        }
        return adj;
    }
    void printGraph() {
        for (std::map<int, std::vector<std::pair<int, int>>>::iterator it = graph.begin(); it != graph.end(); ++it) {
            std::cout << it->first;
            std::vector<std::pair<int, int>> v = it->second;
            for (std::pair<int, int> p : v)
                std::cout << " " << p.first;
            std::cout << std::endl;
        }
    }
};

class Path {
public:
    //find all paths from g
    Path(Graph g, int s);

    //is there a path from s to v
    bool hasPathTo(int s);

    //path from s to v
    std::vector<int> pathTo(int s);
};

#endif //ADJACENCYLIST_GRAPH_H
