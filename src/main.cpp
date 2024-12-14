#include <iostream>
#include "../headers/Output.h"
#include <ctime>

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

void KuwaharaFilter(Image& a, Image& b, Vector2 canvSize){
    // Kuwahara filter
    std::vector<Vector3> data = a.GetImageData();

    for(unsigned int i = 0; i < data.size(); i++){
        Vector3 result(0, 0, 0);
        if(i + 1 <= data.size() && i + canvSize.m_x - 1 <= data.size() && i + canvSize.m_x <= data.size()){
            result = Vector3::average(data[i], data[i + 1], data[i + canvSize.m_x-1], data[i + canvSize.m_x]);
            b.WritePixel(result);
        }
        else if (i +1 <= data.size()){
            result = Vector3::average(data[i], data[i + 1], data[i - canvSize.m_x+1], data[i - canvSize.m_x]);
            b.WritePixel(result);
        }
        else {
            result = Vector3::average(data[i], data[i - 1], data[i - canvSize.m_x-1], data[i - canvSize.m_x]);
            b.WritePixel(result);
        }
        
    }
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

    //This is where the stuff needed to define the canvas size is
    std::string input;

    Vector2 canvSize(8, 8);

    // With how this is currently set up, you WILL have to set it to 128 when you run the program, otherwise you might run into problems
    std::cout << "Canvas Width: ";
    std::cin >> input;
    canvSize.m_x = std::atoi(input.c_str());
    input.clear();
    std::cout << "Canvas Height: ";
    std::cin >> input;
    canvSize.m_y = std::atoi(input.c_str());

    // You can define an image, give it an output directory, and input the canvas size
    // You have to call Init(), otherwise the format won't be recognized by any software that can display it(trust me, there is a reason why
    // init is it's own thing and not just the constructor)
    Image a("output.ppm", canvSize);
    a.Init();
    Image b("kuwahara.ppm", canvSize);
    b.Init();
    Image c("kuwaharaDouble.ppm", canvSize);
    c.Init();
    Image bytewareLogo("bwLogo.ppm", canvSize);
    
    // This is just a loop that randomly writes black and white pixels to an image, WritePixel is really easy to use,
    // All you have to do is either put a value 0-1 * 255, or just pick a value within the 255 range.(you do this for each value as it defines the color of the pixel)
    for(int i = 0; i < canvSize.m_x * canvSize.m_y; i++){
        a.WritePixel(rand_bw() * 255);
    }

    // This allows you to Load an image, just define the directory where it's located, and boom, you can use that image
    bytewareLogo.Load("img/BWIcon.ppm");

    // This is incorrectly named, it is NOT a kuwahara filter, but a box blur(probably)
    KuwaharaFilter(bytewareLogo, b, bytewareLogo.GetResolution());
    KuwaharaFilter(b, c, bytewareLogo.GetResolution());

    // Here you can export your images to the ppm format
    bytewareLogo.Export();
    a.Export();
    b.Export();
    c.Export();

    // if the make file isn't fixed by the time I send this out, then oh well, it's your problem now

    return 0;
}