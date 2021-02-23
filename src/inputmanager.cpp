#include "inputmanager.h"

InputManager::InputManager() {

}

InputManager::~InputManager() {

}

sf::Keyboard::Key InputManager::KeyboardConfiguration(Input key) {
//    Left = 0,
//    Right,
//    Up,
//    Down,

    if(key == Left) return sf::Keyboard::A;
    if(key == Right) return sf::Keyboard::D;
    if(key == Up) return sf::Keyboard::W;
    if(key == Down) return sf::Keyboard::S;
    if(key == LoadMap) return sf::Keyboard::L;

    return sf::Keyboard::Unknown;
}

int InputManager::JoystickConfiguration(Input key) {
//    if(key == Left) return 2;
//    if(key == Right) return 1;
//    if(key == Up) return 3;
//    if(key == Down) return 0;

    return -1;
}

void InputManager::JoystickAxisConfiguration(Input key, sf::Joystick::Axis& axis, float& position) {
    if(key == Left) {
        axis = sf::Joystick::PovY;
        position = -100;
    }

    if(key == Right)  {
        axis = sf::Joystick::PovY;
        position = 100;
    }

    if(key == Up)  {
        axis = sf::Joystick::PovX;
        position = 100;
    }

    if(key == Down)  {
        axis = sf::Joystick::PovX;
        position = -100;
    }
}

bool InputManager::IsKeyBoardPressed(sf::Keyboard::Key key) {
    return sf::Keyboard::isKeyPressed(key);
}

bool InputManager::IsJoystickPressed(unsigned int joystick, unsigned int button) {
    return sf::Joystick::isButtonPressed(joystick, button);
}

bool InputManager::IsJoystickAxis(unsigned int joystick, sf::Joystick::Axis axis, float position) {
    return sf::Joystick::getAxisPosition(joystick, axis) == position;
}

bool InputManager::IsPressed(Input key, unsigned int joystick) {
    sf::Keyboard::Key myKeyboardKey = KeyboardConfiguration(key);
    if(myKeyboardKey != sf::Keyboard::Unknown) {
        if(IsKeyBoardPressed(myKeyboardKey)) {
            return true;
        }
    }


    int myJoystickKey = JoystickConfiguration(key);
    if(myJoystickKey != -1) {
        if(IsJoystickPressed(joystick, myJoystickKey)) {
            return true;
        }
    }

    sf::Joystick::Axis axis;
    float position = 0;
    JoystickAxisConfiguration(key, axis, position);
    if(position != 0) {
        if(IsJoystickAxis(joystick, axis, position)) {
            return true;
        }
    }

    return false;
}

//bool sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
//bool sf::Joystick::isButtonPressed(0, 1);
//float sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
