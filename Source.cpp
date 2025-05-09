/*-----------------------------------------------------------------------------------------------
 ASSEMBLY: PROJECT 1
 Implementers: 1- Adham Ali / 900223243
               2- Ebram Raafat / 900214496
               3- Khadeejah Iraky /
 -----------------------------------------------------------------------------------------------
 */
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <bitset>
#include <sstream>
#include <cmath>
using namespace std;

// Section 1: Printers and Initializers
void printer_of_instructions(vector <vector<string> > sequential_instructions);
void removeLastNElements(vector<int>& registers, int n);
void printer_of_register_in_decimal(vector <int> &registers);
void printer_of_register_in_hexa(vector <int> &registers);
void printer_of_register_in_binary(vector <int> &registers);
void printer_of_final_register_in_allSystems(vector <int> &registers);


//Section 2: Reading from Files
vector <vector<string> > read_instructions (string namefile);
vector<string> splitting(string txt);
vector<int> memory_extraction(string namefile);
void update_memory(vector<int> up);


//Section 3: Extra Code to handle any corner cases
string registers_handling(string x);
string getOffset(const string& input);
string getContentInsideBrackets(const string& input);
string Two_s_Complement(string num);
void replace_ra_with_x1(vector<vector<string>>& code);
void replaceWords(vector<vector<string>>& code);
string signExtention(string s , int key);

//Section 4: Bonuses
int binaryToDecimal(const string& binaryString);
string decimalToBinaryString(int decimal);
string hexToBinary(const string hexString);
string decimalToHex(unsigned long long decimalNumber);
void div_i(string rd, string rs, string imm, vector <int> &registers,int &program_counter);
void mult_i(string rd, string rs, string imm, vector <int> &registers,int &program_counter);
void div(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter);
void mult(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter);

//Section 5: Functions
void addi(string rd, string rs, string imm, vector <int> &registers, vector <int> &memory_stack,int &program_counter);
void lw(string rd, string rs, string imm, vector <int> &registers, vector <int> &memory_stack,vector<int> &large_memory,int &program_counter);
void xori(string rd, string rs, string imm, vector <int> &registers, int &program_counter);
void andi(string rd, string rs, string imm, vector <int> &registers,int &program_counter);
void ori(string rd, string rs, string imm, vector <int> &registers, int &program_counter);
void slli(string rd, string rs, int imm, vector<int> &registers, int &program_counter);
void srli(string rd, string rs, int imm, vector<int> &registers, int &program_counter);
void srai(string rd, string rs, int imm, vector<int> &registers, int &program_counter);
void slti(string rd, string rs, int imm, vector<int> &registers, int &program_counter);
void sltiu(string rd, string rs, int imm, vector<int> &registers, int &program_counter);
void lui(string rd,string imm, vector<int> &registers, int &program_counter);
void add(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter);
void sub(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter);
void xor_func(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter);
void and_func(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter);
void or_func(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter);
void sll(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter);
void srl(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter);
void sra(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter);
void slt(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter);
void sltu(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter);
void sw(string rd, string rs, string imm, vector <int> &registers, vector <int> &memory_stack,vector <int> &large_stack,int &program_counter);
void beq(string rs_1, string rs_2, string label,vector <int> &registers, vector <vector<string>> copy_sequential_instructions,vector <vector<string>> &sequential_instructions , int &program_counter, bool &error_handle);
void bne(string rs_1, string rs_2, string label,vector <int> &registers, vector <vector<string>> copy_sequential_instructions,vector <vector<string>> &sequential_instructions , int &program_counter, bool &error_handle);
void bge(string rs_1, string rs_2, string label,vector <int> &registers, vector <vector<string>> copy_sequential_instructions,vector <vector<string>> &sequential_instructions , int &program_counter, bool &error_handle);
void blt(string rs_1, string rs_2, string label,vector <int> &registers, vector <vector<string>> copy_sequential_instructions,vector <vector<string>> &sequential_instructions , int &program_counter, bool &error_handle);
void bltu(string rs_1, string rs_2, string label,vector <int> &registers, vector <vector<string>> copy_sequential_instructions,vector <vector<string>> &sequential_instructions , int &program_counter, bool &error_handle);
void bgeu(string rs_1, string rs_2, string label,vector <int> &registers, vector <vector<string>> copy_sequential_instructions,vector <vector<string>> &sequential_instructions , int &program_counter, bool &error_handle);
void lb(string rd, string rs, string imm, vector <int> &registers, vector <int> &memory_stack,int &program_counter);
void lbu(string rd, string rs, string imm, vector <int> &registers, vector <int> &memory_stack,int &program_counter);
void lhu(string rd, string rs, string imm, vector <int> &registers, vector <int> &memory_stack,int &program_counter);
void lh(string rd, string rs, string imm, vector <int> &registers, vector <int> &memory_stack,int &program_counter);
void sh(string rd, string rs, string imm, vector <int> &registers, vector <int> &memory_stack,int &program_counter);
void sb(string rd, string rs, string imm, vector <int> &registers, vector <int> &memory_stack,int &program_counter);
void jal(string rs, string label,vector <int> &registers, vector <vector<string>> copy_sequential_instructions,vector <vector<string>> &sequential_instructions , int &program_counter, int i);
void jalr(string rd, string rs, string imm,vector <int> &registers, vector <vector<string>> copy_sequential_instructions,vector <vector<string>> &sequential_instructions , int &program_counter);
void auipc(string rd , string imm, vector <int> &registers , int &program_counter);

