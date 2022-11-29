CLANG_FLAGS=-emit-llvm -c -g
CLANG=clang-6.0

default: ex100-1.bc ex011-2.bc ex015-1.bc ex020-v.bc ex030-2.bc ex050-1.bc ex005-v.bc ex010-1.bc ex011-v.bc ex015-2.bc ex002-1.bc 	ex030-v.bc ex050-2.bc ex010-2.bc ex012-1.bc ex015-v.bc ex002-2.bc ex040-1.bc ex050-v.bc ex010-v.bc ex012-2.bc ex020-1.bc ex002-v.bc 	ex040-2.bc ex005-1.bc ex011-1.bc ex012-v.bc ex020-2.bc ex030-1.bc ex040-v.bc ex005-2.bc 

ex002-1.bc: ex002-1.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex002-2.bc: ex002-2.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex002-v.bc: ex002-v.c
	$(CLANG) $(CLANG_FLAGS) $< 


ex005-1.bc: ex005-1.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex005-2.bc: ex005-2.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex005-v.bc: ex005-v.c
	$(CLANG) $(CLANG_FLAGS) $< 


ex010-1.bc: ex010-1.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex010-2.bc: ex010-2.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex010-v.bc: ex010-v.c
	$(CLANG) $(CLANG_FLAGS) $< 


ex011-1.bc: ex011-1.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex011-2.bc: ex011-2.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex011-v.bc: ex011-v.c
	$(CLANG) $(CLANG_FLAGS) $< 


ex012-1.bc: ex012-1.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex012-2.bc: ex012-2.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex012-v.bc: ex012-v.c
	$(CLANG) $(CLANG_FLAGS) $< 


ex015-1.bc: ex015-1.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex015-2.bc: ex015-2.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex015-v.bc: ex015-v.c
	$(CLANG) $(CLANG_FLAGS) $< 


ex020-1.bc: ex020-1.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex020-2.bc: ex020-2.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex020-v.bc: ex020-v.c
	$(CLANG) $(CLANG_FLAGS) $< 


ex030-1.bc: ex030-1.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex030-2.bc: ex030-2.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex030-v.bc: ex030-v.c
	$(CLANG) $(CLANG_FLAGS) $< 



ex040-1.bc: ex040-1.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex040-2.bc: ex040-2.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex040-v.bc: ex040-v.c
	$(CLANG) $(CLANG_FLAGS) $< 



ex050-1.bc: ex050-1.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex050-2.bc: ex050-2.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex050-v.bc: ex050-v.c
	$(CLANG) $(CLANG_FLAGS) $< 


ex100-1.bc: ex100-1.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex100-2.bc: ex100-2.c
	$(CLANG) $(CLANG_FLAGS) $< 

ex100-v.bc: ex100-v.c
	$(CLANG) $(CLANG_FLAGS) $< 


clean:
	$(RM) *.bc *.*~	 
	$(RM) -r  klee-*
	
