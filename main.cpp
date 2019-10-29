// VectorAndList.cpp : Defines the entry point for the console application.
#include <vector>
#include <list>
#include <string>
#include <cstddef>
#include <stdio.h>
#include <algorithm>

#include "memorySpy.h"

#include "myVector.h"
#include "myList.h"
#include "myString.h"

#define USE_MOVE 0
//#define Vector std::vector
#define Vector MyVector
#define List MyList
//#define String std::basic_string<char, std::char_traits<char>, SpyAllocator<char>>
#define String MyString

int main()
{
    {
        printf("===========Test container============\n");
        Foo::ResetCount();
        printf("Create container\n");
        MyVector<Foo, SpyAllocator<Foo>> foos;
        printf("Destroy container\n");
    }
    
    Foo::ResetCount();
    {
        printf("=======Vector of int================\n\nCreate vector\n");
        Vector<int, SpyAllocator<int>> intVec;
        printf("\nsizeof(intVec) : %ld\n", sizeof(intVec));
        printf("\nCapacity=%ld, Size=%ld\n", intVec.capacity(), intVec.size());
        DO(intVec.push_back(10);)
        DO(intVec.push_back(20);)
        DO(intVec.push_back(30);)
        DO(intVec.push_back(40);)
        DO(intVec.push_back(50);)
        printf("\nCapacity=%ld, Size=%ld\n", intVec.capacity(), intVec.size());
        DO(intVec[3] *= 2;)
        for (size_t i = 0; i < intVec.size(); ++i)
        {
            printf("%d ", intVec[i]);
        }
        printf("\n");
        printf("\nDestroy vector\n\n");
    }
    {
        printf("\n=======Vector of Foo================\n\nCreate vector\n");
        Vector<Foo, SpyAllocator<Foo>> fooVec;
        printf("\nsizeof(fooVec) : %ld\n", sizeof(fooVec));
        DO(fooVec.reserve(2));
        DO(fooVec.push_back(Foo()));
        DO(fooVec.push_back(Foo()));
        DO(fooVec.push_back(Foo()));
        printf("\nDestroy vector\n\n");
    }
    {
        printf("\n=======Vector of Foo================\n\nCreate vector\n");
        Vector<Foo, SpyAllocator<Foo>> fooVec;
        DO(fooVec.reserve(2));
        DO(fooVec.push_back(Foo()));
        DO(fooVec.push_back(Foo()));
        DO(fooVec.clear());
        DO(fooVec.push_back(Foo()));
        printf("\nDestroy vector\n\n");
    }
    {
        printf("\n=======Vector of Foo================\n\nCreate vector\n");
        Vector<Foo, SpyAllocator<Foo>> fooVec;
        DO(fooVec.resize(2));
        DO(fooVec.push_back(Foo()));
        DO(fooVec.push_back(Foo()));
        printf("\nDestroy vector\n\n");
    }
    {
        printf("\n=======Vector of Foo================\n\nCreate vector\n");
        Vector<Foo, SpyAllocator<Foo>> fooVec;
        DO(fooVec.push_back(Foo()));
        DO(fooVec.push_back(Foo()));
        printf("\nCopy fooVec\n\n");
        Vector<Foo, SpyAllocator<Foo>> fooVec2 = fooVec;
        printf("\nDestroy vectors \n");
    }
    {
        printf("\n=======Vector of Foo================\n\nCreate vector\n");
        Vector<Foo, SpyAllocator<Foo>> fooVec;
        DO(fooVec.push_back(Foo()));
        DO(fooVec.push_back(Foo()));
        printf("\nCopy fooVec\n\n");
        Vector<Foo, SpyAllocator<Foo>> fooVec2;
        fooVec2 = fooVec;
        printf("\nDestroy vectors \n");
    }



    {
        printf("\n=======List================\n\nCreate list\n");
        List<int, SpyAllocator<int>> list;
        DO(list.push_back(10));
        DO(list.push_back(20));
        DO(list.push_back(30));
        DO(list.push_back(40));
        DO(list.push_back(50));
        printf("\nList size : %ld\n", list.size());
        printf("\nPrint list:\n");
        for (List<int, SpyAllocator<int>>::iterator it = list.begin(); it != list.end(); ++it)
        {
            printf("%d ", *it);
        }
        printf("\n\n");
        DO(list.remove(20));
        DO(list.remove(40));
        for (List<int, SpyAllocator<int>>::iterator it = list.begin(); it != list.end(); ++it)
        {
            printf("%d ", *it);
        }
        printf("\n\n");
        DO(list.insert(std::find(list.begin(), list.end(), 30), 60));
        printf("\nList size : %ld\n", list.size());
        printf("\nPrint list:\n");
        for (List<int, SpyAllocator<int>>::iterator it = list.begin(); it != list.end(); ++it)
        {
            printf("%d ", *it);
        }
        printf("\n\n");
        printf("\nDestroy list\n\n");
    }
    {
        printf("\n=======List================\n\nCreate list\n");
        List<int, SpyAllocator<int>> list;
        DO(list.push_back(10));
        DO(list.push_back(20));
        DO(list.push_back(30));
        DO(list.push_back(40));
        DO(list.push_back(50));
        printf("\n\nCopy list = list2\n");
        List<int, SpyAllocator<int>> list2 = list;
        DO(list.remove(20));
        DO(list.remove(40));
        DO(list.insert(std::find(list.begin(), list.end(), 30), 60));
        printf("\nPrint list:\n");
        for (List<int, SpyAllocator<int>>::iterator it = list.begin(); it != list.end(); ++it)
        {
            printf("%d ", *it);
        }
        printf("\n\n");
        printf("\nPrint list2:\n");
        for (List<int, SpyAllocator<int>>::iterator it = list2.begin(); it != list2.end(); ++it)
        {
            printf("%d ", *it);
        }
        printf("\n\n");
        printf("\nDestroy lists\n\n");
    }

    {
        printf("\n=======Strings================\n");
        printf("Sizeof String : %ld\n", sizeof(String));
        {
            DO(String s);
            printf("Length of s : %ld\n", s.length());
        }
        {
            DO(String s = "Moins de 16 car");
            printf("Length of s : %ld\n", s.length());
        }
        {
            DO(String s = "Plus de 16 car, 27 au total");
            printf("Length of s : %ld\n", s.length());
        }
        {
            DO(String s = "Plus de 32 car, 34 pour etre exact");
            printf("Length of s : %ld\n", s.length());
        }
        {
            DO(String s = "Plus de 48 car, 51 pour etre exact, bon ca suffit ?");
            printf("Length of s : %ld\n", s.length());
        }
        {
            DO(String s1 = "toto est vraiment une personne incroyable");
            DO(String s2 = s1);
            DO(s1[1] = 'a');
            DO(s1[3] = 'a');
            printf("s1 : %s\n", s1.c_str());
            printf("s2 : %s\n", s2.c_str());
            DO(s2 = s1);
            DO(s2[3] = 'i');
            printf("s1 : %s\n", s1.c_str());
            printf("s2 : %s\n", s2.c_str());
        }
        DO(String s1 = "Bonjour");
        DO(String s2 = " le monde !");
        DO(String s3 = s1 + s2);
        printf("s3 : %s\n", s3.c_str());
        printf("\nDestroy vector\n\n");
    }
    memorySpy.CheckLeaks();
    system("pause");
    return 0;
}