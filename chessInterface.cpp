#include <GL/glut.h>
#include <bits/stdc++.h>
#include "printerw.cpp"
#include "printerb.cpp"
using namespace std;
static int menu_id ;
static int value;
static int window;
int screen_render = 0;
string CHESS[7] = {"empty","pawn","horse","bishop","rook","queen","king"};
int cost[7] 		= {		0		,	10	,		30		,		30	,		50	,	90	,	900};
int hdx[8] = { 1, 2, 2, 1,-1,-2,-2,-1};
int hdy[8] = { 2, 1,-1,-2,-2,-1, 1, 2};
int bdx[4] = {1,1,-1,-1};
int bdy[4] = {1,-1,-1,1};
int rdx[4] = {1,0,-1,0};
int rdy[4] = {0,-1,0,1};
float cost0[8][8] = {
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
	{0.5,1.0,1.0,-2.0,-2.0,1.0,1.0,0.5},
	{0.5,-0.5,-1.0,2.5,2.5,-1.0,-0.5,0.5},
	{0.0,0.0,0.0,2.0,2.0,0.0,0.0,0.0},
	{0.5,0.5,1.0,2.5,2.5,1.0,0.5,0.5},
	{1.0,1.0,4.0,3.0,3.0,2.0,1.0,1.0},
	{5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}
};
float cost1[8][8] = {
	{-5.0,-4.0,-3.0,-3.0,-3.0,-3.0,-4.0,-5.0},
	{-4.0,-2.0,0.0,0.0,0.0,0.0,-2.0,-4.0},
	{-3.0,0.5,1.0,1.5,1.5,1.0,0.5,-3.0},
	{-3.0,0.0,1.5,2.0,2.0,1.5,0.0,-3.0},
	{-3.0,0.5,1.5,2.0,2.0,1.5,0.5,-3.0},
	{-3.0,0.0,1.0,1.5,1.5,1.0,0.0,-3.0},
	{-4.0,-2.0,0.0,0.5,0.5,0.0,-2.0,-4.0},
	{-5.0,-4.0,-3.0,-3.0,-3.0,-3.0,-4.0,-5.0}
};
float cost2[8][8] = {
	{-2.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-2.0},
	{-1.0,0.5,0.0,0.0,0.0,0.0,0.5,-1.0},
	{-1.0,1.0,1.0,1.0,1.0,1.0,1.0,-1.0},
	{-1.0,0.0,1.0,1.0,1.0,1.0,0.0,-1.0},
	{-1.0,0.5,0.5,1.0,1.0,0.5,0.5,-1.0},
	{-1.0,0.0,0.5,1.0,1.0,0.5,0.5,-1.0},
	{-1.0,0.0,0.0,0.0,0.0,0.0,0.0,-1.0},
	{-2.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-2.0}
};
float cost3[8][8] = {
	{0.0,0.0,0.0,0.5,0.5,0.0,0.0,0.0},
	{-0.5,0.0,0.0,0.0,0.0,0.0,0.0,-0.5},
	{-0.5,0.0,0.0,0.0,0.0,0.0,0.0,-0.5},
	{-0.5,0.0,0.0,0.0,0.0,0.0,0.0,-0.5},
	{-0.5,0.0,0.0,0.0,0.0,0.0,0.0,-0.5},
	{-0.5,0.0,0.0,0.0,0.0,0.0,0.0,-0.5},
	{-0.5,1.0,1.0,1.0,1.0,1.0,1.0,-0.5},
	{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}
};
float cost4[8][8] = {
	{-2.0,-1.0,-1.0,-0.5,-0.5,-1.0,-1.0,-2.0},
	{-1.0,0.0,0.0,0.0,0.0,0.0,0.0,-1.0},
	{-1.0,0.5,0.5,1.0,1.0,0.5,0.5,-1.0},
	{0.0,0.0,0.5,0.5,0.5,0.5,0.0,-0.5},
	{-0.5,0.0,0.5,0.5,0.5,0.5,0.0,-0.5},
	{-1.0,0.0,0.5,0.5,0.5,0.5,0.0,-1.0},
	{-1.0,0.0,0.0,0.0,0.0,0.0,0.0,-1.0},
	{-2.0,-1.0,-1.0,-0.5,-0.5,-1.0,-1.0,-2.0}
};
float cost5[8][8] = {
	{2.0,3.0,1.0,0.0,0.0,1.0,3.0,2.0},
	{2.0,2.0,0.0,0.0,0.0,0.0,2.0,2.0},
	{-1.0,-2.0,-2.0,-2.0,-2.0,-2.0,-2.0,-1.0},
	{-2.0,-3.0,-3.0,-4.0,-4.0,-3.0,-3.0,-2.0},
	{-3.0,-4.0,-4.0,-5.0,-5.0,-4.0,-4.0,-3.0},
	{-3.0,-4.0,-4.0,-5.0,-5.0,-4.0,-4.0,-3.0},
	{-3.0,-4.0,-4.0,-5.0,-5.0,-4.0,-4.0,-3.0},
	{-3.0,-4.0,-4.0,-5.0,-5.0,-4.0,-4.0,-3.0}
};



