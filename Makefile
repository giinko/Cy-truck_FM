all: progc/src/traitement_t progc/src/traitement_s

progc/src/traitement_t: progc/src/traitement_t.c progc/src/fonction_t.c
	gcc progc/src/traitement_t.c progc/src/fonction_t.c -o progc/src/traitement_t

progc/src/traitement_s: progc/src/traitement_s.c progc/src/fonction_s.c
	gcc progc/src/traitement_s.c progc/src/fonction_s.c -o progc/src/traitement_s

clean:
	rm -f progc/src/traitement_t progc/src/traitement_s
