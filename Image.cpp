
/* 
 * Author: Amy Brodie (BRDAMY004)
 * CSC3022H Tutorial 4
 * Created on 17 April 2016, 1:54 PM
 */


#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Image.h"

namespace BRDAMY004{
    Image::Image() : data(new unsigned char[1]){
        
    }
    
    Image::Image(Image& rhs) : height(rhs.height),data(std::move(rhs.data)), width(rhs.width){
        
    }
    
    Image::Image(Image&& rhs) : data(std::move(rhs.data)), height(rhs.height), width(rhs.width){
        rhs.data.release();
        rhs.width = 0;
        rhs.height = 0;
    }
    
    Image & Image::operator =(Image& rhs){
        if (this != &rhs){
            data = std::move(rhs.data);
            width = rhs.width;
            height = rhs.height;
        }
    }
    
    Image & Image::operator =(Image&& rhs){
        if (this != &rhs){
            data = std::move(rhs.data);
            width = rhs.width;
            height = rhs.height;
            rhs.width = 0;
            rhs.height = 0;
        }
    }
    
    
    
    void Image::load(std::string imageName){
        std::ifstream stream(imageName.c_str(), std::ios::binary);
        std::string temp;
        std::getline(stream, temp, '\n');
        std::getline(stream, temp, '\n');
        while (temp[0] == '#'){
            std::getline(stream, temp, '\n');
        }
        std::istringstream iss(temp);
        iss >> height >> std::ws >> width;
        stream >> temp >> std::ws;
        int length = width * height;
        data.reset(new unsigned char [length]);
        stream.read((char *)data.get(), length);
        stream.close();
    }
    
    std::unique_ptr<unsigned char[]> Image::getData(){
        return std::move(data);
    }
    
    int Image::getHeight(){
        return height;
    }
    
    int Image::getWidth(){
        return width;
    }
    
    void Image::save(std::string outputFile){
        std::ofstream stream(outputFile);
        stream << "P5" << std::endl;
        stream << "#Output image" << std::endl;
        stream << height << " " << width << std::endl;
        stream << "255" << std::endl;
        stream.write((char *)data.get(), width*height);
        stream.close();
    }
    
    Image::iterator::iterator(u_char* p, int i) : ptr(p), index(i){
        
    }
    
    Image::iterator::iterator(const iterator& rhs) : ptr(rhs.ptr), index(rhs.index){
        
    }
    
    Image::iterator & Image::iterator::operator =(const iterator& rhs){
        if (this != &rhs){
            ptr = rhs.ptr;
            index = rhs.index;
        }
    }
    
    Image::iterator & Image::iterator::operator ++(){
        ++index;
        ++ptr;
        return *this;
    }
    
    Image::iterator Image::iterator::operator ++(int){
        Image::iterator temp = *this;
        operator ++();
        return temp;
    }
    
    Image::iterator & Image::iterator::operator --(){
        --index;
        --ptr;
        return *this;
    }
    
    u_char Image::iterator::operator *(){
        return this->ptr[index];
    }
    
    bool Image::iterator::operator !=(Image::iterator rhs){
        return index != rhs.index;
    }
    
    bool Image::iterator::operator ==(Image::iterator rhs){
        return index == rhs.index;
    }
    
    int Image::iterator::getIndex(){
        return index;
    }
    
    u_char Image::iterator::getPtrValue(){
        return *ptr;
    }
    
    Image::iterator Image::begin(){
        Image::iterator it(data.get(), 0);
        return it;
    }
    
    Image::iterator Image::end(){
        Image::iterator it(data.get(), width*height);
        return it;
    }
    
    Image & Image::operator+(Image image2){
        Image:: iterator itStart2 = image2.begin();
        for (Image::iterator itStart1 = this->begin(); itStart1 != this->end(); itStart1++){
            int temp = (int)(*itStart1.ptr) + (int)(*itStart2.ptr);
            if (temp > 255){
                *itStart1.ptr = (u_char)255;
            }
            else if (temp < 0){
                *itStart1.ptr = (u_char)0;
            }
            else{
                *itStart1.ptr = (u_char)temp;
            }
            if (itStart2 != image2.end()){
                itStart2++;
            }
        }
        return *this;
    }
    
    Image & Image::operator-(Image image2){
        Image:: iterator itStart2 = image2.begin();
        for (Image::iterator itStart1 = this->begin(); itStart1 != this->end(); itStart1++){
            int temp = (int)*itStart1.ptr - (int)*itStart2.ptr;
            if (temp > 255){
                *itStart1.ptr = (u_char)255;
            }
            else if (temp < 0){
                *itStart1.ptr = (u_char)0;
            }
            else{
                *itStart1.ptr = (u_char)temp;
            }
            if (itStart2 != image2.end()){
                itStart2++;
            }
        }
        return *this;
    }
    
    Image & Image::operator*(int f){
        for (Image::iterator itStart1 = this->begin(); itStart1 != this->end(); itStart1++){
            int temp = (int)*itStart1.ptr;
            if (temp > f){
                *itStart1.ptr = (u_char) 255;
            }
            else{
                *itStart1.ptr = (u_char) 0;
            }
        }
        return *this;
    }
    
    Image & Image::operator/(Image image2){
        Image:: iterator itStart2 = image2.begin();
        for (Image::iterator itStart1 = this->begin(); itStart1 != this->end(); itStart1++){
            int temp = (int)*itStart2.ptr;
            if (temp != 255){
                *itStart1.ptr = (u_char)0;
            }
            if (itStart2 != image2.end()){
                itStart2++;
            }
        }
        return *this;
    }
    
    Image & Image::operator!(){
        u_char array [width*height];
        for (Image::iterator itStart1 = this->begin(); itStart1 != this->end(); itStart1++){
            int temp = (int)*itStart1.ptr;
            *itStart1.ptr = (u_char)(255-temp);
        }
        return *this;
    }
    
    bool Image::operator ==(int i){
        bool flag = true;
        for (Image::iterator itStart1 = this->begin(); itStart1 != this->end(); itStart1++){
            if ((int)(*itStart1.ptr) != i){
                flag = false;
            }
        }
        return flag;
    }
    
    void Image::addImages(Image image2){
        *this = (*this) + image2;
    }
    
    void Image::subtractImages(Image image2){
        *this = (*this) - image2;
    }
    
    void Image::invertImage(){
        *this = !(*this);
    }
    
    void Image::maskImages(Image image2){
        *this = (*this) / image2;
    }
    
    void Image::threshholdImage(int f){
        *this = (*this)*f;
    }
    
    u_char & Image::operator[](int i){
        return data[i];
    }
    
    Image::~Image(){
        
    }
}