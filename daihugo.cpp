#include <cstdio>
#include <stdio.h>
#include <string>
#include <string.h>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

typedef vector<int> vi;

#define FOR(i,a,b) for (int i=(a);i<(b);i++)
#define RFOR(i,a,b) for (int i=(b)-1;i>=(a);i--)
#define REP(i,n) for (int i=0;i<(n);i++)
#define RREP(i,n) for (int i=(n)-1;i>=0;i--)

#define ALL(a) (a).begin(),a.end()
#define MAXE(a) *max_element(ALL(a))
#define MINE(a) *min_element(ALL(a))

int cn = 5;
int rn = 6;
int m[100][100];

class Matrix{
  int cn;//行数
  int rn;//列数(=cn+1)
  int *m;
  public :
  Matrix(int y,int x,int *m){
    this->cn  = y; 
    this->rn  = x; 
    this->m   = m; 
  }; 

};

 enum State{
    ADVANCE  = 0,
    RECESSION = 1,
  };


  void showmt(){
    for(int i = 0;i<cn;i++){
      for(int j = 0;j<rn;j++){
        printf("%-4d",m[i][j]);
      }
      cout <<endl;
     }
      cout <<endl;
  }

  void initmt(){
    for(int i = 0;i<cn;i++){
      for(int j = 0;j<rn;j++){
        m[i][j] = (rn * i + j + 1)%11;
      }
     }
  }

int main(){
  State s = ADVANCE;
  initmt();
  showmt();

  int cur = 0;
  int quot;
  //前進消去
  switch(s){
    case ADVANCE :
      if(cur < cn){
        //(cur,cur)を1にする
        /*
        3 6 4 3 6 4   <-  cur 
        8 9 3 8 9 3
        1 1 4 5 1 4
        ---------------------  cur *= 4 *= 11
        1 2 5 1 2 5   <-  cur
        8 9 3 8 9 3
        1 1 4 5 1 4
        */
        if(m[cur][cur] != 1){
          for(int i=1;i<11;i++){
            if(m[cur][cur]*i%11 == 1){
              m[cur][cur]*=i%=11;
              break; 
            }
          }
        }    

        quot = m[cur+1][cur];
        // 第cur+1列から第cur列のquot倍を引く
         /*
         
        1 2 5 1 2 5  <-  cur
        8 9 3 8 9 3
        1 1 4 5 1 4
        ---------------------
        1 2 5 1 2 5  <-  cur
        0 6 . . . .
        1 1 4 5 1 4
        */
        for(int i = 0;i<rn;i++){
          m[cur+1][i] -= (quot * m[cur][i]);
        }
        cur += 1;
        showmt();
      }
      break;
    case RECESSION :
      break;
  }
  
}
