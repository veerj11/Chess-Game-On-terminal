#include "chess.h"
#include<string>
using namespace std;




player::player(string s, Color c)
{
	wins=0 , losses=0 , draws=0;
    name=s;
    color=c;
}
player::player()
{
}




void match::display_result(player p1,player p2)
{
    cout<<"      WIN     LOSS     DRAW"<<endl<<endl;
    cout<<(p1.get_name()).substr(0,3)<<"     "<<p1.getwins()<<"        "<<p1.getlosses()<<"        "<<p1.getdraws()<<endl;
    cout<<(p2.get_name()).substr(0,3)<<"     "<<p2.getwins()<<"        "<<p2.getlosses()<<"        "<<p2.getdraws()<<endl;
}




Square::Square()
{
	piece = EMPTY;
	color = NONE;
}

void Square::setSpace(Square* space)
{
	color = space->getColor();
	piece = space->getPiece();
}

void Square::setEmpty()
{
	color = NONE;
	piece = EMPTY;
}

void Square::setPieceAndColor(Piece p, Color c)
{
	piece = p;
	color = c;
}






Board::Board()
{
    for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			square[i][j].setX(i);
			square[i][j].setY(j);
		}

    for (int i = 0; i < 8; i++)
	{
		square[i][1].setPieceAndColor(PAWN, WHITE);
		square[i][6].setPieceAndColor(PAWN, BLACK);

	}


	square[0][0].setPieceAndColor(ROOK, WHITE);
	square[1][0].setPieceAndColor(KNIGHT, WHITE);
	square[2][0].setPieceAndColor(BISHOP, WHITE);
	square[3][0].setPieceAndColor(QUEEN, WHITE);
	square[4][0].setPieceAndColor(KING, WHITE);
	square[5][0].setPieceAndColor(BISHOP, WHITE);
	square[6][0].setPieceAndColor(KNIGHT, WHITE);
	square[7][0].setPieceAndColor(ROOK, WHITE);

	square[0][7].setPieceAndColor(ROOK, BLACK);
	square[1][7].setPieceAndColor(KNIGHT, BLACK);
	square[2][7].setPieceAndColor(BISHOP, BLACK);
	square[3][7].setPieceAndColor(QUEEN, BLACK);
	square[4][7].setPieceAndColor(KING, BLACK);
	square[5][7].setPieceAndColor(BISHOP, BLACK);
	square[6][7].setPieceAndColor(KNIGHT, BLACK);
	square[7][7].setPieceAndColor(ROOK, BLACK);


	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
			square[j][i].setPieceAndColor(EMPTY, NONE);

	}
}

void Board::printBoard()
{
	cout << "   Y: 1  2  3  4  5  6  7  8 " << endl << "X:" << endl;
	for (int i = 0; i < 8; i++)
	{
	    char ch=i+65;
		cout << " " << ch << "   ";
		for (int j = 0; j < 8; j++)
		{
			Piece p = square[i][j].getPiece();
			Color c = square[i][j].getColor();

			switch (p)
			{
			case KING: (c == WHITE) ? cout << " K " : cout << " k ";
				break;
			case QUEEN: (c == WHITE) ? cout << " Q " : cout << " q ";
				break;
			case BISHOP:(c == WHITE) ? cout << " B " : cout << " b ";
				break;
			case KNIGHT:(c == WHITE) ? cout << " H " : cout << " h ";
				break;
			case ROOK: (c == WHITE) ? cout << " R " : cout << " r ";
				break;
			case PAWN: (c == WHITE) ? cout << " P " : cout << " p ";
				break;
			case EMPTY: cout << " " << " " << " ";
				break;
			default: cout << "XXX";
				break;
			}

		}
		cout << endl;
	}
}






