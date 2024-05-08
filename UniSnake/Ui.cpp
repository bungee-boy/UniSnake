#include "Ui.h"

const int Ui::RectWidth{ 8 };
const int Ui::RectBorder{ 3 };
const sf::Color Ui::RectInnerCol{ 120, 120, 120, 255 };
const sf::Color Ui::RectOuterCol{ 50, 50, 50, 255 };

bool Ui::loadFont(const std::string fontName) {
	sf::Font newFont;
	if (!newFont.loadFromFile("fonts\\" + fontName + ".ttf")) {
		std::cerr << "Ui::loadFont(fontName) -> Failed to load font file! (" + fontName + ".ttf)\n";
		return false;
	}
	m_fonts.insert({ fontName, newFont });
	return true;
}

void Ui::unloadFonts() {

}

sf::Text* Ui::addText(const std::string txt, const std::string fontName, const sf::Vector2f pos, const bool center, const unsigned int size, const unsigned int style) {
	if (!m_fonts.count(fontName)) {  // If font is not loaded
		if (!loadFont(fontName))  // Try to load new font
			return new sf::Text();  // If fails, return
	}
	sf::Text* newText = new sf::Text(txt, m_fonts[fontName], size);  // Create text
	newText->setPosition({ (center) ? pos.x - newText->getGlobalBounds().width / 2 : pos.x, pos.y});  // Set position (with centering)
	newText->setStyle(style);
	m_textList.push_back(newText);  // Add text to list (to be drawn)
	return newText;
}

void Ui::clearTexts() {
	m_textList.clear();
}

sf::FloatRect Ui::addRect(const sf::Vector2f pos, const sf::Vector2f size, const sf::Color fillColour, const sf::Color outlineColour, const float thickness) {
	sf::RectangleShape* newRect = new sf::RectangleShape(size);
	newRect->setPosition(pos);
	newRect->setFillColor(fillColour);
	newRect->setOutlineThickness(thickness);
	newRect->setOutlineColor(outlineColour);
	m_rectList.push_back(newRect);
	return newRect->getGlobalBounds();
}

sf::FloatRect Ui::addLineX(const sf::Vector2f startPos, const unsigned int xSize, const sf::Color fillColour, const sf::Color outlineColour) {
	return addRect(startPos, { static_cast<float>(xSize), RectWidth }, fillColour, outlineColour, -RectBorder);
}

sf::FloatRect Ui::addLineY(const sf::Vector2f startPos, const unsigned int ySize, const sf::Color fillColour, const sf::Color outlineColour) {
	return addRect(startPos, { RectWidth, static_cast<float>(ySize) }, fillColour, outlineColour, -RectBorder);
}

void Ui::clearRects() {
	m_rectList.clear();
}

bool Ui::loadTexture(const std::string textureName) {
	sf::Texture* newTexture = new sf::Texture;
	if (!newTexture->loadFromFile("textures\\" + textureName + ".png")) {  // Load texture
		std::cerr << "Ui::loadTexture(textureName) -> Failed to load" + textureName + ".png" << '\n';
		return false;
	}
	newTexture->setSmooth(true);
	m_textures.insert({ textureName, newTexture });
	return true;
}

void Ui::unloadTextures() {

}

sf::FloatRect Ui::addRectTexture(const std::string textureName, const sf::Vector2f pos, const sf::Vector2f size, const float rotation, const sf::Color colour, const bool center) {
	if (!m_textures.count(textureName)) {  // If texture is not loaded
		if (!loadTexture(textureName))  // Attempt to load texture
			return { 0.0f, 0.0f, 0.0f, 0.0f };  // Return if failed
	}

	sf::RectangleShape* newRect = new sf::RectangleShape(size);
	newRect->setPosition(pos);
	newRect->setRotation(rotation);
	newRect->setTexture(m_textures[textureName]);
	newRect->setFillColor(colour);
	if (center)
		newRect->setOrigin(size.x / 2, size.y / 2);
	m_rectList.push_back(newRect);
	return newRect->getGlobalBounds();
}

void Ui::clearAll() {
	clearRects();
	clearTexts();
}

void Ui::update() {

}

void Ui::draw(sf::RenderWindow* window) {
	ListNode<sf::RectangleShape*>* currRect = m_rectList.getHead();  // Draw rects
	while (currRect != nullptr) {
		window->draw(*currRect->data);
		currRect = currRect->next;
	}
	ListNode<sf::Text*>* currText = m_textList.getHead();  // Draw text
	while (currText != nullptr) {
		window->draw(*currText->data);
		currText = currText->next;
	}
}
