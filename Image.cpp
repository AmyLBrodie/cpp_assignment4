
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
    //constructor
    Image::Image() : data(new unsigned char[1]){
        
    }
    
    // copy constructor
    Image::Image(Image& rhs) : height(rhs.height), width(rhs.width) ,data(std::move(rhs.data)){
    }
    
    //move constructor
    Image::Image(Image&& rhs) : data(std::move(rhs.data)), height(rhs.height), width(rhs.width){
        rhs.data.release();
        rhs.width = 0;
        rhs.height = 0;
    }
    
    // copy assignment operator
    Image & Image::operator =(Image& rhs){
            data = std::move(rhs.data);
            width = rhs.width;
            height = rhs.height;
        
    }
    
    // move assignment operator
    Image & Image::operator =(Image&& rhs){
        if (this != &rhs){
            data = std::move(rhs.data);
            width = rhs.width;
            height = rhs.height;
            rhs.width = 0;
            rhs.height = 0;
        }
    }
    
    
    // load images from pgm file into an Image
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
        stream >> *this;
        //stream.read((char *)data.get(), length);
        stream.close();
    }
    
    // return the unique pointer data
    std::unique_ptr<unsigned char[]> Image::getData(){
        return std::move(data);
    }
    
    // return the height of the image
    int Image::getHeight(){
        return height;
    }
    
    // return the width of the image
    int Image::getWidth(){
        return width;
    }
    
    // save an Image into a pgm file
    void Image::save(std::string outputFile){
        std::ofstream stream(outputFile);
        stream << "P5" << std::endl;
        stream << "#Output image" << std::endl;
        stream << height << " " << width << std::endl;
        stream << "255" << std::endl;
        //stream.write((char *)data.get(), width*height);
        stream << *this;
        stream.close();
    }
    
    // constructor for iterator
    Image::iterator::iterator(u_char* p, int i) : ptr(p), index(i){
        
    }
    
    // copy constructor for iterator
    Image::iterator::iterator(const iterator& rhs) : ptr(rhs.ptr), index(rhs.index){
        
    }
    
    // copy assignment operator for iterator
    Image::iterator & Image::iterator::operator =(const iterator& rhs){
        if (this != &rhs){
            ptr = rhs.ptr;
            index = rhs.index;
        }
    }
    
    // prefix ++ operator for iterator
    Image::iterator & Image::iterator::operator ++(){
        ++index;
        ++ptr;
        return *this;
    }
    
    // postfix ++operator for iterator
    Image::iterator Image::iterator::operator ++(int){
        Image::iterator temp = *this;
        operator ++();
        return temp;
    }
    
    // -- operator for iterator
    Image::iterator & Image::iterator::operator --(){
        --index;
        --ptr;
        return *this;
    }
    
    // * operator for iterator
    u_char Image::iterator::operator *(){
        return this->ptr[index];
    }
    
    // != operator for iterator
    bool Image::iterator::operator !=(Image::iterator rhs){
        return index != rhs.index;
    }
    
    // == operator for iterator
    bool Image::iterator::operator ==(Image::iterator rhs){
        return index == rhs.index;
    }
    
    // returns the index of the iterator
    int Image::iterator::getIndex(){
        return index;
    }
    
    // returns the pointer of the iterator (currently pointed to object)
    u_char Image::iterator::getPtrValue(){
        return *ptr;
    }
    
    // return the beginning of the iterator
    Image::iterator Image::begin(){
        Image::iterator it(data.get(), 0);
        return it;
    }
    
    // return the end of the iterator
    Image::iterator Image::end(){
        Image::iterator it(data.get(), width*height);
        return it;
    }
    
    // addition operator for two images
    Image & Image::operator+(Image image2){
        if (height == image2.getHeight() && width == image2.getWidth()){
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
        }
        return *this;
    }
    
    // subtraction operator for two images
    Image & Image::operator-(Image image2){
        if (height == image2.getHeight() && width == image2.getWidth()){
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
        }
        return *this;
    }
    
    // thresholding operator for an image, with given threshold f
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
    
    // masking operator for two images
    Image & Image::operator/(Image image2){
        if (height == image2.getHeight() && width == image2.getWidth()){
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
        }
        return *this;
    }
    
    // inverse operator for an image
    Image & Image::operator!(){
        u_char array [width*height];
        for (Image::iterator itStart1 = this->begin(); itStart1 != this->end(); itStart1++){
            int temp = (int)*itStart1.ptr;
            *itStart1.ptr = (u_char)(255-temp);
        }
        return *this;
    }
    
    // == operator only works for images that contain only one pixel value (i.e. 255 or 0, etc.)
    bool Image::operator ==(int i){
        bool flag = true;
        for (Image::iterator itStart1 = this->begin(); itStart1 != this->end(); itStart1++){
            if ((int)(*itStart1.ptr) != i){
                flag = false;
            }
        }
        return flag;
    }
    
    // adds two images together
    void Image::addImages(Image image2){
        *this = (*this) + image2;
        
    }
    
    // subtracts an image from another
    void Image::subtractImages(Image image2){
        *this = (*this) - image2;
    }
    
    // inverts an image
    void Image::invertImage(){
        *this = !(*this);
    }
    
    // masks an image with another image
    void Image::maskImages(Image image2){
        *this = (*this) / image2;
    }
    
    // threshold an image with the supplied int
    void Image::threshholdImage(int f){
        *this = (*this)*f;
    }
    
    // return the element at index i
    u_char & Image::operator[](int i){
        return data[i];
    }
    
    //destructor
    Image::~Image(){
        
    }
    
    // output stream operator
    std::ostream & operator<<(std::ostream & stream, Image & img){
        for (Image::iterator it=img.begin(); it!=img.end(); it++){
            stream << it.getPtrValue();
        }
        return stream;
    }
    
    // input stream operator
    Image & operator>>(std::istream & stream, Image & img){
        u_char temp [img.getHeight()*img.getWidth()];
        stream.read((char*)temp, img.getHeight()*img.getWidth());
        int i = 0;
        for (Image::iterator it=img.begin(); it!=img.end(); it++){
            *it.ptr = temp[i];
            i++;
        }
        return img;
    }
}