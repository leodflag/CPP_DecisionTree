#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>   //最新版本!!!!!!!!!!!!!!!!!!2/19 最新最新版
using namespace std;
struct Data_Str{
	string **Data;
	int D_row;
	int D_col;
};
struct goalData{  // 目標表單
	string nextNode; // 指標下個 node !=NULL 
	string goalString; // 目標字串
	int *goalrow; // 目標所在陣列位址 
	int goalYES;  // 目標Yes數量	 
	int goalNO;	  // 目標No數量 
	double goalE; // 目標熵 
};
typedef struct Node{
	int col;  // 行數 
	string NodeData;  // 欄位 
	struct goalData left;  // 左屬性 
	struct goalData middle; // 中屬性 
	struct goalData right;  // 右屬性 
	double NodeE;  // 整個欄位屬性的 熵 
	double Gain;  //   
}DecisionTree;
struct MaxData{
	string *MaxGoalSArray;
	DecisionTree MaxNode;
	double MaxGain;
};
typedef struct TNode{
	DecisionTree data;
	struct TNode *LeftNode;
	struct TNode *MiddleNode;
	struct TNode *RightNode;
}NODE;
typedef NODE *DTree;
DTree head=NULL;
//---------檢測決策樹是否是空的-----------
int isTreeEmpty() {
	if(head==NULL) return 1;
	else           return 0;
}
//---------輸入決策樹-----------
void createTreeNode(DecisionTree TreeNode){
	DTree newNode, current;
	int inserted=0; // 是否加入新的節點 
	newNode= new NODE; 
	newNode->data=TreeNode;
	newNode->LeftNode=new NODE;
	newNode->MiddleNode=new NODE;
	newNode->RightNode=new NODE;
	cout<<newNode->data.middle.nextNode<<endl;
	if(isTreeEmpty()){ 
		head=newNode; // 建立根節點 
	}else{
		current=head;
		while(!inserted){
			if(current->LeftNode->data.NodeData==""){
				if(current->data.left.nextNode==newNode->data.NodeData){
					current->LeftNode=newNode; // 建立連結 
					inserted=1; //設為1 
				}else{
					current=current->LeftNode;
				}
			}
//			else if(current->MiddleNode==NULL){
//				if(current->data.middle.nextNode==newNode->data.NodeData){
//					current->MiddleNode=newNode; 
//					inserted=1;
//				}else{
//					current=current->MiddleNode;
//				}
//			}else{
//				if(current->RightNode==NULL){
//					if(current->data.right.nextNode==newNode->data.NodeData){
//						current->RightNode=newNode;
//						inserted=1;
//					}else{
//						current=current->RightNode;
//					}
//				}
//			}
		}
	}
//	cout<<head->data.NodeData<<endl;
//	cout<<head->LeftNode->data.NodeData<<endl;
//	cout<<head->MiddleNode->data.NodeData<<endl;
//	cout<<head->RightNode->data.NodeData<<endl;
//	if(head->data.NodeData==""){
//		cout<<&(head->data)<<endl;
//	}
//	
}
//----------讀檔----------
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
//----------建立原始資料----------
string** createBaseData(int data_row,int data_col){
	string **data=NULL; //宣告矩陣
	data=new string *[data_row]; //建立有data_row個string的陣列位址
	for(int i=0;i<data_row;i++){
		data[i]=new string[data_col]; // 每條陣列位址內再加data_col個string的陣列位址
	}
	readData(data,data_row,data_col);
	return data;
}
//---------取得目標直行的字串陣列-----------
string* returnGoalArray(int c){
	int row_len=15,col_len=6;
	string **data=createBaseData(row_len,col_len);
	//----------找尋直行內的不重複屬性----------
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
	//---------將找到的屬性作成陣列-----------
	string *goalDArray=new string[4] ; // 建立 goalData的陣列
	for(int row=0;row<row_len;row++){
		goalDArray[row]=data[row][c]; // 矩陣成員
//		goalDArray[row]=goalD[row].goalString;
		cout<<"goalDArray[row]"<<goalDArray[row]<<endl;
	}
	for(int i=0;i<4;i++){
		if(goalDArray[i]==""){
			goalDArray[i]="NULL";
			cout<<goalDArray[i]<<endl;
		}
	}
	return goalDArray;
}
//----------熵計算----------
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
//---------每行每列對應的Y/NO-----------  
struct goalData find_yes_no(Data_Str data,int c,struct goalData str){
	str.goalYES=0;
	str.goalNO=0;
	int goalrow[10],i=0;
//	cout<<"str="<<str.goalString<<endl;
	for(int row=0;row<data.D_row;row++){
//		cout<<"data[row][c]="<<data[row][c]<<endl;
		if(str.goalString==data.Data[row][c]){
			goalrow[i]=row;
			cout<<"goalrow[i]goalrow[i]="<<i<<"，"<<goalrow[i]<<endl;
			i++;
//			cout<<str.goalString<<endl;
			if(data.Data[row][5]=="Yes"){
				str.goalYES+=1;
//				cout<<"Y=="<<str.goalYES<<endl;
			}else{
				str.goalNO+=1;
//				cout<<"N=="<<str.goalNO<<endl;
			}
		}
	}
	if(str.goalYES==0){ //如果yes完全沒有 
		str.nextNode="No"; //令下一個節點為no 
		str.goalE=0.0;  //熵設為0 
	}else if(str.goalNO==0){
		str.nextNode="Yes";
		str.goalE=0.0;
	}else{
		str.goalE=Entropy_function(str.goalYES,str.goalNO);
	}
	str.goalrow=goalrow;
	return str;
}
Data_Str make_goal_data(string GoalStr,int c){  //小表 ：目標字，所在欄位    OKKKKKKKKKKKKKKKKKKKKK
	int data_row=15;
	int data_col=6;
	Data_Str Data; 
	Data.Data=createBaseData(data_row,data_col);
	for(int r=1;r<data_row;r++){ //控制第一橫行 
		if(Data.Data[r][c]!=GoalStr){ // 若不等於目標 
			for(int j=r+1;j<data_row;j++){  //第二橫行	
				for(int col=0;col<data_col;col++){  // 取下個橫列 
					Data.Data[j-1][col]=Data.Data[j][col];  //  放回前橫列 
				}
			}
				--data_row;
				--r;
		}
	}
	Data.D_row=data_row;
	Data.D_col=data_col;
	for(int j=0;j<Data.D_row;j++){
		for(int i=0;i<Data.D_col;i++){
			cout<<"make_goal_data，"<<Data.Data[i][j]<<endl;
		}
	}
	cout<<"llkhkjhklgkljgkjgkjgjkguigeiwuuwmiwom"<<Data.D_row<<endl;
	return Data;
}
//----------找尋目標欄位Gain值----------
DecisionTree findgoalS(Data_Str data,string *array,int c){ // 尋找不重複的，存入struct goalData，回傳字串陣列
	//---------計算行內不同屬性的Y/N個數-----------
	DecisionTree TreeNode;
	int YesAll=0, NoAll=0, All=0, leftN=0, middleN=0, rightN=0, r=0;
	while(r!=4){
		if(r==0){
			TreeNode.NodeData=array[r]; 	// 第一個字是欄位
		}else if(r==1){
			TreeNode.left.goalString=array[r]; 	 // 左指標指向的字
			TreeNode.left=find_yes_no(data,c,TreeNode.left);
			leftN=TreeNode.left.goalYES+TreeNode.left.goalNO;
			cout<<"leftN="<<leftN<<endl;
			YesAll+=TreeNode.left.goalYES;
			NoAll+=TreeNode.left.goalNO;
		}else if(r==2){
			TreeNode.middle.goalString=array[r]; 	 // 中指標指向的字
			TreeNode.middle=find_yes_no(data,c,TreeNode.middle);
			middleN=TreeNode.middle.goalYES+TreeNode.middle.goalNO;
			cout<<"middleN="<<middleN<<endl;
			YesAll+=TreeNode.middle.goalYES;
			NoAll+=TreeNode.middle.goalNO;
		}else if(r==3){
			TreeNode.right.goalString=array[r]; 	 // 右指標指向的字
			TreeNode.right=find_yes_no(data,c,TreeNode.right);
			rightN=TreeNode.right.goalYES+TreeNode.right.goalNO;
			cout<<"rightN="<<rightN<<endl;
			YesAll+=TreeNode.right.goalYES;
			NoAll+=TreeNode.right.goalNO;
		}else{
			break;
		}
		r++;
	}
	printf("NOALL=%d\n",NoAll);
	printf("YESALL=%d\n",YesAll);
	//----------計算目標Gain值----------
	All=YesAll+NoAll;
	cout<<"ALL="<<All<<endl;
	TreeNode.NodeE=Entropy_function(YesAll,NoAll);
	printf("ALL，TreeNode.NodeE=%f\n",TreeNode.NodeE);
	cout<<"(double)leftN/All*TreeNode.left.goalE=="<<(double)leftN/All*TreeNode.left.goalE<<endl;
	cout<<"(double)middleN/All*TreeNode.middle.goalE="<<(double)middleN/All*TreeNode.middle.goalE<<endl;
	cout<<"(double)rightN/All*TreeNode.right.goalE="<<(double)rightN/All*TreeNode.right.goalE<<endl;
	TreeNode.Gain=TreeNode.NodeE-(double)leftN/All*TreeNode.left.goalE\
								-(double)middleN/All*TreeNode.middle.goalE\
								-(double)rightN/All*TreeNode.right.goalE;
	printf("TreeNode.Gain=%f\n",TreeNode.Gain);
	if(TreeNode.right.goalString==""){
		cout<<"TreeNode.right.goalString===NULL"<<endl;
	}
	return TreeNode;
}
//-------------找尋最大Gain值-----------------
DecisionTree findMaxGain(Data_Str data){ 
	DecisionTree goalNode,MaxNode;
	string *goalsArray,*MaxGoalSArray;   
//	Data_Str Data
	int i;
	double MaxGain=0.0,Gain=0.0;
	for(i=1;i<5;i++){  //1~4欄 
		goalsArray=returnGoalArray(i); //取得每行屬性 
		goalNode=findgoalS(data,goalsArray,i); //找到所有屬性的資料 
		Gain=goalNode.Gain; //取得Gain值 
		cout<<i<<"，Gain="<<Gain<<endl;
		if(Gain>MaxGain){
			goalNode.col=i;
			MaxGain=Gain;
			MaxNode=goalNode;
			MaxGoalSArray=goalsArray;  // 最大的屬性找到後去做小表 
		}
	}
//	createTreeNode(MaxNode);
	cout<<"MaxGain="<<MaxGain<<endl;
	cout<<"MaxNode="<<MaxNode.NodeData<<endl;
//	for(int j=0;j<4;j++){
//		string **DATA=make_goal_data(MaxGoalSArray[j],15,6,goalNode.col);
//		findMaxGain(DATA,goalNode.col);
//	}
	return 	MaxNode;
}
void inOrder(DTree ptr){
    while(ptr!=NULL){
        inOrder(ptr->LeftNode);
        cout<<ptr->data.NodeData<<endl;
        inOrder(ptr->MiddleNode);
        inOrder(ptr->RightNode);
    }
}
void printInOrder(){
    inOrder(head);
    printf("\n");
}
void GO(string *goalArray,int MAX_Col){
	DecisionTree MaxNode;
	for(int i=0;i<4;i++){
		Data_Str data=make_goal_data(goalArray[i],MAX_Col);  //根據SUNNY製作DATA 
		MaxNode=findMaxGain(data); //在SUNNY的資料裡找最大    跟著畫一次決策樹 
		
//		createTreeNode(MaxNode); //建樹 
	}
	
}
int main() {
	//---------------讀取檔案data----------------
	Data_Str data,data2;
	data.D_row=15;
	data.D_col=6;
	DecisionTree MaxNode,MaxNode2;
	data.Data=createBaseData(data.D_row,data.D_col);
	MaxNode=findMaxGain(data);
	cout<<MaxNode.middle.nextNode<<endl;
	cout<<"-------------第一個最大出現拉-----------這裡是分界線------------------------------------------"<<endl; 
	createTreeNode(MaxNode); //建樹 
//	printInOrder();
////	inOrder(MaxNode);
	string *goalArray=returnGoalArray(MaxNode.col); // 找最大欄的字串串列 
////	GO(goalArray,MaxNode.col);  //成功!!!!!!!!!!!!!!!! 
	data2=make_goal_data(goalArray[1],MaxNode.col);  //要改 	
	MaxNode2=findMaxGain(data2);	
	createTreeNode(MaxNode2); //建樹 
//	cout<<"-------------338&339都對啦-----------這裡是分界線------------------------------------------"<<endl; 
//	Data_Str data3; 
//	data3=make_goal_data(goalArray[3],MaxNode.col);  //要改 
//	MaxNode=findMaxGain(data3);	
//	cout<<"-------------第二步做出來啦-----------這裡是分界線------------------------------------------"<<endl;    
//
//	
	
	return 0;
}
