#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct YahtzeeCombination {
	sf::String name;
	int score;
};

std::string checkCombination(std::vector<int> frontValues);

extern const int numCombinations;
extern sf::Text combinationText[];
extern sf::Text combinationScore[];
extern const int NUM_COMBINATIONS;
extern const char* combinationNames[];
extern bool combinationClicked[];

