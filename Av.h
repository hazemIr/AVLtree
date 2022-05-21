
#include <iostream>
#include "AvElement.h"
//#include "library.h"

template<class Key, class Data>
class AVL {
public:
    Element<Key, Data> *root;
    int size;

    AVL(Element<Key, Data> *root = nullptr, int size = 0) : root(root), size(size) {};

    void recursiveDelete(Element<Key, Data> *tree) {
        if (tree == nullptr) {
            return;
        }
        recursiveDelete(tree->leftSon);
        recursiveDelete(tree->rightSon);
        size--;
        delete tree;
    }

    void recursiveDataDelete(Element<Key, Data>* tree){
        if(tree== nullptr)
            return;
        delete tree->data;
        recursiveDataDelete(tree->rightSon);
        recursiveDataDelete(tree->leftSon);
    };

    ~AVL() {
        if(root)
            recursiveDelete(root);
    }

    ///functions
    //print functions to check its functionality
    void inOrder(Element<Key, Data> *tree) {
        if (tree == nullptr)
            return;
        inOrder(tree->leftSon);
        std::cout << tree->key << " "<<"  BFF is: " <<BFF(tree)<< "  height is: "<<tree->height<<std::endl;
        inOrder(tree->rightSon);
    }
    void preOrder(Element<Key, Data> *tree) {
        if (tree == nullptr)
            return;
        std::cout << tree->key << " ";
        preOrder(tree->leftSon);
        preOrder(tree->rightSon);
    }

    void postOrder(Element<Key, Data> *tree) {
        if (tree == nullptr)
            return;
        postOrder(tree->leftSon);
        postOrder(tree->rightSon);
        std::cout << tree->key << " ";
    }

    int getHeight(Element<Key, Data> *element) {
        if (element == nullptr) {
            return -1;
        }
        return element->height;
    }
///returns the father if the key is not found
    Element<Key, Data>* find(Key key){
        if(this == nullptr){
            return nullptr;
        }
        Element<Key, Data> *current = this->root;
        Element<Key, Data> *parent = nullptr;
        if(this->root == nullptr)
            return parent;

        while(current != nullptr){
            if(current->key == key)
                return current;

            else if(key < current->key)
            {
                parent =current;
                current=current->leftSon;
            }
            else{
                parent =current;
                current=current->rightSon;
            }
        }
        return parent;

    }

    int BFF(Element<Key, Data> *element) {
        if (element == nullptr) {
            return -1;
        }
        //leaf
        if (element->leftSon == nullptr && element->rightSon == nullptr) {
            return 0;
        }
        //has only leftSon
        if (element->rightSon == nullptr) {
            return element->leftSon->height + 1;
        }
        //has only rightSon
        if (element->leftSon == nullptr) {
            return -(element->rightSon->height + 1);
        }
        //BFF
        return element->leftSon->height - element->rightSon->height;
    }

    void updateHeight(Element<Key, Data> *subTree) {
        if (subTree == nullptr) {
            return;
        }
        if (subTree->leftSon == nullptr && subTree->rightSon == nullptr) {
            subTree->height = 0;
            return;
        }
        int left =0, right =0;
        if(subTree->leftSon != nullptr){
            left = getHeight(subTree->leftSon);
        }
        if(subTree->rightSon != nullptr){
            right = getHeight(subTree->rightSon);
        }
        if(right >left){
            subTree->height =right+1;
        }
        else {
            subTree->height = left +1;
        }
    }

    Element<Key,Data>* rotateLL(Element<Key, Data> *tree) {
        /* if (tree == nullptr) {
             return;
         }
         Element<Key, Data> *l = tree->leftSon;
         Element<Key ,Data> *lr;
         if(l->rightSon != nullptr)
             lr =l->rightSon;

         if (root == tree) {
             root = l;
         }
         tree->leftSon = lr;
         if (lr != nullptr) {
             lr->father = tree;
         }
         lr = tree;
         Element<Key ,Data> *lf=l->father;
         lf = tree->father;
         if (lf != nullptr) {
             if (lf->leftSon == tree) {
                 lf->leftSon = l;
             } else {
                 lf->rightSon = l;
             }
         }
         tree->father = l;
         updateHeight(tree);
         updateHeight(tree->father);
         //return tempElement;*/
        if (tree == nullptr) {
            return nullptr;
        }
        Element<Key, Data> *tmp = tree->leftSon;
        if (root == tree) {
            root = tmp;
        }
        tree->leftSon = tmp->rightSon;
        if (tmp->rightSon != nullptr) {
            tmp->rightSon->father = tree;
        }
        tmp->rightSon = tree;
        tmp->father = tree->father;
        if (tmp->father != nullptr) {
            if (tmp->father->leftSon == tree) {
                tmp->father->leftSon = tmp;
            } else {
                tmp->father->rightSon = tmp;
            }
        }
        tree->father = tmp;
        updateHeight(tree);
        updateHeight(tree->father);
        return tmp;

    }

