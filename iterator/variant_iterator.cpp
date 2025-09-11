#include <iostream>
#include <iterator>
#include <vector>
#include <forward_list>
#include <list>
void _input_iterator(){ // dipakai untuk input
    std::cout << "masukkan 3 angka: ";
    std::istream_iterator<int> input_it(std::cin); //baca dari cin
    std::istream_iterator<int>end; //penanda akhir

    std::vector<int>data;   
    while(input_it != end && data.size() < 3){
        data.push_back(*input_it); //push back deferencing iterator
        ++input_it;
    }
    std::cout << "data yang dibaca" << std::endl;
    for(auto x: data){
        std::cout << x << " ";
    }
}  
void _output_iterator(){ //dipakai untuk menulis data
    std::vector<int>numbers {1,2,3,4,5};
    std::ostream_iterator<int> output_it(std::cout," ");
    for(auto x: numbers){
        *output_it = x;
    }
} 
void _forward_iterator(){ //bisa maju berkali2 namun tidak bisa mundur
    //singly linked list container
    std::forward_list<int> fl = {1,2,3,4,5};
    std::forward_list<int>::iterator it = fl.begin();
    while(it != fl.end()){
        std::cout << *it << std::endl;
    }
    //output 1 2 3 4 5
}
void _bidirectional_iterator(){ //bisa maju bisa mundur
    std::list<int>ls = {1,2,3,4,5};
    std::list<int>::iterator it = ls.begin();
    ++it; //it menunjuk alamat memory 20 skrg
    std::cout << "ini it: " << *it << std::endl;
    --it; //it menunjuk alamat memory 1 sekarang
    std::cout << "ini it: " << *it << std::endl;
}
void _random_acces_iterator(){ //bisa maju mundur dan lompat
    std::vector<int>v = {1,2,3,4,5};
    std::vector<int>::iterator it = v.begin();
    std::cout << *(it + 3); //output adlah 4
}
int main(){
    _bidirectional_iterator();
    return 0;
}