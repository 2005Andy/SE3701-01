# HW-4

**question 1**：  
考虑使用动态规划算法处理。采取自底向上的方法，按照步长从小到大依次处理不同长度的矩阵链。下面是程序动态规划部分核心代码以及运行截图：

~~~

void matrixChain(const vector<int>& dims) {
    int n = dims.size() - 1;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<vector<int>> split(n, vector<int>(n, 0));

    for (int l = 2; l <= n; ++l) {
        for (int i = 0; i < n - l + 1; ++i) {
            int j = i + l - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; ++k) {
                int cost = dp[i][k] + dp[k + 1][j] + dims[i] * dims[k + 1] * dims[j + 1];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }
}

~~~

![matrix_chain](https://github.com/2005Andy/SE3701-01/raw/HW-4/matrix_chain.png)

