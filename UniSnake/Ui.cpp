#include "Ui.h"

bool Ui::loadFont(std::string fontName) {
	sf::Font newFont;
	if (!newFont.loadFromFile(fontName + ".ttf")) {
		std::cerr << "Ui::loadFont(fontName) -> Failed to load font file! (" + fontName + ")\n";
		return false;
	}
	m_fonts.insert({ fontName, newFont });
}

void Ui::addText(std::string txt, std::string fontName, sf::Vector2f pos, bool center) {
	if (!m_fonts.count(fontName)) {  // If font is not loaded
		if (!loadFont(fontName))  // Try to load new font
			return;  // If fails, return
	}
	//sf::Font 
}

void Ui::update() {

}

void Ui::draw(sf::RenderWindow* window) {

}
