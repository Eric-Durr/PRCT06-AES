# SSI P06 - IMPLEMENTACIÓN DE AES

[![C/C++ CI](https://github.com/Eric-Durr/PRCT06-AES/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/Eric-Durr/PRCT06-AES/actions/workflows/c-cpp.yml)

> Se implementa el algoritmo de Rijndael.

**Estructura del repositorio:**

```
prct06-AES/
├─ docs/                                        # Project documentation folder
├─ include/                                     # Library files folder
│  ├─ Catch2/catch.h                            ## C++ TDD testing framework
├─ src/                                         # Source files folder
├─ test/                                        # Test files folder
├─ .gitignore                                   # Ignored files git config file
├─ makefile                                     # C++ tasks automation file
├─ Doxyfile                                     # Doxygen configuration file 
├─ ASSIGNMENT.pdf                                # P06 - assignment
├─ README.md                                    # Front repository information file
```

**Uso**

**Compilación del ejecutable**

```bash
$ make
```

**Ejecución del programa**

```bash
$ ./aes_simulator <key> <input> ["trace"]
```

**Ejemplos**

```
./aes_simulator 000102030405060708090a0b0c0d0e0f 00112233445566778899aabbccddeeff
--- Encriptado AES de 128 b ---

 Bloque de texto plano origen:

04488cc
115599dd
2266aaee
3377bbff


 Bloque encriptado resultante:
696ad870
c47bcdb4
e04b7c5
d830805a
```

```
./aes_simulator 000102030405060708090a0b0c0d0e0f 00112233445566778899aabbccddeeff trace
--- Encriptado AES de 128 b ---

 Bloque de texto plano origen:

04488cc
115599dd
2266aaee
3377bbff
LAP 0:
R0 (Subclave =0 1 2 3 4 5 6 7 8 9 a b c d e f ) = 0 10 20 30 40 50 60 70 80 90 a0 b0 c0 d0 e0 f0
LAP 1:
R1 (Subclave =d6 aa 74 fd d2 af 72 fa da a6 78 f1 d6 ab 76 fe ) = 89 d8 10 e8 85 5a ce 68 2d 18 43 d8 cb 12 8f e4
LAP 2:
R2 (Subclave =b6 92 cf b 64 3d bd f1 be 9b c5 0 68 30 b3 fe ) = 49 15 59 8f 55 e5 d7 a0 da ca 94 fa 1f a 63 f7
LAP 3:
R3 (Subclave =b6 ff 74 4e d2 c2 c9 bf 6c 59 c bf 4 69 bf 41 ) = fa 63 6a 28 25 b3 39 c9 40 66 8a 31 57 24 4d 17
LAP 4:
R4 (Subclave =47 f7 f7 bc 95 35 3e 3 f9 6c 32 bc fd 5 8d fd ) = 24 72 40 23 69 66 b3 fa 6e d2 75 32 88 42 5b 6c
LAP 5:
R5 (Subclave =3c aa a3 e8 a9 9f 9d eb 50 f3 af 57 ad f6 22 aa ) = c8 16 77 bc 9b 7a c9 3b 25 2 79 92 b0 26 19 96
LAP 6:
R6 (Subclave =5e 39 f 7d f7 a6 92 96 a7 55 3d c1 a a3 1f 6b ) = c6 2f e1 9 f7 5e ed c3 cc 79 39 5d 84 f9 cf 5d
LAP 7:
R7 (Subclave =14 f9 70 1a e3 5f e2 8c 44 a df 4d 4e a9 c0 26 ) = d1 87 6c f 79 c4 30 a b4 55 94 ad d6 6f f4 1f
LAP 8:
R8 (Subclave =47 43 87 35 a4 1c 65 b9 e0 16 ba f4 ae bf 7a d2 ) = fd e3 ba d2 5 e5 d0 d7 35 47 96 4e f1 fe 37 f1
LAP 9:
R9 (Subclave =54 99 32 d1 f0 85 57 68 10 93 ed 9c be 2c 97 4e ) = bd 6e 7c 3d f2 b5 77 9e b 61 21 6e 8b 10 b6 89
LAP a:
R10 (Subclave =13 11 1d 7f e3 94 4a 17 f3 7 a7 8b 4d 2b 30 c5 ) = 69 c4 e0 d8 6a 7b 4 30 d8 cd b7 80 70 b4 c5 5a
Bloque de texto cifrado: 69 c4 e0 d8 6a 7b 4 30 d8 cd b7 80 70 b4 c5 5a


 Bloque encriptado resultante:
696ad870
c47bcdb4
e04b7c5
d830805a
```

**Lanzamiento de los tests**
```bash
$ make test
```

Se compila y ejecuta el conjunto de tests para luego ejecutarlos, de suceder satisfactoriamente debe aparecer lo siguiente por terminal:

También se puede ejecutar un despliegue detallado de los tests si ya se ha lanzado el comando anterior:

```bash
$ ./aes_simulator_test -s
```

**AES S-box**
```
                            Y
      ______________________________________________
   __|0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
  |0 63 7c 77 7b f2 6b 6f c5 30 01 67 2b fe d7 ab 76 
  |1 ca 82 c9 7d fa 59 47 f0 ad d4 a2 af 9c a4 72 c0
  |2 b7 fd 93 26 36 3f f7 cc 34 a5 e5 f1 71 d8 31 15
  |3 04 c7 23 c3 18 96 05 9a 07 12 80 e2 eb 27 b2 75
  |4 09 83 2c 1a 1b 6e 5a a0 52 3b d6 b3 29 e3 2f 84
  |5 53 d1 00 ed 20 fc b1 5b 6a cb be 39 4a 4c 58 cf
  |6 d0 ef aa fb 43 4d 33 85 45 f9 02 7f 50 3c 9f a8
X |7 51 a3 40 8f 92 9d 38 f5 bc b6 da 21 10 ff f3 d2
  |8 cd 0c 13 ec 5f 97 44 17 c4 a7 7e 3d 64 5d 19 73
  |9 60 81 4f dc 22 2a 90 88 46 ee b8 14 de 5e 0b db
  |a e0 32 3a 0a 49 06 24 5c c2 d3 ac 62 91 95 e4 79
  |b e7 c8 37 6d 8d d5 4e a9 6c 56 f4 ea 65 7a ae 08
  |c ba 78 25 2e 1c a6 b4 c6 e8 dd 74 1f 4b bd 8b 8a  
  |d 70 3e b5 66 48 03 f6 0e 61 35 57 b9 86 c1 1d 9e
  |e e1 f8 98 11 69 d9 8e 94 9b 1e 87 e9 ce 55 28 df 
  |f 8c a1 89 0d bf e6 42 68 41 99 2d 0f b0 54 bb 16 
```


**Referencias y enlaces:**

- [Enlace al repositorio](https://github.com/Eric-Durr/PRCT06-AES)
- [Tutorial de Doxygen para C++](https://caiorss.github.io/C-Cpp-Notes/Doxygen-documentation.html)
- [Convert hex string to integer](https://www.includehelp.com/stl/convert-hex-string-to-integer-using-stoi-function-in-cpp-stl.aspx)
- [C++ bitwise operators - tutorials point](https://www.tutorialspoint.com/cplusplus/cpp_bitwise_operators.htm)
- [how to read specific bits with bitwise operators - stack overflow](https://stackoverflow.com/questions/19626652/how-to-read-specific-bits-of-an-unsigned-int)

- [Free online AES encryption and decryption tool - CODEPY](https://codepy.io/aes.html)

- [AES explaineed step by step - the sslstore](https://www.thesslstore.com/blog/advanced-encryption-standard-aes-what-it-is-and-how-it-works/)

- [AES Explained - computherphile in YouTube](https://www.youtube.com/watch?v=O4xNJsjtN6E&t=453s)

- [SergyBel`s AES implementation - GitHub](https://github.com/SergeyBel/AES)

**[Documentación online](https://eric-durr.github.io/PRCT06-AES/)**

**Licencia**

[MIT](https://choosealicense.com/licenses/mit/)

**Autoría**

- Eric Dürr Sierra - [alu0101027005](alu0101027005@ull.edu.es)

