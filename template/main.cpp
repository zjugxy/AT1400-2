#include <iostream>
#include <cstring>
#include <map>
#include <functional>
#include <memory>
#include "strBlob.h"
#include "Textquery.h"
#include<fstream>
#include<memory>
#include"Strvec.h"
using ptr = std::shared_ptr<std::vector<int>>;
ptr returnptr()
{
    return std::make_shared<std::vector<int>>();
}

void read(ptr temp)
{
    int num;
    while (std::cin >> num)
    {
        temp->push_back(num);
    }
}

void show(ptr temp)
{
    for (auto it = temp->begin(); it != temp->end(); it++)
        std::cout << *it << std::endl;
}
std::allocator<string> Strvec::alloc;
int main()
{


    std::allocator<string> strlist;
    auto ptr1_start = strlist.allocate(10);
    auto p = ptr1_start;
    strlist.construct(p++,10,'s');
    strlist.construct(p++,10,'s');
    strlist.construct(p++,10,'s');
    strlist.construct(p++,10,'s');
    strlist.construct(p++,10,'s');

    auto ptr2 = strlist.allocate(5);
    std::uninitialized_copy(ptr1_start,ptr1_start+5,ptr2);

    for(auto p = ptr2;p<ptr2+5;p++){
        std::cout<<*p<<std::endl;
    }
    


    std::ifstream inFile("nerf.txt", std::ios::in);
    std::ifstream in2("nerf.txt",std::ios::in);
    Strvec vec;
    string str_;
    while (in2>>str_)
    {   
        vec.push_back(str_);
    }
    Strvec newvec(vec);
    for(int i=0;i<10;i++){
        std::cout<<*(vec.begin()+i)<<' '<<*(newvec.begin()+i)<<std::endl;
    }





    TextQuery txt(inFile);
    string str;
    while (std::cin>>str)
    {
        /* code */
        auto answer = txt.query(str);
        print(std::cout,answer);
    }
    
}
