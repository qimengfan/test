#include <stdio.h>
#include <string.h>

int int1, int2, n1, n2, sub;

char *valueToMachine(int num, int length) {
    static char binary[9]; // 最大支持8位的二进制表示
    int i;
    for (i = length - 1; i >= 0; i--) {
        binary[i] = (num & 1) + '0'; // 取出最低位，并转换为字符 '0' 或 '1'
        num >>= 1; // 右移一位，相当于除以2
    }
    binary[length] = '\0'; // 添加字符串结束符
    return binary;
}

char *addsub(char *int1, char *int2, int sub, int length, char *eflags) {
    static char result[9];
    int carry = 0;
    int i;
    for (i = length - 1; i >= 0; i--) {
        int bit1 = int1[i] - '0';
        int bit2 = int2[i] - '0';
        int sum = bit1 + bit2+ carry;
        result[i] = (sum & 1) + '0'; // 取出最低位并转换为字符 '0' 或 '1'
        carry = sum >> 1; // 右移一位，相当于除以2
    }
    result[length] = '\0'; // 添加字符串结束符

    // 更新eflags
    eflags[0] = (carry & 1) + '0'; // cf
    eflags[2] = (result[0] == '0') + '0'; // zf
    eflags[4] = (result[0] == '1') + '0'; // sf
    eflags[6] = ((int1[0] == '1' && int2[0] == '1' && result[0] == '0') || 
                (int1[0] == '0' && int2[0] == '0' && result[0] == '1')) + '0'; // of

    return result;
}

int machineToValue(char *binary, int length) {
    int result = 0;
    int i;
    for (i = 0; i < length; i++) {
        result = (result << 1) + (binary[i] - '0');
    }
    return result;
}

int computing(int int1, int int2, int n1, int n2, int sub) {
    int length = (n1 > n2) ? n1 : n2;
    char *int1_binary = valueToMachine(int1, length);
    char *int2_binary = valueToMachine(int2, length);
    char eflags[8];

    char *result_binary = addsub(int1_binary, int2_binary, sub, length, eflags);

    return machineToValue(result_binary, length);
}

int main() {
    // 1. 从屏幕上读取两个整数
    printf("请输入两个整数（-128 到 127 之间）：");
    scanf("%d %d", &int1, &int2);

    // 2. 从屏幕上读取两个整数
    printf("请输入两个整数（4 或 8）：");
    scanf("%d %d", &n1, &n2);

    // 3. 从屏幕上读取0或者1存入sub
    printf("请输入0（表示加法）或 1（表示减法）：");
    scanf("%d", &sub);

    // 4. 调用computing函数计算加减法，并返回结果
    int result = computing(int1, int2, n1, n2, sub);

    // 4.1 - 4.5 根据需求输出结果
    // 输出结果
    printf("最终结果为：%d\n", result);

    return 0;
}

