# Chess 2.0

## Overview

Chess 2.0 is an advanced chess game that introduces new features and mechanics to the traditional game of chess. This project includes a custom chessboard, unique piece configurations, and special portal mechanics to enhance the gameplay experience.

## Features

- **Custom Chess Pieces**: Define unique chess pieces with custom movement rules.
- **Portals**: Add portals to the chessboard that allow pieces to teleport from one position to another.
- **Game Settings**: Configure game settings such as board size and turn limits.
- **Move Validation**: Ensure that all moves are valid according to the defined rules.
- **Game Management**: Manage the game flow, including determining the winner.

## Getting Started

### Prerequisites

- C++20 compatible compiler
- CMake (optional, for building the project)

### Building the Project

1. Clone the repository:
    ```sh
    git clone https://github.com/ardafincan/Chess-2.0.git
    cd Chess-2.0
    ```

2. Build the project using the provided Makefile:
    ```sh
    make
    ```

3. Run the game:
    ```sh
    ./bin/chess_game data/chess_pieces.json
    ```

### Running Tests

To run the tests, use the following command:
```sh
make test
```

## Project Structure

- `src/`: Contains the source code for the project.
- `include/`: Contains the header files for the project.
- `data/`: Contains JSON configuration files for chess pieces and game settings.
- `third_party/`: Contains a third-party library, including the nlohmann JSON library.
- `tests/`: Contains unit tests for the project.
- `.vscode/`: Contains configuration files for Visual Studio Code.

## Configuration

### Chess Pieces

Chess pieces are defined in JSON files located in the `data/` directory. Each piece has a type, starting positions for both colors, movement rules, and a count.

Example:
```json
{
  "type": "Pawn",
  "positions": {
    "white": [{"x": 0, "y": 1}, {"x": 1, "y": 1}],
    "black": [{"x": 0, "y": 6}, {"x": 1, "y": 6}]
  },
  "movement": {
    "forward": 1,
    "sideways": 0,
    "diagonal": 1,
    "l_shape": false,
    "first_move_forward": 2,
    "diagonal_capture": 1
  },
  "count": 8
}
```

### Portals

Portals are defined in the JSON configuration file and specify entry and exit positions, as well as properties like preserve direction and allowed colors.

Example:
```json
{
  "type": "Portal",
  "id": "portal1",
  "positions": {
    "entry": { "x": 3, "y": 3 },
    "exit": { "x": 5, "y": 5 }
  },
  "properties": {
    "preserve_direction": true,
    "allowed_colors": ["white", "black"],
    "cooldown": 1
  }
}
```

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your changes.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgements

- [nlohmann/json](https://github.com/nlohmann/json) for the JSON library.