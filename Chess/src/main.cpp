#include "chess/chess.hpp"
#include "chess/pieces.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

using namespace sf;

// [row][col]
std::vector<std::vector<PIECE_NAMES>> board{
    {BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, BLACK_KING,
     BLACK_BISHOP, BLACK_KNIGHT, BLACK_ROOK},
    {BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN,
     BLACK_PAWN, BLACK_PAWN},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN,
     WHITE_PAWN, WHITE_PAWN},
    {WHITE_ROOK, WHITE_KNIGHT, WHITE_BISHOP, WHITE_QUEEN, WHITE_KING,
     WHITE_BISHOP, WHITE_KNIGHT, WHITE_ROOK},
};

int main() {
  RenderWindow app(VideoMode(W, H), "Chess");
  app.setFramerateLimit(FRAME_LIMIT);
  sf::Texture board_texture;
  board_texture.loadFromFile(
      "/home/delivers6/SFML16Games/Chess/resources/images/board0.png");
  sf::Sprite board_sprite(board_texture);

  std::vector<std::shared_ptr<Pieces>> pieces;
  pieces.reserve(32);
  for (int row = 0; row < board.size(); row++) {
    for (int col = 0; col < board[row].size(); col++) {
      if (board[row][col] != PIECE_NAMES::EMPTY) {
        std::shared_ptr<Pieces> piece =
            std::make_shared<Pieces>(board[row][col], row, col);
        pieces.emplace_back(piece);
      }
    }
  }

  for (int i = 0; i < pieces.size(); i++) {
    pieces[i]->checkMoveableSquares(board);
  }

  bool isMove = false, firstClick = false, isWhite = true,
       whiteKingChecked = false, blackKinghChecked = false;
  float dx = 0, dy = 0;
  int n, firstClickedPiece = -1;
  sf::Vector2i firstClickedPos;

  while (app.isOpen()) {

    Event event;
    while (app.pollEvent(event)) {
      if (event.type == Event::Closed) {
        app.close();
      }
      // int n = -1;
      if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i pos = sf::Mouse::getPosition(app);
        if (!firstClick) {
          firstClick = true;
          for (int i = 0; i < pieces.size(); i++) {
            if (pieces[i]->getSprite().getGlobalBounds().contains(pos.x,
                                                                  pos.y)) {

              firstClickedPiece = i;
              firstClickedPos.x = pieces[i]->getSprite().getPosition().x;
              firstClickedPos.y = pieces[i]->getSprite().getPosition().y;
            }
          }
        }
        if (event.mouseButton.button == sf::Mouse::Left) {
          for (int i = 0; i < pieces.size(); i++) {
            if (pieces[i]->getSprite().getGlobalBounds().contains(pos.x,
                                                                  pos.y)) {
              n = i;
              isMove = true;
              dx = pos.x - pieces[i]->getSprite().getPosition().x;
              dy = pos.y - pieces[i]->getSprite().getPosition().y;
              break;
            }
          }
        }
      }
      if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == Mouse::Left) {
          firstClick = false;
          sf::Vector2i pos = sf::Mouse::getPosition(app);
          bool wrongMove = false;

          // Wrong move order. White to play.
          if (isWhite && pieces[firstClickedPiece]->getPieceEnum() >= 6) {
            std::cout << "Wrong move. White to play.\n";
            pieces[firstClickedPiece]->move(
                std::floor((firstClickedPos.x + static_cast<int>(SIZE / 2)) /
                           SIZE) *
                    SIZE,
                std::floor((firstClickedPos.y + static_cast<int>(SIZE / 2)) /
                           SIZE) *
                    SIZE);
            wrongMove = true;
          }
          // Wrong move order. Black to play
          else if (!isWhite && pieces[firstClickedPiece]->getPieceEnum() < 6) {
            pieces[firstClickedPiece]->move(
                std::floor((firstClickedPos.x + static_cast<int>(SIZE / 2)) /
                           SIZE) *
                    SIZE,
                std::floor((firstClickedPos.y + static_cast<int>(SIZE / 2)) /
                           SIZE) *
                    SIZE);
            std::cout << "Wrong move. Black to play.\n";
            wrongMove = true;
          }

          if (!wrongMove) {
            bool isOccupied = false;
            for (int i = 0; i < pieces.size(); i++) {
              if (firstClickedPiece == i) {
                continue;
              }
              if (pieces[i]->getSprite().getGlobalBounds().contains(pos.x,
                                                                    pos.y)) {
                isOccupied = true;
                if (pieces[firstClickedPiece]
                        ->squareStatus_[pos.y / SIZE][pos.x / SIZE] ==
                    UNMOVEABLE) {
                  pieces[firstClickedPiece]->move(
                      std::floor(
                          (firstClickedPos.x + static_cast<int>(SIZE / 2)) /
                          SIZE) *
                          SIZE,
                      std::floor(
                          (firstClickedPos.y + static_cast<int>(SIZE / 2)) /
                          SIZE) *
                          SIZE);
                  break;
                }

                else if (pieces[firstClickedPiece]
                             ->squareStatus_[pos.y / SIZE][pos.x / SIZE] ==
                         TAKEABLE) {
                  // If your move reveals a check, you can't move.
                  bool checkReveals = false;
                  updateBoardStatus(pieces, board);
                  for (int i = 0; i < pieces.size(); i++) {
                    pieces[i]->checkMoveableSquares(board);
                    if (pieces[i]->checks) {
                      checkReveals = true;
                    }
                  }
                  // If move reveals a check, it's illegal move.
                  if (checkReveals) {
                    pieces[firstClickedPiece]->move(
                        std::floor(
                            (firstClickedPos.x + static_cast<int>(SIZE / 2)) /
                            SIZE) *
                            SIZE,
                        std::floor(
                            (firstClickedPos.y + static_cast<int>(SIZE / 2)) /
                            SIZE) *
                            SIZE);
                  } else {
                    isOccupied = true;
                    pieces[firstClickedPiece]->move(
                        std::floor(pos.x / SIZE) * SIZE,
                        std::floor(pos.y / SIZE) * SIZE);

                    // If there is any check on the board, if there is, your
                    // move should remove check otherwise it's an illegal move.
                    bool checks = false;
                    updateBoardStatus(pieces, board);
                    for (int i = 0; i < pieces.size(); i++) {
                      if(isWhite)
                      {
                        if (pieces[i]->isWhite)
                        {
                          continue;
                        }
                      }
                      else if(!isWhite)
                      {
                        if (!pieces[i]->isWhite)
                        {
                          continue;
                        }
                      }
                      
                      pieces[i]->checkMoveableSquares(board);
                      if (pieces[i]->checks) {
                        std::cout << pieces[i]->getName() << " checks.\n";
                        checks = true;
                      }
                    }
                    // If king is still checked, it's an illegal move.
                    if (checks) {
                      pieces[firstClickedPiece]->move(
                          std::floor(
                              (firstClickedPos.x + static_cast<int>(SIZE / 2)) /
                              SIZE) *
                              SIZE,
                          std::floor(
                              (firstClickedPos.y + static_cast<int>(SIZE / 2)) /
                              SIZE) *
                              SIZE);
                    }
                    // If there is no active check on king
                    else {
                      pieces.erase(pieces.begin() + i);

                      if (isWhite)
                        isWhite = false;
                      else
                        isWhite = true;
                      break;
                    }
                  }
                }
              }
            }
            if (!isOccupied) {
              if (pieces[firstClickedPiece]
                      ->squareStatus_[pos.y / SIZE][pos.x / SIZE] == MOVEABLE) {
                pieces[firstClickedPiece]->move(std::floor(pos.x / SIZE) * SIZE,
                                                std::floor(pos.y / SIZE) *
                                                    SIZE);

                // If your move reveals a check, you can't move.
                bool checkReveals = false;
                updateBoardStatus(pieces, board);
                for (int i = 0; i < pieces.size(); i++) {
                  pieces[i]->checkMoveableSquares(board);
                  if (pieces[i]->checks) {
                    checkReveals = true;
                  }
                }
                // If move reveals a check, it's illegal move.
                if (checkReveals) {
                  pieces[firstClickedPiece]->move(
                      std::floor(
                          (firstClickedPos.x + static_cast<int>(SIZE / 2)) /
                          SIZE) *
                          SIZE,
                      std::floor(
                          (firstClickedPos.y + static_cast<int>(SIZE / 2)) /
                          SIZE) *
                          SIZE);
                }
                // If move doesn't reveal a check
                else {
                  // If there is any check on the board, if there is, your
                  // move should remove check otherwise it's an illegal move.
                  bool checks = false;
                  updateBoardStatus(pieces, board);
                  for (int i = 0; i < pieces.size(); i++) {
                    if (isWhite)
                    {
                      if(pieces[i]->isWhite)
                      {
                        continue;
                      }
                    }
                    else if (!isWhite)
                    {
                      if(!pieces[i]->isWhite)
                      {
                        continue;
                      }
                    }
                    pieces[i]->checkMoveableSquares(board);
                    if (pieces[i]->checks) {
                      std::cout << pieces[i]->getName() << " checks.\n";
                      checks = true;
                    }
                  }
                  // If king is still checked, it's an illegal move.
                  if (checks) {
                    pieces[firstClickedPiece]->move(
                        std::floor(
                            (firstClickedPos.x + static_cast<int>(SIZE / 2)) /
                            SIZE) *
                            SIZE,
                        std::floor(
                            (firstClickedPos.y + static_cast<int>(SIZE / 2)) /
                            SIZE) *
                            SIZE);
                  } 
                  // If there is not active check, it's legal move.
                  else {
                    if (isWhite) {
                      isWhite = false;
                    } else
                      isWhite = true;
                  }
                }
              } else {
                pieces[firstClickedPiece]->move(
                    std::floor(
                        (firstClickedPos.x + static_cast<int>(SIZE / 2)) /
                        SIZE) *
                        SIZE,
                    std::floor(
                        (firstClickedPos.y + static_cast<int>(SIZE / 2)) /
                        SIZE) *
                        SIZE);
              }
            }
            // If pieces is put on different square, check square status for
            // every piece due to new position of the board.

            updateBoardStatus(pieces, board);
            for (int i = 0; i < pieces.size(); i++) {
              pieces[i]->checkMoveableSquares(board);
            }
          }
          isMove = false;
        }
        firstClickedPiece = -1;
      }
      if (isMove) {
        pieces[n]->move(sf::Mouse::getPosition(app).x - dx,
                        sf::Mouse::getPosition(app).y - dy);
      }
    }
    app.clear();
    app.draw(board_sprite);
    for (int i = 0; i < pieces.size(); i++) {
      app.draw(pieces[i]->getSprite());
    }
    if (firstClickedPiece >= 0) {
      app.draw(pieces[firstClickedPiece]->getSprite());
    }

    app.display();
  }
  return 0;
}