    Element<Key,Data>* rotateRR(Element<Key, Data> *tree) {
        /*  if (tree == nullptr) {
              return;
          }
          Element<Key, Data> *r = tree->rightSon;
          Element<Key, Data> *rl;
          //if it has left son
          if(r->leftSon != nullptr)
              rl ==r->leftSon;
          if (root == tree) {
              root = r;
          }

          tree->rightSon = r->leftSon;
          if (r->leftSon != nullptr) {
              rl->father = tree;
          }
          rl = tree;
          Element<Key ,Data>* rf=r->father;
          rf = tree->father;
          //if it has  a father connect the father with the left son
          if (rf != nullptr) {
              if (rf->leftSon == tree) {
                  rf->leftSon = r;
              } else {
                  rf->rightSon = r;
              }
          }
          tree->father = r;
          updateHeight(tree);
          updateHeight(tree->father);
          //return tempElement;*/
        if (tree == nullptr) {
            return nullptr;
        }
        Element<Key, Data> *tmp = tree->rightSon;
        if (root == tree) {
            root = tmp;
        }
        tree->rightSon = tmp->leftSon;
        if (tmp->leftSon != nullptr) {
            tmp->leftSon->father = tree;
        }
        tmp->leftSon = tree;
        tmp->father = tree->father;
        if (tmp->father != nullptr) {
            if (tmp->father->leftSon == tree) {
                tmp->father->leftSon = tmp;
            } else {
                tmp->father->rightSon = tmp;
            }
        }
        tree->father = tmp;
        updateHeight(tree);
        updateHeight(tree->father);
        return tmp;

    }

    Element<Key,Data>* rotateRL(Element<Key, Data> *tree) {
        tree->rightSon =rotateLL(tree->rightSon);
        return rotateRR(tree);
        //   return tempElement;
    }
    Element<Key,Data>* rotateLR(Element<Key, Data> *tree) {
        tree->leftSon =rotateRR(tree->leftSon);
        return rotateLL(tree);
        //return tempElement;
    }

    Element<Key,Data>* rotate(Element<Key, Data>* subTree){

        if(subTree == nullptr){
            return nullptr;
        }updateHeight(subTree);
        int rootBff=BFF(subTree), leftBff=BFF(subTree->leftSon), rightBff=BFF(subTree->rightSon);
        if((rootBff==2) && (leftBff>=0) ) {
            return rotateLL(subTree);
        }
        else if((rootBff==2) && (leftBff <0)){
            return  rotateLR(subTree);

        }
        else if((rootBff ==-2) && (rightBff <= 0)){
            return rotateRR(subTree);
        }
        else if ((rootBff ==-2) && (rightBff >0)) {
            return rotateRL(subTree);
        }
        return subTree;
    }

    /*  void insertAux(Element<Key, Data> *tree, Element<Key, Data> *newElement){
          Element<Key, Data> *current =find(newElement->key);
          if(current->key == newElement->key){
              //throw AlreadyExist();
          }
          if(current->key > newElement->key){
              current->leftSon =newElement;
              newElement->father = current;
              size++;
          }
          else{
              current->rightSon =newElement;
              newElement->father =current;
              size++;
          }
          Element<Key, Data>* ptr =newElement;
          while(ptr->father != nullptr && ptr != nullptr){
              updateHeight(ptr->father);
              ptr =ptr->father;
          }
          rotate(this->root);
      }*/

    Element<Key, Data>* insertAux(Element<Key, Data>* subTree, Element<Key, Data>* newNode) {
        if (subTree == nullptr) {
            return nullptr;
        }

        if (newNode->key > subTree->key) {
            if (subTree->rightSon == nullptr) {
                subTree->rightSon = newNode;
                newNode->father = subTree;
            } else {
                subTree->rightSon = insertAux(subTree->rightSon, newNode);
            }
        } else if (newNode->key < subTree->key) {
            if (subTree->leftSon == nullptr) {
                subTree->leftSon = newNode;
                newNode->father = subTree;
            } else {
                subTree->leftSon = insertAux(subTree->leftSon, newNode);
            }
        }

        updateHeight(subTree);
        return rotate(subTree);
    }

    void insert(const Key& key, const Data& data){
        Element<Key, Data> *newElement =new Element<Key, Data>(key, data);
        if(!newElement){}
        //   throw OutOfMemory();

        if(this->root == nullptr){
            root = newElement;
            size++;
            //updateHeight(root);
        }
        else{
            insertAux(root, newElement);
            size++;
        }
    }


