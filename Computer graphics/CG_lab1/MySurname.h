#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

/*
	This header contain the coordinates, using which i can draw my own surname.
	It's first task for my laboratory work.
*/

///TODO: resize letters, add other letters
const std::vector<sf::Vector2i> MY_SURNAME = 
{  
	//K
	sf::Vector2i(10, 30), sf::Vector2i(10, 75),
	sf::Vector2i(10, 55), sf::Vector2i(25, 30),
	sf::Vector2i(10, 55), sf::Vector2i(25, 75),

	//o
	sf::Vector2i(25, 45), sf::Vector2i(25, 70),
	sf::Vector2i(25, 70), sf::Vector2i(30, 75),
	sf::Vector2i(30, 75), sf::Vector2i(35, 75),
	sf::Vector2i(35, 75), sf::Vector2i(40, 70),
	sf::Vector2i(40, 70), sf::Vector2i(40, 45),
	sf::Vector2i(40, 45), sf::Vector2i(35, 40),
	sf::Vector2i(35, 40), sf::Vector2i(30, 40),
	sf::Vector2i(30, 40), sf::Vector2i(25, 45),

	//m
	sf::Vector2i(45, 40), sf::Vector2i(45, 75),
	sf::Vector2i(45, 45), sf::Vector2i(50, 40),
	sf::Vector2i(50, 40), sf::Vector2i(55, 45),
	sf::Vector2i(55, 45), sf::Vector2i(55, 75),
	sf::Vector2i(55, 45), sf::Vector2i(60, 40),
	sf::Vector2i(60, 40), sf::Vector2i(65, 45),
	sf::Vector2i(65, 45), sf::Vector2i(65, 75),

	//a
	sf::Vector2i(70, 45), sf::Vector2i(75, 40),
	sf::Vector2i(75, 40), sf::Vector2i(80, 40),
	sf::Vector2i(80, 40), sf::Vector2i(83, 45),
	sf::Vector2i(83, 45), sf::Vector2i(83, 75),
	sf::Vector2i(83, 70), sf::Vector2i(80, 75),
	sf::Vector2i(80, 75), sf::Vector2i(75, 75),
	sf::Vector2i(75, 75), sf::Vector2i(70, 70),
	sf::Vector2i(70, 70), sf::Vector2i(70, 60),
	sf::Vector2i(70, 60), sf::Vector2i(75, 57),
	sf::Vector2i(75, 57), sf::Vector2i(80, 57),
	sf::Vector2i(80, 57), sf::Vector2i(83, 60),

	//r
	sf::Vector2i(88, 75), sf::Vector2i(88, 40),
	sf::Vector2i(88, 43), sf::Vector2i(91, 40),
	sf::Vector2i(91, 40), sf::Vector2i(94, 40),
	sf::Vector2i(94, 40), sf::Vector2i(97, 43),

	//y
	sf::Vector2i(100, 40), sf::Vector2i(107, 55),
	sf::Vector2i(107, 55), sf::Vector2i(114, 40),
	sf::Vector2i(107, 55), sf::Vector2i(107, 75),

	//a
	sf::Vector2i(117, 45), sf::Vector2i(122, 40),
	sf::Vector2i(122, 40), sf::Vector2i(127, 40),
	sf::Vector2i(127, 40), sf::Vector2i(130, 45),
	sf::Vector2i(130, 45), sf::Vector2i(130, 75),
	sf::Vector2i(130, 70), sf::Vector2i(127, 75),
	sf::Vector2i(127, 75), sf::Vector2i(122, 75),
	sf::Vector2i(122, 75), sf::Vector2i(117, 70),
	sf::Vector2i(117, 70), sf::Vector2i(117, 60),
	sf::Vector2i(117, 60), sf::Vector2i(122, 57),
	sf::Vector2i(122, 57), sf::Vector2i(127, 57),
	sf::Vector2i(127, 57), sf::Vector2i(130, 60),

	//n
	sf::Vector2i(135, 40), sf::Vector2i(135, 75),
	sf::Vector2i(135, 43), sf::Vector2i(140, 40),
	sf::Vector2i(140, 40), sf::Vector2i(144, 40),
	sf::Vector2i(144, 40), sf::Vector2i(148, 45),
	sf::Vector2i(148, 45), sf::Vector2i(148, 75),

	//s
	sf::Vector2i(151, 73), sf::Vector2i(155, 75),
	sf::Vector2i(155, 75), sf::Vector2i(158, 75),
	sf::Vector2i(158, 75), sf::Vector2i(161, 72),
	sf::Vector2i(161, 72), sf::Vector2i(160, 67),
	sf::Vector2i(160, 67), sf::Vector2i(151, 48),
	sf::Vector2i(151, 48), sf::Vector2i(152, 43),
	sf::Vector2i(152, 43), sf::Vector2i(155, 40),
	sf::Vector2i(155, 40), sf::Vector2i(158, 40),
	sf::Vector2i(158, 40), sf::Vector2i(162, 42),

	//k
	sf::Vector2i(165, 40), sf::Vector2i(165, 75),
	sf::Vector2i(165, 62), sf::Vector2i(172, 45),
	sf::Vector2i(165, 63), sf::Vector2i(172, 75),

	//i
	sf::Vector2i(175, 45), sf::Vector2i(175, 75),
	sf::Vector2i(175, 40), sf::Vector2i(175, 42),

	//y
	sf::Vector2i(178, 40), sf::Vector2i(185, 55),
	sf::Vector2i(185, 55), sf::Vector2i(191, 40),
	sf::Vector2i(185, 55), sf::Vector2i(185, 75),

	//=)
	sf::Vector2i(190, 55), sf::Vector2i(200, 55),
	sf::Vector2i(190, 60), sf::Vector2i(200, 60),
	sf::Vector2i(200, 40), sf::Vector2i(202, 45),
	sf::Vector2i(202, 45), sf::Vector2i(205, 50),
	sf::Vector2i(205, 50), sf::Vector2i(205, 65),
	sf::Vector2i(202, 70), sf::Vector2i(205, 65),
	sf::Vector2i(200, 75), sf::Vector2i(202, 70)

};