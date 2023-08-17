#ifndef RESOURCES_H
#define RESOURCES_H

#include <SFML/Graphics.hpp>

extern sf::Texture texture;
extern sf::Sprite cube;
extern int arrAnimation[6];
extern sf::Font font;
extern sf::Text text;
extern sf::RectangleShape blockRect;
extern sf::Text textHeading;
extern sf::Texture background;
extern sf::Sprite spriteBackground;
extern sf::Texture textureDiceRoll;
extern sf::Sprite spriteDiceRoll;
extern sf::Text rollText;
extern sf::Texture textureRetryButton;
extern sf::Sprite spriteRetryButton;

void loadResources();

#endif
