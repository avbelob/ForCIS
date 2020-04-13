// Тут иногда очень плохой код... Извините :c

#include <iostream>
#include <vector>

enum {
  field_height_ = 3,
  field_width_ = 4
};

class Field {
 public:
  explicit Field() {
    field_.resize(field_height_);
  }

  void FieldCreation() {
    field_.resize(field_height_);
    std::cout << "Введите поле 4x3 ('b' - бомба, '0' - пустая клетка):\n";
    for (int i = 0; i < field_height_; ++i) {
      for (int j = 0; j < field_width_; ++j) {
        cell_ *cur_cell = new cell_;
        std::cin >> cur_cell->value;
        field_[i].emplace_back(*cur_cell);
      }
    }
  }

  void PrintField() {
    for (int i = 0; i < field_height_; ++i) {
      for (int j = 0; j < field_width_; ++j) {
        if (!field_[i][j].is_open) {
          std::cout << "- ";
        } else {
          std::cout << field_[i][j].value << " ";
        }
      }
      std::cout << "\n";
    }
  }

  bool IsGameEnd() {
    return is_game_end_;
  }

  bool IsOpen(int first_coord, int second_coord) {
    --first_coord;
    --second_coord;
    return field_[first_coord][second_coord].is_open;
  }

  char GetValue(int first_coord, int second_coord) {
    --first_coord;
    --second_coord;
    if (!field_[first_coord][second_coord].is_open) {
      return '-';
    } else {
      return field_[first_coord][second_coord].value;
    }
  }

  void OpenCell(int first_coord, int second_coord, int &points) {
    ++open_cell_count_;
    points += GetPounts(first_coord, second_coord);
    field_[first_coord - 1][second_coord - 1].is_open = true;
    if (field_[first_coord - 1][second_coord - 1].value == 'b') {
      is_game_end_ = true;
      points -= 5;
    }
    if (open_cell_count_ == field_height_ * field_width_) {
      is_game_end_ = true;
    }
  }

  int GetPounts(int first_coord, int second_coord) {
    int points = 0;
    --first_coord;
    --second_coord;

    if (first_coord != 0) {
      if (second_coord != 0) {
        if (field_[first_coord - 1][second_coord - 1].is_open) {
          points += (int) field_[first_coord - 1][second_coord - 1].value - 48;
        }
      }
      if (second_coord != field_width_ - 1) {
        if (field_[first_coord - 1][second_coord + 1].is_open) {
          points += (int) field_[first_coord - 1][second_coord + 1].value - 48;
        }
      }

      if (field_[first_coord - 1][second_coord].is_open) {
        points += (int) field_[first_coord - 1][second_coord].value - 48;
      }
    }

    if (first_coord != field_height_ - 1) {
      if (second_coord != 0) {
        if (field_[first_coord + 1][second_coord - 1].is_open) {
          points += (int) field_[first_coord + 1][second_coord - 1].value - 48;
        }
      }
      if (second_coord != field_width_ - 1) {
        if (field_[first_coord + 1][second_coord + 1].is_open) {
          points += (int) field_[first_coord + 1][second_coord + 1].value - 48;
        }
      }

      if (field_[first_coord + 1][second_coord].is_open) {
        points += (int) field_[first_coord + 1][second_coord].value - 48;
      }
    }

    if (second_coord != 0) {
      if (field_[first_coord][second_coord - 1].is_open) {
        points += (int) field_[first_coord][second_coord - 1].value - 48;
      }
    }
    if (second_coord != field_width_ - 1) {
      if (field_[first_coord][second_coord + 1].is_open) {
        points += (int) field_[first_coord][second_coord + 1].value - 48;
      }
    }

    if (points == 0) {
      points = 1;
    }

    return points;
  }

 private:
  bool is_game_end_ = false;
  int open_cell_count_ = 0;
  struct cell_ {
    int is_open = false;
    char value;
  };
  std::vector<std::vector<cell_>> field_;
};

void GameEnd(int &player_points, int &our_points) {
  std::cout << "Ваши очки: " << player_points << "\n";
  std::cout << "Очки программы: " << our_points << "\n";
  if (player_points > our_points) {
    std::cout << "Вы победили!\n";
    exit(0);
  } else {
    if (player_points == our_points) {
      std::cout << "Ничья!\n";
      exit(0);
    }
    std::cout << "Вы проиграли!\n";
    exit(0);
  }
};

void PlayerStep(Field &field, int &player_points, int &our_points) {
  field.PrintField();
  std::cout << "Введите координаты кледки, которую хотите открыть: \n";
  int first_coord = 0;
  int second_coord = 0;
  std::cin >> first_coord >> second_coord;
  field.OpenCell(first_coord, second_coord, player_points);
  field.PrintField();
  if (field.IsGameEnd()) {
    GameEnd(player_points, our_points);
  }
}

