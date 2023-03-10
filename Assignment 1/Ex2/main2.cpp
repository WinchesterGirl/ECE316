#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {

    ifstream fin;
    fin.open("Input_TestFile_Exe2.txt");        //open file
    string a,number,temp;
    char deloper=',';
    string action;

    vector<string> pinakas;

    string output="";

    while (!fin.eof()){     //while not end of file


        temp="";

        getline(fin,a);   //read line

        if(a.find(deloper) == string::npos){ //not find a match with the deloper until the end of the string
            action= a.substr(0,a.size()+1);             //action
            number= "" ;                                        //number
        }
        else{
            action= a.substr(0,a.find(deloper));             //action
            number= a.substr(action.size()+1,a.size()+1);  //number
        }





        if(action=="Remove" || action =="remove" ){         //if action is remove then remove the number given (only if it is the 1st number)
            if(pinakas.size()==0){
                cout<<"Element "<<number<<" could not be removed because the queue is empty"<<endl;
            }
            else{
                if(pinakas[0]==number){
                    pinakas.erase(pinakas.begin());
                }
                else if (number==""){
                    pinakas.erase(pinakas.begin());
                }

                else{
                    cout<<"Element "<<number<<" could not be removed"<<endl;
                }
            }
        }

        else if(action=="Size" || action=="size"){
            cout<<"The size of the queue is "<<pinakas.size()<<endl;
        }

        else if(action=="Add" || action=="add"){
            for(int i=0;i<number.size();i++){
                if(number[i]==','){
                    pinakas.push_back(temp);                  //fill the vector with the numbers of the line split by ","
                    temp="";
                }
                else{
                    temp+=number[i];
                }
            }
            pinakas.push_back(temp);                  //fill the vector with the numbers of the line split by ","
            //.emplace_back(number);
        }





        else if (action=="Print" || action=="print"){

            if (pinakas.size()==0){

                cout<<"Queue is empty"<<endl;

            }
            else{

                cout<<"The contents of the queue are the following : ";

                for (int i=0;i<pinakas.size();i++){

                    cout<<pinakas[i];

                    if(i!=pinakas.size()-1){
                        cout<<",";
                    }
                }

                cout<<endl;
            }

        }
    }





    return 0;

}
