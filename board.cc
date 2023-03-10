#include "board.h"

bool Board::At(const int x, const int y) const { return board_[x][y]; }

void Board::Set(const int x, const int y, const bool value) {
  board_[x][y] = value;
}

int Board::ClearLines() {
  int cleared_lines{0};

  int y{Board::Height() - 1};
  while (y >= 0) {
    int quantity{0};
    for (int x{0}; x < Board::Width(); ++x) {
      if (At(x, y)) ++quantity;
    }

    if (quantity == 0) {
      break;
    } else if (quantity == Board::Width()) {
      for (int x{0}; x < Board::Width(); ++x) {
        Set(x, y, false);
      }

      MoveLines(y);
      ++cleared_lines;
    } else {
      --y;
    }
  }

  return cleared_lines;
}

void Board::Clear() {
  for (int x{0}; x < Board::Width(); ++x) {
    for (int y{0}; y < Board::Height(); ++y) {
      Set(x, y, false);
    }
  }
}

void Board::MoveLines(const int max_y) {
  for (int y{max_y}; y > 0; --y) {
    for (int x{0}; x < Board::Width(); ++x) {
      Set(x, y, At(x, y - 1));
    }
  }
}
