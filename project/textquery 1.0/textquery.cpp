#include "textquery.h"

TextQuery::TextQuery(ifstream& file)
{
  LineNo count = 0;
  for(string line; std::getline(file, line);)
    {
      ++count;
      source.push_back(line);
      std::istringstream wordStream(line);
      string word;
      while(wordStream >> word)
        {
          if(wordRows.find(word) == wordRows.end())
            {
              wordRows[word].reset(new set<LineNo>);
            }
          wordRows[word]->insert(count);
        }
    }
}

QueryResult TextQuery::query(const string& word)
{
  static shared_ptr<set<LineNo>> voidSet(new set<LineNo>());

  auto wordMap = wordRows.find(word);

  if(wordMap == wordRows.end())
    {
      return QueryResult(word, source, voidSet);
    }
  else
    {
      return QueryResult(word, source, wordMap->second);
    }
}

QueryResult::QueryResult(const string& sw, const vector<string>& s, shared_ptr<set<LineNo>> rows):
  findWord(sw), source(s), wordRows(rows)
{
}