int GetNotOpenNeighCellsCount(Field &field, ssize_t i, ssize_t j) {
  int not_open_neigh_count = 0;
  if (i != 1) {
    if (j != 1) {
      if (!field.IsOpen(i - 1, j - 1)) {
        ++not_open_neigh_count;
      }
    }
    if (j != field_width_) {
      if (!field.IsOpen(i - 1, j + 1)) {
        ++not_open_neigh_count;
      }
    }
    if (!field.IsOpen(i - 1, j)) {
      ++not_open_neigh_count;
    }
  }

  if (i != field_height_) {
    if (j != 1) {
      if (!field.IsOpen(i + 1, j - 1)) {
        ++not_open_neigh_count;
      }
    }
    if (j != field_width_) {
      if (!field.IsOpen(i + 1, j + 1)) {
        ++not_open_neigh_count;
      }
    }

    if (!field.IsOpen(i + 1, j)) {
      ++not_open_neigh_count;
    }
  }

  if (j != 1) {
    if (!field.IsOpen(i, j - 1)) {
      ++not_open_neigh_count;
    }
  }
  if (j != field_width_) {
    if (!field.IsOpen(i, j + 1)) {
      ++not_open_neigh_count;
    }
  }
  return not_open_neigh_count;
}

int GetNeighCellsCount(Field &field, ssize_t i, ssize_t j) {
  if ((i == 1 && j == 1) || (i == 1 && j == field_width_) ||
      (i == field_height_ && j == 1) ||
      (i == field_height_ && j == field_width_)) {
    return 3;
  }
  if (i == 1 || j == 1 || i == field_height_ || j == field_width_) {
    return 5;
  }
  return 8;
}

void OurStep(Field &field, int &player_points, int &our_points) {
  double bomb_probability[field_height_][field_width_] = {};
  double not_open_neigh_count = 0;
  double cur_value = 0;

  // Подсчёт вероятностей
  for (ssize_t i = 1; i <= field_height_; ++i) {
    for (ssize_t j = 1; j <= field_width_; ++j) {
      if (field.IsOpen(i, j) && field.GetValue(i, j) != '0') {
        not_open_neigh_count = GetNotOpenNeighCellsCount(field, i, j);

        cur_value = (int) field.GetValue(i, j) - 48;

        if (i != 1) {
          if (j != 1) {
            bomb_probability[i - 1][j - 1] +=
                    cur_value / not_open_neigh_count;
          }
          if (j != field_width_) {
            bomb_probability[i - 1][j + 1] +=
                    cur_value / not_open_neigh_count;
          }

          bomb_probability[i - 1][j] += cur_value / not_open_neigh_count;
        }

        if (i != field_height_) {
          if (j != 1) {
            bomb_probability[i + 1][j - 1] +=
                    cur_value / not_open_neigh_count;
          }
          if (j != field_width_) {
            bomb_probability[i + 1][j + 1] +=
                    cur_value / not_open_neigh_count;
          }

          bomb_probability[i + 1][j] += cur_value / not_open_neigh_count;
        }

        if (j != 1) {
          bomb_probability[i][j - 1] +=
                  cur_value / not_open_neigh_count;
        }
        if (j != field_width_) {
          bomb_probability[i][j + 1] +=
                  cur_value / not_open_neigh_count;
        }

      }


      // Не очень хотим идти в клетки без соседей,
      // так что давайте сделаем им большие вероятности
      // (но меньше 1, чтобы ходить в них, если все открытые клетки
      // соседничают с бомбами)
      if (!field.IsOpen(i, j)) {
        if (GetNotOpenNeighCellsCount(field, i, j) ==
            GetNeighCellsCount(field, i, j)) {
          bomb_probability[i][j] = 0.99;
        }
      }

    }
  }

  int min_probability = INT8_MAX;
  int first_coord = 0;
  int second_coord = 0;

  for (ssize_t i = 1; i <= field_height_; ++i) {
    for (ssize_t j = 1; j <= field_width_; ++j) {
      if (!field.IsOpen(i, j)) {
        if (bomb_probability[i][j] < min_probability) {
          min_probability = bomb_probability[i][j];
          first_coord = i;
          second_coord = j;
        } else {
          if (bomb_probability[i][j] == min_probability) {
            if (field.GetPounts(i, j) >
                field.GetPounts(first_coord, second_coord)) {
              min_probability = bomb_probability[i][j];
              first_coord = i;
              second_coord = j;
            }
          }
        }
      }
    }
  }

  field.OpenCell(first_coord, second_coord, our_points);
  field.PrintField();
  if (field.IsGameEnd()) {
    GameEnd(player_points, our_points);
  }
}

int main() {
  Field field;

  field.FieldCreation();

  int player_points = 0;
  int our_points = 0;

  while (true) {
    PlayerStep(field, player_points, our_points);
    OurStep(field, player_points, our_points);
  }
}

