SOURCE=$(lastword $(filter-out README.md, $(wildcard *.md)))
BASE?=$(basename $(SOURCE))
TARGET?=$(BASE).pdf

%.pdf: %.tex
	rm -f $*.aux
	lualatex $<

%.tex: %.md
	pandoc --citeproc --csl=chicago-author-date-de-adapted.csl --data-dir=. -t latex --template ti2 -s $< -o $@

all: $(TARGET)

clean:
	rm -f *.aux *.dvi *.log *.bbl *.blg *.toc *.out \
	      *.nav *.snm *.pdf *.tex *.run.xml *.bcf


