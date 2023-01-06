
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "ShaderAndTriangle.h"
void Awake()
{
    CreateTriangle();
    CompileShaders();
}
void Update()
{
    DrawTriangle();
}