#include <iostream>
#include <stdexcept>
class Stack{
    private:
        enum Mode{write = 1,read = 2,undo = 3,redo = 4,unknown = 5};
    private:
        int size;
        int temp_size;
        int capacity;
        std::string* arr;
        std::string* temp;
    public:
        Stack(){
            this->temp_size = 0;
            this->size = 0;
            this->capacity = 1;
            this->arr = new std::string[capacity];
            this->temp = new std::string[capacity];
        }
        Stack(int capacity){
            this->temp_size = 0;
            this->size = 0;
            this->capacity = capacity;
            this->arr = new std::string[capacity];
            this->temp = new std::string[capacity];
        }
        ~Stack(){
            delete[] arr;
        }
    public:
        Mode classifyInput(const std::string& text){
            if(text.find("read") != std::string::npos){
                return read;
            }else if(text.find("write") != std::string::npos){
                return write;
            }else if(text.find("undo") != std::string::npos){
                return undo;
            }else if(text.find("redo") != std::string::npos){
                return redo;
            }
            return unknown;
        }  
    public:
        bool is_full()const noexcept{
            if(size == capacity){
                return true;
            }
            return false;
        }
        std::string get_operation(const std::string& text){
            std::string ans = "";
            Mode m = classifyInput(text);
            if(m == read){
                return "read";
            }else if(m == write){
                return "write";
            }else if(m == undo){
                return "undo";
            }else if(m == redo){
                return "redo";
            }
            return "";
        }
        bool is_empty()const noexcept{
            if(size == 0){
                return true;
            }
            return false;
        }
        std::string top(){
            return arr[size];
        }
    private:
        void Write(const std::string& text){
            if(is_full()){
                throw std::runtime_error("Stack telah penuh");
            }
            Mode m = classifyInput(top());
            if(m == read){
                arr[size] = text;
                size++;
            }else{
                std::string operasi = get_operation(text);
                if(!operasi.empty()){
                    std::cout << "Tidak dapat melakukan operasi" << operasi << std::endl;
                }else{
                    std::cout << "Keyword tidak ditemukan" << std::endl;
                }
            }
        }
        void pop(){
            Mode m = classifyInput(top());
            if(m == undo){
                temp[temp_size] = top();
                temp_size++;
                arr[size - 1] = "";
                size--;
            }
        }
    public:
        void menu(){
            
        }
};
int main(){     
    std::cin.get();
    return 0;
}