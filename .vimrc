nnoremap <F1> :Make<cr>
nnoremap <F2> :ter ++open ./build/testspritegrid -s<cr>
nnoremap <F3> :Termdebug _build/spritegrid<cr>
nnoremap <F4> :ter ++close ./build/spritegrid<cr>

packadd termdebug
let g:termdebug_wide = 1

let g:syntastic_cpp_compiler_options = '-DDEBUG -std=c++17'
let g:syntastic_cpp_include_dirs = [ 'build', '/usr/include/SDL2' ]
