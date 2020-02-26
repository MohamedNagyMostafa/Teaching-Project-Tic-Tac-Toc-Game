#include <iostream>

using namespace std;

/// Game Status
const int DRAW_STATUS = 0;
const int O_PLAYER_WINNER = -3;
const int X_PLAYER_WINNER = 3;
const int IN_GAME = 4;
const int FULL_BOARD = 9;
/// Game Visible Options
const char X_TOKEN = 'X';
const char O_TOKEN = 'O';
const char Empty_TOKEN = '_';
/// Game Hidden Options
const short EMPTY_SLOT = 0;
const short X_SLOT = 1;
const short O_SLOT = -1;
const short BOARD_DIMENTION = 3;
const short TOKEN_SWAPPER = -1;
/// Game Settings
const char ACCEPT = 'y';
const char REJECT = 'n';
const char BOARD_BORDER = '|';
/// Game Strings
const string GAME_RULES =
"Welcome, Enjoy with Tic Tac Toc Game.\
Please read the instruction carefully.\n\
The game board has 8 slots to put a token(X/O). \
Each player have to choose a particular token in advance.\n\
The turn will be played in order(one by one method). There're two \
 expected ends you will meet:\n1-Drawing: When the board is full, and there's \
no player achieved one of the winning states.\n2-A Winner: When one of the player \
successfully fills three slots next to each other by his token whether as diagonal or \
row/column shape.\n\nThere's no undo option in this game, so please be careful while \
choosing the number of the slot where you'll insert you token.\n\n\
| 1 | 2 | 3 |\n| 4 | 5 | 6 |\n| 7 | 8 | 9 |\n\n\
\t\tLet's Begin!";

const string ASK_TO_REPEAT_ST = "Play Again! (y/n)";
const string ASK_TO_LOCATE_TOKEN_ON_BOARD_ST = "Enter the position on the board: ";
const string ASK_TO_STARTING_TOKEN = "Choose which token do you want to start the game? (O/X) ";
const string CONGRATS_X_PLAYER = "\n\tCongratulation for the X token player! \n\tYou are the winner";
const string CONGRATS_O_PLAYER = "\n\tCongratulation for the O token player! \n\tYou are the winner";
const string DRAW_GAME = "\n\tUnfortunately, there's no winner !! \n\tGood luck next time.";

///processes
bool isVictory(short board[BOARD_DIMENTION][BOARD_DIMENTION]);
short boardState(short board[BOARD_DIMENTION][BOARD_DIMENTION]);
///Input & Update
void askPutToken(short board[BOARD_DIMENTION][BOARD_DIMENTION], short token);
bool askToRepeat();
short askstartToken();
///Show to the user
void displayBoard(short board[BOARD_DIMENTION][BOARD_DIMENTION]);
void displayRules();
void displayResult(short lastBoardStatus);



int main(){

    displayRules();
    do{
        short board[BOARD_DIMENTION][BOARD_DIMENTION] ={
            {EMPTY_SLOT,EMPTY_SLOT,EMPTY_SLOT},
            {EMPTY_SLOT,EMPTY_SLOT,EMPTY_SLOT},
            {EMPTY_SLOT,EMPTY_SLOT,EMPTY_SLOT}
        };
        displayBoard(board);
        short token = askstartToken();

        do{

            askPutToken(board, token);

            token =token *TOKEN_SWAPPER;
            displayBoard(board);

        }while(isVictory(board));

        short lastState = boardState(board);
        displayResult(lastState);

    }while(askToRepeat());
return 0;
}

///processes
bool isVictory(short board[BOARD_DIMENTION][BOARD_DIMENTION]){
    return boardState(board) == IN_GAME;
}

short boardState(short board[BOARD_DIMENTION][BOARD_DIMENTION]){
    short draw = 0, row = 0, column = 0,
    rDiagonal=0, lDiagonal=0, rDPointer =0, lDPointer =2;
    short status = IN_GAME; /// Normal State

    for(int i=0; i<BOARD_DIMENTION; i++){
        for(int j=0; j<BOARD_DIMENTION; j++){
            row+= board[i][j];column+= board[j][i];draw +=((board[i][j]==X_SLOT || board[i][j]==O_SLOT)?1:EMPTY_SLOT);
        }
        rDiagonal += board[i][rDPointer];
        lDiagonal += board[i][lDPointer];
        ///Check Victory
        if(row == X_PLAYER_WINNER ||column == X_PLAYER_WINNER ||
            rDiagonal == X_PLAYER_WINNER|| lDiagonal == X_PLAYER_WINNER){
            status=X_PLAYER_WINNER; break;
        }else if(row == O_PLAYER_WINNER ||column == O_PLAYER_WINNER
                 || rDiagonal == O_PLAYER_WINNER || lDiagonal == O_PLAYER_WINNER){
            status=O_PLAYER_WINNER; break;
        }
        row = 0;column = 0; rDPointer+=1; lDPointer-=1;
    }
    /// Check Draw
    if(draw == FULL_BOARD) status=DRAW_STATUS;

    return status;
}

void askPutToken(short board[BOARD_DIMENTION][BOARD_DIMENTION], short token){
    int pos, row, column;
    do{
    cout<<ASK_TO_LOCATE_TOKEN_ON_BOARD_ST;
    cin >> pos;
    pos--;
    row = ((pos<BOARD_DIMENTION)?0:((pos<BOARD_DIMENTION*2)?1:2));
    column = (pos%BOARD_DIMENTION);
    }while(pos < 0 || pos > BOARD_DIMENTION * BOARD_DIMENTION || board[row][column] != EMPTY_SLOT );

    board[row][column] = token;
}

bool askToRepeat(){
    char choice;
    do{
    cout << ASK_TO_REPEAT_ST;
    cin >> choice;
    }while(choice != ACCEPT && choice != REJECT);

    return (choice == ACCEPT);
}

short askstartToken(){
    char token;
    do{
        cout <<ASK_TO_STARTING_TOKEN;
        cin >> token;
    }while(token != X_TOKEN && token != O_TOKEN);

    return (token == X_TOKEN)?X_SLOT: O_SLOT;
}

///Show to the user
void displayBoard(short board[BOARD_DIMENTION][BOARD_DIMENTION]){
    cout<<endl<<endl;
    for(int i =0; i < BOARD_DIMENTION; i++){
            cout<<"\t\t"<<BOARD_BORDER;
        for(int j=0; j<BOARD_DIMENTION; j++){
            cout<<" "<<((board[i][j] == EMPTY_SLOT)?Empty_TOKEN
            :((board[i][j]== X_SLOT)?X_TOKEN:O_TOKEN))<<" "<<BOARD_BORDER;
        }
        cout<<"\t\t"<<endl;
    }
    cout<<endl;
}
void displayRules(){
    cout <<GAME_RULES;
}
void displayResult(short lastBoardStatus){
    switch(lastBoardStatus){
    case X_PLAYER_WINNER:
        cout<<CONGRATS_X_PLAYER;
        break;
    case O_PLAYER_WINNER:
        cout<<CONGRATS_O_PLAYER;
        break;
    default:
        cout<<DRAW_GAME;
    }
}

