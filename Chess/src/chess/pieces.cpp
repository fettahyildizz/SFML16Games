#include "chess/pieces.hpp"

Pieces::Pieces(const PIECE_NAMES &name, const int &row, const int &col)
    : name_(name) {
  figures_texture.loadFromFile(
      "/home/delivers6/SFML16Games/Chess/resources/images/figures.png");
  sprite_ = std::make_shared<sf::Sprite>(figures_texture);
  if (name < 6)
    isWhite = true;
  else
    isWhite = false;
  
  switch (name) {
  case WHITE_ROOK:
    sprite_->setTextureRect(sf::IntRect(0, SIZE, SIZE, SIZE));
    break;
  case WHITE_KNIGHT:
    sprite_->setTextureRect(sf::IntRect(SIZE, SIZE, SIZE, SIZE));
    break;
  case WHITE_BISHOP:
    sprite_->setTextureRect(sf::IntRect(2 * SIZE, SIZE, SIZE, SIZE));
    break;
  case WHITE_QUEEN:
    sprite_->setTextureRect(sf::IntRect(3 * SIZE, SIZE, SIZE, SIZE));
    break;
  case WHITE_KING:
    sprite_->setTextureRect(sf::IntRect(4 * SIZE, SIZE, SIZE, SIZE));
    break;
  case WHITE_PAWN:
    sprite_->setTextureRect(sf::IntRect(5 * SIZE, SIZE, SIZE, SIZE));
    break;
  case BLACK_ROOK:
    sprite_->setTextureRect(sf::IntRect(0, 0, SIZE, SIZE));
    break;
  case BLACK_KNIGHT:
    sprite_->setTextureRect(sf::IntRect(SIZE, 0, SIZE, SIZE));
    break;
  case BLACK_BISHOP:
    sprite_->setTextureRect(sf::IntRect(2 * SIZE, 0, SIZE, SIZE));
    break;
  case BLACK_QUEEN:
    sprite_->setTextureRect(sf::IntRect(3 * SIZE, 0, SIZE, SIZE));
    break;
  case BLACK_KING:
    sprite_->setTextureRect(sf::IntRect(4 * SIZE, 0, SIZE, SIZE));
    break;
  case BLACK_PAWN:
    sprite_->setTextureRect(sf::IntRect(5 * SIZE, 0, SIZE, SIZE));
    break;
  case EMPTY:
    break;
  }
  sprite_->setPosition(col * SIZE, row * SIZE);
  squareStatus_.resize(8); // resize row vector
  for (int i = 0; i < 8; i++) {
    squareStatus_[i].resize(8); // resize col vector
    for (int j = 0; j < 8; j++) {
      squareStatus_[i][j] = UNMOVEABLE;
    }
  }
}

