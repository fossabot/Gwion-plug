#include <cv.hpp>

#include "loup.hpp"
#include "fx.hpp"
#include "ciel.hpp"

Ciel::Ciel() {
  pic = imread("ciel.jpeg");
}

void Ciel::run(Loup* loup, Mat frame) {
  float alpha = loup->joy()->scale;
  addWeighted(pic, alpha, frame, 1 - alpha, 0, frame);
}
