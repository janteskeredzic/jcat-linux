# jcat

A custom recration of the Linux tool 'cat'.
Recreated for learning purposes and expanded with custom execution flags:

-n (numbered lines)
-s (display file size)
-E (show line end with $)


#BUILDING

###To build jcat you need gcc:

```shell
sudo apt install gcc
```

###After you ahve installed gcc build simply by using:

```shell
gcc -Wall jcat.c -o jcat
```

#Usage

```shell
./jcat -n -s sampletext.txt
```
