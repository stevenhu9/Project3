#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include<iostream>
#include <algorithm>  
#include <math.h>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <map>
#include <utility>
#include <list>
using namespace std;

class City
{
    int id;
    string name;
    string country;
    std::pair<double, double> coordinates;
public:
    City() {}
    City(int id, string name, string country, std::pair<double, double> coordinates)
    {
        this->id = id;
        this->name = name;
        this->country = country;
        this->coordinates = coordinates;
    }
    int getID() { return id; }
    string getName() { return name; }
    string getCountry() { return country; }
    std::pair<double, double> getCoordinates() { return coordinates; }
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

            //ID, NAME, COUNTRY, COORDINATES

            //GeoID
            int ID;
            string tempID;
            getline(stream, tempID, ';');
            ID = stoi(tempID);
            //out << "ID: " << ID;

            //ASCI Name
            string Name;
            getline(stream, Name, ';');
            //cout << "  Name: " << Name;

            //Country
            string Country;
            getline(stream, Country, ';');
            //cout << "  Country: " << Country;

            //Coordinates
            string Coordinatesx;
            getline(stream, Coordinatesx, ',');
            double coordinatesx = stod(Coordinatesx);
            //cout << "  Coordinates: " << Coordinatesx;

            string Coordinatesy;
            getline(stream, Coordinatesy, ';');
            double coordinatesy = stod(Coordinatesy);
            //cout << ", " << Coordinatesy << endl;

            pair<double, double> coordinates = make_pair(coordinatesx, coordinatesy);

            City object(ID, Name, Country, coordinates);
            Cities.push_back(object);
        }
    }
}

void calculateInBetween(vector<City>& cities, vector<City>& answers, City src, City final) {
    // get starting location
    // get end location
    // get number of stops
    // based on coordinates, get all cities within range of the starting location and end location
    bool north = false;
    bool east = false;
    bool south = false;
    bool west = false;
    // starting location
    double startX = src.getCoordinates().first;
    double startY = src.getCoordinates().second;
    //cout << start << " " << startX << ", " << startY << endl;
    // end location
    double endX = final.getCoordinates().first;
    double endY = final.getCoordinates().second;
    //cout << end << " " << endX << ", " << endY << endl;
    if (endX > startX)
    {
        east = true;
    }
    else
    {
        west = true;
    }
    if (endY > startY)
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
    answers.push_back(src);
    for (unsigned int i = 0; i < cities.size(); i++)
    {
        if (cities[i].getCoordinates().first <= maxx && cities[i].getCoordinates().first >= minx && cities[i].getCoordinates().second <= maxy && cities[i].getCoordinates().second >= miny && cities[i].getName() != src.getName() && cities[i].getName() != final.getName())
        {
            answers.push_back(cities[i]);
        }
    }
    answers.push_back(final);
}

