
# requirements

the cpp portion of this script requires img-processor.out which can be built runnign `make`
in the processor-cpp directory. Also `PIL` and `numpy` need to be pip installed.

all python scripts are writen in `python 3.6`

### note
calling instructions for scripts can be found by passing no arguments to the scripts

# processor.py

this selects between the cpp processor, which takes and ouputs binaries, or the python processor,
which takes images. I've tested only whith jpg's. 

# jpg-to-bin.py

takes a jpg and makes a bin file that feeds into the cpp processor


# Results

IO is killer and ended up being the main time consumer, at least when dealing with the c++ code. 
My fastest code, not including io, was the pragma c++ code, but this is in my mind impractical 
because the bottleneck at that point would have undoutably been IO. I unfortunetly never got the
IO in c++ figured, but did start looking into rogersce/cnpy, which is a library for loading in numpy
binary files. 

The fastest method including io ended up just being the plain numpy code. Once you know numpy its 
the easiest to write as well. The only drawback is that numpy is complicated, but if your doing this
type of work a lot, this would be a greate solution. 



