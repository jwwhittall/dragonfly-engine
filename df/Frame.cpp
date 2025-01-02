#include "Frame.h"
#include "logManager.h"
#include "DisplayManager.h"

//creates empty frame with default dimensions 0 x 0
//no characters in frame to draw; empty
df::Frame::Frame()
{
	m_width = 0;
	m_height = 0;
	m_frame_str = "";
}

//creates frame with given attributes
df::Frame::Frame(int new_width, int new_height, std::string frame_str)
{
	m_width = new_width;
	m_height = new_height;
	m_frame_str = frame_str;
}

//set width to given value
void df::Frame::setWidth(int new_width)
{
	m_width = new_width;
}

//returns width of frame
int df::Frame::getWidth() const
{
	return m_width;
}

//returns height of frame
int df::Frame::getHeight() const
{
	return m_height;
}

//sets height of frame to given value
void df::Frame::setHeight(int new_height)
{
	m_height = new_height;
}

//sets string of frame chars to given value
void df::Frame::setString(std::string new_frame_str)
{
	m_frame_str = new_frame_str;
}

//returns string of frame chars
std::string df::Frame::getString() const
{
	return m_frame_str;
}

//draws frame on window
int df::Frame::draw(df::Vector position, Color color) const
{
	//Error check empty string
	if (this->getString().empty())
	{
		LM.writeLog("\nframe.draw- frame is empty!");
		return -1;
	}

	//Determine offset since centered at position
	int x_offset = this->getWidth() / 2;
	int y_offset = this->getHeight() / 2;


	//Draw character by character
	for (int y = 0; y < this->getHeight(); y++)
	{
		for (int x = 0; x < this->getWidth(); x++)
		{
			df::Vector temp_pos(position.getX() + x - x_offset,
				position.getY() + y - y_offset);

			DM.drawCh(temp_pos, m_frame_str[y * this->getWidth() + x], color);
		}// x
	}//y
}
