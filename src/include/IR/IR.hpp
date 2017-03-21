#pragma once
#include <string>
#include <memory>
#include <cstddef>
#include "IR/IRSubtypes.hpp"
#include "IR/Label.hpp"
#include "IR/Offset.hpp"
#include "IR/MemAddr.hpp"
#include "AST/ASTNodes.hpp"

namespace Compiler{
namespace IR{
namespace Inst{

struct Inst;
struct JumpCond;
struct JumpIncond;
struct LoadI;
struct Load;
struct LoadReg;
struct LoadRegOffs;
struct Store;
struct StoreReg;
struct Arith;
struct Comparison;
struct PtrElem;
struct GetRetVal;
struct SetRetVal;
struct SetPar;
struct Return;
struct ReturnMain;
struct Call;

using PtrInst         = std::unique_ptr<Inst>;
using PtrJumpIncond   = std::unique_ptr<JumpIncond>;
using PtrJumpCond     = std::unique_ptr<JumpCond>;
using PtrLoadI        = std::unique_ptr<LoadI>;
using PtrLoad         = std::unique_ptr<Load>;
using PtrLoadReg      = std::unique_ptr<LoadReg>;
using PtrLoadRegOffs  = std::unique_ptr<LoadRegOffs>;
using PtrStore        = std::unique_ptr<Store>;
using PtrStoreReg     = std::unique_ptr<StoreReg>;
using PtrArith        = std::unique_ptr<Arith>;
using PtrComparison   = std::unique_ptr<Comparison>;
using PtrPtrElem      = std::unique_ptr<PtrElem>;

using PtrGetRetVal    = std::unique_ptr<GetRetVal>;
using PtrSetRetVal    = std::unique_ptr<SetRetVal>;
using PtrSetPar       = std::unique_ptr<SetPar>;
using PtrReturn       = std::unique_ptr<Return>;
using PtrReturnMain   = std::unique_ptr<ReturnMain>;
using PtrCall         = std::unique_ptr<Call>;



struct InstAddress{
  InstAddress(const MemAddr addr)
    :addr_(addr){}
  ~InstAddress() = default;
protected:
  MemAddr addr_;
};

struct InstSrc{
  InstSrc(const Reg src) : src_(src){}
  ~InstSrc() = default;
  Reg RegSrc() const noexcept { return src_;}
protected:
  Reg src_;
};

struct InstSrcSrc{
  InstSrcSrc(const Reg src1, const Reg src2) : src1_(src1), src2_(src2){}
  ~InstSrcSrc() = default;
  Reg RegSrc1() const noexcept { return src1_;}
  Reg RegSrc2() const noexcept { return src2_;}
protected:
  Reg src1_;
  Reg src2_;
};

struct InstDst {
  InstDst(const Reg reg_dst) : dst_(reg_dst){};
  ~InstDst() = default;

  Reg RegDst() const noexcept { return dst_;}
protected:
  Reg dst_;
};

struct InstVal {
  InstVal( const NodeValue val) : val_(val){};
  ~InstVal() = default;

  NodeValue Value() const noexcept { return val_;}
protected:
  NodeValue val_;
};

struct InstOffset {
  InstOffset(const Offset offset) : offset_(offset){};
  ~InstOffset() = default;

  const Offset GetOffset() const noexcept { return offset_;}
protected:
   Offset offset_;
};


//Interface
struct Inst{
  Inst(){};
  virtual ~Inst() = default;

  virtual std::string str() const noexcept = 0;
};

struct BinaryOp : public Inst, public InstDst, public InstSrcSrc{
  BinaryOp(const Reg reg_dst, const Reg src1, const Reg src2)
  : InstDst(reg_dst), InstSrcSrc(src1, src2){};
  virtual ~BinaryOp() = default;

  virtual std::string str() const noexcept = 0;
};

struct UnaryOp : public Inst, public InstDst, public InstSrc{
  UnaryOp(const Reg reg_dst, const Reg src1)
  : InstDst(reg_dst), InstSrc(src1){};
  virtual ~UnaryOp() = default;

  virtual std::string str() const noexcept = 0;
};


}//end namespace Inst
}//end namespace IR
}//end namespace Compiler

#include "Inst/Jumps.hpp"
#include "Inst/MemAccess.hpp"
#include "Inst/Ops.hpp"
#include "Inst/Functions.hpp"
