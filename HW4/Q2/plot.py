import pandas as pd
import matplotlib.pyplot as plt

# 1. 关键修正：skipinitialspace=True 会自动处理逗号后的空格
# 如果你的文件有表头，直接 read_csv 即可，不用手动给 names
df = pd.read_csv('results_O3.csv', skipinitialspace=True)

# 2. 检查一下列名，防止列名里也带空格
df.columns = df.columns.str.strip()

plt.figure(figsize=(10, 6))

# 3. 分离数据并绘图
for dtype in ['FP32', 'FP64']:
    data = df[df['type'] == dtype]
    # 画 kij 曲线
    plt.plot(data['n'], data['kij_GFLOPs'], '-o', label=f'kij_{dtype}')
    # 画 jki 曲线
    plt.plot(data['n'], data['jki_GFLOPs'], '--s', label=f'jki_{dtype}')

plt.xscale('log', base=2)  # 矩阵维度通常按2的幂增长，对数坐标更直观
plt.xlabel('Matrix Size (n)')
plt.ylabel('Performance (GFLOPs)')
plt.title('Matrix Multiplication Performance (Loop Permutation)')
plt.legend()
plt.grid(True, which="both", ls="-")
plt.savefig('results_O3_performance.png')
plt.show()