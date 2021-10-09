//
// Created by 裴沛东 on 2021/10/9.
//

#ifndef SHAREDPTR_SHAREDPTR_H
#define SHAREDPTR_SHAREDPTR_H
#include <atomic>
#include <iostream>
#include <cassert>

using std::atomic;
template<typename T>
class SharedPtr {
public:
    SharedPtr(T *ptr = nullptr):m_ptr(ptr),m_use(new atomic<long>(0)){ if(ptr) {(*m_use)++;}}
    SharedPtr(const SharedPtr<T> &s):m_ptr(s.m_ptr),m_use(s.m_use){
        std::cout<<"copy construct called"<<std::endl;
        (*m_use)++;
    }
    SharedPtr<T>& operator= (const SharedPtr<T> &s) {
        if(this->m_ptr == s.m_ptr) {
            return *this;
        }
        if(this->m_ptr) {
            *(this->m_use)--;
            if(*(this->m_use) == 0) {
                delete this->m_ptr;
                delete this->m_use;
            }
        }
        this->m_ptr = s.m_ptr;
        this->m_use = m_use;
        (*this->m_use)++;
        return *this;
    }
    SharedPtr(const SharedPtr<T> &&s) {
        *this = std::move(s);
    }
    void operator= (SharedPtr<T> &&s) {
        std::cout<<"move assigned construct be called"<<std::endl;
        if(this->m_ptr == s.m_ptr) {
            return;
        }
        if(this->m_ptr) {
            (*(this->m_use))--;
            if(*(this->m_use) == 0) {
                delete this->m_ptr;
                delete this->m_use;
            }
        }
        this->m_ptr = s.m_ptr;
        this->m_use = s.m_use;
        s.m_ptr = nullptr;
        s.m_use = nullptr;
    }
    T& operator*() {
        return *(this->m_ptr);


    }
    T* operator->() {
        assert(this->m_ptr == nullptr);
        return this->m_ptr;

    }
    long use_count() {
        return *m_use;

    }
    ~SharedPtr() {
        std::cout<<"deconstruct be called"<<std::endl;
        if(m_use && m_ptr) {
            --(*m_use);
            if((*m_use) == 0) {
                delete m_use;
                m_use = nullptr;
                delete m_ptr;
                m_ptr = nullptr;
            }
            m_ptr = nullptr;
        }

    }
private:
    atomic<long> *m_use;
    T *m_ptr = nullptr;



};


#endif //SHAREDPTR_SHAREDPTR_H
