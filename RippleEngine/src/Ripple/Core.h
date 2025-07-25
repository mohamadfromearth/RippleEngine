#pragma once

#ifdef RP_BUILD_DLL
    #define RIPPLE_API __declspec(dllexport)
  #else
    #define RIPPLE_API __declspec(dllimport)
   #endif
