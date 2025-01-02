//system includes
#include <SFML/Graphics.hpp>

//engine includes
#include "DisplayManager.h"
#include "Vector.h"
#include "LogManager.h"
#include "Color.h"
#include "Utility.h"

namespace df {

	//set type and initialize attributes
	DisplayManager::DisplayManager()
	{
		setType("DisplayManager");

		//set window dimentions to default
		m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
		m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;

		m_window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
		m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;

	}

	//returns only instance of DisplayManager
	DisplayManager& DisplayManager::getInstance()
	{
		static DisplayManager single;
		return single;
	}

	//Opens graphics window, ready for text-based display
	//Return 0 if ok, else return -1
	int DisplayManager::startUp()
	{
		//If window already created, do nothing
		if (!m_p_window == NULL)
		{
			return 0;
		}

		//create window
		m_p_window = new sf::RenderWindow(sf::VideoMode(m_window_horizontal_pixels, m_window_vertical_pixels), WINDOW_TITLE_DEFAULT, WINDOW_STYLE_DEFAULT);
		//set mouse cursor invisible
		m_p_window->setMouseCursorVisible(false);
		//sync with monitor refresh rate
		m_p_window->setVerticalSyncEnabled(true);

		//load font, if font doesn't load, write error log
		if (!m_font.loadFromFile(FONT_FILE_DEFAULT))
		{
			LM.writeLog("\nDM constructor: Font not loaded!");
			return -1;
		}

		//start up base manager
		Manager::startUp();
		LM.writeLog("\nDISPLAY MANAGER STARTUP CALLED");
		return 0;

	}

	void DisplayManager::shutDown()
	{
		m_p_window->close();
		m_p_window = NULL;
		Manager::shutDown();
	}

	//Draw a character at window location (x,y) with color
	//Return 0 if ok, else -1
	int DisplayManager::drawCh(Vector world_pos, char ch, Color color) const
	{
		df::Utility u = df::Utility();
		Vector view_pos = u.worldToView(world_pos);

		//Make sure window is allocated
		if (m_p_window == NULL)
		{
			LM.writeLog("DM.drawCh- window not allocated!");
			return -1;
		}

		//Convert spaces (x,y) to pixels (x,y)
		Vector pixel_pos = DM.spacesToPixels(view_pos);

		//Draw background rectangle since text is "see through" in SFML
		static sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(DM.charWidth(), DM.charHeight()));
		rectangle.setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);
		rectangle.setPosition(pixel_pos.getX() - DM.charWidth() / 10,
			pixel_pos.getY() + DM.charHeight() / 5);
		m_p_window->draw(rectangle);

		//Create character text to draw
		static sf::Text text("", m_font);
		text.setString(ch);
		text.setStyle(sf::Text::Bold); //Make bold, since looks better

		//Scale to right size
		if (DM.charWidth() < DM.charHeight())
		{
			text.setCharacterSize(DM.charWidth() * 2);
		}
		else text.setCharacterSize(DM.charHeight() * 2);

		//Set SFML color based on Dragonfly color
		switch (color) {
		case YELLOW:
			text.setFillColor(sf::Color::Yellow);
			break;
		case RED:
			text.setFillColor(sf::Color::Red);
			break;
		case BLACK:
			text.setFillColor(sf::Color::Black);
			break;
		case GREEN:
			text.setFillColor(sf::Color::Green);
			break;
		case BLUE:
			text.setFillColor(sf::Color::Blue);
			break;
		case MAGENTA:
			text.setFillColor(sf::Color::Magenta);
			break;
		case CYAN:
			text.setFillColor(sf::Color::Cyan);
			break;
		case WHITE:
			text.setFillColor(sf::Color::White);
			break;
		//default? use default color
		//TODO: change so this is not hard coded
		default:
			text.setFillColor(sf::Color::White);
			LM.writeLog("\nDM.drawCh- Color of text not recognized! Setting to default white");
			break;
		}

		//Set position in window (in pixels)
		text.setPosition(pixel_pos.getX(), pixel_pos.getY());

		//Draw character
		m_p_window->draw(text);

		return 0; //Success

	}
	//Draw string at window location (x,y) with color
	//Justified left, center or right
	//Return 0 if ok, else -1
	int DisplayManager::drawString(Vector pos, std::string str, Justification just, Color color) const
	{
		//Get starting position
		Vector starting_pos = pos;
		switch (just) {
		case CENTER_JUSTIFIED:
			starting_pos.setX(pos.getX() - str.size() / 2);
			break;
		case RIGHT_JUSTIFIED:
			starting_pos.setX(pos.getX() - str.size());
			break;
		case LEFT_JUSTIFIED:
		default:
			break;
		}

		//Draw string character by character
		for (int i = 0; i < str.size(); i++)
		{
			Vector temp_pos(starting_pos.getX() + i, starting_pos.getY());
			drawCh(temp_pos, str[i], color);
		}

		return 0;
	}

	//return horizontal dimention in chars
	int DisplayManager::getHorizontal() const
	{
		return m_window_horizontal_chars;
	}

	//return vertical dimention in chars
	int DisplayManager::getVertical() const
	{
		return m_window_vertical_chars;
	}

	//return horizontal dimention in pixels
	int DisplayManager::getHorizontalPixels() const
	{
		return m_window_horizontal_pixels;
	}

	//return vertical dimention in pixels
	int DisplayManager::getVerticalPixels() const
	{
		return m_window_vertical_pixels;
	}

	//Render current window buffer
	//Return 0 if ok, else -1
	int DisplayManager::swapBuffers()
	{
		//Make sure window is allocated
		if (m_p_window == NULL) {
			LM.writeLog("\nDM.swapBuffers- window not allocated!");
			return -1;
		}

		//Display current window
		m_p_window->display();

		//Clear another window to get ready for the next draw
		m_p_window->clear();

		return 0; // Success

	}


	//returns pointer to window
	sf::RenderWindow* DisplayManager::getWindow() const
	{
		return m_p_window;
	}

	//computes and returns the height (in pixels) of each character
	float DisplayManager::charHeight()
	{
		return (float)getVerticalPixels() / getVertical();
	}

	//returns width (in pixels) of each character
	float DisplayManager::charWidth()
	{
		return (float)getHorizontalPixels() / getHorizontal();
	}

	//convert number of spaces to pixels
	Vector DisplayManager::spacesToPixels(Vector spaces)
	{
		float newX;
		float newY;
		newX = spaces.getX() * charWidth();
		newY = spaces.getY() * charHeight();
		Vector v = Vector(newX, newY);
		return v;
	}

	//convert num pixels to spaces
	Vector DisplayManager::pixelsToSpaces(Vector pixels)
	{
		float newX;
		float newY;
		newX = pixels.getX() / charWidth();
		newY = pixels.getY() / charHeight();
		Vector v = Vector(newX, newY);
		return v;
	}

}