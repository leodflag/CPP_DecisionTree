#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <math.h>
using namespace std;
struct goalData{  // �ؼЪ�� 
	string *nextNode; // ���ФU�� node 
	string goalString; // �ؼЦr�� 
	int goalYES; 
	int goalNO;
	double goalE; // �ؼ��i 
};
struct Node{
	string NodeData;
	struct goalData left;
	struct goalData middle;
	struct goalData right;
	double NodeE;
}; 
typedef struct Node DecisionTree;
void readData(string **data, int r, int c){   
	ifstream file("data_tree.csv");
	int row;
	int col;
	for(row=0;row<r;row++){
		string line;
		if(!getline(file,line)){  //�q��J�yŪ�J�@���string�ܶq�A����S��0Ū�J�r�šB��^false 
			break;
		}
		stringstream iss(line);  //�N�@�Ӧr�Ŧ�string�ܶqline�����নistringstream���Oiss
		if(!iss.good()){  //�p�G�S���N�^��True 
			break;
		}
		for(col=0;col<c;col++){
			string val;
			getline(iss,val,',');  //�r����� 
			stringstream stringConvertorStringstream(val);  //�N�@�Ӧr�Ŧ��ܶq���ȶǻ���istringstream��H 
			stringConvertorStringstream>>data[row][col];  //��J��x�}
		}
	}
}
double Entropy_function(int YES,int NO){//�@�ӥؼЦr�ꪺ�i 
	double entropy;
	int sum;
	sum=YES+NO;
	double yes;
	double no;
	yes=((double)YES/sum);
	no=((double)NO/sum);
	printf("Y==%f,N==%f,sum=%d\n",yes,no,sum); 
	entropy=-(yes*log2(yes))-(no*log2(no));
	printf("entropy==%f\n",entropy); //�@�ӥؼЦr�ꪺ�i 
	return entropy;
}
struct goalData find_yes_no(string **data,int c,struct goalData str){
	int sum=0;
	str.goalYES=0;
	str.goalNO=0;
	cout<<"str="<<str.goalString<<endl;
	for(int row=0;row<15;row++){  
		cout<<"data[row][c]="<<data[row][c]<<endl;
		if(str.goalString==data[row][c]){  
			cout<<str.goalString<<endl;
			
			if(data[row][5]=="Yes"){
				str.goalYES+=1;
				cout<<"Y=="<<str.goalYES<<endl;
			}else{
				str.goalNO+=1;
				cout<<"N=="<<str.goalNO<<endl;
			}
		}
		cout<<row<<endl;
	}	
	str.goalE=Entropy_function(str.goalYES,str.goalNO);
//	sum=str.goalYES+str.goalNO;
//	cout<<sum<<endl;
	return str;
}
//double Gain(
DecisionTree findgoalS(string **data,string **data2,int c){ // �M�䤣���ƪ��A�s�Jstruct goalData�A�^�Ǧr��}�C 
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
	struct goalData goalD[row_len] ; // �إ� goalData���}�C 
	for(int row=0;row<row_len;row++){
		goalD[row].goalString=data[row][c]; // �x�}���� 
		cout<<"dataCol[k][c]jgkgk="<<data[row][c]<<endl;
	}
	DecisionTree TreeNode;
	int YesAll=0, NoAll=0, All=0;
	for(int r=0;r<row_len;r++){
		if(r==0){
			TreeNode.NodeData=goalD[0].goalString; 	// �Ĥ@�Ӧr�O��� 
			}else if(r==1){
				TreeNode.left.goalString=goalD[1].goalString;	 // �����Ы��V���r 
				TreeNode.left=find_yes_no(data2,c,TreeNode.left);
				YesAll+=TreeNode.left.goalYES;
				NoAll+=TreeNode.left.goalNO;
				printf("YESALL=%d\n",YesAll);
			}else if(r==2){
				TreeNode.middle.goalString=goalD[2].goalString;	 // �����Ы��V���r  
				TreeNode.middle=find_yes_no(data2,c,TreeNode.middle);
				YesAll+=TreeNode.middle.goalYES;
				NoAll+=TreeNode.middle.goalNO;
				printf("YESALL=%d\n",YesAll);
			}else{
				TreeNode.right.goalString=goalD[3].goalString;	 // �k���Ы��V���r  
				TreeNode.right=find_yes_no(data2,c,TreeNode.right);
				YesAll+=TreeNode.right.goalYES;
				NoAll+=TreeNode.right.goalNO;
				printf("YESALL=%d\n",YesAll);
			}		
	}
	All=YesAll+NoAll;
	printf("ALL=%d\n",All);
	
//	goalDptr=goalD; //�N���Ы��V�}�C���Ĥ@�Ӧ�} 
	return TreeNode; 
}


int main() {
	//---------------Ū���ɮ�data---------------- 
	int data_row=15;
	int data_col=6;  
	string **data; //�ŧi�x�} 
	data=new string *[data_row]; //�إߦ�data_row��string���}�C��} 
	for(int i=0;i<data_row;i++){
		data[i]=new string[data_col]; // �C���}�C��}���A�[data_col��string���}�C��} 
	}
	
	string **data2; //�ŧi�x�} 
	data2=new string *[data_row]; //�إߦ�data_row��string���}�C��} 
	for(int i=0;i<data_row;i++){
		data2[i]=new string[data_col]; // �C���}�C��}���A�[data_col��string���}�C��} 
	}
	readData(data,data_row,data_col);
	readData(data2,data_row,data_col);
	//--------------�p��-----------------

//	cout<<root1.left.goalString<<endl;
//	for(int i=0;i<15;i++){
//		cout<<"gougigkg"<<data[i][1]<<endl;
//	}
//	int IKO,yh;
//	IKO=find_yes_no(data,1,root1.left);
//	yh=find_yes_no(data,1,root1.middle);
//	cout<<IKO<<endl;
	struct goalData *goalStr;
	DecisionTree TreeDataPtr;
	TreeDataPtr=findgoalS(data,data2,4);  // ���� 
	cout<<TreeDataPtr.middle.goalString<<endl; //���Ш��� 
//	for(int i=0;i<15;i++){
//		cout<<"iiii"<<data[i][1]<<endl;
//	}
	
	
//	TreeData=
//	setValue(goalStr);
//	cout<<TreeData.NodeData<<endl;
	return 0;
}
