#include <iostream>
#include <vector>

class City
{
public:
	std::string name;

	City(std::string _name) : name(_name) {}
};

class Connection
{
public:
	City *city1;
	City *city2;
	unsigned int distance;

	Connection(City *_city1, City *_city2, unsigned int _distance);
};

Connection::Connection(City *_city1, City *_city2, unsigned int _distance)
{
	if (_city1 == _city2)
	{
		std::cout << "Can't connect a city to itself!" << std::endl;
		return;
	}

	this->city1 = _city1;
	this->city2 = _city2;
	this->distance = _distance;
}

class Graph
{
public:
	std::vector<City *> cities;

	unsigned int GetDistance(City *city1, City *city2);
	unsigned int GetDistance(std::vector<City *> path);

	void AddCity(City *);
	void Connect(City *city1, City *city2, unsigned int distance);

	std::vector<std::vector<City *>> AllPaths();

	~Graph();

private:
	std::vector<Connection *> connections;

	std::vector<std::vector<City *>> AllPermutations(std::vector<City *> cities);
};

unsigned int Graph::GetDistance(City *city1, City *city2)
{
	for (Connection *connection : this->connections)
	{
		if (
			(connection->city1 == city1 && connection->city2 == city2) ||
			(connection->city1 == city2 && connection->city2 == city1))
			return connection->distance;
	}

	return 0;
}

unsigned int Graph::GetDistance(std::vector<City *> path)
{
	unsigned int distance = 0;

	for (unsigned int i = 0; i < path.size() - 1; i++)
	{
		// std::cout << "Distance from " << path[i]->name << " to " << path[i + 1]->name << ": " << this->GetDistance(path[i], path[i + 1]) << std::endl;
		distance += this->GetDistance(path[i], path[i + 1]);
	}

	distance += this->GetDistance(path[0], path[path.size() - 1]);

	return distance;
}

void Graph::AddCity(City *city)
{
	for (City *_city : this->cities)
	{
		if (city == _city)
		{
			std::cout << "Can't add the same city twice!" << std::endl;
			return;
		}
	}

	this->cities.push_back(city);
}

void Graph::Connect(City *city1, City *city2, unsigned int distance)
{
	bool isCity1InGraph = false, isCity2InGraph = false;

	for (City *_city : this->cities)
	{
		if (city1 == _city)
		{
			isCity1InGraph = true;
		}

		if (city2 == _city)
		{
			isCity2InGraph = true;
		}
	}

	if (!isCity1InGraph)
	{
		std::cout << "Can't connect a city that's not in a graph: " << city1->name << "!" << std::endl;
		return;
	}

	if (!isCity2InGraph)
	{
		std::cout << "Can't connect a city that's not in a graph: " << city2->name << "!" << std::endl;
		return;
	}

	if (this->GetDistance(city1, city2) != 0)
	{
		std::cout << "Can't connect cities that are already connected: " << city1->name << ", " << city2->name << "!" << std::endl;
		return;
	}

	this->connections.push_back(new Connection(city1, city2, distance));
}

template <typename T>
std::vector<T> reverse(std::vector<T> v)
{
	std::vector<T> reversed;

	for (int i = v.size() - 1; i >= 0; i--)
	{
		reversed.push_back(v[i]);
	}

	return reversed;
}

std::vector<std::vector<City *>> Graph::AllPaths()
{
	std::vector<std::vector<City *>> paths;

	City *startingCity = this->cities[0];

	std::vector<City *> restOfTheCities = cities;
	restOfTheCities.erase(restOfTheCities.begin());

	std::vector<std::vector<City *>> permutation = AllPermutations(restOfTheCities);

	for (std::vector<City *> path : permutation)
	{
		bool isPathAlreadyInPaths = false;

		std::vector<City *> reversedPath = reverse(path);

		for (std::vector<City *> _path : paths)
		{
			bool pathIsEqual = true;

			for (int i = 0; i < path.size(); i++)
			{
				if (reversedPath[i] != _path[i])
				{
					pathIsEqual = false;
					break;
				}
			}

			if (pathIsEqual)
			{
				isPathAlreadyInPaths = true;
				break;
			}
		}

		if (!isPathAlreadyInPaths)
		{
			paths.push_back(path);
		}
	}

	for (int i = 0; i < paths.size(); i++)
	{
		paths[i].insert(paths[i].begin(), startingCity);
	}

	return paths;
}

std::vector<std::vector<City *>> Graph::AllPermutations(std::vector<City *> cities)
{
	std::vector<std::vector<City *>> permutations;

	if (cities.size() == 1)
	{
		permutations.push_back(cities);
		return permutations;
	}

	for (unsigned int i = 0; i < cities.size(); i++)
	{
		City *city = cities[i];

		std::vector<City *> citiesCopy = cities;
		citiesCopy.erase(citiesCopy.begin() + i);

		std::vector<std::vector<City *>> subPermutations = this->AllPermutations(citiesCopy);

		for (std::vector<City *> subPermutation : subPermutations)
		{
			std::vector<City *> permutation = subPermutation;
			permutation.insert(permutation.begin(), city);

			permutations.push_back(permutation);
		}
	}

	return permutations;
}

Graph::~Graph()
{
	for (City *city : this->cities)
	{
		delete city;
	}

	for (Connection *connection : this->connections)
	{
		delete connection;
	}
}

template <typename T>
T input(std::string message)
{
	std::cout << message;

	T data;
	std::cin >> data;

	return data;
}

std::vector<City *> TravellingSalesman(Graph *graph)
{
	std::vector<City *> cities = graph->cities;
	std::vector<City *> path;

	City *currentCity = cities[0];
	path.push_back(currentCity);

	return path;
}

int main()
{
	Graph *graph = new Graph();

	unsigned int cityNum = input<unsigned int>("Podaj ilosc miast: ");

	if (cityNum < 2)
	{
		std::cout << "Potrzeba przynajmniej dwoch miast!" << std::endl;
		return 1;
	}

	for (int i = 0; i < cityNum; i++)
	{
		City *city = new City(input<std::string>("Podaj nazwe miasta: "));

		graph->AddCity(city);
	}

	for (int i = 0; i < cityNum; i++)
	{
		for (int j = i + 1; j < cityNum; j++)
		{
			unsigned int distance;

			std::cout << "Podaj odleglosc od " << graph->cities[i]->name << " do " << graph->cities[j]->name << ": ";
			std::cin >> distance;

			graph->Connect(graph->cities[i], graph->cities[j], distance);
		}
	}

	std::vector<std::vector<City *>> permutations = graph->AllPaths();
	std::vector<City *> shortestPath = permutations[0];
	unsigned int shortestDistance = 0;

	for (std::vector<City *> path : permutations)
	{
		unsigned int distance = graph->GetDistance(path);

		if (distance < shortestDistance || shortestDistance == 0)
		{
			shortestDistance = distance;
			shortestPath = path;
		}
	}

	std::cout << "Najkrotsza droga: " << std::endl;

	for (City *city : shortestPath)
	{
		std::cout << city->name << " ";
	}

	std::cout << shortestPath[0]->name << std::endl;

	std::cout << "Odleglosc: " << shortestDistance << std::endl;

	delete graph;

	return 0;
}