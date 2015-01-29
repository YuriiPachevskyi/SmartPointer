#include <iostream>
#include <string>

using namespace std;

template <class T>
class SP {
    private:
        T *objPtr;
        void remObjRef() {
            if ( objPtr != NULL && objPtr->decRefCout() == 0 ) {
                delete objPtr;
                objPtr = NULL;
            }
        }
        class BadPtrException{};
    public:
        SP<T>( T *ptr = NULL ) {
            objPtr = ptr;
        }
        SP<T>(SP<T> &objRef) {
            objPtr = objRef.objPtr;
            if ( objPtr != NULL ) {
                objPtr->incRefCout();
            }
        }
        T& operator*() {
            if ( objPtr == NULL ) {
                throw BadPtrException();
            }
            return *objPtr;
        }
        T* operator->() {
            if ( objPtr == NULL ) {
                throw BadPtrException();
            }
            return objPtr;
        }
        SP<T>& operator=(SP<T> &other) {
            if ( *this == other ) {
                return *this;
            }
            if ( other.objPtr != NULL ) {
                other.objPtr->incRefCout();
            }
            remObjRef();
            objPtr = other.objPtr;
            return *this;
        }
        bool operator==(SP<T>& other) {
            return objPtr == other.objPtr;
        }
        ~SP<T>() {
            remObjRef();
        }
};

class RefBase {
    private:
        unsigned int refCouter;
    public:
        RefBase(): refCouter(1) {}
        void incRefCout() {
            refCouter += 1;
        }
        unsigned int decRefCout() {
            return --refCouter;
        }
};

class Human: public RefBase {
    private:
        string name;
    public:
        Human(string name): name(name) {
            cout << "Human constructor name = " << name << endl;
        }
        ~Human() {
            cout << "Human destructor name = " << name << endl;
        }
        string getName() {
            return name;
        }
};

class Car {
    private:
        string model;
        SP<Human> owner;
    public:
        Car(SP<Human> owner, string model): owner(owner), model(model) {
            cout << "Car constructor model = " << model << " owner = " << owner->getName() << endl;
        }
        ~Car() {
            cout << "Car destructor model = " << model << " owner = " << owner->getName() << endl;
        }
        string getModel() {
            return model;
        }
        string getOwner() {
            return owner->getName();
        }
};

ostream& operator<<(ostream& out, Car &car) {
    out << "(model->" << car.getModel() << ", owner->" << car.getOwner() << ")";
    return out;
}

int main() {
    SP<Human> eric(new Human("Eric"));
    // SP<Human> jin(new Human("Jin woo"));
    // eric = jin;
    Car *BMW = new Car(eric, "BMW");
    cout << *BMW << endl;
    delete BMW; //to check is this example works just comment this str

    // cout << eric->getName() << endl;
    // if ( eric == jin ) {
    //     cout << "yes" << endl;
    // } else {
    //     cout << "no" << endl;
    // }

    return 0;
}
