#include "InputManager.h"
#include "DisplayManager.h"
#include "logManager.h"
#include "Manager.h"
#include "EventMouse.h"
#include "EventKeyboard.h"

namespace df {

	InputManager::InputManager()
	{
		setType("InputManager");
	}

	//returns only instance of inputManager
	InputManager& InputManager::getInstance()
	{
		static InputManager single;
		return single;
	}

	//check that DM is started first
	int InputManager::startUp()
	{
		LM.writeLog("\nINPUT MANAGER STARTED");
		if (!DM.isStarted()) {
			LM.writeLog("\nIM.startUp- DM not yet started!");
			return -1;
		}

		//disable repeat key input
		sf::RenderWindow* window = DM.getWindow();
		window->setKeyRepeatEnabled(false);

		Manager::startUp();

		return 0;
	}

	//reenable repeat key input
	void InputManager::shutDown()
	{
		LM.writeLog("\nINPUT MANAGER SHUT DOWN");
		sf::RenderWindow* window = DM.getWindow();
		window->setKeyRepeatEnabled(true);

		Manager::shutDown();
	}

	void InputManager::getInput() const
	{
		//check for any input
		sf::Event e;
		sf::RenderWindow* window = DM.getWindow();
		while (window->pollEvent(e))
		{
			//check by type, then key/button
			if (e.type == sf::Event::KeyPressed)
			{
				df::EventKeyboard* k = new EventKeyboard;
				k->setKeyboardAction(df::KEY_PRESSED);

				switch (e.key.code)
				{
				case sf::Keyboard::A:
					k->setKey(df::Keyboard::A);
					//LM.writeLog("\nKey A pressed!");
					break;
				case sf::Keyboard::B:
					k->setKey(df::Keyboard::B);
					break;
				case sf::Keyboard::C:
					k->setKey(df::Keyboard::C);
					break;
				case sf::Keyboard::D:
					k->setKey(df::Keyboard::D);
					break;
				case sf::Keyboard::E:
					k->setKey(df::Keyboard::E);
					break;
				case sf::Keyboard::F:
					k->setKey(df::Keyboard::F);
					break;
				case sf::Keyboard::G:
					k->setKey(df::Keyboard::G);
					break;
				case sf::Keyboard::H:
					k->setKey(df::Keyboard::H);
					break;
				case sf::Keyboard::I:
					k->setKey(df::Keyboard::I);
					break;
				case sf::Keyboard::J:
					k->setKey(df::Keyboard::J);
					break;
				case sf::Keyboard::K:
					k->setKey(df::Keyboard::K);
					break;
				case sf::Keyboard::L:
					k->setKey(df::Keyboard::L);
					break;
				case sf::Keyboard::M:
					k->setKey(df::Keyboard::M);
					break;
				case sf::Keyboard::N:
					k->setKey(df::Keyboard::N);
					break;
				case sf::Keyboard::O:
					k->setKey(df::Keyboard::O);
					break;
				case sf::Keyboard::P:
					k->setKey(df::Keyboard::P);
					break;
				case sf::Keyboard::Q:
					k->setKey(df::Keyboard::Q);
					break;
				case sf::Keyboard::R:
					k->setKey(df::Keyboard::R);
					break;
				case sf::Keyboard::S:
					k->setKey(df::Keyboard::S);
					break;
				case sf::Keyboard::T:
					k->setKey(df::Keyboard::T);
					break;
				case sf::Keyboard::U:
					k->setKey(df::Keyboard::U);
					break;
				case sf::Keyboard::V:
					k->setKey(df::Keyboard::V);
					break;
				case sf::Keyboard::W:
					k->setKey(df::Keyboard::W);
					break;
				case sf::Keyboard::X:
					k->setKey(df::Keyboard::X);
					break;
				case sf::Keyboard::Y:
					k->setKey(df::Keyboard::Y);
					break;
				case sf::Keyboard::Z:
					k->setKey(df::Keyboard::Z);
					break;
				case sf::Keyboard::Space:
					k->setKey(df::Keyboard::SPACE);
					break;
				case sf::Keyboard::Return:
					k->setKey(df::Keyboard::RETURN);
					break;
				case sf::Keyboard::Escape:
					k->setKey(df::Keyboard::ESCAPE);
					break;
				case sf::Keyboard::Tab:
					k->setKey(df::Keyboard::TAB);
					break;
				case sf::Keyboard::Left:
					k->setKey(df::Keyboard::LEFTARROW);
					break;
				case sf::Keyboard::Right:
					k->setKey(df::Keyboard::RIGHTARROW);
					break;
				case sf::Keyboard::Up:
					k->setKey(df::Keyboard::UPARROW);
					break;
				case sf::Keyboard::Down:
					k->setKey(df::Keyboard::DOWNARROW);
					break;
				case sf::Keyboard::Pause:
					k->setKey(df::Keyboard::PAUSE);
					break;
				case sf::Keyboard::Dash:
					k->setKey(df::Keyboard::MINUS);
					break;
				case sf::Keyboard::Equal:
					k->setKey(df::Keyboard::PLUS);
					break;
				case sf::Keyboard::Tilde:
					k->setKey(df::Keyboard::TILDE);
					break;
				case sf::Keyboard::Period:
					k->setKey(df::Keyboard::PERIOD);
					break;
				case sf::Keyboard::Comma:
					k->setKey(df::Keyboard::COMMA);
					break;
				case sf::Keyboard::Slash:
					k->setKey(df::Keyboard::SLASH);
					break;
				case sf::Keyboard::LControl:
					k->setKey(df::Keyboard::LEFTCONTROL);
					break;
				case sf::Keyboard::RControl:
					k->setKey(df::Keyboard::RIGHTCONTROL);
					break;
				case sf::Keyboard::LShift:
					k->setKey(df::Keyboard::LEFTSHIFT);
					break;
				case sf::Keyboard::RShift:
					k->setKey(df::Keyboard::RIGHTSHIFT);
					break;
				case sf::Keyboard::F1:
					k->setKey(df::Keyboard::F1);
					break;
				case sf::Keyboard::F2:
					k->setKey(df::Keyboard::F2);
					break;
				case sf::Keyboard::F3:
					k->setKey(df::Keyboard::F3);
					break;
				case sf::Keyboard::F4:
					k->setKey(df::Keyboard::F4);
					break;
				case sf::Keyboard::F5:
					k->setKey(df::Keyboard::F5);
					break;
				case sf::Keyboard::F6:
					k->setKey(df::Keyboard::F6);
					break;
				case sf::Keyboard::F7:
					k->setKey(df::Keyboard::F7);
					break;
				case sf::Keyboard::F8:
					k->setKey(df::Keyboard::F8);
					break;
				case sf::Keyboard::F9:
					k->setKey(df::Keyboard::F9);
					break;
				case sf::Keyboard::F10:
					k->setKey(df::Keyboard::F10);
					break;
				case sf::Keyboard::F11:
					k->setKey(df::Keyboard::F11);
					break;
				case sf::Keyboard::F12:
					k->setKey(df::Keyboard::F12);
					break;
				case sf::Keyboard::Num1:
					k->setKey(df::Keyboard::NUM1);
					break;
				case sf::Keyboard::Num2:
					k->setKey(df::Keyboard::NUM2);
					break;
				case sf::Keyboard::Num3:
					k->setKey(df::Keyboard::NUM3);
					break;
				case sf::Keyboard::Num4:
					k->setKey(df::Keyboard::NUM4);
					break;
				case sf::Keyboard::Num5:
					k->setKey(df::Keyboard::NUM5);
					break;
				case sf::Keyboard::Num6:
					k->setKey(df::Keyboard::NUM6);
					break;
				case sf::Keyboard::Num7:
					k->setKey(df::Keyboard::NUM7);
					break;
				case sf::Keyboard::Num8:
					k->setKey(df::Keyboard::NUM8);
					break;
				case sf::Keyboard::Num9:
					k->setKey(df::Keyboard::NUM9);
					break;
				case sf::Keyboard::Num0:
					k->setKey(df::Keyboard::NUM0);
					break;
				}
				onEvent(k);
			}
			if (e.type == sf::Event::KeyReleased)
			{
				df::EventKeyboard* k = new df::EventKeyboard;
				k->setKeyboardAction(df::KEY_RELEASED);
				switch (e.key.code)
				{
				case sf::Keyboard::A:
					k->setKey(df::Keyboard::A);
					//LM.writeLog("\nKey A released!");
					break;
				case sf::Keyboard::B:
					k->setKey(df::Keyboard::B);
					break;
				case sf::Keyboard::C:
					k->setKey(df::Keyboard::C);
					break;
				case sf::Keyboard::D:
					k->setKey(df::Keyboard::D);
					break;
				case sf::Keyboard::E:
					k->setKey(df::Keyboard::E);
					break;
				case sf::Keyboard::F:
					k->setKey(df::Keyboard::F);
					break;
				case sf::Keyboard::G:
					k->setKey(df::Keyboard::G);
					break;
				case sf::Keyboard::H:
					k->setKey(df::Keyboard::H);
					break;
				case sf::Keyboard::I:
					k->setKey(df::Keyboard::I);
					break;
				case sf::Keyboard::J:
					k->setKey(df::Keyboard::J);
					break;
				case sf::Keyboard::K:
					k->setKey(df::Keyboard::K);
					break;
				case sf::Keyboard::L:
					k->setKey(df::Keyboard::L);
					break;
				case sf::Keyboard::M:
					k->setKey(df::Keyboard::M);
					break;
				case sf::Keyboard::N:
					k->setKey(df::Keyboard::N);
					break;
				case sf::Keyboard::O:
					k->setKey(df::Keyboard::O);
					break;
				case sf::Keyboard::P:
					k->setKey(df::Keyboard::P);
					break;
				case sf::Keyboard::Q:
					k->setKey(df::Keyboard::Q);
					break;
				case sf::Keyboard::R:
					k->setKey(df::Keyboard::R);
					break;
				case sf::Keyboard::S:
					k->setKey(df::Keyboard::S);
					break;
				case sf::Keyboard::T:
					k->setKey(df::Keyboard::T);
					break;
				case sf::Keyboard::U:
					k->setKey(df::Keyboard::U);
					break;
				case sf::Keyboard::V:
					k->setKey(df::Keyboard::V);
					break;
				case sf::Keyboard::W:
					k->setKey(df::Keyboard::W);
					break;
				case sf::Keyboard::X:
					k->setKey(df::Keyboard::X);
					break;
				case sf::Keyboard::Y:
					k->setKey(df::Keyboard::Y);
					break;
				case sf::Keyboard::Z:
					k->setKey(df::Keyboard::Z);
					break;
				case sf::Keyboard::Space:
					k->setKey(df::Keyboard::SPACE);
					break;
				case sf::Keyboard::Return:
					k->setKey(df::Keyboard::RETURN);
					break;
				case sf::Keyboard::Escape:
					k->setKey(df::Keyboard::ESCAPE);
					break;
				case sf::Keyboard::Tab:
					k->setKey(df::Keyboard::TAB);
					break;
				case sf::Keyboard::Left:
					k->setKey(df::Keyboard::LEFTARROW);
					break;
				case sf::Keyboard::Right:
					k->setKey(df::Keyboard::RIGHTARROW);
					break;
				case sf::Keyboard::Up:
					k->setKey(df::Keyboard::UPARROW);
					break;
				case sf::Keyboard::Down:
					k->setKey(df::Keyboard::DOWNARROW);
					break;
				case sf::Keyboard::Pause:
					k->setKey(df::Keyboard::PAUSE);
					break;
				case sf::Keyboard::Dash:
					k->setKey(df::Keyboard::MINUS);
					break;
				case sf::Keyboard::Equal:
					k->setKey(df::Keyboard::PLUS);
					break;
				case sf::Keyboard::Tilde:
					k->setKey(df::Keyboard::TILDE);
					break;
				case sf::Keyboard::Period:
					k->setKey(df::Keyboard::PERIOD);
					break;
				case sf::Keyboard::Comma:
					k->setKey(df::Keyboard::COMMA);
					break;
				case sf::Keyboard::Slash:
					k->setKey(df::Keyboard::SLASH);
					break;
				case sf::Keyboard::LControl:
					k->setKey(df::Keyboard::LEFTCONTROL);
					break;
				case sf::Keyboard::RControl:
					k->setKey(df::Keyboard::RIGHTCONTROL);
					break;
				case sf::Keyboard::LShift:
					k->setKey(df::Keyboard::LEFTSHIFT);
					break;
				case sf::Keyboard::RShift:
					k->setKey(df::Keyboard::RIGHTSHIFT);
					break;
				case sf::Keyboard::F1:
					k->setKey(df::Keyboard::F1);
					break;
				case sf::Keyboard::F2:
					k->setKey(df::Keyboard::F2);
					break;
				case sf::Keyboard::F3:
					k->setKey(df::Keyboard::F3);
					break;
				case sf::Keyboard::F4:
					k->setKey(df::Keyboard::F4);
					break;
				case sf::Keyboard::F5:
					k->setKey(df::Keyboard::F5);
					break;
				case sf::Keyboard::F6:
					k->setKey(df::Keyboard::F6);
					break;
				case sf::Keyboard::F7:
					k->setKey(df::Keyboard::F7);
					break;
				case sf::Keyboard::F8:
					k->setKey(df::Keyboard::F8);
					break;
				case sf::Keyboard::F9:
					k->setKey(df::Keyboard::F9);
					break;
				case sf::Keyboard::F10:
					k->setKey(df::Keyboard::F10);
					break;
				case sf::Keyboard::F11:
					k->setKey(df::Keyboard::F11);
					break;
				case sf::Keyboard::F12:
					k->setKey(df::Keyboard::F12);
					break;
				case sf::Keyboard::Num1:
					k->setKey(df::Keyboard::NUM1);
					break;
				case sf::Keyboard::Num2:
					k->setKey(df::Keyboard::NUM2);
					break;
				case sf::Keyboard::Num3:
					k->setKey(df::Keyboard::NUM3);
					break;
				case sf::Keyboard::Num4:
					k->setKey(df::Keyboard::NUM4);
					break;
				case sf::Keyboard::Num5:
					k->setKey(df::Keyboard::NUM5);
					break;
				case sf::Keyboard::Num6:
					k->setKey(df::Keyboard::NUM6);
					break;
				case sf::Keyboard::Num7:
					k->setKey(df::Keyboard::NUM7);
					break;
				case sf::Keyboard::Num8:
					k->setKey(df::Keyboard::NUM8);
					break;
				case sf::Keyboard::Num9:
					k->setKey(df::Keyboard::NUM9);
					break;
				case sf::Keyboard::Num0:
					k->setKey(df::Keyboard::NUM0);
					break;
				}
				onEvent(k);
			}
			if (e.type == sf::Event::MouseMoved)
			{
				df::EventMouse* m = new df::EventMouse;
				m->setMouseAction(df::MOVED);
				m->setMousePosition(df::Vector(e.mouseMove.x, e.mouseMove.y));
				//LM.writeLog("\nMouse moved!");
				onEvent(m);
			}
			if (e.type == sf::Event::MouseButtonPressed)
			{
				df::EventMouse* m = new df::EventMouse;
				m->setMouseAction(df::CLICKED);
				switch (e.mouseButton.button)
				{
				case sf::Mouse::Left:
					m->setMouseButton(df::Mouse::LEFT);
					//LM.writeLog("\nLeft mouse clicked!");
					break;
				case sf::Mouse::Right:
					m->setMouseButton(df::Mouse::RIGHT);
					break;
				case sf::Mouse::Middle:
					m->setMouseButton(df::Mouse::MIDDLE);
					break;
				}
				onEvent(m);
			}
		}
	}
}