void Pieces::checkMoveableSquares(
    std::vector<std::vector<PIECE_NAMES>> &board) {
  int col = getCol();
  int row = getRow();
  std::string name = getName();
  checks = false;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      squareStatus_[i][j] = UNMOVEABLE;
    }
  }
  switch (name_) {
  case WHITE_ROOK:
  case BLACK_ROOK:
    for (int x = col + 1; x < 8; x++) {
      if (x > 7 || x < 0) {
        break;
      }
      if (board[row][x] == EMPTY) {
        squareStatus_[row][x] = MOVEABLE;
      } else if (board[row][x] != EMPTY) {
        // If piece is White and occupying piece is black, then it's considered
        // takeable piece.
        if (name_ == WHITE_ROOK && board[row][x] >= 6) {
          if (board[row][x] == 10) {
            squareStatus_[row][x] = CHECK;
            checks = true;
          } else {
            squareStatus_[row][x] = TAKEABLE;
          }
          break;
        }
        // If piece is Black and occupying piece is white, then it's considered
        // takeable piece.
        else if (name_ == BLACK_ROOK && board[row][x] < 6) {
          if (board[row][x] == 4) {
            squareStatus_[row][x] = CHECK;
            checks = true;
          } else {
            squareStatus_[row][x] = TAKEABLE;
          }
          break;
        }
        // If piece and occupying piece is same color, then it's considered
        // unmoveable piece.
        else {
          squareStatus_[row][x] = UNMOVEABLE;
          break;
        }
      }
    }

    for (int x = col - 1; x >= 0; x--) {
      if (x > 7 || x < 0) {
        break;
      }
      if (board[row][x] == EMPTY) {
        squareStatus_[row][x] = MOVEABLE;
      } else if (board[row][x] != EMPTY) {

        // If piece is White and occupying piece is black, then it's considered
        // takeable piece.
        if (name_ == WHITE_ROOK && board[row][x] >= 6) {
          if (board[row][x] == 10) {
            squareStatus_[row][x] = CHECK;
            checks = true;
          } else {
            squareStatus_[row][x] = TAKEABLE;
          }
          break;
        }
        // If piece is Black and occupying piece is white, then it's considered
        // takeable piece.
        else if (name_ == BLACK_ROOK && board[row][x] < 6) {
          if (board[row][x] == 4) {
            squareStatus_[row][x] = CHECK;
            checks = true;
          } else {
            squareStatus_[row][x] = TAKEABLE;
          }
          break;
        }
        // If piece and occupying piece is same color, then it's considered
        // unmoveable piece.
        else {
          squareStatus_[row][x] = UNMOVEABLE;
          break;
        }
      }
    }

    for (int x = row + 1; x < 8; x++) {
      if (x > 7 || x < 0) {
        break;
      }
      if (board[x][col] == EMPTY) {
        squareStatus_[x][col] = MOVEABLE;
      } else if (board[x][col] != EMPTY) {
        // If piece is White and occupying piece is black, then it's considered
        // takeable piece.
        if (name_ == WHITE_ROOK && board[x][col] >= 6) {
          if (board[row][x] == 10) {
            squareStatus_[row][x] = CHECK;
            checks = true;
          } else {
            squareStatus_[row][x] = TAKEABLE;
          }
          break;
        }
        // If piece is Black and occupying piece is white, then it's considered
        // takeable piece.
        else if (name_ == BLACK_ROOK && board[x][col] < 6) {
          if (board[row][x] == 4) {
            squareStatus_[row][x] = CHECK;
            checks = true;
          } else {
            squareStatus_[row][x] = TAKEABLE;
          }
          break;
        }
        // If piece and occupying piece is same color, then it's considered
        // unmoveable piece.
        else {
          squareStatus_[x][col] = UNMOVEABLE;
          break;
        }
      }
    }

    for (int x = row - 1; x >= 0; x--) {
      if (x > 7 || x < 0) {
        break;
      }
      if (board[x][col] == EMPTY) {
        squareStatus_[x][col] = MOVEABLE;
      } else if (board[x][col] != EMPTY) {
        // If piece is White and occupying piece is black, then it's considered
        // takeable piece.
        if (name_ == WHITE_ROOK && board[x][col] >= 6) {
          if (board[row][x] == 10) {
            squareStatus_[row][x] = CHECK;
            checks = true;
          } else {
            squareStatus_[row][x] = TAKEABLE;
          }
          break;
        }
        // If piece is Black and occupying piece is white, then it's considered
        // takeable piece.
        else if (name_ == BLACK_ROOK && board[x][col] < 6) {
          if (board[row][x] == 4) {
            squareStatus_[row][x] = CHECK;
            checks = true;
          } else {
            squareStatus_[row][x] = TAKEABLE;
          }
          break;
        }
        // If piece and occupying piece is same color, then it's considered
        // unmoveable piece.
        else {
          squareStatus_[x][col] = UNMOVEABLE;
          break;
        }
      }
    }
    break;
  case WHITE_KNIGHT:
  case BLACK_KNIGHT:

    for (int yatay_move = -2; yatay_move < 3; yatay_move++) {
      for (int dikey_move = -2; dikey_move < 3; dikey_move++) {
        if (abs(yatay_move) + abs(dikey_move) != 3) {
          continue;
        }
        // If target is out of border of board.
        if ((row - dikey_move < 0) || (col - yatay_move < 0) ||
            (row - dikey_move > 7) || (col - yatay_move > 7)) {
          continue;
        }

        if (board[row - dikey_move][col - yatay_move] == EMPTY) {
          squareStatus_[row - dikey_move][col - yatay_move] = MOVEABLE;
        }
        // If target piece is not empty
        else {
          // If piece is white knight
          if (name_ == WHITE_KNIGHT) {
            // Target piece is black piece
            if (board[row - dikey_move][col - yatay_move] == 10) {
              squareStatus_[row - dikey_move][col - yatay_move] = CHECK;
              checks = true;
            } else if (board[row - dikey_move][col - yatay_move] >= 6) {
              squareStatus_[row - dikey_move][col - yatay_move] = TAKEABLE;
            }
            // Target piece is white piece
            else if (board[row - dikey_move][col - yatay_move] < 6) {
              squareStatus_[row - dikey_move][col - yatay_move] = UNMOVEABLE;
            }
          }
          // If piece is black knight
          else if (name_ == BLACK_KNIGHT) {
            // Target piece is white
            if (board[row - dikey_move][col - yatay_move] == 4) {
              squareStatus_[row - dikey_move][col - yatay_move] = CHECK;
              checks = true;
            } else if (board[row - dikey_move][col - yatay_move] < 6) {
              squareStatus_[row - dikey_move][col - yatay_move] = TAKEABLE;
            } else if (board[row - dikey_move][col - yatay_move] >= 6) {
              squareStatus_[row - dikey_move][col - yatay_move] = UNMOVEABLE;
            }
          }
        }
      }
    }
    break;

  case WHITE_BISHOP:
  case BLACK_BISHOP:
    for (int diagonal_col = 1; diagonal_col < 8; diagonal_col++) {
      bool flag = false;
      for (int diagonal_row = 1; diagonal_row < 8; diagonal_row++) {
        // Movement Restrains
        if ((row - diagonal_row < 0) || (col - diagonal_col < 0) ||
            (row - diagonal_row > 7) || (col - diagonal_col > 7)) {
          continue;
        }
        if (abs(diagonal_col) != abs(diagonal_row)) {
          continue;
        }
        // End of Movement Restrains

        if (board[row - diagonal_row][col - diagonal_col] == EMPTY) {
          squareStatus_[row - diagonal_row][col - diagonal_col] = MOVEABLE;

        } else {
          if (name_ == WHITE_BISHOP) {
            // Target piece is black piece
            if (board[row - diagonal_row][col - diagonal_col] == 10) {
              squareStatus_[row - diagonal_row][col - diagonal_col] = CHECK;
              checks = true;
              flag = true;
              break;
            } else if (board[row - diagonal_row][col - diagonal_col] >= 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] = TAKEABLE;
              flag = true;
              break;
            }
            // Target piece is white piece
            else if (board[row - diagonal_row][col - diagonal_col] < 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] =
                  UNMOVEABLE;
              flag = true;
              break;
            }
          }
          // If piece is black knight
          else if (name_ == BLACK_BISHOP) {
            // Target piece is white
            if (board[row - diagonal_row][col - diagonal_col] == 4) {
              squareStatus_[row - diagonal_row][col - diagonal_col] = CHECK;
              checks = true;
              flag = true;
              break;
            } else if (board[row - diagonal_row][col - diagonal_col] < 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] = TAKEABLE;
              flag = true;
              break;
            } else if (board[row - diagonal_row][col - diagonal_col] >= 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] =
                  UNMOVEABLE;
              flag = true;
              break;
            }
          }
        }
      }
      if (flag) {
        break;
      }
    }

    for (int diagonal_col = 1; diagonal_col < 8; diagonal_col++) {
      bool flag = false;
      for (int diagonal_row = -1; diagonal_row > -8; diagonal_row--) {
        // Movement Restrains
        if ((row - diagonal_row < 0) || (col - diagonal_col < 0) ||
            (row - diagonal_row > 7) || (col - diagonal_col > 7)) {
          continue;
        }
        if (abs(diagonal_col) != abs(diagonal_row)) {
          continue;
        }
        // End of Movement Restrains

        if (board[row - diagonal_row][col - diagonal_col] == EMPTY) {
          squareStatus_[row - diagonal_row][col - diagonal_col] = MOVEABLE;

        } else {
          if (name_ == WHITE_BISHOP) {
            // Target piece is black piece
            if (board[row - diagonal_row][col - diagonal_col] == 10) {
              squareStatus_[row - diagonal_row][col - diagonal_col] = CHECK;
              checks = true;
              flag = true;
              break;
            } else if (board[row - diagonal_row][col - diagonal_col] >= 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] = TAKEABLE;
              flag = true;
              break;
            }
            // Target piece is white piece
            else if (board[row - diagonal_row][col - diagonal_col] < 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] =
                  UNMOVEABLE;
              flag = true;
              break;
            }
          }
          // If piece is black knight
          else if (name_ == BLACK_BISHOP) {
            // Target piece is white
            if (board[row - diagonal_row][col - diagonal_col] == 4) {
              squareStatus_[row - diagonal_row][col - diagonal_col] = CHECK;
              checks = true;
              flag = true;
              break;
            } else if (board[row - diagonal_row][col - diagonal_col] < 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] = TAKEABLE;
              flag = true;
              break;
            } else if (board[row - diagonal_row][col - diagonal_col] >= 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] =
                  UNMOVEABLE;
              flag = true;
              break;
            }
          }
        }
      }
      if (flag) {
        break;
      }
    }

    for (int diagonal_col = -1; diagonal_col > -8; diagonal_col--) {
      bool flag = false;
      for (int diagonal_row = 1; diagonal_row < 8; diagonal_row++) {
        // Movement Restrains
        if ((row - diagonal_row < 0) || (col - diagonal_col < 0) ||
            (row - diagonal_row > 7) || (col - diagonal_col > 7)) {
          continue;
        }
        if (abs(diagonal_col) != abs(diagonal_row)) {
          continue;
        }
        // End of Movement Restrains

        if (board[row - diagonal_row][col - diagonal_col] == EMPTY) {
          squareStatus_[row - diagonal_row][col - diagonal_col] = MOVEABLE;

        } else {
          if (name_ == WHITE_BISHOP) {
            // Target piece is black piece
            if (board[row - diagonal_row][col - diagonal_col] == 10) {
              squareStatus_[row - diagonal_row][col - diagonal_col] = CHECK;
              checks = true;
              flag = true;
              break;
            } else if (board[row - diagonal_row][col - diagonal_col] >= 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] = TAKEABLE;
              flag = true;
              break;
            }
            // Target piece is white piece
            else if (board[row - diagonal_row][col - diagonal_col] < 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] =
                  UNMOVEABLE;
              flag = true;
              break;
            }
          }
          // If piece is black knight
          else if (name_ == BLACK_BISHOP) {
            // Target piece is white
            if (board[row - diagonal_row][col - diagonal_col] == 4) {
              squareStatus_[row - diagonal_row][col - diagonal_col] = CHECK;
              checks = true;
              flag = true;
              break;
            } else if (board[row - diagonal_row][col - diagonal_col] < 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] = TAKEABLE;
              flag = true;
              break;
            } else if (board[row - diagonal_row][col - diagonal_col] >= 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] =
                  UNMOVEABLE;
              flag = true;
              break;
            }
          }
        }
      }
      if (flag) {
        break;
      }
    }

    for (int diagonal_col = -1; diagonal_col > -8; diagonal_col--) {
      bool flag = false;
      for (int diagonal_row = -1; diagonal_row > -8; diagonal_row--) {
        // Movement Restrains
        if ((row - diagonal_row < 0) || (col - diagonal_col < 0) ||
            (row - diagonal_row > 7) || (col - diagonal_col > 7)) {
          continue;
        }
        if (abs(diagonal_col) != abs(diagonal_row)) {
          continue;
        }
        // End of Movement Restrains

        if (board[row - diagonal_row][col - diagonal_col] == EMPTY) {
          squareStatus_[row - diagonal_row][col - diagonal_col] = MOVEABLE;

        } else {
          if (name_ == WHITE_BISHOP) {
            // Target piece is black piece
            if (board[row - diagonal_row][col - diagonal_col] == 10) {
              squareStatus_[row - diagonal_row][col - diagonal_col] = CHECK;
              checks = true;
              flag = true;
              break;
            } else if (board[row - diagonal_row][col - diagonal_col] >= 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] = TAKEABLE;
              flag = true;
              break;
            }
            // Target piece is white piece
            else if (board[row - diagonal_row][col - diagonal_col] < 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] =
                  UNMOVEABLE;
              flag = true;
              break;
            }
          }
          // If piece is black knight
          else if (name_ == BLACK_BISHOP) {
            // Target piece is white
            if (board[row - diagonal_row][col - diagonal_col] == 4) {
              squareStatus_[row - diagonal_row][col - diagonal_col] = CHECK;
              checks = true;
              flag = true;
              break;
            } else if (board[row - diagonal_row][col - diagonal_col] < 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] = TAKEABLE;
              flag = true;
              break;
            } else if (board[row - diagonal_row][col - diagonal_col] >= 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] =
                  UNMOVEABLE;
              flag = true;
              break;
            }
          }
        }
      }
      if (flag) {
        break;
      }
    }
    break;

  case WHITE_QUEEN:
  case BLACK_QUEEN:

    for (int x = col + 1; x < 8; x++) {
      if (x > 7 || x < 0) {
        break;
      }
      if (board[row][x] == EMPTY) {
        squareStatus_[row][x] = MOVEABLE;
      } else if (board[row][x] != EMPTY) {
        // If piece is White and occupying piece is black, then it's considered
        // takeable piece.
        if (name_ == WHITE_QUEEN && board[row][x] >= 6) {
          if (board[row][x] == 10) {
            squareStatus_[row][x] = CHECK;
            std::cout << "col: " << x << " row: " << row << " Check\n";
            checks = true;
          } else {
            squareStatus_[row][x] = TAKEABLE;
          }
          break;
        }
        // If piece is Black and occupying piece is white, then it's considered
        // takeable piece.
        else if (name_ == BLACK_QUEEN && board[row][x] < 6) {
          if (board[row][x] == 4) {
            squareStatus_[row][x] = CHECK;
            std::cout << "col: " << x << " row: " << row << " Check\n";
            checks = true;
          } else {
            squareStatus_[row][x] = TAKEABLE;
          }
          break;
        }
        // If piece and occupying piece is same color, then it's considered
        // unmoveable piece.
        else {
          squareStatus_[row][x] = UNMOVEABLE;
          break;
        }
      }
    }

    for (int x = col - 1; x >= 0; x--) {
      if (x > 7 || x < 0) {
        break;
      }
      if (board[row][x] == EMPTY) {
        squareStatus_[row][x] = MOVEABLE;
      } else if (board[row][x] != EMPTY) {

        // If piece is White and occupying piece is black, then it's considered
        // takeable piece.
        if (name_ == WHITE_QUEEN && board[row][x] >= 6) {
          if (board[row][x] == 10) {
            squareStatus_[row][x] = CHECK;
            std::cout << "col: " << x << " row: " << row << " Check\n";
            checks = true;
          } else {
            squareStatus_[row][x] = TAKEABLE;
          }
          break;
        }
        // If piece is Black and occupying piece is white, then it's considered
        // takeable piece.
        else if (name_ == BLACK_QUEEN && board[row][x] < 6) {
          if (board[row][x] == 4) {
            squareStatus_[row][x] = CHECK;
            std::cout << "col: " << x << " row: " << row << " Check\n";
            checks = true;
          } else {
            squareStatus_[row][x] = TAKEABLE;
          }
          break;
        }
        // If piece and occupying piece is same color, then it's considered
        // unmoveable piece.
        else {
          squareStatus_[row][x] = UNMOVEABLE;
          break;
        }
      }
    }

    for (int x = row + 1; x < 8; x++) {
      if (x > 7 || x < 0) {
        break;
      }
      if (board[x][col] == EMPTY) {
        squareStatus_[x][col] = MOVEABLE;
      } else if (board[x][col] != EMPTY) {
        // If piece is White and occupying piece is black, then it's considered
        // takeable piece.
        if (name_ == WHITE_QUEEN && board[x][col] >= 6) {
          if (board[x][col] == 10) {
            squareStatus_[x][col] = CHECK;
            std::cout << "col: " << col << " row: " << x << " Check\n";
            checks = true;
          } else {
            squareStatus_[x][col] = TAKEABLE;
          }
          break;
        }
        // If piece is Black and occupying piece is white, then it's considered
        // takeable piece.
        else if (name_ == BLACK_QUEEN && board[x][col] < 6) {
          if (board[x][col] == 4) {
            squareStatus_[x][col] = CHECK;
            std::cout << "col: " << col << " row: " << x << " Check\n";
            checks = true;
          } else {
            squareStatus_[x][col] = TAKEABLE;
          }
          break;
        }
        // If piece and occupying piece is same color, then it's considered
        // unmoveable piece.
        else {
          squareStatus_[x][col] = UNMOVEABLE;
          break;
        }
      }
    }

    for (int x = row - 1; x >= 0; x--) {
      if (x > 7 || x < 0) {
        break;
      }

      if (board[x][col] == EMPTY) {
        squareStatus_[x][col] = MOVEABLE;
      } else if (board[x][col] != EMPTY) {
        // If piece is White and occupying piece is black, then it's considered
        // takeable piece.
        if (name_ == WHITE_QUEEN && board[x][col] >= 6) {
          if (board[x][col] == 10) {
            squareStatus_[x][col] = CHECK;
            std::cout << "col: " << col << " row: " << x << " Check\n";
            checks = true;
          } else {
            squareStatus_[x][col] = TAKEABLE;
          }
          break;
        }
        // If piece is Black and occupying piece is white, then it's considered
        // takeable piece.
        else if (name_ == BLACK_QUEEN && board[x][col] < 6) {
          if (board[x][col] == 4) {
            squareStatus_[x][col] = CHECK;
            std::cout << "col: " << col << " row: " << x << " Check\n";
            checks = true;
          } else {
            squareStatus_[x][col] = TAKEABLE;
          }
          break;
        }
        // If piece and occupying piece is same color, then it's considered
        // unmoveable piece.
        else {
          squareStatus_[x][col] = UNMOVEABLE;
          break;
        }
      }
    }

    for (int diagonal_col = 1; diagonal_col < 8; diagonal_col++) {
      bool flag = false;
      for (int diagonal_row = 1; diagonal_row < 8; diagonal_row++) {
        // Movement Restrains
        if ((row - diagonal_row < 0) || (col - diagonal_col < 0) ||
            (row - diagonal_row > 7) || (col - diagonal_col > 7)) {
          continue;
        }
        if (abs(diagonal_col) != abs(diagonal_row)) {
          continue;
        }
        // End of Movement Restrains

        if (board[row - diagonal_row][col - diagonal_col] == EMPTY) {
          squareStatus_[row - diagonal_row][col - diagonal_col] = MOVEABLE;

        } else {
          if (name_ == WHITE_QUEEN) {
            // Target piece is black piece
            if (board[row - diagonal_row][col - diagonal_col] >= 6) {
              if (board[row - diagonal_row][col - diagonal_col] == 10) {
                squareStatus_[row - diagonal_row][col - diagonal_col] = CHECK;
                std::cout << "col: " << col - diagonal_col << " row: " << row - diagonal_row << " Check\n";
                checks = true;
              } else {
                squareStatus_[row - diagonal_row][col - diagonal_col] =
                    TAKEABLE;
              }
              flag = true;
              break;
            }
            // Target piece is white piece
            else if (board[row - diagonal_row][col - diagonal_col] < 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] =
                  UNMOVEABLE;
              flag = true;
              break;
            }
          }
          // If piece is black knight
          else if (name_ == BLACK_QUEEN) {
            // Target piece is white
            if (board[row - diagonal_row][col - diagonal_col] < 6) {
              if (board[row - diagonal_row][col - diagonal_col] == 4) {
                squareStatus_[row - diagonal_row][col - diagonal_col] = CHECK;
                std::cout << "col: " << col - diagonal_col << " row: " << row - diagonal_row << " Check\n";
                checks = true;
              } else {
                squareStatus_[row - diagonal_row][col - diagonal_col] =
                    TAKEABLE;
              }
              flag = true;
              break;
            } else if (board[row - diagonal_row][col - diagonal_col] >= 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] =
                  UNMOVEABLE;
              flag = true;
              break;
            }
          }
        }
      }
      if (flag) {
        break;
      }
    }

    for (int diagonal_col = 1; diagonal_col < 8; diagonal_col++) {
      bool flag = false;
      for (int diagonal_row = -1; diagonal_row > -8; diagonal_row--) {
        // Movement Restrains
        if ((row - diagonal_row < 0) || (col - diagonal_col < 0) ||
            (row - diagonal_row > 7) || (col - diagonal_col > 7)) {
          continue;
        }
        if (abs(diagonal_col) != abs(diagonal_row)) {
          continue;
        }
        // End of Movement Restrains

        if (board[row - diagonal_row][col - diagonal_col] == EMPTY) {
          squareStatus_[row - diagonal_row][col - diagonal_col] = MOVEABLE;

        } else {
          if (name_ == WHITE_QUEEN) {
            // Target piece is black piece
            if (board[row - diagonal_row][col - diagonal_col] >= 6) {
              if (board[row - diagonal_row][col - diagonal_col] == 10) {
                squareStatus_[row - diagonal_row][col - diagonal_col] = CHECK;
                std::cout << "col: " << col - diagonal_col << " row: " << row - diagonal_row << " Check\n";
                checks = true;
              } else {
                squareStatus_[row - diagonal_row][col - diagonal_col] =
                    TAKEABLE;
              }
              flag = true;
              break;
            }
            // Target piece is white piece
            else if (board[row - diagonal_row][col - diagonal_col] < 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] =
                  UNMOVEABLE;
              flag = true;
              break;
            }
          }
          // If piece is black knight
          else if (name_ == BLACK_QUEEN) {
            // Target piece is white
            if (board[row - diagonal_row][col - diagonal_col] < 6) {
              if (board[row - diagonal_row][col - diagonal_col] == 4) {
                squareStatus_[row - diagonal_row][col - diagonal_col] = CHECK;
                std::cout << "col: " << col - diagonal_col << " row: " << row - diagonal_row << " Check\n";
                checks = true;
              } else {
                squareStatus_[row - diagonal_row][col - diagonal_col] =
                    TAKEABLE;
              }
              flag = true;
              break;
            } else if (board[row - diagonal_row][col - diagonal_col] >= 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] =
                  UNMOVEABLE;
              flag = true;
              break;
            }
          }
        }
      }
      if (flag) {
        break;
      }
    }

    for (int diagonal_col = -1; diagonal_col > -8; diagonal_col--) {
      bool flag = false;
      for (int diagonal_row = 1; diagonal_row < 8; diagonal_row++) {
        // Movement Restrains
        if ((row - diagonal_row < 0) || (col - diagonal_col < 0) ||
            (row - diagonal_row > 7) || (col - diagonal_col > 7)) {
          continue;
        }
        if (abs(diagonal_col) != abs(diagonal_row)) {
          continue;
        }
        // End of Movement Restrains

        if (board[row - diagonal_row][col - diagonal_col] == EMPTY) {
          squareStatus_[row - diagonal_row][col - diagonal_col] = MOVEABLE;

        } else {
          if (name_ == WHITE_QUEEN) {
            // Target piece is black piece
            if (board[row - diagonal_row][col - diagonal_col] >= 6) {
              if (board[row - diagonal_row][col - diagonal_col] == 10) {
                squareStatus_[row - diagonal_row][col - diagonal_col] = CHECK;
                std::cout << "col: " << col - diagonal_col << " row: " << row - diagonal_row << " Check\n";
                checks = true;
              } else {
                squareStatus_[row - diagonal_row][col - diagonal_col] =
                    TAKEABLE;
              }
              flag = true;
              break;
            }
            // Target piece is white piece
            else if (board[row - diagonal_row][col - diagonal_col] < 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] =
                  UNMOVEABLE;
              flag = true;
              break;
            }
          }
          // If piece is black knight
          else if (name_ == BLACK_QUEEN) {
            // Target piece is white
            if (board[row - diagonal_row][col - diagonal_col] < 6) {
              if (board[row - diagonal_row][col - diagonal_col] == 4) {
                squareStatus_[row - diagonal_row][col - diagonal_col] = CHECK;
                std::cout << "col: " << col - diagonal_col << " row: " << row - diagonal_row << " Check\n";
                checks = true;
              } else {
                squareStatus_[row - diagonal_row][col - diagonal_col] =
                    TAKEABLE;
              }
              flag = true;
              break;
            } else if (board[row - diagonal_row][col - diagonal_col] >= 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] =
                  UNMOVEABLE;
              flag = true;
              break;
            }
          }
        }
      }
      if (flag) {
        break;
      }
    }

    for (int diagonal_col = -1; diagonal_col > -8; diagonal_col--) {
      bool flag = false;
      for (int diagonal_row = -1; diagonal_row > -8; diagonal_row--) {
        // Movement Restrains
        if ((row - diagonal_row < 0) || (col - diagonal_col < 0) ||
            (row - diagonal_row > 7) || (col - diagonal_col > 7)) {
          continue;
        }
        if (abs(diagonal_col) != abs(diagonal_row)) {
          continue;
        }
        // End of Movement Restrains

        if (board[row - diagonal_row][col - diagonal_col] == EMPTY) {
          squareStatus_[row - diagonal_row][col - diagonal_col] = MOVEABLE;

        } else {
          if (name_ == WHITE_QUEEN) {
            // Target piece is black piece
            if (board[row - diagonal_row][col - diagonal_col] >= 6) {
              if (board[row - diagonal_row][col - diagonal_col] == 10) {
                squareStatus_[row - diagonal_row][col - diagonal_col] = CHECK;
                std::cout << "col: " << col - diagonal_col << " row: " << row - diagonal_row << " Check\n";
                checks = true;
              } else {
                squareStatus_[row - diagonal_row][col - diagonal_col] =
                    TAKEABLE;
              }
              flag = true;
              break;
            }
            // Target piece is white piece
            else if (board[row - diagonal_row][col - diagonal_col] < 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] =
                  UNMOVEABLE;
              flag = true;
              break;
            }
          }
          else if (name_ == BLACK_QUEEN) {
            // Target piece is white
            if (board[row - diagonal_row][col - diagonal_col] < 6) {
              if (board[row - diagonal_row][col - diagonal_col] == 4) {
                squareStatus_[row - diagonal_row][col - diagonal_col] = CHECK;
                std::cout << "col: " << col - diagonal_col << " row: " << row - diagonal_row << " Check\n";
                checks = true;
              } else {
                squareStatus_[row - diagonal_row][col - diagonal_col] =
                    TAKEABLE;
              }
              flag = true;
              break;
            } else if (board[row - diagonal_row][col - diagonal_col] >= 6) {
              squareStatus_[row - diagonal_row][col - diagonal_col] =
                  UNMOVEABLE;
              flag = true;
              break;
            }
          }
        }
      }
      if (flag) {
        break;
      }
    }
    break;
  case WHITE_KING:
  case BLACK_KING:
    if (col + 1 < 8) {
      if (board[row][col + 1] == EMPTY) {
        squareStatus_[row][col + 1] = MOVEABLE;
      } else if (board[row][col + 1] != EMPTY) {
        // If piece is White and occupying piece is black, then it's considered
        // takeable piece.
        if (name_ == WHITE_KING && board[row][col + 1] >= 6) {
          if (board[row][col + 1] == 10) {
            squareStatus_[row][col + 1] = UNMOVEABLE;
          } else {
            squareStatus_[row][col + 1] = TAKEABLE;
          }
        }
        // If piece is Black and occupying piece is white, then it's considered
        // takeable piece.
        else if (name_ == BLACK_KING && board[row][col + 1] < 6) {
          if (board[row][col + 1] == 4) {
            squareStatus_[row][col + 1] = UNMOVEABLE;
          } else {
            squareStatus_[row][col + 1] = TAKEABLE;
          }
        }
        // If piece and occupying piece is same color, then it's considered
        // unmoveable piece.
        else {
          squareStatus_[row][col + 1] = UNMOVEABLE;
        }
      }
    }

    ///////////////////////////////////////////////////////////////
    if (col - 1 > -1) {
      if (board[row][col - 1] == EMPTY) {
        squareStatus_[row][col - 1] = MOVEABLE;
      } else if (board[row][col - 1] != EMPTY) {
        // If piece is White and occupying piece is black, then it's considered
        // takeable piece.
        if (name_ == WHITE_KING && board[row][col - 1] >= 6) {
          if (board[row][col - 1] == 10) {
            squareStatus_[row][col - 1] = UNMOVEABLE;
          } else {
            squareStatus_[row][col - 1] = TAKEABLE;
          }
        }
        // If piece is Black and occupying piece is white, then it's considered
        // takeable piece.
        else if (name_ == BLACK_KING && board[row][col - 1] < 6) {
          if (board[row][col - 1] == 4) {
            squareStatus_[row][col - 1] = UNMOVEABLE;
          } else {
            squareStatus_[row][col - 1] = TAKEABLE;
          }
        }
        // If piece and occupying piece is same color, then it's considered
        // unmoveable piece.
        else {
          squareStatus_[row][col - 1] = UNMOVEABLE;
        }
      }
    }
    ///////////////////////////////////////////////////////////////
    if (row + 1 < 8) {
      if (board[row + 1][col] == EMPTY) {
        squareStatus_[row + 1][col] = MOVEABLE;
      } else if (board[row + 1][col] != EMPTY) {
        // If piece is White and occupying piece is black, then it's considered
        // takeable piece.
        if (name_ == WHITE_KING && board[row + 1][col] >= 6) {
          if (board[row + 1][col] == 10) {
            squareStatus_[row + 1][col] = UNMOVEABLE;
          } else {
            squareStatus_[row + 1][col] = TAKEABLE;
          }
        }
        // If piece is Black and occupying piece is white, then it's considered
        // takeable piece.
        else if (name_ == BLACK_KING && board[row + 1][col] < 6) {
          if (board[row + 1][col] == 4) {
            squareStatus_[row + 1][col] = UNMOVEABLE;
          } else {
            squareStatus_[row + 1][col] = TAKEABLE;
          }
        }
        // If piece and occupying piece is same color, then it's considered
        // unmoveable piece.
        else {
          squareStatus_[row + 1][col] = UNMOVEABLE;
        }
      }
    }

    if (row - 1 > -1) {
      if (board[row - 1][col] == EMPTY) {
        squareStatus_[row - 1][col] = MOVEABLE;
      } else if (board[row - 1][col] != EMPTY) {
        // If piece is White and occupying piece is black, then it's considered
        // takeable piece.
        if (name_ == WHITE_KING && board[row - 1][col] >= 6) {
          if (board[row - 1][col] == 10) {
            squareStatus_[row - 1][col] = UNMOVEABLE;
          } else {
            squareStatus_[row - 1][col] = TAKEABLE;
          }
        }
        // If piece is Black and occupying piece is white, then it's considered
        // takeable piece.
        else if (name_ == BLACK_KING && board[row - 1][col] < 6) {
          if (board[row - 1][col] == 4) {
            squareStatus_[row - 1][col] = UNMOVEABLE;
          } else {
            squareStatus_[row - 1][col] = TAKEABLE;
          }
        }
        // If piece and occupying piece is same color, then it's considered
        // unmoveable piece.
        else {
          squareStatus_[row - 1][col] = UNMOVEABLE;
        }
      }
    }
    /////////////////////////////////////////////////////////////////
    if (row - 1 > -1 && col - 1 > -1) {
      if (board[row - 1][col - 1] == EMPTY) {
        squareStatus_[row - 1][col - 1] = MOVEABLE;
      } else if (board[row - 1][col - 1] != EMPTY) {
        // If piece is White and occupying piece is black, then it's considered
        // takeable piece.
        if (name_ == WHITE_KING && board[row - 1][col - 1] >= 6) {
          if (board[row - 1][col - 1] == 10) {
            squareStatus_[row - 1][col - 1] = UNMOVEABLE;
          } else {
            squareStatus_[row - 1][col - 1] = TAKEABLE;
          }
        }
        // If piece is Black and occupying piece is white, then it's considered
        // takeable piece.
        else if (name_ == BLACK_KING && board[row - 1][col - 1] < 6) {
          if (board[row - 1][col - 1] == 4) {
            squareStatus_[row - 1][col - 1] = UNMOVEABLE;
          } else {
            squareStatus_[row - 1][col - 1] = TAKEABLE;
          }
        }
        // If piece and occupying piece is same color, then it's considered
        // unmoveable piece.
        else {
          squareStatus_[row - 1][col - 1] = UNMOVEABLE;
        }
      }
    }
    //////////////////////////////////////////////////////////////////
    if (row - 1 > -1 && col + 1 < 8) {
      if (board[row - 1][col + 1] == EMPTY) {
        squareStatus_[row - 1][col + 1] = MOVEABLE;
      } else if (board[row - 1][col + 1] != EMPTY) {
        // If piece is White and occupying piece is black, then it's considered
        // takeable piece.
        if (name_ == WHITE_KING && board[row - 1][col + 1] >= 6) {
          if (board[row - 1][col + 1] == 10) {
            squareStatus_[row - 1][col + 1] = UNMOVEABLE;
          } else {
            squareStatus_[row - 1][col + 1] = TAKEABLE;
          }
        }
        // If piece is Black and occupying piece is white, then it's considered
        // takeable piece.
        else if (name_ == BLACK_KING && board[row - 1][col + 1] < 6) {
          if (board[row - 1][col + 1] == 4) {
            squareStatus_[row - 1][col + 1] = UNMOVEABLE;
          } else {
            squareStatus_[row - 1][col + 1] = TAKEABLE;
          }
        }
        // If piece and occupying piece is same color, then it's considered
        // unmoveable piece.
        else {
          squareStatus_[row - 1][col + 1] = UNMOVEABLE;
        }
      }
    }
    ///////////////////////////////////////////////////////////////
    if (row + 1 < 8 && col + 1 < 8) {
      if (board[row + 1][col + 1] == EMPTY) {
        squareStatus_[row + 1][col + 1] = MOVEABLE;
      } else if (board[row + 1][col + 1] != EMPTY) {
        // If piece is White and occupying piece is black, then it's considered
        // takeable piece.
        if (name_ == WHITE_KING && board[row + 1][col + 1] >= 6) {
          if (board[row + 1][col + 1] == 10) {
            squareStatus_[row + 1][col + 1] = UNMOVEABLE;
          } else {
            squareStatus_[row + 1][col + 1] = TAKEABLE;
          }
        }
        // If piece is Black and occupying piece is white, then it's considered
        // takeable piece.
        else if (name_ == BLACK_KING && board[row + 1][col + 1] < 6) {
          if (board[row + 1][col + 1] == 4) {
            squareStatus_[row + 1][col + 1] = UNMOVEABLE;
          } else {
            squareStatus_[row + 1][col + 1] = TAKEABLE;
          }
        }
        // If piece and occupying piece is same color, then it's considered
        // unmoveable piece.
        else {
          squareStatus_[row + 1][col + 1] = UNMOVEABLE;
        }
      }
    }
    ///////////////////////////////////////////////////////////////
    if (row + 1 < 8 && col - 1 > -1) {
      if (board[row + 1][col - 1] == EMPTY) {
        squareStatus_[row + 1][col - 1] = MOVEABLE;
      } else if (board[row + 1][col - 1] != EMPTY) {
        // If piece is White and occupying piece is black, then it's considered
        // takeable piece.
        if (name_ == WHITE_KING && board[row + 1][col - 1] >= 6) {
          if (board[row + 1][col - 1] == 10) {
            squareStatus_[row + 1][col - 1] = UNMOVEABLE;
          } else {
            squareStatus_[row + 1][col - 1] = TAKEABLE;
          }
        }
        // If piece is Black and occupying piece is white, then it's considered
        // takeable piece.
        else if (name_ == BLACK_KING && board[row + 1][col - 1] < 6) {
          if (board[row + 1][col - 1] == 10) {
            squareStatus_[row + 1][col - 1] = UNMOVEABLE;
          } else {
            squareStatus_[row + 1][col - 1] = TAKEABLE;
          }
        }
        // If piece and occupying piece is same color, then it's considered
        // unmoveable piece.
        else {
          squareStatus_[row + 1][col - 1] = UNMOVEABLE;
        }
      }
    }
    break;
  case WHITE_PAWN:
    if (row != 0) {
      if (row == 6) {
        if (board[row - 2][col] == EMPTY) {
          squareStatus_[row - 2][col] = MOVEABLE;
        }
      }
      if (board[row - 1][col] == EMPTY) {
        squareStatus_[row - 1][col] = MOVEABLE;
      }
      if (board[row - 1][col - 1] >= 6 && board[row - 1][col - 1] != 12) {
        if (board[row - 1][col - 1] == 10) {
          squareStatus_[row - 1][col - 1] = CHECK;
          checks = true;
        } else {
          squareStatus_[row - 1][col - 1] = TAKEABLE;
        }
      }
      if (board[row - 1][col + 1] >= 6 && board[row - 1][col + 1] != 12) {
        if (board[row - 1][col + 1] == 10) {
          squareStatus_[row - 1][col + 1] = CHECK;
          checks = true;
        } else {
          squareStatus_[row - 1][col + 1] = TAKEABLE;
        }
      }
    }
    break;
  case BLACK_PAWN:
    if (row != 7) {
      if (row == 1) {
        if (board[row + 2][col] == EMPTY) {
          squareStatus_[row + 2][col] = MOVEABLE;
        }
      }
      if (board[row + 1][col] == EMPTY) {
        squareStatus_[row + 1][col] = MOVEABLE;
      }
      if (board[row + 1][col - 1] < 6) {
        if (board[row + 1][col - 1] == 10) {
          squareStatus_[row + 1][col - 1] = CHECK;
          checks = true;
        } else {
          squareStatus_[row + 1][col - 1] = TAKEABLE;
        }
      }
      if (board[row + 1][col + 1] < 6) {
        if (board[row + 1][col + 1] == 4) {
          squareStatus_[row + 1][col + 1] = CHECK;
          checks = true;
        } else {
          squareStatus_[row + 1][col + 1] = TAKEABLE;
        }
      }
    }
    break;
  case EMPTY:
    break;
  }
}

