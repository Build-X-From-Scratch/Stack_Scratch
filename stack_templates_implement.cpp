#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <utility>
template <typename type,std::size_t capacity>
class Stack{
    private:
        int size;
        type* arr;
    public:
        //default constructor
        Stack(){
            this->size = 0;
            this->arr = new type[capacity];
        }
        //destructor
        ~Stack(){
            delete[] arr;
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
                std::runtime_error("stack terisi penuh");
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
            capacity *= 2;
            //salin array ke temp
            for(size_t i = 0;i < size;i++){
                temp[i] = arr[i];
            }
            //hapus array lama
            delete[] arr;
            //salin isi temporary array dengan capacity * 2 ke arr
            arr = temp;
        }
    public: //abstraksi print
        void print()const{
            for(size_t i = 0;i < size;i++){
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }

};
int main(){
    Stack<int,100>stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    stack1.print();
    std::cout << "pop element" << std::endl;
    stack1.pop();
    stack1.print();
    std::cout << "element paling atas: " << stack1.top() << std::endl;
    return 0;
}