vector<pair<double, double>> AdjMatrix(string startCity, string endCity, bool& found, bool found2, int stops)
{

    vector<City> cities;

    getData("data.csv", cities);

    //New York

    City start;
    City end;

    found = false;
    found2 = false;

    vector<string> startCitySplit;
    stringstream s_stream(startCity); //create string stream from the string
    while (s_stream.good()) {
        string substr;
        getline(s_stream, substr, ','); //get first string delimited by comma
        startCitySplit.push_back(substr);
    }

    vector<string> endCitySplit;
    stringstream se_stream(endCity); //create string stream from the string
    while (se_stream.good()) {
        string substr;
        getline(se_stream, substr, ','); //get first string delimited by comma
        endCitySplit.push_back(substr);
    }

    for (int i = 0; i < cities.size(); i++)
    {
        if (cities[i].getName() == startCitySplit.at(0) && cities[i].getCountry() == startCitySplit.at(1).substr(1))
        {
            start = cities[i];
            found = true;
        }
        if (cities[i].getName() == endCitySplit.at(0) && cities[i].getCountry() == endCitySplit.at(1).substr(1))
        {
            end = cities[i];
            found2 = true;
        }
    }

    if (found == false || found2 == false)
    {
        vector<pair<double, double>> oo;
        return oo;
    }


    // get starting location
    // get end location
    // get number of stops

    // based on coordinates, get all cities within range of the starting location and end location

    bool north = false;
    bool east = false;
    bool south = false;
    bool west = false;


    // starting location
    double tempx = start.getCoordinates().first;
    double tempy = start.getCoordinates().second;

    // end location
    double tempendx = end.getCoordinates().first;
    double tempendy = end.getCoordinates().second;

    if (tempendx > tempx)
    {
        east = true;
    }
    else
    {
        west = true;
    }

    if (tempendy > tempy)
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
        maxy = tempendy;
        miny = tempy;
    }
    else
    {
        maxy = tempy;
        miny = tempendy;
    }

    if (east)
    {
        maxx = tempendx;
        minx = tempx;
    }
    else
    {
        maxx = tempx;
        minx = tempendx;
    }

    // maxx == x-coordinate of city cannot be greater than maxx
    // maxy == y-coordinate of city cannot be greater than maxy

    vector<City> answers;

    answers.push_back(start);

    for (unsigned int i = 0; i < cities.size(); i++)
    {
        if (cities[i].getCoordinates().first <= maxx && cities[i].getCoordinates().first >= minx && cities[i].getCoordinates().second <= maxy && cities[i].getCoordinates().second >= miny && cities[i].getName() != start.getName() && cities[i].getName() != end.getName())
        {
            answers.push_back(cities[i]);
        }
    }

    answers.push_back(end);
    // generate matrix with each city's distance from each other city

    int edges = 0;
    vector<vector<double>> graph(answers.size(), vector<double>(answers.size(), 0)); // influenced from kapoor's lecture slides
    map<string, int> mapper;

    for (unsigned int i = 0; i < answers.size(); i++)
    {
        for (unsigned int j = i + 1; j < answers.size(); j++)
        {

            double x = pow(answers[i].getCoordinates().first - answers[j].getCoordinates().first, 2);
            double y = pow(answers[i].getCoordinates().second - answers[j].getCoordinates().second, 2);

            double distance = sqrt(x + y);

            string from = answers[i].getName();
            string to = answers[j].getName();


            if (mapper.find(from) == mapper.end())
            {
                mapper[from] = edges++;
            }
            if (mapper.find(to) == mapper.end())
            {
                mapper[to] = edges++;
            }
            graph[mapper[from]][mapper[to]] = distance;
            graph[mapper[to]][mapper[from]] = distance;
        }
    }

    // use breadth first search and the number of stops to generate paths the user can take to get to their location

    // Multiple Paths
    //vector<vector<pair<double, double>>> paths(3,vector<pair<double,double>>(3,make_pair(0.0,0.0)));
    /*
    if (stops == 0)
    {
        paths[0].push_back(make_pair(start.getX(), start.getY()));
        paths[0].push_back(make_pair(end.getX(), end.getY()));
    }

    else
    {
        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < stops; i++)
            {
                if (i == stops - 1)
                {
                    paths[j].push_back(make_pair(end.getX(), end.getY()));
                }

                else
                {

                }
            }
        }
    }
    */


    vector<pair<double, double>> paths;
    vector<City> z;
    vector<double> d;

    cout << endl;


    double distance = 0;

    if (stops == 0)
    {
        z.push_back(start);
        z.push_back(end);
        paths.push_back(make_pair(start.getCoordinates().first, start.getCoordinates().second));
        paths.push_back(make_pair(end.getCoordinates().first, end.getCoordinates().second));
        distance = graph[0][answers.size() - 1];
        distance = distance * 69;
        d.push_back(distance);
    }

    else if (stops > answers.size() - 2)
    {
        cout << "Error: Too many Stops" << endl;
        exit(1);
    }

    else
    {
        paths.push_back(make_pair(start.getCoordinates().first, start.getCoordinates().second));
        z.push_back(start);
        int curr = 0;
        City currC = start;

        double shortest = 999;
        double distance = 0;

        vector<bool> visited(answers.size(), false);
        visited[0] = true;

        for (int j = 0; j < stops; j++)
        {
            for (unsigned int i = 1; i < answers.size() - 1; i++)
            {
                if (graph[curr][i] + graph[i][answers.size() - 1] < shortest && curr != i && visited[i] == false)
                {
                    distance += graph[curr][i];
                    curr = i;
                    currC = answers[i];
                    shortest = graph[curr][i] + graph[i][answers.size() - 1];
                    visited[i] = true;
                }
            }
            distance = distance * 69;
            d.push_back(distance);
            distance = 0;
            shortest = 999;
            z.push_back(currC);
            paths.push_back(make_pair(currC.getCoordinates().first, currC.getCoordinates().second));
        }
        z.push_back(end);
        d.push_back(graph[curr][answers.size() - 1] * 69);
        paths.push_back(make_pair(end.getCoordinates().first, end.getCoordinates().second));
    }

    for (unsigned int i = 0; i < paths.size() - 1; i++)
    {
        cout << "The distance from " << z[i].getName() << " to " << z[i + 1].getName() << " is " << d[i] << " miles" << endl;
    }

    return paths;
};

