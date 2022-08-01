#include<bits/stdc++.h>

// t0 5 t1 1 t2 2 t3 3 t4 4 zero 0
#define T1 "0001"
#define T2 "0010"
#define T3 "0011"
#define T4 "0100"
#define T0 "0101"
#define ZERO "0000"
#define INSTRUCTION_SIZE 1

using namespace std;

string convert(string line) {
    string instruction="";
    vector<string> v;
    stringstream ss(line);
    string item;
    if(getline(ss, item, ' ')) {
        if (item=="lw") instruction += "0000";
        else if (item=="bneq") instruction += "0001";
        else if (item=="subi") instruction += "0010";
        else if (item=="beq") instruction += "0011";
        else if (item=="j") instruction += "0100";
        else if (item=="addi") instruction += "0101";
        else if (item=="sw") instruction += "0110";
        else if (item=="or") instruction += "0111";
        else if (item=="add") instruction += "1000";
        else if (item=="and") instruction += "1001";
        else if (item=="ori") instruction += "1010";
        else if (item=="nor") instruction += "1011";
        else if (item=="andi") instruction += "1100";
        else if (item=="sub") instruction += "1101";
        else if (item=="sll") instruction += "1110";
        else if (item=="srl") instruction += "1111";
        else return "Error";
    }

    while (getline(ss,item,',')) {
        v.push_back(item);
    }
    
    // R format : sub, or, and, add, nor
    if((instruction=="1101")||(instruction=="0111")||(instruction=="1001")||(instruction=="1000")||(instruction=="1011")) {
        // rs
        if (v[1]=="$t0") instruction += T0;
        else if (v[1]=="$t1") instruction += T1;
        else if (v[1]=="$t2") instruction += T2;
        else if (v[1]=="$t3") instruction += T3;
        else if (v[1]=="$t4") instruction += T4;
        else if (v[1]=="$zero") instruction += ZERO;       

        // rt
        if (v[2]=="$t0") instruction += T0;
        else if (v[2]=="$t1") instruction += T1;
        else if (v[2]=="$t2") instruction += T2;
        else if (v[2]=="$t3") instruction += T3;
        else if (v[2]=="$t4") instruction += T4;
        else if (v[2]=="$zero") instruction += ZERO;       

        // rd
        if (v[0]=="$t0") instruction += T0;
        else if (v[0]=="$t1") instruction += T1;
        else if (v[0]=="$t2") instruction += T2;
        else if (v[0]=="$t3") instruction += T3;
        else if (v[0]=="$t4") instruction += T4;
        else if (v[0]=="$zero") instruction += ZERO;

        return instruction;
    }

    // S format : srl, sll
    else if((instruction=="1110")||(instruction=="1111")){

        if (v[1]=="$t0") instruction += T0;
        else if (v[1]=="$t1") instruction += T1;
        else if (v[1]=="$t2") instruction += T2;
        else if (v[1]=="$t3") instruction += T3;
        else if (v[1]=="$t4") instruction += T4;
        else if (v[1]=="$zero") instruction += ZERO;       

        if (v[0]=="$t0") instruction += T0;
        else if (v[0]=="$t1") instruction += T1;
        else if (v[0]=="$t2") instruction += T2;
        else if (v[0]=="$t3") instruction += T3;
        else if (v[0]=="$t4") instruction += T4;
        else if (v[0]=="$zero") instruction += ZERO;              

        int const_int=stoi(v[2]);
        string const_str="0000";

        for(int j=0; const_int>0; j++) {    
            const_str[const_str.size()-j-1]=(const_int%2)?'1':'0';
            const_int= const_int/2;  
        }    

        instruction += const_str;

        return instruction;
    }
    
    // I format constant : ori, addi, andi, subi
    else if((instruction=="1010")||(instruction=="1100")||(instruction=="0101")||(instruction=="0010")){
        // rs
        if (v[1]=="$t0") instruction += T0;
        else if (v[1]=="$t1") instruction += T1;
        else if (v[1]=="$t2") instruction += T2;
        else if (v[1]=="$t3") instruction += T3;
        else if (v[1]=="$t4") instruction += T4;
        else if (v[1]=="$zero") instruction += ZERO;       

        // rd
        if (v[0]=="$t0") instruction += T0;
        else if (v[0]=="$t1") instruction += T1;
        else if (v[0]=="$t2") instruction += T2;
        else if (v[0]=="$t3") instruction += T3;
        else if (v[0]=="$t4") instruction += T4;
        else if (v[0]=="$zero") instruction += ZERO;              

        int const_int=stoi(v[2]);
        string const_str="0000";

        for(int j=0; const_int>0; j++) {    
            const_str[const_str.size()-j-1]=(const_int%2)?'1':'0';
            const_int= const_int/2;  
        }    

        instruction += const_str;

        return instruction;
    }

    // I format control : beq, bneq
    else if((instruction=="0011")||(instruction=="0001")){

        if (v[1]=="$t0") instruction += T0;
        else if (v[1]=="$t1") instruction += T1;
        else if (v[1]=="$t2") instruction += T2;
        else if (v[1]=="$t3") instruction += T3;
        else if (v[1]=="$t4") instruction += T4;
        else if (v[1]=="$zero") instruction += ZERO;       
        // instruction += " "; //for debugging

        if (v[0]=="$t0") instruction += T0;
        else if (v[0]=="$t1") instruction += T1;
        else if (v[0]=="$t2") instruction += T2;
        else if (v[0]=="$t3") instruction += T3;
        else if (v[0]=="$t4") instruction += T4;
        else if (v[0]=="$zero") instruction += ZERO;              
        // instruction += " "; //for debugging

        int const_int=stoi(v[2])*INSTRUCTION_SIZE; //+1?
        string const_str="0000";

        for(int j=0; const_int>0; j++) {    
            const_str[const_str.size()-j-1]=(const_int%2)?'1':'0';
            const_int= const_int/2;  
        }    

        instruction += const_str;

        return instruction;
    }

    // I format memory : sw, lw
    else if((instruction=="0110")||(instruction=="1010")){

        string constant;
        stringstream ss2(v[1]);
        if (getline(ss2,item,'(')) {
            constant=item;
        }
        if (getline(ss2,item,')')) {
            if (item=="$t0") instruction += T0;
            else if (item=="$t1") instruction += T1;
            else if (item=="$t2") instruction += T2;
            else if (item=="$t3") instruction += T3;
            else if (item=="$t4") instruction += T4;
            else if (item=="$zero") instruction += ZERO;
        }
        
        if (v[0]=="$t0") instruction += T0;
        else if (v[0]=="$t1") instruction += T1;
        else if (v[0]=="$t2") instruction += T2;
        else if (v[0]=="$t3") instruction += T3;
        else if (v[0]=="$t4") instruction += T4;
        else if (v[0]=="$zero") instruction += ZERO;              
        // instruction += " "; //for debugging

        int const_int=stoi(constant)*INSTRUCTION_SIZE;
        string const_str="0000";

        for(int j=0; const_int>0; j++) {    
            const_str[const_str.size()-j-1]=(const_int%2)?'1':'0';
            const_int= const_int/2;  
        }    

        instruction += const_str;

        return instruction;
    }

    // J format : j
    else if((instruction=="1110")){

        int const_int=stoi(v[0])*INSTRUCTION_SIZE;
        string const_str="00000000";

        for(int j=0; const_int>0; j++) {    
            const_str[const_str.size()-j-1]=(const_int%2)?'1':'0';
            const_int= const_int/2;  
        }    

        instruction += const_str;
   
        // instruction += " "; //for debugging

        instruction += "0000";

        return instruction;
    }

    else return instruction;
}

int main () 
{
    string line;
    ifstream fin ("assembly.txt");
    ofstream fout ("machine.txt");
    if (fin.is_open()) {
        while (getline (fin,line)) {
            fout<<convert(line)<<endl;
        }
        fin.close();
    }
    else cout<<"Unable to open file"<<endl; 
    fout.close();
    return 0;
}