
# Add the hello library
add_library(hello STATIC
    src/hello.cpp
)

# Specify include directory for the library
target_include_directories(hello PUBLIC include)
