#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "spherical.h"
#include "cube.h"
#include "rules.h"
#include "range.h"

void reshapeScreen(sf::Vector2u screenSize);
void initOpenGL();
void drawScene();
void* Roll(void*);


#endif