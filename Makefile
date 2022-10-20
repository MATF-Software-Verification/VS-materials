.PHONY: compile_materials

compile_materials: 
	./make_materials

prerequisites: compile_materials

MATERIALS.pdf: prerequisites 

