#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <math.h>
#include <limits> 
using namespace std;
struct goalData{  // 目標表單 
	string nextNode; // 指標下個 node 
	string goalString; // 目標字串 
	int goalYES; 
	int goalNO;
	double goalE; // 目標熵 
};
typedef struct Node{
	string NodeData;
	struct goalData left;
	struct goalData middle;
	struct goalData right;
	double NodeE;
	double Gain;
}DecisionTree; 
typedef struct TNode{
	string data;
	struct TNode *next;
}NODE;

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
//	printf("Y==%f,N==%f,sum=%d\n",yes,no,sum); 
	entropy=-(yes*log2(yes))-(no*log2(no));
//	printf("entropy==%f\n",entropy); //一個目標字串的熵 
	return entropy;
}
struct goalData find_yes_no(string **data,int c,struct goalData str){
	int sum=0;
	str.goalYES=0;
	str.goalNO=0;
//	cout<<"str="<<str.goalString<<endl;
	for(int row=0;row<15;row++){  
//		cout<<"data[row][c]="<<data[row][c]<<endl;
		if(str.goalString==data[row][c]){  
//			cout<<str.goalString<<endl;
			if(data[row][5]=="Yes"){
				str.goalYES+=1;
//				cout<<"Y=="<<str.goalYES<<endl;
			}else{
				str.goalNO+=1;
//				cout<<"N=="<<str.goalNO<<endl;
			}
		}
//		cout<<row<<endl;
	}	
	if(str.goalYES==0){
		str.nextNode="Yes";
		str.goalE=0.0;
	}else if(str.goalNO==0){
		str.nextNode="No";
		str.goalE=0.0;
	}else{
		str.goalE=Entropy_function(str.goalYES,str.goalNO);
	}
	return str;
}
DecisionTree findgoalS(string **data,string **data2,int c){ // 尋找不重複的，存入struct goalData，回傳字串陣列 
	int row_len=15;
	for(int i=0;i<row_len;i++){
 		for(int j=i+1;j<row_len;j++){
 			if(data[i][c]==data[j][c]){
 				for(int k=j+1;k<row_len;k++){
 					data[k-1][c]=data[k][c];
				}
				--row_len;
				--j; 					
			}
		}
	}
	struct goalData *goalDptr; 
	struct goalData goalD[row_len] ; // 建立 goalData的陣列 
	for(int row=0;row<row_len;row++){
		goalD[row].goalString=data[row][c]; // 矩陣成員 
//		cout<<"dataCol[k][c]jgkgk="<<data[row][c]<<endl;
	}
	DecisionTree TreeNode;
	int YesAll=0, NoAll=0, All=0, leftN=0, middleN=0, rightN=0; 
	for(int r=0;r<row_len;r++){
		if(r==0){
			TreeNode.NodeData=goalD[0].goalString; 	// 第一個字是欄位 
			}else if(r==1){
				TreeNode.left.goalString=goalD[1].goalString;	 // 左指標指向的字 
				TreeNode.left=find_yes_no(data2,c,TreeNode.left);
				leftN=TreeNode.left.goalYES+TreeNode.left.goalNO;
				cout<<"leftN="<<leftN<<endl;
				YesAll+=TreeNode.left.goalYES;
				NoAll+=TreeNode.left.goalNO;
			}else if(r==2){
				TreeNode.middle.goalString=goalD[2].goalString;	 // 中指標指向的字  
				TreeNode.middle=find_yes_no(data2,c,TreeNode.middle);
				middleN=TreeNode.middle.goalYES+TreeNode.middle.goalNO;
				cout<<"middleN="<<middleN<<endl;
				YesAll+=TreeNode.middle.goalYES;
				NoAll+=TreeNode.middle.goalNO;
			}else{
				TreeNode.right.goalString=goalD[3].goalString;	 // 右指標指向的字  
				TreeNode.right=find_yes_no(data2,c,TreeNode.right);
				rightN=TreeNode.right.goalYES+TreeNode.right.goalNO;
				cout<<"rightN="<<rightN<<endl;
				YesAll+=TreeNode.right.goalYES;
				NoAll+=TreeNode.right.goalNO;
			}		
	}
	printf("NOALL=%d\n",NoAll);
	printf("YESALL=%d\n",YesAll);
	All=YesAll+NoAll;
	cout<<"ALL="<<All<<endl;
	TreeNode.NodeE=Entropy_function(YesAll,NoAll);
	cout<<"TreeNode.Gain="<<TreeNode.Gain<<endl;
	cout<<"(double)leftN/All*TreeNode.left.goalE=="<<(double)leftN/All*TreeNode.left.goalE<<endl;
	cout<<"(double)middleN/All*TreeNode.middle.goalE="<<(double)middleN/All*TreeNode.middle.goalE<<endl;
	cout<<"(double)rightN/All*TreeNode.right.goalE="<<(double)rightN/All*TreeNode.right.goalE<<endl;
	TreeNode.Gain=TreeNode.NodeE-(double)leftN/All*TreeNode.left.goalE\
								-(double)middleN/All*TreeNode.middle.goalE\
								-(double)rightN/All*TreeNode.right.goalE;
	printf("TreeNode.Gain=%f\n",TreeNode.Gain);
	
//	goalDptr=goalD; //將指標指向陣列的第一個位址 
	return TreeNode; 
}
double findgoalSNUM(string **data,string **data2,int c){ // 尋找不重複的，存入struct goalData，回傳字串陣列 
	int row_len=15;
	for(int i=0;i<row_len;i++){
 		for(int j=i+1;j<row_len;j++){
 			if(data[i][c]==data[j][c]){
 				for(int k=j+1;k<row_len;k++){
 					data[k-1][c]=data[k][c];
				}
				--row_len;
				--j; 					
			}
		}
	}
	struct goalData *goalDptr; 
	struct goalData goalD[row_len] ; // 建立 goalData的陣列 
	for(int row=0;row<row_len;row++){
		goalD[row].goalString=data[row][c]; // 矩陣成員 
//		cout<<"dataCol[k][c]jgkgk="<<data[row][c]<<endl;
	}
	DecisionTree TreeNode;
	int YesAll=0, NoAll=0, All=0, leftN=0, middleN=0, rightN=0; 
	for(int r=0;r<row_len;r++){
		if(r==0){
			TreeNode.NodeData=goalD[0].goalString; 	// 第一個字是欄位 
			}else if(r==1){
				TreeNode.left.goalString=goalD[1].goalString;	 // 左指標指向的字 
				TreeNode.left=find_yes_no(data2,c,TreeNode.left);
				leftN=TreeNode.left.goalYES+TreeNode.left.goalNO;
//				cout<<"leftN="<<leftN<<endl;
				YesAll+=TreeNode.left.goalYES;
				NoAll+=TreeNode.left.goalNO;
			}else if(r==2){
				TreeNode.middle.goalString=goalD[2].goalString;	 // 中指標指向的字  
				TreeNode.middle=find_yes_no(data2,c,TreeNode.middle);
				middleN=TreeNode.middle.goalYES+TreeNode.middle.goalNO;
				YesAll+=TreeNode.middle.goalYES;
				NoAll+=TreeNode.middle.goalNO;
			}else{
				TreeNode.right.goalString=goalD[3].goalString;	 // 右指標指向的字  
				TreeNode.right=find_yes_no(data2,c,TreeNode.right);
				rightN=TreeNode.right.goalYES+TreeNode.right.goalNO;
				YesAll+=TreeNode.right.goalYES;
				NoAll+=TreeNode.right.goalNO;
			}		
	}
//	printf("NOALL=%d\n",NoAll);
//	printf("YESALL=%d\n",YesAll);
	All=YesAll+NoAll;
//	cout<<"ALL="<<All<<endl;
	TreeNode.NodeE=Entropy_function(YesAll,NoAll);
//	cout<<"(leftN/All)*TreeNode.left.goalE=="<<(double)leftN/All<<endl;
	TreeNode.Gain=TreeNode.NodeE-(double)leftN/All*TreeNode.left.goalE\
								-(double)middleN/All*TreeNode.middle.goalE\
								-(double)rightN/All*TreeNode.right.goalE;
//	printf("TreeNode.Gain=%f\n",TreeNode.Gain);
	
//	goalDptr=goalD; //將指標指向陣列的第一個位址 
	return TreeNode.Gain; 
}

int main() {
	//---------------讀取檔案data---------------- 
	int data_row=15;
	int data_col=6;  
	string **data; //宣告矩陣 
	data=new string *[data_row]; //建立有data_row個string的陣列位址 
	for(int i=0;i<data_row;i++){
		data[i]=new string[data_col]; // 每條陣列位址內再加data_col個string的陣列位址 
	}
	
	string **data2; //宣告矩陣 
	data2=new string *[data_row]; //建立有data_row個string的陣列位址 
	for(int i=0;i<data_row;i++){
		data2[i]=new string[data_col]; // 每條陣列位址內再加data_col個string的陣列位址 
	}
	readData(data,data_row,data_col);
	readData(data2,data_row,data_col);
	//--------------計算-----------------

	DecisionTree TreeDataPtr;
	struct TNode DTNode;
//	TreeDataPtr=findgoalS(data,data2,1);  // 指標 
	
	double MaxGain=0.0,Gain=0.0;
	for(int i=1;i<5;i++){
		Gain=findgoalSNUM(data,data2,i);
		cout<<i<<"，Gain="<<Gain<<endl;
		if(Gain>MaxGain){
			MaxGain=Gain;
		}
	}
	cout<<"MaxGain="<<MaxGain<<endl;
	return 0;
}
