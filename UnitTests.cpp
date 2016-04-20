#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Image.h"
#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>

TEST_CASE("Move Constructor for Image"){
    BRDAMY004::Image image;
    image.load("test1.pgm");
    int height = image.getHeight();
    int width = image.getWidth();
    BRDAMY004::Image newImage;
    newImage = std::move(image);
    
    REQUIRE(newImage == 255);
    REQUIRE(newImage.getHeight() == height);
    REQUIRE(newImage.getWidth() == width);
    REQUIRE(image.getHeight() == 0);
    REQUIRE(image.getWidth() == 0);
    REQUIRE(image.getData() == nullptr);
}

TEST_CASE("Copy Constructor for Image"){
    BRDAMY004::Image image;
    image.load("test1.pgm");
    int height = image.getHeight();
    int width = image.getWidth();
    BRDAMY004::Image newImage(image);
    
    REQUIRE(newImage == 255);
    REQUIRE(newImage.getHeight() == height);
    REQUIRE(newImage.getWidth() == width);
    REQUIRE(image.getHeight() == height);
    REQUIRE(image.getWidth() == width);
    REQUIRE(image.getData() == nullptr);
}

TEST_CASE("Copy Assignment Operator for Image"){
    BRDAMY004::Image image;
    image.load("test1.pgm");
    int height = image.getHeight();
    int width = image.getWidth();
    BRDAMY004::Image newImage;
    newImage.load("test2.pgm");
    newImage = image;
    
    REQUIRE(newImage == 255);
    REQUIRE(newImage.getHeight() == height);
    REQUIRE(newImage.getWidth() == width);
    REQUIRE(image.getHeight() == height);
    REQUIRE(image.getWidth() == width);
    REQUIRE(image.getData() == nullptr);
}

TEST_CASE("Move Assignment Operator for Image"){
    BRDAMY004::Image image;
    image.load("test1.pgm");
    BRDAMY004::Image newImage;
    newImage.load("test2.pgm");
    int height = newImage.getHeight();
    int width = newImage.getWidth();
    image = std::move(newImage);
    
    REQUIRE(image == 0);
    REQUIRE(newImage.getHeight() == 0);
    REQUIRE(newImage.getWidth() == 0);
    REQUIRE(image.getHeight() == height);
    REQUIRE(image.getWidth() == width);
    REQUIRE(newImage.getData() == nullptr);
}

TEST_CASE("The Image Iterator"){
    BRDAMY004::Image image;
    image.load("test1.pgm");
    BRDAMY004::Image::iterator it1 = image.begin();
    BRDAMY004::Image::iterator it2 = image.end();
    
    REQUIRE(it1 != it2);
    REQUIRE(it1.getIndex() == 0);
    REQUIRE(it2.getIndex() == (image.getHeight()*image.getWidth()));
    REQUIRE(*it1 == it1.getPtrValue());
    REQUIRE((--it2).getIndex() == (image.getHeight()*image.getWidth())-1);
    REQUIRE(*(++it1) == (++it1).getPtrValue());
    REQUIRE((it1++).getIndex() == 2);
    REQUIRE(it1.getIndex() == 3);
}

TEST_CASE("The Inverting Operator"){
    BRDAMY004::Image image;
    image.load("test1.pgm");
    REQUIRE(image == 255);
    image.invertImage();
    REQUIRE(image == 0);
    
    BRDAMY004::Image image1;
    image1.load("test2.pgm");
    REQUIRE(image1 == 0);
    image1.invertImage();
    REQUIRE(image1 == 255);
}

TEST_CASE("The Thresholding Operator"){
    BRDAMY004::Image image;
    image.load("test1.pgm");
    REQUIRE(image == 255);
    image.threshholdImage(255);
    REQUIRE(image == 0);
    
    BRDAMY004::Image image1;
    image1.load("test2.pgm");
    REQUIRE(image1 == 0);
    image1.threshholdImage(-1);
    REQUIRE(image1 == 255);
}

TEST_CASE("The Masking Operator"){
    BRDAMY004::Image image;
    image.load("test1.pgm");
    BRDAMY004::Image image1;
    image1.load("test2.pgm");
    REQUIRE(image == 255);
    image.maskImages(image1);
    REQUIRE(image == 0);
}


TEST_CASE("The Addition Operator"){
    BRDAMY004::Image image;
    BRDAMY004::Image image1;
    image.load("test1.pgm");
    image1.load("test1.pgm");
    image.addImages(image1);
    REQUIRE(image == 255);
    
    BRDAMY004::Image image2;
    BRDAMY004::Image image3;
    image2.load("test2.pgm");
    image3.load("test2.pgm");
    image2.addImages(image3);
    REQUIRE(image2 == 0);
}

TEST_CASE("The Subtraction Operator"){
    BRDAMY004::Image image;
    image.load("test1.pgm");
    BRDAMY004::Image image1;
    image1.load("test2.pgm");
    image1.subtractImages(image);
    REQUIRE(image1 == 0);
}

