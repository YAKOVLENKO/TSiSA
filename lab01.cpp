#include<iostream>
#include<vector>

std::vector<std::vector<float>> NewSymplex(std::vector<std::vector<float>> symplex, int r, int k)
{
	
	std::vector<std::vector<float>> tmp = symplex;
	tmp[r][k] = 1 / symplex[r][k];

	float &rk = symplex[r][k];

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (j == k && i != r)
				tmp[i][j] = - symplex[i][j] / rk;
			else if (j != k && i == r)
				tmp[i][j] = symplex[i][j] / rk;
			else if ((j != k && i != r) || (j != k) || (i != r))
				tmp[i][j] = symplex[i][j] - symplex[r][j] * symplex[i][k] / rk;
		}
	}

	return tmp;
}

template< typename T>
std::vector<T> Fill(std::vector<T> tmp, T obj, int t)
{
	for (int i = 0; i < t; ++i)
		tmp.push_back(obj);
	return tmp;
}

int main()
{
	float z = 0;
	int r = 0, k = 0;
	std::vector<std::vector<float>> symplex;
	std::vector<float> line;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			std::cin >> z;
			line.push_back(z);
		}
		symplex.push_back(line);
		line.clear();
	}
	while (z < 100)
	{
		std::cout << "Write line r: ";
		std::cin >> r;
		std::cout << "Write column k: ";
		std::cin >> k;
		symplex = NewSymplex(symplex, r, k);
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				std::cout << symplex[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}
