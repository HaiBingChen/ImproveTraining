//
// Created by mike on 2021/9/21.
//

#include <iostream>
#include <memory>
#include "CPP/InheritedConstructor/InheritedConstructor.h"

int main(int argc, const char** argv)
{
    std::cout << "This is the improve training for some of software skills" << std::endl;

    //==============================================================//
    //CPP Training
    //继承构造函数测试
    auto pInheritedConstructor = std::make_shared<NS_InheritedConstructor::InheritedConstructor>();
    pInheritedConstructor->InheritedConstructorTest();

    //==============================================================//

    return 0;
}
