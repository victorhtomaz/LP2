#include <stdio.h>
#include <stdlib.h>

float kgtolibra(float toConvert);
float libratokg(float toConvert);
float kgtoonca(float toConvert);
float oncatokg(float toConvert);

float kgtolibra(float toConvert)
{
	return toConvert * 2.2046;
}

float libratokg(float toConvert)
{
	return toConvert / 2.2046;
}

float kgtoonca(float toConvert)
{
	return toConvert * 35.274;
}

float oncatokg(float toConvert)
{
	return toConvert / 35.274;
}

