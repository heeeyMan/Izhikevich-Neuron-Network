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
	std::pair<int, int> ind_neuro(int index); // функция по индексу нейрона находит его в массиве с нейронами neurons
	void Run_tt(Neuron_Izik& a, int time); // вспомогательная функция для функции Run_Kutt() для того чтобы избежать дублирования
	void Run_Kutt(); // функция реализующая метод Рунге - Кутта для сети нейронов, описывающих динамику мембранного потенциала нейрона Ижикевича
	double rand_pow_conn(int min, int max); // функция генерирует случайное значение веса связи min < pow_con < max
	void Create_net(); // функция заполняющая массив с нейронами
	void Conn(int a, int b, int rand); // вспомогательная функция для функции Connect() для того чтобы избежать дублирования
	void Connect(int x); // функиция создающая связи в сети
	void Save_in_file(); // сохраняет данные в файл
protected:
	double prob_conn; // вероятность связи
	int count_neuro; // размер массива, содержащего нейроны
	double pow_con; // вес связи
	std::map<int, std::vector<double>> time_spike; // хранит номер нейрона и его времена спайков в сети
	std::vector<std::vector<Neuron_Izik>> neurons; // хранит нейроны, которые есть в сети
	std::map<int, std::map<int, double>> net_for_post; // хранит для каждого нейрона список всех нейронов, которые по отношению к нему являются постсинаптическими
};
void Launch_net(Net& a); // запускает сеть считаться
