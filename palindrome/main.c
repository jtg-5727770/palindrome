#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
typedef char element;

typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;
// 스택 초기화 함수
void init_stack(StackType* s)
{
    s->top = -1;
}
// 공백 상태 검출 함수
int is_empty(StackType* s)
{
    return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1));
}
StackType* s;
// 삽입함수
void push(StackType* s, element item)
{
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else s->data[++(s->top)] = item;
}
// 삭제함수
element pop(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        return 0;
    }
    else return s->data[(s->top)--];
}
//피크함수
element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        return 0;
    }
    else return s->data[(s->top)];
}
// 회문 검사 함수
int is_palindrome(char* str) {
    StackType s1, s2, s3;
    int len = strlen(str);

    init_stack(&s1);
    init_stack(&s2);
    init_stack(&s3);

    for (int i = 0; i < len; i++) {
        // 띄어쓰기, 쉼표, 어퍼스트로피는 건너뜀
        if (str[i] == ' ' || str[i] == ',' || str[i] == '\'') {
            continue;
        }
        // 대문자를 소문자로 바꿔서 저장
        else if ('A' <= str[i] && str[i] <= 'Z') {
            push(&s1, str[i] - ('A' - 'a'));
            push(&s3, str[i] - ('A' - 'a'));
        }
        else {
            push(&s1, str[i]);
            push(&s3, str[i]);
        }
    }

    // s1을 s2에 역순으로 저장
    while (!is_empty(&s1)) {
        element tmp = pop(&s1);
        push(&s2, tmp);
    }

    // s2와 s3를 비교
    while (!is_empty(&s2) && !is_empty(&s3)) {
        element tmp1 = pop(&s2);
        element tmp2 = pop(&s3);
        if (tmp1 != tmp2) {
            return 0; // 회문이 아님
        }
    }
    if (is_empty(&s2) && is_empty(&s3)) {
        return 1; // 회문임
    }
    return 0; // 회문이 아님
}

int main(void)
{
    char str[MAX_STACK_SIZE];
    char str2[10];

    do {
        printf("문자열을 입력하시오: ");
        fgets(str, sizeof(str), stdin);
        str[strlen(str) - 1] = '\0';
        if (is_palindrome(str)) {
            printf("회문입니다.\n");
        }
        else {
            printf("회문이 아닙니다.\n");
        }
        printf("\n계속 하시겠습니까?(y/n):");
        fgets(str2, sizeof(str2), stdin);
        str2[strlen(str2) - 1] = '\0';
        printf("\n");
    } while (!strcmp(str2, "y") || !strcmp(str2, "Y"));

    system("pause");
    return 0;
}