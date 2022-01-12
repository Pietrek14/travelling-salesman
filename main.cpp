/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>

class City {
public:
    std::string name;
    
    City(std::string _name) : name(_name) {}
};

class Connection {
public:
    City* city1;
    City* city2;
    
    unsigned int distance;
    
    Connection(City* _city1, City* _city2, unsigned int _distance);
};

Connection::Connection(City* _city1, City* _city2, unsigned int _distance) {
    if(_city1 == _city2) {
        std::cout << "Can't connect a city to itself!" << std::endl;
        return;
    }
    
    this->city1 = _city1;
    this->city2 = _city2;
    this->distance = _distance;
}

class Graph {
public:
    std::vector<City*> cities;
    
    unsigned int GetDistance(City* city1, City* city2);
    
    void AddCity(City*);
    void Connect(City* city1, City* city2, unsigned int distance);
    
    ~Graph();
private:
    std::vector<Connection*> connections;
};

unsigned int Graph::GetDistance(City* city1, City* city2) {
    for(Connection* connection : this->connections) {
        if(
            (connection->city1 == city1 && connection->city2 == city2) ||
            (connection->city1 == city2 && connection->city2 == city1)
        )
            return connection->distance;
    }
    
    return 0;
}

void Graph::AddCity(City* city) {
    for(City* _city : this->cities) {
        if(city == _city) {
            std::cout << "Can't add the same city twice!" << std::endl;
            return;
        }
    }
    
    this->cities.push_back(city);
}

void Graph::Connect(City* city1, City* city2, unsigned int distance) {
    bool isCity1InGraph = false, isCity2InGraph = false;
    
    for(City* _city : this->cities) {
        if(city1 == _city) {
            isCity1InGraph = true;
        }
        
        if(city2 == _city) {
            isCity2InGraph = true;
        }
    }
    
    if(!isCity1InGraph) {
        std::cout << "Can't connect a city that's not in a graph: " << city1->name << "!" << std::endl;
        return;
    }
    
    if(!isCity2InGraph) {
        std::cout << "Can't connect a city that's not in a graph: " << city2->name << "!" << std::endl;
        return;
    }
    
    if(this->GetDistance(city1, city2) != 0) {
        std::cout << "Can't connect cities that are already connected: " << city1->name << ", " << city2->name << "!" << std::endl;
        return;
    }
    
    this->connections.push_back(new Connection(city1, city2, distance));
}

Graph::~Graph() {
    for(City* city : this->cities) {
        delete city;
    }
    
    for(Connection *connection : this->connections) {
        delete connection;
    }
}

template<typename T>
T input(std::string message) {
    std::cout << message;
    
    T data;
    std::cin >> data;
    
    return data;
}

int main()
{
    Graph* graph = new Graph();
    
    unsigned int cityNum = input<unsigned int>("Podaj ilosc miast: ");
    
    if(cityNum < 2) {
        std::cout << "Potrzeba przynajmniej dwoch miast!" << std::endl;
        return 1;
    }
    
    for(int i = 0; i < cityNum; i++) {
        City* city = new City(input<std::string>("Podaj nazwe miasta: "));
        
        graph->AddCity(city);
    }
    
    for(int i = 0; i < cityNum; i++) {
        for(int j = i + 1; j < cityNum; j++) {
            unsigned int distance;
            
            std::cout << "Podaj odleglosc od " << graph->cities[i]->name << " do " << graph->cities[j]->name << ": ";
            std::cin >> distance;
        }
    }
    
    delete graph;

    return 0;
}
