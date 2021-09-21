//
// Created by mike on 2021/9/21.
// 右值引用
//

#ifndef IMPROVETRAINING_RVALUEREFERENCE_H
#define IMPROVETRAINING_RVALUEREFERENCE_H

namespace NS_RvalueReference {
    //浅拷贝
    class ShallowCopy {
    public:
        ShallowCopy() : d(new int(0)) {
            std::cout << "ShallowCopy()" << std::endl;
        }

        // 拷贝构造函数，浅拷贝，两个指针指向同一块内存
        ShallowCopy(const ShallowCopy &h) : d(h.d) {
            std::cout << "ShallowCopy(const ShallowCopy &h)" << std::endl;
        }

        ~ShallowCopy() {
            delete d;
            std::cout << "~ShallowCopy" << std::endl;
        }

        int *d;
    };

    //深拷贝
    class DeepCopy {
    public:
        DeepCopy() : d(new int(0)) {
            std::cout << "DeepCopy()" << std::endl;
        }

        // 拷贝构造函数，深拷贝，重新分配一块内存，并且值相同
        DeepCopy(const DeepCopy &h) : d(new int(*h.d)) {
            std::cout << "DeepCopy(const ShallowCopy &h)" << std::endl;
        }

        ~DeepCopy() {
            delete d;
            std::cout << "~DeepCopy" << std::endl;
        }

        int *d;
    };

    //移动构造
    class MoveConstructor {
    public:
        MoveConstructor() : d(new int(1)) {
            std::cout << "MoveConstructor()" << std::endl;
        }

        // 拷贝构造函数，深拷贝，重新分配一块内存，并且值相同
        MoveConstructor(const MoveConstructor &h) : d(new int(*h.d)) {
            std::cout << "MoveConstructor(const ShallowCopy &h)" << std::endl;
        }

        MoveConstructor(MoveConstructor &&h) : d(h.d) {
            h.d = nullptr;
            std::cout << "MoveConstructor(MoveConstructor && h)" << std::endl;
        }

        ~MoveConstructor() {
            delete d;
            std::cout << "~MoveConstructor" << std::endl;
        }

        int *d;
    };

    class RvalueReference {
    public:
        void RvalueReferenceTest() {
            std::cout << "++++++++++ RvalueReferenceTest() +++++++++++" << std::endl;
            //ShallowCopy s1; //调用ShallowCopy()，为s1.d分配内存
            //ShallowCopy s2(s1); //调用拷贝构造函数，s1.d和s2.d指向同一块内存
            //s1析构，释放s1.d内存
            //s2析构，此时s2.d指向的内存已经被释放，如果不加判断直接delete会造成double free

            std::cout << "=================================================" << std::endl;

            DeepCopy d1;
            DeepCopy d2(d1);

            std::cout << "=================================================" << std::endl;

            //这里返回的是右值的引用，会再次触发移动构造函数，m指向临时量的内存，临时量的d被设置为nullptr，
            // 然后析构掉，此时内存还是之前的内存。可以看到两次移动构造函数都没有重新分配内存，大大提高了效率。
            //由于编译器优化，可能临时量右值返回的移动构造不会打印
            MoveConstructor m1 = GetTemp();
            std::cout << "Call GetTemp, m1.d = " << m1.d << ", *m1.d = " << *m1.d <<std::endl;

            //将左值强制转换为右值引用，等同于static_cast<T&&>(lvalue);
            //MoveConstructor m2 = static_cast<MoveConstructor &&>(m2);
            MoveConstructor m2 = std::move(m1);
            std::cout << "Call std::move, m2.d = " << m2.d << ", *m2.d = " << *m2.d <<std::endl;
            //下面打印会挂掉，m1在std::move后内部的指针已经指向nullptr，不能再使用
            //std::cout << "Call std::move, m1.d = " << m1.d << ", *m1.d = " << *m1.d <<std::endl;

            std::cout << "=================================================" << std::endl;

            int a = 1;
            int b = 2;
            const int c = 3;
            const int d = 4;

            PerfectForward(a);
            PerfectForward(std::move(b));
            PerfectForward(c);
            PerfectForward(std::move(d));

            std::cout << "---------- RvalueReferenceTest() -----------" << std::endl << std::endl;
        }

    private:
        static MoveConstructor GetTemp() {
            MoveConstructor h;
            std::cout << "GetTemp, h.d = " << h.d << ", *h.d = " << *h.d <<std::endl;
            //这里如果定义了移动构造函数，则会调用移动构造函数，如果没有则调用拷贝构造函数
            //使用移动构造函数，会返回一个临时的右值，右值的d指向h.d的内存，然后h.d设置为nullptr，避免在析构时把内存释放掉
            return h;
        }

        //完美转发
        template<typename T>
        void PerfectForward(T &&t);

        static void PerfectForwardFunc(int && m) { std::cout << "PerfectForwardFunc: rvalue ref" << std::endl; }
        static void PerfectForwardFunc(int & m) { std::cout << "PerfectForwardFunc: lvalue ref" << std::endl; }
        static void PerfectForwardFunc(const int && m) { std::cout << "PerfectForwardFunc: const rvalue ref" << std::endl; }
        static void PerfectForwardFunc(const int & m) { std::cout << "PerfectForwardFunc: const lvalue ref" << std::endl; }
    };

    template<typename  T>
    void RvalueReference::PerfectForward(T &&t)
    {
        std::cout << "PerfectForward, t = " << t << std::endl;
        PerfectForwardFunc(std::forward<T>(t));
    }
}
#endif //IMPROVETRAINING_RVALUEREFERENCE_H
