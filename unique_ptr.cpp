#include <iostream>
#include <string>
// #include <memory>

template <class T>
class unique_ptr {
    private:
        T* objPtr;
        void removeObjPtr() {
            if ( objPtr != nullptr ) {
                delete objPtr;
                objPtr = nullptr;
            }
        }
    public:
        unique_ptr(T* ptr = nullptr) {
            objPtr = ptr;
        }
        unique_ptr(unique_ptr<T>&& other) {
            objPtr = other.objPtr;
            other.objPtr = nullptr;
        }
        unique_ptr<T>& operator=(unique_ptr<T>&& other) {
            this->removeObjPtr();
            objPtr = other.objPtr;
            other.objPtr = nullptr;
            return *this;
        }
        ~unique_ptr() {
            this->removeObjPtr();
        }
        T* operator->() {
            return objPtr;
        }

        unique_ptr(unique_ptr<T>& other) = delete;
        T& operator=(unique_ptr<T>& other) = delete;
};

class Test {
    private:
        std::string name;
    public:
        Test(std::string name): name(name) {
            std::cout << "Test counstructor name = " << name << std::endl;
        }
        ~Test() {
            std::cout << "~Test destructor name = " << name << std::endl;
        }
        std::string getName() const {
            return name;
        }
};

void printName(unique_ptr<Test> other) {
    std::cout << "Name = " << other->getName() << std::endl;
}

int main() {
    unique_ptr<Test> matros(new Test("matros"));
    // printName(std::move(matros));
    unique_ptr<Test> vasilii(new Test("vasilii"));

    // vasilii = matros;

    vasilii = std::move(matros);

    std::cout << vasilii->getName()  << std::endl;

    return 0;
}
