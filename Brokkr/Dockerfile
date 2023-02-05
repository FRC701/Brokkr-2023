# 1. Base image
#FROM python:3.8.3-slim-buster
FROM python:3.9 as builder
RUN apt-get update && apt-get install -y git
RUN apt-get update && apt-get install -y pip
# 👇 STYLE YOUR DOCKERFILE LIKE A PRO
#RUN pip install -U \
 #   pip \
  #  setuptools \
   # wheel \
    

# Copy the requirements file to the container
#COPY requirements.txt ./

# Install the required packages
#RUN pip install -r requirements.txt

# Clone the wpiformat repository from GitHub
RUN git clone https://github.com/wpilibsuite/styleguide.git

WORKDIR /styleguide/wpiformat

RUN useradd -m -r user && \
    chown user /styleguide/wpiformat

RUN pip install -e .

COPY ./src src/

COPY .styleguide .
# Copy the clang files from the local directory to the container
COPY .clang-format .
COPY .clang-tidy .

ENTRYPOINT ["python", "-m"]

#usage: sudo docker run --rm linter wpiformat -v