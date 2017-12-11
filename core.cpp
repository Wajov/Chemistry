#include "core.h"

string itos(const int n) {
    string s;
    if (n != 0 && (int)abs(n) != 1) {
        for (int t = (int)abs(n); t > 0; t /= 10) {
            s = (char)(t % 10 + '0') + s;
        }
    }
    return s;
}

string toHtml(const string m, const int c) {
    string text;
    for (int i = 0; i < (int)m.size(); i++) {
        if (isdigit(m[i])) {
            text = text + "<sub>" + m[i] + "</sub>";
        } else {
            text += m[i];
        }
    }
    if (c != 0) {
        text += "<sup>" + itos(c) + (c > 0 ? "+" : "-") + "</sup>";
    }
    return text;
}

string simplify(const string s) {
    int count = 1;
    for (int i = (int)s.size() - 2; i > 0 && count; i--) {
        if (s[i] == '(') {
            count--;
        } else if (s[i] == ')') {
            count++;
        }
    }
    return count ? s.substr(1, s.size() - 2) : s;
}

void unpackage(const vector<string> v, vector<string> &vm, vector<int> &vc) {
    for (int k = 0; k < (int)v.size(); k++) {
        string s = v[k], m;
        int c = 0;
        if (*s.rbegin() == '+' || *s.rbegin() == '-') {
            string ts;
            int i;
            for (ts = "", i = (int)s.size() - 2; isdigit(s[i]); i--) {
                ts = s[i] + ts;
            }
            c = ts == "" ? 1 : atoi(ts.c_str());
            c *= *s.rbegin() == '+' ? 1 : -1;
            m = s[i] == ')' ? simplify(s.substr(0, i + 1)) : s.substr(0, i + 1);
        } else {
            m = s;
        }
        vm.push_back(m);
        vc.push_back(c);
    }
}

/* double round(double r)
{
    return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
} */

void analyze(string s, int *E)
{
    int i, j, k, t, s1[101], s2[101];
    string tmp;
    memset(s1, 0, sizeof(s1));
    memset(s2, 0, sizeof(s2));
    for (i = 0; i < (int)s.size(); i++)
    {
        if (s[i] == '[')
            s[i] = '(';
        if (s[i] == ']')
            s[i] = ')';
    }
    for (i = j = 0; i < (int)s.size(); i++)
        if (s[i] > 47 && s[i] < 58)
        {
            t = 0;
            for (; i < (int)s.size() - 1 && s[i + 1] > 47 && s[i + 1] < 58; i++)
                t = t * 10 + s[i] - 48;
            t = t * 10 + s[i] - 48;
            if (s1[j] == 113)
            {
                for (k = j - 1; s1[k]; k--)
                    s2[k] *= t;
                s1[k] = -1;
            }
            else
                s2[j] *= t;
        }
        else
        {
            j++;
            if (s[i] == '(' || s[i] == ')')
            {
                s1[j] = s[i] == '(' ? 0 : 113;
                s2[j] = 0;
            }
            else
            {
                tmp = s[i];
                if (i < (int)s.size() - 1 && s[i + 1] > 96 && s[i + 1] < 123)
                {
                    tmp += s[i + 1];
                    i++;
                }
                for (k = 1; k < 113; k++)
                    if (element[k] == tmp)
                        s1[j] = k;
                s2[j] = 1;
            }
        }
    for (i = 1; i <= j; i++)
        if (s1[i] > 0 && s1[i] < 113)
            *(E + s1[i]) += s2[i];
}

vector <int> balance(vector <string> s1, vector <int> q1, vector <string> s2, vector <int> q2)
{
    int n = (int)q1.size(), m = (int)q2.size(), num = 113, i, j, k, tmp, E[101][113];
    double s, a[114][101], t[114][101], T[101];
    bool flag;
    vector <double> ans;
    vector <int> fin;
    memset(E, 0, sizeof(E));
    ans.clear();
    for (i = 0; i < n; i++)
        analyze(s1[i], E[i + 1]);
    for (i = 0; i < m; i++)
        analyze(s2[i], E[n + i + 1]);
    for (i = 1; i < 113; i++)
    {
        for (j = 1; j <= n; j++)
            t[i][j] = E[j][i];
        for (j = 1; j < m; j++)
            t[i][n + j] = -E[n + j][i];
        t[i][n + m] = E[n + m][i];
    }
    for (i = 1; i <= n; i++)
        t[113][i] = q1[i - 1];
    for (i = 1; i < m; i++)
        t[113][n + i] = -q2[i - 1];
    t[113][n + m] = q2[m - 1];
    for (i = 1; i < n + m; i++)
    {
        for (tmp = 0, j = 1; j <= num; j++)
        {
            flag = false;
            for (k = 1; !flag && k < n + m; k++)
                if (t[j][k])
                    flag = true;
            if (flag)
                memcpy(a[++tmp], t[j], sizeof(t[j]));
            else
                if (t[j][n + m])
                    return fin;
        }
        if ((num = tmp) < n + m - 1)
            return fin;
        flag = false;
        for (j = i; !flag && j <= num; j++)
            if (a[j][i])
            {
                memcpy(T, a[i], sizeof(T));
                memcpy(a[i], a[j], sizeof(T));
                memcpy(a[j], T, sizeof(T));
                flag = true;
            }
        if (!flag && i < n + m - 1)
            return fin;
        for (j = i + 1; j <= n + m; j++)
            a[i][j] /= a[i][i];
        a[i][i] = 1;
        for (j = i + 1; j <= num; j++)
        {
            for (k = i + 1; k <= n + m; k++)
                a[j][k] -= a[i][k] * a[j][i];
            a[j][i] = 0;
        }
        memcpy(t, a, sizeof(a));
    }
    for (i = 1; i < n + m; i++)
        ans.push_back(0);
    for (i = n + m - 1; i; i--)
    {
        for (j = i + 1; j < n + m; j++)
            a[i][n + m] -= a[i][j] * ans[j - 1];
        ans[i - 1] = a[i][n + m] / a[i][i];
    }
    for (i = n + m; i <= num; i++)
    {
        for (s = 0, j = 1; j <= n + m; j++)
            s += a[i][j] * ans[j - 1];
        if (fabs(s - a[i][n + m]) > 1e-5)
        {
            ans.clear();
            return fin;
        }
    }
    flag = false;
    for (i = 1; !flag; i++)
    {
        flag = true;
        for (j = 1; flag && j < n + m; j++)
            if (fabs((int)(ans[j - 1] * i + 0.5) - ans[j - 1] * i) > 1e-5)
                flag = false;
    }
    for (j = 1; j < n + m; j++)
        ans[j - 1] *= i - 1;
    ans.push_back(i - 1);
    for (i = 0; i < n + m; i++)
        if (fabs(ans[i]) < 1e-5)
            return fin;
    for (i = 0; i < n + m; i++)
        fin.push_back((int)(ans[i] + 0.5));
    return fin;
}
