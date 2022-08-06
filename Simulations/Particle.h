#pragma once

#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Particle
{
public:
	Vector2f pos;
	RectangleShape rect;

	Particle() {}
	
	Particle(float x, float y, int size) {
		this->pos.x = x;
		this->pos.y = y;		

		rect.setSize(Vector2f(size, size));

		rect.setFillColor(Color(255,255,255,255));
		setPosition(pos.x, pos.y);
		
	}

	void setFillColor(Color color) {
		rect.setFillColor(color);
	}

	void setOutlineThickness(float thickness) {
		rect.setOutlineThickness(thickness);
	}

	void setPosition(float x, float y) {
		rect.setPosition(x, y);
	}

	Vector2f getPosition() {
		return rect.getPosition();
	}
	
	void draw(RenderWindow& window) {
		window.draw(rect);
	}
};

