
template<class Key, class Data>
class Element{
public:
    //properties
    int height;
    Key key;
    Data data;
    Element* father;
    Element* leftSon;
    Element* rightSon;


    //functions
    //C'tor && D'tor
    Element() :height(0), key(nullptr), data(nullptr),father(nullptr), leftSon(nullptr), rightSon(nullptr){};

    Element(const Key &key, const Data &data, Element *father = nullptr) :
            height(0),key(key), data(data), father(father), leftSon(nullptr),
            rightSon(nullptr) {};

    Element(const Element& other): height(other.height),key(other.key), data(other.data),
            father(nullptr),rightSon(nullptr), leftSon(nullptr) {
        if (other.parent != nullptr) {
            father = new Element(*other.father);
        }
        if (other.leftSon != nullptr) {
            leftSon = new Element(*other.leftSon);
        }
        if (other.rightSon != nullptr) {
            rightSon = new Element(*other.rightSon);
        }
    }

    ~Element() =default;

    //operators
    Element &operator=(const Element &other) {
        key = other.key;
        data = other.data;
        height = other.height;

        Element *toDelete1 = leftSon;
        leftSon = new Element(*other.leftSon);
        delete toDelete1;

        Element *toDelete2 = rightSon;
        rightSon = new Element(*other.rightson);
        delete toDelete2;

        Element *toDelete3 = father;
        father = new Element(*other.father);
        delete toDelete3;

        return *this;
    }

    bool operator==(const Element &element) const {
        return (this->key == element.key);
    }

    bool operator>(const Element &element) const {
        return (this->key > element.key);
    }

    bool operator<(const Element &element) const {
        return (this->key < element.key);
    }

};
#endif //INC_234218WET1_TRY1_AVLELEMENT_H
