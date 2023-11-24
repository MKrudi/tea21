#include "bmp.h"
#include <fstream>
#include <vector>
#include <iostream>

template<typename T>
static void read_value(std::fstream& file,T* value )
{
    file.read(reinterpret_cast<char*>(value), sizeof(T));
}

void displayAsciiImage(const std::vector<uint8_t>&grey_buffer, int width, int height)
{
    const std::string ascii_chars = " .:-=+*#%@";

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; j++)
        {
            int index = grey_buffer[i+(height-j)*width]*(ascii_chars.size()-1)/255;
            char ascii_char = ascii_chars[index];

            std::cout << ascii_char;
        }
        std::cout << "|" << std::endl;
    }
}


bool BMP::read(const std::string& filename)
{
    auto ret = false;
    // Header und Info erstellen
    std::fstream infile; 
    infile.open(filename, std::ios::binary | std::ios::in); 
    
    if (!infile.is_open()) {
        fmt::println("Unable to open the file: {}\n",filename);
        return ret;
    }
    BITMAPFILEHEADER file_header;

    read_value(infile,&file_header.bfType);
    read_value(infile,&file_header.bfSize);
    read_value(infile, &file_header.bfReserved);
    read_value(infile, &file_header.bfOffBits);

    BITMAPINFOHEADER info_header;

    read_value(infile, &info_header.biSize);
    read_value(infile, &info_header.biWidth);
    read_value(infile, &info_header.biHeight);
    read_value(infile, &info_header.biPlanes);
    read_value(infile, &info_header.biBitCount);
    read_value(infile, &info_header.biCompression);
    read_value(infile, &info_header.biSizeImage);
    read_value(infile, &info_header.biXPelsPerMeter);
    read_value(infile, &info_header.biYPelsPerMeter);
    read_value(infile, &info_header.biClrUsed);
    read_value(infile, &info_header.biClrImportant);

    // Vektor für Pixel-Buffer
    int buffer_size = info_header.biWidth*info_header.biHeight;      //Breite mal Höhe des Bildes
    std::vector<pixel> pixel_buffer(buffer_size);
    int width_length = info_header.biWidth * 3;
    int padding_length = 4 - width_length % 4;
    fmt::print("Padding: {}", padding_length);

    for (int j = 0; j < info_header.biHeight; j++)
    {
        for (int i = 0; i < info_header.biWidth; i++)
        {
            read_value(infile, &pixel_buffer[i+j*(info_header.biWidth)].red);
            read_value(infile, &pixel_buffer[i+j*(info_header.biWidth)].green);
            read_value(infile, &pixel_buffer[i+j*(info_header.biWidth)].blue);
        }
        for (int x = 0; x < padding_length; x++)
        {
            infile >> pixel_buffer[j].alpha;
        }
    }
    std::vector<uint8_t> grey_buffer(buffer_size);
    for (int i = 0; i < buffer_size; i++)
    {
        grey_buffer[i] = pixel_buffer[i].grey();
    }
    
    displayAsciiImage(grey_buffer, info_header.biWidth, info_header.biHeight);

    fmt::println("Type: {}", file_header.bfType);
    fmt::println("Size Header: {}", file_header.bfSize);
    fmt::println("Bits: {}", file_header.bfOffBits);
    fmt::println("Reserved: {}", file_header.bfReserved);
    fmt::println("Width: {}", info_header.biWidth);
    fmt::println("Height: {}", info_header.biHeight);
    fmt::println("BitCount: {}", info_header.biBitCount);
    fmt::println("ClrImportant: {}", info_header.biClrImportant);
    fmt::println("ClrUsed: {}", info_header.biClrUsed);
    fmt::println("Compression: {}", info_header.biCompression);
    fmt::println("Planes: {}", info_header.biPlanes);
    fmt::println("Size Info: {}", info_header.biSize);
    fmt::println("SizeImage: {}", info_header.biSizeImage);
    fmt::println("XPelsPerMeter: {}", info_header.biXPelsPerMeter);
    fmt::println("YPelsPerMeter: {}", info_header.biYPelsPerMeter);
    fmt::println("Buffer: {}", buffer_size);

    return ret;
}

bool BMP::write(const std::string& filename)
{
    auto ret=false;
    // Info --> pixels --> grey --> ascii --> print
 


    
    return ret;
}