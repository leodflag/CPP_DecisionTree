#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>   //最新版本!!!!!!!!!!!!!!!!!!2/19 最新最新版
using namespace std;
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
//	newNode=(DTree) malloc(sizeof(NODE));
	newNode= new NODE; 
	newNode->data=TreeNode;
	newNode->LeftNode=NULL;
	newNode->MiddleNode=NULL;
	newNode->RightNode=NULL;
	if(isTreeEmpty()){ 
		head=newNode; // 建立根節點 
	}else{
		current=head;
		while(!inserted){
			if(current->LeftNode==NULL){
				if(current->data.left.nextNode==newNode->data.NodeData){
					current->LeftNode=newNode; // 建立連結 
					cout<<"lkhoibiuobyiboyoibyuioyuiohnyuioynuiobuiniun"<<current->data.NodeData<<endl;
					inserted=1; //設為1 
				}else{
					current=current->LeftNode;
				}
			}else if(current->MiddleNode==NULL){
				if(current->data.middle.nextNode==newNode->data.NodeData){
					current->MiddleNode=newNode; 
					inserted=1;
				}else{
					current=current->MiddleNode;
				}
			}else{
				if(current->RightNode==NULL){
					if(current->data.right.nextNode==newNode->data.NodeData){
						current->RightNode=newNode;
						inserted=1;
					}else{
						current=current->RightNode;
					}
				}
			}
		}
	}
}

//----------建立決策樹----------
//void createDecisionTree(int len,string *Array){
//	for(int i;i<len;i++){
//		insertTreeNode(Array);
//	}
//}
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
	string **data; //宣告矩陣
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
struct goalData find_yes_no(string **data,int c,struct goalData str){
	str.goalYES=0;
	str.goalNO=0;
	int goalrow[10],i=0;
//	cout<<"str="<<str.goalString<<endl;
	for(int row=0;row<15;row++){
//		cout<<"data[row][c]="<<data[row][c]<<endl;
		if(str.goalString==data[row][c]){
			goalrow[i]=row;
			cout<<"goalrow[i]goalrow[i]="<<i<<"，"<<goalrow[i]<<endl;
			i++;
//			cout<<str.goalString<<endl;
			if(data[row][5]=="Yes"){
				str.goalYES+=1;
//				cout<<"Y=="<<str.goalYES<<endl;
			}else{
				str.goalNO+=1;
//				cout<<"N=="<<str.goalNO<<endl;
			}
		}
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
	str.goalrow=goalrow;
	return str;
}
string** make_goal_data(string GoalStr,int data_row,int data_col,int c){  //小表 
//	=15;
//	=6;
	string **Data=createBaseData(data_row,data_col);
	for(int r=1;r<data_row;r++){
		if(Data[r][c]!=GoalStr){ // 若不等於目標 
			for(int j=r+1;j<data_row;j++){
				for(int col=0;col<data_col;col++){  // 取下個橫列 
					Data[j-1][col]=Data[j][col];  //  放回前橫列 
				}
			}
			--data_row;
			--r;
		}
	}	

	return Data;
}
//----------找尋目標欄位Gain值----------
DecisionTree findgoalS(string **data2,string *array,int c){ // 尋找不重複的，存入struct goalData，回傳字串陣列
	//---------計算行內不同屬性的Y/N個數-----------
	DecisionTree TreeNode;
	int YesAll=0, NoAll=0, All=0, leftN=0, middleN=0, rightN=0, r=0;
	while(r!=4){
		if(r==0){
			TreeNode.NodeData=array[r]; 	// 第一個字是欄位
		}else if(r==1){
			TreeNode.left.goalString=array[r]; 	 // 左指標指向的字
			TreeNode.left=find_yes_no(data2,c,TreeNode.left);
			leftN=TreeNode.left.goalYES+TreeNode.left.goalNO;
			cout<<"leftN="<<leftN<<endl;
			YesAll+=TreeNode.left.goalYES;
			NoAll+=TreeNode.left.goalNO;
		}else if(r==2){
			TreeNode.middle.goalString=array[r]; 	 // 中指標指向的字
			TreeNode.middle=find_yes_no(data2,c,TreeNode.middle);
			middleN=TreeNode.middle.goalYES+TreeNode.middle.goalNO;
			cout<<"middleN="<<middleN<<endl;
			YesAll+=TreeNode.middle.goalYES;
			NoAll+=TreeNode.middle.goalNO;
		}else if(r==3){
			TreeNode.right.goalString=array[r]; 	 // 右指標指向的字
			TreeNode.right=find_yes_no(data2,c,TreeNode.right);
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
//
//-------------找尋最大Gain值-----------------
DecisionTree findMaxGain(string **data,int col){ 
	DecisionTree goalNode,MaxNode;
	string *goalsArray,*MaxGoalSArray;
	int i;
	double MaxGain=0.0,Gain=0.0;
	for(i=1;i<col;i++){  //5欄 
		goalsArray=returnGoalArray(i); //取得每行屬性 
//		if(goalsArray[i-1]!=""){
//			data=make_goal_data(goalsArray[i-1],i);
//		}
		goalNode=findgoalS(data,goalsArray,i); //找到所有屬性的資料 
		Gain=goalNode.Gain; //取得Gain值 
		cout<<i<<"，Gain="<<Gain<<endl;
		if(Gain>MaxGain){
			goalNode.col=i;
			MaxGain=Gain;
			MaxNode=goalNode;
			MaxGoalSArray=goalsArray;
		}
	}
//	createTreeNode(MaxNode);
	cout<<"MaxGain="<<MaxGain<<endl;
	cout<<"MaxNode="<<MaxNode.NodeData<<endl;
	return 	MaxNode;
}
void inOrder(DTree ptr){
    while(ptr!=NULL){
        inOrder(ptr->LeftNode);
//        printf("%s",ptr->data.NodeData);
        inOrder(ptr->MiddleNode);
        inOrder(ptr->RightNode);
    }
}
void printInOrder(){
    inOrder(head);
    printf("\n");
}
int main() {
	//---------------讀取檔案data----------------
	int data_row=15;
	int data_col=6;
	DecisionTree MaxNode,MaxNode2;
	string **data=createBaseData(data_row,data_col);
	MaxNode=findMaxGain(data,5); //找到最大 
	createTreeNode(MaxNode); //建樹 
	string* goalArray=returnGoalArray(MaxNode.col); // 找最大欄的字串串列 
	// 做小表 
	string **data2=make_goal_data(goalArray[1],15,6,1);
	MaxNode2=findMaxGain(data2,4);

	return 0;
}