    void remove(const Key& key){
        Element<Key, Data> *toDelete =find(key);
        if(!toDelete){
            // throw Element not exist();
        }
        else if(toDelete->key != key){
            // throw Element not exist();
        }
        else{
            size--;
            root =removeAux(this->root, key);
        }
    }

    Element<Key, Data> *removeAux(Element<Key, Data> *subTree, const Key& key) {
        if (subTree->key == key) {
            //if it has no children
            if (subTree->leftSon == nullptr && subTree->rightSon == nullptr)
            {
                delete subTree;
                subTree = nullptr;
            }
                //if it has one child
            else if (subTree->rightSon == nullptr || subTree->leftSon == nullptr)
            {
                Element<Key, Data> *toDelete = nullptr;
                //if it has left child
                if (subTree->leftSon) {
                    toDelete = subTree->leftSon;
                }
                    //if it has right child
                else {
                    toDelete = subTree->rightSon;
                }
                toDelete->father = subTree->father;
                delete subTree;
                subTree = toDelete;
            }
                //if it has two children
            else
            {
                Element<Key, Data> *son = subTree->rightSon;
                while (son->leftSon)
                {
                    son = son->leftSon;
                }
                if (son != nullptr)
                {
                    subTree->data = son->data;
                    subTree->key = son->key;
                    subTree->rightSon = removeAux(subTree->rightSon, son->key);
                }
            }
        }
            //go left
        else if(subTree->key > key)
        {
            subTree->leftSon = removeAux(subTree->leftSon, key);
        }
            //go right
        else
        {
            subTree->rightSon = removeAux(subTree->rightSon, key);
        }

        updateHeight(subTree);
        return rotate(subTree);
    }
/*
    void remove(const Key& key){
        Element<Key, Data> *toDelete =find(key);
        if(!toDelete){
            // throw Element not exist();
        }
        else if(toDelete->key != key){
            // throw Element not exist();
        }
        else{
            size--;
            root =removeAux(this->root, key);
        }
    }

    Element<Key ,Data> *removeAux(Element<Key ,Data> *toDelete, const Key& key) {
        //if not found
        if(!toDelete){
            return nullptr;
        }

        //if found
        if (toDelete->key == key) {
            //if it has no sons
            if (toDelete->leftSon == nullptr && toDelete->rightSon == nullptr) {
                delete toDelete;
                toDelete = nullptr;
            }

            //if it has one son
            else if (toDelete->rightSon == nullptr || toDelete->leftSon == nullptr) {
                Element<Key, Data> *current = nullptr;
                if (toDelete->leftSon) {
                    current = toDelete->leftSon;
                } else {
                    current = toDelete->rightSon;
                }

                current->father = toDelete->father;
                delete toDelete;
                toDelete = current;
            }
            //if it has two sons
            else {
                Element<Key, Data> *son = toDelete->rightSon;
                //To check
                while (son->leftSon) {
                    son = son->leftSon;
                }
                if (son != nullptr) {
                    toDelete->data = son->data;
                    toDelete->key = son->key;
                    toDelete->rightSon = removeAux(toDelete->rightSon, son->key);
                }
            }
        }

        else if(toDelete->key > key) {
            toDelete->leftSon = removeAux(toDelete->leftSon, key);
            }

        else {
            toDelete->rightSon = removeAux(toDelete->rightSon, key);
        }
        //updateHeight(toDelete);
        rotate(this->root);///check
        return this->root;
    }*/

    /* Element<Key,Data>* find_min(Element<Key,Data>* node) {
         if (!node) return nullptr;
         if (!node->leftSon) return node;
         else return find_min(node->leftSon);
     }
     Element<Key,Data>* remove_min(Element<Key,Data>* node) {
         if (!node->leftSon)
             return node->rightSon;
         node->leftSon = remove_min(node->leftSon);
         return rotate(node);
     }
     Element<Key,Data>* remove(Element<Key,Data>* node,const Key& key) {
         if (!node) return nullptr;
         if (node->key > key)
             node->leftSon = remove(node->leftSon, key);
         else if (node->key < key)
             node->rightSon = remove(node->rightSon, key);
         else {
             Element<Key,Data>* L = node->leftSon;
             Element<Key,Data>* R = node->rightSon;
             delete node;
             if (!R){
                 //R->father = nullptr;
                 return L;
             }
             Element<Key,Data>* min = find_min(R);
             min->rightSon = remove_min(R);
             min->leftSon = L;
             return rotate(min);
         }
         return rotate(node);
     }*/

};


#endif
