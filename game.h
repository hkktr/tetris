#ifndef TETRIS_GAME_H_
#define TETRIS_GAME_H_

#include <EEPROM.h>

#include "board.h"
#include "display.h"
#include "tetromino.h"

/* Settings */
constexpr unsigned long kIntroDelay{1000};          // default: 1000
constexpr unsigned long kGameOverDelay{3000};       // default: 3000
constexpr unsigned long kActionTimeDelay{150};      // default: 150
constexpr unsigned long kMoveTimeDelay{350};        // default: 350
constexpr unsigned long kRapidFallLineDelay{20};    // default: 20
constexpr unsigned long kClearedLineScoreBonus{5};  // default: 5

/* Pins */
constexpr int kLeftButtonPin{4};
constexpr int kRightButtonPin{3};
constexpr int kRotateButtonPin{5};
constexpr int kRapidFallButtonPin{2};
constexpr int kLcdRsPin{8};
constexpr int kLcdEnablePin{9};
constexpr int kLcdD4Pin{10};
constexpr int kLcdD5Pin{11};
constexpr int kLcdD6Pin{12};
constexpr int kLcdD7Pin{13};

/**
 * Responsible for initializing and managing the state of the game. It also
 * handles user input and updates the game state accordingly.
 */
class Game {
 public:
  /**
   * Deallocates the memory used by the display and tetromino objects.
   */
  ~Game();

  /**
   * Initializes the pins for input, sets up the EEPROM
   * for reading and writing high score data, initializes the display for
   * output, and starts the intro sequence.
   */
  void Setup();
  /**
   * Performs an update on the game state every tick, which includes
   * updating the tetromino position, checking for completed lines,
   * and handling user input.
   */
  void Update();

 private:
  static constexpr int kMemoryHighScoreAddress{0};

  /**
   * Handles a rapid tetromino fall if the user chooses to do so. If the user
   * presses the "drop" key, the method immediately moves the current tetromino
   * to the bottom of the board, then clears any completed lines and updates
   * score.
   *
   *  @returns True if rapid fall occured, false otherwise.
   */
  bool HandleRapidFall();
  /**
   * Checks user input and updates the tetromino if possible.
   *
   * @param time The elapsed time in milliseconds
   *
   * @returns True if resulted in any changes to the board, false otherwise.
   */
  bool HandleUserInput(const unsigned long time);
  /**
   * Moves the current tetromino down by one cell if the delta time
   * since the last move down is greater than a constant value.
   *
   * @param time The elapsed time in milliseconds
   *
   * @returns True if resulted in any changes to the board, false otherwise.
   */
  bool HandleTetrominoMoveDown(const unsigned long time);
  /**
   * Removes the current tetromino from the board and updates the score.
   */
  void RemoveTetromino();

  /**
   * Displays the game's intro sequence, which includes showing the game
   * title and author. Once the intro is complete, the method starts the game.
   */
  void Intro();
  /**
   * Resets the game state and starts the game. This includes resetting
   * the score, deleting the tetromino, and clearing the game board.
   */
  void Start();
  /**
   * Displays the "game over" message and waits for the player to restart the
   * game. If the player has achieved a new high score, the method saves it to
   * the EEPROM memory.
   */
  void GameOver();

  Board board_;
  Display* display_;
  Tetromino* tetromino_;

  int score_{0};
  unsigned long last_action_time_{0};
  unsigned long last_move_time_{0};
};

#endif  // TETRIS_GAME_H_