# cs3102-btree

* Implementar un Arbol B, usando el codigo de ejemplo. 
* Funciones a implementar:
  * Busqueda: booleano
  * Insert: void
  * Print: (a discrecion)

## Codigo de ejemplo. 


``` BTREE
#include <iostream>
#include <vector> 

template <typename T>
class SS_Traits{
public:
  typedef T  value_t;
  typedef std::vector<value_t> container_t;
  typedef std::vector<value_t*> pcontainer_t;
  typedef typename container_t::iterator iterator_t;
  
  class simple_search{
  public:
    bool operator() (container_t a, value_t v){
      return false;
    }
  };

  class post_order_print{
  public:
    void operator() (void){
      std::cout << "post order" << std::endl;
    }
  };

  typedef simple_search functor_t;
  typedef post_order_print print_t;
};

template <typename T>
class BS_Traits{
public:
  typedef T  value_t;
  typedef std::vector<value_t> container_t;
  typedef std::vector<value_t*> pcontainer_t;
  typedef typename container_t::iterator iterator_t;
  
  class binary_search{
  public:
    bool operator() (container_t a, value_t v){
      return false;
    }
  };

  class pre_order_print{
  public:
    void operator() (void){
      std::cout << "pre order" << std::endl;
    }
  };

  typedef binary_search functor_t;
  typedef pre_order_print print_t;
};

template <typename T, int S> 
class BNode {
public:
  typedef typename T::value_t value_t;
  typedef typename T::container_t container_t;
  typedef typename T::pcontainer_t pcontainer_t;

  container_t keys;
  pcontainer_t ptrs;
  std::size_t  order;

  BNode(void):order(S){
    keys=container_t(order,0);
    ptrs=pcontainer_t(order,NULL);
  }

  ~BNode(void){}
};

template <typename T, int S>
class BTree {
public: 
  typedef typename T::value_t value_t;
  typedef typename T::functor_t functor_t;
  typedef typename T::print_t print_t;

  BNode<T,S>* root;
  print_t print;
  functor_t search;

  BTree(void):root(NULL){
  }

  ~BTree(void){}

  void insert(const value_t& val = 0){
    // TODO :: INSERT
  }

  bool find(const value_t = 0) const{
    // TODO :: SEARCH
    // search(x); inside each page
    return false;
  }

  template <typename _T, int _S>
  friend std::ostream& operator<<(std::ostream& out, BTree<_T,_S> tree){
    tree.print();// (out)
    // IN PRE POST LEVEL ORDER
    return out;
  }

};

int main() {
  typedef BS_Traits<int> btrait_t;
  BTree<btrait_t,4> tree;
  tree.find(10);
  std::cout<<tree<< std::endl;


  typedef SS_Traits<float> strait_t;
  BTree<strait_t,10> stree; 
  std::cout<<stree<< std::endl;
}

```
