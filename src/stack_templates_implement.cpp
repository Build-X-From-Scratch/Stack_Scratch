/**
 * @file stack_templates_implement adalah sebuah program untuk mengimplementasikan
 * stack menggunakan templates dan array dinamis.templates bertujuan supaya stack
 * dapat bekerja untuk semua tipe data dan array dinamis dipakai supaya stack dapat
 * terbatas dalam static memory
 * 
 * @author yusuf
 * @date august 27
 * 
 * @bug belum mengimplementasikan copy constructor dan copy assignment
 */
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <utility>
template <typename type>
class Stack{
    private:
        std::size_t capacity;
        int size;
        type* arr;
    public:
        //default constructor
        Stack(){
            this->capacity = 1;
            this->size = 0;
            this->arr = new type[capacity];
        }
        //constructor
        Stack(std::size_t capacity){
            this->capacity = capacity;
            this->size = 0;
            this->arr = new type[capacity];
        }
        //destructor
        ~Stack(){
            clear();
        }
        //copy constructor
        Stack(const Stack& obj){
            size = obj.size; //supaya tiap object konsisten size yg dimiliki
            capacity = obj.capacity;
            arr = new type[capacity]; //alokasi ulang arr
            for(size_t i = 0;i < size;i++){
                arr[i] = obj.arr[i];
            }     
        }
        Stack& operator=(const Stack& obj){
            //this disini menunjuk objek saat ini
            if(this != &obj){
                //copy array lama ke array baru
                delete[] arr;
                size = obj.size;  
                   arr = new type[capacity];
                for(size_t i = 0;i < size;i++){
                    arr[i] = obj.arr[i];
                }
            }
            return *this;
        }
        /**
         * example with simple study case
         * let a = 2,b = 3 your task swap to variable
         * simple method use temporary variabel
         * solution
         * temp = a
         * a = b
         * b = temp
         */
        void swap(Stack& others){
            //tukar capacity
            std::size_t tempCapa = capacity;
            capacity = others.size;
            others.size = tempCapa;
            //tukar size
            int tempSize = size;
            size = others.size;
            others.size = tempSize;
            //tukar array
            type* temp = new type[capacity];
            temp = arr;
            arr = others.arr;
            others.arr = temp; 
        }
    public: //abstraksi metod getter
        int get_size()const{
            return this->size;
        }
        bool is_full()const{
            if(size == capacity){
                return true;
            }
                return false;
        }
        type top()const{
            return this->arr[size - 1];
        }
    public: //abstraksi method setter
        /**
         * @brief method untuk menambahkan data ketumpukkan
         * 
         * @param data data bertipe type yang dimasukkan ke stack
         *              diterima sebagai const reference agar:
         *              -tidak terjadi copy berlebihan
         *              - object asli tidak dimodifikasi
         * @details referensi digunakan untuk menunjuk nilai yg ingin di push
         * untuk menghindari copy berlebihan
         * cara kerja
         * misal ada x = 10 dengan memory 0xc00000
         * dengan menggunakan parameter referensi maka
         * kita hanya mengambil nilai dari alamat memory
         * 
         * Time Complexity O(1),Space Complexity O(1)
         */
        void push(const type &data){
            if(size == capacity){
                grow_array();
            }
            arr[size] = data;
            size++;
        }
        /**
         * @brief method untuk pop element,yaitu sebuah operasi
         * untuk menghapus element paling atas pada stack
         * 
         * @details Time Complexity O(1),Space Complexity O(1)
         */
        void pop(){
            arr[size - 1] = 0;
            size--;
            if(size == capacity / 2){
                shrink_array();
            }
        }
        /**
         * @brief emplace adalah operasi stack yang memunkinkan kita
         * membuat objek langsung pada stack tanpa membuat temporary variabel
         * dan menyalin  ke stack
         * 
         * @param Args sebuah templates variadic yang memunkinkan menerima 
         * jumlah argumen dan parameter fungsi dengan jumlah tak terbatas dan
         * berbagai tipe data
         * 
         * @details operasi push biasa nya memakai temporary variabel lalu menyalin
         * ke stack 
         * misal saat memanggil stack1.push(1);
         * yang terjadi adalah membuat variabel temp  = 1; lalu disalin ke stack
         * dengan emplace yang kita lakukan adalah langsung menyimpan 1 ke stack
         * tanpa melakukan salinan menyalin
         */
        template <typename... Args>
        void emplace(Args&&... args){
            if(size == capacity){
                throw std::runtime_error("stack terisi penuh");
             }
            new(&arr[size]) type(std::forward<Args>(args)...);
            size++;    
        }
    public: //abstraksi dynamic array
        /**
         * @brief grow array adalah salah satu method dynamic array
         * yang bertujuan ketika size == capacity kita dapat meningkatkan
         * jumlah kapasitas array menggunakan metode array doubling yaitu
         * menggadakan ukuran array menjadi 2 kali lipat dari ukuran awal
         * 
         * @details 
         * cara kerja:
         * -buat array temporary untuk menyalin array lama
         * -salin isi array lama ke temporary array
         * -hapus array lama
         * -salin isi temporary array ke array lama(array kosong)
         * Time Complexity O(n),Space Complexity O(n) 
         */
        void grow_array(){
            type* temp = new type[capacity * 2];
            capacity = capacity * 2;
            //salin array ke temp
            for(size_t i = 0;i < size;i++){
                temp[i] = arr[i];
            }
            //hapus array lama
            delete[] arr;
            //salin isi temporary array dengan capacity * 2 ke arr
            arr = temp;
        }
        /**
         * @brief adalah method untuk mengecilkan kapasitas sebuah array dinamis
         * 
         * @details time complexity O(n),Space Complexity O(n)
         * karena membutuhkan copy dari array sebelumnya
         */
        void shrink_array(){
            type* temp = new type[capacity];
            //salin array ke temp
            for(size_t i = 0;i < size;i++){
                temp[i] = arr[i];
            }
            //hapus array lama
            delete[] arr;
            //salin temporary array ke array lama(kosong)
            arr = temp;

        }
        /**
         * @brief resize adalah method jika n > capacity maka array dinamis
         * akan di perbesar hingga capacity = n,jika sebalik nya maka array akan
         * diperkecil hinggap capacity = n
         * 
         * @details Time Complexity O(n),Space Complexity O(n)
         */
        void resize(int n){
            type* temp = new type[n];
            for(size_t i = 0;i < n;i++){
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;
        }
    public: //abstraksi print
        void print()const{
            for(size_t i = 0;i < size;i++){
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }
    public: //abstraksi method clear
    /**
     * @brief clear adalah salah satu method untuk membersihkan tumpukkan
     * dengan method clear kita dapat menghapus semua element dalam satu tumpukkan
     * 
     * @details karena harus menghapus satu persatu maka
     * time complexity O(n),Space Complexity O(1)
     */
        void clear(){ 
            for(size_t i = 0;i < size;i++){
                arr[i] = 0;
            }
            size = 0;
        }

};
int main(){
    Stack<int>stack1(100);
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    stack1.print();
    std::cout << "pop element" << std::endl;
    stack1.pop();
    stack1.print();
    std::cout << "element paling atas: " << stack1.top() << std::endl;
    Stack<int>stack2(100);
    stack2 = stack1;
    stack2.print();
    Stack<int>stack5(100);
    stack5.push(10);
    stack5.push(20);
    stack5.push(30);
    std::cout << "stack 5 sebelum swap" << std::endl;
    stack5.print();
    std::cout << "sesusah swapp" << std::endl;
    stack5.swap(stack1);
    stack5.print();
    return 0;
}