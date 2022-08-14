#include<bits/stdc++.h>

#define T0 "0001"
#define T1 "0010"
#define T2 "0011"
#define T3 "0100"
#define T4 "0101"
#define ZERO "0000"
#define INSTRUCTION_SIZE 1

#define LW "0000"
#define BNEQ "0001"
#define SUBI "0010"
#define BEQ "0011"
#define J "0100"
#define ADDI "0101"
#define SW "0110"
#define OR "0111"
#define ADD "1000"
#define AND "1001"
#define ORI "1010"
#define NOR "1011"
#define ANDI "1100"
#define SUB "1101"
#define SLL "1110"
#define SRL "1111"

using namespace std;

string convert(string line) {
    string instruction="";
    vector<string> v;
    stringstream ss(line);
    string item;
    if(getline(ss, item, ' ')) {
        if (item == "lw") instruction += LW;
        else if (item == "bneq") instruction += BNEQ;
        else if (item == "subi") instruction += SUBI;
        else if (item == "beq") instruction += BEQ;
        else if (item == "j") instruction += J;
        else if (item == "addi") instruction += ADDI;
        else if (item == "sw") instruction += SW;
        else if (item == "or") instruction += OR;
        else if (item == "add") instruction += ADD;
        else if (item == "and") instruction += AND;
        else if (item == "ori") instruction += ORI;
        else if (item == "nor") instruction += NOR;
        else if (item == "andi") instruction += ANDI;
        else if (item == "sub") instruction += SUB;
        else if (item == "sll") instruction += SLL;
        else if (item == "srl") instruction += SRL;
        else return "Error";
    }

    while (getline(ss,item,',')) {
        v.push_back(item);
    }
    
    // R format : sub, or, and, add, nor
    if((instruction == SUB)||(instruction == OR)||(instruction == AND)||(instruction == ADD)||(instruction == NOR)) {
        // rs
        if (v[1] == "$t0") instruction += T0;
        else if (v[1] == "$t1") instruction += T1;
        else if (v[1] == "$t2") instruction += T2;
        else if (v[1] == "$t3") instruction += T3;
        else if (v[1] == "$t4") instruction += T4;
        else if (v[1] == "$zero") instruction += ZERO;       

        // rt
        if (v[2] == "$t0") instruction += T0;
        else if (v[2] == "$t1") instruction += T1;
        else if (v[2] == "$t2") instruction += T2;
        else if (v[2] == "$t3") instruction += T3;
        else if (v[2] == "$t4") instruction += T4;
        else if (v[2] == "$zero") instruction += ZERO;       

        // rd
        if (v[0] == "$t0") instruction += T0;
        else if (v[0] == "$t1") instruction += T1;
        else if (v[0] == "$t2") instruction += T2;
        else if (v[0] == "$t3") instruction += T3;
        else if (v[0] == "$t4") instruction += T4;
        else if (v[0] == "$zero") instruction += ZERO;

        return instruction;
    }

    // S format : sll, srl
    else if((instruction == SLL)||(instruction == SRL)){

        if (v[1] == "$t0") instruction += T0;
        else if (v[1] == "$t1") instruction += T1;
        else if (v[1] == "$t2") instruction += T2;
        else if (v[1] == "$t3") instruction += T3;
        else if (v[1] == "$t4") instruction += T4;
        else if (v[1] == "$zero") instruction += ZERO;       

        if (v[0] == "$t0") instruction += T0;
        else if (v[0] == "$t1") instruction += T1;
        else if (v[0] == "$t2") instruction += T2;
        else if (v[0] == "$t3") instruction += T3;
        else if (v[0] == "$t4") instruction += T4;
        else if (v[0] == "$zero") instruction += ZERO;              

        int const_int=stoi(v[2]);
        string const_str=LW;

        for(int j=0; const_int>0; j++) {    
            const_str[const_str.size()-j-1]=(const_int%2)?'1':'0';
            const_int= const_int/2;  
        }    

        instruction += const_str;

        return instruction;
    }
    
    // I format constant : ori, addi, andi, subi
    else if((instruction == ORI)||(instruction == ADDI)||(instruction == ANDI)||(instruction == SUBI)){
        // rs
        if (v[1] == "$t0") instruction += T0;
        else if (v[1] == "$t1") instruction += T1;
        else if (v[1] == "$t2") instruction += T2;
        else if (v[1] == "$t3") instruction += T3;
        else if (v[1] == "$t4") instruction += T4;
        else if (v[1] == "$zero") instruction += ZERO;       

        // rd
        if (v[0] == "$t0") instruction += T0;
        else if (v[0] == "$t1") instruction += T1;
        else if (v[0] == "$t2") instruction += T2;
        else if (v[0] == "$t3") instruction += T3;
        else if (v[0] == "$t4") instruction += T4;
        else if (v[0] == "$zero") instruction += ZERO;              

        int const_int=stoi(v[2]);
        string const_str=LW;

        for(int j=0; const_int>0; j++) {    
            const_str[const_str.size()-j-1]=(const_int%2)?'1':'0';
            const_int= const_int/2;  
        }    

        instruction += const_str;

        return instruction;
    }

    // I format control : beq, bneq
    else if((instruction == BEQ)||(instruction == BNEQ)){

        if (v[1] == "$t0") instruction += T0;
        else if (v[1] == "$t1") instruction += T1;
        else if (v[1] == "$t2") instruction += T2;
        else if (v[1] == "$t3") instruction += T3;
        else if (v[1] == "$t4") instruction += T4;
        else if (v[1] == "$zero") instruction += ZERO;       
        // instruction += " "; //for debugging

        if (v[0] == "$t0") instruction += T0;
        else if (v[0] == "$t1") instruction += T1;
        else if (v[0] == "$t2") instruction += T2;
        else if (v[0] == "$t3") instruction += T3;
        else if (v[0] == "$t4") instruction += T4;
        else if (v[0] == "$zero") instruction += ZERO;              
        // instruction += " "; //for debugging

        int const_int=stoi(v[2])*INSTRUCTION_SIZE; //+1?
        string const_str=LW;

        for(int j=0; const_int>0; j++) {    
            const_str[const_str.size()-j-1]=(const_int%2)?'1':'0';
            const_int= const_int/2;  
        }    

        instruction += const_str;

        return instruction;
    }

    // I format memory : sw, lw
    else if((instruction == SW)||(instruction == LW)){

        string constant;
        stringstream ss2(v[1]);
        if (getline(ss2,item,'(')) {
            constant=item;
        }
        if (getline(ss2,item,')')) {
            if (item == "$t0") instruction+=T0;
            else if (item == "$t1") instruction+=T1;
            else if (item == "$t2") instruction+=T2;
            else if (item == "$t3") instruction+=T3;
            else if (item == "$t4") instruction+=T4;
            else if (item == "$zero") instruction+=ZERO;
        }
        
        if (v[0] == "$t0") instruction+=T0;
        else if (v[0] == "$t1") instruction+=T1;
        else if (v[0] == "$t2") instruction+=T2;
        else if (v[0] == "$t3") instruction+=T3;
        else if (v[0] == "$t4") instruction+=T4;
        else if (v[0] == "$zero") instruction+=ZERO;              
        // instruction+=" "; //for debugging

        int const_int=stoi(constant)*INSTRUCTION_SIZE;
        string const_str="0000";

        for(int j=0; const_int>0; j++) {    
            const_str[const_str.size()-j-1]=(const_int%2)?'1':'0';
            const_int= const_int/2;  
        }    

        instruction+=const_str;

        return instruction;
    }

    // J format : j
    else if((instruction == J)){

        int const_int=stoi(v[0])*INSTRUCTION_SIZE;
        string const_str="00000000";

        for(int j=0; const_int>0; j++) {    
            const_str[const_str.size()-j-1]=(const_int%2)?'1':'0';
            const_int= const_int/2;  
        }    

        instruction += const_str;
   
        // instruction += " "; //for debugging

        instruction += LW;

        return instruction;
    }

    else return instruction;
}

int main () 
{
    string line;
    ifstream fin("assembly.txt");
    ofstream fout("machine.txt");
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