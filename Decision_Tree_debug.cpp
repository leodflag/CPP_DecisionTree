#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
struct Data_Str{  //紀錄二維矩陣長寬 
	string **Data;
	int D_row;  
	int D_col;
};
struct goalData{  // 目標屬性表單
	string nextNode; // 指標下個 node !=NULL 
	string goalString; // 目標屬性 
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
DTree head=NULL; // 令一開始的根結點為空 
//---------檢測決策樹是否是空的-----------
int isTreeEmpty() {
	if(head==NULL) return 1;
	else           return 0;
}
//---------輸入決策樹-----------
void createTreeNode(DecisionTree TreeNode,string goalStr){
	DTree newNode, current ,YES ,NO;
	int inserted=0; // 是否加入新的節點 
	YES= new NODE; //建立YES根節點做葉節點 
	YES->data.NodeData="Yes";
	YES->LeftNode=new NODE;
	YES->MiddleNode=new NODE;
	YES->RightNode=new NODE;
	NO= new NODE; //建立NO根節點做葉節點 
	NO->data.NodeData="No";
	NO->LeftNode=new NODE;
	NO->MiddleNode=new NODE;
	NO->RightNode=new NODE;
	newNode= new NODE; 
	newNode->data=TreeNode; //建立新的根節點做葉節點 
	newNode->LeftNode=new NODE;
	newNode->MiddleNode=new NODE;
	newNode->RightNode=new NODE;
	if(TreeNode.left.nextNode=="Yes"){  // TreeNode的左子樹若下個指向節點為Yes 
		newNode->LeftNode=YES;   // 新節點的左指標指向YES 
	}else if(TreeNode.left.nextNode=="No"){ // TreeNode的右子樹若下個指向節點為NO 
		newNode->LeftNode=NO;	 // 新節點的左指標指向NO 
	}else{
		newNode->LeftNode->data.NodeData="";  // 令新節點的左指標指向的根資料為空 
	}
	if(TreeNode.middle.nextNode=="Yes"){  //  中子樹 
		newNode->MiddleNode=YES;
	}else if(TreeNode.middle.nextNode=="No"){
		newNode->MiddleNode=NO;
	}else{	
		newNode->MiddleNode->data.NodeData="";
	}
	if(TreeNode.right.nextNode=="Yes"){ //右子樹 
		newNode->RightNode=YES;
	}else if(TreeNode.right.nextNode=="No"){
		newNode->RightNode=NO;
	}else{
		newNode->RightNode->data.NodeData="";
	}
	cout<<"newNode->data.NodeData，"<<newNode->data.NodeData<<endl;
	cout<<"newNode->LeftNode->data.NodeData，"<<newNode->LeftNode->data.NodeData<<endl;
	cout<<"newNode->MiddleNode->data.NodeData，"<<newNode->MiddleNode->data.NodeData<<endl;
	cout<<"newNode->RightNode->data.NodeData，"<<newNode->RightNode->data.NodeData<<endl;
	if(isTreeEmpty()){  //return 1 =NULL ； 0=樹存在 
		head=newNode; // 建立根節點 
	}else{
		current=head;  //令當前指標指向head 
		while(!inserted){  //若新節點未加入 
			if(current->LeftNode->data.NodeData==""){  //如果當前節點的左節點指向的根資料為空 
				if(current->data.left.goalString==goalStr){ //如果當前節點指向的資料內左屬性的目標屬性跟輸入的屬性一樣 
					current->LeftNode=newNode; // 建立連結 
					inserted=1;
				}else{
					current=current->LeftNode; // 令左指向的節點為當前節點，繼續左走 
				}
			}else if(current->MiddleNode->data.NodeData==""){  //當前節點的中節點 
				if(current->data.middle.goalString==goalStr){
					current->MiddleNode=newNode;
					inserted=1;
				}else{
					current=current->MiddleNode;
				}
			}else if(current->RightNode->data.NodeData==""){  //當前節點的右節點  
				if(current->data.right.goalString==goalStr){
					current->RightNode=newNode;
					inserted=1;
				}else{
					current=current->RightNode;
				}			
			}			
		}
	}
	cout<<"head->data.NodeData，"<<head->data.NodeData<<endl;
	cout<<"head->LeftNode->data.NodeData，"<<head->LeftNode->data.NodeData<<endl;
	cout<<"head->MiddleNode->data.NodeData，"<<head->MiddleNode->data.NodeData<<endl;
	cout<<"head->RightNode->data.NodeData，"<<head->RightNode->data.NodeData<<endl;
}
//----------讀檔----------
void readData(string **data, int r, int c){
	ifstream file("data_tree.csv"); //讀入檔案 
	int row;
	int col;
	for(row=0;row<r;row++){
		string line;
		if(!getline(file,line))  //從輸入流讀入一行到string變量，直到沒有0讀入字符、返回false
			break;
		stringstream iss(line);  //將一個字符串string變量line的值轉成istringstream類別iss
		if(!iss.good())  //如果沒錯就回傳True
			break;
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
	for(int i=0;i<data_row;i++)
		data[i]=new string[data_col]; // 每條陣列位址內再加data_col個string的陣列位址
	readData(data,data_row,data_col);
	return data;
}
//---------取得目標直行的字串陣列-----------
string* returnGoalArray(int c){ // c為特定欄位 
	int row_len=15,col_len=6;
	string **data=createBaseData(row_len,col_len);
	//----------找尋直行內的不重複屬性----------
	for(int i=0;i<row_len;i++){
 		for(int j=i+1;j<row_len;j++){
 			if(data[i][c]==data[j][c]){  //若第二個橫排跟第一個橫排一樣 
 				for(int k=j+1;k<row_len;k++){
 					data[k-1][c]=data[k][c]; //將第三個橫排往前放到第二個橫排 
				}
				--row_len; //行排數量減1 
				--j;
			}
		}
	}
	//---------將找到的屬性作成陣列-----------
	string *goalDArray=new string[4] ; // 建立 goalData的陣列
	for(int row=0;row<row_len;row++){
		goalDArray[row]=data[row][c]; // 矩陣成員
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
struct goalData find_yes_no(Data_Str data,int c,struct goalData str){
	str.goalYES=0;
	str.goalNO=0;
	int goalrow[10],i=0;
//	cout<<"str="<<str.goalString<<endl;
	for(int row=0;row<data.D_row;row++){
//		cout<<"data[row][c]="<<data[row][c]<<endl;
		if(str.goalString==data.Data[row][c]){ // 若目標字串==資料表內的字串 
			goalrow[i]=row;
			cout<<"goalrow[i]"<<i<<"，"<<goalrow[i]<<endl;
			i++;
//			cout<<str.goalString<<endl;
			if(data.Data[row][5]=="Yes"){  //找出同橫列的Y/N 
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
	}
	else{
		str.goalE=Entropy_function(str.goalYES,str.goalNO);
	}
	return str;
}
Data_Str make_goal_data(string GoalStr,int c){  //小表 ：目標字，所在欄位    OKKKKKKKKKKKKKKKKKKKKK
	int data_row=15;
	int data_col=6;
	Data_Str Data; 
	Data.Data=createBaseData(data_row,data_col);  // 做大表 
	for(int r=1;r<data_row;r++){ // 控制第一橫行 
		if(Data.Data[r][c]!=GoalStr){ // 若不等於目標 
			for(int j=r+1;j<data_row;j++){  // 第二橫行	
				for(int col=0;col<data_col;col++){  // 取下個橫列 
					Data.Data[j-1][col]=Data.Data[j][col];  //  放回前橫列 
				}
			}
				--data_row;
				--r;
		}
	}
	// 印出小表、確認是否正確 
	Data.D_row=data_row;
	Data.D_col=data_col;
	for(int j=0;j<Data.D_row;j++){
		for(int i=0;i<Data.D_col;i++){
			cout<<"make_goal_data，"<<Data.Data[i][j]<<endl;
		}
	}
	return Data;
}
//----------找尋目標欄位Gain值----------
DecisionTree findgoalS(Data_Str data,string *array,int c){ // 尋找不重複的，存入struct goalData，回傳字串陣列
	//---------計算行內不同屬性的Y/N個數-----------
	DecisionTree TreeNode;
	int YesAll=0, NoAll=0, All=0, leftN=0, middleN=0, rightN=0, r=0;
	while(r!=4){
		if(r==0){  // 為了將根節點資料、左中右屬性抓出來 
			TreeNode.NodeData=array[r]; 	// 第一個字是欄位
		}else if(r==1){
			TreeNode.left.goalString=array[r]; 	 // 左屬性) 
			TreeNode.left=find_yes_no(data,c,TreeNode.left); // 找Y/N個數 
			leftN=TreeNode.left.goalYES+TreeNode.left.goalNO; // 計算左屬性個數 
			cout<<"leftN="<<leftN<<endl;
			YesAll+=TreeNode.left.goalYES; // 計算表的全部YES 
			NoAll+=TreeNode.left.goalNO;   // 計算表的全部NO 
		}else if(r==2){
			TreeNode.middle.goalString=array[r]; 	 // 中屬性
			TreeNode.middle=find_yes_no(data,c,TreeNode.middle);
			middleN=TreeNode.middle.goalYES+TreeNode.middle.goalNO;
			cout<<"middleN="<<middleN<<endl;
			YesAll+=TreeNode.middle.goalYES;
			NoAll+=TreeNode.middle.goalNO;
		}else if(r==3){
			TreeNode.right.goalString=array[r]; 	 // 右屬性
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
	if(leftN==0){ //若左屬性個數為0 
		TreeNode.left.nextNode="NULL"; // 左屬性的下個指向為NULL 
	}
	if(middleN==0){
		TreeNode.middle.nextNode="NULL";
	}
	if(rightN==0){
		TreeNode.right.nextNode="NULL";
	}
	printf("NOALL=%d\n",NoAll);
	printf("YESALL=%d\n",YesAll);
	//----------計算目標Gain值----------
	All=YesAll+NoAll;
	cout<<"ALL="<<All<<endl;
	TreeNode.NodeE=Entropy_function(YesAll,NoAll); // 計算根節點的熵 
	printf("ALL，TreeNode.NodeE=%f\n",TreeNode.NodeE);
	cout<<"(double)leftN/All*TreeNode.left.goalE=="<<(double)leftN/All*TreeNode.left.goalE<<endl;
	cout<<"(double)middleN/All*TreeNode.middle.goalE="<<(double)middleN/All*TreeNode.middle.goalE<<endl;
	cout<<"(double)rightN/All*TreeNode.right.goalE="<<(double)rightN/All*TreeNode.right.goalE<<endl;
	// 計算根節點的資訊獲利 
	TreeNode.Gain=TreeNode.NodeE-(double)leftN/All*TreeNode.left.goalE \   
								-(double)middleN/All*TreeNode.middle.goalE \
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
	string *goalsArray;   
	int i;
	double MaxGain=0.0,Gain=0.0;
	for(i=1;i<5;i++){  //1~4欄 
		goalsArray=returnGoalArray(i); //取得每行屬性 
		goalNode=findgoalS(data,goalsArray,i); //找到所有屬性的資料 
		Gain=goalNode.Gain; //取得根節點Gain值 
		cout<<i<<"，Gain="<<Gain<<endl;
		if(Gain>MaxGain){  //找最大Gain值的根節點 
			goalNode.col=i;
			MaxGain=Gain;
			MaxNode=goalNode;
		}
	}
	cout<<"MaxGain="<<MaxGain<<endl;
	cout<<"MaxNode="<<MaxNode.NodeData<<endl;
	cout<<"MaxNode.left.goalString="<<MaxNode.left.goalString<<endl;
	cout<<"MaxNode.left.nextNode="<<MaxNode.left.nextNode<<endl;
	cout<<"MaxNode.middle.goalString="<<MaxNode.middle.goalString<<endl;
	cout<<"MaxNode.middle.nextNode="<<MaxNode.middle.nextNode<<endl;
	cout<<"MaxNode.right.goalString="<<MaxNode.right.goalString<<endl;
	cout<<"MaxNode.right.nextNode="<<MaxNode.right.nextNode<<endl;
	return 	MaxNode;
}
void inOrder(DTree ptr){  // 中序走訪 
    if(ptr->data.NodeData!="")  // 停止條件 ；若根節點的資料不為空 
        cout<<ptr->data.NodeData<<endl;  // 印出來 
    else 
    	return;
    inOrder(ptr->LeftNode); //遞迴： 輸入的時候會變成  ptr->LeftNode->data.NodeData
    inOrder(ptr->MiddleNode);
    inOrder(ptr->RightNode);
}
void GO(string *goalArray,int MAX_Col){
	DecisionTree MaxNode;
	for(int i=1;i<4;i++){
		if(goalArray[i]!=""){ // 為了濾掉已經有葉節點的overcast屬性 
			Data_Str data=make_goal_data(goalArray[i],MAX_Col);  //根據SUNNY製作DATA 
			MaxNode=findMaxGain(data); //在SUNNY的資料裡找最大    跟著畫一次決策樹 
			if(MaxNode.left.nextNode==""){  //為了解決最後一步的strong在find_yes_no時未被分類 
				if(MaxNode.left.goalYES>MaxNode.left.goalNO){
					MaxNode.left.nextNode="Yes";
				}else{
					MaxNode.left.nextNode="No";
				}				
			}
			if(MaxNode.middle.nextNode==""){
				if(MaxNode.middle.goalYES>MaxNode.middle.goalNO){
					MaxNode.middle.nextNode="Yes";
				}else{
					MaxNode.middle.nextNode="No";
				}				
			}
			if(MaxNode.right.nextNode==""){
				if(MaxNode.right.goalYES>MaxNode.right.goalNO){
					MaxNode.right.nextNode="Yes";
				}else{
					MaxNode.right.nextNode="No";
				}				
			}
			createTreeNode(MaxNode,goalArray[i]); //建樹 
						
		}

	}
	
}
int main() {
	Data_Str data,data2;
	data.D_row=15;
	data.D_col=6;
	DecisionTree MaxNode;
	data.Data=createBaseData(data.D_row,data.D_col); //  讀取檔案data
	MaxNode=findMaxGain(data); // 找到head樹的根節點 
	createTreeNode(MaxNode,MaxNode.middle.goalString); // 建樹 
	string *goalArray=returnGoalArray(MaxNode.col); // 找最大資訊獲利欄的字串串列 
	cout<<"-------------第一個最大出現拉-----------這裡是分界線------------------------------------------"<<endl; 
	if(MaxNode.left.nextNode!=""){   // 為了將overcast從製作小表時排除，已存yes 
		goalArray[1]="";
	}
	if(MaxNode.middle.nextNode!=""){
		goalArray[2]="";
	}
	if(MaxNode.right.nextNode!=""){
		goalArray[3]="";
	}
	GO(goalArray,MaxNode.col);  // 輸入最大資訊獲利欄的字串串列以建造樹 
	inOrder(head);  // 中序走訪 
	return 0;
}
