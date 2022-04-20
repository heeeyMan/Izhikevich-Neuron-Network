#pragma once
#include "Neuro_Izik.h"
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>

class Net : public Neuron_Izik{
public:
	Net();
	std::pair<int, int> ind_neuro(int index); // ������� �� ������� ������� ������� ��� � ������� � ��������� neurons
	void Run_tt(Neuron_Izik& a, int time); // ��������������� ������� ��� ������� Run_Kutt() ��� ���� ����� �������� ������������
	void Run_Kutt(); // ������� ����������� ����� ����� - ����� ��� ���� ��������, ����������� �������� ����������� ���������� ������� ���������
	double rand_pow_conn(int min, int max); // ������� ���������� ��������� �������� ���� ����� min < pow_con < max
	void Create_net(); // ������� ����������� ������ � ���������
	void Conn(int a, int b, int rand); // ��������������� ������� ��� ������� Connect() ��� ���� ����� �������� ������������
	void Connect(int x); // �������� ��������� ����� � ����
	void Save_in_file(); // ��������� ������ � ����
protected:
	double prob_conn; // ����������� �����
	int count_neuro; // ������ �������, ����������� �������
	double pow_con; // ��� �����
	std::map<int, std::vector<double>> time_spike; // ������ ����� ������� � ��� ������� ������� � ����
	std::vector<std::vector<Neuron_Izik>> neurons; // ������ �������, ������� ���� � ����
	std::map<int, std::map<int, double>> net_for_post; // ������ ��� ������� ������� ������ ���� ��������, ������� �� ��������� � ���� �������� ������������������
};
void Launch_net(Net& a); // ��������� ���� ���������
