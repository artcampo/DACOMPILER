#include "VisitorPrettyPrinter.hpp"

    virtual void visit(Program const& p) {
        if (this->before(p)) { return; }

        for (auto c: p.classes) {
            c->accept(*this);
        }

        this->after(p);
    }  