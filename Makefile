.PHONY: compile_materials prerequisites clean format-code FORCE

LATEXMK = latexmk
LATEX_FLAGS = -xelatex -shell-escape -interaction=nonstopmode -halt-on-error -file-line-error

compile_materials: MATERIALS.pdf

prerequisites: MATERIALS.pdf

MATERIALS.pdf: MATERIALS.tex _latex/preamble.tex _latex/abstract.tex FORCE
	$(LATEXMK) $(LATEX_FLAGS) MATERIALS.tex

FORCE:

clean:
	$(LATEXMK) -C MATERIALS.tex
	rm -rf _minted _minted-MATERIALS

format-code:
	fd -e c -e cpp -e h -e hpp -x clang-format --style="{BasedOnStyle: llvm, IndentWidth: 4}" -i
