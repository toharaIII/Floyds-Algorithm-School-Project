#ifndef floyds_h
#define floyds_h
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

void floyd(vector<vector<int>>& wMatrix, vector<vector<int>>& dMatrix, vector<vector<int>>& pMatrix);
void printMatrix(vector<vector<int>> matrix);
void path(int q, int r, vector<vector<int>>& pMatrix);

void floyd(vector<vector<int>>& wMatrix, vector<vector<int>>& dMatrix, vector<vector<int>>& pMatrix){
    unsigned long size=wMatrix.size(); //made unsigned long instead of int get rid of warning on xcode
    copy(wMatrix.begin(), wMatrix.end(), dMatrix.begin()); //copying wMatrix ocontents to dMatrix

    for(int k=0; k<size; k++){
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                if(dMatrix[i][k]+dMatrix[k][j]<dMatrix[i][j]){
                    pMatrix[i][j]=k+1; //converts from 0th to 1th indexing
                    dMatrix[i][j]=dMatrix[i][k]+dMatrix[k][j];
                }
            }
        }
    }
}

void printMatrix(vector<vector<int>> matrix){
    unsigned long size=matrix.size(); //made unsigned long instead of int get rid of warning on xcode
    cout<<setw(5)<<" ";
    for(int col=0; col<size; col++) cout<<setw(4)<<"v"<<col+1; //printing column labels

    cout<<"\n";

    for(int row=0; row<size; row++){
        cout<<setw(5)<<"v"<<row+1; //printing corresponding row label
        for(int col=0; col<size; col++) cout<<setw(5)<<matrix[row][col]; //printing row contents
        cout<<"\n";
    }
}

void path(int q, int r, vector<vector<int>>& pMatrix){
    int qq=q-1;
    int rr=r-1; //above 2 lines counter act the 1th indexing that the p matrix is in
    if(pMatrix[qq][rr]!=0){
        path(q, pMatrix[qq][rr], pMatrix);
        cout<<"v"<<pMatrix[qq][rr]<<" ";
        path(pMatrix[qq][rr], r, pMatrix);
    }
}
#endif
