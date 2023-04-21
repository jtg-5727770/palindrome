#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
typedef char element;

typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;
// ���� �ʱ�ȭ �Լ�
void init_stack(StackType* s)
{
    s->top = -1;
}
// ���� ���� ���� �Լ�
int is_empty(StackType* s)
{
    return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1));
}
StackType* s;
// �����Լ�
void push(StackType* s, element item)
{
    if (is_full(s)) {
        fprintf(stderr, "���� ��ȭ ����\n");
        return;
    }
    else s->data[++(s->top)] = item;
}
// �����Լ�
element pop(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        return 0;
    }
    else return s->data[(s->top)--];
}
//��ũ�Լ�
element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        return 0;
    }
    else return s->data[(s->top)];
}
// ȸ�� �˻� �Լ�
int is_palindrome(char* str) {
    StackType s1, s2, s3;
    int len = strlen(str);

    init_stack(&s1);
    init_stack(&s2);
    init_stack(&s3);

    for (int i = 0; i < len; i++) {
        // ����, ��ǥ, ���۽�Ʈ���Ǵ� �ǳʶ�
        if (str[i] == ' ' || str[i] == ',' || str[i] == '\'') {
            continue;
        }
        // �빮�ڸ� �ҹ��ڷ� �ٲ㼭 ����
        else if ('A' <= str[i] && str[i] <= 'Z') {
            push(&s1, str[i] - ('A' - 'a'));
            push(&s3, str[i] - ('A' - 'a'));
        }
        else {
            push(&s1, str[i]);
            push(&s3, str[i]);
        }
    }

    // s1�� s2�� �������� ����
    while (!is_empty(&s1)) {
        element tmp = pop(&s1);
        push(&s2, tmp);
    }

    // s2�� s3�� ��
    while (!is_empty(&s2) && !is_empty(&s3)) {
        element tmp1 = pop(&s2);
        element tmp2 = pop(&s3);
        if (tmp1 != tmp2) {
            return 0; // ȸ���� �ƴ�
        }
    }
    if (is_empty(&s2) && is_empty(&s3)) {
        return 1; // ȸ����
    }
    return 0; // ȸ���� �ƴ�
}

int main(void)
{
    char str[MAX_STACK_SIZE];
    char str2[10];

    do {
        printf("���ڿ��� �Է��Ͻÿ�: ");
        fgets(str, sizeof(str), stdin);
        str[strlen(str) - 1] = '\0';
        if (is_palindrome(str)) {
            printf("ȸ���Դϴ�.\n");
        }
        else {
            printf("ȸ���� �ƴմϴ�.\n");
        }
        printf("\n��� �Ͻðڽ��ϱ�?(y/n):");
        fgets(str2, sizeof(str2), stdin);
        str2[strlen(str2) - 1] = '\0';
        printf("\n");
    } while (!strcmp(str2, "y") || !strcmp(str2, "Y"));

    system("pause");
    return 0;
}