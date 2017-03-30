#include "RasterAlgorithms.h"

namespace ra
{

	sf::Image create_image(const std::vector<PseudoPixel>& pixels, const int size, const sf::Color& background)
	{
		sf::Image ret_value;
		//Search max x and y coordinate, adding 2 (spare area) and multipling this value on size
		int width = (int)(std::max_element(pixels.begin(), pixels.end(),
			[](const PseudoPixel& lhs, const PseudoPixel& rhs)->bool{return lhs.coordinate.x < rhs.coordinate.x; })->coordinate.x + 2) * size;
		int height = (int)(std::max_element(pixels.begin(), pixels.end(),
			[](const PseudoPixel& lhs, const PseudoPixel& rhs)->bool{return lhs.coordinate.y < rhs.coordinate.y; })->coordinate.y + 2) * size;

		ret_value.create(width, height, background);
		for (auto it = pixels.begin(); it != pixels.end(); ++it)
		{
			for (int i = 0; i < size; ++i)
				for (int j = 0; j < size; ++j)
				{
					ret_value.setPixel((int)(it->coordinate.x * size + j), (int)(it->coordinate.y * size + i), it->color);
				}
		};

		return ret_value;
	};

	std::vector<PseudoPixel> line_algorithm_dda(sf::Vector2i beg_pos, sf::Vector2i end_pos, const sf::Color& color)
	{
		int length = (int)std::sqrt(pow((beg_pos.x - end_pos.x), 2) + pow((beg_pos.y - end_pos.y), 2)) + 1;
		std::vector<PseudoPixel> ret_value(length);
		sf::Vector2f delta;
		delta.x = ((end_pos.x - beg_pos.x) / (float)(length - 1));
		delta.y = ((end_pos.y - beg_pos.y) / (float)(length - 1));

		int i;
		for (i = 0; i < length; ++i)
		{
			ret_value[i].color = color;
			ret_value[i].coordinate.x = beg_pos.x + delta.x * (float)i;
			ret_value[i].coordinate.y = beg_pos.y + delta.y * (float)i;
		};

		ret_value.resize(i);
		return ret_value;
	};

	std::vector<PseudoPixel> line_algorithm_bresenham(sf::Vector2i beg_pos, sf::Vector2i end_pos, const sf::Color& color)
	{
		int length = (int)std::sqrt(pow((beg_pos.x - end_pos.x), 2) + pow((beg_pos.y - end_pos.y), 2)) + 1;
		std::vector<PseudoPixel> ret_value(length);

		const int dx = std::abs(end_pos.x - beg_pos.x);
		const int dy = std::abs(end_pos.y - beg_pos.y);
		const int step_x = beg_pos.x < end_pos.x ? 1 : -1;
		const int step_y = beg_pos.y < end_pos.y ? 1 : -1;

		int error = dx - dy;
		int i = 0;

		while (beg_pos.x != end_pos.x || beg_pos.y != end_pos.y)
		{
			ret_value[i].coordinate.x = beg_pos.x;;
			ret_value[i].coordinate.y = beg_pos.y;
			ret_value[i].color = color;
			const int error2 = error * 2;
			++i;

			if (error2 > -dy)
			{
				error -= dy;
				beg_pos.x += step_x;
			}

			if (error2 < dx)
			{
				error += dx;
				beg_pos.y += step_y;
			}

		}
		//Last pixel
		ret_value[i].coordinate.x = beg_pos.x;;
		ret_value[i].coordinate.y = beg_pos.y;
		ret_value[i].color = color;
		++i;

		ret_value.resize(i);

		return ret_value;
	};

