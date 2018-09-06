//
// Created by mustang on 18-7-10.
//

#ifndef TESTING_MY_SMARTPOINT_H
#define TESTING_MY_SMARTPOINT_H

#include "assert.h"

template <typename T> class i_smart_point
{
private:
    int *re_count;
    T *t;

    void increment_re_count() const
    {
        ++(*re_count);
    }

public:
    void use_count()
    {
        std::cout<<*re_count<<std::endl;
    }

public:
    // 默认构造
    explicit i_smart_point(T *t_= nullptr):t{t_}
    {
        re_count = new int(1);
    }

    i_smart_point (const i_smart_point<T>& rhs)
    {
        re_count = rhs.re_count;
        t = rhs.t;
        rhs.increment_re_count();
    }

    i_smart_point<T>&operator=(const i_smart_point<T> &rhs)
    {
        if(this->re_count!=rhs.re_count)
        {
            if(--(*this->re_count)==0)
            {
                delete (re_count);
                delete (t);
            }
            this->re_count = rhs.re_count;
            this->t = rhs.t;
            rhs.increment_re_count();
        }

        return *this;
    }

    ~i_smart_point()
    {
        if(--*re_count==0)
        {
            delete (t);
            delete (re_count);
            return;
        } 
    }

    T &operator*()
    {
        assert(t != nullptr);
        return *t;
    }

};

#endif //TESTING_MY_SMARTPOINT_H
