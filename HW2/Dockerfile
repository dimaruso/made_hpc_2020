FROM ubuntu:18.04
LABEL MAINTAINER dimarussio@gmail.com

RUN apt-get update && \
    apt-get install -y g++ \
                       bash
WORKDIR /Matrix
COPY Matrix.h Matrix.cpp test.cpp /Matrix/
RUN g++ -O3 -o multiply_O3 test.cpp Matrix.cpp  

ENTRYPOINT ["./multiply_O3"]
