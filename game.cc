#include "game.h"

Game::~Game() {
  delete display_;
  delete tetromino_;
}

void Game::Setup() {
  pinMode(kLeftButtonPin, INPUT_PULLUP);
  pinMode(kRightButtonPin, INPUT_PULLUP);
  pinMode(kRotateButtonPin, INPUT_PULLUP);
  pinMode(kRapidFallButtonPin, INPUT_PULLUP);

  randomSeed(analogRead(0));

  if (!EEPROM.read(kMemoryHighScoreAddress)) {
    EEPROM.write(kMemoryHighScoreAddress, 0);
  }

  display_ = new Display(kLcdRsPin, kLcdEnablePin, kLcdD4Pin, kLcdD5Pin,
                         kLcdD6Pin, kLcdD7Pin);

  Intro();
}

void Game::Update() {
  bool changes{false};

  if (!tetromino_) {
    tetromino_ = new Tetromino();
    changes = true;

    if (tetromino_->Collide(board_)) return GameOver();
  }

  const unsigned long time{millis()};
  if (HandleRapidFall()) return;
  if (HandleUserInput(time)) changes = true;
  if (HandleTetrominoMoveDown(time)) changes = true;

  if (changes) display_->DrawBoard(board_, tetromino_);
}

bool Game::HandleRapidFall() {
  if (digitalRead(kRapidFallButtonPin) == LOW) {
    while (!tetromino_->MoveDown(board_)) {
      display_->DrawBoard(board_, tetromino_);
      delay(kRapidFallLineDelay);
    }

    RemoveTetromino();
    return true;
  }

  return false;
}

bool Game::HandleUserInput(const unsigned long time) {
  const unsigned long last_action_delta{time - last_action_time_};

  if (last_action_delta >= kActionTimeDelay) {
    bool action{false};

    if (digitalRead(kLeftButtonPin) == LOW) {
      action = tetromino_->Move(board_, Tetromino::Direction::kLeft);
    } else if (digitalRead(kRightButtonPin) == LOW) {
      action = tetromino_->Move(board_, Tetromino::Direction::kRight);
    } else if (digitalRead(kRotateButtonPin) == LOW) {
      action = tetromino_->Rotate(board_);
    }

    if (action) {
      last_action_time_ = time;
      return true;
    }
  }

  return false;
}

bool Game::HandleTetrominoMoveDown(const unsigned long time) {
  const unsigned long last_move_delta{time - last_move_time_};

  if (last_move_delta >= kMoveTimeDelay) {
    if (tetromino_->MoveDown(board_)) RemoveTetromino();
    last_move_time_ = time;
    return true;
  }

  return false;
}

void Game::RemoveTetromino() {
  tetromino_->Draw(board_, true);
  delete tetromino_;
  tetromino_ = nullptr;

  ++score_;
  score_ += board_.ClearLines() * kClearedLineScoreBonus;

  display_->PrintScore(score_);
}

void Game::Intro() {
  display_->Intro();
  delay(kIntroDelay);
  Start();
}

void Game::Start() {
  delete tetromino_;
  tetromino_ = nullptr;

  score_ = 0;
  last_action_time_ = millis();
  last_move_time_ = millis();

  board_.Clear();
  display_->Start();
}

void Game::GameOver() {
  const int high_score{EEPROM.read(0)};

  display_->GameOver(score_, high_score);
  if (score_ > high_score) EEPROM.update(0, score_);
  delay(kGameOverDelay);

  display_->Restart();
  while (digitalRead(kRotateButtonPin) == HIGH) {
  }
  Start();
}
