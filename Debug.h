#pragma once
#ifndef DEBUG_H_
#define DEBUG_H_

#include <iostream>
#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

#endif  // DEBUG_H_