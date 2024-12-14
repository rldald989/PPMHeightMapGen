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

void BlurFilter(Image& a, Image& b, Vector2 canvSize){
    std::vector<Vector3> data = a.GetImageData();

    for(unsigned int i = 0; i < data.size(); i++){
        Vector3 result(0, 0, 0);
        if(i + 1 <= data.size() && i + canvSize.m_x - 1 <= data.size() && i + canvSize.m_x <= data.size()){
            result = Vector3::average(data[i], data[i + 1], data[i + canvSize.m_x-1], data[i + canvSize.m_x]);
        }
        else if (i +1 <= data.size()){
            result = Vector3::average(data[i], data[i + 1], data[i - canvSize.m_x+1], data[i - canvSize.m_x]);
        }
        else {
            result = Vector3::average(data[i], data[i - 1], data[i - canvSize.m_x-1], data[i - canvSize.m_x]);
            
        }
        b.WritePixel(result);
    }
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

int main(){
    srand(time(0));

    clock_t start = clock();

    //This is where the stuff needed to define the canvas size is
    std::string input;

    Vector2 canvSize(8, 8);

    // You can define an image, give it an output directory, and input the canvas size
    // You have to call Init(), otherwise the format won't be recognized by any software that can display it(trust me, there is a reason why
    // init is it's own thing and not just the constructor)
    Image a("output.ppm", canvSize);
    Image im("AVCh.ppm", canvSize);
    
    // This is just a loop that randomly writes black and white pixels to an image, WritePixel is really easy to use,
    // All you have to do is either put a value 0-1 * 255, or just pick a value within the 255 range.(you do this for each value as it defines the color of the pixel)
    for(int i = 0; i < canvSize.m_x * canvSize.m_y; i++){
        a.WritePixel(Vector3::rand() * 255);
    }

    im.Load("img/AVYCharacter.ppm");
    Image q_blur = QuadraBlur(im, "outputBlur.ppm", im.GetResolution());

    // Here you can export your images to the ppm format
    q_blur.Export();

    clock_t end = clock();
    float duration = float(end - start) / CLOCKS_PER_SEC;

    std::cout << duration << std::endl;
    return 0;
}