#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = a, _b = (b); i <= _b; ++i)
#define REP(i, a, b) for (int i = a, _b = (b); i < _b; ++i)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; --i)
#define nl cout << endl
#define endl '\n'

#define JUDGE(name) if (fopen(name".inp", "r")) { freopen(name".inp","r",stdin); freopen(name".out","w",stdout); }

int getDay () {
    int n;
    int low = 1, high = 31;
    do {
        cout << "Nhap so ngay trong khoang [" << low << ", " << high << "]: ";
        cin >> n;
    } while (n < low || n > high);
    return n;
}

int getMonth () {
    int n;
    int low = 1, high = 12;
    do {
        cout << "Nhap so thang trong khoang [" << low << ", " << high << "]: ";
        cin >> n;
    } while (n < low || n > high);
    return n;
}

int getYear () {
    int n;
    int low = 2000, high = 2099;
    do {
        cout << "Nhap so nam trong khoang [" << low << ", " << high << "]: ";
        cin >> n;
    } while (n < low || n > high);
    return n;
}

/*
31: 1,3,5,7,8,10,12
30: 4,6,9,11
28-29: 2
*/
const int numDay[] = {-1,31,28,31,30,31,30,31,31,30,31,30,31};

bool isValid (int date, int month, int year) {
    if (year % 4 != 0 || year % 400 == 0) { // ko phai nam nhuan
        if (date <= numDay[month]) return 1; // ngay X thuoc thang
    } else { // nam nhuan
        if (month == 2) {
            if (date <= numDay[month] + 1) return 1;
        } else if (date <= numDay[month]) return 1;
    }

    return 0;
}

void getDate (int& day, int& month, int& year) {
    do {
        day = getDay();
        month = getMonth();
        year = getYear();
    } while (!isValid(day, month, year));
    nl;
}

bool check (int year) {
    if (year % 4 == 0 || year % 400 == 0) return 1;
    return 0;
}

int totalDay (int year) {
    if (check(year)) return 366;
    return 365;
}

int getDist (int day1, int month1, int year1, int day2, int month2, int year2) {
    int cntDay;
    if (year1 != year2) { // khac nam
        cntDay = 0;
        for(int i=year1+1; i<year2; i++) cntDay += totalDay(i);
        cout << cntDay << endl;
        if (month1 != 12) for(int i=month1+1; i<=12; i++) cntDay += numDay[i];
        cout << cntDay << endl;
        if (month2 != 1) for(int i=1; i<month2; i++) cntDay += numDay[i];
        cout << cntDay << endl;
        if (month1 <= 2 && check(year1)) cntDay++;
        if (month2 >= 2 && check(year2)) cntDay++;
        cout << cntDay << endl;
        cntDay += (numDay[month1] - day1 + 1);
        cntDay += day2;
        cout << cntDay << endl;
        return cntDay;
    } else { // cung nam
        cntDay = 0;
        if (month1 != month2) {
            if (month1 != 12) for(int i=month1+1; i<month2; i++) cntDay += numDay[i]; // thang kh chua ngay nhap vao input
            if (check(year1) && (month1 <= 2 && month2 >= 2)) cntDay++;
            cntDay += (numDay[month1] - day1 + 1); // so ngay tu day1 den het thang
            cntDay += day2; // so ngay tu dau thang den day2
        } else cntDay += (day2 - day1) + 1; // so ngay trong cung 1 thang
        return cntDay;
    }
}

void sortDay (int day1, int month1, int year1, int day2, int month2, int year2) {
    if (year1 != year2) { // khac nam
         if (year1 > year2) {
            swap(year1,year2);
            swap(month1, month2);
            swap(day1, day2);
         }
    } else {
        if (month1 != month2) { // khac thang
            if (month1 > month2) {
                swap(month1, month2);
                swap(day1, day2);
            }
        } else {
            if (day1 != day2 && day1 > day2) swap(day1, day2);
        }
    }
}

void solve (void) {
    int day1, month1, year1, day2, month2, year2;
    cout << "NHAP THOI DIEM T1" << endl;
    getDate(day1, month1,year1);
    cout << "NHAP THOI DIEM T2" << endl;
    getDate(day2, month2,year2);

    sortDay(day1, month1, year1, day2, month2, year2);
    int delta = getDist (day1, month1, year1, day2, month2, year2);
    cout << "SO NGAY GIUA T1 VA T2: " << delta;
}

int main () {
//    ios::sync_with_stdio(0);
//    cin.tie(0); cout.tie(0);
    // JUDGE("woody");

    solve();

}
