/**
 * @file stack_linked_list.cpp 
 * 
 * @brief sebuah program untuk mensimulasikan bagaimana stack bekerja 
 * menggunakan implementasi singly linked list
 * 
 * @author Muh Yusuf
 * 
 * @date 29 august
 *
 * @version 2.0
 */
#include <iostream>
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
        //copy constructor
        Stack(const Stack& obj){
            if(obj.head == nullptr){
                return;
            }
            head = new Node(obj.head->data);
            Node* curr = head;
            Node* temp = obj.head->next;
            while(temp != nullptr){
                curr->next = new Node(temp->data);
                curr = curr->next;
                temp = temp->next;
            }
            
        }
        //copy assignment
        Stack& operator=(const Stack& obj){
            if(this == &obj){//copy diri sendiri  
                return *this; //kembalikan object saat ini
            }
            clear();
            if(!obj.head){ //obj == nullptr
                head = nullptr;
                return *this;
            }
            //head adalah object saat ini
            //obj adalah objek lain yang ingin di copy
            head = new Node(obj.head->data); 
            //isi node pertama yang menunjuk head dengan mengambil dari object lain(ingin di copy)
            Node* curr = head;
            //pakai curr sebagai pointer penunjuk 
            Node* temp = obj.head->next;
            //inialisasi temp sebagai pointer untuk mengerakkan obj.head(object lain)
            while(temp != nullptr){
                curr->next = new Node(temp->data); // insert node dari object lain
                curr = curr->next; //jalankan pointer curr
                temp = temp->next; //jalankan pointet temp
            }
            return *this;
        }
        ~Stack()noexcept{
            clear();
        }
    public://abstraksi getter
        int is_size()const noexcept{
            return this->size;
        }
        bool is_empty()const noexcept{
            if(size == 0){
                return true;
            }
            return false;
        }
        type top(Node* head)const noexcept{
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
    void clear() noexcept{
        //pakai konsep deletin at beginning tp head terus di loop       
        while(head != nullptr){
            Node* temp = head; //node menunjuk pointer saat ini
            head = head->next;
            delete temp; //hapus node
        }
        size = 0;
    }
    public: //abstraksi print
        void print_detail(){
            Node* curr = head;
            while (curr != nullptr) {              // cek node yg sedang ditunjuk
                std::cout << curr->data << " ";
                curr = curr->next;                 // maju ke node berikutnya
            }
            std::cout << std::endl;
        }
        
};
int main(){
    Stack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    stack1.push(4);
    std::cout << "setelah push!" << std::endl;
    std::cout << "size stack: " << stack1.is_size() << std::endl;
    std::cout << stack1.is_empty() << std::endl;
    stack1.print_detail();
    stack1.pop();
    std::cout << "Pop Element" << std::endl;
    stack1.print_detail();
    
    Stack<int> stack2 = stack1; //copy constructor
    std::cout << "setelah copy" << std::endl;
    // stack2 = stack1;
    stack2.print_detail();
    //stack1.pop();
    Stack<int>stack3;
    stack3 = stack1;
    std::cout << "copy assignment" << std::endl;
    stack3.print_detail();
    std::cin.get();
    return 0;
} 