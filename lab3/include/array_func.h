#pragma once

#include <iostream>
#include <vector>
#include "Figure.h"

void input(std::vector<Figure*>& v);
void output(std::vector<Figure*>& v);
void print_square(std::vector<Figure*>& v);
void print_geomc(std::vector<Figure*>& v);
double square_sum(std::vector<Figure*>& v);
bool del(std::vector<Figure*>& v, int i);



