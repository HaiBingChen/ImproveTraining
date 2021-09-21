//
// Created by user on 2021/9/21.
//

#include <execinfo.h>
#include "Signal.h"

sig_name sig_name_table[] =
{
    {SIGHUP,		"SIGHUP"},
    {SIGINT,		"SIGINT"},
    {SIGQUIT,		"SIGQUIT"},
    {SIGILL,		"SIGILL"},
    {SIGTRAP,		"SIGTRAP"},
    {SIGABRT,		"SIGABRT"},
    {SIGIOT,		"SIGIOT"},
    {SIGBUS,		"SIGBUS"},
    {SIGFPE,		"SIGFPE"},
    {SIGKILL,		"SIGKILL"},
    {SIGUSR1,		"SIGUSR1"},
    {SIGSEGV,		"SIGSEGV"},
    {SIGUSR2,		"SIGUSR2"},
    {SIGPIPE,		"SIGPIPE"},
    {SIGALRM,		"SIGALRM"},
    {SIGTERM,		"SIGTERM"},
    {SIGSTKFLT,		"SIGSTKFLT"},
    {SIGCHLD,		"SIGCHLD"},
    {SIGCONT,		"SIGCONT"},
    {SIGSTOP,		"SIGSTOP"},
    {SIGTSTP,		"SIGTSTP"},
    {SIGTTIN,		"SIGTTIN"},
    {SIGTTOU,		"SIGTTOU"},
    {SIGURG,		"SIGURG"},
    {SIGXCPU,		"SIGXCPU"},
    {SIGXFSZ,		"SIGXFSZ"},
    {SIGVTALRM,		"SIGVTALRM"},
    {SIGPROF,		"SIGPROF"},
    {SIGWINCH,		"SIGWINCH"},
    {SIGIO,			"SIGIO|SIGPOLL"},
    {SIGNALINVAILD, "SIGNALINVAILD"},
};

const std::string &Signal::SigToStr(int signo)
{
    int sig_idx = SearchSigno(sig_name_table, 0, sizeof(sig_name_table) / sizeof(sig_name) - 1, signo);
    return sig_name_table[sig_idx].signm;
}

int Signal::SearchSigno(const sig_name *array, int start, int end, int signo) {
    int left = start;
    int right = end;

    while (left <= right)
    {
        int mid = (left + right)/2;

        if (signo < array[mid].signo)
        {
            right = mid -1;
        }
        else if (signo > array[mid].signo)
        {
            left = mid + 1;
        }
        else
            return mid;
    }

    return SIGNALINVAILD;
}

void Signal::Init()
{
    //MWP_INFO_FUNC();

    signal(SIGKILL,     Signal::OnSignal);
    signal(SIGSTOP,     Signal::OnSignal);
    signal(SIGTSTP,     Signal::OnSignal);
    signal(SIGBUS,      Signal::OnSignal);
    signal(SIGFPE,      Signal::OnSignal);
    signal(SIGSTKFLT,   Signal::OnSignal);
    signal(SIGABRT,     Signal::OnSignal);
    signal(SIGSEGV,     Signal::OnSignal);
    signal(SIGINT,      Signal::OnSignal);
    signal(SIGTERM,     Signal::OnSignal); // Normal kill
    signal(SIGIOT,      Signal::OnSignal);
    signal(SIGPIPE,     Signal::OnSignal);
    signal(SIGURG,      Signal::OnSignal);
    signal(SIGXCPU,     Signal::OnSignal);
    signal(SIGXFSZ,     Signal::OnSignal);
    signal(SIGPOLL,     Signal::OnSignal);
    signal(SIGSYS,      Signal::OnSignal);
}

void Signal::OnSignal(int sig)
{
    std::cout << "Signal::OnSignal - " << SigToStr(sig) << "(" << sig << ")" << std::endl;

    signal(sig, nullptr);
    switch(sig)
    {
        case SIGABRT:
        case SIGTSTP:
        case SIGBUS:
        case SIGFPE:
        case SIGSTKFLT:
        case SIGSEGV:
        case SIGINT:
        case SIGPIPE:
        case SIGSYS:
            PrintBackTrace();
            exit(0);
            //    case SIGKILL:
            //    case SIGSTOP:
        case SIGTERM: // Normal kill, don't print backtrace
            exit(0);
        default:break;;
    }
}

void Signal::PrintBackTrace()
{
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << "Back Trace:" << std::endl;
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    void *array[10] = {0};
    size_t size = backtrace(array, 10);
    char **strNames = (char **)backtrace_symbols(array, size);

    for (size_t i = 0; i < size; i++)
    {
        printf("%02zu:%s\n", i, strNames[i]);
    }

    std::cout << "--------------------------------------------------------------------------------" << std::endl;
}