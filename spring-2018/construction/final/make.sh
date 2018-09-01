FILE=final
pdflatex -shell-escape $FILE.tex
bibtex $FILE.aux
pdflatex -shell-escape $FILE.tex
pdflatex -shell-escape $FILE.tex
