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
	string goalString; // �ؼЦr�� 2�ӥH�W 
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
//�ثe�u��@�Өíp���i�A�n��h�ӥλ��j�A�b���̰��A���ӬO��}�Ӱ� 
struct goalData findColAtt(string **data,int c,int r){ //����줺���Ҧ��ݩʡAr����r�� 
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
	}
	cout << colAtt.goalString <<endl;
	printf("findColAtt  Yes=%d,No=%d\n",colAtt.goalYES,colAtt.goalNO);
	colAtt.goalE=Entropy_function(colAtt.goalYES,colAtt.goalNO);
	return colAtt;
}
double Gain(double *E,int c){ // �n����ӥH�W���~���A�G�ݭn�ǤJ�}�C 
}
void findMultgoal(string **data,int data_col){ //�p��h���i 
	int size=4;
	int data_row=15;
	bool reString[data_row]={0};
	struct goalData goalcolAttArray[4];
	struct goalData *goalcolAtt; // �x�s�ؼ���쪺�����U���ݩ� n�� 
	goalcolAtt=goalcolAttArray; // ���Ы��V�ʺA�}�C 
	for(int i=0;i<size;i++){	
		for(int row=0;row<data_row;row++){ // �C�ӳ����L�@�M 
			if(reString[row]==0){ // �p�G�S�g���L 
				//goalcolAtt[i].goalString=data[row][data_col]; //��wcol�A�Orow���ؼ�
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
	string **data; //�ŧi�x�} 
	double goalentropy; //�ŧi�@�ӥؼЦr�ꪺ�i 
	data=new string *[data_row]; //�إߦ�data_row��string���}�C��} 
	for(int i=0;i<data_row;i++){
		data[i]=new string[data_col]; // �C���}�C��}���A�[data_col��string���}�C��} 
	}
	readData(data,data_row,data_col);
	findMultgoal(data,1);
	printf("YES=%s\n","jijij");
	return 0;
}