vector<int> legalMoves(int, bool);



class chessPiece{
public:
	int pieceDef;
	bool white;
	chessPiece (int pd,bool w){
		pieceDef = pd;
		white = w;
	}

	chessPiece(){
		pieceDef = 0;
		white = true;
	}

	void setEmpty(){
		pieceDef= 0;
	}

	void operator =(chessPiece c){
		this->pieceDef = c.pieceDef;
		this->white = c.white;
	}
};

struct logentry{
public:
	pair<int,int> move;
	chessPiece Apiece ;
	chessPiece Bpiece ;
	logentry(chessPiece A,chessPiece B , int locA , int locB){
		move.first = locA;
		move.second = locB;
		Apiece = A;
		Bpiece = B;
	}
};

class chessSquare{
public:
	int x , y;
	chessPiece curr;
	bool white;
	bool legal;

	chessSquare(){
		x=0;y=0;
		white = true;
		legal = false;
	}

	void drawPiece(){
		if(curr.pieceDef == 0){
			if(white){
				glColor3f(0.941,0.941,0.874);
			}else{
				glColor3f(0.247,0.345,0.4);
			}
			glRecti(x+10,y+10,x+90,y+90);

			return;
		}
		if(curr.white){
			switch (curr.pieceDef) {
				case 1:
						drawwP(x+10,y+10);
						break;
				case 2:
						drawwN(x+10,y+10);
						break;
				case 3:
						drawwB(x+10,y+10);
						break;
				case 4:
						drawwR(x+10,y+10);
						break;
				case 5:
						drawwQ(x+10,y+10);
						break;
				case 6:
						drawwK(x+10,y+10);
						break;
					}
		}else{
			switch (curr.pieceDef) {
				case 1:
						drawbP(x+10,y+10);
						break;
				case 2:
						drawbN(x+10,y+10);
						break;
				case 3:
						drawbB(x+10,y+10);
						break;
				case 4:
						drawbR(x+10,y+10);
						break;
				case 5:
						drawbQ(x+10,y+10);
						break;
				case 6:
						drawbK(x+10,y+10);
						break;
					}
		}
	}
	void setSquare(chessPiece cp){
		curr.white = cp.white;
		curr.pieceDef = cp.pieceDef;
	}

	void setAslegal(){
		glColor3f(0.7421,0.9196,0.62109);
		glRecti(x,y,x+100,y+100);
		drawPiece();
		legal = true;
	}

	void setNormal(){
		legal = false;
		setclear();
		drawPiece();
	}

	void setclear(){
		if(white){
			glColor3f(0.941,0.941,0.874);
		}else{
			glColor3f(0.247,0.345,0.4);
		}
		glRecti(x,y,x+100,y+100);
	}


};

