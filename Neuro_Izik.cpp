#include "Neuro_Izik.h"

Neuron_Izik::Neuron_Izik() : V_peak(35), i(0), a(0.02), b(0.2), d(8),
k(0.3), c(-65), I_ex(0), V_r(-60), V_t(-40), V0(10), U0(0), Cm(50),
x(0), y(0), x_old(V0), y_old(U0), K1_x(0), K2_x(0), K3_x(0), K4_x(0), K1_y(0), K2_y(0), K3_y(0), K4_y(0),
h(0.5), T_sim(1000), N_sim(T_sim / h), I_syn(N_sim, 0), obstacle(1){}

Neuron_Izik::Neuron_Izik(int i) : V_peak(35), i(i), a(0.02), b(0.5), d(100),
k(0.5), c(-65), I_ex(0), V_r(-60), V_t(-45), V0(-60), U0(0), Cm(50),
x(0), y(0), x_old(V0), y_old(U0), K1_x(0), K2_x(0), K3_x(0), K4_x(0), K1_y(0), K2_y(0), K3_y(0), K4_y(0),
h(0.5), T_sim(1000), N_sim(T_sim / h), I_syn(N_sim, 0), obstacle(1){}

Neuron_Izik::Neuron_Izik(int i_syn, int i) : V_peak(0), i(i), a(0.02), b(0.5), d(100),
k(0.5), c(-65), I_ex(140), V_r(-60), V_t(-45), V0(-60), U0(0), Cm(50),
x(0), y(0), x_old(V0), y_old(U0), K1_x(0), K2_x(0), K3_x(0), K4_x(0), K1_y(0), K2_y(0), K3_y(0), K4_y(0),
h(0.5), T_sim(1000), N_sim(T_sim / h), I_syn(N_sim, i_syn), obstacle(1){}

Neuron_Izik::Neuron_Izik(bool isObtacle, int i) : V_peak(0), i(i), a(0.02), b(0.5), d(100),
k(0.5), c(-65), I_ex(140), V_r(-60), V_t(-45), V0(-60), U0(0), Cm(50),
x(0), y(0), x_old(V0), y_old(U0), K1_x(0), K2_x(0), K3_x(0), K4_x(0), K1_y(0), K2_y(0), K3_y(0), K4_y(0),
h(0.5), T_sim(1000), N_sim(T_sim / h), I_syn(N_sim, 0), obstacle(isObtacle) {}


double Neuron_Izik::K_x(double x_old, double y_old, int time) {
    if (i == 61) {
        bool k = true;
        //std::cout << x_old << " ";
    }
    return (k * (x_old - V_r) * (x_old - V_t) - y_old + I_ex) / Cm;
}
double Neuron_Izik::K_y(double x_old, double y_old) {
    return a * (b * (x_old - V_r) - y_old);
}

bool operator < (const Neuron_Izik& a, const Neuron_Izik& b) {
    return a.i < b.i;
}

