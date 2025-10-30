#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool canDivide(const vector<int>& salaries, int M, long long maxSum) {
    int count = 1;
    long long currentSum = 0;
    
    for (int salary : salaries) {
        if (salary > maxSum) return false;
        
        if (currentSum + salary > maxSum) {
            count++;
            currentSum = salary;
            if (count > M) return false;
        } else {
            currentSum += salary;
        }
    }
    return true;
}

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<int> salaries(N);
    long long total = 0;
    int maxSalary = 0;
    
    for (int i = 0; i < N; i++) {
        cin >> salaries[i];
        total += salaries[i];
        maxSalary = max(maxSalary, salaries[i]);
    }
    
    long long low = maxSalary;
    long long high = total;
    long long answer = total;
    
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        
        if (canDivide(salaries, M, mid)) {
            answer = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    cout << answer << endl;
    return 0;
}
