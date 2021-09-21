//
// Created by user on 2021/9/21.
//

#ifndef IMPROVETRAINING_SIGNAL_H
#define IMPROVETRAINING_SIGNAL_H

#include "CommonHeader.h"

#define  SIGNALINVAILD 1000
struct sig_name
{
    int		signo;	            // signal number
    const std::string &signm;	// singal name
};

class Signal {
public:
    static void Init();

private:
    static const std::string &SigToStr(int signo);
    static int SearchSigno(const sig_name* array, int start, int end, int signo);
    static void OnSignal(int sig);
    static void PrintBackTrace();
};


#endif //IMPROVETRAINING_SIGNAL_H
