#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define BOARD_SIZE 8

typedef enum { WHITE, BLACK } Color;
typedef enum { EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING } PieceType;

typedef struct {
    PieceType type;
    Color color;
    bool hasMoved;
} Piece;

Piece board[BOARD_SIZE][BOARD_SIZE];
char playerNames[2][50];
Color turn = WHITE;
bool enPassantAvailable = false;
int enPassantX = -1, enPassantY = -1;

const char *pieceNames[] = {"  ", "P", "R", "N", "B", "Q", "K"};

void initBoard();
void printBoard();
bool movePiece(char *input);
bool isValidMove(int sx, int sy, int dx, int dy);
bool isPathClear(int sx, int sy, int dx, int dy);
bool isCheck(Color color);
bool canCastle(Color color, int side);
void promotePawn(int x, int y);
void switchTurn();
void notifyCheck();
void declareWinner(Color color);
void getMoveInput();
bool isCheckmate(Color color);

int main() {
    printf("Enter White player name: ");
    scanf("%s", playerNames[WHITE]);
    printf("Enter Black player name: ");
    scanf("%s", playerNames[BLACK]);

    initBoard();
    printBoard();

    while (1) {
        if (isCheckmate(turn)) {
            declareWinner((turn == WHITE) ? BLACK : WHITE);
        }
        getMoveInput();
        printBoard();
        notifyCheck();
    }
    return 0;
}

void initBoard() {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j].type = EMPTY;
            board[i][j].hasMoved = false;
        }

    for (int i = 0; i < BOARD_SIZE; i++) {
        board[1][i] = (Piece){PAWN, BLACK, false};
        board[6][i] = (Piece){PAWN, WHITE, false};
    }
    board[0][0] = board[0][7] = (Piece){ROOK, BLACK, false};
    board[7][0] = board[7][7] = (Piece){ROOK, WHITE, false};
    board[0][1] = board[0][6] = (Piece){KNIGHT, BLACK, false};
    board[7][1] = board[7][6] = (Piece){KNIGHT, WHITE, false};
    board[0][2] = board[0][5] = (Piece){BISHOP, BLACK, false};
    board[7][2] = board[7][5] = (Piece){BISHOP, WHITE, false};
    board[0][3] = (Piece){QUEEN, BLACK, false};
    board[7][3] = (Piece){QUEEN, WHITE, false};
    board[0][4] = (Piece){KING, BLACK, false};
    board[7][4] = (Piece){KING, WHITE, false};
}

void printBoard() {
    printf("\n   a   b   c   d   e   f   g   h\n");
    printf(" +---+---+---+---+---+---+---+---+\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d|", 8 - i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            Piece p = board[i][j];
            if (p.type == EMPTY) printf("   |");
            else printf(" %c%c|", p.color == WHITE ? 'W' : 'B', pieceNames[p.type][0]);
        }
        printf("%d\n", 8 - i);
        printf(" +---+---+---+---+---+---+---+---+\n");
    }
    printf("   a   b   c   d   e   f   g   h\n\n");
}

void getMoveInput() {
    char move[10];
    printf("%s's move (e.g., e2e4, resign, draw): ", playerNames[turn]);
    scanf("%s", move);
    if (strcmp(move, "resign") == 0) {
        declareWinner((turn == WHITE) ? BLACK : WHITE);
    }
    if (strcmp(move, "draw") == 0) {
        printf("Draw agreed.\n");
        exit(0);
    }
    if (!movePiece(move)) {
        printf("Invalid move. Try again.\n");
        getMoveInput();
    }
}

bool movePiece(char *input) {
    if (strlen(input) != 4) return false;

    int sy = input[0] - 'a';
    int sx = 8 - (input[1] - '0');
    int dy = input[2] - 'a';
    int dx = 8 - (input[3] - '0');

    if (sx<0||sy<0||dx<0||dy<0||sx>=8||sy>=8||dx>=8||dy>=8) return false;

    Piece *src = &board[sx][sy];
    Piece *dest = &board[dx][dy];
    if (src->type == EMPTY || src->color != turn) return false;

    Piece captured = *dest;
    if (!isValidMove(sx, sy, dx, dy)) return false;

    // en passant
    if (src->type==PAWN && dx==enPassantX && dy==enPassantY && dest->type==EMPTY) {
        if (turn==WHITE) board[dx+1][dy].type = EMPTY;
        else board[dx-1][dy].type = EMPTY;
    }
    // castling
    if (src->type==KING && abs(dy-sy)==2) {
        if (dy>sy) { board[sx][5]=board[sx][7]; board[sx][7].type=EMPTY; }
        else       { board[sx][3]=board[sx][0]; board[sx][0].type=EMPTY; }
    }

    *dest = *src;
    dest->hasMoved = true;
    src->type = EMPTY;
    // pawn promotion
    if (dest->type==PAWN && (dx==0||dx==7)) promotePawn(dx, dy);
    // set en passant
    if (dest->type==PAWN && abs(dx-sx)==2) {
        enPassantAvailable = true;
        enPassantX = (sx+dx)/2; enPassantY = dy;
    } else enPassantAvailable = false;

    // illegal move into check?
    if (isCheck(turn)) {
        *src = *dest;
        *dest = captured;
        return false;
    }

    switchTurn();
    return true;
}

