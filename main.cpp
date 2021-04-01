#include <iostream>
#include <random>

enum class CellState {
    Empty, X, O
};

enum class Sign {
    X, O
};

struct GameData {
 CellState *field;
 int field_dimension;
 Sign player_sign;
};

struct TurnOutcome {
    bool isOver : 1;
    Sign victor : 1;
    bool isDraw : 1;
};

GameData initField () {
GameData game_data {};
int n;
std::cout<<"Enter field dimension n = nxn: ";
std::cin>>n;
game_data.field = new CellState[n*n];
for (int i=0; i<n*n;i++)
{
game_data.field[i] = CellState::Empty;
}
game_data.field_dimension = n;
return game_data;
}


bool isValidCell(size_t row, size_t column, size_t field_dimension) {
   return row >= 0 && row < field_dimension && column >= 0 && column < field_dimension;
}

CellState getCell(CellState *field, size_t row, size_t column, size_t field_dimension) {
if (!isValidCell(row, column, field_dimension)) return CellState::Empty;
 return field[column * field_dimension + row];
}

bool isCellEmpty(CellState *field, size_t row, size_t column, size_t field_dimension) {
    return getCell(field, row, column, field_dimension) == CellState::Empty;
}

void putSign(CellState *field, Sign sign, size_t row, size_t column, size_t field_dimension) {
    if (isValidCell(row, column, field_dimension)) {
        field[column * field_dimension + row] = (sign == Sign::X) ? CellState::X : CellState::O;
    }
}

bool askQuestion(char positive, char negative) {
    char sign {};
    std::cin >> sign;
    sign = tolower(sign);

    while (sign != positive && sign != negative) {
        std::cout << "Wrong input: received '" << sign << "', should be one of " << positive << " or " << negative << "\n";
        std::cin >> sign;
        sign = tolower(sign);
    }
    return sign == positive;
}

Sign queryPlayerSign() {
    std::cout << "Please input wheter you're X or O: ";
    bool isX = askQuestion('x', 'o');
    return isX ? Sign::X : Sign::O;
}

TurnOutcome checkTurnOutcome(CellState *field, size_t field_dimension);

void processAiTurn(CellState *field, Sign ai_sign, size_t field_dimension) {
    size_t *empty_cells = new size_t[field_dimension*field_dimension];
    const size_t kInvalidCellIdx = 42;
    std::fill_n(empty_cells, field_dimension*field_dimension, kInvalidCellIdx);
    size_t last_empty_cell_idx = 0;
    for (size_t i = 0; i < field_dimension*field_dimension; i++) {
        if (field[i] == CellState::Empty) {
            empty_cells[last_empty_cell_idx] = i;
            last_empty_cell_idx++;
        }
    }

    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_int_distribution<size_t> dist(0, last_empty_cell_idx - 1);
    
    for (size_t i = 0; i < last_empty_cell_idx; i++) {
        size_t target = empty_cells[i];
        field[target] = ai_sign == Sign::X ? CellState::X : CellState::O;
        auto outcome = checkTurnOutcome(field, field_dimension);
        if (outcome.isOver) {
            return;
        }
        field[target] = CellState::Empty;

        auto opposite_sign = ai_sign == Sign::X ? Sign::O : Sign::X;
        field[target] = opposite_sign == Sign::X ? CellState::X : CellState::O;
        outcome = checkTurnOutcome(field, field_dimension);
        if (outcome.isOver) {
            field[target] = ai_sign == Sign::X ? CellState::X : CellState::O;
            return;
        }
        field[target] = CellState::Empty;
    }
    size_t target = empty_cells[dist(mt)];
    putSign(field, ai_sign, target % field_dimension, target / field_dimension, field_dimension);
}

void processPlayerTurn(CellState *field, Sign player_sign, size_t field_dimension) {
    std::cout << "Enter row and column: ";

    int row, column;
    std::cin >> row >> column;

    while (!isValidCell(row - 1, column - 1, field_dimension) || !isCellEmpty(field, row - 1, column - 1, field_dimension)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong input, please enter row and column of an empty cell: ";
        std::cin >> row >> column;
    }

    putSign(field, player_sign, row - 1, column - 1, field_dimension);
}

