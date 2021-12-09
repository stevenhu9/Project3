#include <iomanip>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

#include "City.h"
#include "Graph.h"

using namespace std;

void getData(string fileName, vector<City>& Cities)
{
	ifstream openedFile(fileName);

	if (openedFile.is_open())
	{
		string oneLine;
		getline(openedFile, oneLine);

		while (getline(openedFile, oneLine))
		{
			istringstream stream(oneLine);

			//ID, NAME, COUNTRY, POPULATION, TIMEZONE, COORDINATES

			string holder;

			//GeoID
			int ID;
			string tempID;
			getline(stream, tempID, ';');
			ID = stoi(tempID);
			//cout << "ID: " << ID;

			//Name
			getline(stream, holder, ';');

			//ASCI Name
			string Name;
			getline(stream, Name, ';');
			//cout << "  Name: " << Name;

			//Alternative Name, Feature class, featrue code, country code
			getline(stream, holder, ';');
			getline(stream, holder, ';');
			getline(stream, holder, ';');
			getline(stream, holder, ';');

			//Country
			string Country;
			getline(stream, Country, ';');
			//cout << "  Country: " << Country;

			//Country Code 2,Admin 1,2,3,4
			getline(stream, holder, ';');
			getline(stream, holder, ';');
			getline(stream, holder, ';');
			getline(stream, holder, ';');
			getline(stream, holder, ';');

			//Population
			string Population;
			getline(stream, Population, ';');
			//cout << "Population: " << Population;

			//Elevation and Digital Elavation model
			getline(stream, holder, ';');
			getline(stream, holder, ';');
			
			//TimeZone
			string TimeZone;
			getline(stream, TimeZone, ';');
			//cout << "  TimeZone: " << TimeZone;

			//Modification Date, LABEL EN
			getline(stream, holder, ';');
			getline(stream, holder, ';');

			//Coordinates
			string Coordinates;
			getline(stream, Coordinates, ';');
			int index = Coordinates.find(',');
			int y = stod(Coordinates.substr(0, index));
			int x = stod(Coordinates.substr(index + 1));
            pair<double, double> coordinates = make_pair(y, x);
			//cout << "  Coordinates: " << Coordinates << endl;

			City object(ID, Name, Country, Population, TimeZone, coordinates);
			Cities.push_back(object);
		}
	}
}

void sortData(vector<City> Cities, map<string, pair<double, double>>& cities) {
    for(City c : Cities) {
        cities[c.getName()] = c.getCoordinates();
    }
}

void calculateInBetween(vector<City>& cities, map<string, pair<double, double>>& setCities, string start, string end, vector<City>& answers, City& src, City& final) {
    // get starting location
    // get end location
    // get number of stops

    // based on coordinates, get all cities within range of the starting location and end location

    bool north = false;
    bool east = false;
    bool south = false;
    bool west = false;


    // starting location
    int startX = setCities[start].second;
    int startY = setCities[start].first;

    //cout << start << " " << startX << ", " << startY << endl;

    // end location
    int endX = setCities[end].second;
    int endY = setCities[end].first;

    //cout << end << " " << endX << ", " << endY << endl;

    if (endX > startX)
    {
        east = true;
    }
    else
    {
        west = true;
    }

    if (endY > endX)
    {
        north = true;
    }

    else
    {
        south = true;
    }

    double maxy;
    double maxx;
    double miny;
    double minx;

    if (north)
    {
        maxy = endY;
        miny = startY;
    }
    else
    {
        maxy = startY;
        miny = endY;
    }

    if (east)
    {
        maxx = endX;
        minx = startX;
    }
    else
    {
        maxx = startX;
        minx = endX;
    }

    // maxx == x-coordinate of city cannot be greater than maxx
    // maxy == y-coordinate of city cannot be greater than maxy

    for (int i = 0; i < cities.size();i++)
    {
        if ((cities[i].getCoordinates().second <= maxx && cities[i].getCoordinates().second >= minx) && (cities[i].getCoordinates().first <= maxy && cities[i].getCoordinates().first >= miny))
        {
            answers.push_back(cities[i]);
            if((cities[i].getCoordinates().second == maxx || cities[i].getCoordinates().second == minx) && (cities[i].getCoordinates().first == maxy || cities[i].getCoordinates().first == miny)) {
                if (cities[i].getName() == start)
                    src = cities[i];
                else if (cities[i].getName() == end)
                    final = cities[i];
            }
        }
    }

    /*for (int j = 0; j < answers.size(); j++)
    {
        cout << answers[j].getName() << " " << answers[j].getCoordinates().second << ", " << answers[j].getCoordinates().first << endl;
    }*/

    //cout << answers.size() << endl;

    // generate matrix with each city's distance from the starting location
    // use breadth first search and the number of stops to generate paths the user can take to get to their location
    // display possible paths and their distances
}

int main()
{
	vector<City> cities;
    map<string, pair<double, double>> setCities; //easy look up for city being searched
	getData("data.csv", cities);
	sortData(cities, setCities);

	//cout << cities[0].getCoordinates().first << " " << cities[0].getCoordinates().second << endl;
	//cout << setCities.size() << endl;
	//cout << cities.size() << endl;

	vector<City> answers;
	City src;
	City final;

	calculateInBetween(cities, setCities, "Overton", "Oban", answers, src, final);

	//cout << src.getName() << " " << src.getCoordinates().second << " " << src.getCoordinates().first << endl;
    //cout << final.getName() << " " << final.getCoordinates().second << " " << final.getCoordinates().first << endl;

    Graph adjList(answers);

    cout << answers.size() << " " << adjList.indexes.size() << " " << adjList.graph.size() << endl;


    vector<string> path = adjList.ShortestPath(src, final, 4);

    for(string s : path) {
        pair<double, double> coordinates = setCities[s];
        cout << s << " " << coordinates.second << ", " << coordinates.first << endl;
    }

    return 0;
}