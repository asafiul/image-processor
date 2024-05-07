#pragma once

#ifndef PRECPPPROJECT_BMP_UTILS_H
#define PRECPPPROJECT_BMP_UTILS_H

#include <cstdint>
#include <string>
#include <fstream>
#include <vector>

const uint8_t MAX_COLOR_VALUE = 255;
const double MAX_COLOR_VALUE_DOUBLE = 255;
const int32_t MAX_COLOR_VALUE_INT32 = 255;

struct RGB {
public:
    RGB() : b_(0), g_(0), r_(0) {
    }

    RGB(uint8_t b, uint8_t g, uint8_t r) : b_(b), g_(g), r_(r) {
    }

    explicit RGB(uint8_t rgb) : b_(rgb), g_(rgb), r_(rgb) {
    }
    /*
        explicit RGB(const std::vector<double>& vec)
            : b_(static_cast<uint8_t>(std::clamp(vec[0], 0.0, MAX_COLOR_VALUE_DOUBLE))),
              g_(static_cast<uint8_t>(std::clamp(vec[1], 0.0, MAX_COLOR_VALUE_DOUBLE))),
              r_(static_cast<uint8_t>(std::clamp(vec[2], 0.0, MAX_COLOR_VALUE_DOUBLE))){};
    */
    explicit RGB(const std::vector<int32_t>& vec)
        : b_(static_cast<uint8_t>(std::clamp(vec[0], 0, MAX_COLOR_VALUE_INT32))),
          g_(static_cast<uint8_t>(std::clamp(vec[1], 0, MAX_COLOR_VALUE_INT32))),
          r_(static_cast<uint8_t>(std::clamp(vec[2], 0, MAX_COLOR_VALUE_INT32))) {
    }

public:
    void Set(RGB& rgb) {
        b_ = rgb.b_;
        g_ = rgb.g_;
        r_ = rgb.r_;
    }

    uint8_t GetB() const {
        return b_;
    }

    uint8_t GetG() const {
        return g_;
    }

    uint8_t GetR() const {
        return r_;
    }

    RGB operator-(const RGB& other) const {
        return RGB(b_ - other.GetB(), g_ - other.GetG(), r_ - other.r_);
    }

protected:
    uint8_t b_;
    uint8_t g_;
    uint8_t r_;
} __attribute__((packed));

class BMPImage {
public:
    static const uint16_t BMP_SIGNATURE = 0x4D42;  // BM
    static const uint16_t DIB_BITS_PER_PIXEL = 24;

    struct BMPHeader {
        uint16_t signature;
        uint32_t size;
        uint16_t reserved1;
        uint16_t reserved2;
        uint32_t offset;
    } __attribute__((packed));

    struct DIBHeader {
        uint32_t header_size;
        int32_t width;
        int32_t height;
        uint16_t color_planes_num;
        uint16_t bits_per_pixel;
        uint32_t compression;
        uint32_t image_size;
        int32_t hor_res;
        int32_t ver_res;
        uint32_t colors_num;
        uint32_t important_colors_num;
    } __attribute__((packed));

    struct Row {
        friend class BMPImage;

    public:
        Row(){};

        RGB& operator[](size_t j) {
            return parent_->GetElement(row_, j);
        }

    protected:
        Row(size_t row, BMPImage* parent) : row_(row), parent_(parent) {
        }

    protected:
        size_t row_;
        BMPImage* parent_;
    };

public:
    BMPImage() : image_(nullptr) {
    }

    BMPImage(const std::string& input, const std::string& output) {
        OpenInput(input);
        ReadBmp();
        /// при необходимости можно сразу проверить корректность output файла
        //        CheckOutput(output);
    }

    ~BMPImage();

    void OpenInput(const std::string& filename);
    //    void OpenOutput(const std::string& filename);

    void Close();

    void ReadBmp();

    void WriteBmp(const std::string& filename);

    bool IsOpen() const {
        return file_.is_open();
    }

    void CheckOutput(const std::string& filename);

    void Assign(int32_t n, int32_t m);

    void SwapImage(BMPImage& other);

    void SetPixel(size_t i, size_t j, RGB rgb) {
        image_[Offset(i, j)].Set(rgb);
    }

    RGB* GetPixel(size_t i, size_t j) {
        return &image_[Offset(i, j)];
    }

    Row operator[](size_t i) {
        Row row(i, this);
        return row;
    }

    RGB& GetElement(size_t i, size_t j) {
        return image_[Offset(i, j)];
    }

    size_t Offset(size_t n, size_t m) const {
        return n * dib_header_.width + m;
    }

    int32_t GetWidth() const {
        return dib_header_.width;
    }
    int32_t GetHeight() const {
        return dib_header_.height;
    }

protected:
    void ReadBmpHeader();

    void ReadDibHeader();

    void ReadImage();

protected:
    std::string filename_;
    std::ifstream file_;

    BMPHeader bmp_header_;
    DIBHeader dib_header_;
    RGB* image_;
};

#endif  // PRECPPPROJECT_BMP_UTILS_H