class chessboard{
public:
chessSquare board[8][8];
stack < logentry > move_stack;
bool lastWhite;
int lastx,lasty;
	void initiate(){
		lastWhite = false;
		bool white = true;
		int x = 100,y = 100;
		for(int i = 0 ; i <8;i++){
			for(int j = 0 ; j <8;j++){
					board[i][j].x = y;
					board[i][j].y = x;
					board[i][j].white = !white;
					glRecti(x,y,x+100,y+100);
					x+=100;
					if(white){
						glColor3f(0.941,0.941,0.874);
					}else{
						glColor3f(0.247,0.345,0.4);
					}
					white = !white;
			}
			if(white){
				glColor3f(0.941,0.941,0.874);
			}else{
				glColor3f(0.247,0.345,0.4);
			}
			white = !white;
			x = 100;
			y+=100;
		}

	}
	void setpieces(){
		int order[8] = {4,2,3,5,6,3,2,4};
		for(int i = 0 ; i < 8 ; i++){
			board[i][1].curr.pieceDef = 1;
			board[i][1].curr.white = true;
			board[i][0].curr.white = true;
			board[i][0].curr.pieceDef = order[i];
			board[i][6].curr.pieceDef = 1;
			board[i][6].curr.white = false;
			board[i][7].curr.white = false;
			board[i][7].curr.pieceDef = order[i];
		}
		for(int i = 0 ; i < 8 ; i++){
			for(int j = 2 ; j < 6 ; j++){
					board[i][j].curr.pieceDef  = 0;
			}
		}
		for(int i = 0 ; i < 8 ; i++){
			for(int j = 0 ; j < 8 ; j++){
				board[i][j].drawPiece();
			}
			glFlush();
		}

	}

	void getlegal(int a , int b){
		resetLegal();
		vector<int> moves = legalMoves(a*8+b, lastWhite);
		for(int i = 0 ; i < moves.size() ; i++){
			board[moves[i]/8][moves[i]%8].setAslegal();
		}
		glFlush();
	}

	void resetLegal(){
		for(int i = 0 ; i < 8 ; i++){
			for(int j = 0 ; j < 8 ; j++){
				board[i][j].setNormal();
			}
		}
	}

	void move(int a , int b){
		resetLegal();
		if (board[lastx][lasty].curr.pieceDef==6 && abs(a-lastx) == 2){
			if (a > lastx){
				logentry m(board[a+1][b].curr,board[a-1][b].curr,(a+1)*8 + b, (a-1)*8 + b);
				move_stack.push(m);
				board[a-1][b].curr.pieceDef = 4;
				board[a-1][b].curr.white = board[lastx][lasty].curr.white;
				board[7][b].curr.pieceDef = 0;
				board[a-1][b].drawPiece();
				board[a+1][b].setclear();
			}
			else{
				logentry n(board[a-2][b].curr,board[a+1][b].curr,(a-2)*8 + b, (a+1)*8 + b);
				move_stack.push(n);
				board[a+1][b].curr.pieceDef = 4;
				board[a+1][b].curr.white = board[lastx][lasty].curr.white;
				board[0][b].curr.pieceDef = 0;
				board[a+1][b].drawPiece();
				board[a-2][b].setclear();
			}
		}
		logentry l(board[lastx][lasty].curr,board[a][b].curr,lastx*8 + lasty, a*8 + b);
		move_stack.push(l);

		board[a][b].curr.pieceDef = board[lastx][lasty].curr.pieceDef;
		board[a][b].curr.white = board[lastx][lasty].curr.white;
		board[lastx][lasty].curr.pieceDef = 0;
		if ((b==0 || b==7) && board[a][b].curr.pieceDef==1 )
			board[a][b].curr.pieceDef = 5;
		board[a][b].setclear();
		board[lastx][lasty].setclear();
		board[a][b].drawPiece();

		lastWhite = !lastWhite;
	}

