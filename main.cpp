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
typedef TNode *DecisionTree; // DecisionTree �����O���� 
struct goalData{  // �ؼЪ�� 
	int goalcol; // �ؼ���� 
	string goalString; // �ؼЦr�� 
	int goalYES=0; 
	int goalNO=0;
	double goalE; // �ؼ��i 
};
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

int *countNum(string **data,string goalString,int c){ // ��J��Ưx�}�A�ؼЦr��A���c�� 
//	int countgoal=0;
//	int countYes=0;
//	int countNo=0;
	static int Yes_No[2]={0,0}; //E[0]=Y  E[1]=N 
	cout << goalString << endl;  
	for(int row=1;row<15;row++){
		if(goalString==data[row][c]){
			if(data[row][5]=="Yes"){
				Yes_No[0]+=1;
			}else{
				Yes_No[1]+=1;
			}
		//	countgoal++;
		}
	}
	/*	
	for(int i=0;i<2;i++){
		printf("count==%d\n",E[i]);
	}*/
	//printf("goalString=%s , countgoal=%d , countYes=%d , countNo=%d\n",goalString,countgoal,countYes,countNo);
	//printf(" countgoal=%d , countYes=%d , countNo=%d\n",countgoal,countYes,countNo);
	return Yes_No;//�^�ǯx�}�A�n�Ϋ��� 
}
double Entropy_function1(int YES,int NO){//�@�ӥؼЦr�ꪺ�i 
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
double Entropy_function(int p[],int p_size){
	double entropy;
	for(int i=0;i<p_size;i++){
		entropy+=-(p[i]*log2(p[i]));
	}
	printf("entropy==%f\n",entropy); //�@�ӥؼЦr�ꪺ�i 
	return entropy;
}

//�ثe�u��@�Өíp���i�A�n��h�ӥλ��j�A�b���̰��A���ӬO��}�Ӱ� 
void findColAtt(string **data,int c,int r){ //����줺���Ҧ��ݩʡAr����r�� 
	struct goalData colAtt; // �n�}�C��m�٬O�}�C����?
	colAtt.goalString=data[r][c];
	for(int row=0;row<15;row++){ //�C��C 
		if(data[row][c]==colAtt.goalString){  //�Y�ؼЦr�굥���row��C 
			if(data[row][5]=="Yes"){
				colAtt.goalYES+=1;
			}else{
				colAtt.goalNO+=1;
			}
		}
	}cout << colAtt.goalString <<endl;
	printf("findColAtt  Yes=%d,No=%d\n",colAtt.goalYES,colAtt.goalNO);
	colAtt.goalE=Entropy_function1(colAtt.goalYES,colAtt.goalNO);
}
double Gain(double *E,int c){ // �n����ӥH�W���~���A�G�ݭn�ǤJ�}�C 
	
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
	int data_col=6; //[i][0]�~��L�X�F�� 
	string **data; //�ŧi�x�} 
	struct goalData *goalcolAtt; //�x�s�ؼ���쪺�����U���ݩ� 
	int *Y_N;//�ŧi���СA���x�s countNum ���}�C 
	double goalentropy; //�ŧi�@�ӥؼЦr�ꪺ�i 
	data=new string *[data_row]; //�إߦ�data_row��string���}�C��} 
	for(int i=0;i<data_row;i++){
		data[i]=new string[data_col]; // �C���}�C��}���A�[data_col��string���}�C��} 
	}
	readData(data,data_row,data_col);/*
	for(int row=0;row<data_row;row++){    
		for(int col=0;col<1;col++){
			cout << data[row][0] << endl; 
		}
	}
	Y_N=countNum(data,"Sunny",1);
	for(int i=0;i<2;i++){
		printf("count==%d\n",Y_N[i]);
	}
	goalentropy=Entropy_function(Y_N,2); //�@�ӥؼЦr�ꪺ�i */

	
	
	printf("YES=%s\n","jijij");
	return 0;
}
