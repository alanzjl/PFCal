#include "stdafx.h"
#include <Eigen/Dense>
#include "Element_class.h"
using namespace std;


void Bus_input(Bus bus[])
{
	cout << "How many buses in the power system (less than 100) : " << endl;
	cin >> total_buses;
	cout << "Please input the buses in order\n";
	double real, imag;
	for (int i = 0; i < total_buses; i++)
	{
		bus[i].id = i;
		cout << "Which kind of bus? (0 for Vθ, 1 for PV, 2 for PQ)" << endl;
		cin >> bus[i].type;
		switch (bus[i].type)
		{
			case Bus_VT:
				cout << "Input the rating voltage for Vθ bus" << endl;
				cin >> bus[i].v_rating;
				cout << "Input the real part of real voltage for Vθ bus" << endl;
				cin >> real;
				cout << "Input the imag part of real voltage for Vθ bus" << endl;
				cin >> imag;
				bus[i].v.set(real, imag);
				break;
			case Bus_PV:
				cout << "Input the rating voltage for PV bus" << endl;
				cin >> bus[i].v_rating;
				cout << "Input the active power P for PV bus" << endl;
				cin >> bus[i].P;
				cout << "Input the voltage magnitude for PV bus" << endl;
				cin >> bus[i].v_mag;
				break;
			case Bus_PQ:
				cout << "Input the rating voltage VN for PQ bus" << endl;
				cin >> bus[i].v_rating;
				cout << "Input the active power P for PQ bus" << endl;
				cin >> bus[i].P;
				cout << "Input the reactive power Q for PQ bus" << endl;
				cin >> bus[i].Q;
				break;
			default:
				cout << "Wrong input!" << endl;
		}
	}

	cout << "Now: " << endl;
	for (int i = 0; i < total_buses; i++)
	{
		cout << "Bus #" << i <<  ": ";
		switch (bus[i].type)
		{
			case Bus_VT:
				cout << "Vθ bus ( V = " << bus[i].v << " )" << endl;
				break;
			case Bus_PV:
				cout << "PV bus ( Vmag = " << bus[i].v_mag << "; P = " << bus[i].P << " )" << endl;
				break;
			case Bus_PQ:
				cout << "PQ bus ( P = " << bus[i].P << " Q = " << bus[i].Q << ")" << endl;
				break;
		}
	}
}

void Line_input(Line line[])
{
	cout << endl << "Input the transmission line:" << endl;
	cout << "From where to where ( 0 1) " << endl;
}

void GetMatrixY(double Y[MAX_BUSES][MAX_BUSES][2])
{
	for (int i = 0; i < total_buses; i++)
	{
		for (int j = 0; j < total_buses; j++)
		{
			cout << "输入Y[" << i << "][" << j << "]: ";
			cin >> Y[i][j][0] >> Y[i][j][1];
		}
	}
}

void Initialize_Bus(Bus bus[])
{
	for (int i = 0; i < total_buses; i++)
	{
		if (bus[i].type != Bus_VT)								//not V_theta bus
		{
			Complex init(1, 0);
			bus[i].v_es[0] = init;								//initailize voltage: 220+j0
		}
		else
		{
			for (int j = 0; j < MAX_ITERATION; j++)				//initailize  v_theta voltage
			{
				bus[i].v_es[j] = bus[i].v;
			}
		}
	}
}

