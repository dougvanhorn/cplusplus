FROM ubuntu:22.04

# Think of this file as a build script, it says:
# Grab the ubuntu docker image, v22.04
# Copy a file into that image.
# Run that script
# When someone "runs" this container, the default command is /bin/bash.

COPY setup-ubuntu.sh /tmp/setup-ubuntu.sh
RUN chmod 755 /tmp/setup-ubuntu.sh
RUN /tmp/setup-ubuntu.sh

# Start the attaching user in the /opt directory.
WORKDIR /opt


CMD ["/bin/bash"]