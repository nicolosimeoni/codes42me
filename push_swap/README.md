# push_swap

A C sorting project from the **42 curriculum**. Given a list of unique integers,
`push_swap` prints instructions to sort them using two stacks and the permitted
operations (`sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`).

## Approach

For up to five numbers, use dedicated small-stack sorting. Otherwise, push two
numbers to stack B, then repeatedly select the cheapest element to transfer:
consider both rotation directions and combine simultaneous rotations via `rr`
or `rrr`. After reducing A to three numbers, sort those and reinsert elements
from B. Finally rotate the minimum element to the top of A.

