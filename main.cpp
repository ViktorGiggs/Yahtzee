#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "Cube.h"
#include "YahtzeeCombination.h"
#include "resources.h"


Cube cubes[5]; // Глобальная переменная для массива объектов класса Cube

int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 700), "Yahtzee");
    sf::Image icon;
    icon.loadFromFile("resources/ico.png");
    window.setIcon(32, 32, icon.getPixelsPtr());

    loadResources();

    // Инициализация начальных параметров кубиков и отображение на экране
    int arrAnimation[6] = { -5, 120, 250, 380, 500, 640 }; // Массив смещений текстур для каждого значения кубика
    int x = 50; // Начальная позиция кубика по оси X

    // Создание и отображение пяти кубиков
    for (int i = 0; i < 5; i++) {
        cube.setPosition(x, 300); // Установка позиции кубика
        window.draw(cube); // Отображение кубика на экране
        cubes[i].front = 0; // Установка значения грани кубика в 0 (начальное значение)
        x += 150; // Увеличение значения X для следующего кубика
    }

    // Заполнение и отображение текстовых полей для комбинаций
    for (int i = 0; i < numCombinations; i++) {
        combinationText[i].setString(combinationNames[i]); // Установка текста для поля комбинации
        combinationText[i].setFont(font); // Установка шрифта для поля комбинации
        combinationText[i].setCharacterSize(20); // Установка размера шрифта для поля комбинации
        combinationText[i].setFillColor(sf::Color::White); // Установка цвета текста для поля комбинации
        combinationText[i].setPosition(100, 300 + i * 30); // Установка позиции поля комбинации на экране

        combinationScore[i].setFont(font); // Установка шрифта для поля счета комбинации
        combinationScore[i].setCharacterSize(20); // Установка размера шрифта для поля счета комбинации
        combinationScore[i].setFillColor(sf::Color::White); // Установка цвета текста для поля счета комбинации
        combinationScore[i].setPosition(500, 300 + i * 30); // Установка позиции поля счета комбинации на экране
    }


    bool isSpinning = false; // Флаг, указывающий, вращаются ли кубики в данный момент
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime; // Время начала игры или вращения кубиков
    std::vector<int> clickedCubes; // Вектор, содержащий индексы кубиков, по которым был выполнен щелчок

    bool gameStarted = false; // Флаг, указывающий на начало игры
    int countRolls = 0; // Счетчик количества бросков кубиков
    bool allRed = false; // Флаг для отслеживания того, что все комбинации являются красными
    bool combinationSelected = false; // Флаг, указывающий, выбрана ли комбинация
    bool combinationLocked = false; // Флаг блокировки выбранной комбинации
    int selectedCombinationIndex = -1; // Индекс выбранной комбинации (-1, если комбинация не выбрана)

    bool startScreen = true; // Флаг, указывающий, что отображается стартовый экран

    sf::Clock textBlinkClock; // Часы для мигания текста
    bool drawText = true; // Флаг, указывающий, нужно ли отображать текст
    bool cubesThrown = false; // Флаг, указывающий, были ли брошены кубики


    // Цикл, отвечающий за отображение стартового экрана, на котором мигает надпись
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

        // Отрисовка фона
        window.draw(spriteBackground);

        // Мигание текста
        if (textBlinkClock.getElapsedTime().asMilliseconds() >= 500)
        {
            drawText = !drawText;
            textBlinkClock.restart();
        }
        if (drawText)
        {
            // Отрисовка мигающей надписи
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
        // Обработка событий

        sf::Event event;
        while (window.pollEvent(event))
        {
            // Закрытие окна
            if (event.type == sf::Event::Closed)
                window.close();

            // Обработка нажатия клавиши пробела
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (!cubesThrown) { // Проверяем, что кубики не были брошены
                    gameStarted = true;
                    if (countRolls < 3) {
                        isSpinning = true;
                        startTime = std::chrono::high_resolution_clock::now();
                        countRolls++;
                    }
                }
            }

            // Обработка нажатия левой кнопки мыши
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

                // Проверка, что нажатие произошло внутри спрайта
                if (spriteDiceRoll.getGlobalBounds().contains(worldPos)) {
                    gameStarted = true;
                    if (countRolls < 3) {
                        isSpinning = true;
                        startTime = std::chrono::high_resolution_clock::now();
                        countRolls++;

                        // Уменьшаем масштаб спрайта на 10%
                        spriteDiceRoll.setScale(0.29f, 0.29f);
                    }
                }

                // Обработка нажатия на кубики
                if (gameStarted && countRolls < 3) {
                    for (int i = 0; i < 5; i++) {
                        int xPos = 50 + i * 150;
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                        // Проверка, что нажатие произошло на конкретном кубике
                        if (mousePos.x >= xPos && mousePos.x <= xPos + 140
                            && mousePos.y >= 300 - 200 && mousePos.y <= 300) {
                            cubes[i].isBlocked = !cubes[i].isBlocked;
                            break;
                        }
                    }
                }
            }

            // Обработка отпускания левой кнопки мыши
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                if (gameStarted) {
                    // Восстанавливаем исходный масштаб спрайта
                    spriteDiceRoll.setScale(0.3f, 0.3f);
                }
            }
        }


        // Обработка анимации вращения

        if (isSpinning) {
            combinationLocked = false;

            // Установка цвета текста комбинаций в белый
            for (int i = 0; i < NUM_COMBINATIONS; i++) {
                combinationText[i].setFillColor(sf::Color::White);
                combinationScore[i].setFillColor(sf::Color::White);
            }

            // Получение текущего времени
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

            // Проверка, прошло ли уже 1 секунда
            if (elapsed.count() >= 1) {
                isSpinning = false;
            }
            else {
                // Генерация случайного числа для каждого неблокированного кубика
                for (int i = 0; i < 5; i++) {
                    if (!cubes[i].isBlocked) {
                        cubes[i].front = rand() % 6 + 1;
                    }
                }
            }
        }


        // Обработка нажатия на комбинации

        if (!isSpinning) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (gameStarted && countRolls <= 3) { // Проверяем, что кубики были брошены
                        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                        // Проверяем, на какую комбинацию было произведено нажатие
                        for (int i = 0; i < NUM_COMBINATIONS; i++) {
                            sf::FloatRect bounds = combinationText[i].getGlobalBounds();

                            // Если нажатие произошло в пределах комбинации
                            if (bounds.contains(mousePosition.x, mousePosition.y)) {
                                if (combinationLocked) {
                                    // Если выбранная комбинация заблокирована, то ничего не делаем
                                    break;
                                }
                                if (combinationClicked[i]) {
                                    // Если комбинация уже выбрана, то ничего не делаем
                                    break;
                                }
                                if (combinationSelected) {
                                    if (i == selectedCombinationIndex) {
                                        combinationLocked = true; // блокируем выбранную комбинацию
                                        combinationClicked[i] = true;
                                        combinationText[i].setFillColor(sf::Color::Red);
                                        combinationScore[i].setFillColor(sf::Color::Red);
                                    }
                                    else {
                                        // Сбрасываем предыдущее состояние выбранной комбинации
                                        combinationClicked[i] = false;
                                        combinationText[i].setFillColor(sf::Color::White);
                                        combinationScore[i].setFillColor(sf::Color::White);
                                        combinationSelected = false;
                                        selectedCombinationIndex = -1;
                                    }
                                }
                                else {
                                    // Устанавливаем состояние выбранной комбинации
                                    combinationClicked[i] = true;
                                    combinationText[i].setFillColor(sf::Color::Red);
                                    combinationScore[i].setFillColor(sf::Color::Red);
                                    countRolls = 0;
                                    gameStarted = false;

                                    // Сбрасываем состояние кубиков
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



            // Вычисление суммы, комбинации и общего счета

            int sum = countDroppedNumbers(cubes); // Вычисляем сумму выпавших чисел на кубиках
            std::vector<int> frontValues = getFrontValues(cubes); // Получаем значения передних граней кубиков
            std::string combination = checkCombination(frontValues); // Проверяем комбинацию на основе передних значений
            int score = countDroppedNumbers(cubes); // Вычисляем счет на основе выпавших чисел на кубиках

            int totalScore = 0;
            for (int i = 0; i < 13; i++) {
                if (combinationClicked[i] && combinationText[i].getFillColor() == sf::Color::Red) {
                    totalScore += std::stoi(combinationScore[i].getString().toAnsiString()); // Суммируем очки за выбранные и отмеченные комбинации
                }
            }

            allRed = true;
            for (int i = 0; i < NUM_COMBINATIONS; i++) {
                if (combinationScore[i].getFillColor() != sf::Color::Red) {
                    allRed = false; // Проверяем, все ли комбинации отмечены красным цветом
                    break;
                }
            }

            if (allRed) {

                // очищаем экран и рисуем только фон
                window.clear();
                window.draw(spriteBackground);

                // выводим текст с общим количеством очков
                sf::Text totalScoreText;
                totalScoreText.setString("Total Score: " + std::to_string(totalScore));
                totalScoreText.setFont(font);
                totalScoreText.setCharacterSize(24);
                totalScoreText.setOrigin(totalScoreText.getLocalBounds().width / 2, totalScoreText.getLocalBounds().height / 2);
                totalScoreText.setPosition(window.getView().getCenter());


                // отображаем текст и обновляем экран
                window.clear();
                window.draw(spriteBackground);
                window.draw(totalScoreText);
                window.display();

                // сбрасываем счетчик бросков и продолжаем игру
                countRolls = 3;
                continue;
            }

        }


        window.clear(); // Очистка содержимого окна

        x = 50; // Инициализация переменной x

        window.draw(spriteBackground); // Отрисовка спрайта фона

        for (int i = 0; i < 5; i++) {
            cube.setTextureRect(sf::IntRect(arrAnimation[cubes[i].front - 1], 0, 140, 140)); // Установка прямоугольной области текстуры для кубика
            cube.setPosition(x + 30, 300 - 200); // Установка позиции кубика
            window.draw(cube); // Отрисовка кубика

            text.setString(std::to_string(cubes[i].front)); // Установка текста для отображения значения кубика
            text.setPosition(x + 85, 250); // Установка позиции текста
            window.draw(text); // Отрисовка текста

            if (cubes[i].isBlocked) {
                blockRect.setPosition(x + 30, 300 - 200); // Установка позиции блокирующего прямоугольника
                window.draw(blockRect); // Отрисовка блокирующего прямоугольника
            }

            x += 150; // Увеличение значения x для следующего кубика
        }


        // Отрисовка элементов интерфейса

        window.draw(spriteDiceRoll); // Отрисовка спрайта кнопки "Roll Dice"
        window.draw(rollText); // Отрисовка текста на кнопке

        for (int i = 0; i < numCombinations; i++) {
            window.draw(combinationText[i]); // Отрисовка текста комбинаций
            window.draw(combinationScore[i]); // Отрисовка текста счета комбинаций
        }

        for (int i = 0; i < NUM_COMBINATIONS; i++) {
            if (combinationClicked[i]) {
                combinationText[i].setFillColor(sf::Color::Red); // Установка цвета текста выбранных комбинаций в красный
                combinationScore[i].setFillColor(sf::Color::Red); // Установка цвета текста счета выбранных комбинаций в красный
            }
            else {
                combinationText[i].setFillColor(sf::Color::Yellow); // Установка цвета текста остальных комбинаций в желтый
                combinationScore[i].setFillColor(sf::Color::Yellow); // Установка цвета текста счета остальных комбинаций в желтый
            }
        }

        window.draw(textHeading);
        window.display();

    }
    return 0;
}