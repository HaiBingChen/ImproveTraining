//
// Created by mike on 2021/9/21.
// 委派构造函数
//

#ifndef IMPROVETRAINING_DELEGATEDCONSTRUCTOR_H
#define IMPROVETRAINING_DELEGATEDCONSTRUCTOR_H

#include "CommonHeader.h"

namespace NS_DelegatedConstructor {
    //普通冗余构造函数，每个构造函数都重复调用Init初始化函数
    class Normal {
    public:
        Normal() : type(1), name("name1") {
            Init();
            std::cout << "Normal() called, type = " << type << ", name = " << name << std::endl;
        }

        Normal(int i) : type(i), name("name2") {
            Init();
            std::cout << "Normal(int i) called, type = " << type << ", name = " << name << std::endl;
        }

        Normal(const std::string &n) : type(1), name(n) {
            Init();
            std::cout << "Normal(const std::string &n) called, type = " << type << ", name = " << name << std::endl;
        }

        Normal(int i, const std::string &n) : type(i), name(n) {
            Init();
            std::cout << "Normal(int i, const std::string &n) called, type = " << type << ", name = " << name
                      << std::endl;
        }

    private:
        void Init() { std::cout << "Init() called " << std::endl; }

        int type;
        std::string name;
    };

    //委派构造函数1
    class Delegated1 {
    public:
        //委托构造函数
        Delegated1() {
            Init();
            std::cout << "Delegated1() called, type = " << type << ", name = " << name << std::endl;
        }

        //目标构造函数
        Delegated1(int i) : Delegated1() {
            type = i;
            std::cout << "Delegated1(int i) called, type = " << type << ", name = " << name << std::endl;
        }

        Delegated1(const std::string &n) : Delegated1() {
            name = n;
            std::cout << "Delegated1(const std::string &n) called, type = " << type << ", name = " << name << std::endl;
        }

        Delegated1(int i, const std::string &n) : Delegated1() {
            type = i;
            name = n;
            std::cout << "Delegated1(int i, const std::string &n) called, type = " << type << ", name = " << name
                      << std::endl;
        }

    private:
        void Init() { std::cout << "Init() called " << std::endl; }

        int type { 1 }; //默认设置为1
        std::string name { "name1"}; //默认设置为name1
    };

    //委派构造函数2
    class Delegated2 {
    public:
        //目标构造函数
        Delegated2() : Delegated2(2, "delegated2_name2") {
            std::cout << "Delegated1() called, type = " << type << ", name = " << name << std::endl;
        }

        Delegated2(int i) : Delegated2(i, "delegated2_name2") {
            std::cout << "Delegated1(int i) called, type = " << type << ", name = " << name << std::endl;
        }

        Delegated2(const std::string &n) : Delegated2(2, n) {
            std::cout << "Delegated1(const std::string &n) called, type = " << type << ", name = " << name << std::endl;
        }

        //委托构造函数
        Delegated2(int i, const std::string &n) : type(i), name(n) {
            Init();
            std::cout << "Delegated1(int i, const std::string &n) called, type = " << type << ", name = " << name
                      << std::endl;
        }

    private:
        void Init() { std::cout << "Init() called " << std::endl; }

    private:
        int type; //没有默认值
        std::string name; //没有默认值
    };

    //测试类
    class DelegatedConstructor {
    public:
        void DelegatedConstructorTest() {
            std::cout << "++++++++++ DelegatedConstructorTest() +++++++++++" << std::endl;

            auto m_pNormal1 = std::make_shared<Normal>();
            auto m_pNormal2 = std::make_shared<Normal>(1);
            auto m_pNormal3 = std::make_shared<Normal>("normal_name1");
            auto m_pNormal4 = std::make_shared<Normal>(2, "normal_name2");

            std::cout << "=================================================" << std::endl;

            auto m_pDelegated11 = std::make_shared<Delegated1>();
            auto m_pDelegated12 = std::make_shared<Delegated1>(1);
            auto m_pDelegated13 = std::make_shared<Delegated1>("delegaed1_name1");
            auto m_pDelegated14 = std::make_shared<Delegated1>(1, "delegaed1_name2");

            std::cout << "=================================================" << std::endl;

            auto m_pDelegated21 = std::make_shared<Delegated2>();
            auto m_pDelegated22 = std::make_shared<Delegated2>(2);
            auto m_pDelegated23 = std::make_shared<Delegated2>("delegaed2_name1");
            auto m_pDelegated24 = std::make_shared<Delegated2>(2, "delegaed2_name2");

            std::cout << "---------- DelegatedConstructorTest() -----------" << std::endl << std::endl;
        }
    };
};


#endif //IMPROVETRAINING_DELEGATEDCONSTRUCTOR_H
