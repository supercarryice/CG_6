#define _CRT_SECURE_NO_WARNINGS

#include"IFS.h"

IFS::IFS() :num(0)
{

}

IFS::IFS(char *file)
{
	readFile(file);
}

void IFS::readFile(char *file)
{
	transformation.clear();
	p.clear();

	// open the file
	FILE *input = fopen(file, "r");
	assert(input != NULL);

	// read the number of transforms
	int num_transforms;
	fscanf(input, "%d", &num_transforms);
	assert(num_transforms > 0);

	num = num_transforms;

	float temp = 0;
	for (int i = 0;i < num_transforms;i++) {
		float probability;
		fscanf(input, "%f", &probability);
		Matrix m;
		m.Read3x3(input);

		transformation.push_back(m);
		temp += probability;
		p.push_back(temp);
	}

	p[num_transforms - 1] = 1.01;

	fclose(input);
}

void IFS::render(Image &img, int pointNum, int iter)
{
	Vec3f color(0, 0, 0);
	int width = img.Width();
	int height = img.Height();
	while (pointNum--)
	{
		Vec4f point((float)rand() / 32757, (float)rand() / 32757 , 0 , 1);
		for (int i = 0;i < iter;i++)
		{
			float randfloat = (float)rand() / 32758;
			Matrix m = transformation.back();
			for (int j = 0;j < p.size();j++)
			{
				if (randfloat < p[j])
				{
					m = transformation[j];
					break;
				}
			}
			m.Transform(point);
		}
		int tx = min((int)(point.x()*width), width - 1);
		int ty = min((int)(point.y()*height), height - 1);
		tx = max(tx, 0);
		ty = max(ty, 0);
		img.SetPixel(tx, ty, color);
	}
}