# chess-in-c

A complete chess game built in C for terminal play between two human players. Includes support for special moves like **castling**, **en passant**, **pawn promotion**, **resign**, and **draw offers**, along with **check** and **checkmate** detection.


## 📌 Features

* Full 8x8 chessboard with move validation
* Two-player terminal interface
* **Special Moves**:

  *  Castling (both king-side and queen-side)
  *  En Passant
  *  Pawn Promotion (to Q/R/B/N)
* **Game Outcomes**:

  *  Checkmate
  *  Draw offer (auto-accepted for now)
  *  Resignation
* ❇️ Board printed clearly with ranks/files and pieces

---

## 🖥️ Preview

```
   a   b   c   d   e   f   g   h
 +---+---+---+---+---+---+---+---+
8| BR| BN| BB| BQ| BK| BB| BN| BR|8
 +---+---+---+---+---+---+---+---+
7| BP| BP| BP| BP| BP| BP| BP| BP|7
 +---+---+---+---+---+---+---+---+
6|   |   |   |   |   |   |   |   |6
 +---+---+---+---+---+---+---+---+
5|   |   |   |   |   |   |   |   |5
 +---+---+---+---+---+---+---+---+
4|   |   |   |   |   |   |   |   |4
 +---+---+---+---+---+---+---+---+
3|   |   |   |   |   |   |   |   |3
 +---+---+---+---+---+---+---+---+
2| WP| WP| WP| WP| WP| WP| WP| WP|2
 +---+---+---+---+---+---+---+---+
1| WR| WN| WB| WQ| WK| WB| WN| WR|1
 +---+---+---+---+---+---+---+---+
   a   b   c   d   e   f   g   h
```

---

## ⚙️ How to Compile & Run ?

### 🔧 Compile

```bash
gcc chess.c -o chess
```

### ▶️ Run

```bash
./chess
```

---

## 🎮 Gameplay Instructions

* **Move format**: Enter moves like `e2e4`, `g8f6`, etc.
* **Special commands**:

  * `resign` → resign from game
  * `draw` → offer a draw (auto-accepted for now)
* **Promotion**: If a pawn reaches the last rank, you’ll be prompted to promote (e.g. `Q`, `N`, `R`, `B`)
* **En Passant**: Automatically detected and allowed if applicable

---

## 🎓 Example Demo Game (Standard Algebraic Input)

Here's a demo game played using this engine:

```
White's move: e2e4
Black's move: e7e5
White's move: g1f3
Black's move: b8c6
White's move: f1c4
...
...
```


## 🛠️ Code Overview

| Function          | Purpose                           |
| ----------------- | --------------------------------- |
| `initBoard()`     | Sets up initial chess position    |
| `printBoard()`    | Neatly prints current board       |
| `getMoveInput()`  | Takes and interprets player input |
| `movePiece()`     | Executes the move with rules      |
| `isValidMove()`   | Checks legality                   |
| `canCastle()`     | Handles castling logic            |
| `isCheck()`       | Detects if king is in check       |
| `isCheckmate()`   | Checks checkmate condition        |
| `promotePawn()`   | Promotes pawn after 8th/1st rank  |
| `isEnPassant()`   | Allows en passant if legal        |
| `declareWinner()` | Ends game with winner or draw     |


---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

