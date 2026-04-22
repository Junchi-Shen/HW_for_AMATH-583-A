#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <set>
#include <iomanip>

using namespace std;

// 模拟 6-bit 浮点数转换
struct FP6 {
    int s, k, n;
    int bias;

    double toDouble(int bits) {
        int sign = (bits >> 5) & 0x1;
        int exp = (bits >> 2) & 0x7;  // 3 bits
        int frac = bits & 0x3;        // 2 bits

        double s_val = (sign == 0) ? 1.0 : -1.0;

        if (exp == 0) {
            // 非规范化数或零
            return s_val * (frac / 4.0) * pow(2, 1 - bias);
        } else if (exp == 7) {
            // NaN 或 Inf (画图时忽略)
            return NAN;
        } else {
            // 规范化数
            return s_val * (1.0 + frac / 4.0) * pow(2, exp - bias);
        }
    }
};

int main() {
    FP6 sys = {1, 3, 2, 3}; // s=1, k=3, n=2, bias=3
    set<double> points;

    // 1. 遍历所有 6-bit 可能性 (0 to 63)
    for (int i = 0; i < 64; ++i) {
        double val = sys.toDouble(i);
        if (!isnan(val) && !isinf(val)) {
            points.insert(val);
        }
    }

    // 2. 生成 SVG 文件
    ofstream svg("fp_axis.svg");
    svg << "<svg width='800' height='200' xmlns='http://www.w3.org/2000/svg'>\n";
    svg << "<line x1='50' y1='100' x2='750' y2='100' stroke='black' stroke-width='2' />\n";

    for (double x : points) {
        // 映射坐标：将数值范围 [-14, 14] 映射到屏幕 [50, 750]
        double screenX = 400 + x * 25; 
        string color = (abs(x) < 0.25 && x != 0) || (x == 0) ? "red" : "blue";
        
        // 画刻度线
        svg << "<line x1='" << screenX << "' y1='90' x2='" << screenX << "' y2='110' "
            << "stroke='" << color << "' stroke-width='2' />\n";
        
        // 标注一些关键数字
        if (abs(x) == 0 || abs(x) == 1 || abs(x) == 14) {
            svg << "<text x='" << screenX - 5 << "' y='130' font-size='12'>" << x << "</text>\n";
        }
    }

    svg << "<text x='350' y='50' font-family='Arial' font-size='16'>6-bit FP Number Line (Red: Denorm/Zero, Blue: Norm)</text>\n";
    svg << "</svg>";
    svg.close();

    cout << "SVG file 'fp_axis.svg' has been generated!" << endl;
    return 0;
}