void Pieces::move(const int &x, const int &y) { sprite_->setPosition(x, y); }

const bool Pieces::getChecks() const { return checks; }

const sf::Sprite &Pieces::getSprite() const { return *sprite_; }

const std::string Pieces::getName() const { return getPieceName(name_); }

const std::string Pieces::getNote() const {
  return toChessNote(sprite_->getPosition().x / SIZE,
                     sprite_->getPosition().y / SIZE);
}

const PIECE_NAMES Pieces::getPieceEnum() const { return name_; }

const std::vector<std::vector<SQUARE_STATUS>> Pieces::getSquareStatus() const {
  return squareStatus_;
}

const int Pieces::getCol() const { return sprite_->getPosition().x / SIZE; }
const int Pieces::getRow() const { return sprite_->getPosition().y / SIZE; }

void updateBoardStatus(const std::vector<std::shared_ptr<Pieces>> &pieces,
                       std::vector<std::vector<PIECE_NAMES>> &board) {
  for (int row = 0; row < board.size(); row++) {
    for (int col = 0; col < board[row].size(); col++) {
      bool found = false;
      for (int i = 0; i < pieces.size(); i++) {
        if (pieces[i]->getSprite().getGlobalBounds().contains(col * SIZE,
                                                              row * SIZE)) {
          board[row][col] = pieces[i]->getPieceEnum();
          found = true;
          break;
        }
      }
      if (!found) {
        board[row][col] = PIECE_NAMES::EMPTY;
      }
    }
  }
}

std::string toChessNote(const int &col, const int &row) {
  std::string ret = "";
  char temp_x = char((8 - row) + 48);
  char temp_y = col + 97;
  ret += temp_y;
  ret += temp_x;
  return ret;
}