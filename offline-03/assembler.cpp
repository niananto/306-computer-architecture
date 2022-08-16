#include<bits/stdc++.h>
// #include<boost/algorithm/string.hpp>

#define ZERO "0"
#define T0 "1"
#define T1 "2"
#define T2 "3"
#define T3 "4"
#define T4 "5"
#define SP "6"

#define LW "0"
#define BNEQ "1"
#define SUBI "2"
#define BEQ "3"
#define J "4"
#define ADDI "5"
#define SW "6"
#define OR "7"
#define ADD "8"
#define AND "9"
#define ORI "a"
#define NOR "b"
#define ANDI "c"
#define SUB "d"
#define SLL "e"
#define SRL "f"

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

string toHex(int n, int len) {
    string r = toBinary(n, len);
    string hex = "";
    for (int i = 0; i < r.size(); i += 4) {
        string temp = r.substr(i, 4);
        if (temp == "0000") {
            hex += "0";
        } else if (temp == "0001") {
            hex += "1";
        } else if (temp == "0010") {
            hex += "2";
        } else if (temp == "0011") {
            hex += "3";
        } else if (temp == "0100") {
            hex += "4";
        } else if (temp == "0101") {
            hex += "5";
        } else if (temp == "0110") {
            hex += "6";
        } else if (temp == "0111") {
            hex += "7";
        } else if (temp == "1000") {
            hex += "8";
        } else if (temp == "1001") {
            hex += "9";
        } else if (temp == "1010") {
            hex += "a";
        } else if (temp == "1011") {
            hex += "b";
        } else if (temp == "1100") {
            hex += "c";
        } else if (temp == "1101") {
            hex += "d";
        } else if (temp == "1110") {
            hex += "e";
        } else if (temp == "1111") {
            hex += "f";
        }
    }
    return hex;
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
    else if (opcode == "push") instruction += SW;
    else if (opcode == "pop") instruction += LW;
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
        instruction += toHex(stoi(commaSplitted[2]), 4);

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
        instruction += toHex(stoi(commaSplitted[2]), 4);
        
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
        if (commaSplitted.size() > 1) {
            vector<string> parenthesisSplitted1 = stringSplitter(commaSplitted[1], '(');
            vector<string> parenthesisSplitted2 = stringSplitter(parenthesisSplitted1[1], ')');
            instruction += determineRegister(parenthesisSplitted2[0]);
            instruction += determineRegister(commaSplitted[0]);
            instruction += toHex(stoi(parenthesisSplitted1[0]), 4);
        } else { // push pop
            instruction += SP;
            instruction += determineRegister(commaSplitted[0]);
            instruction += "0";
        }
        
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
            if (line.size() == 0) continue;

            string machineCode = convert(line);
            if (machineCode != "ERROR") {
                machineCodes.push_back(machineCode);
            }

            // cout << line << endl;
        }

        // iterate over both labelCalls
        for (auto a : branchLabelCalls) {
            string label = a.first;
            int lineNo = a.second;
            int offset = labelLineNo[label] - (lineNo + 1);

            // convert to hex
            string hex = toHex(offset, 4);

            // add to machineCodes
            machineCodes[lineNo] += hex;
        }
        for (auto a : jumpLabelCalls) {
            string label = a.first;
            int lineNo = a.second;
            int offset = labelLineNo[label];

            // convert to hex
            string hex = toHex(offset, 8);

            // add to machineCodes
            machineCodes[lineNo] += hex + "0";
        }

        ofstream fout("machine.txt");
        fout << "v2.0 raw" << endl;
        for (string m : machineCodes) {
            fout << m << endl;
        }
        fout.close();

        fin.close();
    }
    else cout << "Unable to open file" << endl;

    return 0;
}