vector<pair<double, double>> adjList(string startCity, string endCity, bool& found, bool& found2, int stops)
{
    vector<City> cities;
    map<string, pair<double, double>> setCities; //easy look up for city being searched
    getData("data.csv", cities);

    City src;
    City final;

    found = false;
    found2 = false;

    vector<string> startCitySplit;
    stringstream s_stream(startCity); //create string stream from the string
    while (s_stream.good()) {
        string substr;
        getline(s_stream, substr, ','); //get first string delimited by comma
        startCitySplit.push_back(substr);
    }

    vector<string> endCitySplit;
    stringstream se_stream(endCity); //create string stream from the string
    while (se_stream.good()) {
        string substr;
        getline(se_stream, substr, ','); //get first string delimited by comma
        endCitySplit.push_back(substr);
    }

    for (int i = 0; i < cities.size(); i++)
    {
        if (cities[i].getName() == startCitySplit.at(0) && cities[i].getCountry() == startCitySplit.at(1).substr(1))
        {
            src = cities[i];
            found = true;
        }
        if (cities[i].getName() == endCitySplit.at(0) && cities[i].getCountry() == endCitySplit.at(1).substr(1))
        {
            final = cities[i];
            found = true;
        }
    }

    vector<City> answers;
    calculateInBetween(cities, answers, src, final);

    map<string, vector<pair<string, double>>> linkedlist;

    for (int i = 0; i < answers.size(); i++)
    {
        for (int j = i + 1; j < answers.size(); j++)
        {
            double x = pow(answers[i].getCoordinates().first - answers[j].getCoordinates().first, 2);
            double y = pow(answers[i].getCoordinates().second - answers[j].getCoordinates().second, 2);

            double distance = sqrt(x + y);
            string from = answers[i].getName();
            string to = answers[j].getName();
            linkedlist[from].push_back(make_pair(to, distance));
            if (linkedlist.find(to) == linkedlist.end())
            {
                linkedlist[to] = {};
            }
        }
    }

    vector<pair<double, double>> paths;
    vector<City> z;
    vector<double> d;
    double distance = 0;

    if (stops == 0)
    {
        z.push_back(src);
        z.push_back(final);
        paths.push_back(make_pair(src.getCoordinates().first, src.getCoordinates().second));
        paths.push_back(make_pair(final.getCoordinates().first, final.getCoordinates().second));
        for (int i = 0; i < linkedlist[src.getName()].size(); i++)
        {
            if (linkedlist[src.getName()][i].first == final.getName())
            {
                distance = linkedlist[src.getName()][i].second;
                break;
            }
        }
        distance = distance * 69;
        d.push_back(distance);
    }
    else if (stops > answers.size() - 2)
    {
        cout << "Error: Too many Stops" << endl;
    }
    else
    {
        paths.push_back(make_pair(src.getCoordinates().first, src.getCoordinates().second));
        z.push_back(src);
        int curr = 0;
        string currCS = src.getName();
        City currC = src;
        double shortest = 999;
        distance = 0;
        vector<bool> visited(answers.size(), false);
        visited[0] = true;
        for (int j = 0; j < stops; j++)
        {
            for (int i = 0; i < answers.size() - 2; i++)
            {
                string to = linkedlist[currCS][i].first;
                int length = linkedlist[to].size();
                if (linkedlist[currCS][i].second + linkedlist[to][length - 1].second < shortest && visited[i] == false)
                {
                    distance += linkedlist[currCS][i].second;
                    curr = i;
                    currC = answers[i];
                    shortest = linkedlist[currCS][i].second + linkedlist[to][length - 1].second;
                    visited[i] = true;
                }
            }
            distance = distance * 69;
            d.push_back(distance);
            distance = 0;
            shortest = 999;
            z.push_back(currC);
            paths.push_back(make_pair(currC.getCoordinates().first, currC.getCoordinates().second));
        }
        z.push_back(final);
        distance = distance * 69;
        int length = linkedlist[currCS].size();
        d.push_back(linkedlist[currCS][length - 1].second);
        paths.push_back(make_pair(final.getCoordinates().first, final.getCoordinates().second));
    }
    for (int i = 0; i < paths.size() - 1; i++)
    {
        cout << "The distance from " << z[i].getName() << " to " << z[i + 1].getName() << " is " << d[i] << " miles" << endl;
    }

    return paths;

}

