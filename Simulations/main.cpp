#include <iostream>
#include <SFML/Graphics.hpp>

#include "PerlinNoise.hpp"

using namespace std;
using namespace sf;
using namespace siv;

int main()
{
	const int width = 1920;
	const int height = 1080;
	RenderWindow window(
		VideoMode(width, height),
		"SFML works!"
	);
	RenderWindow window2(
		VideoMode(width, height),
		"SFML works!"
	);
	

	Shader shader;
	const PerlinNoise::seed_type seed = 123456u;
	PerlinNoise noise{seed};

	Font font;
	font.loadFromFile("consola.ttf");

	Color color(200, 200, 0, 255);

	Text fpsText;
	fpsText.setFont(font);
	fpsText.setCharacterSize(24);
	fpsText.setFillColor(color);
	fpsText.setPosition(15, 15);

	Text frameTimeText;
	frameTimeText.setFont(font);
	frameTimeText.setCharacterSize(24);
	frameTimeText.setFillColor(color);
	frameTimeText.setPosition(15, 45);

	frameTimeText.setString(0 + " ms");
	fpsText.setString(0 + " fps");
	
	window.setFramerateLimit(60);

	if (!shader.loadFromFile("vertex.shader", "fragment.shader"))
	{
		//error
	}

	Texture texture;
	Sprite sprite;

	texture.create(width, height);
	sprite.setTexture(texture);

	float tx = texture.getSize().x;
	float ty = texture.getSize().y;
	
	shader.setUniform("u_resolution", 
			Vector2f(
				texture.getSize().x,
				texture.getSize().y
			)
	);

	float rep = 4;
	
	Clock deltaClock;
	Clock t;
	Clock time;
	while (window.isOpen())
	{
		float dt = deltaClock.restart().asSeconds();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == event.KeyReleased )
				if (event.key.code == Keyboard::Escape){
					window.close();
				}
			
		}
		
		window.clear();
		window2.clear();
		//----------Drawing Starts----------

		float r = (float)(rand() % 255) / 255;
		shader.setUniform("u_time", time.getElapsedTime().asSeconds());
		window.draw(sprite, &shader);
		window2.draw(sprite, &shader);
		
		int fps = 1000 / (dt * 1000);
		float frameTime = dt * 1000;

		if (ceil(t.getElapsedTime().asSeconds() * 100) / 100 >= 1 / rep)
		{
			string frames = to_string(fps);
			string ft = to_string(frameTime);

			fpsText.setString(frames + " fps");
			frameTimeText.setString("frame time: " + ft + " ms");

			t.restart();
		}
		
		window.draw(fpsText);
		window.draw(frameTimeText);

		window2.draw(fpsText);
		window2.draw(frameTimeText);
		//----------Drawing Ends----------
		window.display();
		window2.display();
	}
	return 0;
}

