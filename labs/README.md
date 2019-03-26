Tasks:
1. stack memory corruption - shellcode
2. stack memory corruption - underflow, insufficient index check
3. stack memory corruption - overflow, binary protocol, unchecked len
4. stack memory corruption - off-by-one, rbp null poisoning (assumption: rbp & 0xf == 0)
5. infoleak - ASLR, invalid C string, arbitrary write, got overwrite
6. integer overflow, read-what-where, write-what-where, ret2libc - [35c3ctf sum](https://junior.35c3ctf.ccc.ac/uploads/sum-b22202e31d8d84ec55a8f7cb698e2d656622f806.zip)
7. ROP basics - [ROP Emporium callme](https://ropemporium.com/challenge/callme.html)
8. More ROP - [ROP Emporium badchars](https://ropemporium.com/challenge/badchars.html)
9. ROP chain pivoting - [ROP Emporium pivot](https://ropemporium.com/challenge/pivot.html)
10. Format string - stack format string, infoleak, full relro


Tools:
* [pwntools](https://github.com/Gallopsled/pwntools)
* [Cool video, smash like and subscribe](https://www.youtube.com/watch?v=zsh-3J-fTSk&t=4661s)
* [gef](https://github.com/hugsy/gef)
* checksec
* [ROPgadget](https://github.com/JonathanSalwan/ROPgadget)
* [ropper](https://github.com/sashs/Ropper)
* [onegadget](https://github.com/david942j/one_gadget)
* [valgrind](http://valgrind.org/)
* [AFL](http://lcamtuf.coredump.cx/afl/)
* [sanitizers](https://github.com/google/sanitizers)
