
#include<bits/stdc++.h>
using namespace std;

enum opcodes {NOR,ORI,SUB,SLL,LW,BEQ,ANDI,SUBI,SW,J,BNEQ,AND,OR,ADDI,SRL,ADD};
enum registers{T0,T1,T2,T3,T4,ZERO=7};

vector<string> tokenizeCommand(string line){
    vector<string> tokens;
    cout<<"input "<<line<<endl;

    string token="";
    for(int i=0;i<line.length();i++){
        if(line[i]!=' ' && line[i]!=',' && line[i]!='(' && line[i]!=')' ){
            token=token+line[i];
            cout<<"now going over "<<line[i]<<endl;
           }
           else{
            if(token.length()!=0){
                    cout<<"got a new token."<<token<<" the delim was "<<line[i]<<endl;
                tokens.push_back(token);
            token="";}
           }
    }tokens.push_back(token);//to push back the last token
    cout<<"returning tokens"<<endl;
    for(int i=0;i<tokens.size();i++){
        cout<<"tokens[i]"<<tokens[i]<<endl;    }
    return tokens;
}
string decimalToBinary(int num,int numOfBits=4){
    cout<<"the num to convert" <<num<<endl; bool negative=false;
    string str="";
    string leadingZeros="";
    if(num<0) {negative=true; cout<<"negative"<<endl; num=-num;}

    while(num){
        (num&1)?str+='1':str+='0';
        num>>=1;
    }
     reverse(str.begin(), str.end()); cout<<str<<endl;


    for(int i=0;i<(numOfBits-str.length());i++){
        leadingZeros+='0';
        cout<<"leading zeros "<<leadingZeros<<endl;
   }
    str=leadingZeros+str;
    if(negative){
    for(int i=0;i<str.length();i++){
        (str[i]=='0')? str[i]='1':str[i]='0';


    }
    for(int j=str.length()-1;j>=0;j--){

        if(str[j]=='1'){str[j]='0';}
       else  if(str[j]=='0'){str[j]='1';break;}
    }

    }
   cout<<"the value " <<str<<endl;

   return str;
}
string addRegister(string reg){

    if(reg=="$t1") return decimalToBinary(T1);
    else if(reg=="$t2")return decimalToBinary(T2);
    else if(reg=="$t3")return decimalToBinary(T3);
    else if(reg=="$t4")return decimalToBinary(T4);
    else if(reg=="$zero")return decimalToBinary(ZERO);
    else if(reg=="$t0")return decimalToBinary(T0);
}


int main(){

    vector<string> tokens;
    string input;
    string command;
    ifstream fin("assembly2.txt");
    ofstream fout("machineKayanika.txt");
    while(getline(fin,input)){
            command="";
            cout<<"got this command "<<input<<endl;

    tokens=tokenizeCommand(input);
    if(tokens[0]=="add") command+=decimalToBinary(ADD);
        else if(tokens[0]=="addi") command+=decimalToBinary(ADDI);
        else if(tokens[0]=="sub") command+=decimalToBinary(SUB);
        else if(tokens[0]=="subi") command+=decimalToBinary(SUBI);
        else if(tokens[0]=="and") command+=decimalToBinary(AND);
        else if(tokens[0]=="andi") command+=decimalToBinary(ANDI);
        else if(tokens[0]=="or") command+=decimalToBinary(OR);
        else if(tokens[0]=="ori") command+=decimalToBinary(ORI);
        else if(tokens[0]=="sll") command+=decimalToBinary(SLL);
        else if(tokens[0]=="srl") command+=decimalToBinary(SRL);
        else if(tokens[0]=="nor") command+=decimalToBinary(NOR);
        else if(tokens[0]=="lw") command+=decimalToBinary(LW);
        else if(tokens[0]=="sw") command+=decimalToBinary(SW);
        else if(tokens[0]=="beq") command+=decimalToBinary(BEQ);
        else if(tokens[0]=="bneq") command+=decimalToBinary(BNEQ);
        else if(tokens[0]=="j") command+=decimalToBinary(J);
        cout<<"token [0]"<<tokens[0]<<endl;


        if(tokens[0]=="add"||tokens[0]=="sub"||tokens[0]=="and"||tokens[0]=="or"||tokens[0]=="nor"){

           command+= addRegister(tokens[2]);
           command+= addRegister(tokens[3]);
           command+= addRegister(tokens[1]);
        }
        else if(tokens[0]=="ori"||tokens[0]=="subi"||tokens[0]=="andi"||tokens[0]=="addi"||tokens[0]=="sll"||tokens[0]=="srl"||tokens[0]=="beq"||tokens[0]=="bneq"){

           command+= addRegister(tokens[2]);
          command+=  addRegister(tokens[1]);
          command+=decimalToBinary(stoi(tokens[3]));
        }


   else if(tokens[0]=="sw"||tokens[0]=="lw"){

           command+= addRegister(tokens[3]);
          command+=  addRegister(tokens[1]);
          command+=decimalToBinary(stoi(tokens[2]));
   }
   else if(tokens[0]=="j"){
       command+=decimalToBinary(stoi(tokens[1]),8);
       command+="0000";


   }
   fout<<command<<endl;

    }


command="";

}
