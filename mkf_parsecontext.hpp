#ifndef MKF_PARSECONTEXT_HPP_INCLUDED
#define MKF_PARSECONTEXT_HPP_INCLUDED


#include"mkf_book.hpp"
#include"mkf_node.hpp"
#include"mkf_cursor.hpp"
#include"mkf_ctype.hpp"


namespace mkf{




class
ParseContext
{
  Node*  root;

  std::vector<const Definition*>        defchain;
  std::vector<const Definition*>  error_defchain;

  const pp::Character*  error_p;

  const Node*  get(const Definition&  def, const pp::String&  s);

public:
  const Book&  book;

   ParseContext(const Book&  book_);
  ~ParseContext();


  const Node*  operator()(                      const pp::String&  s);
  const Node*  operator()(const char*  defname, const pp::String&  s);

  Node*  release_root();

  void  push_error(const pp::Character*  p);

  bool  enter(const char*  defname, const pp::Character*&  p, Node&  node);

  void  print() const;

};


}


#endif