 void click(int button, int state, int x, int y){
			if(button == GLUT_LEFT_BUTTON &&state == GLUT_DOWN){

				int a = x;
				int b = 1000 - y;
				a = a/100;
				b = b/100;
				a--,b--;
				if(a>=0&&a<8&&b>=0&&b<8){
					if (board[a][b].legal == true){
						move(a,b);
					}
					else{
						char c = 'A' + b;
						cout << "squareSelected "<<c<<a<<endl;
						cout << "\tsquare color = "<<(board[a][b].white?"white":"black") << endl;
						cout << "\tselected piece = "<<CHESS[board[a][b].curr.pieceDef]<<endl;
						cout << "\tpiece color = "<<(board[a][b].curr.white?"white":"black") << endl;
						getlegal(a,b);
						lastx = a, lasty = b;
					}
			}
		}
	}

	void emptyMoveLog(){
		while (!move_stack.empty()) {
			move_stack.pop();
		}
	}

	void undo(){
		if(move_stack.empty()){
			return;
		}
		logentry lg = move_stack.top();
		move_stack.pop();
		int last = lg.move.second;
		int prev = lg.move.first;
		chessPiece prevPiece = lg.Apiece;
		chessPiece lastPiece = lg.Bpiece;
		lastx = last/8;
		lasty = last%8;
		int a = prev/8;
		int b = prev%8;
			
		board[a][b].curr.pieceDef = prevPiece.pieceDef;
		board[a][b].curr.white = prevPiece.white;
		board[lastx][lasty].curr.pieceDef = lastPiece.pieceDef;
		board[lastx][lasty].curr.white = lastPiece.white;
		board[a][b].setclear();
		board[lastx][lasty].setclear();
		board[a][b].drawPiece();
		board[lastx][lasty].drawPiece();
		lastWhite = !lastWhite;
		glFlush();
		if (prevPiece.pieceDef == 6 && abs(a-lastx)>1){
			undo();
			lastWhite = !lastWhite;
		}
	}

}cb;

void click(int button, int state, int x, int y){
	if(button != GLUT_RIGHT_BUTTON){
		cb.click(button,state,x,y);
	}

}

bool legalState(bool lastWhite){
	int a,b;
	bool found = false;
	for (int i =0 ; i<8; i++){
		for (int j = 0; j<8; j++){
			if (cb.board[i][j].curr.pieceDef == 6 && (cb.board[i][j].curr.white == lastWhite))
				a = i,b=j;
		}
	}
	for (int i = 0; i<8; i++){												//check if horse is attacking
		int x = a+hdx[i], y = b+hdy[i];
		if (x<0 || x>7 || y<0 || y>7)
			continue;
		if (cb.board[x][y].curr.pieceDef == 2 && cb.board[x][y].curr.white != lastWhite)
			return false;
	}
	for (int i = 0; i<4; i++){												//checking diagonal attack on king
		int x = a+bdx[i], y = b+bdy[i];
		while (x>=0 && x<8 && y>=0 && y<8){

			if (cb.board[x][y].curr.pieceDef != 0){

				if (cb.board[x][y].curr.white == lastWhite || cb.board[x][y].curr.pieceDef == 2 || cb.board[x][y].curr.pieceDef == 4){
					// Intensionally Empty
				}

				else if (cb.board[x][y].curr.pieceDef == 1){		//Found opposite color Pawndiagonally
					if ((x == a+1 || x==a-1) && y==(b+ ((lastWhite)? 1 : -1) )){

						return false;
					}
				}

				else if (cb.board[x][y].curr.pieceDef == 6){		//Found opposite color King diagonally
					if ((x == a+1 || x==a-1) && (y==b+1 || y==b-1) ){

						return false;
					}
				}

				else if (cb.board[x][y].curr.pieceDef == 3){								//Found opposite color Bishop diagonally
					return false;
				}

				else if (cb.board[x][y].curr.pieceDef == 5){								//Found opposite color Queen diagonally
					return false;
				}
				break;
			}
			else
				x+=bdx[i], y+=bdy[i];
		}
	}
	for (int i = 0; i<4; i++){												//checking diagonal attack on king
		int x = a+rdx[i], y = b+rdy[i];
		while (x>=0 && x<8 && y>=0 && y<8){

			if (cb.board[x][y].curr.pieceDef != 0){

				if (cb.board[x][y].curr.white == lastWhite || cb.board[x][y].curr.pieceDef == 1 ||cb.board[x][y].curr.pieceDef == 2 || cb.board[x][y].curr.pieceDef == 3){
					// Intensionally Empty
				}

				else if (cb.board[x][y].curr.pieceDef == 6){							//Found opposite color King HV
					if (abs(x-a) < 2 && abs(y-b) < 2){

						return false;
					}
				}

				else if (cb.board[x][y].curr.pieceDef == 4){								//Found opposite color Rook HV
					return false;
				}

				else if (cb.board[x][y].curr.pieceDef == 5){								//Found opposite color Queen HV
					return false;
				}
				break;
			}
			else
				x+=rdx[i], y+=rdy[i];
		}
	}
	return true;
}