string inputText(sf::Clock& clock, sf::Event& event, string& playerInput, sf::Text& playerText)
{
    if (event.type == sf::Event::TextEntered)
    {
        if (std::isprint(event.text.unicode))
        {
            playerInput += event.text.unicode;
            playerText.setString(playerInput);
        }
    }
    else if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::BackSpace)
        {
            if (!playerInput.empty())
            {
                playerInput.pop_back();
                playerText.setString(playerInput);
            }
        }
    }
    return playerInput;
}

void underScore(sf::Clock& clock, string& playerInput, sf::Text& playerText, bool displayCurser)
{
    static sf::Time text_effect_time;
    static bool show_cursor;

    text_effect_time += clock.restart();

    if (text_effect_time >= sf::seconds(1.5f))
    {
        show_cursor = !show_cursor;
        text_effect_time = sf::Time::Zero;
    }

    if(displayCurser)
        playerText.setString(playerInput + (show_cursor ? '_' : ' '));
    else
        playerText.setString(playerInput + (show_cursor ? ' ' : ' '));
}

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

double degreesToRadians(double degrees) {
    return (degrees * M_PI) / 180;
}

pair <double, double> LongLangToPixels(double latitude, double longitude)
{
    /*

    const double TILE_SIZE = 1024;                              // Pixel size of the base tile.
    const double ORIGIN = TILE_SIZE / 2;                        // The point to which LatLng (0, 0) projects.
    const double PIXELS_PER_DEGREE = TILE_SIZE / 360;           // Number of pixels of world coords for every degree.
    const double PIXELS_PER_RADIAN = TILE_SIZE / (2 * M_PI);    // Number of pixels of world coords for every radian.

    const double x = ORIGIN + longitude * PIXELS_PER_DEGREE;

    double sinY = sin(latitude * M_PI / 180);
    sinY = min(max(sinY, -0.9999), 0.9999);
    const double y = ORIGIN + 0.5 * (log((1 + sinY) / (1 - sinY)) * -PIXELS_PER_RADIAN);

    */

    double const FE = 180; // false easting
    double const radius = 2256 / (2 * M_PI);

    double const latRad = degreesToRadians(latitude);
    double const lonRad = degreesToRadians(longitude + FE);

    double const x = lonRad * radius;

    double const yFromEquator = radius * log(tan(M_PI / 4 + latRad / 2));
    double const y = 1504 / 2 - yFromEquator;



    pair <double, double> pixels;
    pixels.first = (x-110);
    pixels.second = (y-110);

    return pixels;
}