void printField(CellState *field, size_t field_dimension);

bool isDraw(CellState *field, size_t field_dimension) {
    for (size_t i = 0; i < field_dimension; i++) {
        if (field[i] == CellState::Empty) {
            return false;
        }
    }
    return true;
}

bool checkLine(CellState *field, size_t start_row, size_t start_column, int delta_row, int delta_column, size_t field_dimension) {
    size_t current_row = start_row;
    size_t current_column = start_column;
    auto first = getCell(field, start_row, start_column, field_dimension);
    if (first == CellState::Empty) {
        return false;
    }
    while (isValidCell(current_row, current_column, field_dimension)) {
        if (getCell(field, current_row, current_column, field_dimension) != first) {
            return false;
        }
        current_row += delta_row;
        current_column += delta_column;
    }
    return true;
}

#define CHECK_LINE(start_row, start_column, delta_row, delta_column) \
        if (checkLine(field, start_row, start_column, delta_row, delta_column, field_dimension)) { \
            outcome.isOver = true; \
            outcome.victor = getCell(field, start_row, start_column, field_dimension) == CellState::X ? Sign::X : Sign::O; \
            return outcome; \
        }


TurnOutcome checkTurnOutcome(CellState *field, size_t field_dimension) {
    TurnOutcome outcome {};
    for (size_t row = 0; row < field_dimension; row++) {
        CHECK_LINE(row, 0, 0, 1)
    }
    for (size_t column = 0; column < field_dimension; column++) {
        CHECK_LINE(0, column, 1, 0)
    }
    CHECK_LINE(0, 0, 1, 1)
    CHECK_LINE(0, 2, 1, -1)

    if (isDraw(field, field_dimension)) {
        outcome.isDraw = true;
        outcome.isOver = true;
    }
    return outcome;
}

#undef CHECK_LINE

TurnOutcome runGameLoop(Sign player_sign) {
    GameData game_data  = initField ();
    TurnOutcome outcome {};

    while(true) {
        if(player_sign == Sign::X) {
            processPlayerTurn(game_data.field, Sign::X, game_data.field_dimension);
        } else {
            processAiTurn(game_data.field, Sign::X, game_data.field_dimension);
        }
        
        printField(game_data.field, game_data.field_dimension);
        outcome = checkTurnOutcome(game_data.field, game_data.field_dimension);
        if (outcome.isOver) {
            return outcome;
        }

        if(player_sign == Sign::O) {
            processPlayerTurn(game_data.field, Sign::O, game_data.field_dimension);
        } else {
            processAiTurn(game_data.field, Sign::O, game_data.field_dimension);
        }
        
        printField(game_data.field, game_data.field_dimension);
        outcome = checkTurnOutcome(game_data.field, game_data.field_dimension);
        if (outcome.isOver) {
            return outcome;
        }
    }
}

void printField(CellState *field, size_t field_dimension) {
    std::cout << "=========\n";
    for (size_t row = 0; row < field_dimension; row++) {
        std::cout << "||";
        for (size_t column = 0; column < field_dimension; column++) {
            switch (getCell(field, row, column, field_dimension))
            {
            case CellState::Empty:
                std::cout << " ";
                break;
            case CellState::X:
                std::cout << "X";
                break;
            case CellState::O:
                std::cout << "O";
                break;
            }
            std::cout << "|";
        }
        std::cout << "|\n";
    }
    std::cout << "=========\n";
}

bool queryPlayAgain() {
    std::cout << "Want to play again? [y or n]: ";
    return askQuestion('y', 'n');
}

void printGameOutcome(const TurnOutcome& outcome, Sign player_sign) {
    if (outcome.isDraw) {
        std::cout << "It's a draw.\n";
    } else if (outcome.victor == player_sign) {
        std::cout << "Congrats! You're winner.\n";
    } else {
        std::cout << "No luck this time.\n";
    }
}

int main() {    
    Sign player_sign = queryPlayerSign();
    bool shouldExit = false;
    while(!shouldExit) {
        auto outcome = runGameLoop(player_sign);
        printGameOutcome(outcome, player_sign);
        shouldExit = !queryPlayAgain();
        if (!shouldExit)
        {
        player_sign = queryPlayerSign();
        }
    }

    return 0;
}