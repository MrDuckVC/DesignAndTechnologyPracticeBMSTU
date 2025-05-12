#pragma once

#include <SFML/Graphics.hpp>

namespace chess {
const int BOARD_SIZE = 8;
const int WINDOW_SIZE = 1000;

const sf::Color WHITE_CELL_COLOR = sf::Color(240, 195, 128);
const sf::Color BLACK_CELL_COLOR = sf::Color(109, 62, 23);
const sf::Color SELECTED_FIGURE_CELL_COLOR = sf::Color(68, 117, 69);
const sf::Color CAN_MOVE_TO_CELL_COLOR = sf::Color(104, 179, 105);
const sf::Color CANT_MOVE_FIGURE_CELL_COLOR = sf::Color(117, 35, 18);
const sf::Color CAN_ATTACK_CELL_COLOR = sf::Color(44, 77, 45);

const std::string WHITE_PAWN_IMAGE_PATH = "assests/chess/pawn.png";
const std::string BLACK_PAWN_IMAGE_PATH = "assests/chess/pawn1.png";
const std::string WHITE_KNIGHT_IMAGE_PATH = "assests/chess/knight.png";
const std::string BLACK_KNIGHT_IMAGE_PATH = "assests/chess/knight1.png";
const std::string WHITE_BISHOP_IMAGE_PATH = "assests/chess/bishop.png";
const std::string BLACK_BISHOP_IMAGE_PATH = "assests/chess/bishop1.png";
const std::string WHITE_ROOK_IMAGE_PATH = "assests/chess/rook.png";
const std::string BLACK_ROOK_IMAGE_PATH = "assests/chess/rook1.png";
const std::string WHITE_QUEEN_IMAGE_PATH = "assests/chess/queen.png";
const std::string BLACK_QUEEN_IMAGE_PATH = "assests/chess/queen1.png";
const std::string WHITE_KING_IMAGE_PATH = "assests/chess/king.png";
const std::string BLACK_KING_IMAGE_PATH = "assests/chess/king1.png";
}
