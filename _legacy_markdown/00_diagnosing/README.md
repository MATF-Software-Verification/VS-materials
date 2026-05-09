# Dijagnoziranje problema

**Ciljevi**: 
  - Posmatrati program kao crnu kutiju (često ne znamo koji se kod izvršava)
  - Analizirati ponašanje kako bi se pronašli uzroci problema
  - Proširiti znanje o osnovnim alatima za merenje performansi
  - Napraviti temelj za metodičnu analizu sistema - ne možemo raditi kvalitetnu analizu ako ne znamo šta i kako možemo analizirati


## Alati za analizu performansi

Poznavanje Linux-a: Kako se procesi pokreću, gde se čuvaju informacije o procesima, uredjajima i sl.
Videti: 
  - `/proc`
  - `/sys`

Alati koje ćemo pomenuti uglavnom pristupaju fajlovima unutar pomenutih direktorijuma. 

![](00_diagnosing/linux_observability_tools.png)
Kompletan spisak se može naći na [linku](https://www.brendangregg.com/linuxperf.html).


- `uptime` 
Koristi ga `top` (i varijante kao npr. `htop`).

```sh
$ uptime
14:17:27 up  5:43,  1 user,  load average: 0.41, 0.93, 1.06
``` 

Prosek load-a je dat u intervalima od (približno) 1, 5 i 15 minuta.

### `top` / `htop`
Prikazuju izveštaj sumarno i po procesu.

Problemi:
- Mogu da lako promaknu procesi koji se brzo izvrše (u takvim slučajevima koristiti `atop`)!
- Koristi dosta resursa

### `ps`
```sh
$ ps -ef f
[...]
root        1044       1  0 08:34 ?        Ssl    0:00 /usr/bin/lightdm
root        1056    1044  7 08:34 tty7     Ssl+  26:47  \_ /usr/lib/Xorg :0 -seat seat0 -auth /run/lightdm/root/:0
root        1088    1044  0 08:34 ?        Sl     0:00  \_ lightdm --session-child 13 16
ivan        1118    1088  0 08:34 ?        Ss     0:08      \_ i3
root        1050       1  0 08:34 ?        Ssl    0:00 /usr/lib/accounts-daemon
ivan        1095       1  0 08:34 ?        Ss     0:00 /usr/lib/systemd/systemd --user
ivan        1096    1095  0 08:34 ?        S      0:00  \_ (sd-pam)
[...]
```

### `vmstat`
```sh
$ vmstat -Sm 1
procs -----------memory---------- ---swap-- -----io---- -system-- -------cpu-------
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st gu
 2  0     46    782    251   7993    0    0  3406   312 6224   35 12  4 83  1  0  0
 1  0     46    806    251   7986    0    0     0     0 2564 6940  4  3 93  0  0  0
 1  0     46    802    251   7986    0    0     0     0 1713 4499  3  2 95  0  0  0
 0  0     46    801    251   7986    0    0     0     0 1730 4536  2  2 96  0  0  0
^C
```

cpu:
 - `us` - user vreme - aplikacija, JVM...
 - `sy` - system vreme - kernel


### `iostat`
```sh
$ iostat -xmdz 1
Linux [...]   09/23/2023      _x86_64_        (8 CPU)

Device    r/s     rMB/s   rrqm/s  %rrqm r_await rareq-sz     w/s     wMB/s  ...
dm-0      8.97      0.31     0.00   0.00    0.45    35.22   22.48      0.23  ...
dm-1      0.06      0.00     0.00   0.00    0.26     5.58    0.07      0.00  ...
loop0     0.00      0.00     0.00   0.00    0.00     1.27    0.00      0.00  ...
nvme0n1   6.49      0.31     2.55  28.24    0.27    48.76   12.25      0.23  ...
sda      25.68      3.00     0.46   1.78    2.95   119.49    0.52      0.08  ...

^C
```

### `swapon`
```sh
$ swapon -s
Filename    Type            Size            Used            Priority
/dev/dm-1   partition       17898688        3991268         -2
```

### `mpstat`
```sh
$ mpstat -P ALL 1
Linux [...]   09/23/2023      _x86_64_        (8 CPU)

CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
all    4.14    0.00    2.01    0.50    0.38    0.25    0.00    0.00    0.00   92.73
  0    3.03    0.00    1.01    0.00    0.00    1.01    0.00    0.00    0.00   94.95
  1    5.94    0.00    2.97    0.00    0.00    0.00    0.00    0.00    0.00   91.09
  2    3.96    0.00    1.98    0.00    0.99    0.99    0.00    0.00    0.00   92.08
  3    4.04    0.00    2.02    0.00    1.01    0.00    0.00    0.00    0.00   92.93
  4    5.00    0.00    1.00    0.00    1.00    0.00    0.00    0.00    0.00   93.00
  5    4.00    0.00    1.00    0.00    0.00    0.00    0.00    0.00    0.00   95.00
  6    3.06    0.00    3.06    4.08    0.00    0.00    0.00    0.00    0.00   89.80
  7    4.00    0.00    3.00    0.00    0.00    0.00    0.00    0.00    0.00   93.00
^C
```

### `lsof`

Prikazuje otvorene fajl deskriptore.

### `pidstat`
```sh
$ pidstat -t 1
11:04:46 AM   UID       PID    %usr %system  %guest   %wait    %CPU   CPU  Command
11:04:46 AM     0         1    0.00    0.00    0.00    0.00    0.01     1  systemd
11:04:46 AM     0         2    0.00    0.00    0.00    0.00    0.00     3  kthreadd
11:04:46 AM     0        15    0.00    0.00    0.00    0.00    0.00     0  ksoftirqd/0
11:04:46 AM     0        16    0.00    0.02    0.00    0.01    0.02     4  rcu_preempt
11:04:46 AM     0        18    0.00    0.00    0.00    0.00    0.00     0  migration/0
11:04:46 AM     0        24    0.00    0.00    0.00    0.00    0.00     1  migration/1
11:04:46 AM     0        25    0.00    0.00    0.00    0.00    0.00     1  ksoftirqd/1
11:04:46 AM     0        30    0.00    0.00    0.00    0.00    0.00     2  migration/2
11:04:46 AM     0        31    0.00    0.01    0.00    0.00    0.01     2  ksoftirqd/2
11:04:46 AM     0        36    0.00    0.00    0.00    0.00    0.00     3  migration/3
11:04:46 AM     0        37    0.00    0.00    0.00    0.00    0.00     3  ksoftirqd/3
^C
```

### `strace` 

`strace` - *System Call Tracer*. Može takođe da prevede argumente sistemskih poziva. Baziran na `ptrace`. Može da uspori izvršavanje i do 100x.

```sh
$ strace ls
execve("/usr/bin/ls", ["ls"], 0x7fffc329f270 /* 131 vars */) = 0
brk(NULL)                               = 0x55e00371d000

[...]

close(3)                                = 0
openat(AT_FDCWD, "/usr/lib/libcap.so.2", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0 s\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=42992, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f76305ec000
mmap(NULL, 45128, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f76305e0000
mmap(0x7f76305e3000, 20480, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x3000) = 0x7f76305e3000
mmap(0x7f76305e8000, 8192, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x8000) = 0x7f76305e8000
mmap(0x7f76305ea000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x9000) = 0x7f76305ea000
close(3)

[...]
```

```sh
$ strace -e close ls
close(3)                                = 0
close(3)                                = 0
close(3)                                = 0
close(3)                                = 0
close(3)                                = 0
INDEX     lab002.c  lab004.c  lab006.c  lab008.c  Makefile
lab001.c  lab003.c  lab005.c  lab007.c  lab013.c  README.md
close(1)                                = 0
close(2)                                = 0
+++ exited with 0 +++
```

```sh
$ strace -t -r -p <PID> -o <REPORT_OUTPUT>
# -t - timestamp
# -r - relative time for each syscall
# -p - PID
# -o - output path
```

```sh
$ strace -c ls
INDEX     lab002.c  lab004.c  lab006.c  lab008.c  Makefile
lab001.c  lab003.c  lab005.c  lab007.c  lab013.c  README.md
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
  0.00    0.000000           0         2           read
  0.00    0.000000           0         2           write
  0.00    0.000000           0         7           close
  0.00    0.000000           0        13           mmap
  0.00    0.000000           0         4           mprotect
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         3           brk
  0.00    0.000000           0         2           ioctl
  0.00    0.000000           0         2           pread64
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         6         4 prctl
  0.00    0.000000           0         2         1 arch_prctl
  0.00    0.000000           0         2           getdents64
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         5           openat
  0.00    0.000000           0         6           newfstatat
  0.00    0.000000           0         1           set_robust_list
  0.00    0.000000           0         1           prlimit64
  0.00    0.000000           0         1           getrandom
  0.00    0.000000           0         1           rseq
------ ----------- ----------- --------- --------- ----------------
100.00    0.000000           0        64         6 total

```

### Analiza mreže

Osim alata specifično namenjenih za duboku analizu mrežnih protokola (npr. [`Wireshark`](https://www.wireshark.org/)), korisno je znati kako brzo dobiti informacije o ostvarenim konekcijama i programima koji su se vezali na odgovarajuće portove.

#### `tcpdump`

Prikazuje odlazne/dolazne TCP pakete na odgovarajućem portu.
```sh
$ sudo tcpdump dst port 123
tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
listening on eth0, link-type EN10MB (Ethernet), capture size 65535 bytes
21:02:19.112502 IP test33.ntp > 199.30.140.74.ntp: NTPv4, Client, length 48
21:02:19.113888 IP 216.239.35.0.ntp > test33.ntp: NTPv4, Server, length 48
21:02:20.150347 IP test33.ntp > 216.239.35.0.ntp: NTPv4, Client, length 48
21:02:20.150991 IP 216.239.35.0.ntp > test33.ntp: NTPv4, Server, length 48
```

#### `netstat` / `ss`

Prikazuju informacije o konekcijama i soketima, konfigurabilni po protokolu i stanju.
```sh
$ netstat -tulnp
Active Internet connections (only servers)
Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name
tcp        0      0 127.0.0.1:57343         0.0.0.0:*               LISTEN      3501/steam
tcp        0      0 0.0.0.0:27036           0.0.0.0:*               LISTEN      3501/steam
tcp        0      0 127.0.0.1:33095         0.0.0.0:*               LISTEN      3501/steam
tcp        0      0 127.0.0.1:35831         0.0.0.0:*               LISTEN      3501/steam
tcp        0      0 127.0.0.1:43221         0.0.0.0:*               LISTEN      -
tcp        0      0 127.0.0.1:27060         0.0.0.0:*               LISTEN      3501/steam
tcp6       0      0 ::1:631                 :::*                    LISTEN      -
tcp6       0      0 :::6600                 :::*                    LISTEN      1135/mpd
udp        0      0 0.0.0.0:27036           0.0.0.0:*                           3501/steam
udp        0      0 0.0.0.0:5353            0.0.0.0:*                           -
udp        0      0 0.0.0.0:46653           0.0.0.0:*                           -
udp        0      0 0.0.0.0:38865           0.0.0.0:*                           -
udp6       0      0 :::44350                :::*                                -
udp6       0      0 :::5353                 :::*                                -
udp6       0      0 :::46653                :::*                                -
```

`netstat` zamenjuje kompletniji alat `ss`.
```sh
$ ss -tunpl
Netid State  Recv-Q Send-Q  Local Address:Port    Peer Address:Port Process
udp   UNCONN 0      0             0.0.0.0:27036        0.0.0.0:*     users:(("steam",pid=3501,fd=123))
udp   UNCONN 0      0             0.0.0.0:5353         0.0.0.0:*
udp   UNCONN 0      0             0.0.0.0:46653        0.0.0.0:*
udp   UNCONN 0      0             0.0.0.0:38865        0.0.0.0:*
udp   UNCONN 0      0                [::]:44350           [::]:*
udp   UNCONN 0      0                [::]:5353            [::]:*
udp   UNCONN 0      0                [::]:46653           [::]:*
tcp   LISTEN 0      128         127.0.0.1:57343        0.0.0.0:*     users:(("steam",pid=3501,fd=48))
tcp   LISTEN 0      128           0.0.0.0:27036        0.0.0.0:*     users:(("steam",pid=3501,fd=124))
tcp   LISTEN 0      4096        127.0.0.1:631          0.0.0.0:*
tcp   LISTEN 0      128         127.0.0.1:33095        0.0.0.0:*     users:(("steam",pid=3501,fd=53))
tcp   LISTEN 0      128         127.0.0.1:35831        0.0.0.0:*     users:(("steam",pid=3501,fd=83))
tcp   LISTEN 0      4096        127.0.0.1:43221        0.0.0.0:*
tcp   LISTEN 0      128         127.0.0.1:27060        0.0.0.0:*     users:(("steam",pid=3501,fd=84))
tcp   LISTEN 0      4096            [::1]:631             [::]:*
tcp   LISTEN 0      5                   *:6600               *:*     users:(("mpd",pid=1135,fd=4))
```

### System Activity Reporter (`sar`)

Može da prati iskorišćenost CPU, RAM memorije, swap memorije, mrežnih uredjaja itd.

```sh
$ sar -u 1 3
11:12:22 AM     CPU     %user     %nice   %system   %iowait    %steal     %idle
11:12:23 AM     all      3.88      0.00      1.88      0.25      0.00     93.99
11:12:24 AM     all      4.45      0.00      1.11      0.12      0.00     94.31
11:12:25 AM     all      3.98      0.00      1.99      0.25      0.00     93.78
Average:        all      4.10      0.00      1.66      0.21      0.00     94.03
```

```sh
$ sar -r 1 3
11:13:26 AM kbmemfree   kbavail kbmemused  %memused kbbuffers  kbcached  kbcommit   %commit  kbactive   kbinact   kbdirty
11:13:27 AM   5841564   7857352   7545328     46.37     31224   2286720  21332312     62.43   6722340   1418056      1004
11:13:28 AM   5841060   7856848   7545928     46.38     31224   2286720  21328940     62.42   6722596   1418048         0
11:13:29 AM   5837028   7852948   7549820     46.40     31232   2286852  21332780     62.43   6725632   1418188        76
Average:      5839884   7855716   7547025     46.38     31227   2286764  21331344     62.43   6723523   1418097       360
```

```sh
$ sar -n DEV 1 1
11:14:55 AM     IFACE   rxpck/s   txpck/s    rxkB/s    txkB/s   rxcmp/s   txcmp/s  rxmcst/s   %ifutil
11:14:56 AM        lo      9.00      9.00      0.74      0.74      0.00      0.00      0.00      0.00
11:14:56 AM    enp3s0      0.00      0.00      0.00      0.00      0.00      0.00      0.00      0.00
11:14:56 AM    wlp2s0      1.00      2.00      0.38      1.20      0.00      0.00      0.00      0.00
11:14:56 AM   docker0      0.00      0.00      0.00      0.00      0.00      0.00      0.00      0.00
11:14:56 AM  nordlynx      1.00      2.00      0.34      1.08      0.00      0.00      0.00      0.00

Average:        IFACE   rxpck/s   txpck/s    rxkB/s    txkB/s   rxcmp/s   txcmp/s  rxmcst/s   %ifutil
Average:           lo      9.00      9.00      0.74      0.74      0.00      0.00      0.00      0.00
Average:       enp3s0      0.00      0.00      0.00      0.00      0.00      0.00      0.00      0.00
Average:       wlp2s0      1.00      2.00      0.38      1.20      0.00      0.00      0.00      0.00
Average:      docker0      0.00      0.00      0.00      0.00      0.00      0.00      0.00      0.00
Average:     nordlynx      1.00      2.00      0.34      1.08      0.00      0.00      0.00      0.00
```
