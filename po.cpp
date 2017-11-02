#include <cstdio>
#include <stdio.h>
#include <string>
#include <string.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <math.h>
using namespace std;

typedef vector<int> vi;

#define FOR(i,a,b) for (int i=(a);i<(b);i++)
#define RFOR(i,a,b) for (int i=(b)-1;i>=(a);i--)
#define REP(i,n) for (int i=0;i<(n);i++)
#define RREP(i,n) for (int i=(n)-1;i>=0;i--)

#define ALL(a) (a).begin(),a.end()
#define MAXE(a) *max_element(ALL(a))
#define MINE(a) *min_element(ALL(a))


namespace F8{
    enum bit{
      ooo,
      ioo,
      oio,
      iio,
      ooi,
      ioi,
      oii,
      iii,
  }; 
}
    using namespace F8;
    bit add[8][8] = {
      {ooo,ioo,oio,iio,ooi,ioi,oii,iii},
      {ioo,ooo,iio,oio,ioi,ooi,iii,oii},
      {oio,iio,ooo,ioo,oii,iii,ooi,ioi},
      {iio,oio,ioo,ooo,iii,oii,ioi,ooi},
      {ooi,ioi,oii,iii,ooo,ioo,oio,iio},
      {ioi,ooi,iii,oii,ioo,ooo,iio,oio},
      {oii,iii,ooi,ioi,oio,iio,ooo,ioo},
      {iii,oii,ioi,ooi,iio,oio,ioo,ooo},
    };
    bit mult[8][8] = {
      {ooo,ooo,ooo,ooo,ooo,ooo,ooo,ooo},
      {ooo,ioo,oio,iio,ooi,ioi,oii,iii},
      {ooo,oio,ooi,oii,ioi,iii,ioo,iio},
      {ooo,iio,oii,ioi,ioo,oio,iii,ooi},
      {ooo,ooi,ioi,ioo,iii,iio,oio,oii},
      {ooo,ioi,iii,oio,iio,oii,ooi,ioo},
      {ooo,oii,ioo,iii,oio,ooi,iio,ioi},
      {ooo,iii,iio,ooi,oii,ioo,ioi,oio},
    };
    string binary[8] = {"ooo","ioo","oio","iio","ooi","ioi","oii","iii"};

 enum State{
    ADVANCE  = 0,
    RECESSION = 1,
    END = 2,
  };

int n = 5;
int k = 3;
int t = (n-k)/2;
int cn = n;
int rn = n+1;
int m[100][100];
int r[5] = {0,5,6,3,4};
int b2i(bit b){
  switch(b){
    case ooo: return 0;
    case ioo: return 1;
    case oio: return 2;
    case iio: return 3;
    case ooi: return 4;
    case ioi: return 5;
    case oii: return 6;
    case iii: return 7;
  }
}
  void showmt(){
    for(int j = 0;j<cn;j++){
      for(int i = 0;i<rn;i++){
      cout << m[j][i] << " ";
      }
      cout <<endl;
     }
      cout <<endl;
  }

  void initmt(){
    for(int j = 0;j<cn;j++){
      for(int i = 0;i<rn;i++){
        if(i<n-t){
          m[j][i] = (int)pow(j,i)%8;
        }
        else{
          m[j][i] = r[j]*m[j][i%(n-t)]%8;
        }
      }
     }
  }

int main(){
  State s = ADVANCE;
  initmt();
  showmt();

  int cur = 0;
  int quot;
  showmt();
  while(s != END){
    //前進消去
    switch(s){
      case ADVANCE :
        if(cur < cn){
          //(cur,cur)を1にする
          //3 6 4 3 6 4   <-  cur 
          //8 9 3 8 9 3
          //1 1 4 5 1 4
          //---------------------  cur *= 4 *= 11
          //1 2 5 1 2 5   <-  cur
          //8 9 3 8 9 3
          //1 1 4 5 1 4
          if(m[cur][cur] != 1){
            for(int i=1;i<8;i++){
              if(mult[m[cur][cur]][i] == 1){
                m[cur][cur] = mult[m[cur][cur]][i];
                break; 
              }
            }
          }    
         showmt();
          // 第cur+1~第cn-1行から第curgyou のquot倍を引く
           
          //1 2 5 1 2 5  <-  cur
          //8 9 3 8 9 3
          //1 1 4 5 1 4
          //---------------------
          //1 2 5 1 2 5  <-  cur
          //0 6 . . . .
          //0 10 . . . .

  
          for(int j = 1;j<cn;j++){
             quot = m[cur+j][cur];
            for(int i = 0;i<6;i++){
              m[cur+j][i] = add[ m[cur+j][i] ][ mult[quot][m[cur][i]] ];
            }
              cout << "-----------" << cur << j << endl;
showmt();
          }
          //currentを次に移動
          cur++;
          if(m[cur][cur] != 1){
            for(int i=1;i<8;i++){
              if(mult[m[cur][cur]][i] == 1){
                m[cur][cur] = mult[m[cur][cur]][i];
                break; 
              }
            }
            s = RECESSION;
          }
        }
        break;
      case RECESSION :
         // 第1~第cur-1行から第cur行のquot倍を引く
           
          //1 2 5  
          //0 1 3
          //0 0 1 <-  cur
          //---------------------
          //1 2 0  
          //0 1 0
          //0 0 1 <-  cur
         for(int j = 0;j<cur;j++){
             quot = m[j][cur];
            for(int i = 0;i<rn;i++){
              m[j][i] =add[ m[j][i] ][ mult[quot][m[cur][i]]];
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