bool Moves::check_pawn(int kingX,int kingY,int i,int j)
{
    if (square[i][j].getColor() == WHITE)
    {
        if ((i + 1 == kingX || i - 1 == kingX) && j + 1 == kingY)
            return true;
    }
    else
    {
        if ((i + 1 == kingX || i - 1 == kingX) && j - 1 == kingY)
            return true;
    }
    return false;
}
bool Moves::check_rook(int kingX,int kingY,int i,int j)
{
    int invalid=0;
    if (i == kingX)
    {
        int yIncrement = (kingY - j)/(abs(kingY-j));
        for (int k = j + yIncrement; k != kingY; k += yIncrement)
        {
            if (square[i][k].getColor() != NONE)
                {
                invalid=1;
                break;
                }
        }
    }
    else if (j == kingY)
    {
        int xIncrement = (kingX - i) / (abs(kingX - i));
        for (int k = i + xIncrement; k != kingX; k += xIncrement)
            {
                if (square[k][j].getColor() != NONE)
                    {
                    invalid=1;
                    break;
                    }
            }
    }
    else invalid=1;
    if(invalid==0)
        return true;
    return false;
}
bool Moves::check_bishop(int kingX,int kingY,int i,int j)
{
    int invalid = 0;
    if (abs(i- kingX) == abs(j - kingY))
    {
        int xIncrement = (kingX - i) / (abs(kingX - i));
        int yIncrement = (kingY - j) / (abs(kingY - j));
        for (int k = 1; k < abs(i - kingX); k++)
        {
            if (square[i + xIncrement*k][j + yIncrement*k].getColor() != NONE)
            {
                invalid=1;
                break;
            }

        }
    }
    else invalid=1;
    if(invalid==0)
                return true;
    return false;
}
bool Moves::check_queen(int kingX,int kingY,int i,int j)
{
    int invalid=0;
    if (i == kingX)
    {
        int yIncrement = (kingY - j)/(abs(kingY-j));
        for (int k = j + yIncrement; k != kingY; k += yIncrement)
        {
            if (square[i][k].getColor() != NONE)
                {
                    invalid=1;
                    break;
                }
        }
    }
    else if (j == kingY)
    {
        int xIncrement = (kingX - i) / (abs(kingX - i));
        for (int k = i + xIncrement; k != kingX; k += xIncrement)
        {
            if (square[k][j].getColor() != NONE)
            {
                invalid=1;
                break;
            }
        }
    }
    else if (abs(i- kingX) == abs(j - kingY))
    {
        int xIncrement = (kingX - i) / (abs(kingX - i));
        int yIncrement = (kingY - j) / (abs(kingY - j));
        for (int k = 1; k < abs(i - kingX); k++)
        {
            if (square[i + xIncrement*k][j + yIncrement*k].getColor() != NONE)
            {
                invalid=1;
                break;
            }
        }
    }
    else invalid=1;
    if(invalid==0)
        return true;
    return false;
}
bool Moves::check_king(int kingX,int kingY,int i,int j)
{
 if (abs(i-kingX)<= 1)
    if (abs(j-kingY)<= 1)
        return true;
  return false;
}
bool Moves::check_knight(int kingX,int kingY,int i,int j)
{
    if ((abs(i - kingX) == 2 && abs(j - kingY) == 1) || (abs(i - kingX) == 1 && abs(j - kingY) == 2))
        return true;
    return false;
}
bool Moves::check(Color colour)
{
    int kingX,kingY;
    bool result=0;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            if(square[i][j].getColor()==colour&&square[i][j].getPiece()==KING)
            {
                kingX=i;
                kingY=j;
                break;
            }
        }

    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
    {
        if(square[i][j].getColor()!=colour)
        {
            if(square[i][j].getPiece()==PAWN)
            {
                if(check_pawn(kingX,kingY,i,j))
                    return true;
            }
            else if(square[i][j].getPiece()==KNIGHT)
            {
                 if(check_knight(kingX,kingY,i,j))
                    return true;
            }
            else if(square[i][j].getPiece()==KING)
            {
                if(check_king(kingX,kingY,i,j))
                    return true;
            }
            else if(square[i][j].getPiece()==ROOK)
            {
                if(check_rook(kingX,kingY,i,j))
                    return true;
            }
            else if(square[i][j].getPiece()==BISHOP)
            {
                if(check_bishop(kingX,kingY,i,j))
                    return true;
            }
            else if(square[i][j].getPiece()==QUEEN)
            {
                if(check_queen(kingX,kingY,i,j))
                    return true;
            }
        }
    }
    return false;
}






