#include<stdio.h>
#include<algorithm>
using namespace std;

typedef struct mooncake{
  double num;
  double total;
  double price;
}mc; 

 mc data[1100];
        
bool cmp(mc a,mc b){
     return a.price>b.price;
     }
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    
    for(int i=0;i<n;i++)
     scanf("%lf",&data[i].num);
     
    for(int i=0;i<n;i++)
    scanf("%lf",&data[i].total);
    for(int i=0;i<n;i++)
      data[i].price=data[i].total/data[i].num; 
    sort(data,data+n,cmp);
    
int i = 0;
double result;
  while( (m > 1e-5) && (i < n) ){
    //两种情况
    if( m > data[i].num ){
      m -= data[i].num ;
      result += data[i].total ;
      
    }else{
      result += m*data[i].price;
      m = 0 ;
      break;
    } i++ ;
  }
   
     printf("%.2lf\n",result);  
    
    return 0;
    }