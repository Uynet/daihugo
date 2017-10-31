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
    END = 2,
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
        if(m[i][j] == 0) m[i][j]++;
      }
     }
  }

int main(){
  State s = ADVANCE;
  initmt();
  showmt();

  int cur = 0;
  int quot;
  while(s != END){
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
                m[cur][cur]*=i;
                m[cur][cur]%=11;
                break; 
              }
            }
          }    

         
          // 第cur+1~第cn-1行から第curgyou のquot倍を引く
           /*
           
          1 2 5 1 2 5  <-  cur
          8 9 3 8 9 3
          1 1 4 5 1 4
          ---------------------
          1 2 5 1 2 5  <-  cur
          0 6 . . . .
          0 10 . . . .
          */
          for(int j = 1;j<cn;j++){
             quot = m[cur+j][cur];
            for(int i = 0;i<6;i++){
              m[cur+j][i] = ((m[cur+j][i]-quot * m[cur][i])%11+11)%11;
            }
          }
          //currentを次に移動
          cur++;
          if(cur == cn-1){
                if(m[cur][cur] != 1){
                for(int i=1;i<11;i++){
                  if(m[cur][cur]*i%11 == 1){
                    m[cur][cur]*=i;
                    m[cur][cur]%=11;
                    break; 
                  }
                }
              }    
            s = RECESSION;
          }
          showmt();
        }
        break;
      case RECESSION :
         // 第1~第cur-1行から第cur行のquot倍を引く
           /*
           
          1 2 5  
          0 1 3
          0 0 1 <-  cur
          ---------------------
          1 2 0  
          0 1 0
          0 0 1 <-  cur
          */
         for(int j = 0;j<cur;j++){
             quot = m[j][cur];
            for(int i = 0;i<rn;i++){
              m[j][i] = ((m[j][i]-quot * m[cur][i])%11+11)%11;
            }
          }

          cur--;
          if(cur == 0){
             s = END;

          }
          showmt();
           break;
    }
  }
  
}
