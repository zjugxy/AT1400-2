#pragma once
#include<memory>
#include<string>
#include<utility>
using std::string;
class Strvec{
    private:
    string* elements,*firstfree,*cap;
    static std::allocator<string> alloc;

    public:
    Strvec():elements(nullptr),firstfree(nullptr),cap(nullptr){}
    Strvec(const Strvec& str){
        auto data = alloc_n_copy(str.begin(),str.end());
        elements = data.first;
        cap = firstfree = data.second;
    }
    Strvec& operator=(const Strvec& str){
        free();
        auto data = alloc_n_copy(str.begin(),str.end());
        elements = data.first;
        cap = firstfree = data.second;
        return *this;
    }
    ~Strvec();
    void push_back(const string& temp){
        chk_n_alloc();
        alloc.construct(firstfree++,temp);
    }
    size_t size()const{
        return firstfree - elements;
    }
    size_t capacity() const{
        return cap - elements;
    }

    string* begin()const{
        return elements;
    }

    string* end() const{
        return cap;
    }

    private:
    void free();
    void reallocate();
    void chk_n_alloc(){
        if(size()==capacity())
            reallocate();
    }
    std::pair<string*,string*> alloc_n_copy(const string* start,const string* end);

};
Strvec::~Strvec(){
    free();
}

void Strvec::free(){
    if(elements==nullptr)
        return;
    auto p = firstfree;
    while(p!=elements)
        Strvec::alloc.destroy(--p);
    Strvec::alloc.deallocate(elements,cap-elements);
}

void Strvec::reallocate(){
    auto newcapcity = elements?size()*2:1;
    string* newptr = alloc.allocate(newcapcity);
    auto p = newptr;
    for(auto ptr = elements;ptr!=firstfree;ptr++)
        alloc.construct(p++,std::move(*ptr));
    free();
    elements = newptr;
    firstfree = p;
    cap = elements+newcapcity;
}

std::pair<string*,string*> Strvec::alloc_n_copy(const string* start,const string* end){

    auto ptr = alloc.allocate(end-start);
    auto p = ptr;
    for(auto temp=start;temp!=end;temp++){
        alloc.construct(p++,*temp);
    }
    return {ptr,p};
}
