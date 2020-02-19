#pragma once

#ifdef HEADER_EXPORTS
#define HEADER_API __declspec(dllexport)
#else
#define HEADER_API __declspec(dllimport)
#endif

extern "C" HEADER_API int Check_DLL();

//extern "C" MATHLIBRARY_API void fibonacci_init(    const unsigned long long a, const unsigned long long b);


//extern "C" MATHLIBRARY_API bool fibonacci_next();


//extern "C" MATHLIBRARY_API unsigned long long fibonacci_current();


//extern "C" MATHLIBRARY_API unsigned fibonacci_index();
