#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <cctype>

using namespace std;

int main(){
    ifstream fin;
    fin.open("Input_TestFile_Exe1.txt");
    string a;
    char deloper='#';                                                          //delimiter for operation
    char delarg=',';                                                            //delimiter for numbers
    int sum=0;
    string output="";
    int flag=0;
    string previous;
    while (!fin.eof()){


        getline(fin,a);                                                             //Edw einai i grammi tu file olokliri
        string praxi= a.substr(0,a.find(deloper));                              //Edw einai to eidos tis praxis
        int n;
        n=a.size();
        string restt= a.substr(a.find(deloper)+1,n+1);                          //Edw einai to rest of the string ,oi arithmoi me kommata
        if(flag==0 && (praxi=="Multiply" || praxi=="Division" || praxi=="multiply" || praxi=="division")){
            sum=1;
        }
        else if(flag==0){
            output+='(';
        }

        if((previous=="Multiply" || previous=="Division") && (praxi=="Subtract" || praxi=="Add")){
            output+='(';
        }

        if((previous=="Subtract" || previous=="Add") && (praxi=="Multiply" || praxi=="Division")){
            output+=')';
        }

        flag=1;
        vector<int> numbers;
        string temp="";

        for(int i=0;i<restt.size();i++){
            if(restt[i]==delarg){
                numbers.push_back(stoi(temp));
                temp="";
            }
            else{
               temp+=restt[i];
            }
        }
        numbers.push_back(stoi(temp));

        if(praxi=="Add"|| praxi=="add"){

            for(int i=0;i<numbers.size();i++){
                sum+=numbers[i];
                output+="+";
                output+= to_string(numbers[i]);
            }

        }
        else if(praxi=="Subtract"|| praxi=="subtract"){
            for(int i=0;i<numbers.size();i++){
                sum-=numbers[i];
                output+="-";
                output+= to_string(numbers[i]);
            }
        }
        else if(praxi=="Multiply"||praxi=="multiply"){
            for(int i=0;i<numbers.size();i++){
                sum*=numbers[i];
                output+="*";
                output+=to_string(numbers[i]);
            }
        }
        else{
            for(int i=0;i<numbers.size();i++){
                sum/=numbers[i];
                output+="/";
                output+=to_string(numbers[i]);
            }
        }
        previous=praxi;


    }
    if(previous=="Add" || previous=="Subtract"){
           output+=')';
    }
    cout<<"The equation is:"<<endl;
    cout<<"Equation:"<<output<<endl;
    cout<<"The result is: "<<sum<<endl;




    return 0;
}