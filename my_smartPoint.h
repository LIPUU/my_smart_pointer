//
// Created by mustang on 18-7-10.
//

#ifndef TESTING_MY_SMARTPOINT_H
#define TESTING_MY_SMARTPOINT_H

#include <cassert>

template<typename T>
class i_shared_ptr
{
private:
    int *re_count;
    T *t;

    void increment_re_count() const
    {
        ++(*re_count);
    }

public:
    // 调试函数
    void use_count()
    {
        std::cout << *re_count << std::endl;
    }

public:

    // 默认构造
    explicit i_shared_ptr(T *t_ = nullptr) : t{t_}
    {
        if (t)
        {
            re_count = new int(1);
        } else
        {
            re_count = new int(0);
        }
    }


    // 拷贝构造
    i_shared_ptr(const i_shared_ptr<T> &rhs)
    {
        rhs.increment_re_count();
        re_count = rhs.re_count;
        t = rhs.t;
    }

    i_shared_ptr &operator=(const i_shared_ptr<T> &rhs)
    {
        assert(*re_count >= 0);
        if (this != &rhs)
        {
            if (--*re_count <= 0)
            {
                delete t;
                delete re_count;
            }

            rhs.increment_re_count();
            re_count = rhs.re_count;
            t = rhs.t;
        }
        return *this;
    }

    // 析构函数
    ~i_shared_ptr()
    {
        // t有效意味着*re_count不可能为0
        if (t && --*re_count == 0)
        {
            delete t;
            delete re_count;
            std::cout << "执行了i_shared_ptr析构函数,且销毁了数据和引用计数" << std::endl;
        } else if (!t)
        {
            std::cout << "执行了i_shared_ptr析构函数,由于t未指向数据,所以析构函数什么也不做" << std::endl;
        } else
        {
            std::cout << "执行了i_shared_ptr析构函数,仅仅将引用计数-1,但没有销毁任何东西,此时use_count= " << *re_count << std::endl;
        }

    }


    T &operator*()
    {
        assert(t != nullptr);
        return *t;
    }
};

#endif //TESTING_MY_SMARTPOINT_H
