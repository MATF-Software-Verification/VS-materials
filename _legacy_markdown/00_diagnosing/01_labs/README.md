## Primeri

Primeri preuzeti sa [perf-labs](https://github.com/brendangregg/perf-labs) repozitorijuma [Brendana Gregg-a](https://www.brendangregg.com/), korišćeni tokom [prezentacije o alatima za merenje peformansi Linux kernel-a](https://youtu.be/FJW8nGV4jxY).
- lab002 
```sh
# CPU
$ top
$ htop
$ mpstat
$ mpstat 1
$ mpstat -P ALL 1

# IO
$ iotop 
$ iostat -x 1
$ vmstat 1

# network
$ sar -n DEV 1 
$ netstat -tulnp
$ ss -tunlp

# trace LISTEN
$ strace -p $(pgrep lab002)
```

- lab005

USE (Utilization, Saturation, Errors) metodologija: proverimo CPU, memoriju, disk, network IO

```sh
$ htop               # primetimo kernel vreme, idle time i wait-io
$ mpstat -P ALL 1    # da li je prebukiran jedan CPU?
$ vmstat 1           # memorija ne izgleda da je problem; nema swapping-a
$ iostat -x 1        # primetimo da je disk vrlo zauzet
$ sar -n DEV 1       # network IO nije problem
```

- lab003

```sh
$ vmstat 1           # veliki system i user time
$ pidstat 1          # lab003
$ iostat -x 1        # da li je disk uzrok?
$ sar -n DEV 1       # da li je mreza uzrok?
$ vmstat 1           # da li swapujemo?

$ strace -tp $(pgrep lab003) 2>&1 | head -n 100
# vidimo da aplikacija cita 0 bajtova u petlji
```


