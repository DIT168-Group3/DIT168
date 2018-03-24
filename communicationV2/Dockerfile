FROM alpine:3.7 as builder
MAINTAINER Martin Chukaleski guschuma@student.gu.se
RUN apk update && \
    apk --no-cache add \
        ca-certificates \
        cmake \
        g++ \
        make && \
    apk add libcluon --no-cache --repository https://chrberger.github.io/libcluon/alpine/v3.7 --allow-untrusted
ADD . /opt/sources
WORKDIR /opt/sources
RUN cd /opt/sources && \
    mkdir build4 && \
    cd build4 && \
    cmake -D CMAKE_BUILD_TYPE=Release .. && \
    make && make test && cp communication.Sender /tmp && cp communication.Reciever /tmp

# Deploy.
FROM alpine:3.7
MAINTAINER Martin Chukaleski guschuma@student.gu.se
RUN apk update && \
    apk add libcluon --no-cache --repository https://chrberger.github.io/libcluon/alpine/v3.7 --allow-untrusted && \
    mkdir /opt
WORKDIR /opt
COPY --from=builder /tmp/communication.Sender .
COPY --from=builder /tmp/communication.Reciever .
