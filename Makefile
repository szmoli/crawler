# config
out_dir := out
src_dir := src
conf_dir := conf
CC := gcc
out_name := build.out

# rules
build: $(wildcard $(src_dir)/*.c)
	$(CC) -g $^ -o $(out_dir)/$(out_name) -lm

run:
	$(out_dir)/$(out_name)

clean:
	rm -rf $(out_dir)/*