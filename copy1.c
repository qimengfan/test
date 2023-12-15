#include <stdio.h>
#include <string.h>

int int1, int2, n1, n2, sub;

char *valueToMachine(int num, int length) {
    static char binary[9]; // ���֧��8λ�Ķ����Ʊ�ʾ
    int i;
    for (i = length - 1; i >= 0; i--) {
        binary[i] = (num & 1) + '0'; // ȡ�����λ����ת��Ϊ�ַ� '0' �� '1'
        num >>= 1; // ����һλ���൱�ڳ���2
    }
    binary[length] = '\0'; // ����ַ���������
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
        result[i] = (sum & 1) + '0'; // ȡ�����λ��ת��Ϊ�ַ� '0' �� '1'
        carry = sum >> 1; // ����һλ���൱�ڳ���2
    }
    result[length] = '\0'; // ����ַ���������

    // ����eflags
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
    // 1. ����Ļ�϶�ȡ��������
    printf("����������������-128 �� 127 ֮�䣩��");
    scanf("%d %d", &int1, &int2);

    // 2. ����Ļ�϶�ȡ��������
    printf("����������������4 �� 8����");
    scanf("%d %d", &n1, &n2);

    // 3. ����Ļ�϶�ȡ0����1����sub
    printf("������0����ʾ�ӷ����� 1����ʾ��������");
    scanf("%d", &sub);

    // 4. ����computing��������Ӽ����������ؽ��
    int result = computing(int1, int2, n1, n2, sub);

    // 4.1 - 4.5 ��������������
    // ������
    printf("���ս��Ϊ��%d\n", result);

    return 0;
}

