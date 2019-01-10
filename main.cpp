#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
void readData(string ** data, int r, int c ){
	ifstream file("data_tree.csv",ifstream::in);
	string line;
	while(file>>line){
		cout << line <<endl;
	}
	/*
	getline(file,line);
	for(int row=0;row<r;r++){
		string line1;
		if(!getline(file,line1))
			break;
		stringstream iss(line);
		if(!iss.good())
			break;
		for(int col=0;col<c;c++){
			string val;
			getline(iss,val,',');
			val>>data[row][col];
		}
	}
	*/
}

int main() {
	int data_row=15;
	int data_col=6;
	string **data; //«Å§i¯x°} 
	data=new string *[data_row];
	for(int i=0;i<data_col;i++)
		data[i]=new string[data_col]; 	
	readData(data,data_row,data_col);
	
	
	return 0;
}
