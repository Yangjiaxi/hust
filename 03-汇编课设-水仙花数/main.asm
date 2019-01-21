; a. 从控制台读取字符串存入缓冲区
; b. 通过第二个参数判断读入的字符数量
; c. 检查：
;   1. 读取的字符数量不是3
;   2. 包含有数字之外的字符
;   3. 第一个字符为0
; d. 满足则跳回a
; e. 不满足说明输入正常

; 选择方法
; 1 -> 查表法
; 2 -> 计算法
; 3 -> Otherwise: 提示输入有误，重新输入

; 开始运行:
; A. 查表法
;   a. 遍历TAB
;   b. 如果当前数字小于RANGE
;       -> 调用RADIX输出
;   c. 否则程序结束

; B. 计算法
;   a. 从100到RANGE
;   b. 对于每个数执行QUAD，按规则进行映射
;   c. 若映射的像与原像相等，说明符合水仙花数的规则
;       -> 调用RADIX输出

; END: 单次程序运行结束后会询问是否继续
; Y/y -> 继续
; N/n -> 退出
; Otherwise -> 提示输入有误，重新输入

; ------------------------------------------------------
; 输出换行

.386

CRLF    MACRO
        PUSH    AX
        PUSH    DX
        MOV     AH, 2
        MOV     DL, 0AH
        INT     21H
        MOV     DL, 0DH
        INT     21H
        POP     DX
        POP     AX
        ENDM
; ------------------------------------------------------


; ------------------------------------------------------
; 从控制台读取一段字符存入传入的参数中
READ    MACRO   A
        LEA     DX, A
        MOV     AH, 10
        INT     21H
        ENDM
; ------------------------------------------------------


; ------------------------------------------------------
; 将传入的参数指向的以$结尾的字符串输出到控制台
WRITE   MACRO   A
        PUSH    AX
        PUSH    DX
        LEA     DX, A
        MOV     AH, 9
        INT     21H
        POP     DX
        POP     AX
        ENDM
; ------------------------------------------------------


; ------------------------------------------------------
; 从控制台读取一个字符存入AL
GETC    MACRO
        MOV     AH, 1
        INT     21H
        ENDM
; ------------------------------------------------------


; ------------------------------------------------------
; 将读取的字符串转换为数字
TONUM   MACRO
        LEA     SI, BUF_S

        MOV     BX, 0
NUM_L:  MOV     DX, 0                       ; 第一位和第二位
        MOV     DL, [BX+SI]
        SUB     DL, 30H
        MOV     AL, DL
        MOV     AH, 0
        ADD     RANGE, AX
        MOV     AX, RANGE
        MOV     DX, 10
        MUL     DX
        XOR     DX, DX
        MOV     RANGE, AX
        INC     BX
        CMP     BX, 2
        JL      NUM_L

        MOV     DL, [BX+SI]                 ; 第三位
        SUB     DL, 30H
        MOV     AL, DL
        MOV     AH, 0
        ADD     RANGE, AX
        MOV     AX, RANGE
        MOV     BX, 10
        LEA     SI, OUT_BUF
        CALL    RADIX
        ENDM
; ------------------------------------------------------

DATA    SEGMENT USE16
BUF     DB      10                          ; 保存输入的字符串
BUF_L   DB      ?                           ; 输入字符串的长度
BUF_S   DB      10      DUP(0)              ; 输入的字符

INPUT   DB      'PLEASE INPUT X(100~999): $' ; 输入提示
INERR   DB      'INPUT ERROR! TRY AGAIN.', 0AH, 0DH, '$'
CHOOSE  DB      '1. LOOKUP', 0AH, 0DH, '2. CALCULATE', 0AH, 0DH, 'CHOOSE METHOD YOU WANT: $'
OUT_S   DB      'ALL NARCISSISTIC NUMBER UNDER $'
RES_S   DB      'WANNA PLAY AGAIN? (Y/N): $'
TAB     DW      153, 370, 371, 407          ; 查表法
N       =       8                           ; 表长度 (字节)

RANGE   DW      ?                           ; 实际输入的数字(转换后)
OUT_BUF DB      10      DUP(0)
; A       DB      ?
; B       DB      ?
; C       DB      ?
TMP     DW      0                           ; 累加
DATA    ENDS

STACK   SEGMENT USE16   STACK
        DB      200 DUP(0)
STACK   ENDS

CODE    SEGMENT USE16
        ASSUME  CS:CODE, SS:STACK, DS:DATA
BEGIN:  MOV     AX, DATA
        MOV     DS, AX
        MOV     ES, AX


START:                                      ; 清除所有缓存
        CALL    CLN_A
        ; 读取字符串
        WRITE   INPUT
        READ    BUF
        CRLF
        ; 检查输入字符的长度
        CMP     BUF_L, 3
        JNZ     N_ERR
        ; 检查输入的字符是否为数字
        MOV     BX, 0
CK_D:   MOV     AL, BUF_S[BX]
        CALL    IS_NUM
        CMP     AH, 1
        JE      N_ERR
        INC     BX
        CMP     BX, 3
        JL      CK_D
        ; 检查第一个数字是否为0
        CMP     BUF_S, 30H
        JE      N_ERR
        ; 程序运行到这里说明输入是正确的
        ; 转换成数字存入RANGE
        TONUM
        ; 选择方法
