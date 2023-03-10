#ifndef TETRIS_DISPLAY_H_
#define TETRIS_DISPLAY_H_

#include <LiquidCrystal.h>

#include "board.h"
#include "tetromino.h"

/**
 * The Display class is responsible for managing the display of the game on an
 * LCD screen. It provides methods for printing various messages, drawing the
 * game board, tetromino shapes, and score information on the screen.
 */
class Display {
 public:
  /**
   * The constructor takes six arguments, which are the pin numbers for the LCD
   * screen. It creates a LiquidCrystal object underneath to interface with the
   * LCD screen.
   *
   * @param rs
   * @param enable
   * @param d4
   * @param d5
   * @param d6
   * @param d7
   */
  Display(int rs, int enable, int d4, int d5, int d6, int d7)
      : display_{rs, enable, d4, d5, d6, d7} {}

  /**
   * Draws the game board on the display, including the current tetromino, if
   * available.
   *
   * @param board The game board
   * @param tetromino The current tetromino (optional)
   **/
  void DrawBoard(Board& board, const Tetromino* const tetromino);
  /**
   * Updates the game score on the display.
   *
   * @param score The new score to display
   */
  void PrintScore(const int score);

  /**
   * Displays an introductory message that includes the game title and author.
   */
  void Intro();
  /**
   * Clears the game display and prints the game score, starting with a score of
   * 0.
   */
  void Start();
  /**
   * Displays the player's current score and high score on the game screen.
   *
   * @param score The current score of the game
   * @param high_score The highest score achieved in all previous games
   */
  void GameOver(const int score, const int high_score);
  /**
   * Displays the "game over" message and provides instructions for restarting
   * the game.
   */
  void Restart();

 private:
  /**
   * Updates the character for specific segment of the board.
   *
   * @param column The number of column on the display
   * @param row The number of row on the display
   * @param board The game board
   *
   * @returns True if any changes were made, false otherwise.
   */
  bool UpdateCharacter(const int column, const int row, const Board& board);

  LiquidCrystal display_;
  uint8_t characters_[Board::Columns()][Board::Rows()][Board::BlockWidth()];
};

#endif  // TETRIS_DISPLAY_H_