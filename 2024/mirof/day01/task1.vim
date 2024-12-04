open input

" Put columns one under another
normal w
execute 'normal!' "\<C-V>"
normal Gwe
normal x
normal G
normal o
normal p

" Sort both columns
1,1000sort
1001,2000sort

" Put columns back to each other
execute 'normal!' "\<C-V>"
normal Gwe
normal x
normal gg
normal e
normal l
normal p

" Subtract all pairs
%s/\v(\d+)\s+(\d+)/\=abs(submatch(1) - submatch(2))/

" Take all numbers and sum them
let g:sum = 0
g/\d\+/let g:sum += str2nr(getline('.'))
echo sum
