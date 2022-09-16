# A C++ Example with Docker

You'll need Docker installed.  For Windows, follow along here:

    https://docs.docker.com/desktop/windows/wsl/


## Run this project

From a bash-like command line (WSL on Windows), start by cloning the repo:

    ```bash
    $ git clone git@github.com:dougvanhorn/cplusplus.git
    ```

Next we will build and run the container.  This will take a bit of time the first time through, as
you will need to download the ubuntu image and install some software.  It will be much quicker on
subsequent runs.

    ```bash
    $ ./up
    [+] Building 0.1s (10/10) FINISHED
    => [internal] load build definition from Dockerfile                                                                                         0.0s
    => => transferring dockerfile: 32B                                                                                                          0.0s
    => [internal] load .dockerignore                                                                                                            0.0s
    => => transferring context: 2B                                                                                                              0.0s
    => [internal] load metadata for docker.io/library/ubuntu:22.04                                                                              0.0s
    => [internal] load build context                                                                                                            0.0s
    => => transferring context: 36B                                                                                                             0.0s
    => [1/5] FROM docker.io/library/ubuntu:22.04                                                                                                0.0s
    => CACHED [2/5] COPY setup-ubuntu.sh /tmp/setup-ubuntu.sh                                                                                   0.0s
    => CACHED [3/5] RUN chmod 755 /tmp/setup-ubuntu.sh                                                                                          0.0s
    => CACHED [4/5] RUN /tmp/setup-ubuntu.sh                                                                                                    0.0s
    => CACHED [5/5] WORKDIR /opt                                                                                                                0.0s
    => exporting to image                                                                                                                       0.0s
    => => exporting layers                                                                                                                      0.0s
    => => writing image sha256:6944ae62a8e7d92cbe4a458869a83b243723ca0feec472c7c0387e42f316df9a                                                 0.0s
    => => naming to docker.io/library/cplusplus-image                                                                                           0.0s
    [+] Running 2/2
    ⠿ Network cplusplus_default  Created                                                                                                        0.0s
    ⠿ Container cplusplus        Started                                                                                                        0.4s
    ```

When complete, you should have an ubuntu container running with a C++ build environment:

    ```bash
    $ docker ps
    $ docker ps
    CONTAINER ID   IMAGE             COMMAND       CREATED          STATUS          PORTS     NAMES
    c2a922778e26   cplusplus-image   "/bin/bash"   13 minutes ago   Up 1 minute               cplusplus
    ```

You can attach to the running container now:

    ```bash
    $ ./attach
    root@7ff65e7e43f7:/opt#
    ```

You are now attached to the command line of a running Ubuntu image running as a Docker container.

    ```bash
    root@7ff65e7e43f7:/opt# uname -a
    Linux 7ff65e7e43f7 5.10.104-linuxkit #1 SMP Thu Mar 17 17:08:06 UTC 2022 x86_64 x86_64 x86_64 GNU/Linux
    ```

And if everything went well, you should be able to build the random.cpp file:

    ```bash
    $ make
    g++ -std=c++17 -g -Wall -o main foo.cpp random.cpp
    ```

And run the executable:

    ```bash
    $ ./main
    Hello, world.
    ```

## Summary

Our Makefile builds two CPP files, links them together, and outputs an executable.

We define a function in foo.cpp, it's prototype in foo.h, and include it in random.cpp so we can
use it.