#define INFINITY 2000 //defined as 2000 by professor
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "floyds.h"
using namespace std;

int main(int argc, const char * argv[]) {
    string fileName;
    cout<<"Enter the file name: "<<endl;
    cin>>fileName;
    
    ifstream inputFile;
    inputFile.open(fileName);
    if(!inputFile.is_open()){
        cerr<<"error opening file"<<endl;
        return {};
    } //above segment opens file and ensures there have not been any problems doing so
    
    int size;
    inputFile>>size;
    int edges;
    inputFile>>edges; //above collects the size and the number of edges from the adjacency list
    
    vector<pair<int,int>> outIn(size, make_pair(0,0)); //vector of pairs for each vertices outdegree and indegree
    vector<vector<int>> wMatrix(size, vector<int>(size, INFINITY)); //w matrix, all elements default to infinite
    
    for(int i=0; i<edges; i++){
        string v1;
        string v2;
        int weight;
        inputFile>>v1>>v2>>weight; //collecting an edge from the adjacency list
        
        int a=stoi(v1.substr(1));
        int b=stoi(v2.substr(1)); //above removes the 'v' and collects the number from the vertices for a given edge
        
        outIn[a-1].first++;
        outIn[b-1].second++; //increasing indegree/outdegree for the 2 given vertices
        wMatrix[a-1][b-1]=weight; //collecting the weight from the adjency list
    } //above loop populates degree vector and w matrix as determined by the adjacency list
    
    cout<<"corresponding outdegrees and indegrees:"<<endl;
    cout<<"out: ";
    for(int i=0; i<size; i++) cout<<outIn[i].first<<" ";
    cout<<"\n";
    cout<<"in:  ";
    for(int i=0; i<size; i++) cout<<outIn[i].second<<" ";
    cout<<"\n"<<endl; //above prints the outdegree and indegree of each vertex in increasing order
    
    for(int k=0; k<wMatrix.size(); k++) wMatrix[k][k]=0; //setting the 0s on the identity line
    
    cout<<"W Matrix"<<endl;
    printMatrix(wMatrix);
    cout<<"\n";
    
    vector<vector<int>> dMatrix(size, vector<int>(size, INFINITY));
    vector<vector<int>> pMatrix(size, vector<int>(size, 0));
    floyd(wMatrix, dMatrix, pMatrix);
    cout<<"P Matrix"<<endl;
    printMatrix(pMatrix);
    cout<<"\n";
    cout<<"D Matrix"<<endl;
    printMatrix(dMatrix); //above segments create and print all necessary matrices

    cout<<"\n";
    int paths;
    inputFile>>paths;
    for(int i=0; i<paths; i++){
        string v1;
        string v2;
        inputFile>>v1>>v2;

        int a=stoi(v1.substr(1));
        int b=stoi(v2.substr(1));

        if(dMatrix[a-1][b-1]!=2000){
            cout<<"Path from "<<v1<<" to "<<v2<<": "<<v1<<" ";
            path(a, b, pMatrix);
            cout<<v2<<endl;
        }else cout<<"there is no path between "<<v1<<" and "<<v2<<endl;
    } //above loop takes the start and end of a path and determines if there is a path between the two and if so outputs what vertices are stopped at along said path via a recursive path function

    inputFile.close();
    return 0;
}
