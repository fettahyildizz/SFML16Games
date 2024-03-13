#ifndef PIECES_HPP
#define PIECES_HPP

#include "SFML/Graphics.hpp"
#include "chess/chess.hpp"

static sf::Texture figures_texture;

enum SQUARE_STATUS { CHECK, MOVEABLE, TAKEABLE, UNMOVEABLE };

enum PIECE_NAMES {
  WHITE_ROOK,
  WHITE_KNIGHT,
  WHITE_BISHOP,
  WHITE_QUEEN,
  WHITE_KING,
  WHITE_PAWN,
  BLACK_ROOK,
  BLACK_KNIGHT,
  BLACK_BISHOP,
  BLACK_QUEEN,
  BLACK_KING,
  BLACK_PAWN,
  EMPTY
};

inline std::string getPieceName(const PIECE_NAMES &p) {
  switch (p) {
  case WHITE_ROOK:
    return "WHITE_ROOK";
  case WHITE_KNIGHT:
    return "WHITE_KNIGHT";
  case WHITE_BISHOP:
    return "WHITE_BISHOP";
  case WHITE_QUEEN:
    return "WHITE_QUEEN";
  case WHITE_KING:
    return "WHITE_KING";
  case WHITE_PAWN:
    return "WHITE_PAWN";
  case BLACK_ROOK:
    return "BLACK_ROOK";
  case BLACK_KNIGHT:
    return "BLACK_KNIGHT";
  case BLACK_BISHOP:
    return "BLACK_BISHOP";
  case BLACK_QUEEN:
    return "BLACK_QUEEN";
  case BLACK_KING:
    return "BLACK_KING";
  case BLACK_PAWN:
    return "BLACK_PAWN";
  case EMPTY:
    return "EMPTY";
  default:
    return "Unknown Piece Type";
  }
}
class Pieces {
  PIECE_NAMES name_;
  sf::Vector2i position_;
  std::shared_ptr<sf::Sprite> sprite_;
public:

  Pieces(const PIECE_NAMES &name, const int &row, const int &col);
  /**
  * @param board [row][col]
  */
  void checkMoveableSquares(std::vector<std::vector<PIECE_NAMES>>& board);
  void move(const int &x, const int &y);
  const bool getChecks() const;
  const sf::Sprite &getSprite() const;
  const std::string getName() const;
  const std::string getNote() const;
  const PIECE_NAMES getPieceEnum() const;
  const std::vector<std::vector<SQUARE_STATUS>> getSquareStatus() const;
  const int getCol() const;
  const int getRow() const;
  
  bool checks { false };
  bool isWhite;
  std::vector<std::vector<SQUARE_STATUS>> squareStatus_; /* index order [row][col]*/
};

void updateBoardStatus(const std::vector<std::shared_ptr<Pieces>> &pieces, std::vector<std::vector<PIECE_NAMES>>& board);
std::string toChessNote(const int &x, const int &y);
#endif