namespace Compiler{
namespace IR{
namespace Inst{


struct Arith : public BinaryOp{
  Arith(const Reg reg_dst, const Reg src1, const Reg src2, const ArithType op)
  : BinaryOp(reg_dst, src1, src2), op_(op){};
  virtual ~Arith() = default;

  virtual std::string str() const noexcept{
    return std::string("%")  + std::to_string(dst_)
         + std::string(" = %") + std::to_string(src1_) + std::string(" ")
         + Compiler::IR::str(op_) + std::string(" %")+ std::to_string(src2_);
  }
protected:
  ArithType op_;
};

struct Comparison : public BinaryOp{
  Comparison(const Reg reg_dst, const Reg src1, const Reg src2, const CompType op)
  : BinaryOp(reg_dst, src1, src2), op_(op){};
  virtual ~Comparison() = default;

  virtual std::string str() const noexcept{
    return std::string("%")  + std::to_string(dst_)
         + std::string(" = %") + std::to_string(src1_) + std::string(" ")
         + Compiler::IR::str(op_) + std::string(" %")+ std::to_string(src2_);
  }
protected:
  CompType op_;
};


struct PtrElem : public Inst, public InstAddress, public InstDst{
  PtrElem(const Reg reg_dst, const MemAddr addr)
    : InstAddress(addr), InstDst(reg_dst){}
  virtual ~PtrElem() = default;

  virtual std::string str() const noexcept{
    return std::string("%")  + std::to_string(dst_)
         + std::string(" = PtrElem( ")
         + addr_.str() + std::string(")");
  }
};

}//end namespace Inst
}//end namespace IR
}//end namespace Compiler
