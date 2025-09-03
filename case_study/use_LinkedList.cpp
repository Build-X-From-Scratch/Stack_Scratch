#include <iostream>
#include <string>
#include <stdexcept>
class LinkedList{
    private:
        struct Node{
            char data;
            Node* next;
            Node(const char& data){
                this->data = data;
                this->next = nullptr;
            }
        };
        Node* head;
    private:
        struct validation_result{
            bool is_valid;
            char expected;
            char found;
            int index_error;
        };
    public:
        int size;
        std::string s;
        //default constructor
        LinkedList(){
            this->size = 0;
            this->s = "";
            this->head = nullptr;
        }
        //constructor
        LinkedList(const std::string& s){
            this->s = s;
            this->size = 0;
            this->head = nullptr;
        }
        ~LinkedList(){
            clear();
        }
    public:
        bool is_empty(){
            if(size == 0){
                return true;
            }
            return false;
        }
        char top()const noexcept{
            return head->data;
        }
        bool is_bracket(char bracket)const noexcept{
            if(bracket == '{' || bracket == '}'){
                return true;
            }
            if(bracket == '[' || bracket == ']'){
                return true;
            }
            if(bracket == '(' || bracket == ')'){
                return true;
            }
            return false;
        }
        bool is_open(char open)const noexcept{
            if(open == '{'){
                return true;
            }
            if(open == '['){
                return true;
            }
            if(open == '('){
                return true;
            }
            return false;
        }   
        bool is_close(char close)const noexcept{
           if(close == '}'){
                return true;
            }
            if(close == ']'){
                return true;
            }
            if(close == ')'){
                return true;
            }
            return false;      
        }
        bool is_matching(char open,char close)const noexcept{
            if(open == '{' && close == '}'){
                return true;
            }
            if(open == '[' && close == ']'){
                return true;
            }
            if(open == '(' && close == ')'){
                return true;
            }
            return false;   
        }
        char is_expected(char close)const noexcept{
            if(close == ')'){
                return '(';
            }else if(close == ']'){
                return '[';
            }else if(close == '}'){
                return '{';
            }
            return '\0';
        }
    public:
        void push(char data){
            Node* curr = new Node(data);
            curr->next = head;
            head = curr;
            size++;
        }
        void pop(){
            if(is_empty()){
                throw std::runtime_error("Stack is empty");
            }
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
        }
    public: 
        std::string parser(){
            std::string res;
            for(size_t i = 0;i < s.size();i++){
                if(is_bracket(s[i])){
                    res.push_back(s[i]);
                }
            }
            return res;
        }
        validation_result valid_parantheses(){
            std::string res = parser();
            for(int i = 0;i < res.size();i++){
                if(is_open(res[i])){
                    push(res[i]);
                }else if(is_close(res[i])){
                    if(is_empty()){
                        return {false,' ',' ',i};
                    }else if(!is_matching(top(),res[i])){
                        return {false,is_expected(res[i]),top(),i};
                    }
                    pop();
                }
            }
            return {true,'\0','\0',-1};
        }
        void result(){
            validation_result res = valid_parantheses();
            if(!res.is_valid){
                std::cout << "Bracket is valid" << std::endl;
            }else{
                std::cout << "input: " << s << std::endl;
                std::cout << "Error: expected '" << res.expected << "' but found '" << res.found << "', at index " << res.index_error << std::endl; 
            }
        }
    public:
        void clear(){
            while(head != nullptr){
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }
};
int main(){
    LinkedList* stack = new LinkedList("()");
    stack->result();
    delete stack;
    std::cin.get();
    return 0;
}