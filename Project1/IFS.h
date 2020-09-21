#pragma once
#include<cstdlib>
#include<vector>
#include<algorithm>
#include"matrix.h"
#include"vectors.h"
#include"image.h"

class IFS
{
	int num; // the number of transformation
	vector <Matrix> transformation;
	vector <float> p; //an array of corresponding probabilities

public:
	IFS();
	IFS(char *file);
	void readFile(char *file);
	void render(Image & img, int pointNum, int iter);
};
