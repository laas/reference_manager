#include <string>
#include <map>

#ifndef REFERENCER_H
#define REFERENCER_H

using namespace std;

class Referencer
{
public:
  Referencer();
  ~Referencer() {};

  bool add_reference(string id, string ref);
  bool remove_reference(string ref);

  string list_references();

  bool get_identifier(string ref, string& id);
  bool get_reference(string id, string& ref);
  bool is_referenced(string ref);
private:
  map<string, string> m_references;
};

#endif
