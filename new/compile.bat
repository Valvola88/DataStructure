clang.exe -o dlist.exe .\src\dlist.c .\src\main\main_dlist.c -I .\include\
clang.exe -o llist_int.exe .\src\llist.c .\src\main\main_int_llist.c  -I .\include\
clang.exe -o llist_string.exe .\src\llist.c .\src\main\main_string_llist.c  -I .\include\
clang.exe -o set_ll.exe .\src\set_ll.c .\src\llist.c .\src\main\main_set_ll.c  -I .\include\
clang.exe -o dictionary.exe .\src\dictionary.c .\src\set_ll.c .\src\llist.c .\src\main\main_dictionary.c  -I .\include\