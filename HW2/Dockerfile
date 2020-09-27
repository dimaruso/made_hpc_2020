FROM ubuntu:18.04
MAINTAINER dimarussio@gmail.com

RUN apt-get update && \
    apt-get install -y g++ \
                       make \
                       bash
WORKDIR /Matrix
COPY Matrix.h Matrix.cpp test.cpp /Matrix/

ENTRYPOINT ["/bin/bash", "-l", "-c"]
CMD ["/bin/bash"]