int main()
{
    
    //---------------------------------------------------LOAD IMAGES--------------------------------------------------------------//


    // Create the main window
    sf::RenderWindow window(sf::VideoMode(2256, 1504), "SFML window", sf::Style::Default);

    //map:
    sf::Texture mapText;
    if (!mapText.loadFromFile("Pictures/WorldMap - FutureUse.jpg"))
        return EXIT_FAILURE;
    sf::Sprite Map(mapText);

    //map marker
    sf::Texture mapMarkerText;
    if (!mapMarkerText.loadFromFile("Pictures/mapMarker.png"))
        return EXIT_FAILURE;
    sf::Sprite MapMarker(mapMarkerText);

    //Background Menu:
    sf::Texture BackgroundMenuTexture;
    if (!BackgroundMenuTexture.loadFromFile("Pictures/BackgroundMenuBar.png"))
        return EXIT_FAILURE;
    sf::Sprite BackgroundMenu(BackgroundMenuTexture);

    //Close Button:
    sf::Texture closeTexture;
    if (!closeTexture.loadFromFile("Pictures/closeButton.png"))
        return EXIT_FAILURE;
    sf::Sprite closeButton(closeTexture);

    //Select Implementation Error
    sf::Texture SelectImpErrorTexture;
    if (!SelectImpErrorTexture.loadFromFile("Pictures/SelectImpError.png"))
        return EXIT_FAILURE;
    sf::Sprite SelectImpError(SelectImpErrorTexture);

    //Submit Button:
    sf::Texture SubmitButtonTexture;
    if (!SubmitButtonTexture.loadFromFile("Pictures/SubmitButton.png"))
        return EXIT_FAILURE;
    sf::Sprite SubmitButton(SubmitButtonTexture);

    //Submit Button Clicked:
    sf::Texture SubmitButtonClickedTexture;
    if (!SubmitButtonClickedTexture.loadFromFile("Pictures/SubmitButtonClicked.png"))
        return EXIT_FAILURE;
    sf::Sprite SubmitButtonClicked(SubmitButtonClickedTexture);

    //Edge List Button:
    sf::Texture EdgeListTexture;
    if (!EdgeListTexture.loadFromFile("Pictures/EdgeListButton.png"))
        return EXIT_FAILURE;
    sf::Sprite EdgeListButton(EdgeListTexture);

    //EdgeList Button Clicked:
    sf::Texture EdgeListClickedTexture;
    if (!EdgeListClickedTexture.loadFromFile("Pictures/EdgeListButtonClicked.png"))
        return EXIT_FAILURE;
    sf::Sprite EdgeListButtonClicked(EdgeListClickedTexture);

    //Adjacency List Button:
    sf::Texture AdjacencyListTexture;
    if (!AdjacencyListTexture.loadFromFile("Pictures/AdjacencyListButton.png"))
        return EXIT_FAILURE;
    sf::Sprite AdjacencyListButton(AdjacencyListTexture);

    //Adjacency List Button Clicked:
    sf::Texture AdjacencyListClickedTexture;
    if (!AdjacencyListClickedTexture.loadFromFile("Pictures/AdjacencyListButtonClicked.png"))
        return EXIT_FAILURE;
    sf::Sprite AdjacencyListButtonClicked(AdjacencyListClickedTexture);

    //Starting Location Box:
    sf::Texture StartLocBoxTexture;
    if (!StartLocBoxTexture.loadFromFile("Pictures/StartingLocationBox.png"))
        return EXIT_FAILURE;
    sf::Sprite StartLocBox(StartLocBoxTexture);

    //Starting Location Error Box:
    sf::Texture StartLocErrorBoxTexture;
    if (!StartLocErrorBoxTexture.loadFromFile("Pictures/StartLocErrorBox.png"))
        return EXIT_FAILURE;
    sf::Sprite StartLocErrorBox(StartLocErrorBoxTexture);

    //Ending Location Box:
    sf::Texture EndLocBoxTexture;
    if (!EndLocBoxTexture.loadFromFile("Pictures/EndingLocationBox.png"))
        return EXIT_FAILURE;
    sf::Sprite EndLocBox(EndLocBoxTexture);

    //Ending Location Error Box:
    sf::Texture EndLocErrorBoxTexture;
    if (!EndLocErrorBoxTexture.loadFromFile("Pictures/EndLocErrorBox.png"))
        return EXIT_FAILURE;
    sf::Sprite EndLocErrorBox(EndLocErrorBoxTexture);

    //NumberOfStopsBox:
    sf::Texture NumberOfStopsBoxTexture;
    if (!NumberOfStopsBoxTexture.loadFromFile("Pictures/NumberOfStopsBox.png"))
        return EXIT_FAILURE;
    sf::Sprite NumberOfStopsBox(NumberOfStopsBoxTexture);

    //NumberOfStopsErrorBox:
    sf::Texture NumberOfStopsErrorBoxTexture;
    if (!NumberOfStopsErrorBoxTexture.loadFromFile("Pictures/NumStopsErrorBox.png"))
        return EXIT_FAILURE;
    sf::Sprite NumStopsErrorBox(NumberOfStopsErrorBoxTexture);

    //------------------------------------------------------------------TEXT INPUT---------------------------------------------------------------//
    sf::Font font;
    if (!font.loadFromFile("fonts/regular.otf"))
        return EXIT_FAILURE;

    //Start loc:
    string startLoc;
    sf::Text startText;
    startText.setFont(font);
    startText.setCharacterSize(24);
    startText.setFillColor(sf::Color::Black);

    //End loc:
    string endLoc;
    sf::Text endText;
    endText.setFont(font);
    endText.setCharacterSize(24);
    endText.setFillColor(sf::Color::Black);

    //Num of stops:
    string numStops;
    sf::Text numStopText;
    numStopText.setFont(font);
    numStopText.setCharacterSize(24);
    numStopText.setFillColor(sf::Color::Black);


    //------------------------------------------------------------------ VARIABLES ---------------------------------------------------------------//

    sf::Clock clock1;
    sf::Clock clock2;
    sf::Clock clock3;

    bool sumbitClicked = false;
    bool AdjacencyListClicked = false;
    bool EdgeListClicked = false;
    bool startLocClicked = false;
    bool endLocClicked = false;
    bool numStopsClicked = false;

    bool submitting = false;
    bool ReadyToRun[5];
    for (int i = 0; i < 5; i++)
    {
        ReadyToRun[i] = false;
    }

    string startLocInput;
    string endLocInput;
    string numStopsInput;
    int numStopsInt = 0;

    float menuX = 872;
    float menuY = 294;

    bool startFoundError = false;
    bool endFoundError = false;

    bool closed = false;

    vector<pair <double, double>> markersLoc;


    //------------------------------------------------------------------ SFML LOOP ---------------------------------------------------------------//

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            //allow the window to resize without messing anything up 
           if (event.type == sf::Event::Resized)
            {
                sf::FloatRect view(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(view));
            }

            //left click
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                

                if (closeButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    closed = !closed;
                
                if (SubmitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) //submit button clicked
                    sumbitClicked = true;
                if (AdjacencyListButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) //Adjacency List button clicked
                {
                    AdjacencyListClicked = !AdjacencyListClicked;
                    EdgeListClicked = false;
                }
                if (EdgeListButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) //Edge List button clicked
                {
                    EdgeListClicked = !EdgeListClicked;
                    AdjacencyListClicked = false;
                }
                if (StartLocBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) //start location box clicked
                {
                    startLocClicked = !startLocClicked;
                    endLocClicked = false;
                    numStopsClicked = false;
                }
                if (EndLocBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) //end location box clicked
                {
                    endLocClicked = !endLocClicked;
                    startLocClicked = false;
                    numStopsClicked = false;
                }
                if (NumberOfStopsBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) //num stops box clicked
                {
                    numStopsClicked = !numStopsClicked;
                    endLocClicked = false;
                    startLocClicked = false;
                }
            } 
            else
            {
                sumbitClicked = false;
            }

            //location box inputting text:
            if (startLocClicked)
            {
                startLocInput = inputText(clock1, event, startLoc, startText);
            }
            if (endLocClicked)
            {
                endLocInput = inputText(clock2, event, endLoc, endText);
            }
            if (numStopsClicked)
            {
                numStopsInput = inputText(clock3, event, numStops, numStopText);
            }

            if (submitting && ReadyToRun[4])
            {
                submitting = false;
                sumbitClicked = false;
                for (int i = 0; i < 5; i++)
                {
                    ReadyToRun[i] = false;
                }

                numStopsInt = stoi(numStopsInput) + 2;

                bool startFound = false;
                bool endFound = false;

                //run program
                if (EdgeListClicked)
                {

                    markersLoc = AdjMatrix(startLocInput, endLocInput, startFound, endFound, numStopsInt - 2);
                     
                    /* DOESNT WORK!!!!!
                    if (startFound == false)
                    {
                        numStopsInt = 0;
                        startFoundError = true;
                        //error in start
                    }
                   
                    if(endFound == false)
                    {
                        numStopsInt = 0;
                        endFoundError = true;
                        //error in end
                    }
                    */
                }
                else if (AdjacencyListClicked)
                {
                    markersLoc = adjList(startLocInput, endLocInput, startFound, endFound, numStopsInt - 2);
                }
            }
        }

        window.clear();

        //Map
        window.draw(Map);
         
        if (!closed)
        {
            //location box underscores
            underScore(clock1, startLoc, startText, startLocClicked);
            underScore(clock2, endLoc, endText, endLocClicked);
            underScore(clock3, numStops, numStopText, numStopsClicked);

            //background menu
            BackgroundMenu.setPosition(menuX + 0.f, menuY + 0.f);
            window.draw(BackgroundMenu);

            if (sumbitClicked)
            {
                //submit Button Clicked:
                SubmitButtonClicked.setPosition(menuX + 75.f, menuY + 765.f);
                window.draw(SubmitButtonClicked);
                submitting = true;
            }
            else
            {
                //submit button
                SubmitButton.setPosition(menuX + 75.f, menuY + 765.f);
                window.draw(SubmitButton);
            }

            if (submitting && (!EdgeListClicked && !AdjacencyListClicked))
            {
                SelectImpError.setPosition(menuX + 79.f, menuY + 510.f);
                window.draw(SelectImpError);
                ReadyToRun[0] = false;
            }
            else if (submitting && (EdgeListClicked || AdjacencyListClicked))
            {
                ReadyToRun[0] = true;
            }

            //start location box:
            if (submitting && startLocInput.empty() || startFoundError)
            {
                StartLocErrorBox.setPosition(menuX + 75.f, menuY + 225.f);
                window.draw(StartLocErrorBox);
                ReadyToRun[1] = false;
            }
            else
            {
                StartLocBox.setPosition(menuX + 75.f, menuY + 225.f);
                window.draw(StartLocBox);
            }
            if (submitting && !startLocInput.empty())
            {
                ReadyToRun[1] = true;
            }
            startText.setPosition(menuX + 110.f, menuY + 260);
            window.draw(startText);

            //End location box:
            if (submitting && endLocInput.empty() || endFoundError)
            {
                EndLocErrorBox.setPosition(menuX + 75.f, menuY + 315);
                window.draw(EndLocErrorBox);
                ReadyToRun[2] = false;
            }
            else
            {
                EndLocBox.setPosition(menuX + 75.f, menuY + 315);
                window.draw(EndLocBox);
            }
            if (submitting && !endLocInput.empty())
            {
                ReadyToRun[2] = true;
            }
            endText.setPosition(menuX + 110.f, menuY + 350);
            window.draw(endText);

            //Num Stops box:
            if ((!is_number(numStopsInput) && !numStopsInput.empty()) || (submitting && numStopsInput.empty()))
            {
                NumStopsErrorBox.setPosition(menuX + 75.f, menuY + 405);
                window.draw(NumStopsErrorBox);
                ReadyToRun[3] = false;
            }
            else
            {
                NumberOfStopsBox.setPosition(menuX + 75.f, menuY + 405);
                window.draw(NumberOfStopsBox);
            }
            if ((is_number(numStopsInput) && !numStopsInput.empty()) && submitting)
            {
                ReadyToRun[3] = true;
            }
            numStopText.setPosition(menuX + 110.f, menuY + 440);
            window.draw(numStopText);

            //check for submitting:
            if (submitting && sumbitClicked)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (!ReadyToRun[i])
                    {
                        ReadyToRun[4] = false;
                        break;
                    }
                    else
                        ReadyToRun[4] = true;
                }
            }


            if (EdgeListClicked)
            {
                //Edge List Button Clicked:
                EdgeListButtonClicked.setPosition(menuX + 80.f, menuY + 565.f);
                window.draw(EdgeListButtonClicked);
            }
            else
            {
                //Edge List:
                EdgeListButton.setPosition(menuX + 80.f, menuY + 565.f);
                window.draw(EdgeListButton);
            }

            if (AdjacencyListClicked)
            {
                //Adjacency List Button Clicked:
                AdjacencyListButtonClicked.setPosition(menuX + 78.f, menuY + 640);
                window.draw(AdjacencyListButtonClicked);
            }
            else
            {
                //Adjacency List:
                AdjacencyListButton.setPosition(menuX + 78.f, menuY + 640);
                window.draw(AdjacencyListButton);
            }
        }

        //Map Markers:
        for (int i = 0; i < numStopsInt; i++)
        {
            pair <double, double> temp = LongLangToPixels(markersLoc[i].first, markersLoc[i].second);
            MapMarker.setPosition(temp.first, temp.second);
            window.draw(MapMarker);

            //lines:
            if (i < numStopsInt - 1)
            {
                sf::VertexArray quad(sf::Quads, 4);

                float x1 = temp.first + 25;
                float y1 = temp.second + 50;

                pair <double, double> tempTwo = LongLangToPixels(markersLoc[i + 1].first, markersLoc[i + 1].second);
                float x2 = tempTwo.first + 25;
                float y2 = tempTwo.second + 50;

                quad[0].position = sf::Vector2f(x1, y1);
                quad[1].position = sf::Vector2f(x2, y2);
                quad[2].position = sf::Vector2f(x2, y2 + 5);
                quad[3].position = sf::Vector2f(x1, y1 + 5);

                for (int i = 0; i < 4; i++)
                {
                    quad[i].color = sf::Color::Red;
                }

                window.draw(quad);
            }
        }

        //close button
        closeButton.setPosition(menuX + 210, menuY + 885);
        window.draw(closeButton);

        window.display();       

    }
    return EXIT_SUCCESS;
}