add_executable(
        image_processor
        image_processor.cpp
        BMPImage.cpp BMPImage.h
        FilterSettings.h FilterSettings.cpp
        CLIParser.h CLIParser.cpp
        Filter.cpp Filter.h
        Factory.cpp Factory.h
        Pipeline.cpp Pipeline.h
        Filters/Grayscale.cpp Filters/Grayscale.h
        Filters/Negative.cpp Filters/Negative.h
        Filters/Crop.cpp Filters/Crop.h
        Filters/Sharpening.cpp Filters/Sharpening.h
        Filters/EdgeDetection.cpp Filters/EdgeDetection.h Filters/Mosaic.cpp Filters/Mosaic.h)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")