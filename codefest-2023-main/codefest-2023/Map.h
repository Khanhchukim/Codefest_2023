#pragma once
#include <vector>
#include <sio_message.h>

class Map
{
public:
	size_t getSizeRows();
	size_t getSizeCols();

	std::vector<std::pair<int, int>> &getBombMap();
	std::vector<std::vector<int>> &getMap();
	void updateMap(const std::vector<sio::message::ptr>& map, const std::vector<sio::message::ptr>& bombs, const int* power);
	void updatePositionInMap(int &row, int &col, int &value);
	void print();
	~Map();
	Map();

private:
	int _rows{ 0 };
	int _cols{ 0 };

	std::vector<std::vector<int>> _map;
	std::vector<std::vector<int>> _bombMap;

};
