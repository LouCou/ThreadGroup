# A simple thread group

The user instanciates a ThreadGroup parameterized to process a maximum number of threads at a time.  
The user then *adds* to the ThreadGroup functions and their arguments.  
This *add* method blocks until there is room to launch the function in a thread.

# TODO
- void add(void f(void&ast;), void&ast; arg) is notuser friendly, use some std::function and templates
- measure the performance
- fix Makefile so main.cpp is rebuilt when ThreadGroup changes
