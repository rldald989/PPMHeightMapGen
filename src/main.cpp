#include <iostream>
#include "../headers/Output.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Vector3 rand_bw(){
    float r = (float)(std::rand() % 10) / 10;
    if(r >= 0.5f){
        r = 1;
    }
    else{
        r = 0;
    }
    return Vector3(r, r, r);
}

Image BlurFilter(Image& a, const char* outputFile, Vector2 canvSize){
    std::vector<Vector3> data = a.GetImageData();
    Image b(outputFile, canvSize);
    b.Init();
    for(unsigned int i = 0; i < data.size(); i++){
        Vector3 result(0, 0, 0);
        if(i - canvSize.m_x - 1 > 0
            && i + canvSize.m_x + 1 < data.size()
            ){
            result = Vector3::average
            (
                data[i], 
                data[i + 1], 
                data[i - 1], 

                data[i + canvSize.m_x + 1],
                data[i + canvSize.m_x],
                data[i + canvSize.m_x - 1],

                data[i - canvSize.m_x - 1],
                data[i - canvSize.m_x],
                data[i - canvSize.m_x + 1]
            );
        }
        b.WritePixel(result);
    }
    return b;
}

void BlurFilter(Image& a, Image& b, Vector2 canvSize){
    std::vector<Vector3> data = a.GetImageData();
    for(unsigned int i = 0; i < data.size(); i++){
        Vector3 result(0, 0, 0);
        if(i - canvSize.m_x - 1 > 0
            && i + canvSize.m_x + 1 < data.size()
            ){
            result = Vector3::average
            (
                data[i], 
                data[i + 1], 
                data[i - 1], 

                data[i + canvSize.m_x + 1],
                data[i + canvSize.m_x],
                data[i + canvSize.m_x - 1],

                data[i - canvSize.m_x - 1],
                data[i - canvSize.m_x],
                data[i - canvSize.m_x + 1]
            );
        }
        b.WritePixel(result);
    }
}

Image AAFilter(Image& a, const char* file_name, Vector3& bgColor, Vector2 canvSize){
    std::vector<Vector3> data = a.GetImageData();
    Image b(file_name, canvSize);
    b.Init();
    Vector2 pixel_position(0, 0);
    for(unsigned int i = 0; i < data.size(); i++){
        Vector3 result(0, 0, 0);

        if (pixel_position.m_x >= canvSize.m_x) {
            pixel_position.m_x = 0; // Reset to start of the row
            pixel_position.m_y++;
        }

        if (i > 0 && i < data.size() - 1 &&
            (i - 1) >= 0 
            && (i + 1) < data.size() 
            && (i - (canvSize.m_x * pixel_position.m_y) - 1) >= 0 
            && (i + (canvSize.m_x * pixel_position.m_y) + 1) < data.size() 
            && data[i+1] == bgColor 
            && data[i - (canvSize.m_x * pixel_position.m_y) + 1] == bgColor)
        {
            result = Vector3::average(data[i], data[i - 1], data[i + 1], data[i - (canvSize.m_x * pixel_position.m_y) - 1], data[i + (canvSize.m_x * pixel_position.m_y) + 1]);
        }
        if (i > 0 && i < data.size() - 1  &&
            (i - 1) >= 0 
            && (i + 1) < data.size() 
            && (i - (canvSize.m_x * pixel_position.m_y) - 1) >= 0 
            && (i + (canvSize.m_x * pixel_position.m_y) + 1) < data.size() 
            && data[i - 1] == bgColor 
            && data[i + (canvSize.m_x * pixel_position.m_y) - 1] == bgColor)
        {
            result = Vector3::average(data[i], data[i - 1], data[i + 1], data[i - (canvSize.m_x * pixel_position.m_y) - 1], data[i + (canvSize.m_x * pixel_position.m_y) + 1]);
        }

        b.WritePixel(result);
    }
    return b;
}

Image QuadraBlur(Image& a, const char* output_file, Vector2 canvSize){
    Image b("b.ppm", canvSize);
    Image q("q.ppm", canvSize);
    Image r("r.ppm", canvSize);
    Image s(output_file, canvSize);
    s.Init();

    BlurFilter(a, b, canvSize);
    BlurFilter(b, q, canvSize);
    BlurFilter(q, r, canvSize);
    BlurFilter(r, s, canvSize);

    return s;
}

