#include "RasterAlgorithms.h"
#include "MySurname.h"

#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 700;
const int PSEUDO_PIXEL_SIZE = 5;
const int NUM_OF_TESTS = 1000;


std::vector<sf::Image> create_images()
{
	std::vector<sf::Image> ret_value(ra::AMOUNT_OF_ALGORITHMS);
	for (int i = 0; i < ra::AMOUNT_OF_LINE_ALGORITHMS; ++i)
	{
		ra::algo_func current_algorithm = ra::line_algorithm_dda;
		switch (i % ra::AMOUNT_OF_ALGORITHMS)
		{
		case 0: 
			current_algorithm = ra::line_algorithm_dda;
			break;
		case 1:
			current_algorithm = ra::line_algorithm_bresenham;
			break;
		case 2:
			current_algorithm = ra::line_algorithm_wu;
			break;
		}

		std::vector<ra::PseudoPixel> pixels;
		for (int j = 0; j < MY_SURNAME.size(); j+=2)
		{
			std::vector<ra::PseudoPixel> tmp = current_algorithm(MY_SURNAME[j], MY_SURNAME[j + 1], sf::Color::Black);
			pixels.insert(pixels.end(), tmp.begin(), tmp.end());
		}

		ret_value[i] = ra::create_image(pixels, PSEUDO_PIXEL_SIZE, sf::Color::White);
	}

	ret_value[ra::AMOUNT_OF_ALGORITHMS - 1] = ra::create_image(ra::circle_algorithm_bresenham(sf::Vector2i(100, 70), 30, sf::Color::Black), PSEUDO_PIXEL_SIZE, sf::Color::White);

	return ret_value;
};

void draw_frame(sf::RenderWindow& window, const std::vector<sf::Image>& images, ra::enum_algorithms algo_numb, sf::Font font)
{
	sf::Texture texture;
	texture.loadFromImage(images[static_cast<int>(algo_numb)]);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(0, 0);

	sf::Text curr_algo;
	curr_algo.setFont(font);
	curr_algo.setPosition(100, 100);
	curr_algo.setCharacterSize(20);
	curr_algo.setColor(sf::Color::Red);
	switch (algo_numb)
	{
	case ra::dda:
		curr_algo.setString("Current algorithm is DDA");
		break;
	case ra::bresenham:
		curr_algo.setString("Current algorithm is Bresenham's");
		break;
	case ra::wu:
		curr_algo.setString("Current algorithm is Wu's");
		break;
	case ra::bcircle: 
		curr_algo.setString("Current algorithm is Bresenham's for circle");
		break;
	}

	sf::Text test_info;
	test_info.setFont(font);
	test_info.setPosition(100, 600);
	test_info.setCharacterSize(20);
	test_info.setColor(sf::Color::Green);
	test_info.setString("Press 'T' for runing performance tests...");

	window.draw(sprite);
	window.draw(curr_algo);
	window.draw(test_info);
};

/*	Generate vector with random coordinates and measure time, which needed for execution of these 3 algorithms.
	Result will printed in window.
*/
void make_tests(sf::RenderWindow& window, const sf::Font font, int num_test = 1000)
{
	//Make log-file
	std::ofstream log("log.txt");
	log << "Start tests. Creating vectors... \n";

	sf::Text test_state_info;
	test_state_info.setFont(font);
	test_state_info.setPosition(100, 100);
	test_state_info.setCharacterSize(20);
	test_state_info.setColor(sf::Color::Green);

	std::vector<sf::Vector2i> tests(num_test * 2);
	std::srand(unsigned(std::time(0)));

	//Fill vectors
	for (int i = 0; i < num_test * 2; i++)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			log << "ABORT";
			log.close();
			return;
		}
		tests[i].x = std::rand();
		tests[i].y = std::rand();
		test_state_info.setString("Created " + std::to_string(i) + "\\" + std::to_string(num_test * 2) + " vectors");
		log << "Created [" << i << "] = (" << tests[i].x << ", " << tests[i].y << ")\n";
		window.clear(sf::Color::White);
		window.draw(test_state_info);
		window.display();
	}

	//DDA test
	std::clock_t start = std::clock();
	for (int i = 0; i < num_test * 2; i += 2)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			log << "ABORT";
			log.close();
			return;
		}
		ra::line_algorithm_dda(tests[i], tests[i + 1]);
		test_state_info.setString("DDA test during " + std::to_string((std::clock() - start) / (double)CLOCKS_PER_SEC) + "   seconds, created " + std::to_string(i/2) + " lines.");
		window.clear(sf::Color::White);
		window.draw(test_state_info);
		window.display();
	}
	double dda_result = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	//Bresenhem
	start = std::clock();
	for (int i = 0; i < num_test * 2; i += 2)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			log << "ABORT";
			log.close();
			return;
		}
		ra::line_algorithm_bresenham(tests[i], tests[i + 1]);
		test_state_info.setString("Bresenhem test during " + std::to_string((std::clock() - start) / (double)CLOCKS_PER_SEC) + "   seconds, created " + std::to_string(i / 2) + " lines.");
		window.clear(sf::Color::White);
		window.draw(test_state_info);
		window.display();
	}
	double bresenham_result = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	//Wu
	start = std::clock();
	for (int i = 0; i < num_test * 2; i += 2)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			log << "ABORT";
			log.close();
			return;
		}
		ra::line_algorithm_wu(tests[i], tests[i + 1]);
		test_state_info.setString("Wu test during " + std::to_string((std::clock() - start) / (double)CLOCKS_PER_SEC) + "   seconds, created " + std::to_string(i / 2) + " lines.");
		window.clear(sf::Color::White);
		window.draw(test_state_info);
		window.display();
	}
	double wu_result = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	test_state_info.setString("All test done, results (press Enter to return):");
	sf::Text results;
	results.setFont(font);
	results.setPosition(100, 140);
	results.setCharacterSize(20);
	results.setColor(sf::Color::Red);
	results.setString("DDA: " + std::to_string(dda_result) + "  Bresenham: " + std::to_string(bresenham_result) + "   Wu: " + std::to_string(wu_result));
	log << "All tests done! Results: DDA - " << dda_result << " Bresenham - " << bresenham_result << "Wu - " << wu_result;
	log.close();

	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				return;
		window.clear(sf::Color::White);
		window.draw(test_state_info);
		window.draw(results);
		window.display();
	}
};

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Raster algorithms");
	//window.setFramerateLimit(60);

	const std::string font_file_path = "Content\\Font\\Y2K Neophyte Italic.ttf";
	sf::Font font;
	font.loadFromFile(font_file_path);

	std::vector<sf::Image> images = create_images();
	ra::enum_algorithms current_algo = ra::dda;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
				make_tests(window, font, NUM_OF_TESTS);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				//Decrease current algorithm enumeration
				current_algo = static_cast<ra::enum_algorithms>((static_cast<int>(current_algo) - 1) < 0 ? ra::AMOUNT_OF_ALGORITHMS - 1 : (static_cast<int>(current_algo) - 1));

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				//Increase current algorithm enumeration
				current_algo = static_cast<ra::enum_algorithms>((static_cast<int>(current_algo) + 1) % ra::AMOUNT_OF_ALGORITHMS);
		}

		
		window.clear(sf::Color::White);
		draw_frame(window, images, current_algo, font);
		window.display();
	}

	return 0;
}