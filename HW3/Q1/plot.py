import pandas as pd
import matplotlib.pyplot as plt

# 1. 读取数据
df = pd.read_csv('data.csv')

# 2. 创建图表
plt.figure(figsize=(10, 6))
plt.plot(df['n'], df['flops'], label='Measured Performance', color='blue', linewidth=1.5)

# 3. 装饰图表
plt.title('Level 1 BLAS daxpy Performance')
plt.xlabel('Vector Size (n)')
plt.ylabel('Performance (FLOPs)')
plt.grid(True, which="both", ls="-", alpha=0.5)
plt.legend()

# 4. 保存图片
plt.savefig('performance_plot.png', dpi=300)
plt.show() 