#include "BMPImage.h"

#include <stdexcept>

BMPImage::~BMPImage() {
    if (image_) {
        delete[] image_;
    }
    Close();
}

void BMPImage::OpenInput(const std::string &filename) {
    if (file_.is_open()) {
        throw std::logic_error("File is already open.");
    }

    if (filename.empty()) {
        throw std::invalid_argument("Filename is empty.");
    }

    filename_ = filename;
    file_.open(filename_, std::ios::binary | std::ios::in);

    if (!file_.is_open()) {
        throw std::runtime_error("Cannot open input file.");
    }
}

void BMPImage::Close() {
    if (file_.is_open()) {
        file_.close();
    }
    filename_.clear();
}

void BMPImage::ReadBmp() {
    if (!IsOpen()) {
        throw std::logic_error("File is not open.");
    }

    // Всегда читаем с начала файла
    file_.seekg(0);

    ReadBmpHeader();
    ReadDibHeader();
    ReadImage();
}

void BMPImage::ReadBmpHeader() {
    if (!file_) {
        throw std::runtime_error("Bad BMP file thread.");
    }
    file_.read(reinterpret_cast<char *>(&bmp_header_), sizeof(BMPHeader));
    if (!file_) {
        throw std::runtime_error("Bad BMP file thread.");
    }

    // Проверяем корректность bmp_header_ прямо здесь
    if (bmp_header_.signature != BMP_SIGNATURE) {
        throw std::runtime_error("BMP File is not correct.");
    }
    /// TODO добавить проверки BMPHEADER
}

void BMPImage::ReadDibHeader() {
    if (!file_) {
        throw std::runtime_error("Bad BMP file thread.");
    }
    file_.read(reinterpret_cast<char *>(&dib_header_), sizeof(DIBHeader));
    if (!file_) {
        throw std::runtime_error("Bad BMP file thread.");
    }

    /// TODO добавить проверки DIBHEADER
    // Проверяем корректность dib_header_ прямо здесь
    if (dib_header_.width <= 0 || dib_header_.height <= 0) {
        throw std::runtime_error("BMP Image size is not correct.");
    }
    if (dib_header_.color_planes_num != 1) {
        throw std::runtime_error("BMP the number of color planes must be 1.");
    }
    if (dib_header_.bits_per_pixel != DIB_BITS_PER_PIXEL) {
        throw std::logic_error("BMP bits per pixel must be " + std::to_string(DIB_BITS_PER_PIXEL));
    }
}

void BMPImage::ReadImage() {
    if (!file_) {
        throw std::runtime_error("Bad BMP file thread.");
    }
    Assign(dib_header_.height, dib_header_.width);

    int padding_size = (4 - (dib_header_.width * 3) % 4) % 4;
    char *padding = new char[padding_size];

    for (int i = 0; i < dib_header_.height; ++i) {
        file_.read(reinterpret_cast<char *>(image_ + dib_header_.width * i),
                   static_cast<int32_t>(sizeof(RGB)) * dib_header_.width);
        if (padding_size) {
            file_.read(reinterpret_cast<char *>(padding), padding_size);
        }
        if (!file_) {
            throw std::runtime_error("Bad BMP file thread.");
        }
    }
    delete[] padding;
    /*
            for (int i = 0; i < dib_header_.height; ++i) {
                image.image[i].row = new RGB[dib_header_.width];
                file_.read(reinterpret_cast<char *>(image.image[i].row), sizeof(RGB) * dib_header_.width);
                for (int j = 0; j < dib_header_.width; ++j) {
                    std::cout << static_cast<int>(j) << ": ";
                    std::cout << static_cast<int>(image.image[i].row[j].b) << " ";
                    std::cout << static_cast<int>(image.image[i].row[j].g) << " ";
                    std::cout << static_cast<int>(image.image[i].row[j].r) << std::endl;
                }
                if (padding_size > 0) {
                    file_.read(reinterpret_cast<char *>(padding), padding_size);
                }

                if (!file_) {
                    throw std::runtime_error("Bad BMP file thread.");
                }
            }
            */
    Close();
}

void BMPImage::WriteBmp(const std::string &filename) {
    std::ofstream out(filename, std::ios::binary | std::ios::out);
    if (!out.is_open()) {
        throw std::runtime_error("Cannot open output file.");
    }
    out.write(reinterpret_cast<char *>(&bmp_header_), sizeof(BMPHeader));
    out.write(reinterpret_cast<char *>(&dib_header_), sizeof(DIBHeader));
    int padding_size = (4 - (dib_header_.width * 3) % 4) % 4;
    char *padding = new char[padding_size];
    for (int i = 0; i < dib_header_.height; ++i) {
        out.write(reinterpret_cast<char *>(image_ + dib_header_.width * i),
                  static_cast<int32_t>(sizeof(RGB)) * dib_header_.width);
        if (padding_size) {
            out.write(reinterpret_cast<char *>(padding), padding_size);
        }
    }
    delete[] padding;
    out.close();
}

void BMPImage::CheckOutput(const std::string &filename) {
    std::ofstream out(filename, std::ios::binary | std::ios::out);
    if (!out.is_open()) {
        throw std::logic_error("Cannot find or open output file.");
    }
    out.close();
}

void BMPImage::SwapImage(BMPImage &other) {
    std::swap(other.image_, image_);
    int temp = GetWidth();
    dib_header_.width = other.dib_header_.width;
    other.dib_header_.width = temp;
    int temp2 = GetHeight();
    dib_header_.height = other.dib_header_.height;
    other.dib_header_.height = temp2;
}

void BMPImage::Assign(const int32_t n, const int32_t m) {
    if (n == 0 || m == 0) {
        throw std::logic_error("Invalid image size");
    }
    dib_header_.height = n;
    dib_header_.width = m;
    image_ = new RGB[n * m];
}
