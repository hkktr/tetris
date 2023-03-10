#include "tetromino.h"

Tetromino::Tetromino() {
  constexpr int x{Board::Width() / 2};
  constexpr int y{0};

  const int figure{random(kFiguresSize)};
  for (int i{0}; i < kFigureSize; ++i) {
    shape_[i].x = x + kFigures[figure][i] % 2;
    shape_[i].y = y + kFigures[figure][i] / 2;
  }
}

bool Tetromino::Collide(const Board& board) const {
  for (int i{0}; i < kFigureSize; ++i) {
    const Block& block{shape_[i]};
    if (board.At(block.x, block.y)) return true;
  }
  return false;
}

bool Tetromino::Move(const Board& board, const Direction direction) {
  const int offset{static_cast<int>(direction)};

  for (int i{0}; i < kFigureSize; ++i) {
    const int new_x{shape_[i].x + offset};
    if (new_x < 0 || new_x >= Board::Width()) return false;
    if (board.At(new_x, shape_[i].y)) return false;
  }

  for (int i{0}; i < kFigureSize; ++i) {
    shape_[i].x += offset;
  }
  return true;
}

bool Tetromino::Rotate(const Board& board) {
  // Disables square rotation
  if (abs(shape_[3].x - shape_[0].x) == 1 &&
      abs(shape_[3].y - shape_[0].y) == 1)
    return false;

  const Block& center = shape_[2];
  Block rotated[kFigureSize];

  for (int i{0}; i < kFigureSize; ++i) {
    const int x{shape_[i].y - center.y};
    const int y{shape_[i].x - center.x};
    rotated[i].x = center.x - x;
    rotated[i].y = center.y + y;

    if (rotated[i].x < 0 || rotated[i].x >= Board::Width()) return false;
    if (rotated[i].y < 0 || rotated[i].x >= Board::Height()) return false;
    if (board.At(rotated[i].x, rotated[i].y)) return false;
  }

  for (int i{0}; i < kFigureSize; ++i) {
    shape_[i].x = rotated[i].x;
    shape_[i].y = rotated[i].y;
  }
  return true;
}

bool Tetromino::MoveDown(const Board& board) {
  for (int i{0}; i < kFigureSize; ++i) {
    if (shape_[i].y >= Board::Height() - 1) return true;
    if (board.At(shape_[i].x, shape_[i].y + 1)) return true;
  }

  for (int i{0}; i < kFigureSize; ++i) {
    ++shape_[i].y;
  }
  return false;
}

void Tetromino::Draw(Board& board, const bool value) const {
  for (int i{0}; i < kFigureSize; ++i) {
    const Block& block = shape_[i];
    board.Set(block.x, block.y, value);
  }
}
