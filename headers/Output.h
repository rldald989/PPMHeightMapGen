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
    std::vector<Vector3> m_image_data;
    std::ofstream m_out;
    std::ifstream m_in;
    Vector2 m_resolution;
public:
    Image(const char* output_file_name, Vector2 resolution);
    ~Image();

    void Init();

    void WritePixel(Vector3 pixel);

    void Print();

    void Export();

    void Load(const char* image_path);

    Vector2 GetResolution();

    std::vector<Vector3> GetImageData();
};