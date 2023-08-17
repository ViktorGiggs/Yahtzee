#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "Cube.h"
#include "YahtzeeCombination.h"
#include "resources.h"


Cube cubes[5]; // ���������� ���������� ��� ������� �������� ������ Cube

int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 700), "Yahtzee");
    sf::Image icon;
    icon.loadFromFile("resources/ico.png");
    window.setIcon(32, 32, icon.getPixelsPtr());

    loadResources();

    // ������������� ��������� ���������� ������� � ����������� �� ������
    int arrAnimation[6] = { -5, 120, 250, 380, 500, 640 }; // ������ �������� ������� ��� ������� �������� ������
    int x = 50; // ��������� ������� ������ �� ��� X

    // �������� � ����������� ���� �������
    for (int i = 0; i < 5; i++) {
        cube.setPosition(x, 300); // ��������� ������� ������
        window.draw(cube); // ����������� ������ �� ������
        cubes[i].front = 0; // ��������� �������� ����� ������ � 0 (��������� ��������)
        x += 150; // ���������� �������� X ��� ���������� ������
    }

    // ���������� � ����������� ��������� ����� ��� ����������
    for (int i = 0; i < numCombinations; i++) {
        combinationText[i].setString(combinationNames[i]); // ��������� ������ ��� ���� ����������
        combinationText[i].setFont(font); // ��������� ������ ��� ���� ����������
        combinationText[i].setCharacterSize(20); // ��������� ������� ������ ��� ���� ����������
        combinationText[i].setFillColor(sf::Color::White); // ��������� ����� ������ ��� ���� ����������
        combinationText[i].setPosition(100, 300 + i * 30); // ��������� ������� ���� ���������� �� ������

        combinationScore[i].setFont(font); // ��������� ������ ��� ���� ����� ����������
        combinationScore[i].setCharacterSize(20); // ��������� ������� ������ ��� ���� ����� ����������
        combinationScore[i].setFillColor(sf::Color::White); // ��������� ����� ������ ��� ���� ����� ����������
        combinationScore[i].setPosition(500, 300 + i * 30); // ��������� ������� ���� ����� ���������� �� ������
    }


    bool isSpinning = false; // ����, �����������, ��������� �� ������ � ������ ������
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime; // ����� ������ ���� ��� �������� �������
    std::vector<int> clickedCubes; // ������, ���������� ������� �������, �� ������� ��� �������� ������

    bool gameStarted = false; // ����, ����������� �� ������ ����
    int countRolls = 0; // ������� ���������� ������� �������
    bool allRed = false; // ���� ��� ������������ ����, ��� ��� ���������� �������� ��������
    bool combinationSelected = false; // ����, �����������, ������� �� ����������
    bool combinationLocked = false; // ���� ���������� ��������� ����������
    int selectedCombinationIndex = -1; // ������ ��������� ���������� (-1, ���� ���������� �� �������)

    bool startScreen = true; // ����, �����������, ��� ������������ ��������� �����

    sf::Clock textBlinkClock; // ���� ��� ������� ������
    bool drawText = true; // ����, �����������, ����� �� ���������� �����
    bool cubesThrown = false; // ����, �����������, ���� �� ������� ������


    // ����, ���������� �� ����������� ���������� ������, �� ������� ������ �������
    while (startScreen)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                startScreen = false;
            }
        }

        // ��������� ����
        window.draw(spriteBackground);

        // ������� ������
        if (textBlinkClock.getElapsedTime().asMilliseconds() >= 500)
        {
            drawText = !drawText;
            textBlinkClock.restart();
        }
        if (drawText)
        {
            // ��������� �������� �������
            sf::Text startText("Press space bar to start", font, 36);
            startText.setFillColor(sf::Color::White);
            startText.setOrigin(startText.getLocalBounds().width / 2, startText.getLocalBounds().height / 2);
            startText.setPosition(window.getView().getCenter());
            window.draw(startText);
        }

        window.display();
        window.clear();
    }


    while (window.isOpen())
    {
        // ��������� �������

        sf::Event event;
        while (window.pollEvent(event))
        {
            // �������� ����
            if (event.type == sf::Event::Closed)
                window.close();

            // ��������� ������� ������� �������
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (!cubesThrown) { // ���������, ��� ������ �� ���� �������
                    gameStarted = true;
                    if (countRolls < 3) {
                        isSpinning = true;
                        startTime = std::chrono::high_resolution_clock::now();
                        countRolls++;
                    }
                }
            }

            // ��������� ������� ����� ������ ����
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

                // ��������, ��� ������� ��������� ������ �������
                if (spriteDiceRoll.getGlobalBounds().contains(worldPos)) {
                    gameStarted = true;
                    if (countRolls < 3) {
                        isSpinning = true;
                        startTime = std::chrono::high_resolution_clock::now();
                        countRolls++;

                        // ��������� ������� ������� �� 10%
                        spriteDiceRoll.setScale(0.29f, 0.29f);
                    }
                }

                // ��������� ������� �� ������
                if (gameStarted && countRolls < 3) {
                    for (int i = 0; i < 5; i++) {
                        int xPos = 50 + i * 150;
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                        // ��������, ��� ������� ��������� �� ���������� ������
                        if (mousePos.x >= xPos && mousePos.x <= xPos + 140
                            && mousePos.y >= 300 - 200 && mousePos.y <= 300) {
                            cubes[i].isBlocked = !cubes[i].isBlocked;
                            break;
                        }
                    }
                }
            }

            // ��������� ���������� ����� ������ ����
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                if (gameStarted) {
                    // ��������������� �������� ������� �������
                    spriteDiceRoll.setScale(0.3f, 0.3f);
                }
            }
        }


        // ��������� �������� ��������

        if (isSpinning) {
            combinationLocked = false;

            // ��������� ����� ������ ���������� � �����
            for (int i = 0; i < NUM_COMBINATIONS; i++) {
                combinationText[i].setFillColor(sf::Color::White);
                combinationScore[i].setFillColor(sf::Color::White);
            }

            // ��������� �������� �������
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

            // ��������, ������ �� ��� 1 �������
            if (elapsed.count() >= 1) {
                isSpinning = false;
            }
            else {
                // ��������� ���������� ����� ��� ������� ���������������� ������
                for (int i = 0; i < 5; i++) {
                    if (!cubes[i].isBlocked) {
                        cubes[i].front = rand() % 6 + 1;
                    }
                }
            }
        }


        // ��������� ������� �� ����������

        if (!isSpinning) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (gameStarted && countRolls <= 3) { // ���������, ��� ������ ���� �������
                        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                        // ���������, �� ����� ���������� ���� ����������� �������
                        for (int i = 0; i < NUM_COMBINATIONS; i++) {
                            sf::FloatRect bounds = combinationText[i].getGlobalBounds();

                            // ���� ������� ��������� � �������� ����������
                            if (bounds.contains(mousePosition.x, mousePosition.y)) {
                                if (combinationLocked) {
                                    // ���� ��������� ���������� �������������, �� ������ �� ������
                                    break;
                                }
                                if (combinationClicked[i]) {
                                    // ���� ���������� ��� �������, �� ������ �� ������
                                    break;
                                }
                                if (combinationSelected) {
                                    if (i == selectedCombinationIndex) {
                                        combinationLocked = true; // ��������� ��������� ����������
                                        combinationClicked[i] = true;
                                        combinationText[i].setFillColor(sf::Color::Red);
                                        combinationScore[i].setFillColor(sf::Color::Red);
                                    }
                                    else {
                                        // ���������� ���������� ��������� ��������� ����������
                                        combinationClicked[i] = false;
                                        combinationText[i].setFillColor(sf::Color::White);
                                        combinationScore[i].setFillColor(sf::Color::White);
                                        combinationSelected = false;
                                        selectedCombinationIndex = -1;
                                    }
                                }
                                else {
                                    // ������������� ��������� ��������� ����������
                                    combinationClicked[i] = true;
                                    combinationText[i].setFillColor(sf::Color::Red);
                                    combinationScore[i].setFillColor(sf::Color::Red);
                                    countRolls = 0;
                                    gameStarted = false;

                                    // ���������� ��������� �������
                                    for (int j = 0; j < 5; j++) {
                                        cubes[j].isBlocked = false;
                                    }

                                    combinationSelected = true;
                                    selectedCombinationIndex = i;
                                }
                            }
                        }
                    }
                }
            }



            // ���������� �����, ���������� � ������ �����

            int sum = countDroppedNumbers(cubes); // ��������� ����� �������� ����� �� �������
            std::vector<int> frontValues = getFrontValues(cubes); // �������� �������� �������� ������ �������
            std::string combination = checkCombination(frontValues); // ��������� ���������� �� ������ �������� ��������
            int score = countDroppedNumbers(cubes); // ��������� ���� �� ������ �������� ����� �� �������

            int totalScore = 0;
            for (int i = 0; i < 13; i++) {
                if (combinationClicked[i] && combinationText[i].getFillColor() == sf::Color::Red) {
                    totalScore += std::stoi(combinationScore[i].getString().toAnsiString()); // ��������� ���� �� ��������� � ���������� ����������
                }
            }

            allRed = true;
            for (int i = 0; i < NUM_COMBINATIONS; i++) {
                if (combinationScore[i].getFillColor() != sf::Color::Red) {
                    allRed = false; // ���������, ��� �� ���������� �������� ������� ������
                    break;
                }
            }

            if (allRed) {

                // ������� ����� � ������ ������ ���
                window.clear();
                window.draw(spriteBackground);

                // ������� ����� � ����� ����������� �����
                sf::Text totalScoreText;
                totalScoreText.setString("Total Score: " + std::to_string(totalScore));
                totalScoreText.setFont(font);
                totalScoreText.setCharacterSize(24);
                totalScoreText.setOrigin(totalScoreText.getLocalBounds().width / 2, totalScoreText.getLocalBounds().height / 2);
                totalScoreText.setPosition(window.getView().getCenter());


                // ���������� ����� � ��������� �����
                window.clear();
                window.draw(spriteBackground);
                window.draw(totalScoreText);
                window.display();

                // ���������� ������� ������� � ���������� ����
                countRolls = 3;
                continue;
            }

        }


        window.clear(); // ������� ����������� ����

        x = 50; // ������������� ���������� x

        window.draw(spriteBackground); // ��������� ������� ����

        for (int i = 0; i < 5; i++) {
            cube.setTextureRect(sf::IntRect(arrAnimation[cubes[i].front - 1], 0, 140, 140)); // ��������� ������������� ������� �������� ��� ������
            cube.setPosition(x + 30, 300 - 200); // ��������� ������� ������
            window.draw(cube); // ��������� ������

            text.setString(std::to_string(cubes[i].front)); // ��������� ������ ��� ����������� �������� ������
            text.setPosition(x + 85, 250); // ��������� ������� ������
            window.draw(text); // ��������� ������

            if (cubes[i].isBlocked) {
                blockRect.setPosition(x + 30, 300 - 200); // ��������� ������� ������������ ��������������
                window.draw(blockRect); // ��������� ������������ ��������������
            }

            x += 150; // ���������� �������� x ��� ���������� ������
        }


        // ��������� ��������� ����������

        window.draw(spriteDiceRoll); // ��������� ������� ������ "Roll Dice"
        window.draw(rollText); // ��������� ������ �� ������

        for (int i = 0; i < numCombinations; i++) {
            window.draw(combinationText[i]); // ��������� ������ ����������
            window.draw(combinationScore[i]); // ��������� ������ ����� ����������
        }

        for (int i = 0; i < NUM_COMBINATIONS; i++) {
            if (combinationClicked[i]) {
                combinationText[i].setFillColor(sf::Color::Red); // ��������� ����� ������ ��������� ���������� � �������
                combinationScore[i].setFillColor(sf::Color::Red); // ��������� ����� ������ ����� ��������� ���������� � �������
            }
            else {
                combinationText[i].setFillColor(sf::Color::Yellow); // ��������� ����� ������ ��������� ���������� � ������
                combinationScore[i].setFillColor(sf::Color::Yellow); // ��������� ����� ������ ����� ��������� ���������� � ������
            }
        }

        window.draw(textHeading);
        window.display();

    }
    return 0;
}