#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;

const string element[113] = {"", "H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne",
                             "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca",
                             "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn",
                             "Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y", "Zr",
                             "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn",
                             "Sb", "Te", "I", "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd",
                             "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb",
                             "Lu", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg",
                             "Tl", "Pb", "Bi", "Po", "At", "Rn", "Fr", "Ra", "Ac", "Th",
                             "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm",
                             "Md", "No", "Lr", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg", "Cn"};

string itos(const int n);
string toHtml(const string m, const int c = 0);
string simplify(const string s);
void unpackage(const vector<string> v, vector<string> &vm, vector<int> &vc);
double round(double r);
void analyze(string s, int *E);
vector <int> balance(vector <string> s1, vector <int> q1, vector <string> s2, vector <int> q2);

#endif // CORE_H
