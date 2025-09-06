#include <iostream>
#include <string>
#include <stdexcept>
class Stack{
    private://abstraksi dynamic array
        int size;
        int capacity;
        char* arr;
    private:
        std::string s;
    public:
        //default constructor
        Stack()noexcept{
            this->capacity = 1;
            this->size = 0;
            this->s = "";
            this->arr = new char[capacity];
        }
        //constructor
        Stack(int capacity,std::string s){
            this->capacity = capacity;
            this->size = 0;
            this->s = s;
            this->arr = new char[capacity];
        }
        //destructor
        ~Stack(){
            delete[] arr;
        }
    private: //method valid parantheses
        bool is_open(char bracket){
            if(bracket == '{'){
                return true;
            }
            if(bracket == '('){
                return true;
            }
            if(bracket == '['){
                return true;
            }
            return false;
        }
        private:
            struct validation_result{
                bool is_valid;
                char found;
                char expected;
                int index_error;
            };
        bool is_close(char bracket){
            if(bracket == '}'){
                return true;
            }
            if(bracket == ')'){
                return true;
            }
            if(bracket == ']'){
                return true;
            }
            return false;  
        }
        bool is_matching(char open,char close){
            if(open == '{' && close == '}'){
                return true;
            }
            if(open == '(' && close == ')'){
                return true;
            }
            if(open == '[' && close == ']'){
                return true;
            }
            return false;
        }
        bool is_bracket(char a)const noexcept{
            if(a == '{' || a == '}'){
                return true;
            }
            if(a == '(' || a == ')'){
                return true;
            }
            if(a == '[' || a == ']'){
                return true;
            }
            return false;
        }
        std::string parser(){
            std::string res;
            for(int i = 0;i < this->s.size();i++){
                if(is_bracket(s[i])){
                    res.push_back(s[i]);
                }
            }
            return res;
        }
    private://getter stack
        char top()const noexcept{
            return arr[size - 1];
        }
        bool is_empty()const noexcept{
            if(size == 0){
                return true;
            }
            return false;
        }
    private:
        void push(const char& bracket)noexcept{
            arr[size] = bracket;
            size++;
        }
        void pop(){
            if(size == 0){
                throw std::runtime_error("Stack kosong");
            }
            arr[size - 1] = 0;
            size--;
        }
    public: 
        char get_expected(char close)const noexcept{
            if(close == '}'){
                return '{';
            }
            if(close == ')'){
                return '(';
            }
                return ']';
        }
        validation_result valid_parantheses(){
            std::string res = parser();
            for(int i = 0;i < res.size();i++){
                if(is_open(res[i])){
                    //push ke stack
                    arr[size] = res[i];
                    size++;
                }else if(is_close(res[i])){
                    //jika kosong maka tidak ada pasangan
                    if(is_empty()){
                        return {false,' ',get_expected(arr[size - 1]),i};
                    }
                    //jika tidak matching langsung return false
                    if(!is_matching(arr[size - 1],res[i])){
                        return {false,res[i],get_expected(arr[size -1]),i};
                    }
                    //pop jika matching
                    arr[size - 1] = 0;
                    size--;
                }
            }
            return {true,'\0','\0',-1};
        }

        void result(){
            validation_result res = valid_parantheses();
            if(res.is_valid){
                std::cout << "Bracket Is Valid " << std::endl;
            }else{
                std::cout << "input: " << s << std::endl;
                std::cout << "Error: expected '" << res.expected << "' but found '" << res.found << "', at index " << res.index_error << std::endl; 
            }

        }        
};  
int main(){
    Stack* stack1 = new Stack(100,"([)]");
    stack1->result();
    // Your code here
    std::cin.get();
    return 0;
}