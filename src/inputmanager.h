#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>

class InputManager
{
public:
    InputManager();
    ~InputManager();

    enum Input
    {
        Left = 0,
        Right,
        Up,
        Down,
        LoadMap,

        KeyCount      ///< Keep last -- the total number of inputs
    };

    sf::Keyboard::Key KeyboardConfiguration(Input key);
    int JoystickConfiguration(Input key);
    void JoystickAxisConfiguration(Input key, sf::Joystick::Axis& axis, float& position);
    bool IsKeyBoardPressed(sf::Keyboard::Key);
    bool IsJoystickPressed(unsigned int joystick, unsigned int button);
    bool IsJoystickAxis(unsigned int joystick, sf::Joystick::Axis axis, float position);
    bool IsPressed(Input key, unsigned int joystick = 0);
};

extern InputManager inputManager;

#endif // INPUTMANAGER_H


//bool sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
//bool sf::Joystick::isButtonPressed(0, 1);
//float sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
