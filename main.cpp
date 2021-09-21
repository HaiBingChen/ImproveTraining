//
// Created by mike on 2021/9/21.
//

#include <unistd.h>
#include "CommonHeader.h"
#include "UtilsHeader.h"
#include "CPPHeader.h"

int main(int argc, const char** argv)
{
    std::cout << "This is the improve training for some of software skills" << std::endl;

    Signal::Init();

#if 0
    //CPP Training
    //==============================================================//
    //继承构造函数测试
    auto pInheritedConstructor = std::make_shared<NS_InheritedConstructor::InheritedConstructor>();
    pInheritedConstructor->InheritedConstructorTest();

    //委托构造函数测试
    //==============================================================//
    auto pDelegatedConstructor = std::make_shared<NS_DelegatedConstructor::DelegatedConstructor>();
    pDelegatedConstructor->DelegatedConstructorTest();
#endif
    //右值引用测试
    //==============================================================//
    auto pRvalueReference = std::make_shared<NS_RvalueReference::RvalueReference>();
    pRvalueReference->RvalueReferenceTest();

    return 0;
}
