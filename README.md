# 42Seoul_minitalk
Minitalk subject of 42 Seoul

## Requirements

1.  서로 통신을 하는 서버와 클라이언트 프로그램을 구현한다.
2.  서버 프로그램이 항상 먼저 실행되어야한다. 서버가 실행되면 자신의 PID를 출력한다.
3.  클라이언트 프로그램은 "서버의 PID"와 "서버로 보낼 문자열"을 매개변수로 받는다.
4.  클라이언트는 매개변수로 받은 문자열을 서버로 전송하고, 서버는 그 문자열을 받아서 출력한다.
5.  서버와 클라이언트 사이의 통신은 오로지 SIGUSR1, SIGUSR2 두 개의 UNIX 시그널을 통해서 이루어져야 한다.
6.  서버가 클라이언트에게서 전송 받은 문자열을 출력하는 속도가 너무 느려선 안된다. (1초에 문자 100개를 출력하는 것은 너무 느리다!)
7.  서버는 서버를 재시작 할 필요 없이 여러 클라이언트의 문자열을 수신할 수 있어야 한다.
8.  실행 파일의 이름은 "client"와 "server" 여야 한다.
9.  한 개의 전역 변수를 사용할 수 있다.

\*7번 요구사항은 비동기적으로 여러 클라이언트와 통신할 수 있어야 한다는 것이 아니다. 처음 연결한 클라이언트 하고만 통신할 수 있는 것이 아니라, 한 클라이언트와의 통신이 끝나면 서버를 재시작하지 않고도 다른 클라이언트와 통신이 가능해야 한다는 의미이다.

## 사용할 수 있는 함수

#### signal.h

-   **sigaction, signal. sigemptyset**, sigaddset, **kill**

#### stdlib.h

-   malloc, free, exit

#### unistd.h

-   write, getpid, sleep, usleep, pause

\*bold체의 함수는 핵심적으로 사용되는 함수들임.

### 알아둬야 할 헤더 파일 및 구조체

#### signal.h

-   sigset\_t, sigaction, siginfo\_t (구조체)
-   SIGUSR1, SIGUSR2 (상수)

#### type.h

-   pid\_t (signed int)

## 접근 과정

### 0\. Signal이란?

소프트웨어 인터럽트. 이벤트가 발생하면 시그널을 통해 해당 사실이 프로세스에 "비동기적(asynchronous)"으로 전달됨.  
대부분의 시그널의 경우 signal handler를 통해 해당 시그널을 필요에 맞게 처리할 수 있다.

#### 발생사유

1.  0으로 나누기처럼 프로그램에서 예외적인 상황이 일어나는 경우
2.  kill 함수처럼 시그널을 보낼 수 있는 함수를 사용해서 다른 프로세스에 시그널을 보내는 경우
3.  사용자가 Ctrl+C 같이 인터럽트 키를 입력한 경우

#### 시그널 처리 방식

1.  각 시그널에 지정된 기본 동작 수행 (대부분의 시그널의 경우 default action은 abnormal termination)
2.  시그널 핸들러를 미리 설정해두면 시그널 발생 시 해당 핸들러를 호출.
3.  시그널 무시 (시그널 핸들러를 SIG\_IGN로 설정했을 경우)
4.  특정 시그널을 블록처리 - 무시(ignore)가 아니라 보류(pending)했다가, unblocked 되면 해당 시그널을 핸들링. 단 UNIX의 경우 동일한 시그널을 여러개 queueing 해두지는 않는다. 그저 pending된 시그널이 존재하는지만 알 수 있음.

