# LAB 03.03
##### Họ và tên: Nguyễn Minh Thành - MSSV: 25521710

## Đề bài:
Viết chương trình nhập vào 2 số nguyên dương M, N và thực hiện các việc:
* (a) Kiểm tra M và N có phải số nguyên tố.
* (b) Liệt kê các số nguyên tố nằm giữa M và N (gọi danh sách các số này là L ).
* (c) Tìm số có tổng các chữ số là lớn nhất trong danh sách L .
* (d) Tìm trong L các số nguyên tố Palindrome (là các số khi các chữ số theo thứ tự ngược thì vẫn là nó, ví dụ: 131)
* (e) Tìm trong L tất cả các cặp số lẻ liền kề (chênh nhau 2) và cho biết có bao nhiêu cặp.
* (f) Tìm trong L các cặp số có tổng là M+N.

## Thuật toán:
##### (a) Kiểm tra M và N có phải số nguyên tố
1. Dùng **sàng Eratosthenes** để tạo mảng `isPrime[]`:  
   - Gán `isPrime[i] = true` với mọi `i` từ 0 đến MAXN.  
   - Gán `isPrime[0] = isPrime[1] = false`.  
   - Với mỗi `i` từ 2 đến √MAXN:  
     - Nếu `isPrime[i]` là true, đánh dấu mọi bội `j = i*i, i*i+i, ... < MAXN` là false.  
2. Sau khi sàng:  
   - Nếu `isPrime[M] == true` → M là số nguyên tố.  
   - Nếu `isPrime[N] == true` → N là số nguyên tố.

---

##### (b) Liệt kê các số nguyên tố nằm giữa M và N
1. Tạo danh sách rỗng `L`.  
2. Với mỗi `i` trong đoạn `[M, N]`:  
   - Nếu `isPrime[i] == true`, thêm `i` vào danh sách `L`.  
3. In ra các phần tử trong `L`.

---

##### (c) Tìm số có tổng các chữ số lớn nhất trong L
1. Khởi tạo `maxSum = -1`, `num = -1`.  
2. Với mỗi phần tử `x` trong `L`:  
   - Gọi `sum = 0`.  
   - Trong khi `x > 0`:  
     - `sum += x % 10`  
     - `x /= 10`  
   - Nếu `sum > maxSum`:  
     - `maxSum = sum`  
     - `num = x`  
3. Kết quả là `num` (số có tổng chữ số lớn nhất).

---

##### (d) Tìm các số nguyên tố Palindrome trong L
1. Với mỗi số `x` trong `L`:  
   - Lưu các chữ số của `x` vào mảng `digits[]`.  
   - So sánh đối xứng:  
     - Nếu `digits[i] == digits[cnt-1-i]` với mọi `i` từ 0 đến `cnt/2 - 1`, thì `x` là Palindrome.  
2. In ra các số thỏa mãn điều kiện.

---

##### (e) Đếm cặp số lẻ liền kề trong L chênh nhau 2
1. Khởi tạo `count = 0`.  
2. Duyệt `i` từ 0 đến `len(L) - 2`:  
   - Nếu `L[i]` và `L[i+1]` đều lẻ (`%2 != 0`) **và** `|L[i] - L[i+1]| == 2`:  
     - `count++`  
3. Kết quả là `count`.

---

##### (f) Đếm các cặp số trong L có tổng bằng M + N
1. Khởi tạo `count = 0`.  
2. Duyệt hai vòng lặp lồng nhau:  
   - Với `i` từ 0 đến `len(L) - 1`  
   - Với `j` từ `i+1` đến `len(L) - 1`  
   - Nếu `L[i] + L[j] == M + N`, thì `count++`.  
3. Kết quả là `count`.

## Source Code
```c++
// LAB0303.cpp
#include <bits/stdc++.h>
using namespace std;

#define JUDGE(name) if (fopen(name".inp", "r")) { freopen(name".inp","r",stdin); freopen(name".out","w",stdout); }
const int MAXN = 1e6+5;
bool isPrime[MAXN];

void Eratosthenes () { // if i is a prime number --> isPrime[i] = true
    for(int i=0; i < MAXN; i++) isPrime[i] = true;
    isPrime[0] = isPrime[1] = false;
    for(int i=2; i*i < MAXN; i++) {
        if(isPrime[i]) for(int j=i*i; j < MAXN; j+=i) isPrime[j] = false;
    }
}

int getSum (int n) {
    int sum = 0;
    while (n) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int NumwithLargestSum (int a[], int size) { // n = size of a
    int maxSum = -1;
    int num = -1;
    for(int i=0; i < size; i++) {
        int currSum = getSum(a[i]);
        if (currSum > maxSum) {
            maxSum = currSum;
            num = a[i];
        }
    }
    return num;
}

bool isPalindrome (int n) {
    int digits[10], cnt = 0;
    while (n) {
        digits[cnt++] = n % 10;
        n /= 10;
    }
    for (int i = 0; i < cnt / 2; i++) if (digits[i] != digits[cnt - 1 - i]) return false;
    return true;
}

int countAdjacentOddPairs(int arr[], int size) {
    int cnt = 0;
    for (int i = 0; i < size - 1; ++i) if (arr[i] % 2 != 0 && arr[i + 1] % 2 != 0 && abs(arr[i] - arr[i + 1]) == 2) cnt++;
    return cnt;
}

int countPairs(int arr[], int size, int m, int n) {
    int cnt = 0;
    for(int i=0; i < size; i++) for(int j=i+1; j < size; j++) {
        if (arr[i] + arr[j] == m + n) cnt++;
    }
    return cnt;
}

void solve () {
    cout << "Nhap vao 2 so m, n: ";
    int m,n;
    cin >> m >> n;
    int max_size = max(m,n) + 1;

    // (a) m and n are prime numbers ?
    if (isPrime[m]) cout << m << " is a prime number\n";
    else cout << m << " is not a prime number\n";
    if (isPrime[n]) cout << n << " is a prime number\n";
    else cout << n << " is not a prime number\n";

    // (b) List all prime numbers between m and n
    int primeList[max_size], index = 0;
    for (int i = m; i <= n; i++) if (isPrime[i]) primeList[index++] = i;
    cout << "Prime numbers between " << m << " and " << n << " are: ";
    for (int i = 0; i < index; i++) cout << primeList[i] << " ";
    cout << "\n";

    // (c) Find the prime number with the largest sum of digits
    int largestSum = NumwithLargestSum(primeList, index);
    cout << "The largest sum of digits among these prime numbers is: " << largestSum << "\n";

    // (d) Find out the palindromic prime numbers
    cout << "Palindromic prime numbers between " << m << " and " << n << " are: ";
    for (int i = 0; i < index; i++) if (isPalindrome(primeList[i])) cout << primeList[i] << " ";
    cout << "\n";

    // (e) Count adjacent odd pairs
    int oddPairCount = countAdjacentOddPairs(primeList, index);
    cout << "Number of adjacent odd pairs with a difference of 2: " << oddPairCount << "\n";

    // (f) Count pairs that sum to m + n
    int pairCount = countPairs(primeList, index, m, n);
    cout << "Number of pairs that sum to " << m + n << ": " << pairCount << "\n";
}

int main () {
    Eratosthenes();
    solve();
}
```

## Kiểm tra output
![](https://media.discordapp.net/attachments/961544480366931969/1433632926465265855/image.png?ex=69056635&is=690414b5&hm=cbd8e1ff6557ed2e53de05f170dfee052bc29c876f61da7a7cc5c3c8fd1cc3fa&=&format=webp&quality=lossless&width=1709&height=263)
