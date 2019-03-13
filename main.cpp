#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>   //�̷s����!!!!!!!!!!!!!!!!!!2/19 �̷s�̷s��
using namespace std;
struct Data_Str{
	string **Data;
	int D_row;
	int D_col;
};
struct goalData{  // �ؼЪ��
	string nextNode; // ���ФU�� node !=NULL 
	string goalString; // �ؼЦr��
	int *goalrow; // �ؼЩҦb�}�C��} 
	int goalYES;  // �ؼ�Yes�ƶq	 
	int goalNO;	  // �ؼ�No�ƶq 
	double goalE; // �ؼ��i 
};
typedef struct Node{
	int col;  // ��� 
	string NodeData;  // ��� 
	struct goalData left;  // ���ݩ� 
	struct goalData middle; // ���ݩ� 
	struct goalData right;  // �k�ݩ� 
	double NodeE;  // �������ݩʪ� �i 
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
//---------�˴��M����O�_�O�Ū�-----------
int isTreeEmpty() {
	if(head==NULL) return 1;
	else           return 0;
}

//---------��J�M����-----------
void createTreeNode(DecisionTree TreeNode,string goalStr){
	DTree newNode, current ,YES ,NO;
	YES= new NODE; 
	YES->data.NodeData="Yes";
	YES->LeftNode=new NODE;
	YES->MiddleNode=new NODE;
	YES->RightNode=new NODE;
	NO= new NODE; 
	NO->data.NodeData="No";
	NO->LeftNode=new NODE;
	NO->MiddleNode=new NODE;
	NO->RightNode=new NODE;
	int inserted=0; // �O�_�[�J�s���`�I 
	newNode= new NODE; 
	newNode->data=TreeNode; 
	newNode->LeftNode=new NODE;
	newNode->MiddleNode=new NODE;
	newNode->RightNode=new NODE;
	if(TreeNode.left.nextNode=="Yes"){
		newNode->LeftNode=YES;
	}else if(TreeNode.left.nextNode=="No"){
		newNode->LeftNode=NO;
	}else{
		newNode->LeftNode->data.NodeData="";
	}
	if(TreeNode.middle.nextNode=="Yes"){
		newNode->MiddleNode=YES;
	}else if(TreeNode.middle.nextNode=="No"){
		newNode->MiddleNode=NO;
	}else{	
		newNode->MiddleNode->data.NodeData="";
	}
	if(TreeNode.right.nextNode=="Yes"){
		newNode->RightNode=YES;
	}else if(TreeNode.right.nextNode=="No"){
		newNode->RightNode=NO;
	}else{
		newNode->RightNode->data.NodeData="";
	}
	cout<<"newNode->data.NodeData�A"<<newNode->data.NodeData<<endl;
	cout<<"newNode->LeftNode->data.NodeData�A"<<newNode->LeftNode->data.NodeData<<endl;
	cout<<"newNode->MiddleNode->data.NodeData�A"<<newNode->MiddleNode->data.NodeData<<endl;
	cout<<"newNode->RightNode->data.NodeData�A"<<newNode->RightNode->data.NodeData<<endl;
//	cout<<newNode->data.middle.nextNode<<endl;
	if(isTreeEmpty()){  //return 1 =NULL �F 0=�� 
		head=newNode; // �إ߮ڸ`�I 
	}else{
		current=head;
		while(!inserted){
			if(current->LeftNode->data.NodeData==""){
				if(current->data.left.goalString==goalStr){
					current->LeftNode=newNode; // �إ߳s�� 
					inserted=1;
				}else{
					current=current->LeftNode;
				}
			}else if(current->MiddleNode->data.NodeData==""){
				if(current->data.middle.goalString==goalStr){
					current->MiddleNode=newNode;
					inserted=1;
				}else{
					current=current->MiddleNode;
				}
			}else if(current->RightNode->data.NodeData==""){
				if(current->data.right.goalString==goalStr){
					current->RightNode=newNode;
					inserted=1;
				}else{
					current=current->RightNode;
				}			
			}			
		}
	}
	cout<<"head->data.NodeData�A"<<head->data.NodeData<<endl;
	cout<<"head->LeftNode->data.NodeData�A"<<head->LeftNode->data.NodeData<<endl;
	cout<<"head->MiddleNode->data.NodeData�A"<<head->MiddleNode->data.NodeData<<endl;
	cout<<"head->RightNode->data.NodeData�A"<<head->RightNode->data.NodeData<<endl;
}
//----------Ū��----------
void readData(string **data, int r, int c){
	ifstream file("data_tree.csv");
	int row;
	int col;
	for(row=0;row<r;row++){
		string line;
		if(!getline(file,line))  //�q��J�yŪ�J�@���string�ܶq�A����S��0Ū�J�r�šB��^false
			break;
		stringstream iss(line);  //�N�@�Ӧr�Ŧ�string�ܶqline�����নistringstream���Oiss
		if(!iss.good())  //�p�G�S���N�^��True
			break;
		for(col=0;col<c;col++){
			string val;
			getline(iss,val,',');  //�r�����
			stringstream stringConvertorStringstream(val);  //�N�@�Ӧr�Ŧ��ܶq���ȶǻ���istringstream��H
			stringConvertorStringstream>>data[row][col];  //��J��x�}
		}
	}
}
//----------�إ߭�l���----------
string** createBaseData(int data_row,int data_col){
	string **data=NULL; //�ŧi�x�}
	data=new string *[data_row]; //�إߦ�data_row��string���}�C��}
	for(int i=0;i<data_row;i++)
		data[i]=new string[data_col]; // �C���}�C��}���A�[data_col��string���}�C��}
	readData(data,data_row,data_col);
	return data;
}
//---------���o�ؼЪ��檺�r��}�C-----------
string* returnGoalArray(int c){
	int row_len=15,col_len=6;
	string **data=createBaseData(row_len,col_len);
	//----------��M���椺���������ݩ�----------
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
	//---------�N��쪺�ݩʧ@���}�C-----------
	string *goalDArray=new string[4] ; // �إ� goalData���}�C
	for(int row=0;row<row_len;row++){
		goalDArray[row]=data[row][c]; // �x�}����
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
//----------�i�p��----------
double Entropy_function(int YES,int NO){//�@�ӥؼЦr�ꪺ�i
	double entropy;
	int sum;
	sum=YES+NO;
	double yes;
	double no;
	yes=((double)YES/sum);
	no=((double)NO/sum);
//	printf("Y==%f,N==%f,sum=%d\n",yes,no,sum);
	entropy=-(yes*log2(yes))-(no*log2(no));
//	printf("entropy==%f\n",entropy); //�@�ӥؼЦr�ꪺ�i
	return entropy;
}
//---------�C��C�C������Y/NO-----------  
struct goalData find_yes_no(Data_Str data,int c,struct goalData str){
	str.goalYES=0;
	str.goalNO=0;
	int goalrow[10],i=0;
//	cout<<"str="<<str.goalString<<endl;
	for(int row=0;row<data.D_row;row++){
//		cout<<"data[row][c]="<<data[row][c]<<endl;
		if(str.goalString==data.Data[row][c]){
			goalrow[i]=row;
			cout<<"goalrow[i]goalrow[i]="<<i<<"�A"<<goalrow[i]<<endl;
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
	if(str.goalYES==0){ //�p�Gyes�����S�� 
		str.nextNode="No"; //�O�U�@�Ӹ`�I��no 
		str.goalE=0.0;  //�i�]��0 
	}else if(str.goalNO==0){
		str.nextNode="Yes";
		str.goalE=0.0;
	}
	else{
		str.goalE=Entropy_function(str.goalYES,str.goalNO);
	}
	str.goalrow=goalrow;
	return str;
}
Data_Str make_goal_data(string GoalStr,int c){  //�p�� �G�ؼЦr�A�Ҧb���    OKKKKKKKKKKKKKKKKKKKKK
	int data_row=15;
	int data_col=6;
	Data_Str Data; 
	Data.Data=createBaseData(data_row,data_col);
	for(int r=1;r<data_row;r++){ //����Ĥ@��� 
		if(Data.Data[r][c]!=GoalStr){ // �Y������ؼ� 
			for(int j=r+1;j<data_row;j++){  //�ĤG���	
				for(int col=0;col<data_col;col++){  // ���U�Ӿ�C 
					Data.Data[j-1][col]=Data.Data[j][col];  //  ��^�e��C 
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
			cout<<"make_goal_data�A"<<Data.Data[i][j]<<endl;
		}
	}
	return Data;
}
//----------��M�ؼ����Gain��----------
DecisionTree findgoalS(Data_Str data,string *array,int c){ // �M�䤣���ƪ��A�s�Jstruct goalData�A�^�Ǧr��}�C
	//---------�p��椺���P�ݩʪ�Y/N�Ӽ�-----------
	DecisionTree TreeNode;
	int YesAll=0, NoAll=0, All=0, leftN=0, middleN=0, rightN=0, r=0;
	while(r!=4){
		if(r==0){
			TreeNode.NodeData=array[r]; 	// �Ĥ@�Ӧr�O���
		}else if(r==1){
			TreeNode.left.goalString=array[r]; 	 // �����Ы��V���r
			TreeNode.left=find_yes_no(data,c,TreeNode.left);
			leftN=TreeNode.left.goalYES+TreeNode.left.goalNO;
			cout<<"leftN="<<leftN<<endl;
			YesAll+=TreeNode.left.goalYES;
			NoAll+=TreeNode.left.goalNO;
		}else if(r==2){
			TreeNode.middle.goalString=array[r]; 	 // �����Ы��V���r
			TreeNode.middle=find_yes_no(data,c,TreeNode.middle);
			middleN=TreeNode.middle.goalYES+TreeNode.middle.goalNO;
			cout<<"middleN="<<middleN<<endl;
			YesAll+=TreeNode.middle.goalYES;
			NoAll+=TreeNode.middle.goalNO;
		}else if(r==3){
			TreeNode.right.goalString=array[r]; 	 // �k���Ы��V���r
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
	if(leftN==0){
		TreeNode.left.nextNode="NULL";
	}
	if(middleN==0){
		TreeNode.middle.nextNode="NULL";
	}
	if(rightN==0){
		TreeNode.right.nextNode="NULL";
	}
	printf("NOALL=%d\n",NoAll);
	printf("YESALL=%d\n",YesAll);
	//----------�p��ؼ�Gain��----------
	All=YesAll+NoAll;
	cout<<"ALL="<<All<<endl;
	TreeNode.NodeE=Entropy_function(YesAll,NoAll);
	printf("ALL�ATreeNode.NodeE=%f\n",TreeNode.NodeE);
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
//-------------��M�̤jGain��-----------------
DecisionTree findMaxGain(Data_Str data){ 
	DecisionTree goalNode,MaxNode;
	string *goalsArray,*MaxGoalSArray;   
//	Data_Str Data
	int i;
	double MaxGain=0.0,Gain=0.0;
	for(i=1;i<5;i++){  //1~4�� 
		goalsArray=returnGoalArray(i); //���o�C���ݩ� 
		goalNode=findgoalS(data,goalsArray,i); //���Ҧ��ݩʪ���� 
		Gain=goalNode.Gain; //���oGain�� 
		cout<<i<<"�AGain="<<Gain<<endl;
		if(Gain>MaxGain){
			goalNode.col=i;
			MaxGain=Gain;
			MaxNode=goalNode;
			MaxGoalSArray=goalsArray;  // �̤j���ݩʧ���h���p�� 
		}
	}
//	createTreeNode(MaxNode);
	cout<<"MaxGain="<<MaxGain<<endl;
	cout<<"MaxNode="<<MaxNode.NodeData<<endl;
	cout<<"MaxNode.left.goalString="<<MaxNode.left.goalString<<endl;
	cout<<"MaxNode.left.nextNode="<<MaxNode.left.nextNode<<endl;
	cout<<"MaxNode.middle.goalString="<<MaxNode.middle.goalString<<endl;
	cout<<"MaxNode.middle.nextNode="<<MaxNode.middle.nextNode<<endl;
	cout<<"MaxNode.right.goalString="<<MaxNode.right.goalString<<endl;
	cout<<"MaxNode.right.nextNode="<<MaxNode.right.nextNode<<endl;
//	for(int j=0;j<4;j++){
//		string **DATA=make_goal_data(MaxGoalSArray[j],15,6,goalNode.col);
//		findMaxGain(DATA,goalNode.col);
//	}
	return 	MaxNode;
}
void inOrder(DTree ptr){
    if(ptr->data.NodeData!="")   //��if 
        cout<<ptr->data.NodeData<<endl;
    else 
    	return;
    inOrder(ptr->LeftNode);
    inOrder(ptr->MiddleNode);
    inOrder(ptr->RightNode);
}

void GO(string *goalArray,int MAX_Col){
	DecisionTree MaxNode;
	for(int i=1;i<4;i++){
		if(goalArray[i]!=""){
			Data_Str data=make_goal_data(goalArray[i],MAX_Col);  //�ھ�SUNNY�s�@DATA 
			MaxNode=findMaxGain(data); //�bSUNNY����Ƹ̧�̤j    ��۵e�@���M���� 
			if(MaxNode.left.nextNode==""){
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
			createTreeNode(MaxNode,goalArray[i]); //�ؾ� 
						
		}

	}
	
}
int main() {
	//---------------Ū���ɮ�data----------------
	Data_Str data,data2;
	data.D_row=15;
	data.D_col=6;
	DecisionTree MaxNode,MaxNode2;
	data.Data=createBaseData(data.D_row,data.D_col);
	MaxNode=findMaxGain(data);
	cout<<MaxNode.middle.nextNode<<endl;
	cout<<MaxNode.middle.goalString<<endl;
	createTreeNode(MaxNode,MaxNode.middle.goalString); //�ؾ� 
	string *goalArray=returnGoalArray(MaxNode.col); // ��̤j�檺�r���C 
	cout<<"-------------�Ĥ@�ӳ̤j�X�{��-----------�o�̬O���ɽu------------------------------------------"<<endl; 
	if(MaxNode.left.nextNode!=""){   
		goalArray[1]="";
	}
	if(MaxNode.middle.nextNode!=""){
		goalArray[2]="";
	}
	if(MaxNode.right.nextNode!=""){
		goalArray[3]="";
	}
	GO(goalArray,MaxNode.col);  //���\!!!!!!!!!!!!!!!! 
	inOrder(head);
	return 0;
}
