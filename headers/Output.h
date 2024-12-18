#pragma once
#include <iostream>
#include "string"
#include "Vector/Vector2.h"
#include "Vector/Vector3.h"
#include <fstream>
#include <vector>

struct Pixel{
    Vector3 color;
    Vector2 position;
};

class Image
{
private:
    std::string m_file_data;
    std::string m_output_file_name;
    std::vector<Vector3> m_image_data;
    std::ofstream m_out;
    std::ifstream m_in;
    Vector2 m_resolution;
public:
    Image(const char* output_file_name, Vector2 resolution);
    Image(const Image& image);
    ~Image();

    void Init();

    void WritePixel(Vector3 pixel);

    void Print();

    void Export();

    void Load(const char* image_path);

    static Image Mix(Image& a, Image& b);

    Image operator+(const Image& other);

    Vector2 GetResolution();

    std::vector<Vector3> GetImageData();
};