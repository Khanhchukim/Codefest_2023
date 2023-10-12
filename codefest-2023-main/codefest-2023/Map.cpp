#include "Map.h"
#include <iostream>

Map::Map()
{

}


Map::~Map()
{
}

size_t Map::getSizeRows()
{
	return _map.size();
}

size_t Map::getSizeCols()
{
	return _map[0].size();
}

std::vector<std::vector<int>>& Map::getMap() {
	return _map;
}

// These arrays are used to get row and column
// numbers of 4 neighbours of a given cell
extern int rowNum[];
extern int colNum[];

bool isValid(const int& row, const int& col, const int& row_size, const int& col_size) {
	return 0 <= row && row < row_size && 0 <= col && col < col_size;
}

bool firstTime = true;
void Map::updateMap(const std::vector<sio::message::ptr>& map, const std::vector<sio::message::ptr>& bombs, const int* power) {
	if (firstTime) {
		std::vector<std::vector<int>> new_map;
		for (const auto& map_row : map)
		{
			std::vector<int> row;
			for (const auto& r : map_row->get_vector())
			{
				row.push_back(r->get_int());
			}
			new_map.push_back(row);
		}
		_map = new_map;
		firstTime = false;
	}
	else {
		for (int i = 0; i < _map.size(); i++)
		{
			const sio::message::ptr& map_row = map[i];
			const std::vector<sio::message::ptr> row = map_row->get_vector();
			for (int j = 0; j < row.size(); j++)
			{
				_map[i][j] = row[j]->get_int();
			}
		}
	}

	for (const auto& bomb : bombs)
	{
		auto _bomb = bomb->get_map();
		int playerId = stoi(_bomb["playerId"]->get_string().substr(6, 1));
		int row = _bomb["row"]->get_int();
		int col = _bomb["col"]->get_int();
		_map[row][col] = 1;
		for (int i = 1; i <= power[playerId - 1]; i++) {
			for (int j = 0; j < 4; j++)
			{
				int _row = row + i * rowNum[j];
				int _col = col + i * colNum[j];
				if (isValid(_row, _col, _map.size(), _map[0].size()) && _map[_row][_col] == 0) {
					_map[_row][_col] = -1;
				}
			}
		}
	}

	
}

void Map::updatePositionInMap(int &row, int &col, int &value)
{
	_map[row][col] = value;
}

void Map::print() {
	for (std::vector<int> m : _map) {
		for (int i : m) {
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}
}