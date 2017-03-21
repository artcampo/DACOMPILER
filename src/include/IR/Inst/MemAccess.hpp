namespace Compiler{
namespace IR{
namespace Inst{


struct LoadI : public Inst, public InstDst, public InstVal{
  LoadI(const Reg reg_dst, const NodeValue val)
    : InstDst(reg_dst), InstVal(val){};
  virtual ~LoadI() = default;

  virtual std::string str() const noexcept{
    return std::string("%")  + std::to_string(dst_)
         + std::string(" = LoadI(") + std::to_string(val_)
         + std::string(")") ;
  }
};

struct Load : public Inst, public InstDst, public InstAddress{
  Load(const Reg reg_dst, const MemAddr addr)
    : InstDst(reg_dst), InstAddress(addr){};
  virtual ~Load() = default;

  virtual std::string str() const noexcept{
    return std::string("%")  + std::to_string(dst_)
         + std::string(" = Load [") + addr_.str()
         + std::string("]");
  }
};


struct LoadReg : public Inst, public InstDst, public InstSrc{
  LoadReg(const Reg reg_dst, const Reg reg_src)
    : InstDst(reg_dst), InstSrc(reg_src){};
  virtual ~LoadReg() = default;

  virtual std::string str() const noexcept{
    return std::string("%")  + std::to_string(dst_)
         + std::string(" = Load [ %") + std::to_string(src_)
         + std::string("]");
  }
};


struct LoadRegOffs : public Inst, public InstDst, public InstSrc, public InstOffset{
  LoadRegOffs(const Reg reg_dst, const Reg reg_src, const Offset offset)
    : InstDst(reg_dst), InstSrc(reg_src), InstOffset(offset){};
  virtual ~LoadRegOffs() = default;

  virtual std::string str() const noexcept{
    return std::string("%")  + std::to_string(dst_)
         + " = Load [ %" + std::to_string(src_)
         + " + " + offset_.str()
         + "]";
  }
};


struct Store : public Inst, public InstSrc, public InstAddress{
  Store(const Reg src, const MemAddr addr)
    : InstSrc(src), InstAddress(addr){};
  virtual ~Store() = default;

  virtual std::string str() const noexcept{
    return std::string("store %")  + std::to_string(src_)
         + std::string(" to [") + addr_.str()
         + std::string("]") ;
  }
};

struct StoreReg : public Inst, public InstSrcSrc{
  StoreReg(const Reg src1, const Reg src2)
    : InstSrcSrc(src1, src2){};
  virtual ~StoreReg() = default;

  virtual std::string str() const noexcept{
    return std::string("store %")  + std::to_string(src1_)
         + std::string(" to [%") + std::to_string(src2_)
         + std::string("]") ;
  }
};

}//end namespace Inst
}//end namespace IR
}//end namespace Compiler
