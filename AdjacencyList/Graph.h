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
#include <queue>
#include <limits> //in order to set to infinity
#include <cmath>
#include <set>
#include <stack>
#include "City.h"

#ifndef ADJACENCYLIST_GRAPH_H
#define ADJACENCYLIST_GRAPH_H

//Using the Graph API seen within the Graphs Implementation and Traversal as a template


//MAKE A DIRECTED GRAPH
//taken from StepIk 8.2.2 in order to be used for implemented Dijkstra's SP algorithm

//Making the edges directed with weight (DISTANCE) (GPS's employ a similar method)
struct Edge {
    int src, dest, weight;
    Edge(int _src, int _dest, int _weight) {src = _src; dest = _dest; weight = _weight;}
};

class Graph {
private:
    //Graph Data Structure
    //std::map<std::string, std::vector<std::pair<double, std::string>>> graph;
    //std::map<std::string, int> indexes; //gives the indexes of each city as added to the graph

public:
    std::map<std::string, std::vector<std::pair<double, std::string>>> graph;
    std::map<std::string, int> indexes; //gives the indexes of each city as added to the graph

    Graph();
    Graph(std::vector<City> vec) { //Creates graph with v vertices
        for(int i = 0; i < vec.size(); i++) {
            indexes[vec.at(i).getName()] = i;
            for(int j = 0; j < vec.size(); j++) {
                if(j != i) {
                    //calculate distance
                    double x1 = vec.at(i).getCoordinates().second;
                    double y1 = vec.at(i).getCoordinates().first;

                    double x2 = vec.at(j).getCoordinates().second;
                    double y2 = vec.at(j).getCoordinates().first;

                    double x = std::pow(x2 - x1, 2);
                    double y = std::pow(y2 - y1, 2);

                    double dist = std::sqrt(x + y);

                    //add to adj list
                    if(std::abs(x2 - x1) <= 2 && std::abs(y2 - y1) <= 2)
                        insertEdge(vec.at(i), vec.at(j), dist);
                }
            }
        }
    }
    int V(); //Returns number of vertices
    int E(); //Returns number of edges

    //will be adjusting methods to fit the data we are utilizing
    //all code taken from StePik 7.1.2 to be modified
    void insertEdge(City from, City to, double weight) {
        graph[from.getName()].push_back(std::make_pair(weight, to.getName()));
        if(graph.find(to.getName())==graph.end())
            graph[to.getName()] = {};
    }
    /*bool isEdge(City from, City to) {
        std::vector<std::pair<City, double>> v = graph[from];
        for(std::pair<City, double> p : v) {
            if(p.first.getName() == to.getName() && p.second != 0)
                return true;
        }
        return false;
    }
    int getWeight(City from, City to) {
        std::vector<std::pair<City, double>> v = graph[from];
        for(std::pair<City, double> p : v) {
            if (p.first.getName() == to.getName() && p.second != 0)
                return p.second;
        }
    }*/

    /*std::vector<int> getAdjacent(int vertex) { ***FIX ME***
        std::vector<int> adj;
        std::vector<std::pair<int, int>> v = graph[vertex];
        for(std::pair<int, int> p : v) {
            adj.push_back(p.first);
        }
        return adj;
    }

    void printGraph() { ***FIX ME***
        for (std::map<int, std::vector<std::pair<int, int>>>::iterator it = graph.begin(); it != graph.end(); ++it) {
            std::cout << it->first;
            std::vector<std::pair<int, int>> v = it->second;
            for (std::pair<int, int> p : v)
                std::cout << " " << p.first;
            std::cout << std::endl;
        }
    }*/

    std::vector<std::string> ShortestPath(City src, City final, int numStops) {
        std::string c = src.getName();
        std::vector<std::string> path;
        std::set<std::string> stop;
        while(c != final.getName()) {
            path.push_back(c);
            stop.insert(c);
            std::vector<std::pair<double, std::string>> adj = graph[c];
            double minW = std::numeric_limits<double>::max();
            for(int i = 0; i < adj.size(); i++) {
                if(stop.count(adj.at(i).second) == 0 && adj.at(i).first < minW) {
                    minW = adj.at(i).first;
                    c = adj.at(i).second;
                }
            }
        }
        path.push_back(c);
        return path;
    }

    /*std::vector<std::string> dfs(City src, City dest) {
        //inspo from lecture code
        std::set<std::string> visited;
        std::stack<std::string> s;

        visited.insert(src.getName());
        s.push(src.getName());
        while(!s.empty()) {
            std::string i = s.top();
            s.pop();
            vector<std::pair<double, std::string>> adj = graph[i];
            std::sort(adj.begin(), adj.begin() + adj.size());
            for(std::pair<double, std::string> v : adj) {
                if(visited.count(v.second) == 0) {
                    visited.insert(v.second);
                    s.push(v.second);
                }
            }
            if(visited.count(dest.getName()) == 1) {
                return true;
            }
        }
        return false;
    }*/


    std::vector<std::string> dijkstra(City src, City final) { //***FIX ME***
        // inspo from GeeksForGeeks
        std::vector<double> dist(graph.size(), std::numeric_limits<double>::max());
        dist.at(indexes[src.getName()]) = 0.0; //setting distance of src as 0
        typedef std::pair<double, std::string> pi;
        std::priority_queue <pi, std::vector<pi>, std::greater<pi> > pq;
        std::vector<std::string> path;
        //path.push_back(src.getName());
        std::set<std::string> stop;
        stop.insert(src.getName());

        //Dijkstra's from pseudo code in lecture
        pq.push(std::make_pair(0.0, src.getName()));

        //looping through pq to find the shorted path of each vertex
        while(!pq.empty()) {
            std::pair<double, std::string> p = pq.top();
            pq.pop();
            //relaxing edges
            for(std::pair<double, std::string> p2: graph.at(p.second)) {
                if((dist.at(indexes[p.second]) + p2.first) < dist.at(indexes[p2.second])) {
                    dist.at(indexes[p2.second]) = dist.at(indexes[p.second]) + p2.first; //updating distance
                    //changing priority
                    pq.push(std::make_pair(dist.at(indexes[p2.second]), p2.second));
                    //checking if final is being changed
                    if(p2.second == final.getName())
                        path.push_back(p2.second);
                }
            }
        }
        //path.push_back(final.getName());
        return path;
    }
};

#endif //ADJACENCYLIST_GRAPH_H