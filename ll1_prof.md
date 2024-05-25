# LL1 Grammar Prof

In order for a grammar to be considered LL1, for all pairs of productions A -> B, A -> C the following must be true:

```math
FIRST(B) \cap FIRST(C) = NULL_SET
if FIRST(B) \contains \epsilon, then FIRST(C) \intersect LAST(A) = NULL_SET
if FIRST(C) \contains \epsilon, then FIRST(B) \intersect LAST(A) = NULL_SET
```