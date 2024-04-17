#include "Ui.h"

const int Ui::RectWidth{ 8 };
const int Ui::RectBorder{ 3 };
const sf::Color Ui::RectInnerCol{ 120, 120, 120, 255 };
const sf::Color Ui::RectOuterCol{ 50, 50, 50, 255 };

bool Ui::loadFont(const std::string fontName) {
	sf::Font newFont;
	if (!newFont.loadFromFile(fontName + ".ttf")) {
		std::cerr << "Ui::loadFont(fontName) -> Failed to load font file! (" + fontName + ".ttf)\n";
		return false;
	}
	m_fonts.insert({ fontName, newFont });
	return true;
}

void Ui::unloadFonts() {

}

void Ui::addText(const std::string txt, const std::string fontName, const sf::Vector2f pos, const bool center, const unsigned int size, const unsigned int style) {
	if (!m_fonts.count(fontName)) {  // If font is not loaded
		if (!loadFont(fontName))  // Try to load new font
			return;  // If fails, return
	}
	sf::Text* newText = new sf::Text(txt, m_fonts[fontName], size);  // Create text
	newText->setPosition({ (center) ? pos.x - newText->getGlobalBounds().width / 2 : pos.x, pos.y});  // Set position (with centering)
	newText->setStyle(style);
	m_textList.push_back(newText);  // Add text to list (to be drawn)
}

void Ui::clearTexts() {
	m_textList.clear();
}

void Ui::addRect(const sf::Vector2f pos, const sf::Vector2f size, const sf::Color fillColour, const sf::Color outlineColour, const float thickness) {
	sf::RectangleShape* newRect = new sf::RectangleShape(size);
	newRect->setPosition(pos);
	newRect->setFillColor(fillColour);
	newRect->setOutlineThickness(thickness);
	newRect->setOutlineColor(outlineColour);
	m_rectList.push_back(newRect);
}

void Ui::addLineX(const sf::Vector2f startPos, const unsigned int xSize) {
	addRect(startPos, { static_cast<float>(xSize), RectWidth }, RectInnerCol, RectOuterCol, -RectBorder);
}

void Ui::addLineY(const sf::Vector2f startPos, const unsigned int ySize) {
	addRect(startPos, { RectWidth, static_cast<float>(ySize) }, RectInnerCol, RectOuterCol, -RectBorder);
}

void Ui::clearRects() {
	m_rectList.clear();
}

bool Ui::loadTexture(const std::string texture) {
	sf::Texture* newTexture = new sf::Texture;
	if (!newTexture->loadFromFile("textures\\" + texture)) {  // Load texture
		std::cerr << "Failed to load" << texture << '\n';
		return false;
	}
	newTexture->setSmooth(true);
	m_textures.insert({ texture, newTexture });
	return true;
}

void Ui::unloadTextures() {

}

void Ui::addRectTexture(const std::string texture, const sf::Vector2f pos, const sf::Vector2f size) {
	if (!m_textures.count(texture)) {  // If texture is not loaded
		if (!loadTexture(texture))  // Attempt to load texture
			return;  // Return if failed
	}

	sf::RectangleShape* newRect = new sf::RectangleShape(size);
	newRect->setPosition(pos);
	newRect->setTexture(m_textures[texture]);
	m_rectList.push_back(newRect);
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
