# uses a multi-stage build strategy

# calculus build stage
# takes the base alpine image and enhances it with the build time dependencies
FROM alpine:3.19.0

RUN apk update && apk add --no-cache build-base cmake boost1.82-dev=1.82.0-r3 openssl-dev wt=4.10.0-r0 wt-dev=4.10.0-r0

WORKDIR /calculus
COPY src/ ./src/
COPY CMakeLists.txt .

WORKDIR /calculus/build
RUN cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build . --parallel 4

# # calculus run stage
# FROM alpine:3.19.0
# RUN apk update && apk add --no-cache curl libstdc++ boost1.82-program_options=1.82.0-r3 boost1.82-filesystem=1.82.0-r3 boost1.82-log=1.82.0-r3 boost1.82-log_setup=1.82.0-r3
# RUN addgroup -S ludger && adduser -S ludger -G ludger
# USER ludger:ludger
# COPY --chown=ludger:ludger --from=build ./calculus/bin/calculus /app/
# COPY --chown=ludger:ludger ./calculus/bin/calculus /app/
# RUN mkdir -p /app/dat
# RUN chmod -R 755 /app/dat/
# RUN mkdir -p /app/res
# RUN chmod -R 755 /app/res/

WORKDIR /calculus/bin
RUN mkdir dat
WORKDIR /calculus/bin/dat
RUN touch test.txt
WORKDIR /calculus/bin

# USER ludger:ludger
# ENTRYPOINT [ "./calculus", "--docroot ./dat", "--http-address 0.0.0.0", "--http-port 9090"]
ENTRYPOINT [ "./calculus"]