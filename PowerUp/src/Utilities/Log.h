#ifndef _LOG_HG_
#define _LOG_HG_

#include <iostream>
#include <ctime>

//#define LOG(x) { auto end = std::chrono::system_clock::now(); std::time_t end_time = std::chrono::system_clock::to_time_t(end); std::cout << std::ctime(&end_time) << " - " << x << std::endl; }
#define LOG(x) { std::cout << x << std::endl; }

#endif
