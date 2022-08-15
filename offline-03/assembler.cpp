#include<bits/stdc++.h>
// #include<boost/algorithm/string.hpp>

#define ZERO "0000"
#define T0 "0001"
#define T1 "0010"
#define T2 "0011"
#define T3 "0100"
#define T4 "0101"
#define SP "0110"

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

map<string, int> labelLineNo;
vector< pair<string, int> > branchLabelCalls;
vector< pair<string, int> > jumpLabelCalls;

static inline void ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));
}

static inline void rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), s.end());
}

static inline string trim(string &s) {
    ltrim(s);
    rtrim(s);

    return s;
}

vector<string> stringSplitter(const string& str, const char& delim) {
    stringstream ss(str);
    string item;
    vector<string> elems;
    while (getline(ss, item, delim)) {
        elems.push_back(trim(item));
    }

    return elems;
}

string determineRegister(string regName) {    
    if (regName == "$t0") return T0;
    else if (regName == "$t1") return T1;
    else if (regName == "$t2") return T2;
    else if (regName == "$t3") return T3;
    else if (regName == "$t4") return T4;
    else if (regName == "$zero") return ZERO;

    return "ERROR";
}

string toBinary(int n, int len) {
    string r;
    unsigned u = n;

    while(u!=0) {r=(u%2==0 ?"0":"1")+r; u/=2;}

    if (r.size() < len) {
        while (r.size() != len) {
            r = "0" + r;
        }
    } else if (r.size() > len) {
        r = r.substr(r.size() - len, len);
    }
    
    return r;
}

string convert(string line) {
    static unsigned lineNo = 0;
    string instruction = "";
    string withoutLabel = "";

    if (line.back() == ':') {
        labelLineNo[line.substr(0, line.size() - 1)] = lineNo;
        return "ERROR";
    }

    // first look for labels
    vector<string> labelSplitted = stringSplitter(line, ':');
    if (labelSplitted.size() > 1) {
        // label found
        withoutLabel = labelSplitted[1];

        // add label to map
        labelLineNo[labelSplitted[0]] = lineNo;

    } else {
        // no label found
        withoutLabel = line;
    }

    // split with space, look for operation
    string opcode = stringSplitter(withoutLabel, ' ')[0];
    string withoutComment = stringSplitter(withoutLabel, '/')[0];
    vector<string> commaSplitted = 
        stringSplitter(withoutComment.substr(opcode.size(), withoutComment.size()-opcode.size()), ',');

    if (opcode == "lw") instruction += LW;
    else if (opcode == "bneq") instruction += BNEQ;
    else if (opcode == "subi") instruction += SUBI;
    else if (opcode == "beq") instruction += BEQ;
    else if (opcode == "j") instruction += J;
    else if (opcode == "addi") instruction += ADDI;
    else if (opcode == "sw") instruction += SW;
    else if (opcode == "or") instruction += OR;
    else if (opcode == "add") instruction += ADD;
    else if (opcode == "and") instruction += AND;
    else if (opcode == "ori") instruction += ORI;
    else if (opcode == "nor") instruction += NOR;
    else if (opcode == "andi") instruction += ANDI;
    else if (opcode == "sub") instruction += SUB;
    else if (opcode == "sll") instruction += SLL;
    else if (opcode == "srl") instruction += SRL;
    else return "ERROR";

    // check what type of operation it is
    // R format : sub, or, and, add, nor
    if ((instruction == SUB)||(instruction == OR)||(instruction == AND)||(instruction == ADD)||(instruction == NOR)) {
        instruction += determineRegister(commaSplitted[1]);
        instruction += determineRegister(commaSplitted[2]);
        instruction += determineRegister(commaSplitted[0]);

        lineNo++;
        return instruction;
    }

    // S format : sll, srl
    else if((instruction == SLL)||(instruction == SRL)){
        // rs
        instruction += determineRegister(commaSplitted[1]);     

        // rd
        instruction += determineRegister(commaSplitted[0]);

        // shamt
        instruction += toBinary(stoi(commaSplitted[2]), 4);

        lineNo++;
        return instruction;
    }

    // I format constant : ori, addi, andi, subi
    else if((instruction == ORI)||(instruction == ADDI)||(instruction == ANDI)||(instruction == SUBI)){
        // rs
        instruction += determineRegister(commaSplitted[1]);       

        // rd
        instruction += determineRegister(commaSplitted[0]);             

        // constant
        instruction += toBinary(stoi(commaSplitted[2]), 4);
        
        lineNo++;
        return instruction;
    }

    // I format control : beq, bneq
    else if((instruction == BEQ)||(instruction == BNEQ)){
        instruction += determineRegister(commaSplitted[0]);
        instruction += determineRegister(commaSplitted[1]);

        // offset
        branchLabelCalls.push_back(make_pair(commaSplitted[2], lineNo));
        
        lineNo++;
        return instruction;
    }

    // I format memory : sw, lw
    else if((instruction == SW)||(instruction == LW)){
        vector<string> parenthesisSplitted1 = stringSplitter(commaSplitted[1], '(');
        vector<string> parenthesisSplitted2 = stringSplitter(parenthesisSplitted1[1], ')');
        instruction += determineRegister(parenthesisSplitted2[0]);
        instruction += determineRegister(commaSplitted[0]);
        instruction += toBinary(stoi(parenthesisSplitted1[0]), 4);
        
        lineNo++;
        return instruction;
    }

    // J format : j
    else if((instruction == J)){
        // address
        jumpLabelCalls.push_back(make_pair(commaSplitted[0], lineNo));
        
        lineNo++;
        return instruction;
    }

    cout << "ERROR " << lineNo << " " << line << endl;
    return "ERROR";
}

int main () {
    ifstream fin("assembly.txt");
    vector<string> machineCodes;

    if (fin.is_open()) {
        string line;
        while (getline (fin,line)) {
            string machineCode = convert(line);
            if (machineCode != "ERROR") {
                machineCodes.push_back(machineCode);
            }
        }

        // iterate over both labelCalls
        for (auto a : branchLabelCalls) {
            string label = a.first;
            int lineNo = a.second;
            int offset = labelLineNo[label] - (lineNo + 1);

            // convert to binary
            string binary = toBinary(offset, 4);

            // add to machineCodes
            machineCodes[lineNo] += binary;
        }
        for (auto a : jumpLabelCalls) {
            string label = a.first;
            int lineNo = a.second;
            int offset = labelLineNo[label];

            // convert to binary
            string binary = toBinary(offset, 8);

            // add to machineCodes
            machineCodes[lineNo] += binary + "0000";
        }

        ofstream fout("machine.txt");
        for (string m : machineCodes) {
            fout << m << endl;
        }
        fout.close();

        fin.close();
    }
    else cout << "Unable to open file" << endl;

    return 0;
}