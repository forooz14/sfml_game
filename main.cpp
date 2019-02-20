#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include "Screen.h"
#include "GameObject.h"
using namespace Engine;

Screen startingScreen;

class SampleCircle : public GraphicalGameObject
{
public:
	SampleCircle() : GraphicalGameObject(sf::CircleShape(50.0f))
	{
		this->circle()->setFillColor(sf::Color::Blue);
	}
	void MouseButtonReleased(sf::Event e)
	{
		this->circle()->setPosition(e.mouseButton.x, e.mouseButton.y);
	}
	sf::CircleShape* circle()
	{
		return dynamic_cast<sf::CircleShape*>(this->graphic);
	}
};

class SampleSquare : public GraphicalGameObject
{
public:
	SampleSquare() : GraphicalGameObject(sf::RectangleShape(sf::Vector2f(10, 10)))
	{
		this->square()->setFillColor(sf::Color::Green);
	}
	sf::RectangleShape* square()
	{
		return dynamic_cast<sf::RectangleShape*>(this->graphic);
	}
};




class ExampleClickHandler : public GameObject
{
public:
    void MouseButtonReleased(sf::Event e)
    {
        std::cout << "Mouse clicked at (" << e.mouseButton.x << ", " << e.mouseButton.y << ")" << std::endl;
        SampleSquare* s = new SampleSquare(); //use a heap allocated object which has to be cleaned up later.
        objs.push_back(s);
        s->square()->setPosition(e.mouseButton.x, e.mouseButton.y);
        startingScreen.add(s);
    }
private:
    std::vector<GraphicalGameObject*> objs;
};




class Character : public GraphicalGameObject
{
    bool W_KeyHeld = false;
    bool A_KeyHeld = false;
    bool S_KeyHeld = false;
    bool D_KeyHeld = false;
public:
   // Character(sf::RectangleShape r) : GraphicalGameObject(r) { }
    Character (sf::Sprite s):GraphicalGameObject(s, 450, 250 ){
    }
    void KeyPressed(sf::Event e)
    {
        switch (e.key.code)
        {
            case sf::Keyboard::W:
                this->W_KeyHeld = true;
                break;
            case sf::Keyboard::A:
                this->A_KeyHeld = true;
                break;
            case sf::Keyboard::S:
                this->S_KeyHeld = true;
                break;
            case sf::Keyboard::D:
                this->D_KeyHeld = true;
                break;
            default:
                break;
                
        }
    }
    void KeyReleased(sf::Event e)
    {
        switch (e.key.code)
        {
            case sf::Keyboard::W:
                this->W_KeyHeld = false;
                break;
            case sf::Keyboard::A:
                this->A_KeyHeld = false;
                break;
            case sf::Keyboard::S:
                this->S_KeyHeld = false;
                break;
            case sf::Keyboard::D:
                this->D_KeyHeld = false;
                break;
            default:
                break;
                
        }
    }
    void EveryFrame(uint64_t f)
    {
        sf::RectangleShape* r = this->placeholder();
        if (this->W_KeyHeld) { r->move(0, -10); }
        if (this->A_KeyHeld) { r->move(-10, 0); }
        if (this->S_KeyHeld) { r->move(0, 10); }
        if (this->D_KeyHeld) { r->move(10, 0); }
    }
    sf::RectangleShape* placeholder()
    {
        return dynamic_cast<sf::RectangleShape*>(this->graphic);
    }
};



int main(int argc, char** argv)
{
	//these are static members that should be set before rendering a screen. the window will be locked at these values after rendering has started.
	Screen::windowWidth = 1024;
	Screen::windowHeight = 768;
	Screen::windowTitle = "Game!";

	//screen object which holds game objects
	//Screen startingScreen;
    sf::Sprite m_Sprite;
    sf::Texture m_Texture;
    
    m_Texture.loadFromFile("bob.png");
    m_Texture.setSmooth(true);
    m_Sprite.setTexture(m_Texture);
    
    Character character(m_Sprite);

    

    
	//a class which derives from GameObject and has an event handler
	//ExampleClickHandler clicks;

	//a class which derives from GraphicalGameObject and puts a circle on the screen with an event to move it when the user clicks
	//SampleCircle s;

	//add the objects to the screen
	//startingScreen.add(&s);
	//startingScreen.add(&clicks);
    startingScreen.add(&character);

	//note: The lifetime of the objects added to the screen must be as long as the screen's lifetime. In this case it's ok to use these local variables because this function waits for the thread returned by the screen.
	//For most other cases we'll probably have to use heap allocated objects.

	//render the screen (replaces whichever screen is currently rendering)
	//also join the thread which was returned. this prevents the program from exiting.
	startingScreen.render();

	return 0;
}
