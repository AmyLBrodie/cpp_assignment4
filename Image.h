
/* 
 * File:   Image.h
 * Author: amy
 *
 * Created on 17 April 2016, 1:54 PM
 */

#ifndef IMAGE_H
#define IMAGE_H
namespace BRDAMY004{
    
#include <memory>
    
    class Image{
    private:
        int width, height;
        std::unique_ptr<unsigned char[]> data;
        std::string imageName;
        std::string outputImageName;
    public:
        Image(std::string fileName,std::string outputFile);
        ~Image();
        Image(Image & rhs);
        Image(Image && rhs);
        Image & operator=(Image & rhs);
        Image & operator=(Image && rhs);
        Image & operator+(Image image2);
        Image & operator-(Image image2);
        Image & operator!();
        Image & operator/(Image image2);
        Image & operator*(int f);
        
        void load(std::string fileName);
        void save(std::string outputFile);
        
        class iterator{
            private: 
                unsigned char *ptr;
                iterator(u_char *p);
        public:
            iterator(const iterator & rhs) ;
            iterator & operator=(const iterator & rhs);
            iterator & operator++();
            iterator & operator--();
            iterator & operator*();
        };
    };
}

#endif /* IMAGE_H */

