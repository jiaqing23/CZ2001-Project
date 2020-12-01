# String Matching Algorithm

This folder contains 3 string matching algorithms' implementation(written in C++)

* Brute Force
* KMP(Knuth–Morris–Pratt) Algorithm
* and a ... self-proposed algorithm

## Notation

There are many different terminology in string matching. We will use the following notation:

* Let say we want to search `ATAT` in `CGCGCGATATCGCGCG`
* `ATAT` is called Pattern String ( P )
* `CGCGCGATATCGCGCG` is called Searching String ( S )

## Usage

### Manual Input without File Reading

Be aware, these code are implement based on the assumption that, pattern string only contains of genome sequence alphabet(`A`, `T`, `C`, `G`) and without spacing. If user input are in lowercase, the program will convert it to uppercase and match it.

If you wish to enter the string manually(not reading from file), type **one of the following command**:

```
$ BruteForce
$ KMP
$ Own
```

The program will then show `P:`, enter your pattern string(without spacing and line change). Click enter and program will show `S:`, enter your searching string. We allow user the key in multiline searching string with spacing and any character. After finishing your key in, press `Enter` and `Ctrl+Z` and `Enter` again (For linux user, use `Ctrl-D` instead).

### File Reading

If you wish to read pattern string from file, **put the pattern string on the first line in the file** and type **one of the following command**:

```
$ BruteForce < <span class="hljs-variable">${FILENAME}</span>
$ KMP < <span class="hljs-variable">${FILENAME}</span>
$ Own < <span class="hljs-variable">${FILENAME}</span>
```

For example:

```
$ BruteForce < genome123456.fna
```

If you want to key in pattern string manually, type **one of the following command**:

```
$ BruteForce <span class="hljs-variable">${PATTERN STRING}</span> < <span class="hljs-variable">${FILENAME}</span>
$ KMP <span class="hljs-variable">${PATTERN STRING}</span> < <span class="hljs-variable">${FILENAME}</span>
$ Own <span class="hljs-variable">${PATTERN STRING}</span> < <span class="hljs-variable">${FILENAME}</span>
```

For example:

```
$ BruteForce ATCGGCTAA < genome123456.fna
```

### Limitation

The program will read whole searching string and keep in into buffer, so the maximum file size could read is about **500 MB**.

### But! I need to read a big file!

We have implement another code of KMP Algorithm which can read any size of file (but reading huge file is slow, be aware). The command is similar:

```
$ KMP_large
```

```
$ KMP_large < <span class="hljs-variable">${FILENAME}</span>
```

```
$ KMP_large <span class="hljs-variable">${PATTERN STRING}</span> < <span class="hljs-variable">${FILENAME}</span>
```
