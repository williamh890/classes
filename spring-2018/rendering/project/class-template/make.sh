FILE=cs481_template
pdflatex $FILE.tex
bibtex $FILE.aux
pdflatex $FILE.tex
pdflatex $FILE.tex

