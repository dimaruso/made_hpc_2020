#!/bin/bash

docker build --tag=dimarussio/mult .  

docker run --rm dimarussio/mult 512 8  
docker run --rm dimarussio/mult 1024 4  
docker run --rm dimarussio/mult 2048 2  
docker run --rm dimarussio/mult 4096 1  

docker rmi dimarussio/mult
