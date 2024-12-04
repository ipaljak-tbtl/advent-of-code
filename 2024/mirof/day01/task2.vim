open input

" Put columns one under another and remove spaces
normal w
execute 'normal!' "\<C-V>"
normal Gwe
normal x
normal G
normal o
normal p
normal gg
%s/ //g

" Sort and add to sum if there are same lines in a row 
sort
let g:sum = 0
g/\(^\d\+\)\n\1/let g:sum += str2nr(getline('.'))
echo sum
