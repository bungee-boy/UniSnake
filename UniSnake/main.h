#pragma once
#include <cmath>
#include <iostream>
#include "SFML\Graphics.hpp"

const unsigned int gWidth{ 1000 }, gHeight{ 1000 };  // Screen width, Screen height
unsigned int gFps{ 60 };  // FPS
const double pi{ 3.14159265359 };

sf::RectangleShape gRect;  // Load rect class
sf::CircleShape gCircle;  // Load circle class
sf::RenderWindow gWindow(sf::VideoMode(gWidth, gHeight), "Snake");  // Window (screen)
