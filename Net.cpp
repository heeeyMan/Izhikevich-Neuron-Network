#include "Net.h"
Net::Net() : prob_conn(65), count_neuro(11), pow_con(0){}

std::pair<int, int> Net:: ind_neuro(int index){
    int i = index / count_neuro;
    int j = index % count_neuro;
    if (j != 0) {
        j -= 1;
    }else {
        i -= 1;
        j = count_neuro - 1;
    }
    std::pair<int, int> res(i, j);
    return res;
}
void Net::Run_tt(Neuron_Izik& a, int time){ //реализация метода Рунге-Кутта для определенного нейрона в конкретную единицу времени
    if (a.I_syn[time] != 0){
        a.K1_x = a.K_x(a.x_old, a.y_old, time);
        a.K2_x = a.K_x(a.x_old + h / 2, a.y_old + h / 2 * a.K1_x, time);
        a.K3_x = a.K_x(a.x_old + h / 2, a.y_old + h / 2 * a.K2_x, time);
        a.K4_x = a.K_x(a.x_old + h, a.y_old + h * a.K3_x, time);

        a.x = a.x_old + (a.K1_x + 2 * a.K2_x + 2 * a.K3_x + a.K4_x) * h / 6;

        a.K1_y = a.K_y(a.x_old, a.y_old);
        a.K2_y = a.K_y(a.x_old + h / 2, a.y_old + h / 2 * a.K1_y);
        a.K3_y = a.K_y(a.x_old + h / 2, a.y_old + h / 2 * a.K2_y);
        a.K4_y = a.K_y(a.x_old + h, a.y_old + h * a.K3_y);

        a.y = a.y_old + (a.K1_y + 2 * a.K2_y + 2 * a.K3_y + a.K4_y) * h / 6;

        if (a.x > a.V_peak) { // условие генерации спайка
            if (time < N_sim - 1) {
                for (auto it = net_for_post[a.i].begin(); it != net_for_post[a.i].end(); ++it) {
                    neurons[ind_neuro(it->first).first][ind_neuro(it->first).second].I_syn[time + 1] += a.y * it->second;
                }
            }
            a.x = c;
            a.y += d;
            time_spike[a.i].push_back(time);
        }
        a.V.push_back(a.x);
        a.U.push_back(a.y);
        a.x_old = a.x;
        a.y_old = a.y;
    }
}

void Net::Run_Kutt(){ 
    for (int time = 0; time < N_sim; ++time){
        for (int i = 0; i < count_neuro; ++i) {
            for (int j = 0; j < count_neuro; ++j){        
                Run_tt(neurons[i][j], time);
            }
        }
    }
}
void Net::Create_net(){
    neurons.resize(count_neuro);
    static int index = 1;
    for (int i = 0; i < count_neuro; ++i){
        for (int j = 0; j < count_neuro; ++j) {
            Neuron_Izik new_neuro(index);
            neurons[i].push_back(new_neuro);
            ++index;
        }
    }
    Neuron_Izik gen(0, 20);
    gen.i = neurons[count_neuro / 2][count_neuro / 2].i;
    neurons[count_neuro / 2][count_neuro / 2] = gen;
}
double Net::rand_pow_conn(int min, int max) {
    return min + rand() % (1000 * (max - min)) / 1000.0f;
}
void Net::Conn(int a, int b, int random){
    int rand_i = 0;
    int rand_j = 0;
    for (int i = -1; i < 2; ++i) { 
        for (int j = -1; j < 2; ++j) {
            if ((i == 0 && j == 0)) {
                continue;
            }else {
                random = rand() % 100; /*генерируем случайное число для того чтобы реализовать 
                                       случайное распределение связей, т. е. если prob_conn >= random, то создается связь*/
                if (prob_conn >= random) {
                    //pow_con = rand_pow_conn(5, 100);
                    net_for_post[neurons[a][b].i].insert(std::pair<int, double>(neurons[a + i][b + j].i, pow_con));

                    //random = rand() % 10;
                    //rand_i = random;
                    //random = rand() % 10;
                    //rand_j = random;
                    //net_for_post[neurons[a][b].i].insert(std::pair<int, double>(neurons[rand_i][rand_j].i, pow_con)); // добавление нелокальных случайных связей
                } 
            }
        }
    }
}
void Net::Connect(int random){
    Conn(((count_neuro / 2) + 1), ((count_neuro / 2) + 1), random); // задаем связи для центрального нейрона
    int z, m, n;
    for (int k = count_neuro / 2; k > 0; --k) { // задаем связи для всех других нейронов, двигаять по квадратам от центра
        z = (count_neuro / 2 - k) + count_neuro / 2;
        m = k;
        n = k;
        for (; m <= z; ++m){
            Conn(m, n, random);
        }
        --m;
        for (; n <= z; ++n){
            Conn(m, n, random);
        }
        --n;
        for (; m >= k; --m){
            Conn(m, n, random);
        }
        ++m;
        for (; n > k; --n){
            Conn(m, n, random);
        }
    }


}

void Net::Save_in_file() {
    std::ofstream my_file;
    std::string file_name = "no_rand (pow_con = 10).csv";
    my_file.open(file_name); 
    my_file << 
        "Вероятность установления связи: " << prob_conn << std::endl <<
        "Количество нейронов: " << count_neuro * count_neuro << std::endl <<
        "Вес связи по-умолчанию: " << pow_con << std::endl << 
        "Величина порога: " << neurons[0][0].V_peak << std::endl;

    for (auto it = time_spike.begin(); it != time_spike.end(); ++it){
        my_file << it->first << "; ";
        //std::cout << it->first << ": ";
        for (int i = 0; i < it->second.size(); ++i){
            my_file << it->second[i] << "; ";
            //std::cout << it->second[i] << " ";
        }
        my_file << std::endl;
        //std::cout << std::endl;
    }
    my_file.close();
}
void Launch_net(Net& net){
    net.Create_net();
    srand(time(NULL));
    int random_conn = rand();
    net.Connect(random_conn);
    net.Run_Kutt();
    net.Save_in_file();
}