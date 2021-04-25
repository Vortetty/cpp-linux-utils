#ifndef TERMLIB_HPP
    #define TERMLIB_HPP
    #ifdef _WIN32
        #include <windows.h>
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        bool _ = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int termX = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int termY = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    #else
        #include <sys/ioctl.h>
        struct winsize w;
        bool _ = ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int termX = w.ws_col;
        int termY = w.ws_row;
    #endif
#endif