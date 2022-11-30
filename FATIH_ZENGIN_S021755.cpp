#include <iostream>
#include <vector>
#include <string>

using namespace std;

//big enough to dominate all calculations
#define INF 1000;

static vector<vector<int>> grid = {{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};
vector<vector<int>> i_grid;
//turn = true means it is player turn
static bool turn=true;
static bool i_turn=true;
int depth=0;
void render();
bool addTo(int col);
int lookAhead(int depth, int move);

int main(int argc, char const *argv[])
{
    cout<<"Enter search depth: "<<endl;
    cin>>depth;
    render();
    bool gameOver = false;
    int move = 0;
    string input;

    //game loop
    for(int turn=0;turn<21;turn++){
        //player turn
        do{
            cout<<"Enter your move (between 1-7): "<<endl;
            cin >> input;
        try{
            move = stoi(input);
        }catch(exception e){
            move = 0;
        }
        }while(move<1 || move>7);

        if(addTo(move-1)){
            render();
        }else{
            gameOver = true;
            return 0;
        }
        //machine turn
        //think about future boards
        //evaluate them
        i_grid = grid;
        i_turn = turn;

        int best=-INF;
        int movebest = 0;
        for(int cMove=0;cMove<7;cMove++){
            int point = lookAhead(depth,cMove);
            if(best<point) {
                best = point;
                movebest = cMove;
            }
        }
        //make move
        if(addTo(movebest)){
            render();
        }else{
            gameOver = true;
            return 0;
        }

    }
    cout<<"It's a draw!"<<endl;
    return 0;
}

void render(){
    char symbol[3] = {'#','O','X'};
    for(int row=0; row<6 ; row++){
        for (int col=0; col < 7 ;col++){
            cout<<symbol[grid[col][row]];
            cout<<" ";
        }
        cout<<endl;
    }
        cout<<endl;
        cout<<"-------------"<<endl;
}

bool addTo(int col){
    if(col>6 || col < 0 || grid[col][0] != 0){
        string msg = (turn) ? "Player lost" : "Computer lost";
        cout<<msg<<endl;
        return false;
    }
    else{
        int i=0;
        while(++i<6 && grid[col][i]==0);
        // cout<<i<<endl;
        int piece = turn ? 1 : 2;
        grid[col][--i] = piece;

        //check vertical
        for(int j=0; j<4; j++){
            bool compare = true;
            for(int k=0; k<4; k++){
                int expr = i-j+k;
                if(expr > -1 && expr < 6)
                    compare = compare && (piece == grid[col][expr]);
                else compare = false;
            }
            if(compare){
                render();
                string msg = (turn) ? "Player won" : "Computer won";
                cout<<msg<<endl;
                return false;
            }
        }
        //check horizontal
        for(int j=0; j<4; j++){
            bool compare = true;
            for(int k=0; k<4; k++){
                int expr = col-j+k;
                if(expr > -1 && expr < 7)
                compare = compare && (piece == grid[expr][i]);
                else compare = false;
                
            }
            if(compare){
                render();
                string msg = (turn) ? "Player won" : "Computer won";
                cout<<msg<<endl;
                return false;
            }
        }
        //check diagonal 1
        for(int j=0; j<4; j++){
            bool compare = true;
            for(int k=0; k<4; k++){
                int expr = col-j+k;
                int expr2 = i-j+k;
                if(expr > -1 && expr < 7 && expr2 > -1 && expr2 < 6)
                compare = compare && (piece == grid[expr][expr2]);
                else compare = false;
            }
            if(compare){
                render();
                string msg = (turn) ? "Player won" : "Computer won";
                cout<<msg<<endl;
                return false;
            }
        }
        //check diagonal 1
        for(int j=0; j<4; j++){
            bool compare = true;
            for(int k=0; k<4; k++){
                int expr = col+j-k;
                int expr2 = i-j+k;
                if(expr > -1 && expr < 7 && expr2 > -1 && expr2 < 6)
                compare = compare && (piece == grid[expr][expr2]);
                else compare = false;
            }
            if(compare){
                render();
                string msg = (turn) ? "Player won" : "Computer won";
                cout<<msg<<endl;
                return false;
            }
        }

        turn = !turn;
        return true;
    }
}

//this function moves to another node of the tree and (poorly) evaluates the node
int moveTo(int col){
    if(col>6 || col < 0 || i_grid[col][0] != 0){
        if(i_turn) return INF;
        return -INF;
    }
    else{
        int i=0;
        while(++i<6 && i_grid[col][i]==0);

        int piece = i_turn ? 1 : 2;
        i_grid[col][--i] = piece;
        
        //check vertical
        for(int j=0; j<4; j++){
            bool compare = true;
            for(int k=0; k<4; k++){
                int expr = i-j+k;
                if(expr > -1 && expr < 6)
                    compare = compare && (piece == grid[col][expr]);
                else compare = false;
            }
            if(compare){
                if(i_turn) return INF;
                return -INF;
            }
        }
        //check horizontal
        for(int j=0; j<4; j++){
            bool compare = true;
            for(int k=0; k<4; k++){
                int expr = col-j+k;
                if(expr > -1 && expr < 7)
                compare = compare && (piece == grid[expr][i]);
                else compare = false;
                
            }
            if(compare){
                if(i_turn) return INF;
                return -INF;
            }
        }
        //check diagonal 1
        for(int j=0; j<4; j++){
            bool compare = true;
            for(int k=0; k<4; k++){
                int expr = col-j+k;
                int expr2 = i-j+k;
                if(expr > -1 && expr < 7 && expr2 > -1 && expr2 < 6)
                compare = compare && (piece == grid[expr][expr2]);
                else compare = false;
            }
            if(compare){
                if(i_turn) return INF;
                return -INF;
            }
        }
        //check diagonal 1
        for(int j=0; j<4; j++){
            bool compare = true;
            for(int k=0; k<4; k++){
                int expr = col+j-k;
                int expr2 = i-j+k;
                if(expr > -1 && expr < 7 && expr2 > -1 && expr2 < 6)
                compare = compare && (piece == grid[expr][expr2]);
                else compare = false;
            }
            if(compare){
                if(i_turn) return INF;
                return -INF;
            }
        }



        //evaluation criteria: if the move is closer to the middle, give more points
        //bad criteria but the evaluation function is not going to be graded in this assignment
        int point = 10 * (8-abs(4-col));
        if(i_turn) return -point;
        return point;
    }
}

//this func does a dfs (for a given depth) and returns the best possible points for the root node
int lookAhead(int depth, int move){
    if(depth < 1) return moveTo(move);
    else{
        int best = -INF;
        int movebest = 0;
        vector<vector<int>> old_grid = i_grid;
        static bool old_turn=i_turn;
        for(int cMove=0;cMove<7;cMove++){
            int point = lookAhead(depth-1,cMove);
            if(best<point) {
                best = point;
                movebest = cMove;
            }
            i_grid = old_grid;
            i_turn = old_turn;

        }
        return (best/depth) + moveTo(move);
    }
}