bool isPathClear(int sx,int sy,int dx,int dy){
    int stepX=(dx-sx)?(dx-sx)/abs(dx-sx):0;
    int stepY=(dy-sy)?(dy-sy)/abs(dy-sy):0;
    sx+=stepX; sy+=stepY;
    while(sx!=dx||sy!=dy){
        if(board[sx][sy].type!=EMPTY) return false;
        sx+=stepX; sy+=stepY;
    }
    return true;
}

bool isValidMove(int sx,int sy,int dx,int dy){
    Piece src=board[sx][sy], dest=board[dx][dy];
    if(dest.type!=EMPTY&&dest.color==src.color) return false;
    int dxAbs=abs(dx-sx), dyAbs=abs(dy-sy);
    switch(src.type){
        case PAWN:
            if(src.color==WHITE){
                if(sx-dx==1&&sy==dy&&dest.type==EMPTY) return true;
                if(sx==6&&dx==4&&sy==dy&&dest.type==EMPTY&&board[5][sy].type==EMPTY) return true;
                if(sx-dx==1&&dyAbs==1&&dest.type!=EMPTY&&dest.color==BLACK) return true;
                if(sx==3&&dx==2&&dyAbs==1&&enPassantAvailable&&dx==enPassantX&&dy==enPassantY) return true;
            } else {
                if(dx-sx==1&&sy==dy&&dest.type==EMPTY) return true;
                if(sx==1&&dx==3&&sy==dy&&dest.type==EMPTY&&board[2][sy].type==EMPTY) return true;
                if(dx-sx==1&&dyAbs==1&&dest.type!=EMPTY&&dest.color==WHITE) return true;
                if(sx==4&&dx==5&&dyAbs==1&&enPassantAvailable&&dx==enPassantX&&dy==enPassantY) return true;
            }
            break;
        case ROOK:
            if(sx==dx||sy==dy) return isPathClear(sx,sy,dx,dy);
            break;
        case KNIGHT:
            if((dxAbs==2&&dyAbs==1)||(dxAbs==1&&dyAbs==2)) return true;
            break;
        case BISHOP:
            if(dxAbs==dyAbs) return isPathClear(sx,sy,dx,dy);
            break;
        case QUEEN:
            if((dxAbs==dyAbs&&isPathClear(sx,sy,dx,dy))||((sx==dx||sy==dy)&&isPathClear(sx,sy,dx,dy)))
                return true;
            break;
        case KING:
            if(dxAbs<=1&&dyAbs<=1) return true;
            if(!src.hasMoved&&dxAbs==0&&dyAbs==2) return canCastle(src.color,(dy>sy)?1:0);
            break;
        default: break;
    }
    return false;
}

bool canCastle(Color color,int side){
    int row=(color==WHITE)?7:0;
    if(board[row][4].hasMoved) return false;
    if(side==1){
        if(board[row][7].type!=ROOK||board[row][7].hasMoved) return false;
        if(board[row][5].type!=EMPTY||board[row][6].type!=EMPTY) return false;
    } else {
        if(board[row][0].type!=ROOK||board[row][0].hasMoved) return false;
        if(board[row][1].type!=EMPTY||board[row][2].type!=EMPTY||board[row][3].type!=EMPTY) return false;
    }
    return true;
}

void promotePawn(int x,int y){
    printf("Promote pawn to (Q/R/B/N): ");
    char c; scanf(" %c",&c);
    switch(toupper(c)){
        case 'Q': board[x][y].type=QUEEN; break;
        case 'R': board[x][y].type=ROOK; break;
        case 'B': board[x][y].type=BISHOP; break;
        case 'N': board[x][y].type=KNIGHT; break;
        default: board[x][y].type=QUEEN;
    }
}

bool isCheck(Color color){
    int kx=-1,ky=-1;
    for(int i=0;i<8;i++)for(int j=0;j<8;j++)
        if(board[i][j].type==KING&&board[i][j].color==color)
            kx=i,ky=j;
    for(int i=0;i<8;i++)for(int j=0;j<8;j++)
        if(board[i][j].type!=EMPTY&&board[i][j].color!=color)
            if(isValidMove(i,j,kx,ky)) return true;
    return false;
}

bool isCheckmate(Color color){
    if(!isCheck(color)) return false;
    for(int i=0;i<8;i++)for(int j=0;j<8;j++)
        if(board[i][j].type!=EMPTY&&board[i][j].color==color)
            for(int x=0;x<8;x++)for(int y=0;y<8;y++){
                Piece tempSrc=board[i][j], tempDest=board[x][y];
                if(isValidMove(i,j,x,y)){
                    board[x][y]=tempSrc; board[i][j].type=EMPTY;
                    if(!isCheck(color)){
                        board[i][j]=tempSrc; board[x][y]=tempDest;
                        return false;
                    }
                    board[i][j]=tempSrc; board[x][y]=tempDest;
                }
            }
    return true;
}

void switchTurn(){ turn = (turn==WHITE)?BLACK:WHITE; }

void notifyCheck(){
    if(isCheck(turn)) printf("Check to %s!\n", playerNames[turn]);
}

void declareWinner(Color color){
    printf("%s wins!\n", playerNames[color]);
    exit(0);
}
