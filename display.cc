#include "display.h"

void Display::DrawBoard(Board& board, const Tetromino* const tetromino) {
  if (tetromino) tetromino->Draw(board, true);

  for (int column{0}; column < Board::Columns(); ++column) {
    for (int row{0}; row < Board::Rows(); ++row) {
      if (UpdateCharacter(column, row, board)) {
        const int index{column * Board::Rows() + row};
        display_.createChar(index, characters_[column][row]);
        display_.setCursor(row, column);
        display_.write(uint8_t(index));
      }
    }
  }

  if (tetromino) tetromino->Draw(board, false);
}

void Display::PrintScore(const int score) {
  display_.setCursor(9, 1);
  display_.print(min(score, 999));
}

void Display::Intro() {
  uint8_t block_character[] = {0b11111, 0b11111, 0b11111, 0b11111,
                               0b11111, 0b11111, 0b11111, 0b11111};
  display_.createChar(0, block_character);
  display_.begin(16, 2);

  display_.setCursor(0, 0);
  display_.print("TET ");
  display_.write(uint8_t(0));
  display_.print(" Author:");

  display_.setCursor(0, 1);
  display_.print("RIS ");
  display_.write(uint8_t(0));
  display_.print(" hkktr (HM)");
}

void Display::Start() {
  for (int column{0}; column < Board::Columns(); ++column) {
    for (int row{0}; row < Board::Rows(); ++row) {
      for (int y{0}; y < Board::BlockWidth(); ++y) {
        characters_[column][row][y] = 0b00000;
      }
    }
  }

  display_.clear();
  display_.setCursor(4, 0);
  display_.print("XXXX Score:");

  display_.setCursor(4, 1);
  display_.print("XXXX");
  PrintScore(0);
}

void Display::GameOver(const int score, const int high_score) {
  uint8_t crown_character[] = {0b00000, 0b00000, 0b00000, 0b10101,
                               0b11111, 0b11111, 0b11111, 0b00000};
  display_.createChar(0, crown_character);
  display_.clear();

  display_.setCursor(0, 0);
  display_.print("Your score: ");
  display_.print(score);
  if (score >= high_score) display_.write(uint8_t(0));

  display_.setCursor(0, 1);
  display_.print("High score: ");
  display_.print(high_score);
  if (score <= high_score) display_.write(uint8_t(0));
}

void Display::Restart() {
  display_.clear();
  display_.setCursor(0, 0);
  display_.print("Game over! Press");
  display_.setCursor(0, 1);
  display_.print("rotate to play.");
}

bool Display::UpdateCharacter(const int column, const int row,
                              const Board& board) {
  const int x{column * Board::BlockWidth()};
  const int y{(Board::Rows() - row - 1) * Board::BlockHeight()};

  uint8_t character[8];
  constexpr uint8_t kPowers[]{1, 2, 4, 8, 16};

  for (int i{0}; i < Board::BlockWidth(); ++i) {
    uint8_t value{0};
    for (int j{0}; j < Board::BlockHeight(); ++j) {
      value += board.At(x + i, y + j) * kPowers[j];
    }
    character[i] = value;
  }

  bool changes{false};
  for (int i{0}; i < Board::BlockWidth(); ++i) {
    if (characters_[column][row][i] != character[i]) {
      characters_[column][row][i] = character[i];
      changes = true;
    }
  }

  return changes;
}