	std::vector<PseudoPixel> line_algorithm_wu(sf::Vector2i beg_pos, sf::Vector2i end_pos, const sf::Color& color)
	{
		int dx = (end_pos.x > beg_pos.x) ? (end_pos.x - beg_pos.x) : (beg_pos.x - end_pos.x);
		int dy = (end_pos.y > beg_pos.y) ? (end_pos.y - beg_pos.y) : (beg_pos.y - end_pos.y);

		//If any line is parallel by axis coordinate, draw line using Bresenham's algorithm 
		if ((int)dx == 0 || (int)dy == 0)
		{
			return line_algorithm_bresenham(beg_pos, end_pos, color);
		}

		//Smoothing pixels
		const int smooth = 2;
		int length = (int)std::sqrt(pow((beg_pos.x - end_pos.x), 2) + pow((beg_pos.y - end_pos.y), 2)) * smooth;
		std::vector<PseudoPixel> ret_value(length);

		//Just for using modf
		float int_part = 0;
		float float_part = 0;

		if (dy < dx)
		{
			if (end_pos.x < beg_pos.x)
			{
				std::swap(beg_pos.x, end_pos.x);
				std::swap(beg_pos.y, end_pos.y);
			}

			int sign = end_pos.y > beg_pos.y ? 1 : -1;

			float gradient = dy / (float)dx;
			float iter = beg_pos.y + sign * gradient;
			//First pixel
			ret_value[0].coordinate.x = beg_pos.x;
			ret_value[0].coordinate.y = beg_pos.y;
			ret_value[0].color = color;

			int i = 1;
			for (int x = (int)(beg_pos.x + 1); x < end_pos.x; ++x, i += 2)
			{
				//Top pixel
				float_part = std::modf(iter, &int_part);
				ret_value[i].coordinate.x = x;
				ret_value[i].coordinate.y = int_part;
				ret_value[i].color = color;
				ret_value[i].color.a *= (1 - float_part);

				//Bottom pixel
				float_part = std::modf(iter, &int_part);
				ret_value[i + 1].coordinate.x = x;
				ret_value[i + 1].coordinate.y = int_part + 1;
				ret_value[i + 1].color = color;
				ret_value[i + 1].color.a *= float_part;

				iter += sign * gradient;
			}

			//Last pixel
			ret_value[i].coordinate.x = end_pos.x;
			ret_value[i].coordinate.y = end_pos.y;
			ret_value[i].color = color;
			++i;

			ret_value.resize(i);
		}
		else
		{
			if (end_pos.y < beg_pos.y)
			{
				std::swap(beg_pos.x, end_pos.x);
				std::swap(beg_pos.y, end_pos.y);
			}

			int sign = end_pos.x > beg_pos.x ? 1 : -1;

			float gradient = dx / (float)dy;
			float iter = beg_pos.x + sign * gradient;

			//First pixel
			ret_value[0].coordinate.x = beg_pos.x;
			ret_value[0].coordinate.y = beg_pos.y;
			ret_value[0].color = color;

			int i = 1;
			for (int y = (int)(beg_pos.y + 1); y < end_pos.y; ++y, i += 2)
			{
				//Top pixel
				float_part = std::modf(iter, &int_part);
				ret_value[i].coordinate.x = int_part;
				ret_value[i].coordinate.y = y;
				ret_value[i].color = color;
				ret_value[i].color.a *= (1 - float_part);

				//Bottom pixel
				float_part = std::modf(iter, &int_part);
				ret_value[i + 1].coordinate.x = int_part + 1;
				ret_value[i + 1].coordinate.y = y;
				ret_value[i + 1].color = color;
				ret_value[i + 1].color.a *= float_part;

				iter += sign * gradient;
			}

			//Last pixel
			ret_value[i].coordinate.x = end_pos.x;
			ret_value[i].coordinate.y = end_pos.y;
			ret_value[i].color = color;
			++i;

			ret_value.resize(i);
		}

		return ret_value;
	};

	std::vector<PseudoPixel> circle_algorithm_bresenham(const sf::Vector2i& center, int radius, const sf::Color& color)
	{
		int size = static_cast<int>(3 * radius * M_PI);
		std::vector<PseudoPixel> ret_value(size);

		int x = static_cast<int>(radius);
		int y = 0;
		int dx = static_cast<int>(1 - 2 * radius);
		int dy = 1;
		int error = 0;

		int i = 0;
		while (x > y)
		{
			//Plot 8 points
			ret_value[i] = {sf::Vector2f(center.x + x, center.y + y), color};
			ret_value[i + 1] = { sf::Vector2f(center.x - x, center.y + y), color };
			ret_value[i + 2] = { sf::Vector2f(center.x - x, center.y - y), color };
			ret_value[i + 3] = { sf::Vector2f(center.x + x, center.y - y), color };
			ret_value[i + 4] = { sf::Vector2f(center.x + y, center.y + x), color };
			ret_value[i + 5] = { sf::Vector2f(center.x - y, center.y + x), color };
			ret_value[i + 6] = { sf::Vector2f(center.x - y, center.y - x), color };
			ret_value[i + 7] = { sf::Vector2f(center.x + y, center.y - x), color };

			y++;
			error += dy;
			dy += 2;

			if (2 * error + dx > 0)
			{
				x--;
				error += dx;
				dx += 2;
			}

			i += 8;
		}

		ret_value.resize(i);

		return ret_value;
	};
};