vector<int> legalMoves(int pos, bool lastWhite){											//Castling and Empassant's yet to be implemented
	int a = pos/8,b = pos%8;
	vector<int> moves;
	if (cb.board[a][b].curr.pieceDef == 0 || cb.board[a][b].curr.white == lastWhite)
		return moves;


	if (cb.board[a][b].curr.pieceDef == 1){													//piece is a pawn
		int x = a;
		int y = b + ((cb.board[a][b].curr.white)? 1 : -1);
		if (x>=0 && x<8 && y>=0 && y<8 && cb.board[x][y].curr.pieceDef == 0){
			cb.board[a][b].curr.pieceDef = 0;
			cb.board[x][y].curr.pieceDef = 1;
			cb.board[x][y].curr.white = cb.board[a][b].curr.white;
			if (legalState(!lastWhite)){
				moves.push_back(x*8 + y);
			}
			cb.board[a][b].curr.pieceDef = 1;
			cb.board[x][y].curr.pieceDef = 0;
		}
		x--;
		if (x>=0 && x<8 && y>=0 && y<8 && cb.board[x][y].curr.pieceDef != 0 && cb.board[x][y].curr.white == lastWhite){
			int delp = cb.board[x][y].curr.pieceDef;
			cb.board[a][b].curr.pieceDef = 0;
			cb.board[x][y].curr.pieceDef = 1;
			cb.board[x][y].curr.white = cb.board[a][b].curr.white;
			if (legalState(!lastWhite)){
				moves.push_back(x*8 + y);
			}
			cb.board[a][b].curr.pieceDef = 1;
			cb.board[x][y].curr.pieceDef = delp;
			cb.board[x][y].curr.white = !cb.board[a][b].curr.white;
		}
		x+=2;
		if (x>=0 && x<8 && y>=0 && y<8 && cb.board[x][y].curr.pieceDef != 0 && cb.board[x][y].curr.white == lastWhite){
			int delp = cb.board[x][y].curr.pieceDef;
			cb.board[a][b].curr.pieceDef = 0;
			cb.board[x][y].curr.pieceDef = 1;
			cb.board[x][y].curr.white = cb.board[a][b].curr.white;
			if (legalState(!lastWhite)){
				moves.push_back(x*8 + y);
			}
			cb.board[a][b].curr.pieceDef = 1;
			cb.board[x][y].curr.pieceDef = delp;
			cb.board[x][y].curr.white = !cb.board[a][b].curr.white;
		}
		x--;
		if ((cb.board[a][b].curr.white && y == 2 )||((!cb.board[a][b].curr.white) && y == 5) ){					//Initial Jump
			if (cb.board[x][y].curr.pieceDef == 0){
			y += ((cb.board[a][b].curr.white)? 1 : -1);
			if (x>=0 && x<8 && y>=0 && y<8 && cb.board[x][y].curr.pieceDef == 0){
				cb.board[a][b].curr.pieceDef = 0;
				cb.board[x][y].curr.pieceDef = 1;
				cb.board[x][y].curr.white = cb.board[a][b].curr.white;
				if (legalState(!lastWhite)){
					moves.push_back(x*8 + y);
				}
				cb.board[a][b].curr.pieceDef = 1;
				cb.board[x][y].curr.pieceDef = 0;
			}}
		}
	}

	else if (cb.board[a][b].curr.pieceDef == 2){													//piece is a horse
		int x,y;
		for (int i = 0; i<8; i++){
			x = a+hdx[i], y = b+hdy[i];
			if (x <0 || x > 7 || y<0 || y>7)
				continue;
			if (cb.board[x][y].curr.pieceDef == 0 || cb.board[x][y].curr.white == lastWhite){
				int delp = cb.board[x][y].curr.pieceDef;
				cb.board[a][b].curr.pieceDef = 0;
				cb.board[x][y].curr.pieceDef = 2;
				cb.board[x][y].curr.white = cb.board[a][b].curr.white;
				if (legalState(!lastWhite)){
					moves.push_back(x*8 + y);
				}
				cb.board[a][b].curr.pieceDef = 2;
				cb.board[x][y].curr.pieceDef = delp;
				cb.board[x][y].curr.white = !cb.board[a][b].curr.white;
			}
		}
	}


	else if (cb.board[a][b].curr.pieceDef == 3){													//piece is a bishop
		for (int i = 0; i<4; i++){
			int x = a+bdx[i], y = b+bdy[i];
			while (x>=0 && x<8 && y>=0 && y<8){

				if (cb.board[x][y].curr.pieceDef != 0){
					if (cb.board[x][y].curr.white == lastWhite){
					int delp = cb.board[x][y].curr.pieceDef;
					cb.board[a][b].curr.pieceDef = 0;
					cb.board[x][y].curr.pieceDef = 3;
					cb.board[x][y].curr.white = cb.board[a][b].curr.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					cb.board[a][b].curr.pieceDef = 3;
					cb.board[x][y].curr.pieceDef = delp;
					cb.board[x][y].curr.white = !cb.board[a][b].curr.white;
				}
					break;
				}
				else{
					cb.board[a][b].curr.pieceDef = 0;
					cb.board[x][y].curr.pieceDef = 3;
					cb.board[x][y].curr.white = cb.board[a][b].curr.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					cb.board[a][b].curr.pieceDef = 3;
					cb.board[x][y].curr.pieceDef = 0;
					x+=bdx[i], y+=bdy[i];
				}
			}
		}
	}


	else if (cb.board[a][b].curr.pieceDef == 4){													//piece is a rook
		for (int i = 0; i<4; i++){
		int x = a+rdx[i], y = b+rdy[i];
		while (x>=0 && x<8 && y>=0 && y<8){

			if (cb.board[x][y].curr.pieceDef != 0){
					if (cb.board[x][y].curr.white == lastWhite){
					int delp = cb.board[x][y].curr.pieceDef;
					cb.board[a][b].curr.pieceDef = 0;
					cb.board[x][y].curr.pieceDef = 4;
					cb.board[x][y].curr.white = cb.board[a][b].curr.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					cb.board[a][b].curr.pieceDef = 4;
					cb.board[x][y].curr.pieceDef = delp;
					cb.board[x][y].curr.white = !cb.board[a][b].curr.white;
				}
					break;
				}
				else{
					cb.board[a][b].curr.pieceDef = 0;
					cb.board[x][y].curr.pieceDef = 4;
					cb.board[x][y].curr.white = cb.board[a][b].curr.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					cb.board[a][b].curr.pieceDef = 4;
					cb.board[x][y].curr.pieceDef = 0;
					x+=rdx[i], y+=rdy[i];
				}
			}
		}
	}
	else if (cb.board[a][b].curr.pieceDef == 5){													//piece is a queen
		for (int i = 0; i<4; i++){													//checking diagonal moves
			int x = a+bdx[i], y = b+bdy[i];
			while (x>=0 && x<8 && y>=0 && y<8){

				if (cb.board[x][y].curr.pieceDef != 0){
					if (cb.board[x][y].curr.white == lastWhite){
					int delp = cb.board[x][y].curr.pieceDef;
					cb.board[a][b].curr.pieceDef = 0;
					cb.board[x][y].curr.pieceDef = 5;
					cb.board[x][y].curr.white = cb.board[a][b].curr.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					cb.board[a][b].curr.pieceDef = 5;
					cb.board[x][y].curr.pieceDef = delp;
					cb.board[x][y].curr.white = !cb.board[a][b].curr.white;
				}
					break;
				}
				else{
					cb.board[a][b].curr.pieceDef = 0;
					cb.board[x][y].curr.pieceDef = 5;
					cb.board[x][y].curr.white = cb.board[a][b].curr.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					cb.board[a][b].curr.pieceDef = 5;
					cb.board[x][y].curr.pieceDef = 0;
					x+=bdx[i], y+=bdy[i];
				}
			}
		}
		for (int i = 0; i<4; i++){													//checking horizontal and vertical moves
		int x = a+rdx[i], y = b+rdy[i];
		while (x>=0 && x<8 && y>=0 && y<8){

			if (cb.board[x][y].curr.pieceDef != 0){
					if (cb.board[x][y].curr.white == lastWhite){
					int delp = cb.board[x][y].curr.pieceDef;
					cb.board[a][b].curr.pieceDef = 0;
					cb.board[x][y].curr.pieceDef = 5;
					cb.board[x][y].curr.white = cb.board[a][b].curr.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					cb.board[a][b].curr.pieceDef = 5;
					cb.board[x][y].curr.pieceDef = delp;
					cb.board[x][y].curr.white = !cb.board[a][b].curr.white;
				}
					break;
				}
				else{
					cb.board[a][b].curr.pieceDef = 0;
					cb.board[x][y].curr.pieceDef = 5;
					cb.board[x][y].curr.white = cb.board[a][b].curr.white;
					if (legalState(!lastWhite)){
						moves.push_back(x*8 + y);
					}
					cb.board[a][b].curr.pieceDef = 5;
					cb.board[x][y].curr.pieceDef = 0;
					x+=rdx[i], y+=rdy[i];
				}
			}
		}
	}
	else {																			//checking moves of King
		for (int i = 0; i<4; i++){													//checking horizontal and vertical moves
			int x = a+bdx[i], y = b+bdy[i];
			if ((x>=0 && x<8 && y>=0 && y<8)&&(cb.board[x][y].curr.pieceDef == 0 || cb.board[x][y].curr.white == lastWhite)){
				int delp = cb.board[x][y].curr.pieceDef;
				cb.board[a][b].curr.pieceDef = 0;
				cb.board[x][y].curr.pieceDef = 6;
				cb.board[x][y].curr.white = cb.board[a][b].curr.white;
				if (legalState(!lastWhite)){
					moves.push_back(x*8 + y);
				}
				cb.board[a][b].curr.pieceDef = 6;
				cb.board[x][y].curr.pieceDef = delp;
				cb.board[x][y].curr.white = !cb.board[a][b].curr.white;
			}
			x = a+rdx[i], y = b+rdy[i];
			if ((x>=0 && x<8 && y>=0 && y<8)&&(cb.board[x][y].curr.pieceDef == 0 || cb.board[x][y].curr.white == lastWhite)){
				int delp = cb.board[x][y].curr.pieceDef;
				cb.board[a][b].curr.pieceDef = 0;
				cb.board[x][y].curr.pieceDef = 6;
				cb.board[x][y].curr.white = cb.board[a][b].curr.white;
				if (legalState(!lastWhite)){
					moves.push_back(x*8 + y);
				}
				cb.board[a][b].curr.pieceDef = 6;
				cb.board[x][y].curr.pieceDef = delp;
				cb.board[x][y].curr.white = !cb.board[a][b].curr.white;
			}
		}
		//Check for castling...
		if (a == 4 && b==(cb.board[a][b].curr.white? 0 : 7)){
			bool poss = true;
			cout<<"Checking for castling R..\n";
			if (cb.board[a+1][b].curr.pieceDef != 0 || cb.board[a+2][b].curr.pieceDef != 0 || cb.board[a+3][b].curr.pieceDef != 4 || cb.board[a+3][b].curr.white != cb.board[a][b].curr.white || (legalState(!lastWhite))){
				cout<<"False at 1\n";
				poss =  false;
			}
			if (poss){
			cb.board[a][b].curr.pieceDef = 0;
			cb.board[a+1][b].curr.pieceDef = 6;
			cb.board[a+1][b].curr.white = cb.board[a][b].curr.white;
			if (!legalState(!lastWhite) ){
				cout<<"False at 2\n";
				poss = false;
			}
			cb.board[a+1][b].curr.pieceDef = 0;
			cb.board[a][b].curr.pieceDef = 6;
			}
			if (poss){
			cb.board[a][b].curr.pieceDef = 0;
			cb.board[a+2][b].curr.pieceDef = 6;
			cb.board[a+2][b].curr.white = cb.board[a][b].curr.white;
			if (!legalState(!lastWhite) ){
				cout<<"False at 2\n";
				poss = false;
			}
			cb.board[a+2][b].curr.pieceDef = 0;
			cb.board[a][b].curr.pieceDef = 6;
			}
			if (poss)
				moves.push_back((a+2)*8 + b);
		}
		if (a == 4 && b==(cb.board[a][b].curr.white? 0 : 7)){
			bool poss = true;
			cout<<"Checking for castling L..\n";
			if (cb.board[a-1][b].curr.pieceDef != 0 || cb.board[a-2][b].curr.pieceDef != 0 || cb.board[a-3][b].curr.pieceDef != 0 || cb.board[a-4][b].curr.pieceDef != 4 || cb.board[a-4][b].curr.white != cb.board[a][b].curr.white){
				cout<<"False at 4\n";
				poss =  false;
			}
			if (poss){
			cb.board[a][b].curr.pieceDef = 0;
			cb.board[a-1][b].curr.pieceDef = 6;
			cb.board[a-1][b].curr.white = cb.board[a][b].curr.white;
			if (!legalState(!lastWhite) ){
				cout<<"False at 5\n";
				poss = false;
			}
			cb.board[a-1][b].curr.pieceDef = 0;
			cb.board[a][b].curr.pieceDef = 6;
			}
			if (poss){
			cb.board[a][b].curr.pieceDef = 0;
			cb.board[a-2][b].curr.pieceDef = 6;
			cb.board[a-2][b].curr.white = cb.board[a][b].curr.white;
			if (!legalState(!lastWhite) ){
				cout<<"False at 6\n";
				poss = false;
			}
			cb.board[a-2][b].curr.pieceDef = 0;
			cb.board[a][b].curr.pieceDef = 6;
			}
			if (poss)
				moves.push_back((a-2)*8 + b);
		}
	}
	return moves;
}

