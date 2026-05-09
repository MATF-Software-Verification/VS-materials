#### Zadržavanje katanaca

Prilikom rada niti može doći do pojave zadržavanja katanca *(eng. lock
contention)*, pri kojoj jedna nit ne može da radi zbog blokiranja drugih
niti. Dešava se da nit mora da čeka da muteks ili sinhronizacioni
reader-write objekat budu otključani od strane druge niti. Ovakva pojava
je nepoželjna u višenitnim sistemima, alat *DRD* otkriva ovaj tip
problema. Zadržavanje katanaca stvara kašnjenja, koja bi trebalo da budu
što je moguće kraća. Opcije `–exclusive-threshold=<n>` i
`–shared-threshold=<n>` omogućavaju da DRD otkrije preterano zadržavanje
katanca, tako što će prijaviti svako zadržavanje katanca koje je duže od
zadatog praga. Alat *Helgrind* ne otkriva ovakav tip grešaka.

Pokrenimo DRD za primer `hold_lock.c`. Program dobija preko argumenata komandne linije `-i 500` da bi između zaključavanja i otključavanja muteksa bio uspavan 500ms.
```sh
$ valgrind –tool=drd –exclusive-threshold=10 ./hard_lock -i 500
```

*DRD* nam generiše izveštaj o nitima koje su prekoračile vreme od 10ms
koje smo zadali opcijom `–exclusive-threshold=10`

```txt
Locking mutex ...
==25008== Acquired at:
==25008==    at 0x4C3725B: pthread_mutex_lock (in /usr/lib/valgrind/vgpreload_drd-amd64-linux.so)
==25008==    by 0x400E1C: main (07_hold_lock.c:51)
==25008== Lock on mutex 0xffefff8f0 was held during 505 ms (threshold: 10 ms).
==25008==    at 0x4C3818C: pthread_mutex_unlock (in /usr/lib/valgrind/vgpreload_drd-amd64-linux.so)
==25008==    by 0x400E4D: main (07_hold_lock.c:55)
==25008== mutex 0xffefff8f0 was first observed at:
==25008==    at 0x4C36719: pthread_mutex_init (in /usr/lib/valgrind/vgpreload_drd-amd64-linux.so)
==25008==    by 0x400E04: main (07_hold_lock.c:49)
==25008==
Locking rwlock exclusively ...
==25008== Acquired at:
==25008==    at 0x4C3F484: pthread_rwlock_wrlock (in /usr/lib/valgrind/vgpreload_drd-amd64-linux.so)
==25008==    by 0x400E94: main (07_hold_lock.c:61)
==25008== Lock on rwlock 0xffefff920 was held during 502 ms (threshold: 10 ms).
==25008==    at 0x4C40955: pthread_rwlock_unlock (in /usr/lib/valgrind/vgpreload_drd-amd64-linux.so)
==25008==    by 0x400EAD: main (07_hold_lock.c:63)
==25008== rwlock 0xffefff920 was first observed at:
==25008==    at 0x4C3E705: pthread_rwlock_init (in /usr/lib/valgrind/vgpreload_drd-amd64-linux.so)
==25008==    by 0x400E88: main (07_hold_lock.c:60)
==25008==
Locking rwlock shared ...
Done.
```

Ovako dolazimo do saznanja u kojoj liniji je zaključan neki od katanaca i koliko se dugo držao dok nije otključan.

