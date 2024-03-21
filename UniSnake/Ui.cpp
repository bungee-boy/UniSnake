#include "Ui.h"

bool Ui::loadFont(const std::string fontName) {
	sf::Font newFont;
	if (!newFont.loadFromFile(fontName + ".ttf")) {
		std::cerr << "Ui::loadFont(fontName) -> Failed to load font file! (" + fontName + ".ttf)\n";
		return false;
	}
	m_fonts.insert({ fontName, newFont });
}

void Ui::addText(const std::string txt, const std::string fontName, const sf::Vector2f pos, const bool center, const unsigned int size) {
	if (!m_fonts.count(fontName)) {  // If font is not loaded
		if (!loadFont(fontName))  // Try to load new font
			return;  // If fails, return
	}
	sf::Text* newText = new sf::Text(txt, m_fonts[fontName], size);  // Create text
	newText->setPosition({ (center) ? pos.x - newText->getGlobalBounds().width / 2 : pos.x, pos.y});  // Set position (with centering)
	m_textList.push_back(newText);  // Add text to list (to be drawn)
}

void Ui::clearText() {
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

void Ui::clearRect() {
	m_rectList.clear();
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
