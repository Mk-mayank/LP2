#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class NQueen{

    public :

    bool isSafe(int row , int col, vector<string>&board , int n){
        int x = row ;
        int y = col;
        while(row>= 0 && col >= 0){
            if(board[row][col] == 'Q'){
                return false;
            }
            row--;
            col--;
        }

        row = x ;
        col = y ;

        while(row < n && col >= 0){
            if(board[row][col] == 'Q')return false;
            row++;
            col--;
        }

        row = x ; 
        col = y ;

        while(col >= 0){
            if(board[row][col]=='Q')return false;
            col--;
        }

        return true;
    }
    void solve(int col,vector<string>&board,vector<vector<string>>&ans,int n){
        if(col == n){
            ans.push_back(board);
            return;
        }

        for(int row = 0 ; row < n ; row++){
            if(isSafe(row,col,board,n)){
                board[row][col] = 'Q';
                solve(col+1,board,ans,n);
                board[row][col] = '.';
            }
        }
    }

    void optimize(int col, vector<string>&board,vector<vector<string>>&optians,
        vector<int>&leftrow,vector<int>&uperdiagonal,vector<int>&lowerdiagonal,int n)
        
    {
        if(col == n){
            optians.push_back(board);
            return;
        }

        for(int row= 0 ; row < n ; row++){
            if(leftrow[row] ==0 && lowerdiagonal[row+col]==0 && uperdiagonal[n-1+col-row]==0){
                board[row][col] = 'Q';
                leftrow[row]=1;
                lowerdiagonal[row+col] = 1;
                uperdiagonal[n-1+col-row] = 1 ;

                optimize(col+1,board,optians,leftrow,uperdiagonal,lowerdiagonal,n);

                board[row][col] = '.';
                leftrow[row]=0;
                lowerdiagonal[row+col]=0;
                uperdiagonal[n-1+col-row]=0;

            }
        }

    }

    vector<vector<string>>Nqueen(int n){
        vector<vector<string>>ans;
        vector<vector<string>>optians;
        vector<string>board(n);
        string s(n,'.');
        for(int i = 0 ; i < n ; i++){
            board[i] =s ;
        }

        solve(0,board,ans,n);
        vector<int>leftrow(n,0);
        vector<int>uperdiagonal(2*n-1 ,0);
        vector<int>lowerdiagonal(2*n-1 ,0);
        optimize(0,board,optians,leftrow,uperdiagonal,lowerdiagonal,n);
        return optians;

    }
};

int main(){
    int n = 4; // we are taking 4*4 grid and 4 queens
    NQueen obj;
    vector < vector < string >> ans = obj.Nqueen(n);
    for (int i = 0; i < ans.size(); i++) {
      cout << "Arrangement " << i + 1 << "\n";
      for (int j = 0; j < ans[0].size(); j++) {
        cout << ans[i][j];
        cout << endl;
      }
      cout << endl;
    }
    return 0;
}