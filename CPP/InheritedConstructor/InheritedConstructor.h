//
// Created by mike on 2021/9/21.
// 继承构造函数
//

#ifndef IMPROVETRAINING_INHERITEDCONSTRUCTOR_H
#define IMPROVETRAINING_INHERITEDCONSTRUCTOR_H

#include "CommonHeader.h"

namespace NS_InheritedConstructor {
    class A {
    public:
        A(int i) {
            std::cout << "A(int i) called, i = " << i << std::endl;
        }

        A(double d, int i) {
            std::cout << "A(double d, int i) called, d = " << d << ", i = " << i << std::endl;
        }

        A(float f, int i, const std::string &c) {
            std::cout << "A(float f, int i, char *c) called, f = " << f << ", i = " << i << ", c = " << c << std::endl;
        }
    };

    //传统构造函数，B要初始化基类A的所有构造函数
    class B : A {
    public:
        B(int i) : A(i) {
            std::cout << "B(int i) called, i = " << i << std::endl;
        }

        B(double d, int i = 0) : A(d, i) {
            std::cout << "B(double d, int i) called, d = " << d << ", i = " << i << std::endl;
        }

        B(float f, int i = 0, const std::string &c = "") : A(f, i, c) {
            std::cout << "B(float f, int i, char *c) called, f = " << f << ", i = " << i << ", c = " << c << std::endl;
        }
    };

    //继承构造函数，C可以直接用A的构造函数
    //C++11标准继承构造函数被设计为跟派生类中的各种类默认函数（默认构造、析构、拷贝构造等）一样，是隐式声明的。
    class C : A {
        using A::A;
    private:
        int d{0};
    };

    //测试类
    class InheritedConstructor {
    public:
        void InheritedConstructorTest() {
            std::cout << "++++++++++ InheritedConstructorTest() +++++++++++" << std::endl;

            auto m_pB1 = std::make_shared<B>(1);
            auto m_pB2 = std::make_shared<B>(1.0);
            auto m_pB3 = std::make_shared<B>(1.0, 1, "B called");

            std::cout << "=================================================" << std::endl;

            auto m_pC1 = std::make_shared<C>(2);
            auto m_pC2 = std::make_shared<C>(2.0);
            auto m_pC3 = std::make_shared<C>(2.0, 2, "C called");

            std::cout << "---------- InheritedConstructorTest() -----------" << std::endl << std::endl;
        }
    };
};


#endif //IMPROVETRAINING_INHERITEDCONSTRUCTOR_H
