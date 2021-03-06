#include"cmplr_declaration.hpp"
#include"cmplr_function.hpp"
#include"cmplr_precontext.hpp"




void
Declaration::
read(const mkf::Node&  src, PreContext&  prectx)
{
  mkf::Cursor  cur(src);

  storage_kind = prectx.function? StorageKind::local
                                : StorageKind::global;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "function_declaration")
        {
          auto  fn = new Function;

          fn->read(nd,prectx);

          reset(fn);
        }

      else
        if(nd == "object_declaration")
        {
          read_object_declaration(nd,prectx);
        }


      cur.advance();
    }
}




void
Declaration::
read_object_declaration(const mkf::Node&  src, PreContext&  prectx)
{
  mkf::Cursor  cur(src);

  bool  constant = false;

    while(!cur.test_ended())
    {
      auto&  nd = cur.get();

        if(nd == "identifier")
        {
          nd.collect_characters(name);
        }

      else
        if(nd == "type")
        {
          type.read(nd);
        }

      else
        if(nd == "const")
        {
          constant = true;
        }

      else
        if(nd == "expression")
        {
          literal.reset(new expression::Node(nd,prectx));
        }

      else
        if(nd == "literal_object")
        {
          literal.read(nd,prectx);
        }

      else
        if(nd == "static")
        {
          storage_kind = StorageKind::local_static;
        }


      cur.advance();
    }


    if(constant)
    {
        try
        {
          auto  cs = literal.make_constant(prectx);

          cs.print();

          printf("\n定数化できました\n");
        }


        catch(Constant::Error&  err)
        {
          printf("定数化できませんでした\n");

          throw;
        }
    }
}




