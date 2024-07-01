## SDD

| Produção | Definições |
|----------|------------|
| PARAMLIST -> TYPE ident PARAMLIST' | addType(ident.entry, TYPE.type) | 
| TYPE -> int | TYPE.type = int |
| TYPE -> float | TYPE.type = int |
| TYPE -> string |  TYPE.type = int |
| VARDECL -> TYPE ident ARRAYVARDECL | ARRAYVARDECL.inh_type = TYPE.type VARDECL.type = ARRAYVARDECL.type addEntry(ident.entry, VARDECL.type) |
| ARRAYVARDECL -> [int_constant] ARRAYVARDECL1 | ARRAYVARDECL1.inh_type = array(ARRAYVARDECL.inh_type, int_constant.lexval) ARRAYVARDECL.type = ARRAYVARDECL1.type |
| ARRAYVARDECL -> & | ARRAYVARDECL.type = ARRAYVARDECL.inh_type |

## SDT

PARAMLIST -> TYPE ident PARAMLIST' { addType(ident.entry, TYPE.type)  }
TYPE -> int { TYPE.type = int }
TYPE -> float { TYPE.type = float }
TYPE -> string { TYPE.type = string }
VARDECL -> TYPE ident { ARRAYVARDECL.inh_type = TYPE.type } ARRAYVARDECL { VARDECL.type = ARRAYVARDECL.type } { addEntry(ident.entry, VARDECL.type) }
ARRAYVARDECL -> [int_constant]  { ARRAYVARDECL1.inh_type = array(ARRAYVARDECL.inh_type, int_constant.lexval) } ARRAYVARDECL1 { ARRAYVARDECL.type = ARRAYVARDECL1.type }
ARRAYVARDECL -> & { ARRAYVARDECL.type = ARRAYVARDECL.inh_type }

Nós nomearemos as ações semânticas da seguinte maneira:

SemanticActionAddType = { addType(ident.entry, TYPE.type) }
SemanticActionAddTypeValue = { TYPE.type = int }
SemanticActionAddTypeValue = { TYPE.type = float }
SemanticActionAddTypeValue = { TYPE.type = string }
SemanticActionInheritdType = { ARRAYVARDECL.inh_type = TYPE.type }
SemanticActionSynthesizedType = { VARDECL.type = ARRAYVARDECL.type }
SemanticActionArrayInheritedType = { ARRAYVARDECL1.inh_type = array(ARRAYVARDECL.inh_type, int_constant.lexval) }
SemanticActionArraySynthesizedType = { ARRAYVARDECL.type = ARRAYVARDECL1.type }
SemanticActionArraySynthesizeType = { ARRAYVARDECL.type = ARRAYVARDECL.inh_type }
