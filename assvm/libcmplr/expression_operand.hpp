#ifndef EXPRESSION_OPERAND_HPP_INCLUDED
#define EXPRESSION_OPERAND_HPP_INCLUDED


#include<string>
#include"cmplr_declaration.hpp"
#include"cmplr_context.hpp"
#include"cmplr_type.hpp"
#include"expression_foldresult.hpp"
#include"mkf_node.hpp"




namespace expression{
struct Node;
}


using NodeList = std::vector<expression::Node>;


struct
ArgumentList
{
  NodeList*  node_list;

  constexpr ArgumentList(NodeList*  ls): node_list(ls){}

};


struct
ExpressionList
{
  NodeList*  node_list;

  constexpr ExpressionList(NodeList*  ls): node_list(ls){}

};


struct Initializer;


namespace expression{


enum class
OperandKind
{
  null,

  character,
  integer,
  string,
  identifier,
  expression,
  expression_list,
  argument_list,
  subscript,

};


struct Element;
struct Node;


struct
Subscript
{
  Node*  nd;

  constexpr Subscript(Node*  nd_): nd(nd_){};

};


struct
Operand
{
  OperandKind  kind;

  union Data{
    uint32_t  i;

    char16_t  c;

    std::string*  id;
    std::u16string*  s;

    Node*  nd;

    NodeList*  ndls;

  } data;


  Operand();
  Operand(std::string*  id);
  Operand(char16_t  c);
  Operand(std::u16string*  s);
  Operand(uint32_t  i);
  Operand(Node*  nd);
  Operand(Initializer&&  init);
  Operand(const ArgumentList&  args);
  Operand(const ExpressionList&  exprs);
  Operand(const Subscript&  subsc);
  Operand(const mkf::Node&  src, PreContext&  prectx);
  Operand(const Operand&  rhs);
  Operand(Operand&&  rhs) noexcept;
  ~Operand();


  Operand&  operator=(const Operand&   rhs);
  Operand&  operator=(      Operand&&  rhs) noexcept;

  void  clear();

  void  reset(uint32_t  i);
  void  reset(char16_t  c);
  void  reset(std::string*  id);
  void  reset(std::u16string*  s);
  void  reset(Node*  nd);
  void  reset(Initializer&&  init);
  void  reset(const ArgumentList&  args);
  void  reset(const ExpressionList&  exprs);
  void  reset(const Subscript&  subsc);

  void  print(FILE*  f=stdout) const;

  FoldResult  fold(FoldContext&  ctx) const;

  Type  compile(Context&  ctx) const;

  void  read(const mkf::Node&  src, PreContext&  prectx);

  static uint32_t          read_integer_literal(const mkf::Node&  src);
  static char16_t        read_character_literal(const mkf::Node&  src);
  static std::u16string     read_string_literal(const mkf::Node&  src);

};


}


#endif




