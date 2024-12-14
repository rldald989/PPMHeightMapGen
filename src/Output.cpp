#include "../headers/Output.h"

Image::Image(const char *output_file_name, Vector2 resolution) : m_out(output_file_name), m_resolution(resolution)
{
   
}

Image::~Image()
{
}

void Image::Init()
{
    m_file_data += "P3\n" + std::to_string((int)m_resolution.m_x) + " " + std::to_string((int)m_resolution.m_y) + "\n255\n";
}

void Image::WritePixel(Vector3 pixel)
{
    m_image_data.push_back(pixel);
    m_file_data += Vector3::to_string_i(pixel) + "\n";
}

void Image::Print()
{
    std::cout << m_file_data;
}

void Image::Export()
{
    m_out << m_file_data;
    m_out.close();
}

void Image::Load(const char *image_path)
{
    std::string temp_image_data;
    m_in.open(image_path);
    int counter = 0;
    int rgbCounter = 0;
    Vector3 tempColor(0, 0, 0);
    while(m_in >> temp_image_data){
        counter++;
        if(counter == 2){
            m_resolution.m_x = atoi(temp_image_data.c_str());
        }

        if(counter == 3){
            m_resolution.m_y = atoi(temp_image_data.c_str());
            Init();
        }

        if(counter >= 5){

            if(rgbCounter == 0){
                tempColor.x = std::atoi(temp_image_data.c_str());
            }
            else if(rgbCounter == 1){
                tempColor.y = std::atoi(temp_image_data.c_str());
            }
            else if(rgbCounter == 2){
                tempColor.z = std::atoi(temp_image_data.c_str());
                m_image_data.push_back(tempColor);
                m_file_data += Vector3::to_string_i(tempColor) + "\n";
                
            }
            rgbCounter++;
        }

        if(rgbCounter >= 3){
            rgbCounter = 0;
        }
        
    }
    counter = 0;
}

Vector2 Image::GetResolution()
{
    return m_resolution;
}
std::vector<Vector3> Image::GetImageData()
{
    return m_image_data;
}
