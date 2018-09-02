mkdir dependencies

git clone --depth 1 https://github.com/emil-e/rapidcheck.git dependencies/rapidcheck
curl -L https://github.com/catchorg/Catch2/releases/download/v2.3.0/catch.hpp > ./tests/catch.hpp
