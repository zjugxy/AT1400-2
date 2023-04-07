#pragma once
#include<memory>
#include<vector>
#include<string>
#include<iostream>
class strBlob{
    using mytype = std::vector<std::string>;
    private:
    std::shared_ptr<std::vector<std::string>> ptr;
    void check(int size,std::string error){
        if(size>ptr->size())
            std::cerr<<error<<std::endl;
    }
    public:
    strBlob(){}
    strBlob(std::vector<std::string> li):ptr(std::make_shared<mytype>(li)){};
    strBlob(std::initializer_list<std::string> li):ptr(std::make_shared<mytype>(mytype(li))){};
    void show(){
        for(auto it = ptr->begin();it!=ptr->end();it++)
            std::cout<<*it<<std::endl;
    }
    strBlob& operator=(const strBlob& blob){
        ptr = blob.ptr;
        return *this;
    }
    strBlob(const strBlob& blob):ptr(blob.ptr){}

    void push_back(std::string str)const{
        ptr->push_back(str);
    }
    void pop_back(){
        check(1,"empty elem");
        ptr->pop_back();
    }
    std::vector<std::string>::size_type size(){return ptr->size();}
    std::string& front()const{
        return ptr->front();
    }
    std::string& back() const{
        return ptr->back();
    }
};