void ContrastFilter(Image& a, Image& b){
    // Kuwahara filter
    for(unsigned int i = 0; i < a.GetImageData().size(); i++){
        Vector3 result = (Vector3(1, 1, 1) + .05f) / (a.GetImageData()[i] + .05f);
        b.WritePixel(result);
        
    }
}

void WriteCircle(Image& b, Vector2 position, Vector3 color, float size, Vector2& canvSize){
    Vector2 pixel_position(0, 0);
    Vector2 c_pos(0, 0);
    for(int i = 0; i < canvSize.m_x * canvSize.m_y; i++){
        if(pixel_position.m_x > canvSize.m_x){
            pixel_position.m_y++;
        }
        pixel_position.m_x = i - (canvSize.m_x * pixel_position.m_y);

        if(Vector2::distance(pixel_position, position) <= size){
            b.WritePixel(color * 255);
        }
        else{
            b.WritePixel(Vector3(0, 0, 0));
        }
    }
}

void WriteCircleMask(Image& a, Image& masked_image, Vector2 position, Vector3 color, float size, Vector2& canvSize){
    Vector2 pixel_position(0, 0);
    Vector2 c_pos(0, 0);
    std::vector<Vector3> data = masked_image.GetImageData();
    for(int i = 0; i < canvSize.m_x * canvSize.m_y; i++){
        if(pixel_position.m_x > canvSize.m_x){
            pixel_position.m_y++;
        }
        pixel_position.m_x = i - (canvSize.m_x * pixel_position.m_y);

        if(Vector2::distance(pixel_position, position) <= size){
            a.WritePixel((data[i] + (color * 255)) / 2);
        }
        else{
            a.WritePixel(Vector3(0, 0, 0));
        }
    }
}

int main(){
    srand(time(0));

    

    //This is where the stuff needed to define the canvas size is
    std::string input;

    Vector2 canvSize(8, 8);

    //Width
    std::cout << "Width: ";
    std::cin >> input;
    canvSize.m_x = std::atoi(input.c_str());
    input.clear();
    //Height
    std::cout << "Height: ";
    std::cin >> input;
    canvSize.m_y = std::atoi(input.c_str());

    Vector2 center(canvSize.m_x / 2, canvSize.m_y / 2);

    // Clock should start only BEFORE processing and AFTER setup, otherwise it factors in setup time
    clock_t start = clock();

    // You can define an image, give it an output directory, and input the canvas size
    // You have to call Init(), otherwise the format won't be recognized by any software that can display it(trust me, there is a reason why
    // init is it's own thing and not just the constructor)
    Image noise("noise.ppm", canvSize);
    Image circle_a("circle.ppm", canvSize);
    Image circle_b("circle.ppm", canvSize);
    Image avCh("avCH.ppm", canvSize);

    for(int i = 0; i < canvSize.m_x * canvSize.m_y; i++)
    {
        noise.WritePixel(rand_bw() * 255);
    }

    avCh.Load("img/AVYCharacter.ppm");
    WriteCircle(circle_a, center, Vector3(1, 1, 1), canvSize.m_x/4, canvSize);
    WriteCircleMask(circle_b, avCh, center + 50.0f, Vector3(1, 1, 1), canvSize.m_x/6, canvSize);

    Vector3 black(0, 0, 0);

    Image circleAA_a = AAFilter(circle_a, "circle.ppm", black, canvSize); 
    Image circleAA_b = AAFilter(circle_b, "circle.ppm", black, canvSize); 

    Image circle_comb = Image::Mix(circle_a, circle_b);
    Image img_comb = Image::Mix(circle_comb, avCh);

    Image circleBlur = QuadraBlur(circle_comb, "circleBlurred.ppm", canvSize);
    // Here you can export your images to the ppm format
    circle_comb.Export();
    circleBlur.Export();

    // Prints the execution time
    clock_t end = clock();
    float duration = float(end - start) / CLOCKS_PER_SEC;

    std::cout << duration << std::endl;
    return 0;
}