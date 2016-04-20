
/* 
 * Author: Amy Brodie (BRDAMY004)
 * CSC3022H Tutorial 4
 * Created on 17 April 2016, 1:54 PM
 */

#ifndef IMAGE_H
#define IMAGE_H
#include <memory>
#include <string>
namespace BRDAMY004{
        
    class Image{
    private:
        int width, height;
        std::unique_ptr<unsigned char[]> data;
    public:
        Image();
        
        Image(Image & rhs);
        Image(Image && rhs);
        Image & operator=(Image & rhs);
        Image & operator=(Image && rhs);
        Image & operator+(Image image2);
        Image & operator-(Image image2);
        Image & operator!();
        Image & operator/(Image image2);
        Image & operator*(int f);
        u_char & operator[](int i);
        bool operator==(int i);
        
        void load(std::string imageName);
        void save(std::string outputFile);
        void addImages(Image image2);
        void subtractImages(Image image2);
        void invertImage();
        void maskImages(Image image2);
        void threshholdImage(int f);
        
        std::unique_ptr<unsigned char[]> getData();
        int getHeight();
        int getWidth();
        
        class iterator{
            friend class Image;
        private: 
            unsigned char *ptr;
            int index;
            iterator(u_char *p, int i);
        public:
            iterator(const iterator & rhs) ;
            iterator & operator=(const iterator & rhs);
            iterator & operator++(void);
            iterator operator++(int);
            iterator & operator--();
            u_char operator*();
            bool operator!=(iterator rhs);
            bool operator==(iterator rhs);
            
            int getIndex();
            u_char getPtrValue();
        };
        
        iterator begin(void);
        iterator end(void);
        
        ~Image();
    };
}

#endif /* IMAGE_H */

