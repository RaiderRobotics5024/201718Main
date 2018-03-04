#ifndef _LOG_HG_
#define _LOG_HG_

#include <iostream>
#include <chrono>

#define LOG(x) { std::cout << "[ " << std::chrono::system_clock::now(); << " ] - " << x << std::endl; }

#endif
