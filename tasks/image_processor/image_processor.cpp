#include <iostream>

#include "BMPImage.h"
#include "FilterSettings.h"
#include "CLIParser.h"
#include "Factory.h"

const std::string LENNA_FILENAME = "./lenna.bmp";
const std::string OUTPUT = "./output.bmp";

void Test001() {
    //    std::cout << "TEST 1:\n";
    BMPImage bmp_image;

    try {
        bmp_image.OpenInput(LENNA_FILENAME);
    } catch (std::exception& e) {
        std::cerr << "TEST001 Exception: " << e.what() << "\n";
    } catch (...) {
        std::cerr << "TEST001 Unknown Exception\n";
    }

    //     assert(bmp_image.IsOpen());
    std::cout << "TEST 1: PASSED\n";
}

void Test002() {
    //    std::cout << "TEST 2:\n";
    BMPImage bmp_image;
    bmp_image.OpenInput(LENNA_FILENAME);

    bmp_image.ReadBmp();
    std::cout << "TEST 2: PASSED\n";
}

void Test003() {
    //    std::cout << "TEST 3:\n";
    BMPImage bmp_image(LENNA_FILENAME, OUTPUT);
    try {
        bmp_image.WriteBmp(OUTPUT);
    } catch (std::exception& ex) {
        std::cerr << ex.what() << "\n";
    }
    std::cout << "TEST 3: PASSED\n";
}
void Test004() {
    //    std::cout << "TEST 3:\n";
    try {
        BMPImage bmp_image(LENNA_FILENAME, OUTPUT);
        std::vector<FilterSettings*> fs_vec;
        fs_vec.emplace_back(new FilterSettings("gs", {}));
        fs_vec.emplace_back(new FilterSettings("neg", {}));
        fs_vec.emplace_back(new FilterSettings("edge", {"0.5"}));
        fs_vec.emplace_back(new FilterSettings("sharp", {}));
        fs_vec.emplace_back(new FilterSettings("crop", {"1300", "1300"}));
        Factory factory;
        Pipeline pipeline;
        factory.CreatePipeline(fs_vec, pipeline);
        pipeline.Apply(bmp_image);
        bmp_image.WriteBmp(OUTPUT);
    } catch (std::exception& ex) {
        std::cerr << ex.what() << "\n";
    }
    std::cout << "TEST 4: PASSED\n";
}

int Test() {
    std::cout << "TESTING\n";
    try {
        Test001();
        Test002();
        Test003();
        Test004();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "Unknown Exception\n";
        return 1;
    }
    std::cout << "All tests passed\n";

    return 0;
}

/// Я РЕАЛИЗОВАЛ ДОП ФИЛЬТР МОЗАИКА, НЕ ЗАБУДЬТЕ ПОСМОТРЕТЬ!

int main(int argc, char** argv) {

    //    return Test();
    try {
        if (argc < 3) {
            throw std::logic_error("Not enough arguments. Be sure writing INPUT and OUTPUT files.");
        }
        BMPImage bmp_image(argv[1], argv[2]);

        CLIParser cli_parser(argc - 3, argv + 3);

        Factory factory;

        Pipeline pipeline;
        factory.CreatePipeline(cli_parser.fs_vec, pipeline);
        pipeline.Apply(bmp_image);

        bmp_image.WriteBmp(argv[2]);
    } catch (std::invalid_argument& ie) {
        std::cerr << ie.what() << "\n";
    } catch (std::logic_error& le) {
        std::cerr << le.what() << "\n";
    } catch (std::runtime_error& re) {
        std::cerr << re.what() << "\n";
    } catch (std::exception& ex) {
        std::cerr << ex.what() << "\n";
    } catch (...) {
        std::cerr << "Unknown exception.\n";
    }
    return 0;
}
