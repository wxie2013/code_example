" ~/.config/nvim/init.vim

" --- Basic Editor Settings ---
set nocompatible            " Be iMproved, not compatible with old vi
syntax on                   " Enable syntax highlighting
set number                  " Show line numbers
set tabstop=4               " Tab width set to 4 spaces
set shiftwidth=4            " Indent width set to 4 spaces
set expandtab               " Convert tabs to spaces
set autoindent              " Copy indent from previous line
set smartindent             " Smart auto-indent for C-like languages
set hlsearch                " Highlight search results
set incsearch               " Show search results as you type
set ignorecase              " Ignore case in search patterns
set smartcase               " Override ignorecase if search pattern contains uppercase letters
set softtabstop=4           " Allow smarttab to backspace over 'tabstop' number of spaces
set undofile                " Maintain undo history across sessions
set clipboard=unnamedplus   " Use system clipboard

" --- Leader Key ---
let mapleader = " "         " Set leader key to spacebar

" --- C++ Specific Settings and Commands ---
autocmd FileType cpp setlocal cindent
autocmd FileType cpp setlocal cinoptions=:0,t0,l1,g0,h0,W0,m1,j0,c1,(0,u0,s0,fo0

" Simple C++ compilation and execution (assumes g++ is in your PATH)
" Use <leader>b to compile and <leader>r to run
autocmd FileType cpp nnoremap <buffer> <leader>b :!g++ % -o %< -std=c++17<CR>
autocmd FileType cpp nnoremap <buffer> <leader>r :!./%<<CR>

" --- Colorscheme ---
" You can choose any colorscheme you like. 'default' is a good starting point.
" To use a different colorscheme, ensure it's installed or available on your system.
colorscheme default

