#ifndef __J_CC_OPTIMIZE_ROUTINES_H__
#define __J_CC_OPTIMIZE_ROUTINES_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <optimize/fold_expr.h>

namespace libjcc
{
    typedef std::function<void(std::shared_ptr<libjcc::AST>)> ASTOptimizeRoutine;

    class PreliminaryOptimizer
    {
    public:
        void run(std::shared_ptr<libjcc::AST> ast)
        {
            for (auto routine : m_routines)
            {
                routine(ast);
            }
        }

        void add_routine(ASTOptimizeRoutine routine)
        {
            m_routines.push_back(routine);
        }

        std::vector<ASTOptimizeRoutine> m_routines;
    };

    class Optimizer
    {
    public:
        void run(std::shared_ptr<libjcc::AST> ast)
        {
            for (auto routine : m_routines)
            {
                routine(ast);
            }
        }

        void add_routine(ASTOptimizeRoutine routine)
        {
            m_routines.push_back(routine);
        }

        std::vector<ASTOptimizeRoutine> m_routines;
    };
}

#endif // __J_CC_OPTIMIZE_ROUTINES_H__