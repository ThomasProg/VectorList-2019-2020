#ifndef _MY_STRING_H_
#define _MY_STRING_H_

#include <iostream>
#include <cassert>

class MyString
{
private:
    char* str = nullptr;
public:

    MyString()
    {}

    MyString(const char* strCopied)
    {
        if (str != nullptr)
            delete[] str;
        
        size_t vlength = 0;
        while (str[vlength] != '\0')
            vlength++;
        str = new const char[strCopied.length()];

        size_t i = 0;
        while (strCopied[i] != '\0')
        {
            str[i] = strCopied[i];
            i++;
        }
    }

    ~MyString()
    {}

    size_t length()
    {
        if (str == nullptr)
            return 0;

        size_t vlength = 0;
        while (str[vlength] != '\0')
            vlength++;
        
        return vlength;
    }

    const char* c_str() {return str;}

    const char& operator[](size_t index)
    {
        return str[index];
    }

    operator+(MyString& str)
    {

    }
};

#endif