bool Board::doMove(player &p1,player &p2)
{
	string move;
	int x1, x2, y1, y2;
	bool stop = false;
	while (!stop)
	{
		(turn == WHITE) ? cout <<p1.get_name()<<"'s turn" << endl : cout <<p2.get_name() <<"'s turn" << endl;
		cout<<"Choose 1 to offer a draw"<<endl;
        cout<<"Choose 2 to resign"<<endl;
		cout <<"Or Type in your move as a single four character string. Use x-coordinates first in each pair." << endl;
		cin >> move;
		if(move[0]==49)
        {
             cout<<"Do you accept the draw?"<<endl;
             cout<<"Type y for yes"<<endl;
             cout<<"Type n for no"<<endl;
             char ans;
             cin>>ans;
             if(ans=='y')
             {
                p1.draw();
                p2.draw();
                return false;
             }
             else if(ans=='n')
             {
                 cout<<"Draw Rejected"<<endl;
                 return true;
             }

        }
        else if(move[0]==50)
        {
              if(turn==WHITE)
              {
                  cout<<p2.get_name()<<" wins"<<endl;
                  p2.win();
                  p1.loss();
                  return false;
              }
              else
              {
                    p1.win();
                    p2.loss();
                    cout<<p1.get_name()<<" wins"<<endl;
                    return false;
              }
        }
        else
        {
		x1 = move[0] - 65;
		y1 = move[1] - 49;
		x2 = move[2] - 65;
		y2 = move[3] - 49;
		bool is_king=(getSquare(x2, y2)->getPiece() == KING);
		if (getSquare(x1, y1)->getColor() == turn)
		{
			if (makeMove(x1, y1, x2, y2) == false)
				cout << "Invalid move, try again." << endl;
			else
            {
				stop = true;
                if(is_king)
                {
                    if(turn==BLACK)
                    {
                        p2.win();
                        p1.loss();
                        system("cls");
                        printBoard();
                        cout<<p2.get_name()<<" wins"<<endl;
                    }

                    else
                    {
                        p1.win();
                        p2.loss();
                        system("cls");
                        printBoard();
                        cout<<p1.get_name()<<" wins"<<endl;
                    }

                    return false;
                }

            }
		}

		else
			cout << "That's not your piece. Try again." << endl;
	 }
	 }




	if (turn == BLACK)
		turn = WHITE;
	else
		turn = BLACK;

	return true;
}

bool Board::Game(player &p1,player &p2)
{
	system("cls");
	printBoard();
	if(turn==WHITE)
     {

        if (check(WHITE)==1)
        {
            cout<<"WHITE is in check"<<endl;
        }
     }
	 else
     {

         if (check (BLACK)==1)
        {
            cout<<"BLACK is in check"<<endl;
        }
     }
	return doMove(p1,p2);
}







bool Moves::moveKing(Square* thisKing, Square* thatSpace)
{
	if (abs(thatSpace->getX() - thisKing->getX())<= 1)
		if (abs(thatSpace->getY() - thisKing->getY())<= 1)
		{
			thatSpace->setSpace(thisKing);
			thisKing->setEmpty();
			return true;
		}
		else return false;
	else return false;
}

bool Moves::moveQueen(Square* thisQueen, Square* thatSpace)
{
	int queenX = thisQueen->getX();
	int queenY = thisQueen->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	int yIncrement;
	int xIncrement;

	bool invalid = false;
	if (queenX != thatX || queenY != thatY)
	{

		if (queenX == thatX)
		{
			yIncrement = (thatY - queenY) / (abs(thatY - queenY));
			for (int i = queenY + yIncrement; i != thatY; i += yIncrement)
			{

				if (square[thatX][i].getColor() != NONE)
					return false;

			}
		}
		else
			if (queenY == thatY)
			{

				xIncrement = (thatX - queenX) / (abs(thatX - queenX));
				for (int i = queenX + xIncrement; i != thatX; i += xIncrement)
				{
					if (square[i][thatY].getColor() != NONE)
						return false;
				}
			}
			else
				if (abs(queenX - thatX) == abs(queenY - thatY))
				{
					xIncrement = (thatX - queenX) / (abs(thatX - queenX));
					yIncrement = (thatY - queenY) / (abs(thatY - queenY));

					for (int i = 1; i < abs(queenX - thatX); i++)
					{
						if (square[queenX + xIncrement*i][queenY + yIncrement*i].getColor() != NONE)
							return false;

					}
				}
				else
					return false;
	}



	if (invalid == false)
	{
		thatSpace->setSpace(thisQueen);
		thisQueen->setEmpty();
		return true;
	}
	else
		return false;
}

bool Moves::moveBishop(Square* thisBishop, Square* thatSpace)
{
	int bishopX = thisBishop->getX();
	int bishopY = thisBishop->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;
	Square *s;
	if (abs(bishopX - thatX) == abs(bishopY - thatY))
	{
		int xIncrement = (thatX - bishopX) / (abs(thatX - bishopX));
		int yIncrement = (thatY - bishopY) / (abs(thatY - bishopY));

		for (int i = 1; i < abs(bishopX - thatX); i++)
		{
			if (square[bishopX + xIncrement*i][bishopY + yIncrement*i].getColor() != NONE)
				return false;

		}
	}
	else
		return false;

	if (invalid == false)
	{
		thatSpace->setSpace(thisBishop);
		thisBishop->setEmpty();
		return true;
	}
	else
	{
		return false;
	}
}

bool Moves::moveKnight(Square* thisKnight, Square* thatSpace)
{

	int knightX = thisKnight->getX();
	int knightY = thisKnight->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();

	if ((abs(knightX - thatX) == 2 && abs(knightY - thatY) == 1) || (abs(knightX - thatX) == 1 && abs(knightY - thatY) == 2))
	{
		thatSpace->setSpace(thisKnight);
		thisKnight->setEmpty();
		return true;
	}
	else
	{
		return false;
	}
}

