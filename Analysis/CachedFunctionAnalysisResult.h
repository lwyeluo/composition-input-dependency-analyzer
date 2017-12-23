#pragma once

#include "FunctionInputDependencyResultInterface.h"

#include <unordered_set>

namespace llvm {
class Function;
class BasicBlock;
class Instruction;
}

namespace input_dependency {

class CachedFunctionAnalysisResult final : public FunctionInputDependencyResultInterface
{
public:
    using BasicBlocks = std::unordered_set<llvm::BasicBlock*>;
    using Instructions = std::unordered_set<llvm::Instruction*>;

public:
    CachedFunctionAnalysisResult(llvm::Function* F);

    void analize();
    
public:
    llvm::Function* getFunction() override;
    const llvm::Function* getFunction() const override;
    bool isInputDepFunction() const override;
    void setIsInputDepFunction(bool isInputDep) override;
    bool isInputDependent(llvm::Instruction* instr) const override;
    bool isInputDependent(const llvm::Instruction* instr) const override;
    bool isInputIndependent(llvm::Instruction* instr) const override;
    bool isInputIndependent(const llvm::Instruction* instr) const override;
    bool isInputDependentBlock(llvm::BasicBlock* block) const override;
    FunctionSet getCallSitesData() const override;
    FunctionCallDepInfo getFunctionCallDepInfo(llvm::Function* F) const override;

    long unsigned get_input_dep_blocks_count() const override;
    long unsigned get_input_indep_blocks_count() const override;
    long unsigned get_unreachable_blocks_count() const override;
    long unsigned get_unreachable_instructions_count() const override;
    long unsigned get_input_dep_count() const override;
    long unsigned get_input_indep_count() const override;
    long unsigned get_input_unknowns_count() const override;

private:
    llvm::Function* m_F;
    bool m_is_inputDep;
    BasicBlocks m_inputDepBlocks;
    BasicBlocks m_inputInDepBlocks;
    BasicBlocks m_unreachableBlocks;
    Instructions m_inputDepInstructions;
    Instructions m_inputIndepInstructions;
    Instructions m_unknownInstructions;
    Instructions m_unreachableInstructions;
}; // class CachedFunctionAnalysisResult

} // namespace input_dependency
