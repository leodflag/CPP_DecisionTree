#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <math.h>
using namespace std;
struct Node{
	string data;
	struct Node *left;
	struct Node *middle;
	struct Node *right;
};
typedef struct Node TNode;
typedef TNode *DecisionTree; // DecisionTree 本身是指標 
struct goalData{  // 目標表單 
	int goalcol; // 目標欄位 
	string goalString; // 目標字串 2個以上 
	int goalYES=0; 
	int goalNO=0;
	double goalE; // 目標熵 
};
void readData(string **data, int r, int c){   
	ifstream file("data_tree.csv");
	int row;
	int col;
	for(row=0;row<r;row++){
		string line;
		if(!getline(file,line)){  //從輸入流讀入一行到string變量，直到沒有0讀入字符、返回false 
			break;
		}
		stringstream iss(line);  //將一個字符串string變量line的值轉成istringstream類別iss
		if(!iss.good()){  //如果沒錯就回傳True 
			break;
		}
		for(col=0;col<c;col++){
			string val;
			getline(iss,val,',');  //字串分割 
			stringstream stringConvertorStringstream(val);  //將一個字符串變量的值傳遞給istringstream對象 
			stringConvertorStringstream>>data[row][col];  //輸入到矩陣
		}
	}
}
double Entropy_function(int YES,int NO){//一個目標字串的熵 
	double entropy;
	int sum;
	sum=YES+NO;
	double yes;
	double no;
	yes=((double)YES/sum);
	no=((double)NO/sum);
	printf("Y==%f,N==%f,sum=%d\n",yes,no,sum); 
	entropy=-(yes*log2(yes))-(no*log2(no));
	printf("entropy==%f\n",entropy); //一個目標字串的熵 
	return entropy;
}
//目前只找一個並計算熵，要找多個用遞迴，在哪裡做，應該是拆開來做 
struct goalData findColAtt(string **data,int c,int r){ //找欄位內的所有屬性，r為第r行 
	struct goalData colAtt; // 要陣列位置還是陣列本身?
	colAtt.goalString=data[r][c];
	for(int row=0;row<15;row++){ //每橫列 
		if(data[row][c]==colAtt.goalString){  //若目標字串等於第row橫列 
			if(data[row][5]=="Yes"){
				colAtt.goalYES+=1;
			}else{
				colAtt.goalNO+=1;
			}
		}
	}
	cout << colAtt.goalString <<endl;
	printf("findColAtt  Yes=%d,No=%d\n",colAtt.goalYES,colAtt.goalNO);
	colAtt.goalE=Entropy_function(colAtt.goalYES,colAtt.goalNO);
	return colAtt;
}
double Gain(double *E,int c){ // 要有兩個以上的才能算，故需要傳入陣列 
}
void findMultgoal(string **data,int data_col){ //計算多個熵 
	int size=4;
	int data_row=15;
	bool reString[data_row]={0};
	struct goalData goalcolAttArray[4];
	struct goalData *goalcolAtt; // 儲存目標欄位的內部各個屬性 n個 
	goalcolAtt=goalcolAttArray; // 指標指向動態陣列 
	for(int i=0;i<size;i++){	
		for(int row=0;row<data_row;row++){ // 每個都輪過一遍 
			if(reString[row]==0){ // 如果沒經歷過 
				//goalcolAtt[i].goalString=data[row][data_col]; //鎖定col，令row為目標
				cout << reString[row]<<endl;
				if(data[row][data_col]==goalcolAtt[i].goalString){
					if(data[row][5]=="Yes"){
						goalcolAtt[i].goalYES+=1;
					}else{
						goalcolAtt[i].goalNO+=1;
					}	
				}
				reString[row]=1;
			}
			//cout << reString[row]<<endl;
			goalcolAtt[i].goalString=data[0][data_col]; 
		}
	} 
	printf("\nsize=%d\n",size) ;//	return goalcolAttArray;
	for(int k=0;k<4;k++){
		cout <<goalcolAtt[k].goalString<<endl;
	}
}
void findMax(double a[]){
	double Max=INT_MIN;
	for(int i=0;i<5;i++){
		if(a[i]>Max){
			Max=a[i];	
		}
	}	
}
int main() {
	int data_row=15;
	int data_col=6;  
	string **data; //宣告矩陣 
	double goalentropy; //宣告一個目標字串的熵 
	data=new string *[data_row]; //建立有data_row個string的陣列位址 
	for(int i=0;i<data_row;i++){
		data[i]=new string[data_col]; // 每條陣列位址內再加data_col個string的陣列位址 
	}
	readData(data,data_row,data_col);
	findMultgoal(data,1);
	printf("YES=%s\n","jijij");
	return 0;
}
