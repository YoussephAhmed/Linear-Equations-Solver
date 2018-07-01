#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include<sstream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <math.h>


using namespace std;





// global functions




bool my_find(string input_string, string compare_string, queue <int> &positions)
{
	priority_queue<int> _operators;

	for (int i = 1; i < input_string.length(); i++)
	{
		for (int j = 0; j < compare_string.length(); j++)
		{
			if (input_string[i] == compare_string[j])
				positions.push(i);
		}
	}



	if (positions.empty())
		return false;

	else
		return true;

}




int digit_finder(string input)
{
	int digit_position = 0;
	int t;
	do
	{
		char temp = input[digit_position];
		t = temp;
		digit_position++;
	} while (!(t <= 57 && t >= 48)); // not a digit

	return digit_position - 1;
}



int char_finder(string input)
{
	int char_position = 0;
	int t;
	do
	{
		char temp = input[char_position];
		t = temp;
		char_position++;
	} while (!(t <= 122 && t >= 65)); // not a char

	return char_position - 1;
}

bool is_digit(string input)
{
	for (int i = 0; i < input.length(); i++)
		if (input[i] <= 122 && input[i] >= 65)
			return false;

	return true;
}



bool is_char(string input)
{
	for (int i = 0; i < input.length(); i++)
		if (input[i] <= 57 && input[i] >= 48)
			return false;

	return true;
}





bool no_digits(string in)
{
	if (in.substr(0, 1) == "-" || in.substr(0, 1) == "+")
		in = in.substr(1, in.length() - 1);

	if (in.substr(0, 1) == "")
		return true;

	return false;

}



class variable
{

public:
	string name;
	float coeff;

	variable(float coeff, string name)
	{
		this->coeff = coeff;
		this->name = name;

	}
};


class equation
{
public:
	vector <variable> vars;
	float result;


	void fix_coeff() // makes different coeff for the same variable one coeff
	{
		map <string, vector <float> > variables;

		while (vars.empty() != true)
		{
			variable temp = vars.back();
			variables[temp.name].push_back(temp.coeff);
			vars.pop_back();
		}



		for (auto it = variables.begin(); it != variables.end(); it++)
		{
			float coeff_sum = 0;

			while (it->second.empty() != true)
			{
				coeff_sum += it->second.back();
				it->second.pop_back();
			}


			variable v(coeff_sum, it->first);
			vars.push_back(v);

		}

	}






	void print_equation()
	{
		string output_equation = "";

		for (int i = 0; i < vars.size(); i++)
		{
			variable v = vars[i];
			float coeff = v.coeff;
			if (coeff != 0)
			{

				string s_coeff;
				ostringstream ss;
				ss << coeff;
				s_coeff = ss.str();

				if (coeff >= 0)
					output_equation += "+";


				output_equation += s_coeff;
				output_equation += vars[i].name;
			}
		}

		string s_result;
		ostringstream ss2;
		ss2 << result;
		s_result = ss2.str();


		output_equation += "=";
		output_equation += s_result;


		if (output_equation.substr(0, 1) == "+")
			output_equation = output_equation.substr(1, output_equation.length() - 1);


		cout << output_equation << endl;

	}


	void add_equation(equation in1, equation in2)
	{


		result = in1.result + in2.result;


		map <string, vector <float> > variables;

		while (in1.vars.empty() != true)
		{
			variable temp = in1.vars.back();
			variables[temp.name].push_back(temp.coeff);
			in1.vars.pop_back();
		}



		while (in2.vars.empty() != true)
		{
			variable temp = in2.vars.back();
			variables[temp.name].push_back(temp.coeff);
			in2.vars.pop_back();
		}



		for (auto it = variables.begin(); it != variables.end(); it++)
		{
			float coeff_sum = 0;

			while (it->second.empty() != true)
			{
				coeff_sum += it->second.back();
				it->second.pop_back();
			}


			variable v(coeff_sum, it->first);
			vars.push_back(v);

		}


		sort_equation();

	}



	void sub_equation(equation in1, equation in2)
	{


		result = in1.result - in2.result;


		map <string, vector <float> > variables;

		while (in1.vars.empty() != true)
		{
			variable temp = in1.vars.back();
			variables[temp.name].push_back(temp.coeff);
			in1.vars.pop_back();
		}



		while (in2.vars.empty() != true)
		{
			variable temp = in2.vars.back();
			variables[temp.name].push_back(-temp.coeff);
			in2.vars.pop_back();
		}





		for (auto it = variables.begin(); it != variables.end(); it++)
		{
			float coeff_sum = 0;

			while (it->second.empty() != true)
			{
				coeff_sum += it->second.back();
				it->second.pop_back();
			}


			variable v(coeff_sum, it->first);
			vars.push_back(v);

		}


		sort_equation();
	}



