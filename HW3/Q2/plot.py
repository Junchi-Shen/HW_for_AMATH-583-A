import pandas as pd
import matplotlib.pyplot as plt
import glob

# 1. 读取数据
files = glob.glob('*.csv')

if files:
    # files[0] 表示获取找到的第一个文件
    df = pd.read_csv(files[0])

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