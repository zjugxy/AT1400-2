#pragma once
#include<iostream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<memory>
#include<sstream>
using std::vector;
using std::string;
using std::shared_ptr;
using std::set;
using std::map;
using std::weak_ptr;
class QueryResult{
    public:
    weak_ptr<vector<string>> strs;
    weak_ptr<set<int>> lines;
    std::unique_ptr<int> key;
    QueryResult(shared_ptr<vector<string>> elem1,shared_ptr<set<int>> elem2):strs(elem1),lines(elem2){
    }
    QueryResult(){
    }
};
class TextQuery{
    public:
    TextQuery(std::istream& io){
        strs = std::make_shared<vector<string>>();
        str2set = std::make_shared<map<string,shared_ptr<set<int>>>>();
        std::string line;
        int linenum = 0;
        while(std::getline(io,line)){
            strs->push_back(line);
            std::istringstream stringio(line);
            string singlestr;
            while (stringio>>singlestr)
            {
                if((*str2set)[singlestr]!=nullptr){
                    (*str2set)[singlestr]->emplace(linenum);
                }
                else{
                    (*str2set)[singlestr].reset(new set<int>);
                    (*str2set)[singlestr]->emplace(linenum);
                }
            }
            linenum++;
        }
    }

    QueryResult query(string target){
        if((*str2set)[target]!=nullptr){
            return QueryResult(strs,(*str2set)[target]);
        }
        else{
            return QueryResult();
        }
    }

    private:
    shared_ptr<vector<string>> strs;
    shared_ptr<map<string,shared_ptr<set<int>>>> str2set;
};



void print(std::ostream& io,const QueryResult& qr){
    if(auto ptr = qr.lines.lock()){
        if(auto strptr = qr.strs.lock()){
            for(auto it= ptr->begin();it!=ptr->end();it++){
                io<<"line "<<*it<<":"<<(*strptr)[*it]<<std::endl;
            }
        }
    }
}