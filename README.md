# ft_malloc
## goal of the project
the goal of this project is to understand how the memory is managed by the malloc function and how to optimize it.
 
## compilation
to compile the project, go at the root of the repository and do the command `make`. it will compile to `libft_malloc_$HOSTTYPE.so` and `libft_malloc.so` (link to the first). if `HOSTTYPE` is not set, it will be set to your machine name and your kernel name separated by a `-`

## usage
you can have two usage of the lib. you can either override the normal malloc function in a already compiled program or you can compile your program with the lib , giving you acess to other functions like `show_alloc_mem` or `show_alloc_mem_ex`. in the examples `<folder>` represent the folder containing the compilation results

to override the functions in an already compile program you need to do this command :
 ```
  export LD_LIBRARY_PATH=. LD_PRELOAD=libft_malloc.so
 ```

to compile a program with the lib, you have to add these parameters at the end of your compilation command (for gcc or clang):

```
-L<folder> -lft_malloc
```

## tests
a test program is available at the root. to execute it do the command `make test` and then execute the program that have been compiled with `./tests`

## debug variables
one of the bonus of this project is adding debug environment variable. here is a list of the available debug environment variables
| variable name   | action|
| :------------   | :-----|
| MALLOC_NO_UNMAP | the free function will never free the memory it mapped. active if the variable is set |
| MALLOC_DEBUG_LEVEL | all the functions in the project will print logs in a file named malloc.log. the diffrent log levels available are `NONE` (default) , `ERR`, `WARN`, `INFO`.

## find leaks
since `valgrind` wont work when using this function I added an environment variable that shows if there is still some memory bloc in use at exit. to enable it, you need to set the environment variable `MALLOC_SHOW_LEAKS`
