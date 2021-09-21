//
// Created by mike on 2021/9/21.
//

#include "CommonTraining.h"
#include "CPP/InheritedConstructor/InheritedConstructor.h"
#include "CPP/DelegatedConstructor/DelegatedConstructor.h"

int main(int argc, const char** argv)
{
    std::cout << "This is the improve training for some of software skills" << std::endl;

    //CPP Training
    //==============================================================//
    //继承构造函数测试
    auto pInheritedConstructor = std::make_shared<NS_InheritedConstructor::InheritedConstructor>();
    pInheritedConstructor->InheritedConstructorTest();

    //委托构造函数测试

    //==============================================================//
    auto pDelegatedConstructor = std::make_shared<NS_DelegatedConstructor::DelegatedConstructor>();
    pDelegatedConstructor->DelegatedConstructorTest();

    return 0;
}
