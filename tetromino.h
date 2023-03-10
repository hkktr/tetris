#ifndef TETRIS_TETROMINO_H_
#define TETRIS_TETROMINO_H_

#include "board.h"

constexpr int kFigures[7][4]{{0, 2, 4, 6}, {2, 4, 5, 7}, {3, 5, 4, 6},
                             {3, 5, 4, 7}, {2, 3, 5, 7}, {3, 5, 7, 6},
                             {2, 3, 4, 5}};
constexpr int kFiguresSize{sizeof(kFigures) / sizeof(kFigures[0])};
constexpr int kFigureSize{sizeof(kFigures[0]) / sizeof(kFigures[0][0])};

/**
 * The Tetromino class is responsible for creating and manipulating Tetromino
 * objects, which represent the various shapes used in the game of Tetris. A
 * Tetromino object is composed of four blocks arranged in a specific shape,
 * such as a straight line or a square. The Tetromino class provides functions
 * for moving and rotating these shapes on a game board.
 */
class Tetromino {
 public:
  /**
   * The Direction enum is used to indicate the direction to move the tetromino
   * horizontally. It has two possible values, kLeft and kRight, which
   * respectively represent moving the tetromino to the left or to the right.
   *
   * The Direction enum is used in conjunction with the Move method,
   * which moves the tetromino horizontally based on the specified direction.
   */
  enum class Direction {
    kLeft = -1,
    kRight = 1,
  };

  /**
   * The Tetromino class constructor creates a new Tetromino object of a random
   * figure from the set of pre-defined figures.
   */
  Tetromino();

  /**
   * Checks if the tetromino collides with any other blocks on the game board.
   *
   * @param board The board to check for collisions with the tetromino
   *
   * @returns True if there was a collision, false otherwise.
   */
  bool Collide(const Board& board) const;
  /**
   * Moves the current tetromino left or right by one column, if possible.
   *
   * @param board The board to check for collisions with the tetromino after
   * move in specified direction
   * @param direction The direction to move the tetromino, either
   * `Direction::kLeft`
   *
   * @returns True if the move occured, false otherwise.
   */
  bool Move(const Board& board, const Direction direction);
  /**
   * Rotates the tetromino by 90 degrees, if possible.
   *
   * @param board The board to check for collisions with the tetromino after
   * rotation
   *
   * @returns True if the rotation occured, false otherwise.
   */
  bool Rotate(const Board& board);
  /**
   * Moves the tetromino down by one row, if possible.
   *
   * @param board The board to check for collisions with the tetromino after
   * moving it down
   *
   * @returns True if the tetromino is at the bottom, false otherwise.
   */
  bool MoveDown(const Board& board);
  /**
   * Adds or removes a tetromino from the game board, depending on the value
   * of the passed-in argument.
   *
   * @param board The board to draw or remove the tetromino blocks from
   * @param value The boolean value, where true indicates that the tetromino
   * should be drawn on the board, and false indicates that it should be removed
   * from the board
   */
  void Draw(Board& board, const bool value) const;

 private:
  /**
   * The Block struct represents a single block of a tetromino. It consists of
   * two fields, x and y, which represent the x and y coordinates of the block,
   * respectively.
   */
  struct Block {
    int x;
    int y;
  };

  Block shape_[kFigureSize];
};

#endif  // TETRIS_TETROMINO_H_