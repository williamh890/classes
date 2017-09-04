install.packages("bitops", repos=NULL, type="source")
install.packages("caTools", repos=NULL, type="source")  # install external package
library(caTools)           # external package providing write.gif function
jet.colors <- colorRampPalette(c("#00007F", "blue", "#007FFF", "cyan", "#7FFF7F",
                                                                  "yellow", "#FF7F00", "red", "#7F0000"))
dx <- 2560 # define width
dy <- 1440                  # define height
C <- complex( real=rep(seq(-2.2, 1.0, length.out=dx), each=dy ),
                           imag=rep(seq(-1.2, 1.2, length.out=dy), dx ) )
C <- matrix(C,dy,dx)       # reshape as square matrix of complex numbers
start <- 10
end <- 20
Z <- 0                     # initialize Z to zero
X <- array(0, c(dy,dx,end)) # initialize output 3D array
for (k in 0:end) {          # loop with 20 iterations
      Z <- Z^2+C               # the central difference equation
  X[,,k] <- exp(-abs(Z))   # capture results
}
write.gif(X, "Mandelbrot.gif", col=jet.colors, delay=100)
