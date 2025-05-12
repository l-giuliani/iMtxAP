#ifndef _UTILS_H_
#define _UTILS_H_

namespace NUtils {

class SimpleIteratorElement {
public:
    virtual void* getListElements() = 0;
    virtual uint16_t getNElements() = 0;
};

template <typename T>
class SimpleListIterator {
private:
    T* list;
    uint16_t n;
    uint16_t index;
public:
    SimpleListIterator(SimpleIteratorElement* element) {
        this->list = reinterpret_cast<T*>(element->getListElements());
        this->n = element->getNElements();
        this->index = 0;
    }
    T* begin() {
        this->index = 0;
        return (&this->list[this->index]);
    }
    T* end() {
        this->index = n - 1;
        return (&this->list[this->index]);
    }
    T* next() {
        if(this->index >= this->n) {
            return nullptr;
        }
        T* el = &this->list[this->index];
        this->index++;
        return el;
    }
};

}

#endif // _UTILS_H