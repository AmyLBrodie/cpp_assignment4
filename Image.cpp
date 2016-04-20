
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
    Image::Image(std::string fileName) : imageName(fileName), data(new unsigned char[1]){
        
    }
    
    Image::Image(Image& rhs) : imageName(rhs.imageName), height(rhs.height),data(std::move(rhs.data)), width(rhs.width){
        
    }
    
    Image::Image(Image&& rhs) : imageName(std::move(rhs.imageName)), data(std::move(rhs.data)), height(rhs.height), width(rhs.width){
        rhs.data.release();
        rhs.width = 0;
        rhs.height = 0;
        rhs.imageName = "";
    }
    
    Image & Image::operator =(Image& rhs){
        if (this != &rhs){
            data = std::move(rhs.data);
            width = rhs.width;
            height = rhs.height;
            imageName = rhs.imageName;
        }
    }
    
    Image & Image::operator =(Image&& rhs){
        if (this != &rhs){
            data = std::move(rhs.data);
            width = rhs.width;
            height = rhs.height;
            imageName = std::move(rhs.imageName);
        }
    }
    
    
    
    void Image::load(){
        std::ifstream stream(Image::imageName, std::ios::binary);
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
    
    Image::iterator::iterator(const iterator& rhs) : ptr(rhs.ptr){
        
    }
    
    Image::iterator & Image::iterator::operator =(const iterator& rhs){
        if (this != &rhs){
            ptr = rhs.ptr;
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
    
    Image::iterator Image::begin(){
        Image::iterator it(data.get(), 0);
        //std::cout << height*width << std::endl;
        return it;
    }
    
    Image::iterator Image::end(){
        Image::iterator it(data.get(), width*height);
        //std::cout << (int)(data.get())[width*height] << std::endl;
        return it;
    }
    
    Image & Image::operator+(Image image2){
        Image:: iterator itStart2 = image2.begin();
        for (Image::iterator itStart1 = this->begin(); itStart1 != this->end(); itStart1++){
            //itStart2++;
            //std::cout << "1" << std::endl;
            int temp = (int)(*itStart1.ptr) + (int)(*itStart2.ptr);
            std::cout << (int)(*itStart2.ptr) << std::endl;
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
            std::cout << temp << " ";
            if (temp > f){
                *itStart1.ptr = (u_char) 255;
            }
            else{
                *itStart1.ptr = (u_char) 0;
            }
            std::cout << (int)*itStart1.ptr << std::endl;
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