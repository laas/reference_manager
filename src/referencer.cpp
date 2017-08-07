#include "reference_manager/referencer.h"

#include <cstdlib>
#include <iostream>
#include <vector>

Referencer::Referencer()
{
  m_references = map<string, string>();
}

bool Referencer::add_reference(string id, string ref)
{
  if(!is_referenced(ref))
  {
    for(map<string, string>::iterator it = m_references.begin(); it != m_references.end();)
    {
      if(it->second == id)
        m_references.erase(it->first);
      else
        ++it;
    }

    m_references.insert(make_pair(ref, id));
    return true;
  }
  else
    return false;
}

bool Referencer::remove_reference(string ref)
{
  if(is_referenced(ref))
  {
      m_references.erase(ref);
      return true;
  }
  else
    return false;
}

string Referencer::list_references()
{
  string list;
  for(map<string, string>::iterator it = m_references.begin(); it != m_references.end(); ++it)
    list += it->second + " <=> " + it->first + "\n";

  return list;
}

bool Referencer::get_identifier(string ref, string& id)
{
  if(is_referenced(ref))
  {
    id = m_references[ref];
    return true;
  }
  else
  {
    id  = "";
    return false;
  }
}

bool Referencer::get_reference(string id, string& ref)
{
  ref = "";
  for(map<string, string>::iterator it = m_references.begin(); it != m_references.end(); ++it)
  {
    if(it->second == id)
      ref = it->first;
  }

  if(ref == "")
    return false;
  else
    return true;
}

bool Referencer::is_referenced(string ref)
{
  if(m_references.size())
  {
    if(m_references.count(ref) == 0)
      return false;
    else
      return true;
  }
  else
    return false;
}
