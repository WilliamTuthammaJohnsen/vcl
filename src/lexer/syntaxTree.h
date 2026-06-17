#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include "lexerTokens.h"

class Expr {

};

class Binary : Expr {
    Expr _left;
    Token _operator;
    Expr _right;

    Binary (Expr left, Token opfor, Expr right) {
        _left = left;
        _operator = opfor;
        _right = right;
    }
};

#endif