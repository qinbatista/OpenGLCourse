
#include <stdio.h>
#include <string.h>
#include "ShaderAndTriangle.h"
void Awake()
{
    CreateTriangle();
    CompileShaders();
}
void Update()
{
    if(direction)
        triOffset += triIncrement;
    else
        triOffset -= triIncrement;
    DrawTriangle();
}