void Calculate_Voltage(Bus bus[], Line line[], double Y[MAX_BUSES][MAX_BUSES][2])
{
	int itr_num = 0;								 	//number of interaction
	int equ_num = 2 * (total_buses - num_VT);		   //number of eqations
	VectorXd delta_f(equ_num);
	MatrixXd J(equ_num, equ_num);					  //Jacobi matrix

	while (1)
	{
		for (int i = 1; i < total_buses; i++)	//将 v_theta 置于0 
		{
			int row = 2 * (i - num_VT);
			if (bus[i].type == Bus_PQ)
			{
				//calculate aii and bii
				double aii = 0, bii = 0;
				for (int j = 0; j < total_buses; j++)
				{
					aii += Y[i][j][0] * bus[j].v_es[itr_num].real() -					//Ge-Bf
						Y[i][j][1] * bus[j].v_es[itr_num].imag();

					bii += Y[i][j][0] * bus[j].v_es[itr_num].imag() +			//Gf+Be
						   Y[i][j][1] * bus[j].v_es[itr_num].real();

					//set Jacobi matrix
					int col = 2 * j;

					if (j >= total_buses - num_VT || row < 0) continue;
					//Hij
					J(row, col) = -Y[i][j + num_VT][1] * bus[i].v_es[itr_num].real()	//不算0行0列
						+ Y[i][j + num_VT][0] * bus[i].v_es[itr_num].imag();

					//Nij
					J(row, col + 1) = +Y[i][j + num_VT][0] * bus[i].v_es[itr_num].real()
						+ Y[i][j + num_VT][1] * bus[i].v_es[itr_num].imag();

					//Jij = -Nij
					J(row + 1, col) = -J(row, col + 1); 

					//Lij = Hij
					J(row + 1, col + 1) = J(row, col);
				}

				bus[i].P_es[itr_num] = bus[i].v_es[itr_num].real() * aii +			//Pi
					bus[i].v_es[itr_num].imag() * bii;

				bus[i].Q_es[itr_num] = bus[i].v_es[itr_num].imag() * aii -		//Qi
					bus[i].v_es[itr_num].real() * bii;

				for (int j = 0; j < total_buses - num_VT; j++)
				{
					int col = 2 * j;
					if (i == j + num_VT)					// on diagonal
					{
						//modify Hii
						J(row, col) += bii;
						//modify Nii
						J(row, col + 1) += aii;
						//modify Jii
						J(row + 1, col) += aii;
						//modify Lii
						J(row + 1, col + 1) -= bii;
					}
				}

				//cout << "J: " << endl << J << endl;

				delta_f[row] = bus[i].P - bus[i].P_es[itr_num];
				delta_f[row + 1] = bus[i].Q - bus[i].Q_es[itr_num];		//set delta_f
			}

			else if (bus[i].type == Bus_PV)
			{
				//calculate aii and bii
				double aii = 0, bii = 0;
				int row = 2 * (i - num_VT);
				for (int j = 0; j < total_buses; j++)
				{
					aii += Y[i][j][0] * bus[j].v_es[itr_num].real() -					//Ge-Bf
						Y[i][j][1] * bus[j].v_es[itr_num].imag();

					bii += Y[i][j][0] * bus[j].v_es[itr_num].imag() +			//Gf+Be
						Y[i][j][1] * bus[j].v_es[itr_num].real();

					//set Jacobi matrix
					int col = 2 * j;

					if (j >= total_buses - num_VT || row < 0) continue;
					//Hij
					J(row, col) = -Y[i][j +num_VT][0] * bus[i].v_es[itr_num].real()
						+ Y[i][j + num_VT][1] * bus[i].v_es[itr_num].imag();

					//Nij
					J(row, col + 1) = +Y[i][j + num_VT][1] * bus[i].v_es[itr_num].real()
						+ Y[i][j + num_VT][0] * bus[i].v_es[itr_num].imag();

					//Rij = 0
					J(row + 1, col) = 0;

					//Sij = 0
					J(row + 1, col + 1) = 0;
				}

				bus[i].P_es[itr_num] = bus[i].v_es[itr_num].real() * aii +				//Pi
					bus[i].v_es[itr_num].imag() * bii;
				bus[i].v_mag_es[itr_num] = sqrt(pow(bus[i].v_es[itr_num].real(), 2) +		//Vi^2
					pow(bus[i].v_es[itr_num].imag(), 2));	

				for (int j = 0; j < total_buses - num_VT; j++)
				{
					int col = 2 * j;
					if (i == j + num_VT)
					{
						//modify Hii
						J(row, col) += bii;

						//modify Sii
						J(row + 1, col + 1) = 2 * bus[i].v_es[itr_num].real();

						//modify Nii
						J(row, col + 1) += aii;

						//modify Rii
						J(row + 1, col) = 2 * bus[i].v_es[itr_num].imag();
					}
				}

				delta_f[row] = bus[i].P - bus[i].P_es[itr_num];
				delta_f[row + 1] = pow(bus[i].v_mag , 2) - pow(bus[i].v_mag_es[itr_num], 2);	//set delta_f
			}
		}

		VectorXd delta_x(equ_num);
		delta_x = J.inverse() * delta_f;

		if (J.determinant() == 0)
		{
			cout << "Data error, J is not invertable!" << endl;
			return;
		}
			
		//cout << "J: " << endl << J << endl;
		//cout << "Delta_f: " << endl << delta_f << endl;
		//cout << "Delta_X: " << endl << delta_x << endl;
		
		itr_num++;
		int is_end_flag = 1;
		for (int i = 1; i < total_buses; i++)
		{
			if (delta_x(i) >= pow(10, -5))
			{
				is_end_flag = 0;
			}
			int row = 2 * (i - num_VT);
			if (row < 0) continue;
			bus[i].v_es[itr_num].set(										//update estimated v
				bus[i].v_es[itr_num - 1].real() + delta_x(row + 1), 
				bus[i].v_es[itr_num - 1].imag() + delta_x(row)
				);
		};
		if (is_end_flag)
		{
			cout << "\nCalculation end!!" << endl << "Number of iterations: " << itr_num << endl;
			//cout << "J: " << endl << J << endl;
			//cout << "Delta_X: " << endl << delta_x << endl;
			for (int j = 0; j < total_buses; j++)
			{
				bus[j].v = bus[j].v_es[itr_num];
			}
			break;
		}
			
	}

}

void Calculate_Power(Bus bus[], double Y[MAX_BUSES][MAX_BUSES][2])
{
	//power on VT and PV bus
	for (int i = 0; i < total_buses; i++)
	{
		if (bus[i].type != Bus_PQ)
		{
			Complex sum;
			for (int j = 0; j < total_buses; j++)
			{
				Complex Yij(Y[i][j][0], Y[i][j][1]);
				Complex Uj(bus[j].v.real(), bus[j].v.imag());
				sum = Yij.conjugate() * Uj.conjugate();
			}
			bus[i].P = (bus[i].v * sum).real();
			bus[i].Q = (bus[i].v * sum).imag();
		}
	}
}

void Print_Result(Bus bus[])
{
	for (int i = 0; i < total_buses; i++)
	{
		Complex S(bus[i].P, bus[i].Q);
		cout << "Bus #" << i << ": V = (" << bus[i].v << ")V " << " S = ( " << S << ")VA" << endl;
	}
}

/*int main()
{
	//test();
	Bus bus[MAX_BUSES];
	Bus_input(bus);
	Line line[MAX_BUSES];
	Line_input(line);
	double Y[MAX_BUSES][MAX_BUSES][2];		// Y : [MAX_BUSES][MAX_BUSES][2] real+imag
	GetMatrixY(Y);
	Initialize_Bus(bus);
	Calculate_Voltage(bus, line, Y);
	Calculate_Power(bus, Y);
	Print_Result(bus);
	return 0;
}*/