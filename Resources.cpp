#include "resources.h"

sf::Texture texture;
sf::Sprite cube;
int arrAnimation[6] = { -5, 120, 250, 380, 500, 640 };
sf::Font font;
sf::Text text;
sf::RectangleShape blockRect;
sf::Text textHeading;
sf::Texture background;
sf::Sprite spriteBackground;
sf::Texture textureDiceRoll;
sf::Sprite spriteDiceRoll;
sf::Text rollText;
sf::Texture textureRetryButton;
sf::Sprite spriteRetryButton;

void loadResources() {

    texture.loadFromFile("resources/animation.png");
    cube.setTexture(texture);

    font.loadFromFile("resources/font16.ttf");

    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);

    blockRect.setSize(sf::Vector2f(140, 140));
    blockRect.setFillColor(sf::Color::Transparent);
    blockRect.setOutlineThickness(3);
    blockRect.setOutlineColor(sf::Color::Red);

    textHeading.setString("Yahtzee");
    textHeading.setFont(font);
    textHeading.setCharacterSize(48);
    textHeading.setFillColor(sf::Color::White);
    textHeading.setOrigin(textHeading.getLocalBounds().width / 2, textHeading.getLocalBounds().height / 2);
    textHeading.setPosition(sf::Vector2f(450, 50));

    background.loadFromFile("resources/background.jpg");

    spriteBackground.setTexture(background);

    textureDiceRoll.loadFromFile("resources/RollDice.png");

    spriteDiceRoll.setTexture(textureDiceRoll);
    spriteDiceRoll.setScale(0.3f, 0.3f); //изменение размера спрайта
    spriteDiceRoll.setPosition(670, 450);

    rollText.setFont(font); // Задаем шрифт
    rollText.setString("Roll"); // Задаем текст
    rollText.setCharacterSize(24); // Задаем размер шрифта
    rollText.setFillColor(sf::Color::White); // Задаем цвет текста
    rollText.setPosition(spriteDiceRoll.getPosition().x - -5, spriteDiceRoll.getPosition().y - -120); // Задаем позицию текста


    // Загрузка и настройка других ресурсов
}
