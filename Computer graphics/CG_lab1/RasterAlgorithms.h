#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <SFML/Graphics.hpp>


/*Raster Algorithms*/
namespace ra
{

	const int DEFAULT_PSEUDO_PIXEL_SIZE = 5;
	const int AMOUNT_OF_LINE_ALGORITHMS = 3;
	const int AMOUNT_OF_ALGORITHMS = 4;

	typedef enum { dda, bresenham, wu, bcircle } enum_algorithms;

	struct PseudoPixel
	{
		sf::Vector2f coordinate;
		sf::Color color;
	};

	typedef std::vector<PseudoPixel>(*algo_func)(sf::Vector2i, sf::Vector2i, const sf::Color&);

	/*
	return value: sf::Image
	Create image, created using by pseudo pixels
	1 param: vector with Pseudo pixels, which contain coordinates and pixel color
	2 param: size of pseudo pixel - default this value equal const global variable DEFAULT_PSEUDO_PIXEL_SIZE real pixels
	*/
	sf::Image create_image(const std::vector<PseudoPixel>& pixels, const int size = DEFAULT_PSEUDO_PIXEL_SIZE, const sf::Color& background = sf::Color::Black);

	std::vector<PseudoPixel> line_algorithm_dda(sf::Vector2i beg_pos, sf::Vector2i end_pos, const sf::Color& color = sf::Color::White);

	std::vector<PseudoPixel> line_algorithm_bresenham(sf::Vector2i beg_pos, sf::Vector2i end_pos, const sf::Color& color = sf::Color::White);

	std::vector<PseudoPixel> line_algorithm_wu(sf::Vector2i beg_pos, sf::Vector2i end_pos, const sf::Color& color = sf::Color::White);

	std::vector<PseudoPixel> circle_algorithm_bresenham(const sf::Vector2i& center, int radius, const sf::Color& color = sf::Color::White);
};