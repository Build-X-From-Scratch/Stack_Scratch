/**
 * @file stack_linked_list.cpp 
 * 
 * @brief sebuah program untuk mensimulasikan bagaimana stack bekerja 
 * menggunakan implementasi singly linked list
 * 
 * @author Muh Yusuf
 * 
 * @date 28 august
 * 
 * @version 1.0
 */
#include <iostream>
#include <utility>
#include <stdexcept>
template <typename type>
class Stack{
    private:
        int size;
        struct Node{
            type data;
            Node* next;
            Node(const type& val) : data(val),next(nullptr){}
        };
        Node* head;
    public://abstraksi constructor
        //constructor
        Stack() : head(nullptr),size(0){}
    public://abstraksi getter
        int is_size()const{
            return this->size;
        }
        bool is_empty()const{
            if(size == 0){
                return true;
            }
            return false;
        }
        type top(Node* head)const{
            return head->data;
        }
    public://abstraksi setter
    /**
     * @brief method push adalah method untuk menambahkan element kedalam tumpukkan
     * pada linked list ada 2 opsi yaitu:
     * insert at end,kelemahan time complexity menjadi O(1)
     * insert at head,keuntungan time complexity menjadi O(1)
     * jadi disini kita akan memakai insert at head
     * 
     * @details Time Complexity O(1),Space Complexity O(1)
     */
    void push(const type& data){
        //buat node baru yaitu curr yg menampung informasi data
        Node* curr = new Node(data);
        //buat curr menunjuk ke pointer head
        curr->next = head;
        head = curr;
        //increment size
        size++;
    }
    /**
     * @brief pop adalah salah satu method untuk menghapus element dari
     * tumpukkan,pada linked list berarti kita melakukan delete at beginning
     * 
     * 
     * @details Time Complexity O(1),Space Complexity O(1)
     */
    void pop(){
        if(is_empty()){
            throw std::runtime_error("stack kosong");
        }
        if(head == nullptr){
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
    }
    public: //abstraksi print
        void print_detail(){
            Node* curr = head;
            while (curr != nullptr) {              // cek node yg sedang ditunjuk
                std::cout << curr->data << " -> ";
                curr = curr->next;                 // maju ke node berikutnya
            }
            std::cout << std::endl;
        }
        
};
int main(){
    Stack<int> stack1;
    Stack<char> stack2;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    std::cout << "setelah push!" << std::endl;
    std::cout << "size stack: " << stack1.is_size() << std::endl;
    std::cout << stack1.is_empty() << std::endl;
    stack1.print_detail();
    stack1.pop();
    std::cout << "Pop Element" << std::endl;
    stack1.print_detail();
    //stack1.pop();
} 