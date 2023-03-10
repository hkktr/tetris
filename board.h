#ifndef TETRIS_BOARD_H_
#define TETRIS_BOARD_H_

/**
 * The Board class is used to store and manage the state of the game board.
 */
class Board {
 public:
  /**
   * @param x The x-coordinate of the position
   * @param y The y-coordinate of the position
   *
   * @returns The boolean value of the board at the specified position.
   */
  bool At(const int x, const int y) const;
  /**
   * Sets the value of the board at the specified position to the
   * specified boolean value.
   *
   * @param x The x-coordinate of the position
   * @param y The y-coordinate of the position
   * @param value The new value at specified position
   */
  void Set(const int x, const int y, const bool value);
  /**
   * Checks for full lines on the board and clears them, moving any lines above
   * them down if necessary.
   *
   * @returns The number of lines cleared.
   */
  int ClearLines();
  /**
   * Clears the game board by setting all values in the board array to false.
   */
  void Clear();

  static constexpr int Width() { return kWidth; }
  static constexpr int Height() { return kHeight; }
  static constexpr int BlockWidth() { return kBlockWidth; }
  static constexpr int BlockHeight() { return kBlockHeight; }
  static constexpr int Columns() { return kWidth / kBlockWidth; }
  static constexpr int Rows() { return kHeight / kBlockHeight; }

 private:
  static constexpr int kWidth{16};
  static constexpr int kHeight{20};
  static constexpr int kBlockWidth{8};
  static constexpr int kBlockHeight{5};

  /**
   * Moves all the lines with y lower than the provided value down by one
   * block on the board. This method is used to update the board after clearing
   * lines.
   *
   * @param max_y The y-coordinate value below which lines should be moved down
   */
  void MoveLines(const int max_y);

  bool board_[kWidth][kHeight];
};

#endif  // TETRIS_BOARD_H_