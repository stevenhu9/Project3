//
// Created by Alexa Cole on 12/4/21.
//
#include <iomanip>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>


#ifndef ADJACENCYLIST_CITY_H
#define ADJACENCYLIST_CITY_H

class City
{
    int id;
    std::string name;
    std::string country;
    std::string population;
    std::string timezone;
    std::pair<double, double> coordinates;
public:
    City() {
    }
    City(int id, std::string name, std::string country, std::string population, std::string timezone, std::pair<double, double> coordinates)
    {
        this->id = id;
        this->name = name;
        this->country = country;
        this->population = population;
        this->timezone = timezone;
        this->coordinates = coordinates;
    }
    int getID() { return id; }
    std::string getName() { return name; }
    std::string getCountry() { return country; }
    std::string getPopulation() { return population; }
    std::string getTimezone() { return timezone; }
    std::pair<double, double> getCoordinates() { return coordinates; }
};

#endif //ADJACENCYLIST_CITY_H
