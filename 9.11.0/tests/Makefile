CC = gcc -flto
CFLAGS = -march=native -O3 -Wall -Wextra
LIBS = -lquadmath -lm
src1 = series.c
res1 = precision
src2 = bounds.c
res2 = limits

all: $(res2) $(res1)

$(res1): $(src1) Makefile
	$(CC) $(CFLAGS) $(src1) -o series -DPRECISION=4 $(LIBS)
	strip series
	./series > $(res1)

$(res2): $(src2) Makefile
	$(CC) $(CFLAGS) $(src2) -o bounds -DPRECISION=4 $(LIBS)
	strip bounds
	./bounds > $(res2)
