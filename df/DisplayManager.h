#pragma once

//System includes
#include <SFML/Graphics.hpp>
#include <string>


//Engine includes
#include "Color.h"
#include "Manager.h"
#include "Vector.h"

#define DM df::DisplayManager::getInstance()

namespace df {

	//Defaults for SFML window
	const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
	const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
	const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 80;
	const int WINDOW_VERTICAL_CHARS_DEFAULT = 24;
	const int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar;
	const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black;
	const std::string WINDOW_TITLE_DEFAULT = "Dragonfly";
	const std::string FONT_FILE_DEFAULT = "df-font.ttf";

	enum Justification {
		LEFT_JUSTIFIED,
		CENTER_JUSTIFIED,
		RIGHT_JUSTIFIED,
	};

	class DisplayManager : public Manager {

	private:
		DisplayManager();
		DisplayManager(DisplayManager const&);
		void operator=(DisplayManager const&);
		sf::Font m_font;
		sf::RenderWindow* m_p_window;
		int m_window_horizontal_pixels;
		int m_window_vertical_pixels;
		int m_window_horizontal_chars;
		int m_window_vertical_chars;

	public:
		//Get the one and only instance of the DisplayManager
		static DisplayManager& getInstance();

		//Open graphics window, ready for text-based display
		//Return 0 if ok, else -1
		int startUp();

		//Close graphics window
		void shutDown();

		//Draw character at window location(x,y) with color
		//Return 0 if ok, else -1
		int drawCh(Vector world_pos, char ch, Color color) const;

		//Draw string at window location (x,y) with default color
		//Justified left, center or right
		//Return 0 if ok, else -1
		int drawString(Vector pos, std::string str, Justification just, Color color) const;


		//Return window's horizontal max (in chars)
		int getHorizontal() const;

		//Return window's vertical maximum (in chars)
		int getVertical() const;

		//Return window's horizontal max (in pixels)
		int getHorizontalPixels() const;

		//Return window's vertical max (in pixels)
		int getVerticalPixels() const;

		//Render current window buffer
		//Return 0 if ok, else -1
		int swapBuffers();

		//Return pointer to SFML graphics window
		sf::RenderWindow* getWindow() const;

		//utility functions

		//Compute character height in pixels, based on window size
		float charHeight();

		//Compute character width in pixels, based on window size
		float charWidth();

		//Convert ASCII spaces (x,y) to window pixels(x,y)
		Vector spacesToPixels(Vector spaces);

		//Convert window pixels(x,y) to ASCII spaces(x,y)
		Vector pixelsToSpaces(Vector pixels);

	};

}