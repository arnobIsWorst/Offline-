#include"RedBlackTree.h"

template <class Key, class Value>
class Map{
  public:
     Map(){
        RedBlackTree<Key,Value> tree;
     }
     
     ~Map(){
        tree.clear();
     }

     void insert(Key key, Value value){
         
     }

     void erase(Key key){
         
     }

     void find(Key key){
        auto foundNode = tree.searchTree(key);
        if (foundNode == nullptr) {
            std::cout <<key<< " not found.\n" << std::endl;
        } else {
            std::cout <<key<< " found \n" << std::endl;
        }
     }

     bool clear(){
        if (tree.getSize() == 0) return false;
        tree.clear();
        return true;
     }

     bool empty(){
        return tree.getSize() == 0 ? true : false;
     }

     int size(){
        return tree.getSize();
     }

     void iterate(){

     }
};



