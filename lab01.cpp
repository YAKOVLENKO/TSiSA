#include<iostream>
#include<vector>

std::vector<std::vector<float>> newSymplex(std::vector<std::vector<float>> obj, int col, int line)
{
	std::vector<std::vector<float>> tmpSymplex = obj;
	tmpSymplex[line][col] = 1 / obj[col][line];
	for (int i = 0; i < 4; ++i)
	{
		tmpSymplex[i][line] = - obj[i][line] / obj[col][line];
		tmpSymplex[col][i] = obj[col][i] / obj[col][line];
	}
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (i != col || j != line)
				tmpSymplex[i][j] = obj[i][j] - obj[i][line] * obj[col][j] / obj[col][line];
		}
	}
	return tmpSymplex;
}


bool Check(std::vector<std::vector<float>> tmp, int i, int j, bool val)
{
	if (val == 0)
	{
		for (int k = 0; k < j; ++k)
			if (tmp[i][k] < 0) return true;
	}
	else
	{
		for (int k = 0; k < j; ++k)
			if (tmp[i][k] > 0) return true;
	}
	std::cout << "Error! No solutions!" << std::endl;
	return 0;
}

std::vector<int> FillCin(std::vector<int> tmp)
{
	int smth = 0;
		for (int i = 0; i < 3; ++i)
		{
			std::cin >> smth;
			tmp.push_back(smth);
		}
		return tmp;
}

template <typename N, typename T>
std::vector<N> Fill(std::vector<N> tmp, T val)
{
	for (int i = 0; i < 4; ++i)
		tmp.push_back(val);
	return tmp;
}

int Find(std::string what, int i, int from, int till, std::vector<std::vector<float>> tmp, bool val)
{
	if (val == 0)
	{
		if (what == "line")
			for (int k = from; k < till; ++k)
			{
				if (tmp[i][k] < 0) return k;
			}
		else
		{
			for (int k = from; k < till; ++k)
				if (tmp[k][i] < 0) return k;
		}
		std::cout << "Error! No solutions!" << std::endl;
		return -1;
	}
	else
	{
		if (what == "line")
		{
			for (int k = from; k < till; ++k)
				if (tmp[i][k] >= 0) return k;
		}
		else
		{
			for (int k = from; k < till; ++k)
				if (tmp[i][k] >= 0) return k;
		}
		std::cout << "Error! No solutions!" << std::endl;
		return -1;
	}
}

float FindMin(std::vector<std::vector<float>> obj, int col)
{
	float FutureR = -1;
	std::vector<float> min;
	float tmp = 0;
		for (int i = 0; i < 3; ++i)
		{
			min.push_back(obj[0][i] / obj[col][i]);
			if (min[i] >= 0 && min[i] > tmp) tmp = min[i];
		}
		for (int i = 0; i < 3; ++i)
		{
			if (min[i] >= 0 && min[i] < tmp)
				tmp = min[i];
			FutureR = i;
		}
		return FutureR;
	}

int main()
{
	std::vector<std::vector<float>> symplex;
	int k = -1;
	int r = -1;
	
	{ // заполнение таблиц
		std::vector<float> sline;
		sline = Fill(sline, 0);
		symplex = Fill(symplex, sline);
		float ftmp = 0;
		std::vector<float> line;
		std::vector<int> b;
		std::vector<int> c;
		std::vector<std::vector<float>> A;
		std::cout << "Write A: " << std::endl;
		for (int i = 0; i < 3; ++i)
		{
			std::cout << "Column #" << i + 1 << " ";
			for (int j = 0; j < 3; ++j)
			{
				std::cin >> ftmp;
				line.push_back(ftmp);
			}
			A.push_back(line);
			line.clear();
		}
		std::cout << "Write b: " << std::endl;
		b = FillCin(b);
		std::cout << "Write c: " << std::endl;
		c = FillCin(c);
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (i == 0 && j < 3)
					symplex[i][j] = b[j];
				else if (j == 3 && i > 0)
					symplex[i][j] = c[i - 1];
				else if (i > 0 && j < 4)
					symplex[i][j] = A[i - 1][j];
				else symplex[i][j] = 0;
			}
		}
	}
	
	{	
		if (Find("column", 1, 0, 3, symplex, 0) != -1)
			k = Find("line", Find("column", 1, 0, 3, symplex, 0), 1, 4, symplex, 0);
		else {
			std::cout << "No results!" << std::endl;
			return 0;
		}
		if (k != -1)
		{
			r = FindMin(symplex, k);
			if (r == -1) {
				std::cout << "No results!" << std::endl;
				return 0;
			}
			symplex = newSymplex(symplex, k, r);
		}
		else {
			std::cout << "No results!" << std::endl;
			return 0;
		}
	}

	while (Find("line", 3, 0, 4, symplex, 1) != -1)
	{
		k = Find("line", 3, 0, 4, symplex, 1);
		if (k < 0) return 0;
		r = FindMin(symplex, k);
		if (r < 0) return 0;
		symplex = newSymplex(symplex, k, r);
	}
	
}