	void multiply_num(float num)
	{
		result = result*num;

		for (int i = 0; i < vars.size(); i++)
			vars[i].coeff = vars[i].coeff * num;

	}


	void divide_num(float num)
	{
		result = result / num;

		for (int i = 0; i < vars.size(); i++)
			vars[i].coeff = vars[i].coeff / num;

	}



	int find_name(string name)
	{

		for (int i = 0; i < vars.size(); i++)
			if (vars[i].name == name)
				return i;

		return -1;


	}



	void delete_name(string name)
	{
		for (auto it = vars.begin(); it != vars.end(); it++)
			if (it->name == name)
			{
				vars.erase(it);
				return;
			}
	}





	void sort_equation() // Bubble Sort
	{



		for (int i = 0; i < vars.size() - 1; i++)
		{
			for (int j = 0; j < vars.size() - i - 1; j++)
			{
				string test = vars[j].name;

				if (is_char(test) == true)

				{


					string number_string = vars[j].name;



					string number_string2 = vars[j + 1].name;

					if (number_string2 < number_string)
					{
						variable temp = vars[j];
						vars[j] = vars[j + 1];
						vars[j + 1] = temp;

					}

				}


				else
				{
					int digit_position = digit_finder(vars[j].name);
					string number_string = vars[j].name.substr(digit_position, vars[j].name.length() - digit_position);
					float value = atof(number_string.c_str());


					int digit_position2 = digit_finder(vars[j + 1].name);
					string number_string2 = vars[j + 1].name.substr(digit_position, vars[j + 1].name.length() - digit_position);
					float value2 = atof(number_string2.c_str());

					if (value2 < value)
					{
						variable temp = vars[j];
						vars[j] = vars[j + 1];
						vars[j + 1] = temp;

					}


				}

			}
		}



	}




	void fix_missing(queue <string> unique_vars)
	{

		int n = unique_vars.size();

		for (int i = 0; i < n; i++)
		{
			variable v(0, unique_vars.front());
			unique_vars.pop();
			vars.push_back(v);


		}



		fix_coeff();
		sort_equation();

	}

};


class solver
{
public:

	vector < vector <variable> > eq_var;
	vector < vector <variable> > temp;

	vector <float> results;

	int eqs_size;

	bool check_size()
	{
		for (int i = 0; i < eqs_size; i++)
			if (eq_var[i].size() != eqs_size)
				return false;

		return true;

	}


	void fill_solver(vector <equation> in)
	{

		for (int i = 0; i < eqs_size; i++)
		{
			vector <variable> temp;

			for (int j = 0; j < in[i].vars.size(); j++)
			{
				temp.push_back(in[i].vars[j]);

			}

			eq_var.push_back(temp);
			results.push_back(in[i].result);

		}


	}





	void print_D_matrix()
	{
		for (int i = 0; i < eqs_size; i++)
		{
			for (int j = 0; j < eq_var[i].size(); j++)
				cout << eq_var[i][j].coeff << "       ";

			cout << endl;
		}


	}

	void replace_Dx_matrix(string name)
	{
		temp = eq_var;
		int index;
		for (int j = 0; j < eq_var[0].size(); j++)
			if (eq_var[0][j].name == name)
			{
				index = j;
				break;
			}

		for (int i = 0; i < eqs_size; i++)
		{
			for (int j = 0; j < eq_var[i].size(); j++)

				if (j == index)
					eq_var[i][j].coeff = results[i];



		}


	}





	void reset()
	{
		eq_var = temp;
	}

	double determinant(int n, float mat[100][100] , float result)
	{

		int c, subi, i, j, subj;
		float value=0;

		float submat[100][100];

		if (n == 2)
		{

			float t = (mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]);

			return t;
		}

		else
		{
			for (c = 0; c < n; c++)

			{

				subi = 0;

				for (i = 1; i < n; i++)

				{

					subj = 0;

					for (j = 0; j < n; j++)

					{

						if (j == c)

						{

							continue;

						}

						submat[subi][subj] = mat[i][j];

						subj++;

					}

					subi++;

				}

				result = result + (pow(-1, c) * mat[0][c] * determinant(n - 1, submat , result));

				value += result;
				result = 0;

			}


		}

