#ifndef TEXTQUERY_H
#define TEXTQUERY_H
#include <iostream>
#include <memory>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using std::shared_ptr;
using std::map;
using std::set;
using std::ifstream;
using std::string;
using std::vector;

class QueryResult
{
   using LineNo = size_t;
public:
  vector<string> getSource(){return source;}
  set<LineNo> getSet(){return *wordRows;}
  string getLine(LineNo no){return source.at(no - 1);}
  void print()
  {
    for(auto& rRow : *wordRows)
      {
        std::cout << rRow << std::endl;
      }
  }

  QueryResult() = default;
  QueryResult(const string& sw, const vector<string>& s, shared_ptr<set<LineNo>> rows);
private:
  string findWord;
  vector<string> source;
  shared_ptr<set<LineNo>> wordRows;
};

class TextQuery
{
  using LineNo = size_t;
public:
  TextQuery(ifstream& file);
  QueryResult query(const string& searchWord);
private:
  map<string, shared_ptr<set<LineNo>>> wordRows;
  vector<string> source;
};



#endif // TEXTQUERY_H
