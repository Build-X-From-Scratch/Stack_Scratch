#include <iostream>
#include <vector>
#include <list>
/**
 * @brief ITERATOR
 * iterator adalah pointer pintar yang mununjuk element dalam suatu container
 * iterator begin selalu mununjuk element pertama
 * iterator end selalu mununjuk element terakhir
 */

void _iterator(){
    /*
    iterator vector di sebut bidirectional iterator karena dapat bergerak maju dan mundur
    */
    std::vector<int>v = {1,2,3,4,5};
    std::vector<int>::iterator it; //deklarasi iterator
    //akan mencetak element pada array v
    for(it = v.begin();it != v.end();++it){
        std::cout << *it << "  ";
    }
    std::cout << std::endl;
    //akan mencetak alamat memory
    for(it = v.begin();it != v.end();it += 2){
        std::cout << &it << "  ";
    }
    /*
    it selalu  menunjuk alamat memory dari vector v
    *it arti nya melakukan deferencing terhadap alamat memory tersebut
    */
   std::list<int>l= {1,2,3,4,5,6,7};
   std::list<int>::iterator lst;
   std::cout << std::endl;
   /**
    * list hanya dapat bergerak satu arah karena memakai linked list 
    * linked list menyimpan data secara tidak beraturan,semua data tersebar di heap
    * tp masing node punya alamat ke node berikut nya.
    * berbeda dengan array yg berurutan di heap atau di stack
    */  
    for(lst = l.begin();lst != l.end();lst++){
        std::cout << *lst << " ";
    }
}
int main(){
    _iterator();
    //std::cin.get();
    return 0;
}