		return value;

	}



	double get_determinant()
	{
		float mat[100][100];


		for (int i = 0; i < eq_var.size(); i++)
			for (int j = 0; j < eq_var[0].size(); j++)
				mat[i][j] = eq_var[i][j].coeff;




		return (determinant(eqs_size, mat , 0));
	}




	void solve()
	{
		if (!check_size())
		{
			cout << "No Solution" << endl;
			return;
		}





		float D_value = get_determinant();

		// getting determinants values
		for (int j = 0; j < eq_var[0].size(); j++)
		{
			replace_Dx_matrix(eq_var[0][j].name);

			float Dx_value = get_determinant();

			float divide = Dx_value / D_value;

			if (isnan(divide))
			{
				cout << "No Solution" << endl;
				return;
			}


			reset();

			cout << eq_var[0][j].name << "=" << divide << endl;

		}



	}

};


int main()
{

	// --> start


	string input_equations[100]; // up to 100 equations
	vector <equation> equations(100);


	int n; // number of equations

	cin >> n;

	// getting the input equations
	for (int i = 0; i < n; i++)
		cin >> input_equations[i];





	// substring the input and save it to the equations object
	string operators = "+-";

	queue <int> positions; // operator positions
	stack <float> constants; // equation constants

	for (int i = 0; i < n; i++)
	{

		int equal_finder = input_equations[i].find("=");
		string before = input_equations[i].substr(0, equal_finder);
		string after = input_equations[i].substr(equal_finder + 1, input_equations[i].length() - equal_finder - 1);



		my_find(before, operators, positions);


		int v_start; // starting position
		int v_end; // ending position
		bool negative = false;
		int flag = true;
		while (positions.empty() != true)
		{
			 // for first case special case
			if (flag)
			{
				v_start = 0;
				v_end = positions.front();
				positions.pop();
				if (before.substr(v_start, 1) == "-")
					negative = true;
				flag = false;


				string s_var = before.substr(v_start, v_end - v_start);

				if (!is_digit(s_var))
				{


					int t = char_finder(s_var);
					string var_coeff = s_var.substr(0, t);

					if (no_digits(var_coeff))
					{
						var_coeff += "1";
					}


					float f_var_coeff = atof(var_coeff.c_str());

					string var_name = s_var.substr(t, s_var.length());

					variable v(f_var_coeff, var_name);

					equations[i].vars.push_back(v);

				}

				else
				{
					float sum = atof(s_var.c_str());
					if (!negative)
						sum *= -1;
					constants.push(sum);
				}
			}



			else
			{
				v_start = v_end;
				v_end = positions.front();
				positions.pop();

				if (before.substr(v_start -1, 1) == "-")
					negative = true;



				string s_var = before.substr(v_start, v_end - v_start);

				if (!is_digit(s_var))
				{


					int t = char_finder(s_var);
					string var_coeff = s_var.substr(0, t);

					if (no_digits(var_coeff))
					{
						var_coeff += "1";
					}


					float f_var_coeff = atof(var_coeff.c_str());

					string var_name = s_var.substr(t, s_var.length() - 1);

					variable v(f_var_coeff, var_name);

					equations[i].vars.push_back(v);

				}

				else
				{
					float sum = atof(s_var.c_str());
					if (!negative)
						sum *= -1;
					constants.push(sum);
				}
			}

		}

		string last = before.substr(v_end , before.length() - v_end);

		if (!is_digit(last))
		{


			int t = char_finder(last);
			string var_coeff = last.substr(0, t);

			if (no_digits(var_coeff))
			{
				var_coeff += "1";
			}


			float f_var_coeff = atof(var_coeff.c_str());

			string var_name = last.substr(t, last.length() - 1);

			variable v(f_var_coeff, var_name);

			equations[i].vars.push_back(v);

		}

		else
		{
			float sum = atof(last.c_str());
			if (!negative)
				sum *= -1;
			constants.push(sum);
		}






		// now the after part

		bool multi_term = my_find(after, operators, positions);
		float final_sum;
		if (multi_term)
		{
			int flag = true; // for first case special case
			while (positions.empty() != true)
			{
								if (flag)
				{
					v_start = 0;
					v_end = positions.front();
					positions.pop();
					if (after.substr(v_start, 1) == "-")
						negative = true;
					flag = false;


					string s_var = after.substr(v_start, v_end - v_start);




						float sum = atof(s_var.c_str());
						if (negative)
							sum *= -1;
						constants.push(sum);

				}



				else
				{
					v_start = v_end;
					v_end = positions.front();
					positions.pop();

					if (before.substr(v_start - 1, 1) == "-")
						negative = true;



					string s_var = after.substr(v_start, v_end - v_start);


					float sum = atof(s_var.c_str());
					if (negative)
						sum *= -1;
					constants.push(sum);

				}

			}



			string last2 = after.substr(v_end , after.length() - v_end);



			float sum2 = atof(last2.c_str());
			if (negative)
				sum2 *= -1;
			constants.push(sum2);



		 final_sum = 0;


		 while (constants.empty() != true)
		 {
			 final_sum += constants.top();
			 constants.pop();
		 }


		}

		else
		final_sum = atof(after.c_str());


		equations[i].result = final_sum;

		equations[i].fix_coeff();
		equations[i].sort_equation();


	}





	set<string>unique_vars;

	for (int i = 0; i < n; i++)

		for (int j = 0; j < equations[i].vars.size(); j++)
			unique_vars.insert(equations[i].vars[j].name);



	queue <string> queue_vars;

	for (auto it = unique_vars.begin(); it != unique_vars.end(); it++)
		queue_vars.push(*it);


	for (int i = 0; i < n; i++)
		equations[i].fix_missing(queue_vars);


	solver s1;
	s1.eqs_size = n;
	s1.fill_solver(equations);


	// operations



	string operation;


	///////////////////////////////////// Level 1 //////////////////////////////////

	do
	{

		operation = "";

		string sub1 = "null";
		string sub2 = "null";
		string sub3 = "null";

		string c;
		stringstream ss;

		getline(cin, c);

		ss << c;
		ss >> operation >> sub1 >> sub2 >> sub3;


		if (operation == "num_vars")
		{


			int num_vars = unique_vars.size();

			cout << num_vars << endl;
		}

		else if (operation == "equation")
		{
			int number;
			number = stoi(sub1);
			number--;
			equations[number].print_equation();
		}


		else if (operation == "column")
		{
			string variable_name;

			variable_name = sub1;

			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < equations[i].vars.size(); j++)
				{
					if (equations[i].vars[j].name == variable_name)
						cout << equations[i].vars[j].coeff << endl;
				}
			}

		}


		///////////////////////////////////// Level 2 //////////////////////////////////

		else if (operation == "add")
		{
			int equation_one;
			int equation_two;


			equation_one = stoi(sub1);
			equation_one--;

			equation_two = stoi(sub2);
			equation_two--;

			equation add_result;

			add_result.add_equation(equations[equation_one], equations[equation_two]);
			add_result.print_equation();
		}



		else if (operation == "subtract")
		{
			int equation_one;
			int equation_two;


			equation_one = stoi(sub1);
			equation_one--;

			equation_two = stoi(sub2);
			equation_two--;


			equation sub_result;

			sub_result.sub_equation(equations[equation_one], equations[equation_two]);
			sub_result.print_equation();
		}




		else if (operation == "substitute")
		{
			string variable_name;
			int equation_one;
			int equation_two;

			variable_name = sub1;

			equation_one = stoi(sub2);
			equation_one--;

			equation_two = stoi(sub3);
			equation_two--;

			equation temp1 = equations[equation_one];
			equation temp2 = equations[equation_two];


			int position1 = temp1.find_name(variable_name);
			int position2 = temp2.find_name(variable_name);

			float coeff1 = temp1.vars[position1].coeff;
			float coeff2 = temp2.vars[position2].coeff;

			temp1.delete_name(variable_name);
			temp2.delete_name(variable_name);

			temp2.divide_num(coeff2);
			temp2.multiply_num(-coeff1);


			equation _result;
			_result.add_equation(temp1, temp2);
			_result.print_equation();



		}


		///////////////////////////////////// Level 3 //////////////////////////////////

		else if (operation == "D" && sub1 != "null")
		{
			s1.replace_Dx_matrix(sub1);
			s1.print_D_matrix();
			s1.reset();
		}


		else if (operation == "D")
		{
			s1.print_D_matrix();
		}

		else if (operation == "D_value")
		{
			cout << s1.get_determinant() << endl;
		}



		else if (operation == "solve")
		{
			s1.solve();
		}



	} while (operation != "quit");


	return 0;
}
