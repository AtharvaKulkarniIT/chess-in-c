# ♟️ chess-in-c

A complete chess game built in C for terminal play between two human players. Includes support for special moves like **castling**, **en passant**, **pawn promotion**, **resign**, and **draw offers**, along with **check** and **checkmate** detection.

> ✨ *This project was built as my First Year Mini Project at VIT, Pune.*

---

## 📌 Features

* Full 8x8 chessboard with move validation
* Two-player terminal interface
* **Special Moves**:

  * Castling (both king-side and queen-side)
  * En Passant
  * Pawn Promotion (to Q/R/B/N)
* **Game Outcomes**:

  * Checkmate
  * Draw offer (auto-accepted for now)
  * Resignation
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

  * `resign` → Resign from the game
  * `draw` → Offer a draw (auto-accepted currently)
* **Promotion**: If a pawn reaches the last rank, you'll be prompted to promote (e.g., `Q`, `N`, `R`, `B`)
* **En Passant**: Detected and allowed if conditions are met

---

## 🎓 Example Demo Game

Here’s a short sample demo session using this chess engine:

```
White's move: e2e4
Black's move: e7e5
White's move: g1f3
Black's move: b8c6
White's move: f1c4
Black's move: g8f6
White's move: d2d4
Black's move: e5d4
White's move: e4e5
Black's move: f6e4
White's move: e1g1     <-- Castling!
Black's move: d7d5
White's move: e5d6     <-- En Passant!
...
```

---

## 🛠️ Code Overview

| Function          | Purpose                           |
| ----------------- | --------------------------------- |
| `initBoard()`     | Sets up initial chess position    |
| `printBoard()`    | Neatly prints current board       |
| `getMoveInput()`  | Takes and interprets player input |
| `movePiece()`     | Executes the move with rules      |
| `isValidMove()`   | Checks legality of move           |
| `canCastle()`     | Handles castling logic            |
| `isCheck()`       | Detects if king is in check       |
| `isCheckmate()`   | Checks checkmate condition        |
| `promotePawn()`   | Handles pawn promotion            |
| `isEnPassant()`   | Allows en passant if applicable   |
| `declareWinner()` | Ends game with winner or draw     |

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

