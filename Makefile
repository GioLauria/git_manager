CC = gcc
CFLAGS = -O2 -Wall
TARGETS = git_manager clean_tags automatic_readme_generator

all: $(TARGETS)

git_manager: git_manager.c
	$(CC) $(CFLAGS) -o $@ git_manager.c

clean_tags: clean_tags.c
	$(CC) $(CFLAGS) -o $@ clean_tags.c

automatic_readme_generator: automatic_readme_generator.c
	$(CC) $(CFLAGS) -o $@ automatic_readme_generator.c

clean:
	rm -f $(TARGETS) *.o README.md.tmp
