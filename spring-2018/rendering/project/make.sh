FILE=project0
pdflatex $FILE.tex
bibtex $FILE.aux
pdflatex $FILE.tex
pdflatex $FILE.tex

