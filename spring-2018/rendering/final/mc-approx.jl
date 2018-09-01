samples = [1.73, 1.35, 1.62, 0.17, 1.39, 0.33, 1.03, 0.66, 0.90, 1.19]

f(x) = x^2

integral_estimate = sum(f.(samples)) / length(samples)

println.([
    "estimate $integral_estimate",
    "mean of samples $(mean(samples))",
    "std of samples $(std(samples))"
])
