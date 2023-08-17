#include "YahtzeeCombination.h"

const int NUM_COMBINATIONS = 13;
YahtzeeCombination combinations[NUM_COMBINATIONS] = {
{"Ones", 0},
{"Twos", 0},
{"Threes", 0},
{"Fours", 0},
{"Fives", 0},
{"Sixes", 0},
{"Three of a Kind", 0},
{"Four of a Kind", 0},
{"Full House", 0},
{"Small Straight", 0},
{"Large Straight", 0},
{"Chance", 0},
{"Yahtzee", 0},
};

const int numCombinations = 13;
sf::Text combinationText[numCombinations];
sf::Text combinationScore[numCombinations];

const char* combinationNames[numCombinations] = {
"Ones", "Twos", "Threes", "Fours", "Fives", "Sixes",
"Three of a Kind", "Four of a Kind", "Full House",
"Small Straight", "Large Straight", "Chance", "Yahtzee"
};

bool combinationClicked[NUM_COMBINATIONS] = { false };

std::string checkCombination(std::vector<int> frontValues) {
	int ones = 0, twos = 0, threes = 0, fours = 0, fives = 0, sixes = 0, sum = 0;
	for (int i = 0; i < 5; i++) {
		switch (frontValues[i]) {
		case 1:
			ones++;
			sum += 1;
			break;
		case 2:
			twos++;
			sum += 2;
			break;
		case 3:
			threes++;
			sum += 3;
			break;
		case 4:
			fours++;
			sum += 4;
			break;
		case 5:
			fives++;
			sum += 5;
			break;
		case 6:
			sixes++;
			sum += 6;
			break;
		}
	}

    int ofAKind = std::max({ ones, twos, threes, fours, fives, sixes });

    //Ones
    if (ones == 0) {
        sum += 0;
        if (!combinationClicked[0]) {
            combinationText[0].setFillColor(sf::Color::White);
            combinationScore[0].setFillColor(sf::Color::White);
            combinationScore[0].setString(std::to_string(0));
        }
        else {
            combinationText[0].setFillColor(sf::Color::Yellow);
        }
    }
    else {
        if (!combinationClicked[0]) {
            combinationScore[0].setString(std::to_string(ones * 1));
            ones * 1;

            combinationText[0].setFillColor(sf::Color::Yellow);
        }
    }

    if (combinationClicked[0]) {
        combinationText[0].setFillColor(sf::Color::Red);
        combinationClicked[0] = true; // установка флага в true
    }




    //Twos
    if (twos == 0) {
        sum += 0;
        if (!combinationClicked[1]) {
            combinationText[1].setFillColor(sf::Color::White);
            combinationScore[1].setFillColor(sf::Color::White);
            combinationScore[1].setString(std::to_string(0));
        }
        else {
            combinationText[1].setFillColor(sf::Color::Yellow);
        }
    }
    else {
        if (!combinationClicked[1]) {
            combinationScore[1].setString(std::to_string(twos * 2));
            twos * 2;

            combinationText[1].setFillColor(sf::Color::Yellow);
        }
    }

    if (combinationClicked[1]) {
        combinationText[1].setFillColor(sf::Color::Red);
        combinationClicked[1] = true; // установка флага в true
    }

    //Threes
    if (threes == 0) {
        sum += 0;
        if (!combinationClicked[2]) {
            combinationText[2].setFillColor(sf::Color::White);
            combinationScore[2].setFillColor(sf::Color::White);
            combinationScore[2].setString(std::to_string(0));
        }
        else {
            combinationText[2].setFillColor(sf::Color::Yellow);
        }
    }
    else {
        if (!combinationClicked[2]) {
            combinationScore[2].setString(std::to_string(threes * 3));
            threes * 3;

            combinationText[2].setFillColor(sf::Color::Yellow);
        }
    }

    if (combinationClicked[2]) {
        combinationText[2].setFillColor(sf::Color::Red);
        combinationClicked[2] = true; // установка флага в true
    }

    //Fours
    if (fours == 0) {
        sum += 0;
        if (!combinationClicked[3]) {
            combinationText[3].setFillColor(sf::Color::White);
            combinationScore[3].setFillColor(sf::Color::White);
            combinationScore[3].setString(std::to_string(0));
        }
        else {
            combinationText[3].setFillColor(sf::Color::Yellow);
        }
    }
    else {
        if (!combinationClicked[3]) {
            combinationScore[3].setString(std::to_string(fours * 4));
            fours * 4;

            combinationText[3].setFillColor(sf::Color::Yellow);
        }
    }

    if (combinationClicked[3]) {
        combinationText[3].setFillColor(sf::Color::Red);
        combinationClicked[3] = true; // установка флага в true
    }

    //Fives
    if (fives == 0) {
        sum += 0;
        if (!combinationClicked[4]) {
            combinationText[4].setFillColor(sf::Color::White);
            combinationScore[4].setFillColor(sf::Color::White);
            combinationScore[4].setString(std::to_string(0));
        }
        else {
            combinationText[4].setFillColor(sf::Color::Yellow);
        }
    }
    else {
        if (!combinationClicked[4]) {
            combinationScore[4].setString(std::to_string(fives * 5));
            fives * 5;

            combinationText[4].setFillColor(sf::Color::Yellow);
        }
    }

    if (combinationClicked[4]) {
        combinationText[4].setFillColor(sf::Color::Red);
        combinationClicked[4] = true; // установка флага в true
    }

    //Sixes
    if (sixes == 0) {
        sum += 0;
        if (!combinationClicked[5]) {
            combinationText[5].setFillColor(sf::Color::White);
            combinationScore[5].setFillColor(sf::Color::White);
            combinationScore[5].setString(std::to_string(0));
        }
        else {
            combinationText[5].setFillColor(sf::Color::Yellow);
        }
    }
    else {
        if (!combinationClicked[5]) {
            combinationScore[5].setString(std::to_string(sixes * 6));
            sixes * 6;

            combinationText[5].setFillColor(sf::Color::Yellow);
        }
    }

    if (combinationClicked[5]) {
        combinationText[5].setFillColor(sf::Color::Red);
        combinationClicked[5] = true; // установка флага в true
    }

    //Yahtzee
    if (ofAKind == 5) {
        if (!combinationClicked[12]) {
            combinationScore[12].setString(std::to_string(50));
            combinationText[12].setFillColor(sf::Color::Yellow);
        }
    }
    else {
        if (!combinationClicked[12]) {
            combinationText[12].setFillColor(sf::Color::White);
            combinationScore[12].setFillColor(sf::Color::White);
            combinationScore[12].setString(std::to_string(0));
        }
        else {
            combinationText[12].setFillColor(sf::Color::Red);
            combinationClicked[12] = true;
        }
    }

    //Full House
    if (ofAKind >= 3 && ((ones >= 2 && twos >= 2) || (ones >= 2 && threes >= 2) || (ones >= 2 && fours >= 2) || (ones >= 2 && fives >= 2) || (ones >= 2 && sixes >= 2) ||
        (twos >= 2 && ones >= 2) || (twos >= 2 && threes >= 2) || (twos >= 2 && fours >= 2) || (twos >= 2 && fives >= 2) || (twos >= 2 && sixes >= 2) ||
        (threes >= 2 && ones >= 2) || (threes >= 2 && twos >= 2) || (threes >= 2 && fours >= 2) || (threes >= 2 && fives >= 2) || (threes >= 2 && sixes >= 2) ||
        (fours >= 2 && ones >= 2) || (fours >= 2 && twos >= 2) || (fours >= 2 && threes >= 2) || (fours >= 2 && fives >= 2) || (fours >= 2 && sixes >= 2) ||
        (fives >= 2 && ones >= 2) || (fives >= 2 && twos >= 2) || (fives >= 2 && threes >= 2) || (fives >= 2 && fours >= 2) || (fives >= 2 && sixes >= 2) ||
        (sixes >= 2 && ones >= 2) || (sixes >= 2 && twos >= 2) || (sixes >= 2 && threes >= 2) || (sixes >= 2 && fours >= 2) || (sixes >= 2 && fives >= 2))) {

        if (!combinationClicked[8]) {
            combinationScore[8].setString(std::to_string(25));
            combinationText[8].setFillColor(sf::Color::Yellow);

        }
    }
    else {
        if (!combinationClicked[8]) {
            combinationText[8].setFillColor(sf::Color::White);
            combinationScore[8].setFillColor(sf::Color::White);
            combinationScore[8].setString(std::to_string(0));
        }
        else {
            combinationText[8].setFillColor(sf::Color::Red);
            combinationClicked[8] = true;
        }
    }

    //Small Straight
    if ((ones >= 1 && twos >= 1 && threes >= 1 && fours >= 1) ||
        (twos >= 1 && threes >= 1 && fours >= 1 && fives >= 1) ||
        (threes >= 1 && fours >= 1 && fives >= 1 && sixes >= 1))
    {
        if (!combinationClicked[9]) {
            combinationScore[9].setString(std::to_string(30));
            combinationText[9].setFillColor(sf::Color::Yellow);

        }
    }
    else {
        if (!combinationClicked[9]) {
            combinationText[9].setFillColor(sf::Color::White);
            combinationScore[9].setFillColor(sf::Color::White);
            combinationScore[9].setString(std::to_string(0));
        }
        else {
            combinationText[9].setFillColor(sf::Color::Red);
            combinationClicked[9] = true;
        }
    }

    //Large Straight
    if (ones >= 1 && twos >= 1 && threes >= 1 && fours >= 1 && fives >= 1 || twos >= 1 && threes >= 1 && fours >= 1 && fives >= 1 && sixes >= 1)
    {
        if (!combinationClicked[10]) {
            combinationScore[10].setString(std::to_string(40));
            combinationText[10].setFillColor(sf::Color::Yellow);

        }
    }
    else {
        if (!combinationClicked[10]) {
            combinationText[10].setFillColor(sf::Color::White);
            combinationScore[10].setFillColor(sf::Color::White);
            combinationScore[10].setString(std::to_string(0));
        }
        else {
            combinationText[10].setFillColor(sf::Color::Red);
            combinationClicked[10] = true;
        }
    }

    //Three of a Kind доделать
    if (ofAKind >= 3)
    {
        if (!combinationClicked[6]) {
            combinationScore[6].setString(std::to_string(sum));
            combinationText[6].setFillColor(sf::Color::Yellow);

        }
    }
    else {
        if (!combinationClicked[6]) {
            combinationText[6].setFillColor(sf::Color::White);
            combinationScore[6].setFillColor(sf::Color::White);
            combinationScore[6].setString(std::to_string(0));
        }
        else {
            combinationText[6].setFillColor(sf::Color::Red);
            combinationClicked[6] = true;
        }
    }


    //Four of a Kind доделать
    if (ofAKind >= 4)
    {
        if (!combinationClicked[7]) {
            combinationScore[7].setString(std::to_string(sum));
            combinationText[7].setFillColor(sf::Color::Yellow);

        }
    }
    else {
        if (!combinationClicked[7]) {
            combinationText[7].setFillColor(sf::Color::White);
            combinationScore[7].setFillColor(sf::Color::White);
            combinationScore[7].setString(std::to_string(0));
        }
        else {
            combinationText[7].setFillColor(sf::Color::Red);
            combinationClicked[7] = true;
        }
    }

    //Chance доделать
    if (sum)
    {
        if (!combinationClicked[11]) {
            combinationScore[11].setString(std::to_string(sum));
            combinationText[11].setFillColor(sf::Color::Yellow);

        }
    }
    else {
        if (!combinationClicked[11]) {
            combinationText[11].setFillColor(sf::Color::White);
            combinationScore[11].setFillColor(sf::Color::White);
            combinationScore[11].setString(std::to_string(sum));
        }
        else {
            combinationText[11].setFillColor(sf::Color::Red);
            combinationClicked[11] = true;
        }
    }
    return "Chance: " + std::to_string(sum);
}