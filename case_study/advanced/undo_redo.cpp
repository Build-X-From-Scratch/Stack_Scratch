#include <iostream>
#include <stdexcept>
#include <sstream>
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
            delete[] temp;
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
        bool is_empty()const noexcept{
            if(size == 0){
                return true;
            }
            return false;
        }
        bool temp_is_empty()const noexcept{
            if(temp_size == 0){
                return true;
            }
            return false;
        } 
        std::string top(){
            return arr[size - 1];
        }
        std::string top_temp(){
            return temp[temp_size - 1];
        }
        private:
            /**
             * @brief fungsi untuk mendapatkan operasi dengan melakukan parser
             * terhadap string dengan memisahkan keyword operasi dengan string utama
             * 
             * @param text adalah string input yang masih mentah dalam kata lain masih
             * tercampur dengan keyword(write,read,undo,dan redo)
             * 
             * @return string yang berisi operasi apa saja pada sebuah string
             */
            std::string get_operation(const std::string& text){
                std::string ans = "";
                std::istringstream iss(text);
                std::string cmd;
                iss >> cmd;
                Mode m = classifyInput(cmd);
                return cmd;
            }
            /**
             * @brief fungsi untuk melakukan parser terhadap string,dengan kata
             * lain memisahkan keyword(write,read,undo,dan redo) dengan string utama
             * 
             * @param text adalah string input yang masih mentah dalam kata lain masih
             * tercampur dengan keyword(write,read,undo,dan redo)
             * 
             * @return sebuah string setelah di parser
             * 
             * @details memakai istringstream untuk memisahkan keyword dengan string utama
             * parameter istringstream(is,str)
             * is: objek input stream 
             *   - std::cin(baca dari console)
             *   - std::ifstream(baca dari file)
             *   - std::istringstream(baca dari stream) ->kita memakai ini
             */
            std::string parser(const std::string& text){
                std::istringstream iss(text);
                std::string cmd;
                iss >> cmd; //ambil kata pertama(keyword)
                std::string args; 
                std::getline(iss,args);
                if(!args.empty() && args.front() == ' '){ //jika ada spasi maka erase
                    args.erase(0,1);
                }
                return args;
            }
    private: //abstraksi common operation on stack
        void push_arr(const std::string& text){
            std::string parser_text = parser(text);
            arr[size] = parser_text;
            size++;
        }
        void push_temp(){
            temp[temp_size] = top();
            temp_size++;
        }
        void pop_arr(){
            arr[size - 1] = "";
            size--;
        }
        void pop_temp(){
            temp[temp_size] = "";
            temp_size--;
        }
    public:
        void Write(const std::string& text){
            if(is_full()){
                throw std::runtime_error("Stack telah penuh");
            }
            Mode m = classifyInput(text);
            if(m == write){
                push_arr(text);
            }else{
                std::string operasi = get_operation(text);
                std::cout << "Error: " << operasi << " not available"  << std::endl;
            }
        }
        /**
         * @brief undo adalah salah satu operasi pada text editor,adapun tugas nya adalah
         * membatalkan perubahan yang user lakukan.
         * 
         * @details cara kerja undo:
         * 1.push top pada arr ke temp_stack 
         * 2.pop element top pada arr
         */
        void Undo(const std::string& text){
            Mode m = classifyInput(top());
            if(m == undo){
                if(is_empty()){
                    std::runtime_error("Queue is empty");
                }else{
                    push_temp();
                    pop_arr();
                }
            }else{
                std::string operasi = get_operation(top());   
            }
        }
     void Redo(){
            if(temp_is_empty()){
                throw std::runtime_error("tidak ada perubahan terbaru");
            }else{
                arr[size] = top_temp();
                size++;
                pop_temp();
            }
        }
        void Read(){
            for(size_t i = 0;i < size;i++){
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }
        public:
            std::string input(){
                std::string text;
                std::cin >> text;
                return text;
            }
            void menu(const std::string& text){
                std::string operation =  get_operation(text);
                Mode m = classifyInput(text);
                if(m == write){
                    Write(text);
                }else if(m == read){
                    Read();
                }else if(m == undo){
                    Undo(text);
                }else if(m == redo){
                    Redo();
                }else{
                    std::string operasi = get_operation(top());
                    std::cout << "Error: " << operasi << " not available"  << std::endl;
                }
            }
};
int main(){     
    Stack stack1(1024); //
    stack1.Write("write aku");
    stack1.Write("write dia");
    stack1.Write("write sayang");
    stack1.Write("write kamu");
    stack1.Read(); // aku dia sayang kamu
    stack1.Undo("undo"); // aku dia sayang
    stack1.Read();
    std::cin.get();
    return 0;
}