#include <iomanip>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class City
{
	int id;
	string name;
	string country;
	string population;
	string timezone;
	string coordinates;
public:
	City(int id, string name, string country, string population, string timezone, string coordinates)
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
	string getCoordinates() { return coordinates; }
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
			//cout << "  Coordinates: " << Coordinates << endl;


			City object(ID, Name, Country, Population, TimeZone, Coordinates);
			Cities.push_back(object);
		}
	}
}

int main()
{
	vector<City> cities;
	getData("data.csv", cities);

    return 0;
}