void init2d()//how to display
{
	glClearColor (1.0,1.0,1.0,0.0);
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0,1000.0, 0.0, 1000.0);//same like window size(xl,xh,yl,yh)
}

void display(void)
{
	if(value == 1){
    glutPostRedisplay();
		return;
  }
	if(screen_render == 0){
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.0, 0.0, 0.0);
		glRecti(90,90,910,910);
		glColor3f(0.247, 0.345, 0.4);
		glFlush();
		cb.initiate();
		cb.setpieces();
		cb.emptyMoveLog();
		screen_render = 1;
		cout << "lets start " << endl;
		return;
	}else if(screen_render == 2){
		cb.undo();
		screen_render = 1;
	}
}

void menu(int num){
  if(num == 0){
    glutDestroyWindow(window);
    exit(0);
  }else{
		if(num == 1){
			screen_render = 0;
		}else if(num == 2){
			screen_render = 2;
		}
  }
  glutPostRedisplay();
}

void createMenu(void){
		menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Restart", 1);
		glutAddMenuEntry("Undo", 2);
    glutAddMenuEntry("Quit", 0);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitWindowSize (1000, 1000);
	glutInitWindowPosition (00, 00);
	window = glutCreateWindow ("CHESS");
	init2d();
	glutDisplayFunc(display);
	glutMouseFunc(click);
	createMenu();
	glutMainLoop();

	return 0;
}
