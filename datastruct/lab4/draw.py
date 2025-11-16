import pandas as pd
import matplotlib.pyplot as plt
import os

if not os.path.exists('D:\EXP-code-for-study\datastruct\lab4\sort_times.txt'):
    print("错误：未找到文件")
    exit()

data = pd.read_csv('D:\EXP-code-for-study\datastruct\lab4\sort_times.txt')

plt.rcParams["font.family"] = ["SimHei", "WenQuanYi Micro Hei", "Heiti TC"]
plt.rcParams["axes.unicode_minus"] = False 

plt.figure(figsize=(10, 6))

plt.plot(data['数据规模'], data['插入排序(ms)'], marker='o', label='插入排序')
plt.plot(data['数据规模'], data['选择排序(ms)'], marker='s', label='选择排序')
plt.plot(data['数据规模'], data['快速排序(ms)'], marker='^', label='快速排序')
plt.plot(data['数据规模'], data['归并排序(ms)'], marker='d', label='归并排序')

plt.title('四种排序算法的时间复杂度对比')
plt.xlabel('数据规模')
plt.ylabel('排序时间(毫秒)')
plt.grid(linestyle='--', alpha=0.7)
plt.legend()

plt.savefig('sort_comparison.png', dpi=300, bbox_inches='tight')
print("排序对比图已保存为 sort_comparison.png")

plt.show()