#include <iostream>
#include <vector>
#include <algorithm> // для std::min
#include <climits>
using namespace std;
 // Jump game 
class Solution1 {
public:
    bool canJump(vector<int>& nums) { // + N * 4
        int n = nums.size(); // + 4
        vector<bool> dp(n, false); // dp[i] означает, можно ли достичь индекса i / + N
        dp[0] = true; // начальный индекс достижим
        
        for (int i = 0; i < n; ++i) { // + 4
            if (!dp[i]) continue; // если текущий индекс недостижим, пропускаем
            int maxJump = min(i + nums[i], n - 1); // ограничиваем прыжок последним индексом // + 4
            for (int j = i + 1; j <= maxJump; ++j) { // + 4
                dp[j] = true; // отмечаем индексы, которые можно достичь
            }
        }
        return dp[n - 1]; // проверяем, можно ли достичь последний индекс
    }
}; // N * 4 + N + 4 * 4 = N * 5 + 16

// Jump game II
class Solution2 {
public:
    int jump(vector<int>& nums) { // + N * 4
        int n = nums.size(); // + 4
        vector<int> dp(n, INT_MAX); // Инициализация dp с максимальным значением // + N * 4
        dp[0] = 0; // Начальная позиция требует 0 прыжков
        
        for (int i = 0; i < n; ++i) { // + 4
            int maxJump = min(i + nums[i], n - 1); // Максимально достижимый индекс с позиции i // + 4
            for (int j = i + 1; j <= maxJump; ++j) { // +4
                dp[j] = min(dp[j], dp[i] + 1); // Обновляем минимальное количество прыжков для индекса j
            }
        }
        
        return dp[n - 1]; // Возвращаем минимальное количество прыжков для последнего индекса
    }
}; // N * 4 + N * 4 + 4 * 4 = N * 8 + 16

int main() {
    Solution1();
    Solution2();
    return 0;
}