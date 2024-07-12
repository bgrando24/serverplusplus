# Use an official C++ image as the base
FROM gcc:latest AS builder

# Set the working directory
WORKDIR /src

# Copy the source code into the container
COPY . .

# Install dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    libssl-dev

# Build the application
RUN cmake -S . -B build && cmake --build build

# Debug: list files in build and build/bin after build
RUN ls -la build && ls -la build/bin

# Use a smaller image for the runtime
FROM gcc:latest

# Set the working directory
WORKDIR /src

# Copy the built binary from the builder stage
COPY --from=builder /src/build/bin/serverplusplus /usr/local/bin/serverplusplus

# Expose the necessary ports
EXPOSE 8080

# Run the server
CMD ["serverplusplus"]