CHS_M:  WRITE   CHOOSE
        GETC
        SUB     AL, 30H
        CMP     AL, 1                       ; 查表法
        JE      M_TB
        CMP     AL, 2                       ; 计算法
        JE      M_CAL
        JMP     C_ERR                       ; 到这里说明方法选择错误

M_TB:   CRLF                                ; 执行查表法
        WRITE   OUT_S
        WRITE   OUT_BUF
        CRLF
        MOV     DI, 0
LTB:    MOV     AX, TAB[DI]
        CMP     AX, RANGE
        JG      FINISH
        MOV     BX, 10
        LEA     SI, OUT_BUF
        CALL    RADIX
        WRITE   OUT_BUF
        CRLF
        ADD     DI, 2
        CMP     DI, N
        JL      LTB
        JMP     FINISH

M_CAL:  CRLF                                ; 执行计算法
        WRITE   OUT_S
        WRITE   OUT_BUF
        CRLF

        MOV     CX, 100
CAL:    MOV     AX, CX
        CALL    QUAD                        ; 计算映射，AX->TMP
        CMP     CX, TMP
        JNE     NEXT
        MOV     AX, TMP
        MOV     BX, 10
        LEA     SI, OUT_BUF
        CALL    RADIX
        WRITE   OUT_BUF
        CRLF
NEXT:   INC     CX
        CMP     CX, RANGE
        JLE     CAL
        JMP     FINISH

N_ERR:  WRITE   INERR                       ; 数字输入有误
        JMP     START
C_ERR:  CRLF                                ; 方法选择有误
        WRITE   INERR
        JMP     CHS_M
R_ERR:  WRITE   INERR                       ; 是否重新开始选择有误
        JMP     FINISH
FINISH: WRITE   RES_S                       ; 单次执行结束，询问是否继续
        GETC
        CMP     AL, 'Y'                     ; Y/y
        JE      START
        CRLF
        CMP     AL, 'y'
        JE      START
        CMP     AL, 'N'                     ; N/n
        JE      OVER
        CMP     AL, 'n'
        JE      OVER
        JMP     R_ERR                       ; 都不满足说明输入字符有误
        
OVER:   MOV     AH, 4CH
        INT     21H


; ------------------------------------------------------
; AX中存放的三位数->百位^3 + 十位^3 + 个位^3 -> TMP
QUAD    PROC
        PUSH    CX
        PUSH    DX
        MOV     TMP, 0
        MOV     DL, 10
        DIV     DL
        MOV     BL, AL
        MOV     BH, 0
        MOV     AL, AH
        MOV     AH, 0
        MOV     DX, AX
        MUL     DL
        MUL     DL
        ADD     TMP, AX

        MOV     AX, BX
        MOV     DL, 10
        DIV     DL
        MOV     BL, AL
        MOV     BH, 0
        MOV     AL, AH
        MOV     AH, 0
        MOV     DX, AX
        MUL     DL
        MUL     DL
        ADD     TMP, AX

        MOV     AX, BX
        MOV     DL, AL
        MUL     DL
        MUL     DL
        ADD     TMP, AX

        POP     DX
        POP     CX
        RET
QUAD    ENDP
; ------------------------------------------------------


; ------------------------------------------------------
; 清除所有存储器内容，在重新开始时有用
CLN_A   PROC
        MOV     TMP, 0
        MOV     RANGE, 0
        MOV     AL, 0

        MOV     CX, 10
        LEA     DI, BUF_S
        REP     STOSB

        MOV     CX, 10
        LEA     DI, OUT_BUF
        REP     STOSB
CLN_A   ENDP
; ------------------------------------------------------



; ------------------------------------------------------
; AL中的字符是否为数字字符，为数字->AH置0，否则AL置1
IS_NUM  PROC
        SUB     AL, 30H
        MOV     AH, 0
        CMP     AL, 0
        JL      CHAR
        CMP     AL, 9
        JG      CHAR
        ; 到这里说明AL的字符就是数字，测试成功
        RET
        ; AL非法输入，不是数字，AH置1
CHAR:   MOV     AH, 1
        RET
IS_NUM  ENDP
; ------------------------------------------------------



; ------------------------------------------------------
; AX    要转换的数字
; BX    目标进制
; SI    输出区起始指针
RADIX   PROC
        PUSH    CX
        PUSH    DX
        XOR     CX, CX                      ; 指示栈中元素个数
LOP1:   XOR     DX, DX                      ; 余数清零
        DIV     BX                          ; AX / BX -> AX : DX DX为余数，AX为商
        PUSH    DX                          ; 余数入栈
        INC     CX                          ; 栈计数器+1
        OR      AX, AX                      ; 测试商AX
        JNZ     LOP1                        ; 商为0则停止
LOP2:   POP     BX                          ; 栈弹出一个元素
        ADD     BL, 30H                     ; 元素+30H -> 对应ASCII码(仅考虑十进制，不考虑更高进制的字母)
        MOV     [SI], BL                    ; 存入输出区
        INC     SI                          ; 输出区存储指针+1
        LOOP    LOP2                        ; 循环CX次
        POP     DX
        POP     CX
        MOV     BYTE PTR [SI], '$'          ; 末尾结束标志
        RET
RADIX   ENDP
; ------------------------------------------------------

CODE    ENDS
        END     BEGIN