#pragma once
#include<string>
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

enum Piece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };
enum Color { WHITE, BLACK, NONE };


class player
{
private:
    string name;
    Color color;
    int wins ;
    int losses ;
    int draws ;
public:
    player(string s,Color c);
    player();
    void win(){wins++;}
    void loss(){losses++;}
    void draw(){draws++;}
    int getwins(){return wins;}
    int getlosses(){return losses;}
    int getdraws(){return draws;}
    string get_name(){return name;}

};



class match: player
{
public:
    void display_result(player p1 , player p2);
};



class Square
{
	Piece piece;
	Color color;
	int x, y;
public:
	void setSpace(Square*);
	void setEmpty();
	void setPiece(Piece p){piece=p;}
	void setPieceAndColor(Piece, Color);
	Piece getPiece(){return piece;}
	Color getColor(){return color;}
	void setX(int X) { x = X; }
	void setY(int Y) { y = Y; }
	int getX() { return x; }
	int getY() { return y; }
	Square();
};


Color turn=WHITE;
Square square[8][8];
Square* getSquare(int x, int y)  {return &square[x][y];}



class Moves
{
public:
	bool moveKing(Square* thisKing, Square* thatSpace);
	bool moveQueen(Square* thisQueen, Square* thatSpace);
	bool moveBishop(Square* thisBishop, Square* thatSpace);
	bool moveKnight(Square* thisKnight, Square* thatSpace);
	bool moveRook(Square* thisRook, Square* thatSpace);
	bool movePawn(Square* thisPawn, Square* thatSpace);
	void pawnPromotion(Square* thatSpace);
	bool makeMove(int x1, int y1, int x2, int y2);
	bool check(Color colour);
	bool check_pawn(int kingX,int kingY,int i,int j);
	bool check_rook(int kingX,int kingY,int i,int j);
	bool check_bishop(int kingX,int kingY,int i,int j);
	bool check_queen(int kingX,int kingY,int i,int j);
	bool check_king(int kingX,int kingY,int i,int j);
	bool check_knight(int kingX,int kingY,int i,int j);
};


class Board : public Moves
{
	void printBoard();
public:
	void setSquare(Square * s, int x, int y)  {square[x][y]=*s;}
	bool doMove(player &p1,player &p2);
	bool Game(player &p1,player &p2);

	Board();
};


