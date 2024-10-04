#pragma once
#include "Pathfinding.h"
#include <iostream>

using namespace AIForGames;

class NodeMap
{
    int m_width, m_height;
    float m_cellSize;

    Node** m_nodes;

public:
    void Initialise(std::vector<std::string> asciiMap, int cellSize);
};
