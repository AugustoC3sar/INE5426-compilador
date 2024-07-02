#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "SyntaxAnalyzer.h"

std::string array(std::string type, std::string lexval) {
    return "TODO";
}

void semanticActionAddType(SymbolTable *symbolTable,  std::string identVal, Production TYPE) {
    symbolTable->addTokenType(identVal, TYPE.type);
}

void semanticActionAddTypeValue(Production TYPE, std::string typeValue) {
    TYPE.type = typeValue;
}

void semanticActionInheriteType(Production ARRAYVARDECL, Production TYPE) {
    ARRAYVARDECL.inh_type = TYPE.type;
}

void semanticActionSynthesizedType(Production VARDECL, Production ARRAYVARDECL) {
    VARDECL.type = ARRAYVARDECL.type;
}

void semanticActionArrayInheritedType(Production ARRAYVARDECL1, Production ARRAYVARDECL, std::string lexval) {
    ARRAYVARDECL1.inh_type = array(ARRAYVARDECL.inh_type, lexval);
}

void semanticActionArraySynthesizedType(Production ARRAYVARDECL, Production ARRAYVARDECL1) {
    ARRAYVARDECL.type = ARRAYVARDECL1.type;
}

void semanticActionArraySynthesizeType(Production ARRAYVARDECL) {
    ARRAYVARDECL.type = ARRAYVARDECL.inh_type;
}

#endif