출처  
[https://codingsmu.tistory.com/57](https://codingsmu.tistory.com/57)  
[https://snnchallenge.tistory.com/300](https://snnchallenge.tistory.com/300)  
[https://stackoverflow.com/questions/5730975/difference-in-handling-of-signals-in-unix](https://stackoverflow.com/questions/5730975/difference-in-handling-of-signals-in-unix)  

### 1\. UNIX 시그널 SIGUSR1, SIGUSR2를 사용하여 통신을 하는 방법은?

kill() 함수를 사용하면 특정 pid의 프로세스에게 시그널을 보낼 수 있다.

```c
#include <sys/types.h>
#include <signal.h>

int kill(pid_t pid, int sig);
//pid - 시그널을 보낼 프로세스의 pid
//sig - 보낼 시그널 ex) SIGUSR1
```

문자열의 각 문자를 SIGUSR1, SIGUSR2를 사용하여 bit 단위로 전송한다.  

문자 'a' == 십진수 61 == 이진수 01100001  
이진수 01100001을 맨 왼쪽 bit 부터 bit 연산을 사용하여 하나씩 확인.  
bit가 0이면 SIGUSR1 시그널을 서버로 보내고, 1이면 SIGUSR2 시그널을 보내는 방식으로 서버에 문자를 전송할 수 있다.

### 2\. 서버에서 SIGUSR1, SIGUSR2 시그널을 받아서 원하는 방식대로 처리하는 방법은?

sigaction() 함수를 사용해서 특정 시그널에 시그널 핸들러를 등록할 수 있다.

```c
#include <signal.h>

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
//signum - 시그널 핸들러를 등록할 시그널
//act - 등록할 시그널 핸들러의 정보가 담겨있는 sigaction 구조체의 주소
//oldact - 기존에 등록되어 있는 시그널 핸들러의 정보를 반환할 구조체의 주소
```

시그널 핸들러 함수를 작성하고, 해당 함수의 주소가 담긴 sigaction 구조체를 만든 뒤, sigaction() 함수를 사용해서 SIGUSR1, SIGUSR2에 대한 핸들러를 등록해주면 된다.

### 3\. sigaction 구조체는 무엇인가?

```c
#include <signal.h>

struct  sigaction {
	union __sigaction_u __sigaction_u;  /* signal handler */
	sigset_t sa_mask;               /* signal mask to apply */
	int     sa_flags;
};

union __sigaction_u {
	void    (*__sa_handler)(int);
	void    (*__sa_sigaction)(int, siginfo_t *,	void *);
};
//sigaction 구조체에서 sa_flags 옵션을 통해 두 함수 포인터 중 하나만
//시그널 핸들러로 사용하기 때문에 union으로 선언됨.

#define sa_handler      __sigaction_u.__sa_handler
#define sa_sigaction    __sigaction_u.__sa_sigaction

int sigaction(int sig, const struct sigaction *restrict act,
		struct sigaction *restrict oact);
//sigaction 구조체 형태로 매개변수를 받아 시그널 핸들러를 등록함
```

sa\_flags 변수를 통해 시그널 핸들링에 대한 여러 옵션을 지정할 수 있다. SA\_SIGINFO, SA\_NODEFER등 7가지의 옵션이 있는데, bit 연산을 통해 각 옵션에 대한 bit를 set 해줌으로써 옵션을 지정하는 것이 가능하다. (예: sa\_flags |= SA\_SIGINFO)

 \_\_sigaction\_u union은 2개의 멤버 변수를 갖고 있다. union이고, 두 멤버 변수 모두 포인터이므로 크기가 동일하기 때문에 둘 중 하나의 변수만 사용이 가능하다. (union의 크기는 가장 크기가 큰 변수의 크기이다) 

sa\_flags 에 SA\_SIGINFO bit가 set 되어있지 않으면 시그널 핸들러로 \_\_sa\_handler를 사용하고, set 되어 있으면 \_\_sa\_sigaction을 사용한다.

union의 두 변수는 각각 sa\_handler와 sa\_sigaction으로 define 되어 있으므로 더 간편하게 접근 가능하다.  
  
sa\_mask 변수를 통해 시그널 핸들러가 동작 중일 때 블록할 시그널을 sigset\_t 구조체로 지정할 수 있다. 주의할 점은 시그널 핸들러가 동작 중일 때, 해당 핸들러를 동작시키게 한 시그널은 자동으로 블록 처리가 된다. 만약 그게 싫으면 sa\_flags에 SA\_NODEFER bit를 set 해서 시그널 핸들러를 동작시킨 시그널을 블록하지 않게 할 수 있다.

출처  
[https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=gaechuni&logNo=221154760245](https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=gaechuni&logNo=221154760245) 

### 4\. 왜 sigaction()인가? - signal()을 사용해서 시그널 핸들러를 등록하지 않는 이유

과제의 7번 요구사항 "서버는 서버를 재시작 할 필요 없이 여러 클라이언트의 문자열을 수신할 수 있어야 한다"을 구현하기 위해서는, 현재 서버로 들어오는 SIGUSR1, SIGUSR2 시그널이 어느 클라이언트로부터 오는 시그널인지를 알 수 있어야 한다.

그런데 만약 signal() 함수로 시그널 핸들러를 등록한다면?

```c
#include <signal.h>

void (*signal(int sig, void (*func)(int)))(int);
//sig - 시그널 핸들러를 등록할 시그널
//func - 시그널 핸들러. void func(int signo) 형태.
```

시그널 핸들러 func가 인자로 시그널 번호만 받는다. 즉 시그널을 보낸 프로세스의 정보를 얻을 방법이 없다.

하지만 sigaction()의 경우 sa\_flags에 SA\_SIGINFO bit를 set 하면, 시그널 핸들러 함수의 인자로 시그널 번호와 함께 시그널을 보낸 프로세스의 정보를 담은 siginfo\_t 구조체를 인자로 받을 수 있다.

```c
#include <signal.h>

struct  sigaction {
	union __sigaction_u __sigaction_u;  /* signal handler */
	sigset_t sa_mask;               /* signal mask to apply */
	int     sa_flags;
};

union __sigaction_u {
	void    (*__sa_handler)(int);
	void    (*__sa_sigaction)(int, siginfo_t *,	void *);
};
//SA_SIGINFO bit를 set 하면 핸들러로 __sa_sigaction을 사용하는데
//매개변수에 siginfo_t 구조체가 있는 것을 확인할 수 있다.
//시그널 핸들러가 실행되면, 이 구조체에 담겨있는 시그널을 보낸 프로세스의 정보를 활용 가능하다.

int sigaction(int sig, const struct sigaction *restrict act,
		struct sigaction *restrict oact);
```

sigaction()으로 핸들러를 등록하면서 SA\_SIGINFO bit를 set 해주면, 시그널 핸들러가 3개의 매개변수를 받는 \_\_sa\_sigaction이 되는데, 이 핸들러가 호출되었을 때 내부에서 siginfo\_t 구조체를 활용해서 시그널을 보낸 프로세스의 정보를 알 수 있다.

siginfo\_t 구조체에는 시그널을 보낸 프로세스의 pid도 있기 때문에, SIGUSR1, SIGUSR2 시그널을 통해서 클라이언트 a의 문자열을 수신하는 도중 클라이언트 b의 SIGUSR1, SIGUSR2 시그널이 온다면 siginfo\_t에 있는 pid를 확인해서 클라이언트 b에게 잠시 후에 다시 통신 요청을 보내라고 신호를 줄 수 있다 (이 신호 역시 SIGUSR1 또는 SIGUSR2를 사용하면 된다)

### 5\. siginfo\_t 구조체

sys/signal.h 헤더파일 안에 siginfo\_t 구조체가 정의되어있다. 이 헤더파일은 signal.h에서 include 하므로 signal.h만 include 해줘도 된다. sys/signal.h는 시그널에 대한 define도 되어있다.

```c
#include <sys/signal.h>
//signal.h에서 sys/signal.h를 include한다.

#define SIGHUP 1
#define SIGINT 2

//중략...

#define SIGUSR1 30
#define SIGUSR2 31

typedef struct __siginfo {
	int     si_signo;               /* signal number */
	int     si_errno;               /* errno association */
	int     si_code;                /* signal code */
	pid_t   si_pid;                 /* sending process */
	uid_t   si_uid;                 /* sender's ruid */
	int     si_status;              /* exit value */
	void    *si_addr;               /* faulting instruction */
	union sigval si_value;          /* signal value */
	long    si_band;                /* band event for SIGPOLL */
	unsigned long   __pad[7];       /* Reserved for Future Use */
} siginfo_t;
```

siginfo\_t 에서 si\_pid가 시그널을 보낸 프로세스의 pid이다. 나머지 멤버는 이 과제에서는 사용할 일이 없을 것으로 보인다.

## 세부 구현 사항 및 문제 해결

### 1. 시그널을 보냈지만 상대방이 확인하지 못하는 확률을 최소화
 제일 처음 시도했던 방식은, 클라이언트에서 문자 단위로 시그널을 보내면 (8개의 시그널을 100 μs 간격으로 연속 송신) 서버에서 8개의 시그널을 모아서 문자 하나를 완성시키고, 성공 시 응답 시그널을 클라이언트로 보내는 방식이었다. 하지만 이 경우에는 타이밍 문제 때문에, 그리고 UNIX에서 시그널은 pending 될 뿐 queueing 되지는 않는다는 문제 때문에 문자열이 길어지면 자꾸 송수신에 실패하는 경우가 발생했다.
 
 또 코드의 가독성을 위해서, 시그널 핸들러에서는 서버 혹은 클라이언트가 보낸 시그널을 전역 변수에 저장만 하고 해당 시그널을 실제로 처리하는 함수를 따로 작성하는 방식으로 구현을 했었다. 실제로 코드의 가독성은 매우 좋아졌지만, 함수 호출 및 반환 시에 소요되는 시간 때문인지 송수신에 실패하는 경우가 자주 발생했다.
 
 시그널로만 통신을 하기 때문에, 입력이 똑같아도 송수신이 실패하는 위험성은 반드시 존재한다 (동일한 시그널이 여러 클라이언트에 의해 동시에 수신되어서 먼저 도착한 시그널이 무시되는 경우 등). 따라서 송수신이 실패하는 가능성을 최대한 줄이는 것을 목표로, 클라이언트의 모든 시그널에 서버가 응답 시그널을 보내도록 구현했다. 또 클라이언트는 서버의 응답을 받은 후에 다음 시그널을 보내도록 했다. 이러면 적어도 타이밍 문제 때문에 시그널이 무시되는 확률은 최소화 할 수 있다.
 
 또 클라이언트는 서버의 응답 시그널을 받자마자 바로 다음 시그널을 보내는 것이 아니라, 50 μs sleep을 한 후에 시그널을 보냄으로써 서버가 수신에 실패하는 확률을 줄였다.
 
 마지막으로 초기화 외의 대부분의 작업을 시그널 핸들러 함수 내부에서 수행함으로써, 동일한 시그널에 의해 인터럽트가 걸려서 송수신에 문제가 생기는 경우를 방지했다. 또 시그널 핸들러를 변경해야 하는 경우, 시그널을 보내고 핸들러를 변경하는 것이 아니라, 핸들러를 교체해서 서버/클라이언트의 응답 시그널을 받을 준비를 마치고 시그널을 보냄으로써 변경 이전의 핸들러가 호출되는 경우를 막는다.
 
### 2. 서버가 클라이언트와 통신중일 때 다른 클라이언트의 통신 요청 시그널이 들어오는 경우
 시그널로 송수신을 하기 때문에 서버는 동시에 여러 클라이언트와 통신을 할 수 없다. 시그널은 queueing 되지 않고 pending 되기 때문이다. 따라서 client A와 통신중일 때 client B에게 시그널이 오면, siginfo의 si_pid로 클라이언트를 식별하고, client B에게 SIGUSR2 시그널을 보내서 잠시 기다리라고 한다. 클라이언트는 SIGUSR2를 받으면 잠시 sleep을 한 후에 다시 통신 요청을 하기 위해 SIGUSR1을 서버에 보내고, 그 때 서버가 통신중이 아니라면 클라이언트는 서버와 통신을 시작한다. 만약 클라이언트의 통신 요청 시도가 3회 실패하면 클라이언트는 종료된다.

### 3. 시그널의 타이밍 문제 때문에 클라이언트 혹은 서버가 계속 상대의 시그널을 기다리는 경우
 시그널로만 송수신을 하기 때문에 시그널이 pending되는 과정에서 시그널이 무시되거나, 타이밍 문제 때문에 계속 서로의 시그널을 대기하며 영원히 block되는 경우가 발생할 수 있다. 클라이언트는 그럴 수 있다 쳐도 적어도 서버는 이런 상황이 발생하면 클라이언트와의 연결을 종료하고 다시 listening 상태로 전환해야한다. 따라서 서버 클라이언트 모두 pause() 함수를 사용하지 않고 sleep()함수로 상대의 시그널을 기다린다. 통신 중에 일정 시간 이상(10초 이상) 상대의 시그널이 들어오지 않으면 연결에 문제가 생긴 것으로 간주하고 통신을 종료한다. 클라이언트는 프로그램을 강제 종료하고, 서버는 통신 상태를 초기화하고 listening 상태로 전환한다. 

## 컴파일 및 실행

### 1. 컴파일
```Shell
cd 42Seoul_minitalk
make
```

### 2. 실행
#### Server
```Shell
cd server
./server
```

#### Client
```Shell
cd client
./client <Server PID> <Message>
```
