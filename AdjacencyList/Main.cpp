#include <iomanip>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

class City
{
	int id;
	string name;
	string country;
	string population;
	string timezone;
	pair<double, double> coordinates;
public:
	City(int id, string name, string country, string population, string timezone, pair<double, double> coordinates)
	{
		this->id = id;
		this->name = name;
		this->country = country;
		this->population = population;
		this->timezone = timezone;
		this->coordinates = coordinates;
	}
	int getID() { return id; }
	string getName() { return name; }
	string getCountry() { return country; }
	string getPopulation() { return population; }
	string getTimezone() { return timezone; }
    pair<double, double> getCoordinates() { return coordinates; }
};

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

void sortData(vector<City> Cities, map<string, pair<double, double>>& cities, map<int, vector<City>>& latitude, map<int, vector<City>>& longitude) {
    for(City c : Cities) {
        cities[c.getName()] = c.getCoordinates();

       //insert latitude base on its whole number degree
       int y = int(c.getCoordinates().first);
       latitude[y].push_back(c);

       //insert longitude based on its whole number degree
       int x = int(c.getCoordinates().second);
       latitude[x].push_back(c);
    }
}


int main()
{
	vector<City> cities;
    map<string, pair<double, double>> setCities; //easy look up for city being searched
	map<int, vector<City>> latitude; //sorting city into similar latitude
    map<int, vector<City>> longitude; //sorting city into similar latitude
	getData("data.csv", cities);
	sortData(cities, setCities, latitude, longitude);


	cout << cities[0].getCoordinates().first << " " << cities[0].getCoordinates().second << endl;
	cout << setCities.size() << endl;

    return 0;
}