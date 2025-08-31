#include <iostream>
#include <cstddef>
#include <stdexcept>
//template <int size,std::size_t capacity>
class Stack{
    //data member abstraction
    private:
        int capacity;
        int size;
        int* array;
    //constructor    
    public:
        Stack(){
            this->size = 0;
            this->capacity = 1;
            this->array = new int[capacity];
        }
        Stack(int capacity){
            this->capacity = capacity;
            this->array = new int[capacity];
            int size = 0;
        }   
        ~Stack(){
            delete[] array;
        }
    public:
        //getter is_full
        int get_size(){
            return this->size;
        }
        int get_capacity(){
            return this->capacity;
        }
        bool is_full(){
            if(size == capacity){
                return true;
            }
            return false;
        }
        int top(){
            return this->array[size - 1];
        }
        //getter
        bool is_empty(){
            if(size == 0){
                return true;
            }
            return false;
        }
        //setter push
        void push(int data){
            if(size == capacity){
                std::cout << "jumlah element dalam stack telah maksimal" << std::endl;
                throw std::runtime_error("stack telah penuh");
            }
            array[size] = data;
            size++;
        }
        void pop(){
            array[size - 1] = 0;
            size--;
        }
        public:
            //method print
            void print_stack(){
                for(size_t i = 0;i < size;i++){
                    std::cout << array[i] << " "; 
                }
                std::cout << std::endl;
            }

};
int main(){
    Stack stack1(100);
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    std::cout << "isi stack saat ini" << std::endl;
    stack1.print_stack();
    std::cout << "Kapasitas maksimal Stack: " << stack1.get_capacity() << std::endl;
    std::cout << "Size Array: " << stack1.get_size() << std::endl;
    std::cout << "element paling atas: " << stack1.top() << std::endl;
    return 0;
}