int main()
{
    int program_counter=0;
    
    vector<int> memory_stack;
    vector<int> registers(32, 0);
    vector<int> large_memory=memory_extraction("Memory.txt");
    int starting_address;
    vector <vector<string> > sequential_instructions = read_instructions("Fibonacci.txt");
    replace_ra_with_x1(sequential_instructions);
    replaceWords(sequential_instructions);
    vector <vector<string>> copy_sequential_instructions = sequential_instructions;
    cout<<"WELCOME TO RISC-V SIMULATOR: "<<endl;
    cout<<"Here are the instructions you wrote:"<<endl;
    cout<<"------------------------------------"<<endl;
    printer_of_instructions(sequential_instructions);
    cout<<"------------------------------------"<<endl;
    cout<<"Can you tell me the starting address"<<endl;
    cin>>starting_address;
    
    for(int i=0;i<sequential_instructions.size();i++)
    {
        for(int j=0;j<sequential_instructions[i].size();j++)
        {
            if(sequential_instructions[i][j]=="addi")
            {
                addi(sequential_instructions[i][j+1],sequential_instructions[i][j+2],sequential_instructions[i][j+3],registers, memory_stack, program_counter);
            }
            else if(sequential_instructions[i][j]=="lw")
            {
                string input = sequential_instructions[i][j+2];
                string immediate = getOffset(input);
                string rs =getContentInsideBrackets(input);
                lw(sequential_instructions[i][j+1],rs,immediate,registers, memory_stack, large_memory, program_counter);
            }
            else if(sequential_instructions[i][j]=="xori")
            {
                xori(sequential_instructions[i][j+1],sequential_instructions[i][j+2],sequential_instructions[i][j+3],registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="andi")
            {
                andi(sequential_instructions[i][j+1],sequential_instructions[i][j+2],sequential_instructions[i][j+3],registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="ori")
            {
                ori(sequential_instructions[i][j+1],sequential_instructions[i][j+2],sequential_instructions[i][j+3],registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="slli")
            {
                slli(sequential_instructions[i][j+1],sequential_instructions[i][j+2],stoi(sequential_instructions[i][j+3]),registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="srli")
            {
                srli(sequential_instructions[i][j+1],sequential_instructions[i][j+2],stoi(sequential_instructions[i][j+3]),registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="srai")
            {
                srai(sequential_instructions[i][j+1],sequential_instructions[i][j+2],stoi(sequential_instructions[i][j+3]),registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="slti")
            {
                slti(sequential_instructions[i][j+1],sequential_instructions[i][j+2],stoi(sequential_instructions[i][j+3]),registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="sltiu")
            {
                sltiu(sequential_instructions[i][j+1],sequential_instructions[i][j+2],stoi(sequential_instructions[i][j+3]),registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="add")
            {
                add(sequential_instructions[i][j+1], sequential_instructions[i][j+2], sequential_instructions[i][j+3], registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="sub")
            {
                sub(sequential_instructions[i][j+1], sequential_instructions[i][j+2], sequential_instructions[i][j+3], registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="xor")
            {
                xor_func(sequential_instructions[i][j+1], sequential_instructions[i][j+2], sequential_instructions[i][j+3], registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="and")
            {
                and_func(sequential_instructions[i][j+1], sequential_instructions[i][j+2], sequential_instructions[i][j+3], registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="or")
            {
                or_func(sequential_instructions[i][j+1], sequential_instructions[i][j+2], sequential_instructions[i][j+3], registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="sll")
            {
                sll(sequential_instructions[i][j+1], sequential_instructions[i][j+2], sequential_instructions[i][j+3], registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="srl")
            {
                srl(sequential_instructions[i][j+1], sequential_instructions[i][j+2], sequential_instructions[i][j+3], registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="sra")
            {
                sra(sequential_instructions[i][j+1], sequential_instructions[i][j+2], sequential_instructions[i][j+3], registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="slt")
            {
                slt(sequential_instructions[i][j+1], sequential_instructions[i][j+2], sequential_instructions[i][j+3], registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="sltu")
            {
                sltu(sequential_instructions[i][j+1], sequential_instructions[i][j+2], sequential_instructions[i][j+3], registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="sw")
            {
                string input = sequential_instructions[i][j+2];
                string immediate = getOffset(input);
                string rs =getContentInsideBrackets(input);
                sw(sequential_instructions[i][j+1],rs,immediate,registers, memory_stack,large_memory, program_counter);
            }
            else if(sequential_instructions[i][j]=="ebreak" || sequential_instructions[i][j]=="EBREAK")
            {
                int preference;
                cout<<"The program is finished"<<endl;
                cout<<endl;
                cout<<"You have 4 options"<<endl;
                cout<<"1: Decimal Representaion"<<endl;
                cout<<"2: Binary Representaion"<<endl;
                cout<<"3: Hexadecimal Representaion"<<endl;
                cout<<"4: All Sysytems Representaion"<<endl;
                cout<<"Please choose from 1-4"<<endl;
                cin>>preference;
                if(preference==1)
                {
                    printer_of_register_in_decimal(registers);
                }
                else if(preference==2)
                {
                    printer_of_register_in_binary(registers);
                }
                else if(preference==3)
                {
                    printer_of_register_in_hexa(registers);
                }
                else if(preference==4)
                {
                    printer_of_final_register_in_allSystems(registers);
                }
                else
                {
                    cout<<"It is not an option"<<endl;
                }
                cout<<endl;
                cout<<"The address you paused at is :"<<starting_address+program_counter<<endl;
                cout<<"THANK YOU, HAVE A GOOD DAY !!"<<endl;
                
                return 0;
            }
            else if(sequential_instructions[i][j]=="ecall" || sequential_instructions[i][j]=="ECALL")
            {
                program_counter+=4;
                int preference;
                cout<<"The program is finished"<<endl;
                cout<<endl;
                cout<<"You have 4 options"<<endl;
                cout<<"1: Decimal Representaion"<<endl;
                cout<<"2: Binary Representaion"<<endl;
                cout<<"3: Hexadecimal Representaion"<<endl;
                cout<<"4: All Sysytems Representaion"<<endl;
                cout<<"Please choose from 1-4"<<endl;
                cin>>preference;
                if(preference==1)
                {
                    printer_of_register_in_decimal(registers);
                }
                else if(preference==2)
                {
                    printer_of_register_in_binary(registers);
                }
                else if(preference==3)
                {
                    printer_of_register_in_hexa(registers);
                }
                else if(preference==4)
                {
                    printer_of_final_register_in_allSystems(registers);
                }
                else
                {
                    cout<<"It is not an option"<<endl;
                }
                cout<<endl;
                cout<<"The address we stopped at is = "<<starting_address+program_counter<<endl;
                cout<<"THANK YOU, HAVE A GOOD DAY !!"<<endl;
                return 0;
            }
            else if(sequential_instructions[i][j]=="fence" || sequential_instructions[i][j]=="FENCE")
            {
                program_counter+=4;
                int preference;
                cout<<"The program is finished"<<endl;
                cout<<endl;
                cout<<"You have 4 options"<<endl;
                cout<<"1: Decimal Representaion"<<endl;
                cout<<"2: Binary Representaion"<<endl;
                cout<<"3: Hexadecimal Representaion"<<endl;
                cout<<"4: All Sysytems Representaion"<<endl;
                cout<<"Please choose from 1-4"<<endl;
                cin>>preference;
                if(preference==1)
                {
                    printer_of_register_in_decimal(registers);
                }
                else if(preference==2)
                {
                    printer_of_register_in_binary(registers);
                }
                else if(preference==3)
                {
                    printer_of_register_in_hexa(registers);
                }
                else if(preference==4)
                {
                    printer_of_final_register_in_allSystems(registers);
                }
                else
                {
                    cout<<"It is not an option"<<endl;
                }
                cout<<endl;
                cout<<"The address we stopped at is = "<<starting_address+program_counter<<endl;
                cout<<"THANK YOU, HAVE A GOOD DAY !!"<<endl;
                return 0;
            }
            else if(sequential_instructions[i][j]=="beq")
            {
                bool error_handle= false;
                beq(sequential_instructions[i][j+1], sequential_instructions[i][j+2],sequential_instructions[i][j+3], registers, copy_sequential_instructions,sequential_instructions, program_counter, error_handle);
                if(error_handle==true)
                {
                    i=0; j=0;
                }
            }
            else if(sequential_instructions[i][j]=="bne")
            {
                bool error_handle= false;
                bne(sequential_instructions[i][j+1], sequential_instructions[i][j+2],sequential_instructions[i][j+3], registers, copy_sequential_instructions,sequential_instructions, program_counter, error_handle);
                if(error_handle==true)
                {
                    i=0; j=0;
                }
    
            }
            else if(sequential_instructions[i][j]=="bge")
            {
                bool error_handle= false;
                bge(sequential_instructions[i][j+1], sequential_instructions[i][j+2],sequential_instructions[i][j+3], registers, copy_sequential_instructions,sequential_instructions, program_counter, error_handle);
                if(error_handle==true)
                {
                    i=0; j=0;
                }
            }
            else if(sequential_instructions[i][j]=="blt")
            {
                bool error_handle= false;
                blt(sequential_instructions[i][j+1], sequential_instructions[i][j+2],sequential_instructions[i][j+3], registers, copy_sequential_instructions,sequential_instructions, program_counter, error_handle);
                if(error_handle==true)
                {
                    i=0; j=0;
                }
            }
            else if(sequential_instructions[i][j]=="bltu")
            {
                bool error_handle= false;
                bltu(sequential_instructions[i][j+1], sequential_instructions[i][j+2],sequential_instructions[i][j+3], registers, copy_sequential_instructions,sequential_instructions, program_counter, error_handle);
                if(error_handle==true)
                {
                    i=0; j=0;
                }
            }
            else if(sequential_instructions[i][j]=="bgeu")
            {
                bool error_handle= false;
                bgeu(sequential_instructions[i][j+1], sequential_instructions[i][j+2],sequential_instructions[i][j+3], registers, copy_sequential_instructions,sequential_instructions, program_counter, error_handle);
                if(error_handle==true)
                {
                    i=0; j=0;
                }
            }
            else if(sequential_instructions[i][j]=="lb")
            {
                string input = sequential_instructions[i][j+2];
                string immediate = getOffset(input);
                string rs =getContentInsideBrackets(input);
                lb(sequential_instructions[i][j+1],rs,immediate,registers, memory_stack, program_counter);
            }
            else if(sequential_instructions[i][j]=="lh")
            {
                string input = sequential_instructions[i][j+2];
                string immediate = getOffset(input);
                string rs =getContentInsideBrackets(input);
                lh(sequential_instructions[i][j+1],rs,immediate,registers, memory_stack, program_counter);
            }
            else if(sequential_instructions[i][j]=="lbu")
            {
                string input = sequential_instructions[i][j+2];
                string immediate = getOffset(input);
                string rs =getContentInsideBrackets(input);
                lbu(sequential_instructions[i][j+1],rs,immediate,registers, memory_stack, program_counter);
            }
            else if(sequential_instructions[i][j]=="lhu")
            {
                string input = sequential_instructions[i][j+2];
                string immediate = getOffset(input);
                string rs =getContentInsideBrackets(input);
                lhu(sequential_instructions[i][j+1],rs,immediate,registers, memory_stack, program_counter);
            }
            else if(sequential_instructions[i][j]=="sb")
            {
                string input = sequential_instructions[i][j+2];
                string immediate = getOffset(input);
                string rs =getContentInsideBrackets(input);
                sb(sequential_instructions[i][j+1],rs,immediate,registers, memory_stack, program_counter);
            }
            else if(sequential_instructions[i][j]=="sh")
            {
                string input = sequential_instructions[i][j+2];
                string immediate = getOffset(input);
                string rs =getContentInsideBrackets(input);
                sh(sequential_instructions[i][j+1],rs,immediate,registers, memory_stack, program_counter);
            }
            else if(sequential_instructions[i][j]=="jal")
            {
                jal(sequential_instructions[i][j+1], sequential_instructions[i][j+2], registers, copy_sequential_instructions,sequential_instructions, program_counter, stoi(sequential_instructions[i][j+3]));
                i=0; j=0;
            }
            else if(sequential_instructions[i][j]=="jalr")
            {
                string input = sequential_instructions[i][j+2];
                string immediate = getOffset(input);
                string rs =getContentInsideBrackets(input);
                jalr(sequential_instructions[i][j+1],rs,immediate,registers, copy_sequential_instructions,sequential_instructions, program_counter);
                i=0; j=0;
            }
            else if(sequential_instructions[i][j]=="mult")
            {
                mult(sequential_instructions[i][j+1], sequential_instructions[i][j+2], sequential_instructions[i][j+3], registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="j")
            {
                jal("x0", sequential_instructions[i][j+1], registers, copy_sequential_instructions,sequential_instructions, program_counter, stoi(sequential_instructions[i][j+2]));
                i=0; j=0;
            }
            else if(sequential_instructions[i][j]=="jr")
            {
                string input = sequential_instructions[i][j+2];
                string immediate = getOffset(input);
                string rs =getContentInsideBrackets(input);
                jalr("x0",rs,"0",registers, copy_sequential_instructions,sequential_instructions, program_counter);
                i=0; j=0;
            }
            else if(sequential_instructions[i][j]=="ret")
            {
                string input = sequential_instructions[i][j+2];
                string immediate = getOffset(input);
                string rs =getContentInsideBrackets(input);
                jalr("x0","x1","0",registers, copy_sequential_instructions,sequential_instructions, program_counter);
                i=0; j=0;
            }
            else if(sequential_instructions[i][j]=="mv")
            {
                addi(sequential_instructions[i][j+1],sequential_instructions[i][j+2],"0",registers, memory_stack, program_counter);
            }
            else if(sequential_instructions[i][j]=="not")
            {
                xori(sequential_instructions[i][j+1],sequential_instructions[i][j+2],"-1",registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="au")
            {
                auipc(sequential_instructions[i][j+1] , sequential_instructions[i][j+2], registers ,program_counter);
            }
            else if(sequential_instructions[i][j]=="div")
            {
                div(sequential_instructions[i][j+1], sequential_instructions[i][j+2], sequential_instructions[i][j+3], registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="divi")
            {
                div_i(sequential_instructions[i][j+1],sequential_instructions[i][j+2],sequential_instructions[i][j+3],registers, program_counter);
            }
            else if(sequential_instructions[i][j]=="multi")
            {
                mult_i(sequential_instructions[i][j+1],sequential_instructions[i][j+2],sequential_instructions[i][j+3],registers, program_counter);
            }
        }
    }
    return 0;
}

//Section 1: Printers and Initializers

void printer_of_instructions(vector <vector<string> > sequential_instructions)
{
    for(int i=0;i<sequential_instructions.size();i++)
    {
        for(int j=0;j<sequential_instructions[i].size();j++)
        {
            cout<<sequential_instructions[i][j]<<' ';
        }
        cout<<endl;
    }
    
}
void printer_of_register_in_decimal(vector <int> &registers)
{
    for(int i=0;i<registers.size();i++)
    {
        cout<<"x"<<i<<": "<<registers[i]<<endl;
    }
}
void printer_of_register_in_hexa(vector <int> &registers)
{
    for(int i=0;i<registers.size();i++)
    {
        cout<<"x"<<i<<": "<<decimalToHex(registers[i])<<endl;
    }
}
void printer_of_register_in_binary(vector <int> &registers)
{
    for(int i=0;i<registers.size();i++)
    {
        cout<<"x"<<i<<": "<<decimalToBinaryString(registers[i]) <<endl;
    }
}
void printer_of_final_register_in_allSystems(vector <int> &registers)
{
    for(int i=0;i<registers.size();i++)
    {
        cout<<"Register: "<<i<<": "<<endl;
        cout<<"The default(decimal) representation: " <<registers[i]<<endl;
        cout<<"The binary representation: "<<decimalToBinaryString(registers[i])<<endl;
        cout<<"The hexadecimal representation "<<decimalToHex(registers[i])<<endl;
        cout<<endl;
    }
    
}


void removeLastNElements(vector<int>& registers, int n) {
    if (n < 0) {
        std::cerr << "Error: Negative number of elements to remove." << std::endl;
        return;
    }

    int currentSize = registers.size();
    if (n > currentSize) {
        std::cerr << "Error: Trying to remove more elements than are present." << std::endl;
        return;
    }

    // Resize the vector to remove the last n elements
    registers.resize(currentSize - n);
}


// Section 2: Getting the data from the file
vector <vector<string> > read_instructions (string namefile)
{
    int counter=0;
    ifstream read;
    read.open(namefile);
    string txt;
    vector <vector<string> > sequential_instructions;
    vector<string> download;
    while(getline(read,txt))
    {
        download=splitting(txt);
        download.push_back(to_string(counter));
        counter++;
        sequential_instructions.push_back(download);
    }
    return sequential_instructions;
}

vector<string> splitting(string txt)
{
    vector<string> concatonate;
    txt+=' ';
    int i=0;
    string plus="";
    while(i<txt.length())
    {
        if(txt[i]==':')
        {
            concatonate.push_back(plus+":");
            break;
        }
        if(txt[i]!=' ')
        {
            plus+=txt[i];
        }
        else
        {
            if(plus[plus.length()-1]==',')
            {
                plus=plus.substr(0,plus.length()-1);
                plus=registers_handling(plus);
                concatonate.push_back(plus);
                plus="";
            }
            else
            {
                plus=registers_handling(plus);
                concatonate.push_back(plus);
                plus="";
            }
        }
        i++;
    }
    return concatonate;
}
vector<int> memory_extraction(string namefile)
{
    ifstream read;
    read.open(namefile);
    string txt;
    vector <string> sequential_instructions;
    vector<int> download;
    while(getline(read,txt))
    {
        sequential_instructions.push_back(txt);
    }
    for(int i=0;i<sequential_instructions.size();i++)
    {
        download.push_back(stoi(sequential_instructions[i]));
    }
    return download;
}
void update_memory(vector<int> up)
{
    ofstream out;
    out.open("Memory.txt");
    for(int i=0;i<up.size();i++)
    {
        out<<up[i]<<endl;
    }
}

//Section 3: Returning the registers number in every instruction
string registers_handling(string x){
    char first_char = x[0];
    char second_char = x[1];
    string res = x;
    if (!isalpha(x[0]) || (x[1]<48 || x[1]>57)){return x;}
    if(x == "zero"){return "x0";}
    if(x == "ra"){return "x1";}
    if(x == "sp"){return "x2";}
    if(x == "gp"){return "x3";}
    if(x == "tp"){return "x4";}
    if (first_char == 't'){
            res = 'x';
        if (int(second_char)-48<3){
            res += to_string(int(second_char)-48+5);
        }
        else{
            res += to_string(int(second_char)-48+25);
        }
    }
    if (x == "s0" || x == "sp"){return "x8";}
    
    if (first_char == 's'){
            res='x';
        if (x == "s1"){
            res += '9';
        }
        else{
            res += to_string(int(second_char)-48+16);
        }
    }
    if (first_char == 'a'){
        res ='x';
        res += to_string(int(second_char)-48+10);
        }
return res;
}

string getOffset(const string& input) {
    size_t pos = input.find('(');
    if (pos != string::npos) {
        return input.substr(0, pos);
    }
    return "";
}

string getContentInsideBrackets(const string& input) {
    size_t startPos = input.find('(');
    size_t endPos = input.find(')');
    if (startPos != string::npos && endPos != string::npos && endPos > startPos) {
        return input.substr(startPos + 1, endPos - startPos - 1);
    }
    return "";
}

std::string Two_s_Complement(std::string num) {
    // Flip the bits
    for (char &c : num) {
        c = (c == '0') ? '1' : '0';
    }

    // Add one to the least significant bit
    bool carry = true;
    for (int i = num.size() - 1; i >= 0 && carry; --i) {
        if (num[i] == '0') {
            num[i] = '1';
            carry = false;
        } else {
            num[i] = '0';
        }
    }

    // No need to add '1' at the beginning because std::bitset gives us a 32-bit representation

    return num;
}

void replace_ra_with_x1(vector<vector<string>> &code) {
    for (auto& line : code) {
        std::replace(line.begin(), line.end(), std::string("ra"), std::string("x1"));
    }
}

void replaceWords(vector<vector<string>> &code) {
    for (auto& line : code) {
        for (auto& word : line) {
            // Check for "ra" within parentheses and replace with "x1"
            size_t startPos = word.find("(ra)");
            if (startPos != string::npos) {
                word.replace(startPos, 4, "(x1)");
            }
            
            // Replace "zero" with "x0"
            if (word == "zero") {
                word = "x0";
            }
        }
    }
}
string signExtention(string s , int key)
{
    int len_s = s.length();
    char sign = s[s.length()-1];
    string z_o_flag = "";
    for (int i = len_s; i < 32; i++){
    if (key == 1){
    if (sign == '1'){
    z_o_flag+='1';
    }
    else {
    z_o_flag+='0';
    }
    }
    else{
    z_o_flag+='0';
    }
    }
    z_o_flag+=s;
    return z_o_flag;

}


//Section 4: Bonuses

string decimalToBinaryString(int decimal) {
    if (decimal >= 0)
    {
        return bitset<32>(decimal).to_string();
    } 
    else
    {
        string binary= bitset<32>(decimal*(-1)).to_string();
        return Two_s_Complement(binary);
    }
}


int binaryToDecimal(const string& binaryString) {
    int decimal = 0;
    bool isNegative = false;

    // Check if the number is negative (two's complement)
    if (binaryString[0] == '1') {
        isNegative = true;
    }

    if (isNegative) {
        bool foundOne = false;
        for (int i = binaryString.size() - 1; i >= 0; i--) {
            char bit = binaryString[i];
            if (!foundOne) {
                // Flip the bits until the first '1' is found
                if (bit == '1') {
                    foundOne = true;  // After the first '1', start flipping the bits
                }
            } else {
                bit = (bit == '1' ? '0' : '1');
            }
            // Calculate the decimal value from the modified binary string
            decimal += (bit - '0') * std::pow(2, binaryString.size() - 1 - i);
        }
        decimal = -decimal; // Negate the result as it's a negative number
    } else {
        // Directly convert positive binary strings to decimal
        for (int i = 0; i < binaryString.size(); i++) {
            decimal = decimal * 2 + (binaryString[i] - '0');
        }
    }

    return decimal;
}
string hexToBinary(const string hexString) {
    string binaryString;
    for (char hexChar : hexString) {
        int value;
        if (hexChar >= '0' && hexChar <= '9') {
            value = hexChar - '0';
        } else if (hexChar >= 'a' && hexChar <= 'f') {
            value = hexChar - 'a' + 10;
        } else if (hexChar >= 'A' && hexChar <= 'F') {
            value = hexChar - 'A' + 10;
        } else {
            // Invalid hexadecimal character
            return "";
        }
        binaryString += std::bitset
        <4>(value).to_string();
    }
    return binaryString;
}
string decimalToHex(unsigned long long decimalNumber) {
    stringstream stream;
    stream << "0x"
           << setfill('0') << std::setw(16)
           << hex << uppercase
           << decimalNumber;
    return stream.str();
}

void div_i(string rd, string rs, string imm, vector <int> &registers,int &program_counter) {
    string rd_number = rd.substr(1); // Corrected substr function usage
    string rs_number = rs.substr(1); // Corrected substr function usage

    int rd_X = registers[stoi(rs_number)];
    int immediate = stoi(imm);
    rd_X /= immediate; // Adding immediate value to rs value

    registers[stoi(rd_number)] = rd_X;
    program_counter+=4;
}

void mult_i(string rd, string rs, string imm, vector <int> &registers,int &program_counter) {
    string rd_number = rd.substr(1); // Corrected substr function usage
    string rs_number = rs.substr(1); // Corrected substr function usage

    int rd_X = registers[stoi(rs_number)];
    int immediate = stoi(imm);
    rd_X *= immediate; // Adding immediate value to rs value

    registers[stoi(rd_number)] = rd_X;
    program_counter+=4;
}

void div(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter)
{
    int rd_number = stoi(rd.substr(1));
    int rs1_number = stoi(rs_1.substr(1));
    int rs2_number = stoi(rs_2.substr(1));
    registers[rd_number]= registers[rs1_number]/registers[rs2_number];
    program_counter+=4;
}

void mult(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter)
{
    int rd_number = stoi(rd.substr(1));
    int rs1_number = stoi(rs_1.substr(1));
    int rs2_number = stoi(rs_2.substr(1));
    registers[rd_number]= registers[rs1_number]*registers[rs2_number];
    program_counter+=4;
}

//Section 5: Functions Implementations
void addi(string rd, string rs, string imm, vector <int> &registers, vector <int> &memory_stack,int &program_counter) {
    string rd_number = rd.substr(1); // Corrected substr function usage
    string rs_number = rs.substr(1); // Corrected substr function usage    
    if(rd!="sp")
    {
        int rd_X = registers[stoi(rs_number)];
        int immediate = stoi(imm);
        rd_X += immediate; // Adding immediate value to rs value

        registers[stoi(rd_number)] = rd_X;
    }
    else {
        int immediate=stoi(imm)/4;
        
        if(immediate<=0)
        {
            for(int i=0;i<(immediate*(-1));i++)
            {
                memory_stack.push_back(0);
            }
        }
        else
        {
            removeLastNElements(memory_stack, immediate);
        }
    }

    program_counter+=4;
}

void lw(string rd, string rs, string imm, vector <int> &registers, vector <int> &memory_stack,vector<int> &large_memory,int &program_counter)
{

    int index= stoi(imm)/4;
        if(rs=="sp")
        {
            string rd_number = rd.substr(1);
            registers[stoi(rd_number)] = memory_stack[index];
        }
        else
        {
            string rd_number = rd.substr(1);
            string rs_number = rs.substr(1);
            registers[stoi(rd_number)] = large_memory[stoi(rs_number)+index];
        }
        program_counter+=4;
}
void xori(string rd, string rs, string imm, vector <int> &registers,int &program_counter) {
    string rd_number = rd.substr(1); // Corrected substr function usage
    string rs_number = rs.substr(1); // Corrected substr function usage

    int rd_X = registers[stoi(rs_number)];
    int immediate = stoi(imm);
    rd_X ^= immediate; // Adding immediate value to rs value

    registers[stoi(rd_number)] = rd_X;
    program_counter+=4;
}

void andi(string rd, string rs, string imm, vector <int> &registers,int &program_counter) {
    string rd_number = rd.substr(1); // Corrected substr function usage
    string rs_number = rs.substr(1); // Corrected substr function usage

    int rd_X = registers[stoi(rs_number)];
    int immediate = stoi(imm);
    rd_X &= immediate; // Adding immediate value to rs value

    registers[stoi(rd_number)] = rd_X;
    program_counter+=4;
}

void ori(string rd, string rs, string imm, vector<int> &registers, int &program_counter) {
    string rd_number = rd.substr(1); // Corrected substr function usage
    string rs_number = rs.substr(1); // Corrected substr function usage

    int rd_X = registers[stoi(rs_number)];
    int immediate = stoi(imm);
    rd_X |= immediate; // Adding immediate value to rs value

    registers[stoi(rd_number)] = rd_X;
    program_counter+=4;
}

void slli(string rd, string rs, int imm, vector<int> &registers, int &program_counter) {
    int rd_number = stoi(rd.substr(1));
    int rs_number = stoi(rs.substr(1));
    registers[rd_number] = registers[rs_number] << imm;
    program_counter+=4;
}

void srli(string rd, string rs, int imm, vector<int> &registers, int &program_counter) {
    int rd_number = stoi(rd.substr(1));
    int rs_number = stoi(rs.substr(1));
    registers[rd_number] = (unsigned int)(registers[rs_number]) >> imm;
    program_counter+=4;
}

void srai(string rd, string rs, int imm, vector<int> &registers, int &program_counter) {
    int rd_number = stoi(rd.substr(1));
    int rs_number = stoi(rs.substr(1));
    // Assuming registers are 32-bit, for sign extension in arithmetic shift
    if (registers[rs_number] & (1 << 31)) {
        registers[rd_number] = (registers[rs_number] >> imm) | ~(~0U >> imm);
    } else {
        registers[rd_number] = registers[rs_number] >> imm;
    }
    program_counter+=4;
}

void slti(string rd, string rs, int imm, vector<int> &registers, int &program_counter) {
    int rd_number = stoi(rd.substr(1));
    int rs_number = stoi(rs.substr(1));
    registers[rd_number] = registers[rs_number] < imm ? 1 : 0;
    program_counter+=4;
}

void sltiu(string rd, string rs, int imm, vector<int> &registers, int &program_counter) {
    int rd_number = stoi(rd.substr(1));
    int rs_number = stoi(rs.substr(1));
    registers[rd_number] = (unsigned int)(registers[rs_number]) < (unsigned int)(imm) ? 1 : 0;
    program_counter+=4;
}

void lui(string rd,string imm, vector<int> &registers, int &program_counter)
{
    int rd_number = stoi(rd.substr(1));
    string updated_bits=bitset<20>(stoi(imm)).to_string();
    string all_bits= updated_bits+"000000000000";
    registers[rd_number]= binaryToDecimal(all_bits);
    program_counter+=4;
}

void add(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter)
{
    int rd_number = stoi(rd.substr(1));
    int rs1_number = stoi(rs_1.substr(1));
    int rs2_number = stoi(rs_2.substr(1));
    registers[rd_number]= registers[rs1_number]+registers[rs2_number];
    program_counter+=4;
}

void sub(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter)
{
    int rd_number = stoi(rd.substr(1));
    int rs1_number = stoi(rs_1.substr(1));
    int rs2_number = stoi(rs_2.substr(1));
    registers[rd_number]= registers[rs1_number]-registers[rs2_number];
    program_counter+=4;
}

void xor_func(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter)
{
    int rd_number = stoi(rd.substr(1));
    int rs1_number = stoi(rs_1.substr(1));
    int rs2_number = stoi(rs_2.substr(1));
    registers[rd_number]= registers[rs1_number]^registers[rs2_number];
    program_counter+=4;
}

void and_func(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter)
{
    int rd_number = stoi(rd.substr(1));
    int rs1_number = stoi(rs_1.substr(1));
    int rs2_number = stoi(rs_2.substr(1));
    registers[rd_number]= registers[rs1_number]&registers[rs2_number];
    program_counter+=4;
}

void or_func(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter)
{
    int rd_number = stoi(rd.substr(1));
    int rs1_number = stoi(rs_1.substr(1));
    int rs2_number = stoi(rs_2.substr(1));
    registers[rd_number]= registers[rs1_number]|registers[rs2_number];
    program_counter+=4;
}

void sll(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter) {
    int rd_number = stoi(rd.substr(1));
    int rs1_number = stoi(rs_1.substr(1));
    int rs2_number = stoi(rs_2.substr(1));
    registers[rd_number] = registers[rs1_number] << registers[rs2_number];
    program_counter+=4;
}

void srl(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter) {
    int rd_number = stoi(rd.substr(1));
    int rs1_number = stoi(rs_1.substr(1));
    int rs2_number = stoi(rs_2.substr(1));
    registers[rd_number] = (unsigned int)(registers[rs1_number]) >> (registers[rs2_number]);
    program_counter+=4;
}

void sra(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter) {
    int rd_number = stoi(rd.substr(1));
    int rs1_number = stoi(rs_1.substr(1));
    int rs2_number = stoi(rs_2.substr(1));
    // Assuming registers are 32-bit, for sign extension in arithmetic shift
    if (registers[rs1_number] & (1 << 31)) {
        registers[rd_number] = (registers[rs1_number] >> registers[rs2_number]) | ~(~0U >> registers[rs2_number]);
    } else {
        registers[rd_number] = registers[rs1_number] >> registers[rs2_number];
    }
    program_counter+=4;
}

void slt(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter) {
    int rd_number = stoi(rd.substr(1));
    int rs1_number = stoi(rs_1.substr(1));
    int rs2_number = stoi(rs_2.substr(1));
    registers[rd_number] = registers[rs1_number] < registers[rs2_number] ? 1 : 0;
    program_counter+=4;
}

void sltu(string rd, string rs_1, string rs_2, vector<int> &registers, int &program_counter) {
    int rd_number = stoi(rd.substr(1));
    int rs1_number = stoi(rs_1.substr(1));
    int rs2_number = stoi(rs_2.substr(1));
    registers[rd_number] = (unsigned int)(registers[rs1_number]) < (unsigned int)(registers[rs2_number]) ? 1 : 0;
    program_counter+=4;
}
void sw(string rd, string rs, string imm, vector <int> &registers, vector <int> &memory_stack, vector <int> &large_memory,int &program_counter)
{

    int index= stoi(imm)/4;
        if(rs=="sp")
        {
            string rd_number = rd.substr(1);
             memory_stack[index] = registers[stoi(rd_number)] ;
        }
        else
        {
            string rd_number = rd.substr(1);
            string rs_number = rs.substr(1);
            large_memory[stoi(rs_number)+index]= registers[stoi(rd_number)];
        }
        program_counter+=4;
}
void beq(string rs_1, string rs_2, string label,vector <int> &registers, vector <vector<string>> copy_sequential_instructions,vector <vector<string>> &sequential_instructions , int &program_counter, bool &error_handle)
{
    int rs1_number = stoi(rs_1.substr(1));
    int rs2_number = stoi(rs_2.substr(1));
    int z;
    vector <vector<string> > holding_newData;
    if(registers[rs1_number]==registers[rs2_number])
    {
        error_handle=true;
        bool startPushing = false;
        
        
        for (int i = 0; i < copy_sequential_instructions.size(); i++)
        {
            if (startPushing)
            {
                holding_newData.push_back(copy_sequential_instructions[i]);
            }
            else
            {
                for (int j = 0; j < copy_sequential_instructions[i].size(); j++)
                {
                    if (copy_sequential_instructions[i][j] == label+":") {
                        startPushing = true;
                        z=i;
                        holding_newData.push_back(copy_sequential_instructions[i]);
                        break;
                    }
                }
            }
        }
        sequential_instructions=holding_newData;
        program_counter=z*4;
    }
    else
    {
        error_handle=false;
        program_counter+=4;
    }

}
void bne(string rs_1, string rs_2, string label,vector <int> &registers, vector <vector<string>> copy_sequential_instructions,vector <vector<string>> &sequential_instructions , int &program_counter, bool &error_handle)
{
    int rs1_number = stoi(rs_1.substr(1));
    int rs2_number = stoi(rs_2.substr(1));
    int z;
    
    vector <vector<string> > holding_newData;
    
    if(registers[rs1_number]!=registers[rs2_number])
    {
        error_handle=true;
        bool startPushing = false;

        
         for (int i = 0; i < copy_sequential_instructions.size(); i++)
         {
             if (startPushing)
             {
                 holding_newData.push_back(copy_sequential_instructions[i]);
             }
             else
             {
                 for (int j = 0; j < copy_sequential_instructions[i].size(); j++)
                 {
                     if (copy_sequential_instructions[i][j] == label+":") {
                         startPushing = true;
                         z=i;
                         holding_newData.push_back(copy_sequential_instructions[i]);
                         break;
                     }
                 }
             }
         }
        sequential_instructions=holding_newData;
        program_counter=z*4;
    }
    else
    {
        error_handle=false;
        program_counter+=4;
    }

}

void bge(string rs_1, string rs_2, string label,vector <int> &registers, vector <vector<string>> copy_sequential_instructions,vector <vector<string>> &sequential_instructions , int &program_counter, bool &error_handle)
{
    int rs1_number = stoi(rs_1.substr(1));
    int rs2_number = stoi(rs_2.substr(1));
    int z;
    vector <vector<string> > holding_newData;
    
    if(registers[rs1_number]>=registers[rs2_number])
    {
        error_handle=true;
        bool startPushing = false;

        
         for (int i = 0; i < copy_sequential_instructions.size(); i++)
         {
             if (startPushing)
             {
                 holding_newData.push_back(copy_sequential_instructions[i]);
             }
             else
             {
                 for (int j = 0; j < copy_sequential_instructions[i].size(); j++)
                 {
                     if (copy_sequential_instructions[i][j] == label+":") {
                         startPushing = true;
                         z=i;
                         holding_newData.push_back(copy_sequential_instructions[i]);
                         break;
                     }
                 }
             }
         }
        sequential_instructions=holding_newData;
        program_counter=z*4;
    }
    else
    {
        error_handle=false;
        program_counter+=4;
    }

}
void blt(string rs_1, string rs_2, string label,vector <int> &registers, vector <vector<string>> copy_sequential_instructions,vector <vector<string>> &sequential_instructions , int &program_counter, bool &error_handle)
{
    int rs1_number = stoi(rs_1.substr(1));
    int rs2_number = stoi(rs_2.substr(1));
    int z;
    vector <vector<string> > holding_newData;
    
    if(registers[rs1_number]<registers[rs2_number])
    {
        bool startPushing = false;
        error_handle=true;

        
         for (int i = 0; i < copy_sequential_instructions.size(); i++)
         {
             if (startPushing)
             {
                 holding_newData.push_back(copy_sequential_instructions[i]);
             }
             else
             {
                 for (int j = 0; j < copy_sequential_instructions[i].size(); j++)
                 {
                     if (copy_sequential_instructions[i][j] == label+":") {
                         startPushing = true;
                         z=i;
                         holding_newData.push_back(copy_sequential_instructions[i]);
                         break;
                     }
                 }
             }
         }
        sequential_instructions=holding_newData;
        program_counter=z*4;
    }
    else
    {
        error_handle=false;
        program_counter+=4;
    }

}

void bltu(string rs_1, string rs_2, string label,vector <int> &registers, vector <vector<string>> copy_sequential_instructions,vector <vector<string>> &sequential_instructions , int &program_counter, bool &error_handle)
{

    int rs1_number = stoi(rs_1.substr(1));
    int rs2_number = stoi(rs_2.substr(1));
    int num, num_1;
    int z;
    if(registers[rs1_number]<0)
    {
       string rep= decimalToBinaryString(registers[rs1_number]);
        rep= "0"+rep;
        num = binaryToDecimal(rep);
    }
    else
    {
        num= registers[rs1_number];
    }
    if(registers[rs2_number]<0)
    {
       string rep= decimalToBinaryString(registers[rs2_number]);
        rep= "0"+rep;
        num_1 = binaryToDecimal(rep);
    }
    else
    {
        num_1= registers[rs2_number];
    }
    
    vector <vector<string> > holding_newData;
    if(num<num_1)
    {
        error_handle=true;
        bool startPushing = false;
         for (int i = 0; i < copy_sequential_instructions.size(); i++)
         {
             if (startPushing)
             {
                 holding_newData.push_back(copy_sequential_instructions[i]);
             }
             else
             {
                 for (int j = 0; j < copy_sequential_instructions[i].size(); j++)
                 {
                     if (copy_sequential_instructions[i][j] == label+":") {
                         startPushing = true;
                         z=i;
                         holding_newData.push_back(copy_sequential_instructions[i]);
                         break;
                     }
                 }
             }
         }
        sequential_instructions=holding_newData;
        
        program_counter=z*4;
    }
    else
    {
        error_handle=false;
        program_counter+=4;
    }
}

void bgeu(string rs_1, string rs_2, string label,vector <int> &registers, vector <vector<string>> copy_sequential_instructions,vector <vector<string>> &sequential_instructions , int &program_counter, bool &error_handle)
{

    int rs1_number = stoi(rs_1.substr(1));
    int rs2_number = stoi(rs_2.substr(1));
    int num, num_1;
    int z;
    if(registers[rs1_number]<0)
    {
       string rep= decimalToBinaryString(registers[rs1_number]);
        rep= "0"+rep;
        num = binaryToDecimal(rep);
    }
    else
    {
        num= registers[rs1_number];
    }
    if(registers[rs2_number]<0)
    {
       string rep= decimalToBinaryString(registers[rs2_number]);
        rep= "0"+rep;
        num_1 = binaryToDecimal(rep);
    }
    else
    {
        num_1= registers[rs2_number];
    }
    
    vector <vector<string> > holding_newData;
    if(num>=num_1)
    {
        error_handle=true;
        bool startPushing = false;
         for (int i = 0; i < copy_sequential_instructions.size(); i++)
         {
             if (startPushing)
             {
                 holding_newData.push_back(copy_sequential_instructions[i]);
             }
             else
             {
                 for (int j = 0; j < copy_sequential_instructions[i].size(); j++)
                 {
                     if (copy_sequential_instructions[i][j] == label+":") {
                         startPushing = true;
                         holding_newData.push_back(copy_sequential_instructions[i]);
                         z=i;
                         break;
                     }
                 }
             }
         }
        sequential_instructions=holding_newData;
        
        program_counter=z*4;
    }
    else
    {
        error_handle=false;
        program_counter+=4;
    }
}
void lb(string rd, string rs, string imm, vector <int> &registers, vector <int> &memory_stack,int &program_counter){
    int index= stoi(imm)/4;
    string content = decimalToBinaryString(memory_stack[index]);
    string byte =  content.substr(24,8);
    registers[stoi(rd.substr(1))] = binaryToDecimal(signExtention(byte,1));
    program_counter++;
}

void lbu(string rd, string rs, string imm, vector <int> &registers, vector <int> &memory_stack,int &program_counter){
    int index= stoi(imm)/4;
    string content = decimalToBinaryString(memory_stack[index]);
    string byte =  content.substr(24,8);
    registers[stoi(rd.substr(1))] = binaryToDecimal(signExtention(byte,0));
    program_counter++;
}

void lhu(string rd, string rs, string imm, vector <int> &registers, vector <int> &memory_stack,int &program_counter){
    int index= stoi(imm)/4;
    string content = decimalToBinaryString(memory_stack[index]);
    string byte =  content.substr(24,8);
    registers[stoi(rd.substr(1))] = binaryToDecimal(signExtention(byte,0));
    program_counter++;
}



void lh(string rd, string rs, string imm, vector <int> &registers, vector <int> &memory_stack,int &program_counter){
    int index= stoi(imm)/4;
    string content = decimalToBinaryString(memory_stack[index]);
    string byte =  content.substr(16,16);
    registers[stoi(rd.substr(1))] = binaryToDecimal(signExtention(byte,1));
    program_counter++;

}

void sh(string rd, string rs, string imm, vector <int> &registers, vector <int> &memory_stack,int &program_counter){
    int index= stoi(imm)/4;
    string content = decimalToBinaryString(registers[stoi(rd.substr(1))]);
    string byte =  content.substr(16,16);
    memory_stack[index] = binaryToDecimal(byte);
    program_counter++;

}


void sb(string rd, string rs, string imm, vector <int> &registers, vector <int> &memory_stack,int &program_counter){
    int index= stoi(imm)/4;
    string content = decimalToBinaryString(registers[stoi(rd.substr(1))]);
    string byte =  content.substr(24,8);
    memory_stack[index] = binaryToDecimal(byte);
    program_counter++;

}

void jal(string rs, string label,vector <int> &registers, vector <vector<string>> copy_sequential_instructions,vector <vector<string>> &sequential_instructions , int &program_counter, int i)
{

    int rs_number = stoi(rs.substr(1));
    int z;

    vector <vector<string> > holding_newData;

    bool startPushing = false;

    for (int m = 0; m < copy_sequential_instructions.size(); m++)
    {
        if (startPushing)
        {
            holding_newData.push_back(copy_sequential_instructions[m]);
        }
        else
        {
            for (int j = 0; j < copy_sequential_instructions[m].size(); j++)
            {
                if (copy_sequential_instructions[m][j] == label+":") {
                    startPushing = true;
                    z=m;
                    holding_newData.push_back(copy_sequential_instructions[m]);
                    break;
                }
            }
        }
    }
    
    sequential_instructions=holding_newData;
    
    int rs_X = (i+1)*4;
    registers[rs_number] = rs_X;
    
    program_counter=z*4;
}

void jalr(string rd, string rs, string imm,vector <int> &registers, vector <vector<string>> copy_sequential_instructions,vector <vector<string>> &sequential_instructions , int &program_counter)
{
    int index_jump_to = (registers[stoi(rs.substr(1))]/4)+(stoi(imm)/4)-1;
    copy_sequential_instructions.erase(copy_sequential_instructions.begin(), copy_sequential_instructions.begin() + index_jump_to);
    sequential_instructions=copy_sequential_instructions;
    program_counter=registers[stoi(rs.substr(1))]-4;
}

void auipc(string rd , string imm, vector <int> &registers , int &program_counter)
{
    registers[stoi(rd.substr(1))] = binaryToDecimal((decimalToBinaryString(stoi(imm))).substr(0,20)+"000000000000");
    program_counter+=4;
}

