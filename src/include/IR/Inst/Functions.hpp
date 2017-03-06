namespace Compiler{
namespace IR{
namespace Inst{


struct GetRetVal : public Inst, public InstDst {
  GetRetVal(const Reg reg_dst) : InstDst(reg_dst){};
  virtual ~GetRetVal() = default;

  virtual std::string str() const noexcept{
    return "%" + std::to_string(dst_) + " = GetRetVal()";
  }
};


struct SetRetVal : public Inst, public InstSrc{
  SetRetVal(const Reg src) : InstSrc(src){};
  virtual ~SetRetVal() = default;

  virtual std::string str() const noexcept{
    return "SetRetVal( %"  + std::to_string(src_) + ")";
  }
};


struct SetPar : public Inst, public InstSrc{
  SetPar(const Reg src) : InstSrc(src){};
  virtual ~SetPar() = default;

  virtual std::string str() const noexcept{
    return "SetPar( %"  + std::to_string(src_) + ")";
  }
};


struct Return : public Inst{
  Return(): Inst(){};
  virtual ~Return() = default;

  virtual std::string str() const noexcept{
    return "Return";
  }
};

struct ReturnMain : public Inst{
  ReturnMain(): Inst(){};
  virtual ~ReturnMain() = default;

  virtual std::string str() const noexcept{
    return "ReturnMain";
  }
};

struct Call : public Inst, public InstAddress{
  Call(const MemAddr addr) : InstAddress(addr){};
  virtual ~Call() = default;

  virtual std::string str() const noexcept{
    return "call [" + addr_.str() + "]";
  }
};


}//end namespace Inst
}//end namespace IR
}//end namespace Compiler