bool Moves::moveRook(Square* thisRook, Square* thatSpace)
{
	int rookX = thisRook->getX();
	int rookY = thisRook->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;
	if (rookX != thatX || rookY != thatY)
	{

		if (rookX == thatX)
		{
			int yIncrement = (thatY - rookY) / (abs(thatY - rookY));
			for (int i = rookY + yIncrement; i != thatY; i += yIncrement)
			{
				if (square[thatX][i].getColor() != NONE)
					return false;
			}
		}
		else
			if (rookY == thatY)
			{

				int xIncrement = (thatX - rookX) / (abs(thatX - rookX));
				for (int i = rookX + xIncrement; i != thatX; i += xIncrement)
				{
					if (square[i][thatY].getColor() != NONE)
						return false;
				}
			}
			else
				return false;
	}
	if (invalid == false)
	{
		thatSpace->setSpace(thisRook);
		thisRook->setEmpty();
		return true;
	}
	else
	{
		cout << "That is an invalid move for rook";
		return false;
	}
}

void Moves::pawnPromotion(Square* thatSpace)
{
    cout<<"What do you want to promote the pawn to?"<<endl;
    cout<<"choose 1 for queen"<<endl;
    cout<<"choose 2 for knight"<<endl;
    cout<<"choose 3 for bishop"<<endl;
    cout<<"choose 4 for rook"<<endl;
    int choice;
    cin>>choice;
    if(choice==1)
        thatSpace->setPiece(QUEEN);
    else if(choice==2)
        thatSpace->setPiece(KNIGHT);
    else if(choice==3)
        thatSpace->setPiece(BISHOP);
    else if(choice==4)
        thatSpace->setPiece(ROOK);
}
bool Moves::movePawn(Square* thisPawn, Square* thatSpace)
{
	bool invalid = false;
	int pawnX = thisPawn->getX();
	int pawnY = thisPawn->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();

	if (thisPawn->getColor() == WHITE)
	{

		if (pawnX == thatX && thatY == pawnY + 1 && thatSpace->getColor() == NONE)
		{
			thatSpace->setSpace(thisPawn);
			thisPawn->setEmpty();
            if(thatY==7)
             pawnPromotion(thatSpace);
			return true;
		}
		else
			if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY + 1 == thatY  && thatSpace->getColor() == BLACK)
			{
				thatSpace->setSpace(thisPawn);
				thisPawn->setEmpty();
				 if(thatY==7)
                  pawnPromotion(thatSpace);
				return true;
			}
			else
				return false;
	}
	else
		if (thisPawn->getColor() == BLACK)
		{
			if (pawnX == thatX && thatY == pawnY - 1 && thatSpace->getColor() == NONE)
			{
				thatSpace->setSpace(thisPawn);
				thisPawn->setEmpty();
                if(thatY==0)
                pawnPromotion(thatSpace);
				return true;
			}
			else if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY - 1 == thatY  && thatSpace->getColor() == WHITE)
            {
                thatSpace->setSpace(thisPawn);
                thisPawn->setEmpty();
                if(thatY==0)
                pawnPromotion(thatSpace);
                return true;
            }
            else
                return false;
		}
		else
			return false;
}

bool Moves::makeMove(int x1, int y1, int x2, int y2)
{
	if (x1 < 0 || x1>7 || y1 < 0 || y1>7 || x2 < 0 || x2>7 || y2 < 0 || y2>8)
	{
		cout << "One of your inputs was our of bounds" << endl;
		return false;
	}
	Square* source = getSquare(x1, y1);
	Square* destination = getSquare(x2, y2);

	if (source->getColor() == destination->getColor() && destination->getColor() != NONE)
	{
		cout << "Invalid move: cannot land on your own piece" << endl;
		return false;
	}

	switch (source->getPiece())
	{
	case KING: return moveKing(source, destination);
		break;
	case QUEEN: return moveQueen(source, destination);
		break;
	case BISHOP: return moveBishop(source, destination);
		break;
	case KNIGHT: return moveKnight(source, destination);
		break;
	case ROOK: return moveRook(source, destination);
		break;
	case PAWN: return movePawn(source, destination);
		break;
	case EMPTY: cout << "You do not have a piece there" << endl;  return false;
		break;
	default: cout << "Something went wrong" << endl;
		break;
	}
	return false;
}




/*
	QUICK GAME COORDINATED
		F2F3
		E7E6
		G2G3
		D8H4
		G3G4
		H4E1
*/





